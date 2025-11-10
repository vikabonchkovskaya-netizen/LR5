#include <gtest/gtest.h>
#include "../include/MatrixDLL.h"
#include <stdexcept>

// Базовый тест — нормальные данные
TEST(MatrixDLL_Basic, PositiveValues) {
    double X[] = {1.0, 2.0, 3.0};
    double Y[] = {4.0, 0.5};
    double result = findMaxElement(X, 3, Y, 2);
    EXPECT_DOUBLE_EQ(result, 12.0); // 3 * 4 = 12
}

// Краевой тест 1 — один элемент в каждом массиве
TEST(MatrixDLL_Edge, SingleElements) {
    double X[] = {-5.0};
    double Y[] = {-2.0};
    EXPECT_DOUBLE_EQ(findMaxElement(X, 1, Y, 1), 10.0);
}

// Краевой тест 2 — отрицательные и нули
TEST(MatrixDLL_Edge, MixedValues) {
    double X[] = {-10.0, 0.0, 2.0};
    double Y[] = {-1.0, 3.0};
    double result = findMaxElement(X, 3, Y, 2);
    EXPECT_DOUBLE_EQ(result, 10.0); // (-10 * -1) = 10 — максимум
}

// Проверка на ошибки
TEST(MatrixDLL_Exceptions, InvalidArgs) {
    double X[] = {1.0, 2.0};
    double Y[] = {3.0};
    EXPECT_THROW(findMaxElement(nullptr, 2, Y, 1), std::invalid_argument);
    EXPECT_THROW(findMaxElement(X, 0, Y, 1), std::invalid_argument);
    EXPECT_THROW(findMaxElement(X, 2, nullptr, 1), std::invalid_argument);
}
