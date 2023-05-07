/****************************************************
    ROUND ROBIN CPU SCHEDULING ALGORITHM
*****************************************************

Made by: 	 Jasleen Kaur
Roll NO.:    102118064
Group:       BS-3
Course No:   UCT401
Course Name: Operating Systems
Thapar Institute of Engineering and Technology, Patiala

****************************************************/

/* ROUND ROBIN CPU SCHEDULING

It is a preemptive scheduling algorithm in which each process is given a time slice called a quantum
to execute before it is interrupted and next process is selected.

The algorithm works by maintaining a queue of ready processes and scheduling each process for a
quantum. If the process completes before the quantum, it is removed from the queue. If the process
does not complete before the quantum, it is moved to the end of the queue.

****************************************************/

// C++ code for Round Robin CPU Scheduling

#include <iostream>
#include <queue>
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
    int completionTime;
    int responseTime;
};

// comparison function to sort the processes based on their arrival time
bool compareAT(Process p1, Process p2)
{
    return p1.arrivalTime < p2.arrivalTime;
}

// comparison function to sort the processes based on their pid
bool comparePID(Process p1, Process p2)
{
    return p1.pid < p2.pid;
}

int main()
{
    int n, tq;
    struct Process p[100];
    float avgTAT, avgRT, avgWT;
    int totalTAT = 0, totalRT = 0, totalWT = 0;
    int burstRemaining[100];

    // Reading the number of processes and time quantum
    cout << "Enter the number of processes: ";
    cin >> n;
    cout << "Enter the time quantum: ";
    cin >> tq;

    // Reading the arrival time and burst time of each process
    for (int i = 0; i < n; i++)
    {
        cout << "Enter the arrival time of process " << i + 1 << ": ";
        cin >> p[i].arrivalTime;
        cout << "Enter the burst time of process " << i + 1 << ": ";
        cin >> p[i].burstTime;
        burstRemaining[i] = p[i].burstTime;
        p[i].pid = i + 1;
        p[i].waitingTime = 0;
        p[i].turnAroundTime = 0;
        p[i].startTime = 0;
        p[i].completionTime = 0;
        p[i].responseTime = 0;
    }

    // sorting the processes based on their arrival time
    sort(p, p + n, compareAT);

    queue<int> q;        // initializing an empty queue to store the process IDs
    int currentTime = 0; // initializing the current time to 0
    q.push(0);           // pushing the first process into the queue
    int completed = 0;   // initialize a counter to keep track of completed processes
    int mark[100] = {0}; // initialize an array to keep track of processes that have been added to the queue
    mark[0] = 1;         // mark the first process as added to the queue

    // printing the gantt chart header
    cout << endl
         << "Gantt Chart" << endl
         << "+";
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < p[i].burstTime; j++)
        {
            cout << "-";
        }
        cout << "+";
    }
    cout << endl
         << "|";

    // loop until all processes are completed
    while (completed != n)
    {
        int idx = q.front();
        q.pop();

        // if the process is starting for the first time
        if (burstRemaining[idx] == p[idx].burstTime)
        {
            p[idx].startTime = max(currentTime, p[idx].arrivalTime);
            currentTime = p[idx].startTime;
        }

        // if the process has burst time remaining after one iteration
        if (burstRemaining[idx] - tq > 0)
        {
            burstRemaining[idx] -= tq;
            currentTime += tq;
        }

        // if the process completes within one iteration
        else
        {
            currentTime += burstRemaining[idx];
            burstRemaining[idx] = 0;
            completed++;

            // calculating the completion time, turn around time and waiting time
            p[idx].completionTime = currentTime;
            p[idx].turnAroundTime = p[idx].completionTime - p[idx].arrivalTime;
            p[idx].waitingTime = p[idx].turnAroundTime - p[idx].burstTime;
            p[idx].responseTime = p[idx].startTime - p[idx].arrivalTime;

            // calculating the total turn around time, waiting time and response time
            totalTAT += p[idx].turnAroundTime;
            totalWT += p[idx].waitingTime;
            totalRT += p[idx].responseTime;

            // printing the gantt chart
            cout << " -- "
                 << "P" << p[idx].pid << " -- ";
        }

        // Add newly arrived processes to the queue
        for (int i = 0; i < n; i++)
        {
            if (burstRemaining[i] > 0 && p[i].arrivalTime <= currentTime && mark[i] == 0)
            {
                q.push(i);
                mark[i] = 1;
            }
        }

        // if the current process still has burst time remaining, add it to the queue
        if (burstRemaining[idx] > 0)
        {
            q.push(idx);
        }

        // if the queue is empty, add the next process to the queue
        if (q.empty())
        {
            for (int i = 0; i < n; i++)
            {
                if (burstRemaining[i] > 0)
                {
                    q.push(i);
                    mark[i] = 1;
                    break;
                }
            }
        }
    }

    // calculating the average turn around time, waiting time and response time
    avgTAT = (float)totalTAT / (float)n;
    avgWT = (float)totalWT / (float)n;
    avgRT = (float)totalRT / (float)n;

    // sorting the processes based on their pid
    sort(p, p + n, comparePID);

    // Printing the table
    cout << endl;
    cout << "#P\t"
         << "AT\t"
         << "BT\t"
         << "ST\t"
         << "CT\t"
         << "TAT\t"
         << "WT\t"
         << "RT\t"
         << "\n"
         << endl;

    for (int i = 0; i < n; i++)
    {
        cout << p[i].pid << "\t" << p[i].arrivalTime << "\t" << p[i].burstTime << "\t" << p[i].startTime << "\t" << p[i].completionTime << "\t" << p[i].turnAroundTime << "\t" << p[i].waitingTime << "\t" << p[i].responseTime << "\t" << endl;
    }
    
    // Printing the average turn around time, waiting time and response time
    cout << endl;
    cout << "Average Turn Around Time: " << avgTAT << endl;
    cout << "Average Waiting Time: " << avgWT << endl;
    cout << "Average Response Time: " << avgRT << endl;
}

