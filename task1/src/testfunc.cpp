#include "MatrixDLL.h"

double Wrapper_FindMax(double* X, int n, double* Y, int m) {
    return matrixdll::findMaxElement(X, n, Y, m);
}
