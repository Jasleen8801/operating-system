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
    vector<int> reference_bits(num_frames, 0);
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
                reference_bits.insert(reference_bits.begin(), 1);
            } else {
                // Find least recently used page
                int lru_page = -1;
                int min_reference_bit = 2;
                for (int j = 0; j < num_frames; j++) {
                    if (reference_bits[j] < min_reference_bit) {
                        min_reference_bit = reference_bits[j];
                        lru_page = j;
                    }
                }

                // Replace least recently used page in stack
                frame_stack[lru_page] = current_reference;
                reference_bits[lru_page] = 1;
            }
        } else {
            // Page hit
            page_faults.push_back('H');

            // Update reference bit for hit page
            int hit_page_index = find(frame_stack.begin(), frame_stack.end(), current_reference) - frame_stack.begin();
            reference_bits[hit_page_index] = 1;
        }

        // Shift reference bits to the right
        for (int j = 0; j < num_frames; j++) {
            reference_bits[j] >>= 1;
        }

        // Print current stack and reference bits
        cout << "Stack: ";
        for (int j = 0; j < num_frames; j++) {
            if (frame_stack[j] == -1) {
                cout << "- ";
            } else {
                cout << frame_stack[j] << " ";
            }
        }
        cout << endl;

        cout << "Reference bits: ";
        for (int j = 0; j < num_frames; j++) {
            cout << reference_bits[j] << " ";
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
