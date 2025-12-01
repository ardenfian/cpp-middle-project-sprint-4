#include "metric_impl/parameters_count.hpp"

#include <gtest/gtest.h>

namespace analyzer::metric::metric_impl {

TEST(PARAMETERS_COUNT, comments) {

    function::FunctionExtractor extractor;
    file::File tstFile("../../../src/metric_impl/tests/files/comments.py");

    std::vector<function::Function> funcs = extractor.Get(tstFile);

    CountParametersMetric metric;

    MetricResult res = metric.Calculate(funcs.front());

    EXPECT_EQ(res.value, 3);
}

TEST(PARAMETERS_COUNT, exceptions) {

    function::FunctionExtractor extractor;
    file::File tstFile("../../../src/metric_impl/tests/files/exceptions.py");

    std::vector<function::Function> funcs = extractor.Get(tstFile);

    CountParametersMetric metric;

    MetricResult res = metric.Calculate(funcs.front());

    EXPECT_EQ(res.value, 0);
}

TEST(PARAMETERS_COUNT, if_test) {

    function::FunctionExtractor extractor;
    std::string tstFile = "../../../src/metric_impl/tests/files/if.py";

    std::vector<function::Function> funcs = extractor.Get(tstFile);

    CountParametersMetric metric;

    MetricResult res = metric.Calculate(funcs.front());

    EXPECT_EQ(res.value, 1);
}

TEST(PARAMETERS_COUNT, loops) {
    function::FunctionExtractor extractor;

    std::string tstFile = "../../../src/metric_impl/tests/files/loops.py";

    std::vector<function::Function> funcs = extractor.Get(tstFile);

    CountParametersMetric metric;

    MetricResult res = metric.Calculate(funcs.front());

    EXPECT_EQ(res.value, 1);
}

TEST(PARAMETERS_COUNT, many_lines) {
    function::FunctionExtractor extractor;

    std::string tstFile = "../../../src/metric_impl/tests/files/many_lines.py";

    std::vector<function::Function> funcs = extractor.Get(tstFile);

    CountParametersMetric metric;

    MetricResult res = metric.Calculate(funcs.front());

    EXPECT_EQ(res.value, 0);
}

TEST(PARAMETERS_COUNT, many_parameters) {
    function::FunctionExtractor extractor;

    std::string tstFile = "../../../src/metric_impl/tests/files/many_parameters.py";

    std::vector<function::Function> funcs = extractor.Get(tstFile);

    CountParametersMetric metric;

    MetricResult res = metric.Calculate(funcs.front());

    EXPECT_EQ(res.value, 5);
}

TEST(PARAMETERS_COUNT, match_case) {
    function::FunctionExtractor extractor;

    std::string tstFile = "../../../src/metric_impl/tests/files/match_case.py";

    std::vector<function::Function> funcs = extractor.Get(tstFile);

    CountParametersMetric metric;

    MetricResult res = metric.Calculate(funcs.front());

    EXPECT_EQ(res.value, 1);
}

TEST(PARAMETERS_COUNT, nested_if) {
    function::FunctionExtractor extractor;

    std::string tstFile = "../../../src/metric_impl/tests/files/nested_if.py";

    std::vector<function::Function> funcs = extractor.Get(tstFile);

    CountParametersMetric metric;

    MetricResult res = metric.Calculate(funcs.front());

    EXPECT_EQ(res.value, 2);
}

TEST(PARAMETERS_COUNT, simple) {
    function::FunctionExtractor extractor;

    std::string tstFile = "../../../src/metric_impl/tests/files/simple.py";

    std::vector<function::Function> funcs = extractor.Get(tstFile);

    CountParametersMetric metric;

    MetricResult res = metric.Calculate(funcs.front());

    EXPECT_EQ(res.value, 0);
}

TEST(PARAMETERS_COUNT, ternary) {
    function::FunctionExtractor extractor;

    std::string tstFile = "../../../src/metric_impl/tests/files/ternary.py";

    std::vector<function::Function> funcs = extractor.Get(tstFile);

    CountParametersMetric metric;

    MetricResult res = metric.Calculate(funcs.front());

    EXPECT_EQ(res.value, 1);
}

}  // namespace analyzer::metric::metric_impl
