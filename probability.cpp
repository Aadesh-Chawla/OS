#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void priorityNonPreemptive(vector<string> jobs, vector<int> burstTime, vector<int> jobPriority) {
    int n = jobs.size();
    vector<int> finishTime(n, 0);
    vector<int> turnaroundTime(n, 0);
    vector<int> waitingTime(n, 0);

    vector<int> prioritySorted(n);
    for (int i = 0; i < n; i++) {
        prioritySorted[i] = jobPriority[i];
    }
    sort(prioritySorted.begin(), prioritySorted.end(), greater<int>());

    finishTime[0] = burstTime[0];
    turnaroundTime[0] = finishTime[0];
    waitingTime[0] = 0;

    for (int i = 1; i < n; i++) {
        int index = find(jobPriority.begin(), jobPriority.end(), prioritySorted[i]) - jobPriority.begin();
        finishTime[i] = finishTime[i-1] + burstTime[index];
        turnaroundTime[i] = finishTime[i];
        waitingTime[i] = turnaroundTime[i] - burstTime[index];
    }

    cout << "Non-Preemptive Priority Scheduling:" << endl;
    cout << "Process\tFinish Time\tTurnaround Time\tWaiting Time\n";
    for (int i = 0; i < n; i++) {
        cout << jobs[i] << "\t" << finishTime[i] << "\t\t" << turnaroundTime[i] << "\t\t" << waitingTime[i] << "\n";
    }
}

void priorityPreemptive(vector<string> jobs, vector<int> burstTime, vector<int> jobPriority) {
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
        int maxPriority = *max_element(jobPriority.begin(), jobPriority.end());
        if (maxPriority == INT_MIN) {
            break;
        }

        int maxPriorityIndex = find(jobPriority.begin(), jobPriority.end(), maxPriority) - jobPriority.begin();

        if (remainingBurstTime[maxPriorityIndex] > 0) {
            finishTime[maxPriorityIndex] = time + 1;
            remainingBurstTime[maxPriorityIndex] -= 1;
        }

        if (remainingBurstTime[maxPriorityIndex] == 0) {
            jobPriority[maxPriorityIndex] = INT_MIN;
            turnaroundTime[maxPriorityIndex] = finishTime[maxPriorityIndex];
            waitingTime[maxPriorityIndex] = turnaroundTime[maxPriorityIndex] - burstTime[maxPriorityIndex];
        }

        time += 1;
    }

    for (int i = 0; i < n; i++) {
        turnaroundTime[i] = finishTime[i];
    }

    cout << "\nPreemptive Priority Scheduling:" << endl;
    cout << "Process\tFinish Time\tTurnaround Time\tWaiting Time\n";
    for (int i = 0; i < n; i++) {
        cout << jobs[i] << "\t" << finishTime[i] << "\t\t" << turnaroundTime[i] << "\t\t" << waitingTime[i] << "\n";
    }
}

int main() {
    vector<string> jobs = {"Job1", "Job2", "Job3", "Job4"};
    vector<int> burstTime = {8, 4, 9, 5};
    vector<int> jobPriority = {2, 3, 1, 4};

    priorityNonPreemptive(jobs, burstTime, jobPriority);
    priorityPreemptive(jobs, burstTime, jobPriority);

    return 0;
}
