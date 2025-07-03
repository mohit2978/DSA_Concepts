#include <bits/stdc++.h>
using namespace std;

class Solution{ 
    bool subsetSum(vector<int>&arr, int tar,int i){
        if(i==arr.size() || tar==0){
            return tar==0?true:false;
        }

        bool v1=false;
        bool v2=false;

        if(tar>=arr[i]) v1=subsetSum(arr,tar-arr[i],i+1);
        v2=subsetSum(arr,tar,i+1);

        return v1 |v2;

    }  
public:
    bool isSubsetSum(vector<int>arr, int target){

        return subsetSum(arr,target,0);
    }
};