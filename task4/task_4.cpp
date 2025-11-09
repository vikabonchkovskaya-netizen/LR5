#include <iostream>
#include <sstream>
#include <string>

using namespace std;

void checkInputChoice(int& choice) {
    while (true) {
        cout << "Start?\n1. YES\n2. EXIT\n3. Show menu\n";
        string line;
        if (!getline(cin, line)) continue;
        stringstream ss(line);
        if (ss >> choice && ss.eof() && choice >= 1 && choice <= 3) break;
        cout << "Incorrect input. Enter 1, 2, or 3.\n";
    }
}

void checkInputInt(int& k) {
    while (true) {
        string line;

        if (!getline(cin, line)) continue;
        stringstream ss(line);
        if (ss >> k && ss.eof() && k >= 1) break;
        cout << "Input error. Enter positive integer: ";
    }
}

void checkInputDouble(double& x) {
    while (true) {
        string line;
        if (!getline(cin, line)) continue;
        stringstream ss(line);
        if (ss >> x && ss.eof()) break;
        cout << "Incorrect input. Enter number: ";
    }
}

double** createMatrix(int m, int n) {
    double** arr = new double*[m];
    for (int i = 0; i < m; i++) {
        arr[i] = new double[n];
    }
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            cout << "a[" << i << "][" << j << "]: ";
            checkInputDouble(arr[i][j]);
        }
    }
    return arr;
}

void printMatrix(double** arr, int m, int n) {
    cout << "Matrix:" << endl;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            cout << arr[i][j] << " ";
        }
        cout << endl;
    }
}

int countZeros(double** arr, int m, int n) {
    int count = 0;
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            if (arr[i][j] == 0) count++;
    return count;
}

void findZeroPositions(double** arr, int m, int n, int* arrI, int* arrJ) {
    int idx = 0;
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            if (arr[i][j] == 0) {
                arrI[idx] = i;
                arrJ[idx] = j;
                idx++;
            }
}

double* flattenMatrix(double** arr, int m, int n) {
    double* flat = new double[m * n];
    int k = 0;
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            flat[k++] = arr[i][j];
    return flat;
}

double** reverseMatrix(double* flat, int m, int n) {
    double** rev = new double*[m];
    for (int i = 0; i < m; i++) rev[i] = new double[n];
    int k = m * n;
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            rev[i][j] = flat[--k];
    return rev;
}

void freeMatrix(double** arr, int m) {
    for (int i = 0; i < m; i++) delete[] arr[i];
    delete[] arr;
}

void Task() {
    int m, n;
    cout << "Enter number of rows: "; checkInputInt(m);
    cout << "Enter number of columns: "; checkInputInt(n);

    double** arr = createMatrix(m, n);
    printMatrix(arr, m, n);

    int zeroCount = countZeros(arr, m, n);
    if (zeroCount > 0) {
        int* arrI = new int[zeroCount];
        int* arrJ = new int[zeroCount];
        findZeroPositions(arr, m, n, arrI, arrJ);

        cout << "Zero positions: ";
        for (int i = 0; i < zeroCount; i++)
            cout << "[" << arrI[i] << ";" << arrJ[i] << "] ";
        cout << endl;

        delete[] arrI;
        delete[] arrJ;
    } else {
        cout << "No zeros in the matrix." << endl;
    }

    double* flat = flattenMatrix(arr, m, n);
    double** rev = reverseMatrix(flat, m, n);
    delete[] flat;

    cout << "Reversed matrix:" << endl;
    printMatrix(rev, m, n);

    freeMatrix(arr, m);
    freeMatrix(rev, m);
}


void Menu() {
    cout << "\n=== Task ===" << endl;
    cout << "Zeros are found in the matrix and displayed." << endl;
    cout << "The matrix is displayed in reverse order." << endl;
    cout << "Creator: Viktoriya Bonchkovskaya" << endl;
}


int main() {
    Menu();
    int choice;
    while (true) {
        checkInputChoice(choice);
        if (choice == 1) Task();
        else if (choice == 2) break;
        else if (choice == 3) Menu();
    }
    return 0;
}
