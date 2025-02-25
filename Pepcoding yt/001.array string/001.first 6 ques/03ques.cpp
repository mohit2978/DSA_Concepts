#include<bits/stdc++.h>
using namespace std;
int getSumInRange(vector<int>&vec, int n,vector<vector<int>>updates){

    for(vector<int> v: updates){
        int s=v[0];
        int e=v[1];
        int val=v[2];
        vec[s]=val;
        vec[e+1]=-val;
    }
}

void getPrefixSum(vector<int>&v){

    for(int i=1;i<v.size();i++){
        v[i]=v[i-1]+v[i];
    }
}

void print(vector<int>& v){
    for(int val :v){
        cout<<val<<" ";
    }
    cout<<endl;
}

int main(){
    vector<int>v(6,0); 
    vector<vector<int>>updates ={{1,3,2},{2,4,3},{0,2,-2}};
    getSumInRange(v,5,updates);
    getPrefixSum(v);
    print(v);
    return 0;
}
