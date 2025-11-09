#include <iostream>
#include "RecDLL.h"

int main() {
    int arr[] = {5, 3, 8, 1, 9, 2};
    int minIndex = findMinRecursive(arr, 0, 5);
    int minValue = getMinValue(arr, 0, 5);

    std::cout << "Min value: " << minValue << " at index " << minIndex << std::endl;
    return 0;
}