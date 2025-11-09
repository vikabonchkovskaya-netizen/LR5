#include "MatrixDLL.h"
#include <iostream>

void __stdcall findIndex(int* arrI, int* arrJ, double** arr, int m, int n) {
    int indexI = 0;
    int indexJ = 0;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (arr[i][j] == 0) {
                arrI[indexI++] = i;
                arrJ[indexJ++] = j;
            }
        }
    }
}

double* __stdcall fillOut(double** arr, int m, int n) {
    double* lineArr = new double[n * m];
    int k = 0;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            lineArr[k++] = arr[i][j];
        }
    }
    return lineArr;
}

int __stdcall findZero(double** arr, int m, int n) {
    int countZero = 0;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (arr[i][j] == 0) countZero++;
        }
    }
    return countZero;
}

void __stdcall printPosZero(int* arrI, int* arrJ, int countZero) {
    std::cout << "Zero positions: ";
    for (int i = 0; i < countZero; i++) {
        std::cout << "[" << arrI[i] << ";" << arrJ[i] << "]" << " ";
    }
    std::cout << std::endl;
}

void __stdcall printReverseMatrix(double** reverseArr, int n, int m) {
    std::cout << "Reverse matrix:" << std::endl;
    for (int i = 0; i < m; i++){
        for (int j = 0; j < n; j++){
            std::cout << reverseArr[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

double** __stdcall reverse(double* lineArr, int m, int n) {
    double** reverseArr = new double*[m];
    int k = m * n;
    for (int i = 0; i < m; i++) {
        reverseArr[i] = new double[n];
    }
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            reverseArr[i][j] = lineArr[--k];
        }
    }
    return reverseArr;
}

void __stdcall freeArr(double** arr, int m) {
    for (int i = 0; i < m; i++) {
        delete[] arr[i];
    }
    delete[] arr;
}