#include <gtest/gtest.h>
#include <windows.h>
#include <stdexcept>
#include <string>
#include <iostream>

using namespace std;

// ===== Загрузка DLL =====
HINSTANCE loadDLL() {
    char exePath[MAX_PATH];
    GetModuleFileNameA(NULL, exePath, MAX_PATH);
    string dir(exePath);
    dir = dir.substr(0, dir.find_last_of("\\/"));
    string dllPath = dir + "\\MatrixDLL_task4.dll";

    HINSTANCE lib = LoadLibraryA(dllPath.c_str());
    if (!lib) {
        cerr << "Failed to load DLL from: " << dllPath << endl;
        cerr << "Error code: " << GetLastError() << endl;
        throw runtime_error("DLL not found: " + dllPath);
    }
    return lib;
}

// ===== Указатели на функции =====
typedef int (__stdcall *FindZeroFunc)(double**, int, int);
typedef void (__stdcall *FreeArrFunc)(double**, int);
typedef void (__stdcall *FindIndexFunc)(int*, int*, double**, int, int);
typedef double* (__stdcall *FillOutFunc)(double**, int, int);
typedef double** (__stdcall *ReverseFunc)(double*, int, int);

// ===== ТЕСТ 1: Базовый функционал =====
TEST(MatrixDLLTests, BasicFunctionality) {
    HINSTANCE lib = loadDLL();
    
    FindZeroFunc findZero = (FindZeroFunc)GetProcAddress(lib, "findZero");
    FindIndexFunc findIndex = (FindIndexFunc)GetProcAddress(lib, "findIndex");
    FillOutFunc fillOut = (FillOutFunc)GetProcAddress(lib, "fillOut");
    ReverseFunc reverse = (ReverseFunc)GetProcAddress(lib, "reverse");
    FreeArrFunc freeArr = (FreeArrFunc)GetProcAddress(lib, "freeArr");

    ASSERT_TRUE(findZero && findIndex && fillOut && reverse && freeArr);

    int m = 2, n = 3;
    double** mat = new double*[m];
    mat[0] = new double[n]{1.0, 0.0, 3.0};
    mat[1] = new double[n]{4.0, 5.0, 0.0};

    // Проверка количества нулей
    int zeroCount = findZero(mat, m, n);
    EXPECT_EQ(zeroCount, 2);

    // Проверка позиций нулей
    int* arrI = new int[zeroCount];
    int* arrJ = new int[zeroCount];
    findIndex(arrI, arrJ, mat, m, n);
    EXPECT_TRUE((arrI[0] == 0 && arrJ[0] == 1) || (arrI[0] == 1 && arrJ[0] == 2));

    // Преобразование в линейный массив
    double* flat = fillOut(mat, m, n);
    EXPECT_DOUBLE_EQ(flat[0], 1.0);
    EXPECT_DOUBLE_EQ(flat[1], 0.0);
    EXPECT_DOUBLE_EQ(flat[5], 0.0);

    // Обратное преобразование
    double** reversed = reverse(flat, m, n);
    EXPECT_DOUBLE_EQ(reversed[0][0], 0.0); // Последний элемент становится первым
    EXPECT_DOUBLE_EQ(reversed[1][2], 1.0); // Первый элемент становится последним

    delete[] arrI;
    delete[] arrJ;
    delete[] flat;
    freeArr(reversed, m);
    freeArr(mat, m);
    FreeLibrary(lib);
}

// ===== ТЕСТ 2: Краевой случай 1 (матрица 1x1) =====
TEST(MatrixDLLTests, EdgeCaseSingleElement) {
    HINSTANCE lib = loadDLL();
    
    FindZeroFunc findZero = (FindZeroFunc)GetProcAddress(lib, "findZero");
    FindIndexFunc findIndex = (FindIndexFunc)GetProcAddress(lib, "findIndex");
    FillOutFunc fillOut = (FillOutFunc)GetProcAddress(lib, "fillOut");
    ReverseFunc reverse = (ReverseFunc)GetProcAddress(lib, "reverse");
    FreeArrFunc freeArr = (FreeArrFunc)GetProcAddress(lib, "freeArr");

    ASSERT_TRUE(findZero && findIndex && fillOut && reverse && freeArr);

    double** mat = new double*[1];
    mat[0] = new double[1]{0.0};

    EXPECT_EQ(findZero(mat, 1, 1), 1);

    int i, j;
    findIndex(&i, &j, mat, 1, 1);
    EXPECT_EQ(i, 0);
    EXPECT_EQ(j, 0);

    double* flat = fillOut(mat, 1, 1);
    EXPECT_DOUBLE_EQ(flat[0], 0.0);

    double** rev = reverse(flat, 1, 1);
    EXPECT_DOUBLE_EQ(rev[0][0], 0.0);

    delete[] flat;
    freeArr(rev, 1);
    freeArr(mat, 1);
    FreeLibrary(lib);
}

// ===== ТЕСТ 3: Краевой случай 2 (матрица без нулей) =====
TEST(MatrixDLLTests, EdgeCaseNoZeros) {
    HINSTANCE lib = loadDLL();
    
    FindZeroFunc findZero = (FindZeroFunc)GetProcAddress(lib, "findZero");
    FillOutFunc fillOut = (FillOutFunc)GetProcAddress(lib, "fillOut");
    FreeArrFunc freeArr = (FreeArrFunc)GetProcAddress(lib, "freeArr");

    ASSERT_TRUE(findZero && fillOut && freeArr);

    double** mat = new double*[2];
    mat[0] = new double[3]{1.1, 2.2, 3.3};
    mat[1] = new double[3]{4.4, 5.5, 6.6};

    EXPECT_EQ(findZero(mat, 2, 3), 0);

    double* flat = fillOut(mat, 2, 3);
    for (int k = 0; k < 6; ++k)
        EXPECT_NE(flat[k], 0.0);

    delete[] flat;
    freeArr(mat, 2);
    FreeLibrary(lib);
}

// ===== MAIN =====
int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
