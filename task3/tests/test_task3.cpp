#include <gtest/gtest.h>
#include <windows.h>
#include <stdexcept>
#include <string>

using namespace std;

HINSTANCE loadDLL() {
    char exePath[MAX_PATH];
    GetModuleFileNameA(NULL, exePath, MAX_PATH);
    string dir(exePath);
    dir = dir.substr(0, dir.find_last_of("\\/"));
    string dllPath = dir + "\\MatrixDLL.dll";
    HINSTANCE lib = LoadLibraryA(dllPath.c_str());
    if (!lib) throw runtime_error("DLL not found: " + dllPath);
    return lib;
}

typedef int* (__stdcall *FindElOnDFunc)(int**, int, int, int&);
typedef int (__stdcall *MultiplyFunc)(int*, int);

TEST(MatrixDLLTests, BaseTest) {
    HINSTANCE lib = loadDLL();
    FindElOnDFunc findElOnD = (FindElOnDFunc)GetProcAddress(lib, "findElOnD");
    MultiplyFunc multiply = (MultiplyFunc)GetProcAddress(lib, "multiply");
    if (!findElOnD || !multiply) { FreeLibrary(lib); FAIL() << "Functions not found"; }

    int n = 3, k = 3;
    int** matrix = new int*[n];
    for (int i = 0; i < n; i++) matrix[i] = new int[k];
    matrix[0][0] = 2; matrix[0][1] = 1; matrix[0][2] = 1;
    matrix[1][0] = 1; matrix[1][1] = 3; matrix[1][2] = 1;
    matrix[2][0] = 1; matrix[2][1] = 1; matrix[2][2] = 4;

    int count = 0;
    int* diagonal = findElOnD(matrix, n, k, count);

    EXPECT_EQ(count, 2);
    ASSERT_NE(diagonal, nullptr);
    EXPECT_EQ(diagonal[0], 2);
    EXPECT_EQ(diagonal[1], 4);
    EXPECT_EQ(multiply(diagonal, count), 8);

    for (int i = 0; i < n; i++) delete[] matrix[i];
    delete[] matrix;
    delete[] diagonal;
    FreeLibrary(lib);
}

TEST(MatrixDLLTests, EdgeTestSingleElement) {
    HINSTANCE lib = loadDLL();
    FindElOnDFunc findElOnD = (FindElOnDFunc)GetProcAddress(lib, "findElOnD");
    MultiplyFunc multiply = (MultiplyFunc)GetProcAddress(lib, "multiply");
    if (!findElOnD || !multiply) { FreeLibrary(lib); FAIL() << "Functions not found"; }

    int n = 1, k = 1;
    int** matrix = new int*[n];
    matrix[0] = new int[k]{7};

    int count = 0;
    int* diagonal = findElOnD(matrix, n, k, count);

    EXPECT_EQ(count, 0);
    EXPECT_EQ(diagonal, nullptr);

    delete[] matrix[0];
    delete[] matrix;
    FreeLibrary(lib);
}

TEST(MatrixDLLTests, EdgeTestMatrixWithZeros) {
    HINSTANCE lib = loadDLL();
    FindElOnDFunc findElOnD = (FindElOnDFunc)GetProcAddress(lib, "findElOnD");
    MultiplyFunc multiply = (MultiplyFunc)GetProcAddress(lib, "multiply");
    if (!findElOnD || !multiply) { FreeLibrary(lib); FAIL() << "Functions not found"; }

    int n = 2, k = 2;
    int** matrix = new int*[n];
    for (int i = 0; i < n; i++) matrix[i] = new int[k];
    matrix[0][0] = 0; matrix[0][1] = 2;
    matrix[1][0] = 3; matrix[1][1] = 0;

    int count = 0;
    int* diagonal = findElOnD(matrix, n, k, count);

    EXPECT_EQ(count, 2);
    ASSERT_NE(diagonal, nullptr);
    EXPECT_EQ(diagonal[0], 0);
    EXPECT_EQ(diagonal[1], 0);
    EXPECT_EQ(multiply(diagonal, count), 0);

    for (int i = 0; i < n; i++) delete[] matrix[i];
    delete[] matrix;
    delete[] diagonal;
    FreeLibrary(lib);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
