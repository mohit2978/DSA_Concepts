#include <bits/stdc++.h>
using namespace std;

class Solution{ 
    bool subsetSum(vector<int>&arr, int tar,int i,vector<vector<int>> &dp){
        if(i==arr.size() || tar==0){
            return dp[i][tar]=(tar==0?true:false);
        }

        if(dp[i][tar]!=-1) return dp[i][tar];
        bool v1=false;
        bool v2=false;

        if(tar>=arr[i]) v1=subsetSum(arr,tar-arr[i],i+1,dp);
        v2=subsetSum(arr,tar,i+1,dp);

        return dp[i][tar]=v1 |v2;

    }  
public:
    bool isSubsetSum(vector<int>arr, int target){
        vector<vector<int>> dp(arr.size()+1, vector<int>(target + 1, -1));
        return subsetSum(arr,target,0,dp);
    }
};