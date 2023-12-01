#include <iostream>
#include <vector>
using namespace std;

void roundRobinScheduling(vector<string> jobs, vector<int> burstTime, int timeQuantum) {
    int n = jobs.size();
    vector<int> finishTime(n, 0);
    vector<int> turnaroundTime(n, 0);
    vector<int> waitingTime(n, 0);

    vector<int> remainingBurstTime(n);
    for (int i = 0; i < n; i++) {
        remainingBurstTime[i] = burstTime[i];
    }

    int time = 0;
    while (true) {
        bool done = true;
        for (int i = 0; i < n; i++) {
            if (remainingBurstTime[i] > 0) {
                done = false;
                if (remainingBurstTime[i] > timeQuantum) {
                    time += timeQuantum;
                    remainingBurstTime[i] -= timeQuantum;
                } else {
                    time += remainingBurstTime[i]
                    waitingTime[i] = time - burstTime[i];
                    remainingBurstTime[i] = 0
                    finishTime[i] = time;
                }
            }
        }

        if (done) {
            break;
        }
    }

    for (int i = 0; i < n; i++) {
        turnaroundTime[i] = finishTime[i];
    }

    cout << "Round Robin Scheduling:" << endl;
    cout << "Process\tFinish Time\tTurnaround Time\tWaiting Time\n";
    for (int i = 0; i < n; i++) {
        cout << jobs[i] << "\t" << finishTime[i] << "\t\t" << turnaroundTime[i] << "\t\t" << waitingTime[i] << "\n";
    }
}

int main() {
    vector<string> jobs = {"Job1", "Job2", "Job3"};
    vector<int> burstTime = {10, 5, 8};
    int timeQuantum = 2;

    roundRobinScheduling(jobs, burstTime, timeQuantum);

    return 0;
}
