#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>

using namespace std;

int main() {
    vector<int> requests;
    int num_requests, total_head_movement = 0, initial_head_pos, current_head_pos;

    cout << "Enter the number of requests: ";
    cin >> num_requests;

    cout << "Enter the request sequence: ";
    for (int i = 0; i < num_requests; i++) {
        int request;
        cin >> request;
        requests.push_back(request);
    }

    cout << "Enter initial head position: ";
    cin >> initial_head_pos;

    current_head_pos = initial_head_pos;
    while(!requests.empty()) {
        int min_distance = abs(requests[0] - current_head_pos);
        int min_index = 0;
        for(int i = 1; i < requests.size(); i++) {
            int distance = abs(requests[i] - current_head_pos);
            if(distance < min_distance) {
                min_distance = distance;
                min_index = i;
            }
        }
        total_head_movement += min_distance;
        current_head_pos = requests[min_index];
        requests.erase(requests.begin() + min_index);
    }

    cout << "Total head movement: " << total_head_movement << endl;
    return 0;
}
