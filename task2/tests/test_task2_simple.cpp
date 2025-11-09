#include <iostream>
#include "RecDLL.h"
#include <windows.h>

typedef int (__cdecl *FindMinFunc)(const int*, int, int);

int main() {
    HINSTANCE lib = LoadLibraryA("C:\\Users\\Vika\\Documents\\553501\\OAiP\\LR5\\build\\RecDLL_task2.dll");
 // используем const char*
    if (!lib) {
        std::cerr << "DLL not found!" << std::endl;
        return 1;
    }

    FindMinFunc findMin = (FindMinFunc)GetProcAddress(lib, "findMinRecursive");
    if (!findMin) {
        std::cerr << "Function not found!" << std::endl;
        FreeLibrary(lib);
        return 1;
    }

    int arr[] = {5, 3, 8, 1, 9, 2};
    int index = findMin(arr, 0, 5);

    std::cout << "Index of min: " << index << std::endl;
    FreeLibrary(lib);

    return 0;
}
