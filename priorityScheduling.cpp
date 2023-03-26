#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;

struct Process
{
    int pid;
    int arrivalTime;
    int burstTime;
    int waitingTime = 0;
    int turnAroundTime = 0;
    int startTime = -1;
    int priority;
    int finishTime = -1;
};

void priorityScheduling(vector<Process> &processes)
{
    // Sort the processes based on their arrival time and priority number
    sort(processes.begin(), processes.end(), [](Process p1, Process p2)
         {
        if (p1.arrivalTime == p2.arrivalTime) {
            return p1.priority < p2.priority;
        }
        return p1.arrivalTime < p2.arrivalTime; });

    // Create a priority queue to store the processes
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    int currentTime = 0;

    // Execute the processes in the priority queue
    while (!processes.empty() || !processes.empty())
    {
        // Add the processes that have arrived and not yet executed to the priority queue
        Process p = processes.front();
        pq.push({p.priority, p.pid});
        processes.erase(processes.begin());

        // If no processes have arrived yet, advance time to the arrival time of the next process
        if (pq.empty())
        {
            currentTime = processes.front().arrivalTime;
        }

        // Execute the processes in the priority queue
        int pid = pq.top().second;
        pq.pop();

        Process &p = processes[pid - 1];
        p.waitingTime = currentTime - p.startTime;

        // Update the start time and finish time of the process if it is the first time it is being executed
        if (p.startTime == -1)
        {
            p.startTime = currentTime;
        }
        currentTime += p.burstTime;
        p.finishTime = currentTime;
        p.turnAroundTime = p.finishTime - p.arrivalTime;
    }
}
