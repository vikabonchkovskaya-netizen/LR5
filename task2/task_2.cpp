#include <iostream>
#include <string>
#include <sstream>
using namespace std;

void checkInputChoice(int& choice) {
    while (true) {
        std::cout << "Start?\n1. YES\n2. EXIT\n3. Show menu\n";
        std::string line;
        if (!std::getline(std::cin, line)) {
            std::cout << "Input error.\n";
            continue;
        }
        std::stringstream ss(line);
        if (ss >> choice && ss.eof()) {
            if (choice >= 1 && choice <= 3) break;
            else std::cout << "Incorrect input. Enter 1, 2, or 3.\n";
        } else {
            std::cout << "Incorrect input. Enter a single number.\n";
        }
    }
}

void checkInputInt(int& k){
    while (true) {
        std::string line;
        if (!std::getline(std::cin, line)) {
            std::cout << "Input error.\n";
            continue;
        }
        std::stringstream ss(line);
        if (ss >> k && ss.eof()) {
            if (k > 0 && k <= 100) break;
            else std::cout << "Oshibka: chislo dolzhno byt' polozhitel'nym i <= 100.\n";
        } else {
            std::cout << "Nekorrektnyy vvod. Vvedite odno tseloye chislo.\n";
        }
    }
}

void checkInputArray(double& value){
    while (true) {
        std::string line;
        if (!std::getline(std::cin, line)) {
            std::cout << "Input error.\n";
            continue;
        }
        std::stringstream ss(line);
        if (ss >> value && ss.eof()) break;
        else std::cout << "Incorrect input. Enter an integer.\n";
    }
}

// --- Рекурсивная функция для нахождения индекса минимального элемента ---
int findMinRecursive(const int* arr, int left, int right) {
    if (left == right) return left; // базовый случай: один элемент
    int mid = (left + right) / 2;
    int leftMin = findMinRecursive(arr, left, mid);
    int rightMin = findMinRecursive(arr, mid + 1, right);
    return (arr[leftMin] <= arr[rightMin]) ? leftMin : rightMin;
}

// --- Задача: поиск минимального элемента ---
void Task() {
    int N;
    cout << "vvedite kolichestvo elementov massiva: ";
    checkInputInt(N);

    int* A = new int[N];
    for (int i = 0; i < N; i++) {
        cout << "A[" << i << "] = ";
        checkInputInt(A[i]);
    }

    int minIndex = findMinRecursive(A, 0, N - 1);
    cout << "\nminimalni element massiva: " << A[minIndex] 
         << ", ego indeks: " << minIndex << endl;

    delete[] A;
}
void Menu() {
    cout << "\tTask 2" << endl;
    cout << "\tVariant 5" << endl << endl;
    cout << "Nayti minimalniy element massiva" << endl;
    cout << "Creator: Viktoriya Bonchkovskaya" << endl << endl;
}

int main() {
    setlocale(LC_ALL, "RU");
    int choice = 0;

    while (true) {
        checkInputChoice(choice);
        if (choice == 1) Task();
        else if (choice == 2) break;
        else if (choice == 3) Menu();
    }
    return 0;
}