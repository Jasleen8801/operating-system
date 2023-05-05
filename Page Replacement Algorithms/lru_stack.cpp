#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int num_frames, num_references;
    vector<int> reference_string;

    cout << "Enter the number of frames: ";
    cin >> num_frames;

    cout << "Enter the number of references: ";
    cin >> num_references;

    cout << "Enter the reference string: ";
    for (int i = 0; i < num_references; i++) {
        int reference;
        cin >> reference;
        reference_string.push_back(reference);
    }

    vector<int> frame_stack(num_frames, -1);
    vector<char> page_faults;
    int num_page_faults = 0;

    for (int i = 0; i < num_references; i++) {
        int current_reference = reference_string[i];

        if (find(frame_stack.begin(), frame_stack.end(), current_reference) == frame_stack.end()) {
            // Page fault
            num_page_faults++;
            page_faults.push_back('F');

            if (frame_stack.size() < num_frames) {
                // Add page to stack
                frame_stack.insert(frame_stack.begin(), current_reference);
            } else {
                // Find least recently used page
                int lru_page = -1;
                int farthest_reference = -1;
                for (int j = 0; j < num_frames; j++) {
                    int reference = frame_stack[j];
                    bool found = false;
                    for (int k = i - 1; k >= 0; k--) {
                        if (reference == reference_string[k]) {
                            found = true;
                            if (k > farthest_reference) {
                                farthest_reference = k;
                                lru_page = j;
                            }
                            break;
                        }
                    }
                    if (!found) {
                        lru_page = j;
                        break;
                    }
                }

                // Replace least recently used page in stack
                frame_stack[lru_page] = current_reference;
            }
        } else {
            // Page hit
            page_faults.push_back('H');

            // Update stack to reflect page hit
            frame_stack.erase(find(frame_stack.begin(), frame_stack.end(), current_reference));
            frame_stack.insert(frame_stack.begin(), current_reference);
        }

        // Print current stack
        cout << "Stack: ";
        for (int j = 0; j < num_frames; j++) {
            if (frame_stack[j] == -1) {
                cout << "- ";
            } else {
                cout << frame_stack[j] << " ";
            }
        }
        cout << endl;
    }

    // Print results
    cout << "Number of page faults: " << num_page_faults << endl;
    cout << "Page fault and hit sequence: ";
    for (int i = 0; i < num_references; i++) {
        cout << page_faults[i] << " ";
    }
    cout << endl;

    return 0;
}
