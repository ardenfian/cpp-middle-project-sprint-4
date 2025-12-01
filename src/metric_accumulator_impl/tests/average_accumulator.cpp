#include "metric_accumulator_impl/average_accumulator.hpp"

#include <gtest/gtest.h>

#include <cmath>
#include <stdexcept>

namespace analyzer::metric_accumulator::metric_accumulator_impl::test {

/*Корректное усреднение нескольких значений */
TEST(AVERAGE_ACCUMULATOR, ACCUMULATION) {
    AverageAccumulator accumulator;
    accumulator.Accumulate({.value = 10});
    accumulator.Accumulate({.value = 2});
    accumulator.Accumulate({.value = 3});

    accumulator.Finalize();

    EXPECT_DOUBLE_EQ(accumulator.Get(), 5.0);
}

/*Сброс*/
TEST(AVERAGE_ACCUMULATOR, RESET) {
    AverageAccumulator accumulator;
    accumulator.Accumulate({.value = 100});
    accumulator.Finalize();

    EXPECT_DOUBLE_EQ(accumulator.Get(), 100.0);

    accumulator.Reset();
    accumulator.Accumulate({.value = 4});
    accumulator.Accumulate({.value = 1});
    accumulator.Accumulate({.value = 2});
    accumulator.Accumulate({.value = 3});
    accumulator.Finalize();

    EXPECT_DOUBLE_EQ(accumulator.Get(), 2.5);
}

/*Значение по умолчанию*/
TEST(AVERAGE_ACCUMULATOR, DEFAULT_STATE) {
    AverageAccumulator accumulator;
    accumulator.Finalize();
    EXPECT_TRUE(std::isnan(accumulator.Get()));
}

/*Исключение*/
TEST(AVERAGE_ACCUMULATOR, EXCEPTION) {
    AverageAccumulator accumulator;
    EXPECT_THROW(accumulator.Get(), std::runtime_error);
}

/*Тест с одним значением*/
TEST(AVERAGE_ACCUMULATOR, SINGLE) {
    AverageAccumulator accumulator;
    accumulator.Accumulate({.value = 10});
    accumulator.Finalize();
    EXPECT_EQ(accumulator.Get(), 10);
}

}  // namespace analyzer::metric_accumulator::metric_accumulator_impl::test
