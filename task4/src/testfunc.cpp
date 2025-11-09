#include "Test.h"

void findIndex(int* arrI, int* arrJ, double** arr, int m, int n) {
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

double* fillOut(double** arr, int m, int n) {
    double* lineArr = new double[n * m];
    int k = 0;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            lineArr[k++] = arr[i][j];
        }
    }
    return lineArr;
}

int findZero(double** arr, int m, int n) {
    int countZero = 0;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (arr[i][j] == 0) countZero++;
        }
    }
    return countZero;
}

double** reverse(double* lineArr, int m, int n) {
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

void freeArr(double** arr, int m) {
    for (int i = 0; i < m; i++) {
        delete[] arr[i];
    }
    delete[] arr;
}