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

void checkInputIntK(int& k){
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
double findMaxElement(double* X, int n, double* Y, int m)
{
    double maxVal = X[0] * Y[0];
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            double Z = X[i] * Y[j];
            if (Z > maxVal)
                maxVal = Z;
        }
    }
    return maxVal;
}

void Task() {
    int n, m;

    cout << "Vvedite kolichestvo elementov massiva X: ";
    checkInputIntK(n);
    cout << "Vvedite kolichestvo elementov massiva Y: ";
    checkInputIntK(m);

    double* X = new double[n];
    double* Y = new double[m];

    cout << "Vvedite elementi massiva X:" << endl;
    for (int i = 0; i < n; i++) {
        cout << "X[" << i + 1 << "]: ";
        checkInputArray(X[i]);
    }

    cout << "Vvedite elementi massiva Y:" << endl;
    for (int j = 0; j < m; j++) {
        cout << "Y[" << j + 1 << "]: ";
        checkInputArray(Y[j]);
    }

    double maxZ = findMaxElement(X, n, Y, m);
    cout << "\nNaibolshyu element massiva Z = Xi * Yj: " << maxZ << endl;

    delete[] X;
    delete[] Y;
}

void Menu() {
    cout << "\tTask 1" << endl;
    cout << "\tVariant 5" << endl << endl;
    cout << "Sostavit programy dla naxozdeniya naibolchego elementa massiva Z = Xi * Yj." << endl;
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
