#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

struct Process {
    int id;
    int arrivalTime;
    int burstTime;
    int completionTime;
    int waitingTime;
    int turnaroundTime;
};

bool compareArrivalTime(Process p1, Process p2) {
    return p1.arrivalTime < p2.arrivalTime;
}

bool compareBurstTime(Process p1, Process p2) {
    return p1.burstTime < p2.burstTime;
}

int main(){
    int numProcesses;

    cout << "Enter number of processes: ";
    cin >> numProcesses;

    vector<Process> processes(numProcesses);

    for (int i = 0; i < numProcesses; i++) {
        cout << "Enter arrival time of process " << i + 1 << ": ";
        cin >> processes[i].arrivalTime;
        cout << "Enter burst time of process " << i + 1 << ": ";
        cin >> processes[i].burstTime;
        processes[i].id = i + 1;
    }

    sort(processes.begin(), processes.end(), compareArrivalTime);

    int currentTime = 0;
    for(int i = 0; i < numProcesses; i++) {
        if(currentTime < processes[i].arrivalTime) {
            currentTime = processes[i].arrivalTime;
        }
        sort(processes.begin() + i, processes.end(), compareBurstTime);
        processes[i].completionTime = currentTime + processes[i].burstTime;
        processes[i].turnaroundTime = processes[i].completionTime - processes[i].arrivalTime;
        processes[i].waitingTime = processes[i].turnaroundTime - processes[i].burstTime;
        currentTime = processes[i].completionTime;
    }

    cout << "Process\tArrival Time\tBurst Time\tCompletion Time\tTurnaround Time\tWaiting Time\n";
    for (int i = 0; i < numProcesses; i++) {
        cout << processes[i].id << "\t" << processes[i].arrivalTime << "\t\t" << processes[i].burstTime << "\t\t" << processes[i].completionTime << "\t\t" << processes[i].turnaroundTime << "\t\t" << processes[i].waitingTime << "\n";
    }

    return 0;
}
