#include<bits/stdc++.h>
using namespace std;

int main() {
    set<int> mySet = {10, 20, 30};

    // Insert
    mySet.insert(40);
    mySet.emplace(50);

    /*
    The insert function adds a new element if it's not already present, 
    returning a pair indicating success and an iterator. The emplace function
     constructs the element in place, potentially improving efficiency by 
     avoiding unnecessary copies or moves.
    */

    // Find and Erase
    if (mySet.find(20) != mySet.end())
        mySet.erase(20);

    // Iteration
    for (int x : mySet)
        cout << x << " "; // Output: 10 30 40 50

    // Bounds
    auto lb = mySet.lower_bound(30); // Points to 30
    auto ub = mySet.upper_bound(30); // Points to 40
    cout << "\nLower bound: " << *lb << ", Upper bound: " << *ub << endl;
    /*
    lower_bound(const key_type& key): Returns an iterator to the first element not less than the key.
    upper_bound(const key_type& key): Returns an iterator to the first element greater than the key.
    */

   vector<int> v = {1, 2, 3,3,4,5,6,1,1,1,1,12,2,2};
    set<int> s(v.begin(), v.end());

    for (int x : s)
        cout << x << " ";

     //output:1 2 3 4 5 6 12   
    cout<<endl;
    cout<<"loop by iterator 1----------------------"<<endl;
    for (auto it = s.begin(); it != s.end(); ++it) {
        cout << *it << " ";
    } 
    cout<<endl<<"loop by iterator 2----------------------"<<endl;
    for (auto it = s.rbegin(); it != s.rend(); ++it) {
    std::cout << *it << " "; 
    }
    cout<<endl;

    /*
    Output:
    loop by iterator 1----------------------
    1 2 3 4 5 6 12 
    loop by iterator 2----------------------
    12 6 5 4 3 2 1 
    */
    //lowerbound upperbound and reverse iterator not for unordered set
    return 0;
}
