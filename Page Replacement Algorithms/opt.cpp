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

    vector<int> frame_table(num_frames, -1);
    vector<char> page_faults;
    int num_page_faults = 0;

    for (int i = 0; i < num_references; i++) {
        int current_reference = reference_string[i];
        bool page_found = false;

        for (int j = 0; j < num_frames; j++) {
            if (frame_table[j] == current_reference) {
                // Page hit
                page_found = true;
                page_faults.push_back('H');
                break;
            }
        }

        if (!page_found) {
            // Page fault
            num_page_faults++;
            page_faults.push_back('F');

            if (frame_table.size() < num_frames) {
                // Add page to empty frame
                frame_table.insert(frame_table.begin(), current_reference);
            } else {
                // Find page to replace
                int page_to_replace = -1;
                int max_distance = -1;
                for (int j = 0; j < num_frames; j++) {
                    int distance = 0;
                    for (int k = i + 1; k < num_references; k++) {
                        if (frame_table[j] == reference_string[k]) {
                            break;
                        }
                        distance++;
                    }
                    if (distance > max_distance) {
                        max_distance = distance;
                        page_to_replace = j;
                    }
                }

                // Replace page in frame table
                frame_table[page_to_replace] = current_reference;
            }
        }

        // Print current frame table
        cout << "Frame table: ";
        for (int j = 0; j < num_frames; j++) {
            if (frame_table[j] == -1) {
                cout << "- ";
            } else {
                cout << frame_table[j] << " ";
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
