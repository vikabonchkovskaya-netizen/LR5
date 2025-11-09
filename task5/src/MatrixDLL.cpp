#include "MatrixDLL.h"
#include <iostream>

int __stdcall countEvenColumnOddNumber(int** arr, int m, int n) {
    int count = 0;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (j % 2 != 0) {
                if (arr[i][j] % 2 != 0)
                    count++;
            }
        }
    }
    return count;
}

void __stdcall fillOut(int** arr, int* arr2, int m, int n) {
    int index = 0;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (j % 2 != 0) {
                if (arr[i][j] % 2 != 0)
                    arr2[index++] = arr[i][j];
            }
        }
    }
}

double __stdcall findAverage(int* arr, int count) {
    double sum = 0;
    for (int i = 0; i < count; i++) {
        sum += arr[i];
    }
    return sum / count;
}

void __stdcall printInitial(int** arr, int m, int n) {
    for (int i = 0; i < m; i++){
        for (int j = 0; j < n; j++){
            std::cout << arr[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

void __stdcall printDynamic(int* arr, int count) {
    for (int i = 0; i < count; i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
}

void __stdcall freeArr(int** arr, int m) {
    for (int i = 0; i < m; i++) {
        delete[] arr[i];
    }
    delete[] arr;

}