#include <bits/stdc++.h>
using namespace std;

class Solution
{

    int solveKS(vector<int>& wt, vector<int>& val, int n, int W,int i,vector<vector<int>>&dp){
        if(i<0 || W==0){
            return 0;
        }
        if(dp[i][W]!=-1) return dp[i][W];

        int v1=0;
        if(W>=wt[i]) v1=val[i]+solveKS(wt,val,n,W-wt[i],i-1,dp);
        int v2=solveKS(wt,val,n,W,i-1,dp);

        return dp[i][W]=max(v1,v2);

    }

public:
    int knapsack01(vector<int>& wt, vector<int>& val, int n, int W) {
        vector<vector<int>>dp(n,vector<int>(W+1,-1));
        return solveKS(wt,val,n,W,n-1,dp);
    }

};