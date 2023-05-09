/****************************************************
    RESOURCE ALLOCATION GRAPH (RAG) IMPLEMENTATION
*****************************************************

Made by: 	 Jasleen Kaur
Roll NO.:    102118064
Group:       BS-3
Course No:   UCT401
Course Name: Operating Systems
Thapar Institute of Engineering and Technology, Patiala

****************************************************/

/* RESOURCE ALLOCATION GRAPH (RAG)
A resource allocation graph (RAG) is a directed graph that represents the resource allocation requirements of a set of processes. It is used to determine if a set of processes is safe or not.

A RAG is created by adding an edge from a process to a resource if the process needs the resource. An edge is also added from a resource to a process if the resource is available.

****************************************************/

// C++ code for Resource Allocation Graph (RAG) implementation using adjacency matrix

#include <iostream>
#include <vector>

using namespace std;

// function to create wait-for graph from adjacency matrix
vector<vector<int>> createWaitForGraph(vector<vector<int>> &adjacencyMatrix, int n) {
    vector<vector<int>> waitForGraph(n, vector<int>(n)); 

    // iterate through adjacency matrix
    for(int i = 0; i < n; i++) 
        for(int j = 0; j < n; j++)
            if(adjacencyMatrix[i][j] > 0) // if edge exists
                waitForGraph[i][j] = 1; // add edge from process to resource

    return waitForGraph;
}

// function to check if wait-for graph contains a cycle
bool isCyclic(vector<vector<int>> &graph, vector<int> &visited, int v) {
    visited[v] = 1; // mark current node as visited

    // iterate through all adjacent nodes
    for(int i = 0; i < graph[v].size(); i++) {
        int u = graph[v][i]; // get adjacent node

        // if adjacent node is not visited, check if it contains a cycle
        if(visited[u] == 0) 
            if(isCyclic(graph, visited, u)) 
                return true;
        
        // if adjacent node is visited, then there is a cycle
        else if(visited[u] == 1) 
            return true;
    }

    visited[v] = 2; // mark current node as processed
    return false; // no cycle found
}

int main() {
    int n;

    // get number of processes
    cout << "Enter number of processes: ";
    cin >> n;

    // create adjacency matrix
    vector<vector<int>> adjacencyMatrix(n, vector<int>(n));
    cout << "Enter the adjacency matrix: " << endl;
    for(int i = 0; i < n; i++) 
        for(int j = 0; j < n; j++)
            cin >> adjacencyMatrix[i][j];

    // create wait-for graph
    vector<vector<int>> waitForGraph = createWaitForGraph(adjacencyMatrix, n);

    // check if wait-for graph contains a cycle
    vector<int> visited(n); // 0 = not visited, 1 = visited, 2 = processed
    bool isCycle = false;
    for(int i = 0; i < n; i++) 
        if(visited[i] == 0) 
            if(isCyclic(waitForGraph, visited, i)) {
                isCycle = true;
                break;
            }

    // print result
    if(isCycle) 
        cout << "Wait-for graph contains a cycle." << endl;
    else 
        cout << "Wait-for graph does not contain a cycle." << endl;

    // print wait-for graph
    cout << "Wait-for graph: " << endl;
    for(int i = 0; i < n; i++) {
        cout << i << ": ";
        for(int j = 0; j < n; j++)
            cout << waitForGraph[i][j] << " ";
        cout << endl;
    }

    return 0;
}

/*********************************************************

OUTPUT:

Enter number of processes: 3
Enter the adjacency matrix: 
0 1 0
0 0 1
0 0 0
Wait-for graph does not contain a cycle.
Wait-for graph: 
0: 0 1 0 
1: 0 0 1 
2: 0 0 0

*/
