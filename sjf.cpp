#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void sjfNonPreemptive(vector<string> jobs, vector<int> executionTime) {
    int n = jobs.size();
    vector<int> finishTime(n, 0);
    vector<int> turnaroundTime(n, 0);
    vector<int> waitingTime(n, 0);

    vector<int> executionTimeSorted(n);
    for (int i = 0; i < n; i++) {
        executionTimeSorted[i] = executionTime[i];
    }
    sort(executionTimeSorted.begin(), executionTimeSorted.end());

    finishTime[0] = executionTime[0];
    turnaroundTime[0] = finishTime[0];
    waitingTime[0] = 0;

    for (int i = 1; i < n; i++) {
        int index = find(executionTime.begin(), executionTime.end(), executionTimeSorted[i]) - executionTime.begin();
        finishTime[i] = finishTime[i-1] + executionTime[index];
        turnaroundTime[i] = finishTime[i];
        waitingTime[i] = turnaroundTime[i] - executionTime[index];
    }

    cout << "Non-Preemptive SJF Scheduling:" << endl;
    cout << "Process\tFinish Time\tTurnaround Time\tWaiting Time\n";
    for (int i = 0; i < n; i++) {
        cout << jobs[i] << "\t" << finishTime[i] << "\t\t" << turnaroundTime[i] << "\t\t" << waitingTime[i] << "\n";
    }
}

void sjfPreemptive(vector<string> jobs, vector<int> executionTime) {
    int n = jobs.size();
    vector<int> finishTime(n, 0);
    vector<int> turnaroundTime(n, 0);
    vector<int> waitingTime(n, 0);

    vector<int> remainingExecutionTime(n);
    for (int i = 0; i < n; i++) {
        remainingExecutionTime[i] = executionTime[i];
    }

    int time = 0;
    while (true) {
        bool done = true;
        for (int i = 0; i < n; i++) {
            if (remainingExecutionTime[i] > 0) {
                done = false;
                if (remainingExecutionTime[i] > 1) {
                    time += 1;
                    remainingExecutionTime[i] -= 1;
                } else {
                    time += remainingExecutionTime[i];
                    waitingTime[i] = time - executionTime[i];
                    remainingExecutionTime[i] = 0;
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

    cout << "\nPreemptive SJF Scheduling:" << endl;
    cout << "Process\tFinish Time\tTurnaround Time\tWaiting Time\n";
    for (int i = 0; i < n; i++) {
        cout << jobs[i] << "\t" << finishTime[i] << "\t\t" << turnaroundTime[i] << "\t\t" << waitingTime[i] << "\n";
    }
}

int main() {
    vector<string> jobs = {"Job1", "Job2", "Job3", "Job4"};
    vector<int> executionTime = {6, 8, 7, 3};

    sjfNonPreemptive(jobs, executionTime);
    sjfPreemptive(jobs, executionTime);

    return 0;
}
