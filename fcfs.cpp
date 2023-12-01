#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Process
{
    int processID;
    int arrivalTime;
    int burstTime;
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
    }

    // Sort processes based on arrival time
    sort(processes.begin(), processes.end(), compareArrivalTime);

    // Calculate finish time, waiting time, and turnaround time
    processes[0].finishTime = processes[0].arrivalTime + processes[0].burstTime;
    processes[0].waitingTime = 0;
    processes[0].turnaroundTime = processes[0].burstTime;

    for (int i = 1; i < numProcesses; i++)
    {
        processes[i].finishTime = max(processes[i - 1].finishTime, processes[i].arrivalTime) + processes[i].burstTime;
        processes[i].waitingTime = max(0, processes[i - 1].finishTime - processes[i].arrivalTime);
        processes[i].turnaroundTime = processes[i].waitingTime + processes[i].burstTime;
    }

    // Display the table
    cout << "\nProcess\tArrival Time\tBurst Time\tFinish Time\tWaiting Time\tTurnaround Time\n";
    for (const Process &p : processes)
    {
        cout << p.processID << "\t\t" << p.arrivalTime << "\t\t" << p.burstTime << "\t\t"
             << p.finishTime << "\t\t" << p.waitingTime << "\t\t" << p.turnaroundTime << "\n";
    }

    // Display the final order of execution
    cout << "\nFinal Order of Execution: ";
    for (const Process &p : processes)
    {
        cout << "P" << p.processID << " ";
    }
    cout << "\n";

    return 0;
}
