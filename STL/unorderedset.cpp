#include<bits/stdc++.h>
using namespace std;

int main() {
    unordered_set<int> mySet = {10, 20, 30};
     //lowerbound upperbound and reverse iterator in set  not for unordered set
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

    cout<<endl;

   vector<int> v = {1, 2, 3,3,4,5,6,1,1,1,1,12,2,2};
    unordered_set<int> s(v.begin(), v.end());

    for (int x : s)
        cout << x << " ";

     //output:1 2 3 4 5 6 12   
    cout<<endl;
    cout<<"loop by iterator 1----------------------"<<endl;
    for (auto it = s.begin(); it != s.end(); ++it) {
        cout << *it << " ";
    } 
 
    cout<<endl;

    /*
    Output:
   50 40 10 30 
    12 6 5 4 3 2 1 
    loop by iterator 1----------------------
    12 6 5 4 3 2 1 
    */

    return 0;
}
