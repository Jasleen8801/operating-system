#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

struct Process {
    int id;
    int arrivalTime;
    int burstTime;
    int remainingTime;
    int completionTime;
    int waitingTime;
    int turnaroundTime;
};

int main() {
    int numProcesses, quantum;

    cout << "Enter number of processes: ";
    cin >> numProcesses;

    cout << "Enter quantum: ";
    cin >> quantum;

    vector<Process> processes(numProcesses);

    for (int i = 0; i < numProcesses; i++) {
        cout << "Enter arrival time of process " << i + 1 << ": ";
        cin >> processes[i].arrivalTime;
        cout << "Enter burst time of process " << i + 1 << ": ";
        cin >> processes[i].burstTime;
        processes[i].id = i + 1;
        processes[i].remainingTime = processes[i].burstTime;
    }

    queue<Process> readyQueue;
    int currentTime = 0, completedProcesses = 0;

    while(completedProcesses < numProcesses) {
        for(int i = 0; i < numProcesses; i++) {
            if(processes[i].arrivalTime <= currentTime && processes[i].remainingTime > 0) {
                readyQueue.push(processes[i]);
            }
        }
        if(readyQueue.empty()) {
            currentTime++;
            continue;
        }
        Process currentProcess = readyQueue.front();
        readyQueue.pop();
        int timeSlice = min(quantum, currentProcess.remainingTime);
        currentProcess.remainingTime -= timeSlice;
        currentTime += timeSlice;
        if(currentProcess.remainingTime == 0) {
            currentProcess.completionTime = currentTime;
            currentProcess.turnaroundTime = currentProcess.completionTime - currentProcess.arrivalTime;
            currentProcess.waitingTime = currentProcess.turnaroundTime - currentProcess.burstTime;
            completedProcesses++;
        } else {
            readyQueue.push(currentProcess);
        }

        cout<<"Process\tArrival Time\tBurst Time\tCompletion Time\tTurnaround Time\tWaiting Time\n";
        for (int i = 0; i < numProcesses; i++) {
            cout << processes[i].id << "\t" << processes[i].arrivalTime << "\t\t" << processes[i].burstTime << "\t\t" << processes[i].completionTime << "\t\t" << processes[i].turnaroundTime << "\t\t" << processes[i].waitingTime << "\n";
        }

        return 0;
    }
}
