/****************************************************
    MEMORY MANAGEMENT
*****************************************************

Made by: 	 Jasleen Kaur
Roll NO.:    102118064
Group:       BS-3
Course No:   UCT401
Course Name: Operating Systems
Thapar Institute of Engineering and Technology, Patiala

****************************************************/

/* FREE LIST ALGORITHM

Free list algorithm is a memory management algorithm that is used to allocate the memory to the processes. It is a non-contiguous memory allocation algorithm.

The free list algorithm is used to allocate the memory to the processes in the following ways:
1. First fit
2. Best fit
3. Worst fit

****************************************************/

// C++ code for Free list algorithm implementation

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Define a struct to represent a process with a process ID and memory requirement
struct process
{
    int pid;
    int memory;
};

int main()
{
    // Get the number of processes currently in RAM from the user
    int currentNoOfProcesses;
    cout << "Enter the number of processes currently in RAM: ";
    cin >> currentNoOfProcesses;

    // Create a vector of processes with the given number of processes
    vector<process> processes(currentNoOfProcesses);

    // Get the process ID and memory requirement of each process from the user
    for (int i = 0; i < currentNoOfProcesses; i++)
    {
        cout << "Enter the process id: ";
        cin >> processes[i].pid;
        cout << "Enter the memory required: ";
        cin >> processes[i].memory;
        cout << endl;
    }
    cout << endl;

    // Get the number of processes to be terminated from the user
    int noOfProcessesToBeTerminated;
    cout << "Enter the number of processes to be terminated: ";
    cin >> noOfProcessesToBeTerminated;

    // Create a vector of process IDs for the processes to be terminated
    vector<int> processesToBeTerminated(noOfProcessesToBeTerminated);

    // Get the process ID of each process to be terminated from the user
    for (int i = 0; i < noOfProcessesToBeTerminated; i++)
    {
        cout << "Enter the process id of the process to be terminated: ";
        cin >> processesToBeTerminated[i];
    }
    cout << endl;

    // Select the processes to be terminated based on their process IDs
    vector<process> selectedProcesses;
    for (int i = 0; i < noOfProcessesToBeTerminated; i++)
    {
        for (int j = 0; j < currentNoOfProcesses; j++)
        {
            if (processesToBeTerminated[i] == processes[j].pid)
            {
                selectedProcesses.push_back(processes[j]);
            }
        }
    }

    // Display the list of terminated processes
    cout << "The terminated processes list is: " << endl;
    for (int i = 0; i < noOfProcessesToBeTerminated; i++)
    {
        cout << "Process id: " << selectedProcesses[i].pid << endl;
        cout << "Memory: " << selectedProcesses[i].memory << endl;
        cout << endl;
    }

    // Create vectors to store the free memory list and the wastage for each process
    vector<int> freeList(noOfProcessesToBeTerminated);
    vector<int> wastage(noOfProcessesToBeTerminated);

    // Initialize the free memory list with the memory requirements of the terminated processes
    for (int i = 0; i < noOfProcessesToBeTerminated; i++)
    {
        freeList[i] = selectedProcesses[i].memory;
    }

    // Enter a loop to allocate memory to new processes
    int requirement, n = noOfProcessesToBeTerminated;
    char continueOption;
    do
    {
        // Get the memory requirement for the new process from the user
        cout << "Enter the requirement: ";
        cin >> requirement;

        // If the requirement is zero, skip the allocation process and ask the user if they want to continue
        if (requirement == 0)
        {
            cout << "Requirement is zero so no process is allocated in the memory" << endl;
            cout << "Do you want to continue? (Y/N): ";
            cin >> continueOption;
            continue;
        }

        // Check if the requirement is greater than the available memory and ask the user if they want to continue
        bool processAllocated = false;
        for (int i = 0; i < n; i++)
        {
            if (freeList[i] >= requirement)
            {
                processAllocated = true;
                wastage[i] = freeList[i] - requirement;
            }
            else
            {
                wastage[i] = -1;
            }
        }
        if (!processAllocated)
        {
            cout << "Requirement is greater than the size available in the memory" << endl;
            cout << "Do you want to continue? (Y/N): ";
            cin >> continueOption;
            continue;
        }

        // Allocate memory to the new process using the First fit algorithm
        cout << "First fit" << endl;
        for (int i = 0; i < n; i++)
        {
            if (freeList[i] >= requirement)
            {
                cout << "Process " << freeList[i] << " is allocated to the user" << endl;
                break;
            }
        }

        // Allocate memory to the new process using the Best fit algorithm
        cout << "Best fit" << endl;
        int index = -1;
        int wastage1 = INT_MAX;
        for (int i = 0; i < n; i++)
        {
            if (wastage[i] >= 0 && wastage[i] < wastage1)
            {
                wastage1 = wastage[i];
                index = i;
            }
        }
        if (index >= 0)
        {
            cout << "Process " << freeList[index] << " is allocated to the user" << endl;
        }

        // Allocate memory to the new process using the Worst fit algorithm
        cout << "Worst fit" << endl;
        int wastage2 = -1;
        index = -1;
        for (int i = 0; i < n; i++)
        {
            if (wastage[i] > wastage2)
            {
                wastage2 = wastage[i];
                index = i;
            }
        }
        if (index >= 0)
        {
            cout << "Process " << freeList[index] << " is allocated to the user" << endl;
        }

        // Ask the user if they want to continue
        cout << "Do you want to continue? (Y/N): ";
        cin >> continueOption;

    } while (continueOption == 'Y' || continueOption == 'y');

    return 0;
}

/****************************************************

OUTPUT:
Enter the number of processes currently in RAM: 3
Enter the process id: 1
Enter the memory required: 100

Enter the process id: 2
Enter the memory required: 200

Enter the process id: 3
Enter the memory required: 300


Enter the number of processes to be terminated: 2
Enter the process id of the process to be terminated: 1
Enter the process id of the process to be terminated: 3

The terminated processes list is:
Process id: 1
Memory: 100

Process id: 3
Memory: 300

Enter the requirement: 50
First fit
Process 100 is allocated to the user
Best fit
Process 100 is allocated to the user
Worst fit
Process 300 is allocated to the user

Do you want to continue? (Y/N): y

Enter the requirement: 0
Requirement is zero so no process is allocated in the memory

Do you want to continue? (Y/N): y

Enter the requirement: 400
Requirement is greater than the size available in the memory

Do you want to continue? (Y/N): n
 
****************************************************/
