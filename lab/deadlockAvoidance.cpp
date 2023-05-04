// Deadlock Avoidance Algorithm to find Safe Sequence in C++ is used to check if a system is in deadlock state or not.

#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n;

    // taking input from the user
    do {
        cout << "Enter the no of processes: ";
        cin >> n;
    } while (n <= 0);

    // creating the allocation, max, need, available and finish matrix
    vector<vector<int>> allocation(n, vector<int>(3));
    vector<vector<int>> max(n, vector<int>(3));
    vector<vector<int>> need(n, vector<int>(3));
    vector<int> available(3);
    vector<bool> finish(n, false);

    cout << "Enter the allocation matrix: " << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 3; j++) {
            cin >> allocation[i][j];
        }
    }

    cout << "Enter the max matrix: " << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 3; j++) {
            cin >> max[i][j];
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }

    cout << "Enter the available matrix: " << endl;
    for (int i = 0; i < 3; i++) {
        cin >> available[i];
    }

    // Banker's Algorithm
    vector<int> work = available;
    vector<int> safeSequence;
    int count = 0;

    while (count < n) {
        bool found = false;
        for (int i = 0; i < n; i++) {
            if (!finish[i]) {
                bool canExecute = true;
                for (int j = 0; j < 3; j++) {
                    if (need[i][j] > work[j]) {
                        // if the process cannot be executed, break the loop
                        canExecute = false;
                        break;
                    }
                }
                if (canExecute) {
                    // if the process can be executed, add the allocated resources to the work vector and mark the process as finished
                    for (int j = 0; j < 3; j++) {
                        work[j] += allocation[i][j];
                    }
                    finish[i] = true;
                    found = true;
                    safeSequence.push_back(i);
                    count++;
                }
            }
        }
        if (!found) {
            // if no process is finished in the current iteration, deadlock is detected
            cout << "Deadlock detected" << endl;
            return 0;
        }
    }
    if (count < n) {
        // if all the processes are not finished, deadlock is detected
        cout << "Deadlock detected" << endl;
        return 0;
    }
    else {
        // if all the processes are finished, deadlock is not detected
        // print the safe sequence
        cout << "No deadlock detected" << endl;
        cout << "Safe Sequence: ";
        for (int i = 0; i < n; i++) {
            cout << safeSequence[i] << " ";
        }
        cout << endl;
    }
    return 0;
}

// ********************************************

// INPUT
// Enter the no of processes: 5
// Enter the allocation matrix:
// 0 1 0
// 2 0 0
// 3 0 2
// 2 1 1
// 0 0 2
// Enter the max matrix:
// 7 5 3
// 3 2 2
// 9 0 2
// 2 2 2
// 4 3 3
// Enter the available matrix:
// 3 3 2

// OUTPUT
// No deadlock detected
// Safe Sequence: 1 3 4 0 2
