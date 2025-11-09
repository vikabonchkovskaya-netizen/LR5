#include "Test.h"
#include <algorithm>
#include <iostream>

int* findElOnD(int** arr, int n, int k, int& count) {
    int diagSize = std::min(n, k);
    for (int i = 0; i < diagSize; i++) {
        if (arr[i][i] % 2 == 0) {
            count++;
        }
    }

    if (count == 0) {
        std::cout << "No even elements found on the main diagonal" << std::endl;
        return nullptr;
    }
    else {
        int* onD = new int[count];
        int index = 0;
        for (int i = 0; i < diagSize; i++) {
            if (arr[i][i] % 2 == 0) {
                onD[index++] = arr[i][i];
            }
        }
        return onD;
    }
}

int multiply(int* onD, int count) {
    int res = 1;
    for (int i = 0; i < count; i++) {
        res *= onD[i];
    }
    return res;
}