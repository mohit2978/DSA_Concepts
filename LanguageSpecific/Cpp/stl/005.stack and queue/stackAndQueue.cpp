#include<bits/stdc++.h>
using namespace std;

int main(){
        stack<int> s;
        s.push(10);
        s.emplace(20); // Emplace is similar to push but more effiecient
        cout << "Size: " << s.size() << endl;
        cout << "Top element: " << s.top() << endl;
        //top gives top element without removing it
        //Size: 2
        //Top element: 20

        s.pop();
        cout << "Size: " << s.size() << endl;
        cout << "Top element: " << s.top() << endl;
        //Size: 1
        //Top element: 10

        //queue is just behavior different than stack but same functions
        cout<<"Queue-----------------------------------"<<endl;
        queue<int> q;
        q.push(10);
        q.emplace(20); // Emplace is similar to push but more effiecient
        cout << "Size: " << q.size() << endl;
        cout << "front element: " << q.front() << endl;
        //front gives front element without removing it (only different function here)
       

        q.pop();
        cout << "Size: " << q.size() << endl;
        cout << "front element: " << q.front() << endl;
        /*
        Queue-----------------------------------
        Size: 2
        front element: 10
        Size: 1
        front element: 20
        */
        
    return 0;
    }