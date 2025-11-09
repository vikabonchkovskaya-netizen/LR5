#include <windows.h>
#include <iostream>
#include <string>

using namespace std;

// Типы функций из DLL
typedef int (__stdcall *FindZeroFunc)(double**, int, int);
typedef void (__stdcall *FreeArrFunc)(double**, int);
typedef void (__stdcall *FindIndexFunc)(int*, int*, double**, int, int);
typedef double* (__stdcall *FillOutFunc)(double**, int, int);
typedef double** (__stdcall *ReverseFunc)(double*, int, int);

HINSTANCE loadDLL() {
    char exePath[MAX_PATH];
    GetModuleFileNameA(NULL, exePath, MAX_PATH);
    string dir(exePath);
    dir = dir.substr(0, dir.find_last_of("\\/"));
    string dllPath = dir + "\\MatrixDLL_task5.dll";

    HINSTANCE lib = LoadLibraryA(dllPath.c_str());
    if (!lib) {
        cerr << "Failed to load DLL from: " << dllPath << endl;
        cerr << "Error code: " << GetLastError() << endl;
        return nullptr;
    }
    return lib;
}

void testFunction(const char* funcName) {
    HINSTANCE lib = loadDLL();
    if (!lib) return;
    
    FARPROC func = GetProcAddress(lib, funcName);
    if (func) {
        cout << "✓ Function '" << funcName << "' found" << endl;
    } else {
        cout << "✗ Function '" << funcName << "' NOT found" << endl;
    }
    
    FreeLibrary(lib);
}

void testBasicOperations() {
    cout << "\n=== Testing Basic Operations ===" << endl;
    
    HINSTANCE lib = loadDLL();
    if (!lib) return;
    
    FindZeroFunc findZero = (FindZeroFunc)GetProcAddress(lib, "findZero");
    FreeArrFunc freeArr = (FreeArrFunc)GetProcAddress(lib, "freeArr");

    if (!findZero || !freeArr) {
        cout << "ERROR: Required functions not found!" << endl;
        FreeLibrary(lib);
        return;
    }

    // Создаем тестовую матрицу
    int m = 2, n = 3;
    double** mat = new double*[m];
    mat[0] = new double[n]{1.0, 0.0, 3.0};
    mat[1] = new double[n]{4.0, 5.0, 0.0};

    // Тестируем подсчет нулей
    int zeroCount = findZero(mat, m, n);
    cout << "Zero count: " << zeroCount << " (expected: 2)" << endl;
    
    // Проверяем результат
    if (zeroCount == 2) {
        cout << "✓ Zero counting works correctly" << endl;
    } else {
        cout << "✗ Zero counting failed" << endl;
    }

    // Очистка
    freeArr(mat, m);
    FreeLibrary(lib);
}

int main() {
    cout << "Testing MatrixDLL_task5.dll..." << endl;
    
    // Проверяем наличие функций
    testFunction("findZero");
    testFunction("findIndex");
    testFunction("fillOut");
    testFunction("reverse");
    testFunction("freeArr");
    
    // Тестируем базовую функциональность
    testBasicOperations();
    
    cout << "\nTest completed!" << endl;
    return 0;
}