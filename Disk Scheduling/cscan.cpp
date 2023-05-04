#include <iostream>
#include <algorithm>
using namespace std;

int main() {
    int requests[100], num_requests, initial_head_pos, disk_size, total_head_movement = 0;
    string direction;

    cout << "Enter the number of requests: ";
    cin >> num_requests;

    cout << "Enter the request sequence: ";
    for (int i = 0; i < num_requests; i++) {
        cin >> requests[i];
    }

    cout << "Enter the initial head position: ";
    cin >> initial_head_pos;

    cout << "Enter the direction (left or right): ";
    cin >> direction;

    cout << "Enter the disk size: ";
    cin >> disk_size;

    sort(requests, requests + num_requests);

    int left = 0, right = num_requests - 1;
    while (left <= right) {
        if (direction == "left") {
            if (requests[left] < initial_head_pos) {
                total_head_movement += initial_head_pos - requests[left];
                initial_head_pos = requests[left];
            }
            left++;
        } else if (direction == "right") {
            if (requests[right] > initial_head_pos) {
                total_head_movement += requests[right] - initial_head_pos;
                initial_head_pos = requests[right];
            }
            right--;
        }
    }

    if (direction == "left") {
        total_head_movement += disk_size - 1 - initial_head_pos;
        total_head_movement += disk_size - 1 - requests[left - 1];
    } else if (direction == "right") {
        total_head_movement += initial_head_pos;
        total_head_movement += requests[right + 1];
    }

    cout << "Total head movement is " << total_head_movement << endl;

    return 0;
}
