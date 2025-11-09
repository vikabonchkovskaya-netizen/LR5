#ifdef RECDLL_EXPORTS
#define RECDLL_API __declspec(dllexport)
#else
#define RECDLL_API __declspec(dllimport)
#endif

extern "C" {
    // Функция возвращает индекс минимального элемента массива
    RECDLL_API int findMinRecursive(const int* arr, int left, int right);

    // Функция возвращает минимальное значение массива
    RECDLL_API int getMinValue(const int* arr, int left, int right);
}