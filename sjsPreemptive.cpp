#include <iostream>
#include <queue>
#include <iomanip>
#include <vector>
#include <algorithm>

using namespace std;

struct Process
{
    int pid;
    int arrivalTime;
    int burstTime;
    int remainingTime;
    int startTime;
    int endTime;
    int waitingTime;
    int turnAroundTime;

    bool operator<(const Process &p) const
    {
        // Sort processes according to remaining burst time
        return remainingTime > p.remainingTime;
    }
};

void sjfPreemptiveScheduling(vector<Process> &processes)
{
    int n = processes.size();
    int currentTime = 0;
    int totalWaitingTime = 0;
    int totalTurnAroundTime = 0;

    priority_queue<Process> readyQueue;

    cout << left << setw(10) << "Process" << setw(20) << "Arrival Time" << setw(20) << "Burst Time" << setw(20) << "Start Time" << setw(20) << "Finish Time" << setw(20) << "Waiting Time" << setw(20) << "Turnaround Time" << endl;

    while (!readyQueue.empty() || !processes.empty())
    {
        // Add arrived processes to ready queue
        while (!processes.empty() && processes.front().arrivalTime <= currentTime)
        {
            processes.front().remainingTime = processes.front().burstTime;
            readyQueue.push(processes.front());
            processes.erase(processes.begin());
        }

        // If no process is in ready queue, skip to next arrival
        if (readyQueue.empty())
        {
            currentTime = processes.front().arrivalTime;
            continue;
        }

        // Process first process in ready queue
        Process currentProcess = readyQueue.top();
        readyQueue.pop();

        // Calculate start time of the process
        currentProcess.startTime = currentTime;
        currentTime = max(currentTime, currentProcess.arrivalTime); //// Increment current time to the arrival time of the current process

        // Decrement the remaining time of the process
        currentProcess.remainingTime--;

        // If the process has completed execution
        if (currentProcess.remainingTime == 0)
        {
            currentProcess.endTime = currentTime;
            currentProcess.waitingTime = currentProcess.endTime - currentProcess.burstTime - currentProcess.arrivalTime;
            currentProcess.turnAroundTime = currentProcess.endTime - currentProcess.arrivalTime;
            totalWaitingTime += currentProcess.waitingTime;
            totalTurnAroundTime += currentProcess.turnAroundTime;
        }
        else
        {
            readyQueue.push(currentProcess);
        }

        cout << left << setw(10) << currentProcess.pid << setw(20) << currentProcess.arrivalTime << setw(20) << currentProcess.burstTime << setw(20) << currentProcess.waitingTime << setw(20) << currentProcess.turnAroundTime << endl;
    }

    double avgWaitingTime = (double)totalWaitingTime / n;
    double avgTurnaroundTime = (double)totalTurnAroundTime / n;

    // Printing average waiting time and average turn around time
    cout << "--------------------------------------------------------------------" << endl;
    cout << "Average Waiting Time = " << avgWaitingTime << endl;
    cout << "Average Turnaround Time = " << avgTurnaroundTime << endl;
    cout << "--------------------------------------------------------------------" << endl;
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

    sjfPreemptiveScheduling(processes);

    return 0;
}
