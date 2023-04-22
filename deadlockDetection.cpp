// Deadlock detection algorithm in C++ is used to check if a system is in deadlock state or not.

#include <iostream>
#include <vector>

using namespace std;

// function to check if system is in deadlock state or not
bool isDeadlock(const vector<vector<int>>& allocation, const vector<vector<int>>& max, const vector<int>& available) {
    int n = allocation.size();
    int m = allocation[0].size();

    // create a vector to store the number of available resources for each type
    vector<int> work(m);
    for (int j = 0; j < m; j++) {
        int sum = 0;
        for (int i = 0; i < n; i++) {
            sum += allocation[i][j];
        }
        work[j] = available[j] - sum;
    }

    // create a vector to store the status of each process
    vector<bool> finish(n, false);

    // iterate through all the processes until all the processes are finished or deadlock is detected
    int count = 0;
    while (count < n) {
        bool found = false;
        for(int i = 0; i < n; i++) {
            if (!finish[i]) {
                int j;
                for (j = 0; j < m; j++) {
                    // check if all the resources can be allocated to the process
                    if (max[i][j] - allocation[i][j] > work[j]) {
                        break;
                    }
                }
                if (j == m) {
                    // if all the resources can be allocated to the process
                    for (int k = 0; k < m; k++) {
                        work[k] += allocation[i][k];
                    }
                    finish[i] = true;
                    found = true;
                    count++;
                }
            }
        }
        // if no process is finished in the current iteration, deadlock is detected
        if(!found) {
            return true;
        }
    }
    // if all the processes are finished, deadlock is not detected
    return false;
}

int main() {
    int n, m;

    // taking input from the user
    cout << "Enter the no of processes: ";
    cin >> n;
    cout << "Enter the no of resources: ";
    cin >> m;

    // creating the allocation, max and available matrices
    vector<vector<int>> allocation(n, vector<int>(m));
    vector<vector<int>> max(n, vector<int>(m));
    vector<int> available(m);

    cout << "Enter the allocation matrix: " << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> allocation[i][j];
        }
    }

    cout << "Enter the max matrix: " << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> max[i][j];
        }
    }

    cout << "Enter the available vector: " << endl;
    for (int i = 0; i < m; i++) {
        cin >> available[i];
    }

    // check if deadlock is detected or not
    if (isDeadlock(allocation, max, available)) {
        cout << "Deadlock detected" << endl;
    } else {
        cout << "No deadlock" << endl;
    }

    return 0;

}

// ****************************************************

// INPUT
// Enter the no of processes: 3
// Enter the no of resources: 3
// Enter the allocation matrix:
// 0 1 0
// 2 0 0
// 3 0 2
// Enter the max matrix:
// 7 5 3
// 3 2 2
// 9 0 2
// Enter the available vector:
// 3 3 2    

// OUTPUT
// Deadlock detected

// ****************************************************
