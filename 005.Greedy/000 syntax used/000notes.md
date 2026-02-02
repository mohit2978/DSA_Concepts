# See sort function using comparator

```cpp
#include <iostream>
#include <vector>
#include <algorithm> // for sort
#include <utility>   // for pair
#include <string>

using namespace std;

// --- Class for Examples 6 & 7 ---
struct Student {
    string name;
    int rollNo;
    int marks;
};

// --- Comparator Struct for Example 7 ---
struct ComplexComparator {
    bool operator()(const Student& a, const Student& b) {
        if (a.marks != b.marks) 
            return a.marks > b.marks; // 1. Marks Descending
        
        if (a.name != b.name) 
            return a.name < b.name;   // 2. Name Ascending
        
        return a.rollNo > b.rollNo;   // 3. Roll No Descending
    }
};

int main() {
    // --- 1. Standard Sort (Ascending) ---
    vector<int> arr1 = {5, 2, 9, 1, 5, 6};
    sort(arr1.begin(), arr1.end()); 
    // Result: 1, 2, 5, 5, 6, 9

    // --- 2. Descending Sort ---
    vector<int> arr2 = {5, 2, 9, 1, 5, 6};
    sort(arr2.begin(), arr2.end(), greater<int>()); 
    // Result: 9, 6, 5, 5, 2, 1

    // --- 3. Sort on Part (Ascending) ---
    vector<int> arr3 = {10, 5, 2, 9, 1, 50};
    // Sort only from index 1 to 4 (exclude first and last)
    sort(arr3.begin() + 1, arr3.end() - 1); 
    // Result: 10, 1, 2, 5, 9, 50 (10 and 50 stayed put)

    // --- 4. Sort Pairs Descending (Lexicographical) ---
    // Compares first element, if equal, compares second
    vector<pair<int, int>> pairs1 = {{1, 2}, {3, 1}, {1, 5}, {3, 0}};
    sort(pairs1.begin(), pairs1.end(), greater<pair<int, int>>());
    // Result: {3, 1}, {3, 0}, {1, 5}, {1, 2}

    // --- 5. Sort Pairs Ascending on 2nd Value ---
    vector<pair<int, int>> pairs2 = {{1, 10}, {3, 5}, {2, 8}};
    sort(pairs2.begin(), pairs2.end(), [](const pair<int,int>& a, const pair<int,int>& b) {
        return a.second < b.second;
    });
    // Result: {3, 5}, {2, 8}, {1, 10}

    // --- 6. Simple Class Sort (Sort by Marks Ascending) ---
    vector<Student> class1 = {{"Alice", 1, 80}, {"Bob", 2, 90}, {"Charlie", 3, 70}};
    sort(class1.begin(), class1.end(), [](const Student& a, const Student& b) {
        return a.marks < b.marks;
    });
    // Result: Charlie(70), Alice(80), Bob(90)

    // --- 7. Complex Class Sort ---
    // Criteria: Marks DESC -> Name ASC -> Roll No DESC
    vector<Student> students = {
        {"Alice", 101, 85}, 
        {"Bob", 102, 90}, 
        {"Alice", 105, 85}, // Same Name & Marks as first Alice, different Roll
        {"Dave", 103, 90},  // Same Marks as Bob
        {"Eve", 104, 40}
    };

    // Method A: Using Lambda
    sort(students.begin(), students.end(), [](const Student& a, const Student& b) {
        if (a.marks != b.marks) 
            return a.marks > b.marks; // Higher marks first
        
        if (a.name != b.name) 
            return a.name < b.name;   // Alphabetical name
        
        return a.rollNo > b.rollNo;   // Higher roll no first
    });

    // Method B: Using Comparator Struct
    // sort(students.begin(), students.end(), ComplexComparator());

    // Result Check:
    // 1. Bob   (90, Bob, 102)  - 90 Marks, Name 'B' < 'D'
    // 2. Dave  (90, Dave, 103) - 90 Marks
    // 3. Alice (85, Alice, 105) - 85 Marks, Name 'A', Roll 105 > 101
    // 4. Alice (85, Alice, 101) - 85 Marks, Name 'A'
    // 5. Eve   (40, Eve, 104)
    
    return 0;
}
```

