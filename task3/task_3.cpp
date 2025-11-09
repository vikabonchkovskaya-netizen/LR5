#include <iostream>
#include <sstream>
#include <string>

using namespace std;

// Функция для проверки ввода выбора меню
void checkInputChoice(int& choice) {
    while (true) {
        cout << "Start?\n1. YES\n2. EXIT\n3. Show menu\n";
        string line;
        if (!getline(cin, line)) {
            cout << "Input error.\n";
            continue;
        }
        stringstream ss(line);
        if (ss >> choice && ss.eof()) {
            if (choice >= 1 && choice <= 3) {
                break;
            }
            else {
                cout << "Incorrect input. Enter 1, 2, or 3.\n";
            }
        }
        else {
            cout << "Incorrect input. Enter a single number.\n";
        }
    }
}

// Функция для проверки ввода размеров матрицы
void checkInputInt(int& k) {
    while (true) {
        string line;
        if (!getline(cin, line)) {
            cout << "Input error.\n";
            continue;
        }
        stringstream ss(line);
        if (ss >> k && ss.eof()) {
            if (k < 1) {
                cout << "Input error. Enter positive integer: ";
                continue;
            } else {
                break;
            }
        } else {
            cout << "Incorrect input. Enter integer: ";
        }
    }
}

// Функция для проверки ввода элементов массива
void checkInputArray(int& x) {
    while (true) {
        string line;
        if (!getline(cin, line)) {
            cout << "Input error.\n";
            continue;
        }
        stringstream ss(line);
        if (ss >> x && ss.eof()) {
            break;
        } else {
            cout << "Incorrect input. Enter integer: ";
        }
    }
}

// Функция создания матрицы
int** creatMatrix(int n, int k) {
    int** arr = new int*[n];
    for (int i = 0; i < n; i++) {
        arr[i] = new int[k];
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < k; j++) {
            cout << "a[" << i << "][" << j << "]: ";
            checkInputArray(arr[i][j]);
        }
    }
    return arr;
}

// Функция вывода матрицы
void printInitial(int** arr, int m, int n) {
    cout << "Initial matrix:" << endl;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            cout << arr[i][j] << " ";
        }
        cout << endl;
    }
}

// Функция извлечения элементов главной диагонали
int* findElOnD(int** matrix, int n, int k, int& count) {
    // Определяем размер главной диагонали (минимальный из n и k)
    count = (n < k) ? n : k;
    int* diagonal = new int[count];
    
    // Извлекаем элементы главной диагонали
    for (int i = 0; i < count; i++) {
        diagonal[i] = matrix[i][i];
    }
    
    return diagonal;
}

// Функция вычисления произведения элементов массива
int multiply(int* array, int size) {
    if (size == 0) return 0;
    
    int product = 1;
    for (int i = 0; i < size; i++) {
        product *= array[i];
    }
    
    return product;
}

// Функция освобождения памяти матрицы
void freeMatrix(int** matrix, int rows) {
    for (int i = 0; i < rows; i++) {
        delete[] matrix[i];
    }
    delete[] matrix;
}

// Основная функция выполнения задачи
void Task() {
    int n = 0, k = 0;
    
    cout << "Enter number of rows (n): ";
    checkInputInt(n);
    cout << "Enter number of columns (k): ";
    checkInputInt(k);

    // Создаем матрицу
    int** arr = creatMatrix(n, k);
    
    // Выводим исходную матрицу
    printInitial(arr, n, k);
    
    // Извлекаем главную диагональ
    int count = 0;
    int* diagonal = findElOnD(arr, n, k, count);
    
    // Вычисляем произведение
    int product = multiply(diagonal, count);
    
    // Выводим результаты
    cout << "Elements on main diagonal: ";
    for (int i = 0; i < count; i++) {
        cout << diagonal[i] << " ";
    }
    cout << endl;
    cout << "Product of diagonal elements: " << product << endl;
    
    // Освобождаем память
    freeMatrix(arr, n);
    delete[] diagonal;
}

// Функция отображения меню
void Menu() {
    cout << "\n=== Task 3 ===" << endl;
    cout << "Description: Program processes 2D array, extracts main diagonal" << endl;
    cout << "Creator: Viktoriya Bonchkovskaya" << endl;
}

// Главная функция
int main() {
    int choice = 0;
    Menu();
    
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