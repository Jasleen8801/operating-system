#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct process
{
    int pid;
    int memory;
};

int main()
{
    int currentNoOfProcesses;

    cout << "Enter the number of processes currently in RAM: ";
    cin >> currentNoOfProcesses;

    vector<process> processes(currentNoOfProcesses);

    for (int i = 0; i < currentNoOfProcesses; i++)
    {
        cout << "Enter the process id: ";
        cin >> processes[i].pid;
        cout << "Enter the memory required: ";
        cin >> processes[i].memory;
        cout << endl;
    }
    cout << endl;

    int noOfProcessesToBeTerminated;
    cout << "Enter the number of processes to be terminated: ";
    cin >> noOfProcessesToBeTerminated;

    vector<int> processesToBeTerminated(noOfProcessesToBeTerminated);

    for (int i = 0; i < noOfProcessesToBeTerminated; i++)
    {
        cout << "Enter the process id of the process to be terminated: ";
        cin >> processesToBeTerminated[i];
    }
    cout << endl;

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

    cout << "The terminated processes list is: " << endl;
    for (int i = 0; i < noOfProcessesToBeTerminated; i++)
    {
        cout << "Process id: " << selectedProcesses[i].pid << endl;
        cout << "Memory: " << selectedProcesses[i].memory << endl;
        cout << endl;
    }

    vector<int> freeList(noOfProcessesToBeTerminated);
    vector<int> wastage(noOfProcessesToBeTerminated);

    for (int i = 0; i < noOfProcessesToBeTerminated; i++)
    {
        freeList[i] = selectedProcesses[i].memory;
    }

    int requirement, n = noOfProcessesToBeTerminated;
    char continueOption;

    do
    {
        cout << "Enter the requirement: ";
        cin >> requirement;

        if (requirement == 0)
        {
            cout << "Requirement is zero so no process is allocated in the memory" << endl;
            cout << "Do you want to continue? (Y/N): ";
            cin >> continueOption;
            continue;
        }

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

        // The code for First fit
        cout << "First fit" << endl;
        for (int i = 0; i < n; i++)
        {
            if (freeList[i] >= requirement)
            {
                cout << "Process " << freeList[i] << " is allocated to the user" << endl;
                break;
            }
        }

        // The code for Best fit
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

        // The code for Worst fit
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

        cout << "Do you want to continue? (Y/N): ";
        cin >> continueOption;

    } while (continueOption == 'Y' || continueOption == 'y');

    return 0;
}
