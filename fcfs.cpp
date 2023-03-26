#include <iostream>
#include <queue>
#include <iomanip>

using namespace std;

struct Process
{
    int pid;
    int arrivalTime;
    int burstTime;
};

void fcfsScheduling(Process processes[], int n)
{
    queue<Process> readyQueue;

    int currentTime = 0;
    int totalWaitingTime = 0;
    int totalTurnAroundTime = 0;

    cout << left << setw(10) << "Process" << setw(20) << "Arrival Time" << setw(20) << "Burst Time" << setw(20) << "Waiting Time" << setw(20) << "Turnaround Time" << endl;

    for (int i = 0; i < n; i++)
    {
        // Checking if process has arrived
        while (currentTime < processes[i].arrivalTime)
        {
            currentTime++;
        }

        // Adding process to ready queue
        readyQueue.push(processes[i]);

        // Process first process in the ready queue
        Process currentProcess = readyQueue.front();
        readyQueue.pop();

        // Calculating waiting time and Turn Around Time
        int waitingTime = currentTime - currentProcess.arrivalTime;
        int turnAroundTime = waitingTime + currentProcess.burstTime;

        // Updating total waiting time and total turn around time
        totalWaitingTime += waitingTime;
        totalTurnAroundTime += turnAroundTime;

        // Updating current time
        currentTime += currentProcess.burstTime;

        // Printing process details
        cout << left << setw(10) << currentProcess.pid << setw(20) << currentProcess.arrivalTime << setw(20) << currentProcess.burstTime << setw(20) << waitingTime << setw(20) << turnAroundTime << endl;
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
    Process processes[100];
    int n;

    cout << "Enter the number of processes: ";
    cin >> n;

    for (int i = 0; i < n; i++)
    {
        cout << "Enter the arrival time of process " << i + 1 << ": ";
        cin >> processes[i].arrivalTime;
        cout << "Enter the burst time of process " << i + 1 << ": ";
        cin >> processes[i].burstTime;
        processes[i].pid = i + 1;
    }

    fcfsScheduling(processes, n);

    return 0;
}
