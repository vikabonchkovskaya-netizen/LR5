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

int** creatMatrix(int n, int k) {
    int** arr = new int*[n];
    for (int i = 0; i < n; i++) {
        arr[i] = new int[k];
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < k; j++) {
            std::cout << "a" << i << j << ":" << std::endl;
            checkInputArray(arr[i][j]);
        }
    }

    return arr;
}

void printInitial(int** arr, int m, int n) {
    for (int i = 0; i < m; i++){
        for (int j = 0; j < n; j++){
            std::cout << arr[i][j] << " ";
        }
        std::cout << std::endl;
    }
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
    typedef int*(__stdcall *FindELFunc)(int**, int, int, int&);
    typedef int(__stdcall *MultiplyFunc)(int*, int);

    // 3. ПОЛУЧАЕМ УКАЗАТЕЛИ НА ФУНКЦИИ ИЗ DLL
    FindELFunc pFindElOnD;
    pFindElOnD = (FindELFunc)GetProcAddress(load, "findElOnD");
    MultiplyFunc pMultiply;
    pMultiply = (MultiplyFunc)GetProcAddress(load, "multiply");

    // Проверяем, что все функции найдены
    if (pFindElOnD == nullptr || pMultiply == nullptr) {
        std::cout << "Error: Could not find functions in the library!" << std::endl;
        FreeLibrary(load);
        return;
    }

    int n = 0, k = 0;
    std::cout << "n: ";
    checkInputIntK(n);
    std::cout << "k: ";
    checkInputIntK(k);

    int** arr = creatMatrix(n, k);
    std::cout << "Initial massive:" << std::endl;
    printInitial(arr, n, k);
    int count = 0;
    int* onD = pFindElOnD(arr, n, k, count);

    for (int i = 0; i < n; i++) {
        delete[] arr[i];
    }
    delete[] arr;

    if (onD != nullptr) {
        std::cout << "Even elements on main diagonal: ";
        for (int i = 0; i < count; i++) {
            std::cout << onD[i] << " ";
        }
        std::cout << "\nResult of multiply: " << pMultiply(onD, count) << std::endl;
        delete[] onD;
    }

    // 5. ВЫГРУЖАЕМ БИБЛИОТЕКУ ИЗ ПАМЯТИ
    FreeLibrary(load);
}

void Menu() {
    std::cout << "\tTask 3\n";
    std::cout << "Even elements located on the main diagonal and their multiply are displayed\n" << std::endl;
    std::cout << "Creator: Kseniya Siamionava\n" << std::endl;
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