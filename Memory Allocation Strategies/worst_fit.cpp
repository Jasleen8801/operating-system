#include <iostream>
#include <vector>

using namespace std;

struct memoryBlock {
    int size;
    bool isAllocated;
    int allocatedProcessId;
};

struct Process {
    int id;
    int size;
};

int main() {
    int numBlocks, numProcesses;

    cout << "Enter number of memory blocks: ";
    cin >> numBlocks;

    vector<memoryBlock> blocks(numBlocks);

    cout << "Enter size of each memory block: ";
    for (int i = 0; i < numBlocks; i++) {
        cin >> blocks[i].size;
        blocks[i].isAllocated = false;
        blocks[i].allocatedProcessId = -1;
    }

    cout << "Enter number of processes: ";
    cin >> numProcesses;

    vector<Process> processes(numProcesses);

    for(int i = 0; i < numProcesses; i++) {
        cout << "Enter size of process " << i + 1 << ": ";
        cin >> processes[i].size;
        processes[i].id = i + 1;
    }

    for (int i = 0; i < numProcesses; i++) {
        int worstBlockIndex = -1;
        for (int j = 0; j < numBlocks; j++) {
            if (blocks[j].isAllocated == false && blocks[j].size >= processes[i].size) {
                if (worstBlockIndex == -1) {
                    worstBlockIndex = j;
                } else if (blocks[j].size > blocks[worstBlockIndex].size) {
                    worstBlockIndex = j;
                }
            }
        }
        if (worstBlockIndex != -1) {
            blocks[worstBlockIndex].isAllocated = true;
            blocks[worstBlockIndex].allocatedProcessId = processes[i].id;
        }
    }

    cout << "Block\tSize\tAllocated Process\n";
    for (int i = 0; i < numBlocks; i++) {
        cout << i + 1 << "\t" << blocks[i].size << "\t";
        if (blocks[i].isAllocated) {
            cout << blocks[i].allocatedProcessId;
        } else {
            cout << "Not Allocated";
        }
        cout << endl;
    }
}