/*******************************************************
 * WITH SAME ARRIVAL TIME                             *

INPUT:
Enter the number of processes: 4
Enter the time quantum: 3
Enter the arrival time of process 1: 0
Enter the burst time of process 1: 4
Enter the arrival time of process 2: 0
Enter the burst time of process 2: 3
Enter the arrival time of process 3: 0
Enter the burst time of process 3: 2
Enter the arrival time of process 4: 0
Enter the burst time of process 4: 1

OUTPUT:

Gantt Chart
+----+---+--+-+
| -- P2 --  -- P3 --  -- P4 --  -- P1 --
#P      AT      BT      ST      CT      TAT     WT      RT   

1       0       4       0       10      10      6       0    
2       0       3       3       6       6       3       3    
3       0       2       6       8       8       6       6    
4       0       1       8       9       9       8       8

Average Turn Around Time: 8.25
Average Waiting Time: 5.75
Average Response Time: 4.25

 * WITH DIFFERENT ARRIVAL TIME                       *

INPUT:
Enter the number of processes: 5
Enter the time quantum: 2
Enter the arrival time of process 1: 0
Enter the burst time of process 1: 5
Enter the arrival time of process 2: 1
Enter the burst time of process 2: 4
Enter the arrival time of process 3: 2
Enter the burst time of process 3: 3
Enter the arrival time of process 4: 3
Enter the burst time of process 4: 2
Enter the arrival time of process 5: 4
Enter the burst time of process 5: 1

OUTPUT:

Gantt Chart
+-----+----+---+--+-+
| -- P4 --  -- P5 --  -- P2 --  -- P3 --  -- P1 --
#P      AT      BT      ST      CT      TAT     WT      RT   

1       0       5       0       15      15      10      0    
2       1       4       2       13      12      8       1    
3       2       3       4       14      12      9       2    
4       3       2       8       10      7       5       5    
5       4       1       10      11      7       6       6    

Average Turn Around Time: 10.6
Average Waiting Time: 7.6
Average Response Time: 2.8

*******************************************************/
