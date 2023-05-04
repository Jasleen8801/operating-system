#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>

using namespace std;

struct Process
{
    int pid;
    int arrivalTime;
    int burstTime;
    int waitingTime;
    int turnAroundTime;
    int startTime;
};

bool compareArrivalTime(Process p1, Process p2)
{
    return p1.arrivalTime < p2.arrivalTime;
}

bool compareBurstTime(Process p1, Process p2)
{
    return p1.burstTime < p2.burstTime;
}

void sjfNonPreemptiveScheduling(vector<Process> &processes)
{
    int n = processes.size();
    int currentTime = 0;
    int totalWaitingTime = 0;
    int totalTurnAroundTime = 0;

    // Sort processes according to arrival time
    sort(processes.begin(), processes.end(), compareArrivalTime);

    cout << left << setw(10) << "Process" << setw(20) << "Arrival Time" << setw(20) << "Burst Time" << setw(20) << "Start Time" << setw(20) << "Finish Time" << setw(20) << "Waiting Time" << setw(20) << "Turnaround Time" << endl;

    for (int i = 0; i < n; i++)
    {
        // Sort processes according to burst time
        sort(processes.begin() + i, processes.end(), compareBurstTime);

        // Calculate start time of the process
        processes[i].waitingTime = currentTime - processes[i].arrivalTime;
        processes[i].turnAroundTime = processes[i].burstTime + processes[i].waitingTime;
        processes[i].waitingTime = max(0, processes[i].waitingTime); // If waiting time is negative, set it to 0
        processes[i].startTime = currentTime;

        // Calculate end time of the process
        currentTime += processes[i].burstTime;
        processes[i].turnAroundTime += processes[i].waitingTime;
        totalWaitingTime += processes[i].waitingTime;
        totalTurnAroundTime += processes[i].turnAroundTime;

        cout << left << setw(10) << processes[i].pid << setw(20) << processes[i].arrivalTime << setw(20) << processes[i].burstTime << setw(20) << processes[i].startTime << setw(20) << currentTime << setw(20) << processes[i].waitingTime << setw(20) << processes[i].turnAroundTime << endl;
    }

    cout << "Average Waiting Time: " << (float)totalWaitingTime / n << endl;
    cout << "Average Turnaround Time: " << (float)totalTurnAroundTime / n << endl;
}

int main()
{
    int n;

    cout << "Enter the number of processes: ";
    cin >> n;

    vector<Process> processes(n);

    for (int i = 0; i < n; i++)
    {
        cout << "Enter the arrival time of process " << i + 1 << ": ";
        cin >> processes[i].arrivalTime;
        cout << "Enter the burst time of process " << i + 1 << ": ";
        cin >> processes[i].burstTime;
        processes[i].pid = i + 1;
    }

    sjfNonPreemptiveScheduling(processes);

    return 0;
}
