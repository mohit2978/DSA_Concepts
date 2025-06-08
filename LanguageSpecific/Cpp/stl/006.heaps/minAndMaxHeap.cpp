#include <bits/stdc++.h>
using namespace std;

int main() {
    // Max Heap (default in priority_queue)
    priority_queue<int> maxHeap;

    // Min Heap (by using greater<int>)
    priority_queue<int, vector<int>, greater<int>> minHeap;

    // Sample data
    vector<int> data = {10, 20, 5, 15, 30};

    // Insert elements into Max Heap
    for (int num : data) {
        maxHeap.push(num);
    }

    // Insert elements into Min Heap
    for (int num : data) {
        minHeap.push(num);
    }

    // Display Max Heap
    cout << "Max Heap (Top to Bottom): ";
    while (!maxHeap.empty()) {
        cout << maxHeap.top() << " ";
        maxHeap.pop();
    }
    cout << endl;

    // Display Min Heap
    cout << "Min Heap (Top to Bottom): ";
    while (!minHeap.empty()) {
        cout << minHeap.top() << " ";
        minHeap.pop();
    }
    cout << endl;

    return 0;
}

/*
Output 
Max Heap (Top to Bottom): 30 20 15 10 5 
Min Heap (Top to Bottom): 5 10 15 20 30 
*/
