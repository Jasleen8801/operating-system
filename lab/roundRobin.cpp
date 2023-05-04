#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

struct Process
{
    int pid;
    int arrivalTime;
    int burstTime;
    int waitingTime;
    int turnAroundTime;
    int startTime;
    int remainingTime;
    int finishTime;
};

bool compareArrivalTime(Process p1, Process p2)
{
    return p1.arrivalTime < p2.arrivalTime;
}

void roundRobinScheduling(vector<Process> &processes, int timeQuantum)
{
    int n = processes.size();
    int currentTime = 0;
    int totalWaitingTime = 0;
    int totalTurnAroundTime = 0;

    queue<Process> readyQueue;

    // Sort processes according to arrival time
    sort(processes.begin(), processes.end(), compareArrivalTime);

    // Add the first process to the ready queue
    readyQueue.push(processes[0]);

    cout << left << setw(10) << "Process" << setw(20) << "Arrival Time" << setw(20) << "Burst Time" << setw(20) << "Start Time" << setw(20) << "Finish Time" << setw(20) << "Waiting Time" << setw(20) << "Turnaround Time" << endl;

    while (!readyQueue.empty())
    {
        int i = readyQueue.front().pid;
        readyQueue.pop();

        // Calculate start time of the process
        processes[i].waitingTime = currentTime - processes[i].startTime;
        processes[i].startTime = currentTime;

        // Execute process for the time quantum or the remaining time of the process, whichever is smaller
        int executionTime = min(timeQuantum, processes[i].remainingTime);
        currentTime += executionTime;
        processes[i].remainingTime -= executionTime;

        // If the process is not finished, add it to the ready queue
        if (processes[i].remainingTime > 0)
        {
            readyQueue.push(processes[i]);
        }
        else
        {
            // Calculate end time of the process
            processes[i].finishTime = currentTime;
            processes[i].turnAroundTime = processes[i].finishTime - processes[i].arrivalTime;
            processes[i].waitingTime = processes[i].turnAroundTime - processes[i].burstTime;
            totalWaitingTime += processes[i].waitingTime;
            totalTurnAroundTime += processes[i].turnAroundTime;
        }

        // Add the processes that have arrived and not yet executed to the ready queue
        for (int j = 0; j < n; j++)
        {
            if (processes[j].arrivalTime <= currentTime && processes[j].remainingTime > 0)
            {
                readyQueue.push(processes[j]);
            }
        }

        if (readyQueue.empty())
        {
            currentTime++;
            continue;
        }

        int processIndex = readyQueue.front().pid;
        readyQueue.pop();

        // Execute the process for the time quantum or the remaining time of the process, whichever is smaller
        int remainingTime = processes[processIndex].remainingTime;
        int executedTime = min(timeQuantum, remainingTime);
        currentTime += executedTime;
        processes[processIndex].remainingTime -= executedTime;

        // Update the start time and finish time of the process if it is the first time it is being executed
        if (processes[processIndex].startTime == -1)
        {
            processes[processIndex].startTime = currentTime - executedTime;
        }
        if (processes[processIndex].remainingTime == 0)
        {
            processes[processIndex].finishTime = currentTime;
            processes[processIndex].waitingTime = processes[processIndex].finishTime - processes[processIndex].arrivalTime - processes[processIndex].burstTime;
            processes[processIndex].turnAroundTime = processes[processIndex].finishTime - processes[processIndex].arrivalTime;
            totalWaitingTime += processes[processIndex].waitingTime;
            totalTurnAroundTime += processes[processIndex].turnAroundTime;
        }
        else
        {
            readyQueue.push(processes[processIndex]);
        }

        // Add the processes that have arrived and not yet executed to the ready queue
        for (int j = 0; j < n; j++)
        {
            if (processes[j].arrivalTime <= currentTime && processes[j].remainingTime > 0)
            {
                readyQueue.push(processes[j]);
            }
        }
    }

    for (int i = 0; i < n; i++)
    {
        cout << left << setw(10) << processes[i].pid << setw(20) << processes[i].arrivalTime << setw(20) << processes[i].burstTime << setw(20) << processes[i].startTime << setw(20) << processes[i].finishTime << setw(20) << processes[i].waitingTime << setw(20) << processes[i].turnAroundTime << endl;
    }

    cout << "Average waiting time: " << (float)totalWaitingTime / n << endl;
    cout << "Average turnaround time: " << (float)totalTurnAroundTime / n << endl;
}

int main()
{
    int n;
    int timeQuantum;

    cout << "Enter the number of processes: ";
    cin >> n;
    cout << "Enter the time quantum: ";
    cin >> timeQuantum;

    vector<Process> processes(n);

    for (int i = 0; i < n; i++)
    {
        cout << "Enter the arrival time of process " << i + 1 << ": ";
        cin >> processes[i].arrivalTime;
        cout << "Enter the burst time of process " << i + 1 << ": ";
        cin >> processes[i].burstTime;
        processes[i].pid = i + 1;
        processes[i].remainingTime = processes[i].burstTime;
        processes[i].startTime = -1;
        processes[i].finishTime = -1;
        processes[i].waitingTime = 0;
        processes[i].turnAroundTime = 0;
    }

    roundRobinScheduling(processes, timeQuantum);

    return 0;
}