# See sort function using lambda


```cpp
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <utility> // For pair

using namespace std;

struct Student {
    string name;
    int rollNo;
    int marks;
};

int main() {
    // --- 1. Standard Sort (Ascending) using Lambda ---
    vector<int> arr1 = {5, 2, 9, 1, 5, 6};
    sort(arr1.begin(), arr1.end(), [](int a, int b) {
        return a < b; // "a comes before b if a is smaller"
    });
    // Result: 1, 2, 5, 5, 6, 9

    
    // --- 2. Descending Sort using Lambda ---
    vector<int> arr2 = {5, 2, 9, 1, 5, 6};
    sort(arr2.begin(), arr2.end(), [](int a, int b) {
        return a > b; // "a comes before b if a is larger"
    });
    // Result: 9, 6, 5, 5, 2, 1


    // --- 3. Sort on Part (Ascending) using Lambda ---
    vector<int> arr3 = {10, 5, 2, 9, 1, 50};
    // Sort only elements from index 1 to 4 (values: 5, 2, 9, 1)
    sort(arr3.begin() + 1, arr3.end() - 1, [](int a, int b) {
        return a < b;
    });
    // Result: 10, 1, 2, 5, 9, 50


    // --- 4. Sort on Pair Descending using Lambda ---
    // (Compares first element, if equal then second)
    vector<pair<int, int>> pairs1 = {{1, 2}, {3, 1}, {1, 5}, {3, 0}};
    sort(pairs1.begin(), pairs1.end(), [](const pair<int,int>& a, const pair<int,int>& b) {
        if (a.first != b.first)
            return a.first > b.first;  // First value Descending
        return a.second > b.second;    // Second value Descending
    });
    // Result: {3, 1}, {3, 0}, {1, 5}, {1, 2}


    // --- 5. Sort on Pair Ascending on 2nd Value using Lambda ---
    vector<pair<int, int>> pairs2 = {{1, 10}, {3, 5}, {2, 8}};
    sort(pairs2.begin(), pairs2.end(), [](const pair<int,int>& a, const pair<int,int>& b) {
        return a.second < b.second; // Only cares about 2nd value
    });
    // Result: {3, 5}, {2, 8}, {1, 10}


    // --- 6. Sort on Class Values (Simple: Marks Ascending) ---
    vector<Student> class1 = {{"Alice", 1, 80}, {"Bob", 2, 90}, {"Charlie", 3, 70}};
    sort(class1.begin(), class1.end(), [](const Student& a, const Student& b) {
        return a.marks < b.marks;
    });
    // Result: Charlie(70), Alice(80), Bob(90)


    // --- 7. Complex Class Sort ---
    // Criteria: Marks DESC -> Name ASC -> Roll No DESC
    vector<Student> students = {
        {"Alice", 101, 85}, 
        {"Bob", 102, 90}, 
        {"Alice", 105, 85}, 
        {"Dave", 103, 90}, 
        {"Eve", 104, 40}
    };

    sort(students.begin(), students.end(), [](const Student& a, const Student& b) {
        if (a.marks != b.marks) 
            return a.marks > b.marks; // 1. Marks Descending
        
        if (a.name != b.name) 
            return a.name < b.name;   // 2. Name Ascending (Alphabetical)
        
        return a.rollNo > b.rollNo;   // 3. Roll No Descending
    });

    // Result Logic:
    // 1. Bob (90) comes before Dave (90) because 'B' < 'D'
    // 2. Alice (105) comes before Alice (101) because Marks same, Name same, but Roll 105 > 101
    
    return 0;
}
```

# See priority queue

