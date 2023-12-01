#include <iostream>
#include <pthread.h>
using namespace std;

const int core = 4;

pthread_t thread[core];


int n;
int matrix_A[100][100];
int matrix_B[100][100];
int sum[100][100];
int sub[100][100];
int mult[100][100];

void* addition(void* step) {
    int start = *((int*)step);
    int end = start + n / core;

    for (int i = start; i < end; i++) {
        for (int j = 0; j < n; j++) {
            sum[i][j] = matrix_A[i][j] + matrix_B[i][j];
        }
    }
    pthread_exit(NULL);
}

int main() {
    cout << "Enter n: ";
    cin >> n;

    cout << "Enter elements of matrix A:" << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << "A(" << i << "," << j << "): ";
            cin >> matrix_A[i][j];
        }
    }

    cout << "Enter elements of matrix B:" << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << "B(" << i << "," << j << "): ";
            cin >> matrix_B[i][j];
        }
    }


    int step = 0;
    float stepSize = n / core;
    for (int i = 0; i < core; i++) {
        pthread_create(&thread[i], NULL, &addition, (void*)&step);
        step += stepSize;    
        cout<<"StepSize : "<<stepSize<<endl;
    }

    for (int i = 0; i < core; i++) {
        pthread_join(thread[i], NULL);
    }

    cout << "Sum Matrix:" << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << sum[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}