#include<iostream>

using namespace std;

int main() {
    int max[10][10], alloc[10][10], need[10][10], avail[10], np, nr;

    cout << "Enter the number of processes: ";
    cin >> np;

    cout << "Enter the number of resources: ";
    cin >> nr;

    cout << "Enter the allocation matrix:\n";
    for(int i=0; i<np; i++)
        for(int j=0; j<nr; j++)
            cin >> alloc[i][j];

    cout << "Enter the max matrix:\n";
    for(int i=0; i<np; i++)
        for(int j=0; j<nr; j++)
            cin >> max[i][j];

    cout << "Enter the available resources:\n";
    for(int i=0; i<nr; i++)
        cin >> avail[i];

    for(int i=0; i<np; i++)
        for(int j=0; j<nr; j++)
            need[i][j] = max[i][j] - alloc[i][j];

    int finish[10], safeSeq[10];
    for(int i=0; i<np; i++)
        finish[i] = 0;
    
    int work[10];
    for(int i=0; i<nr; i++)
        work[i] = avail[i];

    int count=0;
    while(count < np) {
        int found = 0;
        for(int p=0; p<np; p++) {
            if(finish[p] == 0) {
                int j;
                for(j=0; j<nr; j++) {
                    if(need[p][j] > work[j])
                        break;
                }
                if(j == nr) {
                    for(int k=0; k<nr; k++)
                        work[k] += alloc[p][k];
                    safeSeq[count++] = p;
                    finish[p] = 1;
                    found = 1;
                }
            }
        }
        if(found == 0) {
            cout << "System is not in a safe state due to process: " << count << endl;
            return 0;
        }
    }

    cout << "System is in a safe state.\nSafe sequence is: ";
    for(int i=0; i<np; i++)
        cout << safeSeq[i] << " ";

    return 0;
}
