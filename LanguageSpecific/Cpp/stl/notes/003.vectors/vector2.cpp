#include<iostream>
#include<vector>
using namespace std;
int main(){
    vector<int>v(5,3);
    for (auto x:v) cout<<x<<" ";
    cout<<endl;
    /*
    output: 3 3 3 3 3  
    5 sized vector all having value 3
    */
    //2d vector 5*3 5 vectors each of size 3 with value 1,2,3,4,5 within each vector
    vector<vector<int>>v2d;
    for(int i=1;i<=5;i++){
        vector<int>v1(3,i);
        v2d.push_back(v1);
    }
    for(auto v1d:v2d){
        for(auto x:v1d){
            cout<<x<<" ";
        }
        cout<<endl;
    }
    /*
    output:
1 1 1 
2 2 2 
3 3 3 
4 4 4 
5 5 5 
    */
    return 0;
}