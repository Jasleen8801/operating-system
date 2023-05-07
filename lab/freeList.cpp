
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    int n;

    // Taking the input from the user
    cout << "Enter the number of processes in free list: ";
    cin >> n;


    vector<int> freeList(n);
    vector<int> wastage(n);
    
    for (int i = 0; i < n; i++)
    {
        cout << "Enter the process id: ";
        cin >> freeList[i];
    }

    int requirement;
    char continueOption;

    do
    {
        cout << "Enter the requirement: ";
        cin >> requirement;

        if (requirement == 0)
        {
            // If the requirement is zero then no process is allocated in the memory
            cout << "Requirement is zero so no process is allocated in the memory" << endl;
            cout << "Do you want to continue? (Y/N): ";
            cin >> continueOption;
            continue;
        }

        bool processAllocated = false; // To check if the process is allocated or not

        for (int i = 0; i < n; i++)
        {
            if (freeList[i] >= requirement)
            // If the process is allocated then the wastage is calculated
            {
                processAllocated = true;
                wastage[i] = freeList[i] - requirement;
            }
            else
            // If the process is not allocated then the wastage is set to -1
            {
                wastage[i] = -1;
            }
        }

        if (!processAllocated)
        {
            // If the process is not allocated then the requirement is greater than the size available in the memory
            cout << "Requirement is greater than the size available in the memory" << endl;
            cout << "Do you want to continue? (Y/N): ";
            cin >> continueOption;
            continue;
        }

        // The code for First fit - The first process that is allocated is the first fit
        cout << "First fit" << endl;
        for (int i = 0; i < n; i++)
        {
            if (freeList[i] >= requirement)
            {
                cout << "Process " << freeList[i] << " is allocated to the user" << endl;
                break;
            }
        }

        // The code for Best fit - The process that is allocated with the least wastage is the best fit
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

        // The code for Worst fit - The process that is allocated with the most wastage is the worst fit
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
        // If the index is greater than or equal to zero then the process is allocated
        {
            cout << "Process " << freeList[index] << " is allocated to the user" << endl;
        }

        // Asking the user if he wants to continue or not
        cout << "Do you want to continue? (Y/N): ";
        cin >> continueOption;

    } while (continueOption == 'Y' || continueOption == 'y');

    return 0;
}
