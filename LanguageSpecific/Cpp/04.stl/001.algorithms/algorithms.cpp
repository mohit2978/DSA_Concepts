#include <bits/stdc++.h>
using namespace std;

template <typename T>
void print(vector<T>&v){
    for (T i:v){
        cout<<i <<" ";
    }
    cout<<"\n";
}

// Overloaded version for vector<pair>
template <typename T1, typename T2>
void print(vector<pair<T1, T2>>& v) {
    for (const auto& p : v) {
        cout << "(" << p.first << ", " << p.second << ") "; // Prints pairs
    }
    cout << "\n";
}
int main(){
    vector<int>v{5,4,3,2,1};
    sort(v.begin(),v.end());
    print(v); // 1 2 3 4 5 
    sort(v.begin(),v.end(),greater<>());
    print(v);//5 4 3 2 1 
    sort(v.begin(),v.end(), [](const auto &a, const auto &b) { return a < b; });// sorts ascending order
    print(v); // 1 2 3 4 5 


    vector<pair<int,int>>v1{
        {1,2},{100,1},{1,100},{1,200},{3, 5}, {3, 2}, {2, 4}, {2, 1}, {1, 7}
        };

        
    sort(v1.begin(), v1.end(), [](pair<int, int>& a,  pair<int, int>& b) {
        if (a.first == b.first) {
            return a.second < b.second; // Compare second elements if first are equal
        }
        return a.first > b.first; // Compare first elements
    });   

    print(v1);//(100, 1) (3, 2) (3, 5) (2, 1) (2, 4) (1, 2) (1, 7) (1, 100) (1, 200) 

    //can see lambdas in cpp yashvant kanetkar 
    return 0;
}