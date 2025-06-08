#include <bits/stdc++.h>
using namespace std;
void print(list<int> &lst){
    for (int i : lst) {
         cout << i << " ";
        }
    cout<<"\n";    
}      
int main() {
    //list is doubly linked list
    list<int> lst;
    lst.push_front(20);
    lst.emplace_front(10);  // Constructs 10 at the beginning
    print(lst);
    cout << "Front element: " << lst.front()<<"\n";
    /*
    Output:
    10 20 
    Front element: 10
    */
    list<int>l{1,2,3,4,5,6,7};
    l.push_back(101);
    l.push_front(303);
    print(l);
    /*
    Output: 303 1 2 3 4 5 6 7 101 
    */
    //pop_front() removes from front and pop_back() pops from back of list ,size() tells size 
    //front() return value of front element
    //back() returns value of back element
    return 0;
 }