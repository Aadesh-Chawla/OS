#include<stdio.h>
#include<pthread.h>


const int core=4;

pthread_t thread[core];

void* addition(){}
// void* substraction(){}



void main(){
    printf("Enter n : \n");
    int n,step;
    scanf("%d",&n);
    int matrix_A[n][n];
    int matrix_B[n][n];
    int sum[n][n];
    int sub[n][n];


    int i,j;

    

    printf("Enter elements of matrix A : \n");
    for(i=0; i<n; i++){
        for(j=0; j<n; j++){
            printf("location : A(%d,%d)",&i,&j);
            scanf("%d",&matrix_A[i][j]);
        }
    }

    printf("Enter elements of matrix B : \n");
    for(i=0; i<n; i++){
        for(j=0; j<n; j++){
            printf("location : B(%d,%d)",&i,&j);
            scanf("%d",&matrix_B[i][j]);
        }
    }

    for(i=0; i<core; i++){

        pthread_create(&thread, NULL, &addition, (void*) step);
    }
    for(i=0; i<core; i++){

        pthread_join(thread[i], NULL);
    }

}
