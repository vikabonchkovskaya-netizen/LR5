#include <gtest/gtest.h>
#include <windows.h>
#include <stdexcept>
#include <string>
#include <iostream>

using namespace std;

// === Типы указателей на функции DLL ===
using FindZeroFunc = int(__stdcall*)(double**, int, int);
using FreeArrFunc = void(__stdcall*)(double**, int);
using FindIndexFunc = void(__stdcall*)(int*, int*, double**, int, int);
using FillOutFunc = double*(__stdcall*)(double**, int, int);
using ReverseFunc = double**(__stdcall*)(double*, int, int);

// === Функция загрузки DLL ===
HINSTANCE loadDLL() {
    char exePath[MAX_PATH];
    GetModuleFileNameA(NULL, exePath, MAX_PATH);
    string dir(exePath);
    dir = dir.substr(0, dir.find_last_of("\\/"));

    // Путь к DLL в папке build
    string dllPath = dir + "\\..\\build\\MatrixDLL_task4.dll";

    HINSTANCE lib = LoadLibraryA(dllPath.c_str());
    if (!lib) throw runtime_error("DLL not found: " + dllPath);
    return lib;
}

// === Тесты ===
TEST(MatrixDLLTests, CountZeros) {
    HINSTANCE lib = loadDLL();
    auto findZero = (FindZeroFunc)GetProcAddress(lib, "findZero");
    auto freeArr = (FreeArrFunc)GetProcAddress(lib, "freeArr");

    ASSERT_TRUE(findZero);
    ASSERT_TRUE(freeArr);

    int m = 2, n = 3;
    double** arr = new double*[m];
    arr[0] = new double[n]{1, 0, 3};
    arr[1] = new double[n]{0, 5, 0};

    EXPECT_EQ(findZero(arr, m, n), 3);

    freeArr(arr, m);
    FreeLibrary(lib);
}

TEST(MatrixDLLTests, FindZeroPositions) {
    HINSTANCE lib = loadDLL();
    auto findZero = (FindZeroFunc)GetProcAddress(lib, "findZero");
    auto findIndex = (FindIndexFunc)GetProcAddress(lib, "findIndex");
    auto freeArr = (FreeArrFunc)GetProcAddress(lib, "freeArr");

    ASSERT_TRUE(findZero);
    ASSERT_TRUE(findIndex);
    ASSERT_TRUE(freeArr);

    int m = 2, n = 2;
    double** arr = new double*[m];
    arr[0] = new double[n]{0, 1};
    arr[1] = new double[n]{2, 0};

    int countZero = findZero(arr, m, n);
    int* arrI = new int[countZero];
    int* arrJ = new int[countZero];

    findIndex(arrI, arrJ, arr, m, n);

    EXPECT_EQ(countZero, 2);
    EXPECT_EQ(arrI[0], 0);
    EXPECT_EQ(arrJ[0], 0);
    EXPECT_EQ(arrI[1], 1);
    EXPECT_EQ(arrJ[1], 1);

    delete[] arrI;
    delete[] arrJ;
    freeArr(arr, m);
    FreeLibrary(lib);
}

TEST(MatrixDLLTests, FlattenMatrix) {
    HINSTANCE lib = loadDLL();
    auto fillOut = (FillOutFunc)GetProcAddress(lib, "fillOut");
    auto freeArr = (FreeArrFunc)GetProcAddress(lib, "freeArr");

    ASSERT_TRUE(fillOut);
    ASSERT_TRUE(freeArr);

    int m = 2, n = 2;
    double** arr = new double*[m];
    arr[0] = new double[n]{1, 2};
    arr[1] = new double[n]{3, 4};

    double* flat = fillOut(arr, m, n);

    EXPECT_EQ(flat[0], 1);
    EXPECT_EQ(flat[1], 2);
    EXPECT_EQ(flat[2], 3);
    EXPECT_EQ(flat[3], 4);

    delete[] flat;
    freeArr(arr, m);
    FreeLibrary(lib);
}

TEST(MatrixDLLTests, ReverseMatrix) {
    HINSTANCE lib = loadDLL();
    auto reverse = (ReverseFunc)GetProcAddress(lib, "reverse");
    auto freeArr = (FreeArrFunc)GetProcAddress(lib, "freeArr");

    ASSERT_TRUE(reverse);
    ASSERT_TRUE(freeArr);

    int m = 2, n = 2;
    double* flat = new double[m*n]{1, 2, 3, 4};

    double** rev = reverse(flat, m, n);

    EXPECT_EQ(rev[0][0], 4);
    EXPECT_EQ(rev[0][1], 3);
    EXPECT_EQ(rev[1][0], 2);
    EXPECT_EQ(rev[1][1], 1);

    freeArr(rev, m);
    delete[] flat;
    FreeLibrary(lib);
}

// === MAIN ===
int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

