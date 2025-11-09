#pragma once
// Функция ищет максимальный элемент матрицы Z = Xi * Yj
// X — массив длины n, Y — массив длины m
// Возвращает максимальное значение Z = Xi * Yj
// Если n <= 0 или m <= 0 — генерирует исключение std::invalid_argument
namespace matrixdll {
    double findMaxElement(double* X, int n, double* Y, int m);
}

// Функции проверки ввода
void checkInputChoice(int& choice);
void checkInputIntK(int& k);
void checkInputArray(double& value);

// Основные функции программы
void Task();
void Menu();
