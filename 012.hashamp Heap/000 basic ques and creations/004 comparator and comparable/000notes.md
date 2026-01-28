# Notes

![alt text](<005 Comparator and comparable_240516_030950.jpg>)

![alt text](<005 Comparator and comparable_240516_030950(1).jpg>) ![alt text](<005 Comparator and comparable_240516_030950(2).jpg>) ![alt text](<005 Comparator and comparable_240516_030950(3).jpg>) ![alt text](<005 Comparator and comparable_240516_030950(4).jpg>) 



![alt text](<005 Comparator and comparable_240516_030950(5).jpg>) ![alt text](<005 Comparator and comparable_240516_030950(6).jpg>) ![alt text](<005 Comparator and comparable_240516_030950(7).jpg>) ![alt text](<005 Comparator and comparable_240516_030950(8).jpg>) ![alt text](<005 Comparator and comparable_240516_030950(9).jpg>) ![alt text](<005 Comparator and comparable_240516_030950(10).jpg>) ![alt text](<005 Comparator and comparable_240516_030950(11).jpg>) ![alt text](<005 Comparator and comparable_240516_030950(12).jpg>) ![alt text](<005 Comparator and comparable_240516_030950(13).jpg>) ![alt text](<005 Comparator and comparable_240516_030950(14).jpg>) ![alt text](<005 Comparator and comparable_240516_030950(15).jpg>) ![alt text](<005 Comparator and comparable_240516_030950(16).jpg>) ![alt text](<005 Comparator and comparable_240516_030950(17).jpg>) ![alt text](<005 Comparator and comparable_240516_030950(18).jpg>) ![alt text](<005 Comparator and comparable_240516_030950(19).jpg>) ![alt text](<005 Comparator and comparable_240516_030950(20).jpg>) ![alt text](<005 Comparator and comparable_240516_030950(21).jpg>) ![alt text](<005 Comparator and comparable_240516_030950(22).jpg>) ![alt text](<005 Comparator and comparable_240516_030950(23).jpg>) ![alt text](<005 Comparator and comparable_240516_030950(24).jpg>) ![alt text](<005 Comparator and comparable_240516_030950(25).jpg>) ![alt text](<005 Comparator and comparable_240516_030950(26).jpg>) ![alt text](<005 Comparator and comparable_240516_030950(27).jpg>) ![alt text](<005 Comparator and comparable_240516_030950(28).jpg>) ![alt text](<005 Comparator and comparable_240516_030950(29).jpg>) ![alt text](<005 Comparator and comparable_240516_030950(30).jpg>) ![alt text](<005 Comparator and comparable_240516_030950(31).jpg>) ![alt text](<005 Comparator and comparable_240516_030950(32).jpg>) ![alt text](<005 Comparator and comparable_240516_030950(33).jpg>) ![alt text](<005 Comparator and comparable_240516_030950(34).jpg>) ![alt text](<005 Comparator and comparable_240516_030950(35).jpg>) ![alt text](<005 Comparator and comparable_240516_030950(36).jpg>) 


Implement a priority queue of student hvaing name ,marks and age sort ascending according to makrks if same makrs then accoring to name ascending if same name then age decending sort

```cpp
#include <iostream>
#include <vector>
#include <queue>
#include <string>

using namespace std;

struct Student {
    string name;
    int marks;
    int age;

    Student(string n, int m, int a) : name(n), marks(m), age(a) {}
};

// Custom Comparator
struct CompareStudent {
    bool operator()(const Student& a, const Student& b) {
        // 1. Marks Ascending (b is higher priority if a has MORE marks)
        if (a.marks != b.marks) {
            return a.marks > b.marks; 
        }
        
        // 2. Name Ascending (if marks same, b is higher priority if a's name is "greater")
        if (a.name != b.name) {
            return a.name > b.name;
        }

        // 3. Age Descending (if name same, b is higher priority if a is YOUNGER)
        return a.age < b.age;
    }
};

int main() {
    // Syntax: priority_queue<Type, Container, Comparator>
    priority_queue<Student, vector<Student>, CompareStudent> pq;

    pq.push(Student("Ankit", 90, 20));
    pq.push(Student("Zoya", 90, 22));
    pq.push(Student("Ankit", 90, 25)); // Same name, Same marks, Higher age
    pq.push(Student("Rahul", 85, 21));

    while (!pq.empty()) {
        Student s = pq.top();
        cout << "Name: " << s.name << " | Marks: " << s.marks << " | Age: " << s.age << endl;
        pq.pop();
    }

    return 0;
}

```

# Multi-Level Comparator Physics

When writing a complex comparator (A then B then C), the logic follows a "Decision Tree."

### 1. The Priority Queue "Reverse" Rule
In `std::priority_queue<T, vector<T>, Compare>`, the element that returns `false` when compared to everyone else ends up at the **TOP**.
- For **Ascending** (Smallest at top): Use `a > b`.
- For **Descending** (Largest at top): Use `a < b`.

### 2. Decision Tree for this Problem
To sort as requested (Marks ↑, Name ↑, Age ↓):

| Priority | Criteria | Rule for PQ (Top is Smallest) |
| :--- | :--- | :--- |
| **Primary** | Marks (Asc) | `if (a.marks != b.marks) return a.marks > b.marks;` |
| **Secondary** | Name (Asc) | `if (a.name != b.name) return a.name > b.name;` |
| **Tertiary** | Age (Desc) | `return a.age < b.age;` (Returns true if `a` is younger, making older `age` higher priority) |

### 3. Why `const Student& a`?
Always pass by **reference** (`&`) and use `const` in comparators.
- **Performance**: Prevents copying the entire `Student` object (especially strings) every time a comparison happens.
- **Safety**: Ensures the comparator doesn't accidentally modify the data while sorting.