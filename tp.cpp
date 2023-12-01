#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Process
{
    int processID;
    int arrivalTime;
    int burstTime;
    int remainingBurstTime;
    int startTime;
    int finishTime;
    int waitingTime;
    int turnaroundTime;
};

bool compareArrivalTime(const Process &a, const Process &b)
{
    return a.arrivalTime < b.arrivalTime;
}

int main()
{
    int numProcesses;

    cout << "Enter the number of processes: ";
    cin >> numProcesses;

    vector<Process> processes(numProcesses);

    cout << "Enter arrival time and burst time for each process:\n";
    for (int i = 0; i < numProcesses; i++)
    {
        processes[i].processID = i + 1;
        cout << "Process " << i + 1 << " - Arrival Time: ";
        cin >> processes[i].arrivalTime;
        cout << "Process " << i + 1 << " - Burst Time: ";
        cin >> processes[i].burstTime;
        processes[i].remainingBurstTime = processes[i].burstTime;
    }

    // Sort processes based on arrival time
    sort(processes.begin(), processes.end(), compareArrivalTime);

    int currentTime = processes[0].arrivalTime;
    vector<int> completionTime(numProcesses, 0);

    // SJF preemptive scheduling
    for (int time = currentTime; ; time++)
    {
        int shortestJobIndex = -1;
        int shortestBurstTime = numeric_limits<int>::max();

        for (int i = 0; i < numProcesses; i++)
        {
            if (processes[i].arrivalTime <= time && processes[i].remainingBurstTime > 0 && processes[i].remainingBurstTime < shortestBurstTime)
            {
                shortestJobIndex = i;
                shortestBurstTime = processes[i].remainingBurstTime;
            }
        }

        if (shortestJobIndex == -1)
            break;

        if (processes[shortestJobIndex].startTime == -1)
            processes[shortestJobIndex].startTime = time;

        processes[shortestJobIndex].remainingBurstTime--;
        currentTime = time + 1;

        if (processes[shortestJobIndex].remainingBurstTime == 0)
        {
            processes[shortestJobIndex].finishTime = currentTime;
            completionTime[shortestJobIndex] = currentTime;
        }
    }

    // Calculate waiting time and turnaround time
    for (int i = 0; i < numProcesses; i++)
    {
        processes[i].waitingTime = processes[i].startTime - processes[i].arrivalTime;
        processes[i].turnaroundTime = processes[i].finishTime - processes[i].arrivalTime;
    }

    // Display the table
    cout << "\nProcess\tArrival Time\tBurst Time\tFinish Time\tWaiting Time\tTurnaround Time\n";
    for (const Process &p : processes)
    {
        cout << p.processID << "\t\t" << p.arrivalTime << "\t\t" << p.burstTime << "\t\t"
             << p.finishTime << "\t\t" << p.waitingTime << "\t\t" << p.turnaroundTime << "\n";
    }

    return 0;
}
