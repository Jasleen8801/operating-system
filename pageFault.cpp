// Compute the no of page faults using FIFO page replacement algorithm
// No of frames - 3
// Request list - 1 2 3 4 1 2 5 1 2 3 4 5

#include <iostream>
#include <queue>

using namespace std;

int main() {
    int frames, requests;
    cout << "Enter the no of frames: ";
    cin >> frames;
    cout << "Enter the no of requests: ";
    cin >> requests;

    int page_faults = 0;
    queue<int> q;

    cout<<"Enter the requests: ";
    for (int i = 0; i < requests; i++) {
        int request;
        cin >> request;
        bool found = false;
        for (int j = 0; j < q.size(); j++) {
            if (q.front() == request) {
                found = true;
                break;
            }
            q.push(q.front());
            q.pop();
        }
        if (!found) {
            if (q.size() == frames) {
                q.pop();
            }
            q.push(request);
            page_faults++;
        }
    }
}
