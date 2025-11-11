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

void checkInputIntK(int& k) {
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

void checkInputArray(int& x) {
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

void Task() {
    // 1. ЗАГРУЖАЕМ ДИНАМИЧЕСКУЮ БИБЛИОТЕКУ
HINSTANCE load;
load = LoadLibraryA("RecDLL.dll");  // ANSI версия
if (load == nullptr) {
    std::cout << "Error: Failed to load RecDLL.dll!" << std::endl;
    return;
}

    // 2. ОБЪЯВЛЯЕМ ТИПЫ УКАЗАТЕЛЕЙ НА ФУНКЦИИ ИЗ DLL
    typedef int (__stdcall *Min)(const int* arr, int left, int right);


    // 3. ПОЛУЧАЕМ УКАЗАТЕЛИ НА ФУНКЦИИ ИЗ DLL
    Min pfindMinRecursive;
   Min pgetMinValue;
    pfindMinRecursive = (Min)GetProcAddress(load, "findMinRecursive");
    pgetMinValue = (Min)GetProcAddress(load, "getMinValue");

    // Проверяем, что все функции найдены
    if (pfindMinRecursive == nullptr || pgetMinValue == nullptr ) {
        std::cout << "Error: Could not find functions in the library!" << std::endl;
        FreeLibrary(load);
        return;
    }

    int n;
    std::cout << "Enter amount of massive: ";
    checkInputIntK(n);
    int* arr = new int[n];
    for (int i = 0; i < n; i++) {
        std::cout << "Enter a" << i << ": ";
        checkInputArray(arr[i]);
    }
   // Вызов первой функции
std::cout << "Recursive result: " << pfindMinRecursive(arr, 0, n - 1) << std::endl;

// ВЫЗОВ ВТОРОЙ ФУНКЦИИ
std::cout << "Min value result: " << pgetMinValue(arr, 0, n - 1) << std::endl;


    // 5. ВЫГРУЖАЕМ БИБЛИОТЕКУ ИЗ ПАМЯТИ
    FreeLibrary(load);
}

void Menu() {
    std::cout << "\tTask 2\n";
    std::cout << "\tVariant 5\n";
    std::cout << "The task involves using a recursive function to find the product of all elements in an array.\n";
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