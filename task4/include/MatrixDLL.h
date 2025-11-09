#ifndef LR5_MATRIXDLL_H
#define LR5_MATRIXDLL_H

#ifdef __cplusplus
extern "C" {
#endif

    // Экспортируем функции из DLL
    __declspec(dllexport) void __stdcall findIndex(int* arrI, int* arrJ, double** arr, int m, int n);
    __declspec(dllexport) double* __stdcall fillOut(double** arr, int m, int n);
    __declspec(dllexport) int __stdcall findZero(double** arr, int m, int n);
    __declspec(dllexport) void __stdcall printPosZero(int* arrI, int* arrJ, int countZero);
    __declspec(dllexport) void __stdcall printReverseMatrix(double** reverseArr, int n, int m);
    __declspec(dllexport) double** __stdcall reverse(double* lineArr, int m, int n);
    __declspec(dllexport) void __stdcall freeArr(double** arr, int m);

#ifdef __cplusplus
}
#endif

#endif //LR5_MATRIXDLL_H