#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Process {
    int id;
    int arrivalTime;
    int burstTime;
    int priority;
    int completionTime;
    int turnaroundTime;
    int waitingTime;
};

bool compareArrivalTime(Process p1, Process p2) {
    return p1.arrivalTime < p2.arrivalTime;
}

bool comparePriority(Process p1, Process p2) {
    return p1.priority < p2.priority;
}

int main()
{
    int numProcesses;

    cout << "Enter the number of processes: ";
    cin >> numProcesses;

    vector<Process> processes(numProcesses);

    for (int i = 0; i < numProcesses; i++) {
        cout << "Enter the arrival time, burst time, and priority for process " << i + 1 << ": ";
        cin >> processes[i].arrivalTime >> processes[i].burstTime >> processes[i].priority;
        processes[i].id = i + 1;
    }

    sort(processes.begin(), processes.end(), compareArrivalTime);

    int currentTime = 0, completedProcesses = 0;
    while (completedProcesses < numProcesses) {
        vector<Process> readyQueue;
        for (int i = 0; i < numProcesses; i++) {
            if (processes[i].arrivalTime <= currentTime && processes[i].burstTime > 0) {
                readyQueue.push_back(processes[i]);
            }
        }
        if (readyQueue.empty()) {
            currentTime++;
            continue;
        }
        sort(readyQueue.begin(), readyQueue.end(), comparePriority);
        readyQueue[0].burstTime--;
        currentTime++;
        if (readyQueue[0].burstTime == 0) {
            completedProcesses++;
            readyQueue[0].completionTime = currentTime;
            readyQueue[0].turnaroundTime = readyQueue[0].completionTime - readyQueue[0].arrivalTime;
            readyQueue[0].waitingTime = readyQueue[0].turnaroundTime - readyQueue[0].burstTime;
        }
    }

    cout << "Process\tArrival Time\tBurst Time\tPriority\tCompletion Time\tTurnaround Time\tWaiting Time\n";
    for (int i = 0; i < numProcesses; i++) {
        cout << processes[i].id << "\t\t" << processes[i].arrivalTime << "\t\t" << processes[i].burstTime << "\t\t"
             << processes[i].priority << "\t\t" << processes[i].completionTime << "\t\t" << processes[i].turnaroundTime << "\t\t" << processes[i].waitingTime << endl;
    }

    return 0;
}
