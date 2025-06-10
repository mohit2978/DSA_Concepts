#include<bits/stdc++.h> 

using namespace std; 
//array is fixed size we cannot change its size once declared so we use vector
//also in here do not perform bound checking

// if we have array size 3 we can iterate through 8  using [] operator rest index 3 to 7 will have garbage value 
// generally [] checks in bound but for array [] is overloaded

// if you need bound checking use at() function

// Function to print an array
template <typename T, size_t N>
void printArray(const array<T, N>& arr) {
    for (const auto& elem : arr) {
        cout << elem << " ";
    }
    cout << endl;
}

// Function to demonstrate basic operations on std::array
void basicOperations() {
    array<int, 5> arr = {10, 20, 30, 40, 50};

    cout << "First element: " << arr.front() << endl;
    cout << "Last element: " << arr.back() << endl;
    cout << "Second element (bounds-checked): " << arr.at(1) << endl;

    cout << "Original array: ";
    printArray(arr);

    // Modify elements
    arr.fill(42);
    cout << "After filling with 42: ";
    printArray(arr);
}

// Function to demonstrate iterators
void iteratorExample() {
    array<int, 5> arr = {5, 4, 3, 2, 1};

    cout << "Iterating forward: ";
    for (auto it = arr.begin(); it != arr.end(); ++it) {
        cout << *it << " ";
    }
    cout << endl;

    cout << "Iterating backward: ";
    for (auto rit = arr.rbegin(); rit != arr.rend(); ++rit) {
        cout << *rit << " ";
    }
    cout << endl;
    
}

// Function to demonstrate integration with STL algorithms
void stlAlgorithmsExample() {
    array<int, 5> arr = {5, 1, 4, 2, 3};//array of integer of 5 size

    // Sorting the array
    sort(arr.begin(), arr.end());
    cout << "Sorted array: ";
    printArray(arr);

    // Finding an element
    int value = 3;
    if (binary_search(arr.begin(), arr.end(), value)) {
        cout << value << " is found in the array!" << endl;
    } else {
        cout << value << " is not found in the array!" << endl;
    }
}

int main() {
    cout << "=== Basic Operations ===" << endl;
    basicOperations();

    cout << "\n=== Iterator Example ===" << endl;
    iteratorExample();

    cout << "\n=== STL Algorithms Example ===" << endl;
    stlAlgorithmsExample();
/*
Output:

=== Basic Operations ===
First element: 10
Last element: 50
Second element (bounds-checked): 20
Original array: 10 20 30 40 50 
After filling with 42: 42 42 42 42 42 

=== Iterator Example ===
Iterating forward: 5 4 3 2 1 
Iterating backward: 1 2 3 4 5 

=== STL Algorithms Example ===
Sorted array: 1 2 3 4 5 
3 is found in the array!
*/
    return 0;
}
