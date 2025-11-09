#define RECDLL_EXPORTS
#include "RecDLL.h"

// Рекурсивный поиск индекса минимального элемента
int findMinRecursive(const int* arr, int left, int right) {
    if (left == right) return left;
    int mid = (left + right) / 2;
    int leftMin = findMinRecursive(arr, left, mid);
    int rightMin = findMinRecursive(arr, mid + 1, right);
    return (arr[leftMin] <= arr[rightMin]) ? leftMin : rightMin;
}

int getMinValue(const int* arr, int left, int right) {
    int index = findMinRecursive(arr, left, right);
    return arr[index];
}