```cpp
#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <utility> // For pair

using namespace std;

struct Student {
    string name;
    int rollNo;
    int marks;
};

// --- Comparator for Case 7 ---
struct ComplexComparator {
    bool operator()(const Student& a, const Student& b) {
        // Logic: Return TRUE if 'a' should be BELOW 'b'
        
        // 1. Marks Descending (High marks on top)
        // If a has less marks than b, a goes below.
        if (a.marks != b.marks) 
            return a.marks < b.marks; 
        
        // 2. Name Ascending (Alphabetical "Alice" on top)
        // If a is "Bob" and b is "Alice", we want Alice on top.
        // So if a.name > b.name ("Bob" > "Alice"), a goes below.
        if (a.name != b.name) 
            return a.name > b.name;   
        
        // 3. Roll No Descending (High roll on top)
        // If a has smaller roll than b, a goes below.
        return a.rollNo < b.rollNo;   
    }
};

int main() {
    // --- 1. Standard Sort (Ascending Output -> Smallest on Top) ---
    // We need a MIN HEAP.
    // Logic: 'a' goes below 'b' if 'a' is GREATER than 'b'.
    priority_queue<int, vector<int>, greater<int>> pq1; 
    for(int x : {5, 2, 9, 1, 5, 6}) pq1.push(x);
    
    cout << "1. Ascending: ";
    while(!pq1.empty()) { cout << pq1.top() << " "; pq1.pop(); }
    cout << endl; // Output: 1 2 5 5 6 9


    // --- 2. Descending Sort (Largest on Top) ---
    // We need a MAX HEAP (Default behavior).
    priority_queue<int> pq2; 
    for(int x : {5, 2, 9, 1, 5, 6}) pq2.push(x);

    cout << "2. Descending: ";
    while(!pq2.empty()) { cout << pq2.top() << " "; pq2.pop(); }
    cout << endl; // Output: 9 6 5 5 2 1


    // --- 3. Sort on Part (Push only specific range) ---
    // PQ cannot sort a "part" of an array in-place. You must push that part into the PQ.
    vector<int> arr3 = {10, 5, 2, 9, 1, 50};
    priority_queue<int, vector<int>, greater<int>> pq3; // Min Heap
    
    // Push only indices 1 to 4
    for(int i=1; i<=4; i++) pq3.push(arr3[i]);

    cout << "3. Part Sort: ";
    while(!pq3.empty()) { cout << pq3.top() << " "; pq3.pop(); }
    cout << endl; // Output: 1 2 5 9


    // --- 4. Pair Descending (Default Max Heap) ---
    // Uses standard pair comparison (First desc, then Second desc)
    priority_queue<pair<int, int>> pq4;
    pq4.push({1, 2}); pq4.push({3, 1}); pq4.push({1, 5}); pq4.push({3, 0});

    cout << "4. Pair Desc: ";
    while(!pq4.empty()) { 
        cout << "{" << pq4.top().first << "," << pq4.top().second << "} "; 
        pq4.pop(); 
    }
    cout << endl; // Output: {3,1} {3,0} {1,5} {1,2}


    // --- 5. Pair Ascending on 2nd Value ---
    // We want Smallest 2nd value on top.
    // Lambda Logic: Returns true if a.second > b.second (a is "worse" than b)
    auto compPair = [](const pair<int,int>& a, const pair<int,int>& b) {
        return a.second > b.second; 
    };
    priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(compPair)> pq5(compPair);
    
    pq5.push({1, 10}); pq5.push({3, 5}); pq5.push({2, 8});

    cout << "5. Pair 2nd Asc: ";
    while(!pq5.empty()) { 
        cout << "{" << pq5.top().first << "," << pq5.top().second << "} "; 
        pq5.pop(); 
    }
    cout << endl; // Output: {3,5} {2,8} {1,10}


    // --- 6. Class Values (Marks Ascending -> Lowest Marks Top) ---
    auto compClassSimple = [](const Student& a, const Student& b) {
        return a.marks > b.marks; // If a has more marks, it goes below (Min Heap)
    };
    priority_queue<Student, vector<Student>, decltype(compClassSimple)> pq6(compClassSimple);
    
    pq6.push({"Alice", 1, 80}); pq6.push({"Bob", 2, 90}); pq6.push({"Charlie", 3, 70});

    cout << "6. Marks Asc: ";
    while(!pq6.empty()) { cout << pq6.top().name << " "; pq6.pop(); }
    cout << endl; // Output: Charlie Alice Bob


    // --- 7. Complex Class Sort (Using Struct Comparator) ---
    // Marks DESC, Name ASC, Roll DESC
    priority_queue<Student, vector<Student>, ComplexComparator> pq7;
    
    pq7.push({"Alice", 101, 85});
    pq7.push({"Bob", 102, 90});
    pq7.push({"Alice", 105, 85});
    pq7.push({"Dave", 103, 90});
    pq7.push({"Eve", 104, 40});

    cout << "7. Complex: ";
    while(!pq7.empty()) { 
        Student s = pq7.top(); pq7.pop();
        cout << "[" << s.name << "-" << s.marks << "-" << s.rollNo << "] "; 
    }
    cout << endl;
    // Expected Output Logic:
    // 1. Bob (90) - vs Dave (90), Bob is alphabetically smaller (Preferred)
    // 2. Dave (90)
    // 3. Alice (85, 105) - vs Alice (85, 101), 105 is larger roll (Preferred)
    // 4. Alice (85, 101)
    // 5. Eve (40)
    
    return 0;
}
```


