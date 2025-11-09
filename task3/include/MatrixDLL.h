#ifndef LR5_MATRIXDLL_H
#define LR5_MATRIXDLL_H

#ifdef __cplusplus
extern "C" {
#endif

    // Экспортируем функции из DLL
    __declspec(dllexport) int* __stdcall findElOnD(int** arr, int n, int k, int& count);
    __declspec(dllexport) int __stdcall multiply(int* onD, int count);

#ifdef __cplusplus
}
#endif

#endif //LR5_MATRIXDLL_H