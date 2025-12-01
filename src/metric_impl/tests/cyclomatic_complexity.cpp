#include "metric_impl/cyclomatic_complexity.hpp"

#include <gtest/gtest.h>

namespace analyzer::metric::metric_impl {

TEST(CYCLOMATIC_COMPLEXITY, comments) {

    function::FunctionExtractor extractor;
    file::File tstFile("../../../src/metric_impl/tests/files/comments.py");

    std::vector<function::Function> funcs = extractor.Get(tstFile);

    CyclomaticComplexityMetric metric;

    MetricResult res = metric.Calculate(funcs.front());

    EXPECT_EQ(res.value, 1);
}

TEST(CYCLOMATIC_COMPLEXITY, exceptions) {

    function::FunctionExtractor extractor;
    file::File tstFile("../../../src/metric_impl/tests/files/exceptions.py");

    std::vector<function::Function> funcs = extractor.Get(tstFile);

    CyclomaticComplexityMetric metric;

    MetricResult res = metric.Calculate(funcs.front());

    EXPECT_EQ(res.value, 4);
}

TEST(CYCLOMATIC_COMPLEXITY, if_test) {

    function::FunctionExtractor extractor;
    std::string tstFile = "../../../src/metric_impl/tests/files/if.py";

    std::vector<function::Function> funcs = extractor.Get(tstFile);

    CyclomaticComplexityMetric metric;

    MetricResult res = metric.Calculate(funcs.front());

    EXPECT_EQ(res.value, 2);
}

TEST(CYCLOMATIC_COMPLEXITY, loops) {
    function::FunctionExtractor extractor;

    std::string tstFile = "../../../src/metric_impl/tests/files/loops.py";

    std::vector<function::Function> funcs = extractor.Get(tstFile);

    CyclomaticComplexityMetric metric;

    MetricResult res = metric.Calculate(funcs.front());

    EXPECT_EQ(res.value, 4);
}

TEST(CYCLOMATIC_COMPLEXITY, many_lines) {
    function::FunctionExtractor extractor;

    std::string tstFile = "../../../src/metric_impl/tests/files/many_lines.py";

    std::vector<function::Function> funcs = extractor.Get(tstFile);

    CyclomaticComplexityMetric metric;

    MetricResult res = metric.Calculate(funcs.front());

    EXPECT_EQ(res.value, 2);
}

TEST(CYCLOMATIC_COMPLEXITY, many_parameters) {
    function::FunctionExtractor extractor;

    std::string tstFile = "../../../src/metric_impl/tests/files/many_parameters.py";

    std::vector<function::Function> funcs = extractor.Get(tstFile);

    CyclomaticComplexityMetric metric;

    MetricResult res = metric.Calculate(funcs.front());

    EXPECT_EQ(res.value, 2);
}

TEST(CYCLOMATIC_COMPLEXITY, match_case) {
    function::FunctionExtractor extractor;

    std::string tstFile = "../../../src/metric_impl/tests/files/match_case.py";

    std::vector<function::Function> funcs = extractor.Get(tstFile);

    CyclomaticComplexityMetric metric;

    MetricResult res = metric.Calculate(funcs.front());

    EXPECT_EQ(res.value, 4);
}

TEST(CYCLOMATIC_COMPLEXITY, nested_if) {
    function::FunctionExtractor extractor;

    std::string tstFile = "../../../src/metric_impl/tests/files/nested_if.py";

    std::vector<function::Function> funcs = extractor.Get(tstFile);

    CyclomaticComplexityMetric metric;

    MetricResult res = metric.Calculate(funcs.front());

    EXPECT_EQ(res.value, 4);
}

TEST(CYCLOMATIC_COMPLEXITY, simple) {
    function::FunctionExtractor extractor;

    std::string tstFile = "../../../src/metric_impl/tests/files/simple.py";

    std::vector<function::Function> funcs = extractor.Get(tstFile);

    CyclomaticComplexityMetric metric;

    MetricResult res = metric.Calculate(funcs.front());

    EXPECT_EQ(res.value, 2);
}

TEST(CYCLOMATIC_COMPLEXITY, ternary) {
    function::FunctionExtractor extractor;

    std::string tstFile = "../../../src/metric_impl/tests/files/ternary.py";

    std::vector<function::Function> funcs = extractor.Get(tstFile);

    CyclomaticComplexityMetric metric;

    MetricResult res = metric.Calculate(funcs.front());

    EXPECT_EQ(res.value, 3);
}

}  // namespace analyzer::metric::metric_impl
