#ifndef LR5_MATRIXDLL_H
#define LR5_MATRIXDLL_H

#ifdef __cplusplus
extern "C" {
#endif

    // Экспортируем функции из DLL
    __declspec(dllexport) int __stdcall countEvenColumnOddNumber(int** arr, int m, int n);
    __declspec(dllexport) void __stdcall fillOut(int** arr, int* arr2, int m, int n);
    __declspec(dllexport) double __stdcall findAverage(int* arr, int count);
    __declspec(dllexport) void __stdcall printInitial(int** arr, int m, int n);
    __declspec(dllexport) void __stdcall printDynamic(int* arr, int count);
    __declspec(dllexport) void __stdcall freeArr(int** arr, int m);

#ifdef __cplusplus
}
#endif

#endif //LR5_MATRIXDLL_H