## Prioirty queue using lmabda

Crucial Note on Syntax: Unlike sort, you cannot just pass the lambda as an argument. You must:

Define the lambda object.

Pass decltype(lambda) as the third template argument.

Pass the lambda object itself to the constructor.


```cpp
#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <utility> // For pair

using namespace std;

struct Student {
    string name;
    int rollNo;
    int marks;
};

int main() {
    // --- 1. Standard Sort (Ascending Output -> Min Heap) ---
    // Logic: Return true if 'a' should be BELOW 'b'.
    // To get smallest on top, larger elements go below.
    auto compAsc = [](int a, int b) {
        return a > b; 
    };
    priority_queue<int, vector<int>, decltype(compAsc)> pq1(compAsc);
    
    for(int x : {5, 2, 9, 1, 5, 6}) pq1.push(x);
    
    cout << "1. Ascending: ";
    while(!pq1.empty()) { cout << pq1.top() << " "; pq1.pop(); }
    cout << endl; // Output: 1 2 5 5 6 9


    // --- 2. Descending Sort (Descending Output -> Max Heap) ---
    // Logic: To get largest on top, smaller elements go below.
    auto compDesc = [](int a, int b) {
        return a < b; 
    };
    priority_queue<int, vector<int>, decltype(compDesc)> pq2(compDesc);
    
    for(int x : {5, 2, 9, 1, 5, 6}) pq2.push(x);

    cout << "2. Descending: ";
    while(!pq2.empty()) { cout << pq2.top() << " "; pq2.pop(); }
    cout << endl; // Output: 9 6 5 5 2 1


    // --- 3. Sort on Part (Push specific range) ---
    // PQ cannot sort a "part" of an existing vector in-place.
    // We just push the specific elements into the PQ.
    vector<int> arr3 = {10, 5, 2, 9, 1, 50};
    auto compPart = [](int a, int b) { return a > b; }; // Min Heap
    priority_queue<int, vector<int>, decltype(compPart)> pq3(compPart);
    
    // Push indices 1 to 4
    for(int i=1; i<=4; i++) pq3.push(arr3[i]);

    cout << "3. Part Sort: ";
    while(!pq3.empty()) { cout << pq3.top() << " "; pq3.pop(); }
    cout << endl; // Output: 1 2 5 9


    // --- 4. Pair Descending (Max Heap) ---
    auto compPairDesc = [](const pair<int,int>& a, const pair<int,int>& b) {
        if (a.first != b.first) return a.first < b.first;
        return a.second < b.second;
    };
    priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(compPairDesc)> pq4(compPairDesc);
    
    pq4.push({1, 2}); pq4.push({3, 1}); pq4.push({1, 5}); pq4.push({3, 0});

    cout << "4. Pair Desc: ";
    while(!pq4.empty()) { 
        cout << "{" << pq4.top().first << "," << pq4.top().second << "} "; 
        pq4.pop(); 
    }
    cout << endl; // Output: {3,1} {3,0} {1,5} {1,2}


    // --- 5. Pair Ascending on 2nd Value (Min Heap on 2nd) ---
    // Logic: 'a' goes below if 'a.second' is LARGER.
    auto compPair2ndAsc = [](const pair<int,int>& a, const pair<int,int>& b) {
        return a.second > b.second; 
    };
    priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(compPair2ndAsc)> pq5(compPair2ndAsc);
    
    pq5.push({1, 10}); pq5.push({3, 5}); pq5.push({2, 8});

    cout << "5. Pair 2nd Asc: ";
    while(!pq5.empty()) { 
        cout << "{" << pq5.top().first << "," << pq5.top().second << "} "; 
        pq5.pop(); 
    }
    cout << endl; // Output: {3,5} {2,8} {1,10}


    // --- 6. Class Values (Marks Ascending -> Min Heap) ---
    auto compMarksAsc = [](const Student& a, const Student& b) {
        return a.marks > b.marks; // Higher marks = Lower priority (go to bottom)
    };
    priority_queue<Student, vector<Student>, decltype(compMarksAsc)> pq6(compMarksAsc);
    
    pq6.push({"Alice", 1, 80}); pq6.push({"Bob", 2, 90}); pq6.push({"Charlie", 3, 70});

    cout << "6. Marks Asc: ";
    while(!pq6.empty()) { cout << pq6.top().name << " "; pq6.pop(); }
    cout << endl; // Output: Charlie Alice Bob


    // --- 7. Complex Class Sort ---
    // Target: Marks DESC, Name ASC, Roll DESC
    // Top of Heap should be: {High Marks, "A" Name, High Roll}
    // Comparator Logic: Returns TRUE if 'a' is "WORSE" than 'b'.
    auto compComplex = [](const Student& a, const Student& b) {
        // 1. Marks: We want High on top. 
        // So 'a' is worse if it has LOWER marks.
        if (a.marks != b.marks) 
            return a.marks < b.marks; 
        
        // 2. Name: We want "Alice" (Small string) on top.
        // So 'a' is worse if it is "Bob" (Larger string).
        if (a.name != b.name) 
            return a.name > b.name;   
        
        // 3. Roll: We want High Roll on top.
        // So 'a' is worse if it has LOWER roll.
        return a.rollNo < b.rollNo;   
    };

    priority_queue<Student, vector<Student>, decltype(compComplex)> pq7(compComplex);
    
    pq7.push({"Alice", 101, 85});
    pq7.push({"Bob", 102, 90});
    pq7.push({"Alice", 105, 85});
    pq7.push({"Dave", 103, 90});
    pq7.push({"Eve", 104, 40});

    cout << "7. Complex: ";
    while(!pq7.empty()) { 
        Student s = pq7.top(); pq7.pop();
        cout << "[" << s.name << "-" << s.marks << "-" << s.rollNo << "] "; 
    }
    cout << endl;
    // Expected Output:
    // 1. [Bob-90-102] ('B' < 'D')
    // 2. [Dave-90-103]
    // 3. [Alice-85-105] (Roll 105 > 101)
    // 4. [Alice-85-101]
    // 5. [Eve-40-104]

    return 0;
}
```







