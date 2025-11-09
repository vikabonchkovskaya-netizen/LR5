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

void checkInputArray(int& x){
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

int** createMatrix(int m, int n) {
    int** arr = new int*[m];
    for (int i = 0; i < m; i++) {
        arr[i] = new int[n];
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

    // 2. ОБЪЯВЛЯЕМ ТИПЫ УКАЗАТЕЛЕЙ НА ФУНКЦИИ ИЗ DLL
    typedef int (__stdcall *CountF)(int**, int, int);
    typedef void (__stdcall *FillF)(int**, int*, int, int);
    typedef double (__stdcall *AverageF)(int*, int);
    typedef void (__stdcall *PrintInitialF)(int** arr, int m, int n);
    typedef void (__stdcall *PrintDynamicF)(int* arr, int count);
    typedef void (__stdcall *FreeArrF)(int** arr, int m);

    // 3. ПОЛУЧАЕМ УКАЗАТЕЛИ НА ФУНКЦИИ ИЗ DLL
    CountF pCount;
    pCount = (CountF)GetProcAddress(load, "countEvenColumnOddNumber");

    FillF pFill;
    pFill = (FillF)GetProcAddress(load, "fillOut");

    AverageF pAverage;
    pAverage = (AverageF)GetProcAddress(load, "findAverage");

    PrintInitialF pPrintInitial;
    pPrintInitial = (PrintInitialF)GetProcAddress(load, "printInitial");

    PrintDynamicF pPrintDynamic;
    pPrintDynamic = (PrintDynamicF)GetProcAddress(load, "printDynamic");

    FreeArrF pFreeArr;
    pFreeArr = (FreeArrF)GetProcAddress(load, "freeArr");

    // Проверяем, что все функции найдены
    if (pCount == nullptr || pFill == nullptr || pAverage == nullptr ||
        pPrintInitial == nullptr || pPrintDynamic == nullptr || pFreeArr == nullptr) {
        std::cout << "Error: Could not find functions in the library!" << std::endl;
        FreeLibrary(load);
        return;
    }

    int n = 0, m = 0;
    std::cout << "m: ";
    checkInputIntK(m);
    std::cout << "n: ";
    checkInputIntK(n);

    int** arr = createMatrix(m, n);
    std::cout << "Initial massive:" << std::endl;
    pPrintInitial(arr, m, n);

    int count = pCount(arr, m, n);

    if (count != 0) {
        int* evenColumnOddNumberArr = new int[count];
        pFill(arr, evenColumnOddNumberArr, m, n);

        pFreeArr(arr, m);

        std::cout << "Odd numbers in even columns:" << std::endl;
        pPrintDynamic(evenColumnOddNumberArr, count);

        std::cout << "Arithmetical mean: " << pAverage(evenColumnOddNumberArr, count) << std::endl;

        delete[] evenColumnOddNumberArr;
    } else {
        pFreeArr(arr, m);
        std::cout << "No such numbers" << std::endl;
    }

    // 5. ВЫГРУЖАЕМ БИБЛИОТЕКУ ИЗ ПАМЯТИ
    FreeLibrary(load);
}

void Menu() {
    std::cout << "\tTask 5\n";
    std::cout << "Show odd numbers in even columns\n" << std::endl;
    std::cout << "Creator:Viktoriya Bonchkovskaya\n" << std::endl;
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