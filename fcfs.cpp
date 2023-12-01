#include <iostream>
#include <vector>
using namespace std;


int main()
{
    vector<string> jobs = {"Job1", "Job2", "Job3", "Job4"};
    vector<int> executionTime = {24, 3, 3, 5};

    int numJobs = jobs.size();
    vector<int> finish_time(numJobs, 0);
    vector<int> turnaroundTime(numJobs, 0);
    vector<int> waiting_time(numJobs, 0);

    finish_time[0] = executionTime[0];
    turnaroundTime[0] = finish_time[0];
    waiting_time[0] = 0;

    for (int i = 1; i < numJobs; i++)
    {
        finish_time[i] = finish_time[i - 1] + executionTime[i];
        turnaroundTime[i] = finish_time[i];
        waiting_time[i] = turnaroundTime[i] - executionTime[i];
    }

    cout << "Job\tCompletion Time\tTurnaround Time\tWaiting Time\n";
    for (int i = 0; i < numJobs; i++)
    {
        cout << jobs[i] << "\t" << finish_time[i] << "\t\t" << turnaroundTime[i] << "\t\t" << waiting_time[i] << "\n";
    }
    return 0;
}
