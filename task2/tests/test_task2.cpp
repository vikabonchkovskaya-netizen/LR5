#include <gtest/gtest.h>
#include "RecDLL.h"
#include <windows.h>
#include <stdexcept>
#include <string>

HINSTANCE loadDLL() {
    char exePath[MAX_PATH];
    GetModuleFileNameA(NULL, exePath, MAX_PATH);
    std::string dir(exePath);
    dir = dir.substr(0, dir.find_last_of("\\/")); // директория exe
    std::string dllPath = dir + "\\RecDLL_task2.dll";

    HINSTANCE lib = LoadLibraryA(dllPath.c_str());
    if (!lib) throw std::runtime_error("DLL not found: " + dllPath);
    return lib;
}

typedef int (__cdecl *FindMinFunc)(const int*, int, int);
typedef int (__cdecl *GetMinValueFunc)(const int*, int, int);

TEST(DLLTests, BaseTest) {
    HINSTANCE lib = loadDLL();
    FindMinFunc findMin = (FindMinFunc)GetProcAddress(lib, "findMinRecursive");
    GetMinValueFunc getMin = (GetMinValueFunc)GetProcAddress(lib, "getMinValue");
    if (!findMin || !getMin) {
        FreeLibrary(lib);
        FAIL() << "Function not found in DLL";
    }

    int A[] = {5,3,8,1,9,2};
    EXPECT_EQ(findMin(A,0,5), 3);
    EXPECT_EQ(getMin(A,0,5), 1);

    FreeLibrary(lib);
}

TEST(DLLTests, EdgeTestSingle) {
    HINSTANCE lib = loadDLL();
    FindMinFunc findMin = (FindMinFunc)GetProcAddress(lib, "findMinRecursive");
    GetMinValueFunc getMin = (GetMinValueFunc)GetProcAddress(lib, "getMinValue");
    if (!findMin || !getMin) {
        FreeLibrary(lib);
        FAIL() << "Function not found in DLL";
    }

    int A[] = {42};
    EXPECT_EQ(findMin(A,0,0), 0);
    EXPECT_EQ(getMin(A,0,0), 42);

    FreeLibrary(lib);
}

TEST(DLLTests, EdgeTestAllEqual) {
    HINSTANCE lib = loadDLL();
    FindMinFunc findMin = (FindMinFunc)GetProcAddress(lib, "findMinRecursive");
    GetMinValueFunc getMin = (GetMinValueFunc)GetProcAddress(lib, "getMinValue");
    if (!findMin || !getMin) {
        FreeLibrary(lib);
        FAIL() << "Function not found in DLL";
    }

    int A[] = {7,7,7,7,7};
    EXPECT_EQ(findMin(A,0,4), 0);
    EXPECT_EQ(getMin(A,0,4), 7);

    FreeLibrary(lib);
}
