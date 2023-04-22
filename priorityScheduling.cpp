#include<bits/stdc++.h>
#include<vector>
#include<algorithm>
using namespace std;

struct Process {
    int pid;
    int arrivalTime;
    int burstTime;
    int priority;
    int remainingTime;
};

bool compare(Process a, Process b) {
    return a.arrivalTime < b.arrivalTime;
}

int main() {
    int n;
    cout << "Enter the number of processes: ";
    cin >> n;
    vector<Process> processes(n);

    for(int i = 0; i < n; i++) {
        cout << "Enter the arrival time, burst time and priority of process " << i + 1 << ": ";
        cin >> processes[i].arrivalTime >> processes[i].burstTime >> processes[i].priority;
        processes[i].pid = i + 1;
        processes[i].remainingTime = processes[i].burstTime;
    }
    
    sort(processes.begin(), processes.end(), compare);

    vector<Process> readyQueue;

    int time = 0;

    Process currentProcess = processes[0];

    while(!processes.empty()) {
        for(auto it = processes.begin(); it != processes.end(); it++) {
            if(it->arrivalTime <= time) {
                readyQueue.push_back(*it);
                processes.erase(it);
            }
            else {
                ++it;
            }
        }

        sort(readyQueue.begin(), readyQueue.end(), compare);

        if(currentProcess.remainingTime == 0) {
            cout << "Process " << currentProcess.pid << " completed at time " << time << endl;
            if(!readyQueue.empty()) {
                currentProcess = readyQueue[0];
                readyQueue.erase(readyQueue.begin());
            }
        }

        if(!readyQueue.empty() && readyQueue[0].priority < currentProcess.priority) {
            cout<<"Process "<<currentProcess.pid<<" preempted at time "<<time<<endl;
            readyQueue.push_back(currentProcess);
            sort(readyQueue.begin(), readyQueue.end(), compare);
            currentProcess = readyQueue[0];
            readyQueue.erase(readyQueue.begin());
        }

        currentProcess.remainingTime--;

        time++;
    }

    for(auto p : processes) {
        int turnAroundTime = time - p.arrivalTime;
        int waitingTime = turnAroundTime - p.burstTime;
    }
}
