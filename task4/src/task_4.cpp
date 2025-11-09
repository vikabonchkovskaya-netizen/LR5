#include <iostream>
#include <sstream>
#include <string>
#include <windows.h>  // для LoadLibrary, GetProcAddress, FreeLibrary

void checkInputChoice(int& choice) {
    while (true) {
        std::cout << "Start?\n1.YES\n2.EXIT\n3.Show menu\n";
        std::string line;
        if (!std::getline(std::cin, line)) {
            std::cout << "Input error.\n";
            continue;
        }
        std::stringstream ss(line);
        if (ss >> choice && ss.eof()) {
            if (choice >= 1 && choice <= 3) {
                break; // одно число в диапазоне и ничего больше
            }
            else {
                std::cout << "Incorrect input. Enter 1, 2, or 3.\n";
            }
        }
        else {
            std::cout << "Incorrect input. Enter a single number.\n";
        }
    }
}

void checkInputIntK(int& k){
    while (true) {
        std::string line;
        if (!std::getline(std::cin, line)) {
            std::cout << "Input error.\n";
            continue;
        }
        std::stringstream ss(line);
        if (ss >> k && ss.eof()) {
            if (k < 1) {
                std::cout << "Input error" << std::endl;
                continue;
            } else {
                break;
            }
        } else {
            std::cout << "Incorrect input.\n";
        }
    }
}

void checkInputArray(double& x){
    while (true) {
        std::string line;
        if (!std::getline(std::cin, line)) {
            std::cout << "Input error.\n";
            continue;
        }
        std::stringstream ss(line);
        if (ss >> x && ss.eof()) {
            break;
        } else {
            std::cout << "Incorrect input.\n";
        }
    }
}

double** createMatrix(int m, int n) {
    double** arr = new double*[m];
    for (int i = 0; i < m; i++) {
        arr[i] = new double[n];
    }
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            std::cout << "a" << i << j << ": ";
            checkInputArray(arr[i][j]);
        }
    }

    return arr;
}

void Task() {
    // 1. ЗАГРУЖАЕМ ДИНАМИЧЕСКУЮ БИБЛИОТЕКУ
    HINSTANCE load;
    load = LoadLibrary("MatrixDLL.dll");
    if (load == nullptr) {
        std::cout << "Error: Failed to load MatrixDLL.dll!" << std::endl;
        return;
    }

    // 2. ОБЪЯВЛЯЕМ ТИПЫ УКАЗАТЕЛЕЙ НА ФУНКЦИИ ИЗ DLL ЛОКАЛЬНО
    typedef void (__stdcall *FindIndexF)(int* arrI, int* arrJ, double** arr, int m, int n);
    typedef double* (__stdcall *FillOutF)(double** arr, int m, int n);
    typedef int (__stdcall *FindZeroF)(double** arr, int m, int n);
    typedef void (__stdcall *PrintPosZeroF)(int* arrI, int* arrJ, int countZero);
    typedef void (__stdcall *PrintReverseMatrixF)(double** reverseArr, int n, int m);
    typedef double** (__stdcall *ReverseF)(double* lineArr, int m, int n);
    typedef void (__stdcall *FreeArrF)(double** arr, int m);

    // 3. ПОЛУЧАЕМ УКАЗАТЕЛИ НА ФУНКЦИИ ИЗ DLL
    FindIndexF pFindIndex;
    pFindIndex = (FindIndexF)GetProcAddress(load, "findIndex");

    FillOutF pFillOut;
    pFillOut = (FillOutF)GetProcAddress(load, "fillOut");

    FindZeroF pFindZero;
    pFindZero = (FindZeroF)GetProcAddress(load, "findZero");

    PrintPosZeroF  pPrintPosZero;
    pPrintPosZero = (PrintPosZeroF)GetProcAddress(load, "printPosZero");

    PrintReverseMatrixF pPrintReverseMatrix;
    pPrintReverseMatrix = (PrintReverseMatrixF)GetProcAddress(load, "printReverseMatrix");

    ReverseF pReverse;
    pReverse = (ReverseF)GetProcAddress(load, "reverse");

    FreeArrF pFreeArr;
    pFreeArr = (FreeArrF)GetProcAddress(load, "freeArr");

    // Проверяем, что все функции найдены
    if (pFindIndex == nullptr || pFillOut == nullptr || pFindZero == nullptr ||
        pPrintPosZero == nullptr || pPrintReverseMatrix == nullptr ||
        pReverse == nullptr || pFreeArr == nullptr) {
        std::cout << "Error: Could not find functions in the library!" << std::endl;
        FreeLibrary(load);
        return;
    }

    int n = 0, m = 0;
    std::cout << "m: ";
    checkInputIntK(m);
    std::cout << "n: ";
    checkInputIntK(n);

    double** arr = createMatrix(m, n);
    int countZero = pFindZero(arr, m, n);

    int* arrI = new int[countZero];
    int* arrJ = new int[countZero];

    pFindIndex(arrI, arrJ, arr, m, n);
    pPrintPosZero(arrI, arrJ, countZero);

    delete[] arrI;
    delete[] arrJ;

    double* lineArr = pFillOut(arr, m, n);
    pFreeArr(arr, m);

    double** reverseArr = pReverse(lineArr, m, n);
    delete[] lineArr;

    pPrintReverseMatrix(reverseArr, m, n);

    pFreeArr(reverseArr, m);
}

void Menu() {
    std::cout << "\tTask 4\n";
    std::cout << "Zeros are found in the matrix and displayed on the screen.\n"
                 "The matrix is output with the elements in reverse order.\n" << std::endl;
    std::cout << "Creator: Viktoriya Bonchkovskaya\n" << std::endl;
}

int main() {
    int choice = 0;
    while (true) {
        checkInputChoice(choice);

        if (choice == 1) {
            Task();
        }
        else if (choice == 2) {
            break;
        }
        else if (choice == 3) {
            Menu();
        }
    }
    return 0;
}