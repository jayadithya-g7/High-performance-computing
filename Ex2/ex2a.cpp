#include <iostream>
#include <chrono>
#include <cstdlib>  

using namespace std;

void method1(int* mat, int* vector, int* result, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < 1; k++) {
                *(result + (n * i) + j) += *(mat + (n * i) + k) * *(vector + (n * k) + j);
            }
        }
    }
}

void method2(int* mat, int* vector, int* result, int n) {
    for (int i = 0; i < n; i++) {
        int sum = 0;
        for (int j = 0; j < n; j++) {
            sum += *(mat + (n * i) + j) * *(vector + j);
        }
        *(result + i) = sum;
    }
}

int main() {
    int n;
    cout << "Enter n: ";
    cin >> n;

    int matrix[n][n];
    int vector[n][1];
    int result[n][1];

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            matrix[i][j] = std::rand() % 100;
        }
    }

    for (int i = 0; i < n; i++) {
        vector[i][0] = std::rand() % 100;
    }

    for (int i = 0; i < n; i++) {
        result[i][0] = 0;
    }

    auto start = chrono::high_resolution_clock::now();
    method1(&matrix[0][0], &vector[0][0], &result[0][0], n);
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> duration = end - start;
    cout << "Matrix-vector multiplication (method1): " << duration.count() << " seconds\n";

    // Reset result before next method
    for (int i = 0; i < n; i++) {
        result[i][0] = 0;
    }

    start = chrono::high_resolution_clock::now();
    method2(&matrix[0][0], &vector[0][0], &result[0][0], n);
    end = chrono::high_resolution_clock::now();
    duration = end - start;
    cout << "Matrix-vector multiplication (method2): " << duration.count() << " seconds\n";

    return 0;
}

