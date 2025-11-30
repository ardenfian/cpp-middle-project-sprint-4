#include <exception>
#include <stdexcept>
#include <unistd.h>

#include <algorithm>
#include <array>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <filesystem>
#include <fstream>
#include <functional>
#include <iomanip>
#include <iostream>
#include <print>
#include <ranges>
#include <sstream>
#include <string>
#include <utility>
#include <variant>
#include <vector>

#include "file.hpp"
#include "function.hpp"
#include "metric.hpp"
#include "metric_accumulator.hpp"

namespace analyzer {

namespace rv = std::ranges::views;
namespace rs = std::ranges;
/**
 * @brief Анализирует список Python-файлов и извлекает метрики для всех функций и методов.
 *
 * Эта функция — центральный "конвейер" обработки:
 * 1. Принимает имена файлов.
 * 2. Для каждого файла создаёт объект `File`, который автоматически парсит его через tree-sitter
 *    и строит AST.
 * 3. Извлекает из AST все функции и методы с помощью `FunctionExtractor`.
 * 4. Объединяет все функции из всех файлов в один плоский список (`join`).
 * 5. Для каждой функции вычисляет набор метрик через переданный `metric_extractor`.
 * 6. Возвращает вектор пар: (функция, результаты её метрик).
 */
auto AnalyseFunctions(const std::vector<std::string> &files,
                      const analyzer::metric::MetricExtractor &metric_extractor) {
    auto getFileAst = [&](const std::string &fileName) -> file::File {
        try {
            return file::File(fileName);
        } catch (const std::exception &e) {
            std::print("{}", e.what());
            throw std::runtime_error("File does not exist");
        }
    };

    auto getFuncs = [&](const file::File &file) -> std::vector<function::Function> {
        function::FunctionExtractor extractor;
        return extractor.Get(file);
    };

    auto getMetrics = [&](const function::Function &func) -> std::pair<function::Function, metric::MetricResults> {
        return std::make_pair(func, metric_extractor.Get(func));
    };

    auto astFiles = files | std::views::transform(getFileAst);
    auto allFuncs = astFiles | std::views::transform(getFuncs) | std::views::join;
    auto allMetrics = allFuncs | std::views::transform(getMetrics) | std::ranges::to<std::vector>();

    return allMetrics;
}

/**
 *
 * @brief Группирует результаты анализа по классам.
 *
 * Эта функция:
 * 1. Отфильтровывает только те функции, которые являются **методами классов**
 *    (у них `class_name.has_value()` == true).
 * 2. Группирует последовательные элементы с одинаковым именем класса с помощью `chunk_by`.
 *
 * Важно:
 * - `chunk_by` работает только с **последовательными** одинаковыми элементами!
 *   Поэтому предполагается, что входной диапазон уже упорядочен по классам
 *   (например, порядок методов в AST сохраняется как в исходном файле).
 * - Если порядок нарушен, один и тот же класс может быть разбит на несколько групп.
 *
 *  Чтобы убедиться, что фильтрация работает, проверьте, что свободные функции (без class_name)
 * действительно исчезают из результата.
 */
auto SplitByClasses(const auto &analysis) {
    auto filterClassFuncs = [](const std::pair<function::Function, metric::MetricResults> &result) {
        return result.first.class_name.has_value();
    };

    auto compareClass = [](const std::pair<function::Function, metric::MetricResults> &lhs,
                           const std::pair<function::Function, metric::MetricResults> &rhs) {
        return lhs.first.class_name == rhs.first.class_name;
    };

    return analysis | std::views::filter(filterClassFuncs) | std::views::chunk_by(compareClass) |
           std::ranges::to<std::vector>();
}

/**
 * @brief Группирует результаты анализа по исходным файлам.
 *
 * Эта функция:
 * - Разбивает весь список функций на группы, где каждая группа содержит
 *   только функции из одного и того же файла (`filename`).
 * - Использует `chunk_by`, поэтому **порядок функций в `analysis` должен быть по файлам**.
 */
auto SplitByFiles(const auto &analysis) {
    auto compareFileNames = [](const std::pair<function::Function, metric::MetricResults> &lhs,
                               const std::pair<function::Function, metric::MetricResults> &rhs) {
        return lhs.first.filename == rhs.first.filename;
    };

    return analysis | std::views::chunk_by(compareFileNames) | std::ranges::to<std::vector>();
}

/**
 * @brief Агрегирует метрики всех функций с помощью аккумулятора.
 *
 * Эта функция:
 * - Проходит по каждому элементу результата `AnalyseFunctions`
 *   (то есть по каждой функции и её метрикам).
 * - Передаёт результаты метрик (`elem.second`) в аккумулятор через `AccumulateNextFunctionResults`.
 */
void AccumulateFunctionAnalysis(const auto &analysis,
                                const analyzer::metric_accumulator::MetricsAccumulator &accumulator) {
    std::ranges::for_each(analysis, [&](const auto &elem) { accumulator.AccumulateNextFunctionResults(elem.second); });
}

}  // namespace analyzer
