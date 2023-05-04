#include <iostream>
#include <vector>

using namespace std;

int main() {
    int numProcesses, numResources;

    cout << "Enter number of processes: ";
    cin >> numProcesses;

    cout << "Enter number of resources: ";
    cin >> numResources;

    vector<int> available(numResources);
    vector<vector<int>> max(numProcesses, vector<int>(numResources));
    vector<vector<int>> allocation(numProcesses, vector<int>(numResources));

    cout << "Enter available resources: ";
    for (int i = 0; i < numResources; i++) {
        cin >> available[i];
    }

    cout << "Enter maximum resources: ";
    for (int i = 0; i < numProcesses; i++) {
        for (int j = 0; j < numResources; j++) {
            cin >> max[i][j];
        }
    }

    cout << "Enter allocated resources: ";
    for (int i = 0; i < numProcesses; i++) {
        for (int j = 0; j < numResources; j++) {
            cin >> allocation[i][j];
        }
    }

    vector<int> work = available;
    vector<bool> finish(numProcesses, false);
    vector<int> safeSequence;

    while(safeSequence.size() < numProcesses) {
        bool found = false;
        for (int i = 0; i < numProcesses; i++) {
            if (!finish[i]) {
                bool canAllocate = true;
                for (int j = 0; j < numResources; j++) {
                    if (max[i][j] - allocation[i][j] > work[j]) {
                        canAllocate = false;
                        break;
                    }
                }

                if (canAllocate) {
                    for (int j = 0; j < numResources; j++) {
                        work[j] += allocation[i][j];
                    }
                    safeSequence.push_back(i);
                    finish[i] = true;
                    found = true;
                }
            }
        }

        if (!found) {
            cout << "System is not in safe state" << endl;
            break;
        }
    }

    if (safeSequence.size() == numProcesses) {
        cout << "System is in safe state" << endl;
        cout << "Safe sequence is: ";
        for (int i = 0; i < numProcesses; i++) {
            cout << safeSequence[i] << " ";
        }
        cout << endl;
    }

    return 0;
}
