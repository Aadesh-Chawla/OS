#include <iostream>
using namespace std;

int main()
{
    int Total_process, Total_resources;
    Total_process = 4;
    Total_resources = 3;
    int finished[5];
    int safe_sequence[Total_process];
    int x = 0;

    int allocated[4][3] = { { 0, 1, 0 }, 
                            { 2, 0, 0 }, 
                            { 3, 0, 2 }, 
                            { 2, 1, 1 } };

    int maximum[4][3] = { { 7, 5, 3 }, 
                            { 3, 2, 2 }, 
                            { 9, 0, 2 }, 
                            { 2, 2, 2 }};

    int availableResources[3] = { 3, 3, 4 };

    for (int k = 0; k < Total_process; k++) {
        finished[k] = 0;
    }

    int resourceNeed[4][3];
    for (int i = 0; i < Total_process; i++) {
        for (int j = 0; j < Total_resources; j++)
            resourceNeed[i][j] = maximum[i][j] - allocated[i][j];
    }

    int y = 0;
    for (int k = 0; k < 4; k++) {
        for (int i = 0; i < Total_process; i++) {
            if (finished[i] == 0) {

                int flag = 0;
                for (int j = 0; j < Total_resources; j++) {
                    if (resourceNeed[i][j] > availableResources[j]){
                        flag = 1;
                        break;
                    }
                }

                if (flag == 0) {
                    safe_sequence[x++] = i;
                    for (y = 0; y < Total_resources; y++)
                        availableResources[y] += allocated[i][y];
                    finished[i] = 1;
                }
            }
        }
    }

    int flag = 1;

    for(int i = 0; i < Total_process; i++) {
        if(finished[i] == 0) {
            flag = 0;
            cout << "Incorrect safe sequence generated.";
            break;
        }
    }

    if(flag == 1) {
        cout << "Safe Sequence : " << endl;
        for (int i = 0; i < Total_process; i++)
            cout << " P" << safe_sequence[i] + 1 << " ->";
        cout<<endl;
    }

    return (0);
}