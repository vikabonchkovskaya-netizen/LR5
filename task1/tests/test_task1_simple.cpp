#include <iostream>
#include "MatrixDLL.h"

int main() {
    double X[] = {1, 2, 3};
    double Y[] = {4, 5};
    double result = matrixdll::findMaxElement(X, 3, Y, 2);
    std::cout << "Test result: " << result << std::endl;
    return 0;
}