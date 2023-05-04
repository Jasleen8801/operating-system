#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Process {
    int id;
    int arrivalTime;
    int burstTime;
    int remainingTime;
    int completionTime;
    int turnaroundTime;
    int waitingTime;
};

bool compareArrivalTime(Process p1, Process p2) {
    return p1.arrivalTime < p2.arrivalTime;
}

bool compareRemainingTime(Process p1, Process p2) {
    return p1.remainingTime < p2.remainingTime;
}

int main()
{
    int numProcesses;

    cout << "Enter the number of processes: ";
    cin >> numProcesses;

    vector<Process> processes(numProcesses);

    for (int i = 0; i < numProcesses; i++) {
        cout << "Enter the arrival time and burst time for process " << i + 1 << ": ";
        cin >> processes[i].arrivalTime >> processes[i].burstTime;
        processes[i].id = i + 1;
        processes[i].remainingTime = processes[i].burstTime;
    }

    sort(processes.begin(), processes.end(), compareArrivalTime);

    int currentTime = 0, completedProcesses = 0;
    while (completedProcesses < numProcesses) {
        int shortestRemainingTime = INT_MAX, shortestRemainingTimeIndex = -1;
        for (int i = 0; i < numProcesses; i++) {
            if (processes[i].arrivalTime <= currentTime && processes[i].remainingTime > 0) {
                if (processes[i].remainingTime < shortestRemainingTime) {
                    shortestRemainingTime = processes[i].remainingTime;
                    shortestRemainingTimeIndex = i;
                }
            }
        }
        if (shortestRemainingTimeIndex == -1) {
            currentTime++;
            continue;
        }
        processes[shortestRemainingTimeIndex].remainingTime--;
        currentTime++;
        if (processes[shortestRemainingTimeIndex].remainingTime == 0) {
            completedProcesses++;
            processes[shortestRemainingTimeIndex].completionTime = currentTime;
            processes[shortestRemainingTimeIndex].turnaroundTime = processes[shortestRemainingTimeIndex].completionTime - processes[shortestRemainingTimeIndex].arrivalTime;
            processes[shortestRemainingTimeIndex].waitingTime = processes[shortestRemainingTimeIndex].turnaroundTime - processes[shortestRemainingTimeIndex].burstTime;
        }
    }

    cout << "Process\tArrival Time\tBurst Time\tCompletion Time\tTurnaround Time\tWaiting Time\n";
    for (int i = 0; i < numProcesses; i++) {
        cout << processes[i].id << "\t\t" << processes[i].arrivalTime << "\t\t" << processes[i].burstTime << "\t\t"
             << processes[i].completionTime << "\t\t" << processes[i].turnaroundTime << "\t\t" << processes[i].waitingTime << endl;
    }
    
    return 0;
}
