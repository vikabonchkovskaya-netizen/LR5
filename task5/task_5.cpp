#include <iostream>
#include <sstream>
#include <string>

// Существующие функции ввода
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
                break;
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

// Функции, которые ранее были в DLL
int countEvenColumnOddNumber(int** arr, int m, int n) {
    int count = 0;
    for (int j = 0; j < n; j += 2) { // Четные столбцы (индексы 0, 2, 4...)
        for (int i = 0; i < m; i++) {
            if (arr[i][j] % 2 != 0) { // Нечетные числа
                count++;
            }
        }
    }
    return count;
}

void fillOut(int** arr, int* out, int m, int n) {
    int index = 0;
    for (int j = 0; j < n; j += 2) {
        for (int i = 0; i < m; i++) {
            if (arr[i][j] % 2 != 0) {
                out[index++] = arr[i][j];
            }
        }
    }
}

double findAverage(int* arr, int count) {
    if (count == 0) return 0.0;
    
    double sum = 0;
    for (int i = 0; i < count; i++) {
        sum += arr[i];
    }
    return sum / count;
}

void printInitial(int** arr, int m, int n) {
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            std::cout << arr[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

void printDynamic(int* arr, int count) {
    for (int i = 0; i < count; i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
}

void freeArr(int** arr, int m) {
    for (int i = 0; i < m; i++) {
        delete[] arr[i];
    }
    delete[] arr;
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
    int n = 0, m = 0;
    std::cout << "m: ";
    checkInputIntK(m);
    std::cout << "n: ";
    checkInputIntK(n);

    int** arr = createMatrix(m, n);
    std::cout << "Initial massive:" << std::endl;
    printInitial(arr, m, n);

    int count = countEvenColumnOddNumber(arr, m, n);

    if (count != 0) {
        int* evenColumnOddNumberArr = new int[count];
        fillOut(arr, evenColumnOddNumberArr, m, n);

        freeArr(arr, m);

        std::cout << "Odd numbers in even columns:" << std::endl;
        printDynamic(evenColumnOddNumberArr, count);

        std::cout << "Arithmetical mean: " << findAverage(evenColumnOddNumberArr, count) << std::endl;

        delete[] evenColumnOddNumberArr;
    } else {
        freeArr(arr, m);
        std::cout << "No such numbers" << std::endl;
    }
}

void Menu() {
    std::cout << "\tTask 5\n";
    std::cout << "Show odd numbers in even columns\n" << std::endl;
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