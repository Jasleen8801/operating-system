#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

int main() {
    vector<int> requests;
    int num_requests, total_head_movement = 0, initial_head_pos, previous_head_pos;

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

    for(int i = 0; i < num_requests; i++) {
        total_head_movement += abs(requests[i] - previous_head_pos);
        previous_head_pos = requests[i];
    }

    cout << "Total head movement: " << total_head_movement << endl;
    return 0;
}
