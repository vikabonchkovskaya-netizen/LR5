#ifndef LR5_RECDLL_H
#define LR5_RECDLL_H

#ifdef __cplusplus
extern "C" {
#endif
extern "C" {
    // Функция возвращает индекс минимального элемента массива
    int __stdcall findMinRecursive(const int* arr, int left, int right);

    // Функция возвращает минимальное значение массива
    int __stdcall getMinValue(const int* arr, int left, int right);
}

#ifdef __cplusplus
}
#endif

#endif //LR5_RECDLL_H