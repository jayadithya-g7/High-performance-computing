#include <iostream>
#include <chrono>
#include <cstdlib>

using namespace std;
using namespace std::chrono;

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
        for (int k = 0; k < 1; k++) {
            for (int j = 0; j < n; j++) {
                *(result + (n * i) + j) += *(mat + (n * i) + k) * *(vector + (n * k) + j);
            }
        }
    }
}

void method3(int* mat, int* vector, int* result, int n) {
    for (int j = 0; j < n; j++) {
        for (int k = 0; k < 1; k++) {
            for (int i = 0; i < n; i++) {
                *(result + (n * i) + j) += *(mat + (n * i) + k) * *(vector + (n * k) + j);
            }
        }
    }
}

void method4(int* mat, int* vector, int* result, int n) {
    for (int j = 0; j < n; j++) {
        for (int i = 0; i < n; i++) {
            for (int k = 0; k < 1; k++) {
                *(result + (n * i) + j) += *(mat + (n * i) + k) * *(vector + (n * k) + j);
            }
        }
    }
}

void method5(int* mat, int* vector, int* result, int n) {
    for (int k = 0; k < 1; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                *(result + (n * i) + j) += *(mat + (n * i) + k) * *(vector + (n * k) + j);
            }
        }
    }
}

void method6(int* mat, int* vector, int* result, int n) {
    for (int k = 0; k < 1; k++) {
        for (int j = 0; j < n; j++) {
            for (int i = 0; i < n; i++) {
                *(result + (n * i) + j) += *(mat + (n * i) + k) * *(vector + (n * k) + j);
            }
        }
    }
}

int main(int argc, char* argv[0]) {
    // int n;
    // cout << "enter n: ";
    // cin >> n;
    int n= atoi(argv[1])

    int matrix[n][n];
    int vector[n][1];
    int result[n][1];

    int r1 = n;
    int c1 = n;
    int r2 = n;
    int c2 = 1;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            matrix[i][j] = std::rand() % 100;
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            matrix[i][j] = std::rand() % 100;
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 1; j++) {
            result[i][j] = 0;
        }
    }

    std::chrono::duration<double> duration;

    auto start = std::chrono::high_resolution_clock::now();

    method1(&matrix[0][0], &vector[0][0], &result[0][0], n);

    auto end = std::chrono::high_resolution_clock::now();

    duration = end - start;

    cout << "ijk :" << duration.count() << endl;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 1; j++) {
            result[i][j] = 0;
        }
    }

    start = std::chrono::high_resolution_clock::now();
    method2(&matrix[0][0], &vector[0][0], &result[0][0], n);
    end = std::chrono::high_resolution_clock::now();
    duration = end - start;
    cout << "ikj:" << duration.count() << endl;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 1; j++) {
            result[i][j] = 0;
        }
    }

    start = std::chrono::high_resolution_clock::now();
    method3(&matrix[0][0], &vector[0][0], &result[0][0], n);
    chrono::duration <double> duration= end - start;
    end = std::chrono::high_resolution_clock::now();
    duration = end - start;
    cout << "jki:" << duration.count() << endl;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 1; j++) {
            result[i][j] = 0;
        }
    }

    start = std::chrono::high_resolution_clock::now();
    method4(&matrix[0][0], &vector[0][0], &result[0][0], n);
    end = std::chrono::high_resolution_clock::now();
    duration = end - start;
    cout << "jik:" << duration.count() << endl;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 1; j++) {
            result[i][j] = 0;
        }
    }

    start = std::chrono::high_resolution_clock::now();
    method5(&matrix[0][0], &vector[0][0], &result[0][0], n);
    end = std::chrono::high_resolution_clock::now();
    duration = end - start;
    cout << "kij :" << duration.count() << endl;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 1; j++) {
            result[i][j] = 0;
        }
    }

    start = std::chrono::high_resolution_clock::now();
    method6(&matrix[0][0], &vector[0][0], &result[0][0], n);
    end = std::chrono::high_resolution_clock::now();
    duration = end - start;
    cout << "kji :" << duration.count() << endl;

    return 0;
}

