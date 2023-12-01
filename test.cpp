#include <iostream>
#include <pthread.h>
#include <vector>
using namespace std;

struct Matrix {
    vector<vector<int>> data;
    int rows;
    int cols;
};


struct ThreadArgs {
    Matrix* result;
    Matrix* matrix1;
    Matrix* matrix2;
    int start_row;
    int end_row;
};

void* matrixAddition(void* args) {
    ThreadArgs* threadArgs = static_cast<ThreadArgs*>(args);
    for (int i = threadArgs->start_row; i < threadArgs->end_row; ++i) {
        for (int j = 0; j < threadArgs->matrix1->cols; ++j) {
            threadArgs->result->data[i][j] = threadArgs->matrix1->data[i][j] + threadArgs->matrix2->data[i][j];
        }
    }
    pthread_exit(NULL);
}

void* matrixSubtraction(void* args) {
    ThreadArgs* threadArgs = static_cast<ThreadArgs*>(args);
    for (int i = threadArgs->start_row; i < threadArgs->end_row; ++i) {
        for (int j = 0; j < threadArgs->matrix1->cols; ++j) {
            threadArgs->result->data[i][j] = threadArgs->matrix1->data[i][j] - threadArgs->matrix2->data[i][j];
        }
    }
    pthread_exit(NULL);
}

void* matrixMultiplication(void* args) {
    ThreadArgs* threadArgs = static_cast<ThreadArgs*>(args);
    for (int i = threadArgs->start_row; i < threadArgs->end_row; ++i) {
        for (int j = 0; j < threadArgs->matrix2->cols; ++j) {
            threadArgs->result->data[i][j] = 0;
            for (int k = 0; k < threadArgs->matrix1->cols; ++k) {
                threadArgs->result->data[i][j] += threadArgs->matrix1->data[i][k] * threadArgs->matrix2->data[k][j];
            }
        }
    }
    pthread_exit(NULL);
}

int main() {
    int choice;
    while (true) {
        cout << "Matrix Operations Menu:\n";
        cout << "1. Matrix Addition\n";
        cout << "2. Matrix Subtraction\n";
        cout << "3. Matrix Multiplication\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 4) {
            break;
        }

        int rows, cols;
        cout << "Enter number of rows: ";
        cin >> rows;
        cout << "Enter number of columns: ";
        cin >> cols;

        Matrix matrix1, matrix2, result;
        matrix1.rows = matrix2.rows = result.rows = rows;
        matrix1.cols = matrix2.cols = result.cols = cols;

        cout << "Enter elements of matrix 1:\n";
        matrix1.data.resize(rows, vector<int>(cols));
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                cin >> matrix1.data[i][j];
            }
        }

        cout << "Enter elements of matrix 2:\n";
        matrix2.data.resize(rows, vector<int>(cols));
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                cin >> matrix2.data[i][j];
            }
        }

        result.data.resize(rows, vector<int>(cols));

        int numThreads;
        cout << "Enter the number of threads: ";
        cin >> numThreads;

        pthread_t threads[numThreads];
        ThreadArgs threadArgs[numThreads];

        int rowsPerThread = rows / numThreads;
        int extraRows = rows % numThreads;
        int currentRow = 0;

        for (int i = 0; i < numThreads; ++i) {
            threadArgs[i].result = &result;
            threadArgs[i].matrix1 = &matrix1;
            threadArgs[i].matrix2 = &matrix2;
            threadArgs[i].start_row = currentRow;
            threadArgs[i].end_row = currentRow + rowsPerThread + (i < extraRows ? 1 : 0);

            if (choice == 1) {
                pthread_create(&threads[i], NULL, matrixAddition, static_cast<void*>(&threadArgs[i]));
            } else if (choice == 2) {
                pthread_create(&threads[i], NULL, matrixSubtraction, static_cast<void*>(&threadArgs[i]));
            } else if (choice == 3) {
                pthread_create(&threads[i], NULL, matrixMultiplication, static_cast<void*>(&threadArgs[i]));
            }

            currentRow = threadArgs[i].end_row;
        }

        for (int i = 0; i < numThreads; ++i) {
            pthread_join(threads[i], NULL);
        }

        cout << "Resulting matrix:\n";
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                cout << result.data[i][j] << " ";
            }
            cout << "\n";
        }
    }

    return 0;
}
