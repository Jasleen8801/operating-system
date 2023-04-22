/****************************************************
    RESOURCE ALLOCATION GRAPH (RAG) IMPLEMENTATION USING DFS
*****************************************************

Made by: 	 Jasleen Kaur
Roll NO.:    102118064
Group:       BS-3
Course No:   UCT401
Course Name: Operating Systems
Thapar Institute of Engineering and Technology, Patiala

****************************************************/

/* RESOURCE ALLOCATION GRAPH (RAG)

A resource allocation graph (RAG) is a directed graph that represents the resource allocation
requirements of a set of processes. It is used to determine if a set of processes is safe or not.

A RAG is created by adding an edge from a process to a resource if the process needs the resource.
An edge is also added from a resource to a process if the resource is available.

****************************************************/

// C++ code for Resource Allocation Graph (RAG) implementation using DFS

#include <iostream>
#include <vector>

using namespace std;

// functiion to check if RAG contains a cycle
bool isCyclic(vector<vector<int>> &graph, vector<int> &color, int v) {
    color[v] = 1; // mark current node as visited

    // iterate through all adjacent nodes
    for(int i = 0; i < graph[v].size(); i++) {
        int u = graph[v][i]; // get adjacent node

        // if adjacent node is not visited, check if it contains a cycle
        if(color[u] == 0) {
            if(isCyclic(graph, color, u)) {
                return true;
            }
        }

        // if adjacent node is visited, then there is a cycle
        else if(color[u] == 1) {
            return true;
        }
    }

    color[v] = 2; // mark current node as processed
    return false; // no cycle found
}

// function to check if RAG is safe
bool isSafe(vector<vector<int>> &allocation, vector<vector<int>> &max, vector<int> &available, int n, int m) {
    vector<vector<int>> need(n, vector<int>(m)); // need matrix

    // calculate need matrix
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }

    // create the resource allocation graph
    vector<vector<int>> graph(n + m, vector<int>());
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            // add edges from the available resources to the processes that need them
            if(available[j] >= need[i][j]) {
                graph[n + j].push_back(i);
            }

            // add edges from the processes to the resources they need
            if(need[i][j] > 0) {
                graph[i].push_back(n + j);
            }
        }
    }

    // check if RAG contains a cycle
    vector<int> color(n + m, 0); // 0 = not visited, 1 = visited, 2 = processed
    for(int i = 0; i < n + m; i++) {
        if(color[i] == 0) {
            if(isCyclic(graph, color, i)) {
                return false; // RAG contains a cycle
            }
        }
    }

    return true; // RAG does not contain a cycle
}

int main() {
    int n, m;

    // taking input from user
    cout << "Enter number of processes: ";
    cin >> n;
    cout << "Enter number of resources: ";
    cin >> m;

    // create allocation, max and available matrices
    vector<vector<int>> allocation(n, vector<int>(m));
    vector<vector<int>> max(n, vector<int>(m));
    vector<int> available(m);

    cout << "Enter allocation matrix: " << endl;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            cin >> allocation[i][j];
        }
    }

    cout << "Enter max matrix: " << endl;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            cin >> max[i][j];
        }
    }

    cout << "Enter available matrix: " << endl;
    for(int i = 0; i < m; i++) {
        cin >> available[i];
    }

    // check if RAG is safe
    if(isSafe(allocation, max, available, n, m)) {
        cout << "RAG is safe" << endl;
    }
    else {
        cout << "RAG is not safe" << endl;
    }

    return 0;
}
