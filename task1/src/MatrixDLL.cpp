#include "../include/MatrixDLL.h"
#include <stdexcept>

double findMaxElement(double* X, int n, double* Y, int m)
{
    if (n <= 0 || m <= 0)
        throw std::invalid_argument("Razmery massivov dolzhny byt polozhitelnimi");

    double maxVal = X[0] * Y[0];
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            double Z = X[i] * Y[j];
            if (Z > maxVal)
                maxVal = Z;
        }
    }
    return maxVal;
}