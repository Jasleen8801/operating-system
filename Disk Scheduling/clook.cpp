#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int main() {
    vector<int> requests;
    int num_requests, total_head_movement = 0, initial_head_pos, disk_size;
    string direction;

    cout << "Enter the number of requests: ";
    cin >> num_requests;

    cout << "Enter the request sequence: ";
    for (int i = 0; i < num_requests; i++) {
        int request;
        cin >> request;
        requests.push_back(request);
    }

    cout << "Enter the initial head position: ";
    cin >> initial_head_pos;

    cout << "Enter the direction (left or right): ";
    cin >> direction;

    cout << "Enter the disk size: ";
    cin >> disk_size;

    sort(requests.begin(), requests.end());

    int left = 0, right = num_requests - 1;
    while(left <= right) {
        if(direction == "left") {
            if(requests[left] < initial_head_pos) {
                total_head_movement += initial_head_pos - requests[left];
                initial_head_pos = requests[left];
            }
            left++;
        }
        else if(direction == "right") {
            if(requests[right] > initial_head_pos) {
                total_head_movement += requests[right] - initial_head_pos;
                initial_head_pos = requests[right];
            }
            right--;
        }
    }

    if(direction == "left") {
        total_head_movement += requests[left - 1];
        for(int i = left - 2; i >= 0; i--) {
            total_head_movement += requests[i + 1] - requests[i];
        }
    } 
    else if(direction == "right") {
        total_head_movement += disk_size - 1 - requests[right + 1];
        for(int i = right + 1; i < num_requests; i++) {
            total_head_movement += requests[i] - requests[i - 1];
        }
    }

    cout << "Total head movement: " << total_head_movement << endl;
    return 0;
}
