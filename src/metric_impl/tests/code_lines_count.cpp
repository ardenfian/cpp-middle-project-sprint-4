#include "metric_impl/code_lines_count.hpp"

#include <gtest/gtest.h>
#include <vector>

#include "function.hpp"
#include "metric.hpp"

namespace analyzer::metric::metric_impl {

// здесь ваш код
// TEST(BasicCheck, Sum) { EXPECT_EQ(1 + 1, 2); }

TEST(CODE_LINES_COUNT, comments) {

    function::FunctionExtractor extractor;
    file::File tstFile("../../../src/metric_impl/tests/files/comments.py");

    std::vector<function::Function> funcs = extractor.Get(tstFile);

    CodeLinesCountMetric metric;

    MetricResult res = metric.Calculate(funcs.front());

    EXPECT_EQ(res.value, 3);
}

TEST(CODE_LINES_COUNT, exceptions) {

    function::FunctionExtractor extractor;
    file::File tstFile("../../../src/metric_impl/tests/files/exceptions.py");

    std::vector<function::Function> funcs = extractor.Get(tstFile);

    CodeLinesCountMetric metric;

    MetricResult res = metric.Calculate(funcs.front());

    EXPECT_EQ(res.value, 7);
}

TEST(CODE_LINES_COUNT, if_test) {

    function::FunctionExtractor extractor;
    std::string tstFile = "../../../src/metric_impl/tests/files/if.py";

    std::vector<function::Function> funcs = extractor.Get(tstFile);

    CodeLinesCountMetric metric;

    MetricResult res = metric.Calculate(funcs.front());

    EXPECT_EQ(res.value, 3);
}

TEST(CODE_LINES_COUNT, loops) {
    function::FunctionExtractor extractor;

    std::string tstFile = "../../../src/metric_impl/tests/files/loops.py";

    std::vector<function::Function> funcs = extractor.Get(tstFile);

    CodeLinesCountMetric metric;

    MetricResult res = metric.Calculate(funcs.front());

    EXPECT_EQ(res.value, 6);
}

TEST(CODE_LINES_COUNT, many_lines) {
    function::FunctionExtractor extractor;

    std::string tstFile = "../../../src/metric_impl/tests/files/many_lines.py";

    std::vector<function::Function> funcs = extractor.Get(tstFile);

    CodeLinesCountMetric metric;

    MetricResult res = metric.Calculate(funcs.front());

    EXPECT_EQ(res.value, 11);
}

TEST(CODE_LINES_COUNT, many_parameters) {
    function::FunctionExtractor extractor;

    std::string tstFile = "../../../src/metric_impl/tests/files/many_parameters.py";

    std::vector<function::Function> funcs = extractor.Get(tstFile);

    CodeLinesCountMetric metric;

    MetricResult res = metric.Calculate(funcs.front());

    EXPECT_EQ(res.value, 1);
}

TEST(CODE_LINES_COUNT, match_case) {
    function::FunctionExtractor extractor;

    std::string tstFile = "../../../src/metric_impl/tests/files/match_case.py";

    std::vector<function::Function> funcs = extractor.Get(tstFile);

    CodeLinesCountMetric metric;

    MetricResult res = metric.Calculate(funcs.front());

    EXPECT_EQ(res.value, 7);
}

TEST(CODE_LINES_COUNT, nested_if) {
    function::FunctionExtractor extractor;

    std::string tstFile = "../../../src/metric_impl/tests/files/nested_if.py";

    std::vector<function::Function> funcs = extractor.Get(tstFile);

    CodeLinesCountMetric metric;

    MetricResult res = metric.Calculate(funcs.front());

    EXPECT_EQ(res.value, 8);
}

TEST(CODE_LINES_COUNT, simple) {
    function::FunctionExtractor extractor;

    std::string tstFile = "../../../src/metric_impl/tests/files/simple.py";

    std::vector<function::Function> funcs = extractor.Get(tstFile);

    CodeLinesCountMetric metric;

    MetricResult res = metric.Calculate(funcs.front());

    EXPECT_EQ(res.value, 5);
}

TEST(CODE_LINES_COUNT, ternary) {
    function::FunctionExtractor extractor;

    std::string tstFile = "../../../src/metric_impl/tests/files/ternary.py";

    std::vector<function::Function> funcs = extractor.Get(tstFile);

    CodeLinesCountMetric metric;

    MetricResult res = metric.Calculate(funcs.front());

    EXPECT_EQ(res.value, 1);
}

}  // namespace analyzer::metric::metric_impl
