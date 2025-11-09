#include "MatrixDLL.h"
#include <stdexcept>

namespace matrixdll {

double findMaxElement(double* X, int n, double* Y, int m)
{
    if (n <= 0 || m <= 0)
        throw std::invalid_argument("Размеры массивов должны быть положительными");

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

} 
