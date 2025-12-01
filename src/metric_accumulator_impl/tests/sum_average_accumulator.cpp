#include "metric_accumulator_impl/sum_average_accumulator.hpp"

#include <gtest/gtest.h>

#include <cmath>

namespace analyzer::metric_accumulator::metric_accumulator_impl::test {

/*Корректное усреднение нескольких значений */
TEST(SUM_ACCUMULATOR, ACCUMULATION) {
    SumAverageAccumulator accumulator;
    accumulator.Accumulate({.value = 10});
    accumulator.Accumulate({.value = 2});
    accumulator.Accumulate({.value = 3});

    accumulator.Finalize();

    EXPECT_DOUBLE_EQ(accumulator.Get().average, 5.0);
    EXPECT_EQ(accumulator.Get().sum, 15);
}

/*Сброс*/
TEST(SUM_ACCUMULATOR, RESET) {
    SumAverageAccumulator accumulator;
    accumulator.Accumulate({.value = 100});
    accumulator.Finalize();

    EXPECT_DOUBLE_EQ(accumulator.Get().average, 100.0);
    EXPECT_EQ(accumulator.Get().sum, 100.0);

    accumulator.Reset();
    accumulator.Accumulate({.value = 4});
    accumulator.Accumulate({.value = 1});
    accumulator.Accumulate({.value = 2});
    accumulator.Accumulate({.value = 3});
    accumulator.Finalize();

    EXPECT_DOUBLE_EQ(accumulator.Get().average, 2.5);
    EXPECT_EQ(accumulator.Get().sum, 10);
}

/*Значение по умолчанию*/
TEST(SUM_ACCUMULATOR, DEFAULT_STATE) {
    SumAverageAccumulator accumulator;
    accumulator.Finalize();
    EXPECT_TRUE(std::isnan(accumulator.Get().average));
    EXPECT_EQ(accumulator.Get().sum, 0);
}

/*Исключение*/
TEST(SUM_ACCUMULATOR, EXCEPTION) {
    SumAverageAccumulator accumulator;
    EXPECT_THROW(accumulator.Get(), std::runtime_error);
}

/*Тест с одним значением*/
TEST(SUM_ACCUMULATOR, SINGLE) {
    SumAverageAccumulator accumulator;
    accumulator.Accumulate({.value = 10});
    accumulator.Finalize();
    EXPECT_DOUBLE_EQ(accumulator.Get().average, 10.0);
    EXPECT_EQ(accumulator.Get().sum, 10);
}

}  // namespace analyzer::metric_accumulator::metric_accumulator_impl::test
