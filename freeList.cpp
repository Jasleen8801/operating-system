#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
    int n;
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
