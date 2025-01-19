#include <bits/stdc++.h>
using namespace std;
struct Compare {
    bool operator()(pair<int, int> a, pair<int, int> b) {
        return a.second > b.second; // Compare based on priority (ascending)
    }
};
int main() {
    // Max-heap (default behavior) in java it is min-heap by default
    priority_queue<int> pq;

    // Insert elements
    pq.push(10);
    pq.push(20);
    pq.push(5);

    // Display and remove elements
    cout << "Max-heap elements in descending order:\n";
    while (!pq.empty()) {
        cout << pq.top() << " "; // Access the largest element
        pq.pop();               // Remove the top element
    }
    cout << endl;
    /*
    Output:
    Max-heap elements in descending order:
    20 10 5 
    */

       // Min-heap (using custom comparator)
    priority_queue<int, vector<int>, greater<int>> minHeap;

    // Insert elements
    minHeap.push(10);
    minHeap.push(20);
    minHeap.push(5);

    // Display and remove elements
    cout << "Min-heap elements in ascending order:\n";
    while (!minHeap.empty()) {
        cout << minHeap.top() << " "; // Access the smallest element
        minHeap.pop();               // Remove the top element
    }
    cout << endl;

    /*
    Output:
    Min-heap elements in ascending order:
    5 10 20 
    */

       // Max-heap for pairs based on the first element maximum
    priority_queue<pair<int, int>> pq1;

    // Insert elements (ID, Priority)
    pq1.push({1, 30});
    pq1.push({2, 20});
    pq1.push({3, 50}); // Highest priority

    // Process elements in descending order of priority
    cout << "Max-Heap (Descending by priority):\n";
    while (!pq1.empty()) {
        auto top = pq1.top();
        cout << "ID: " << top.first << ", Priority: " << top.second << endl;
        pq1.pop();
    }
    /*
    Max-Heap (Descending by priority):
    ID: 3, Priority: 50
    ID: 2, Priority: 20
    ID: 1, Priority: 30
    */

   //based on 2nd element min heap
     priority_queue<pair<int, int>, vector<pair<int, int>>, Compare> pq3;

    // Insert elements (ID, Priority)
    pq3.push({1, 30}); // Higher priority
    pq3.push({2, 20});
    pq3.push({3, 50}); // Highest priority

    // Process elements in ascending order of priority
    cout << "Min-Heap (Ascending by priority):\n";
    while (!pq3.empty()) {
        auto top = pq3.top();
        cout << "ID: " << top.first << ", Priority: " << top.second << endl;
        pq3.pop();
    }
    /*
    Min-Heap (Ascending by priority):
    ID: 2, Priority: 20
    ID: 1, Priority: 30
    ID: 3, Priority: 50
    */
    
    return 0;
}


