/*
Given two integer arrays, val and wt, each of size N, which represent the 
values and weights of N items respectively, and an integer W representing the maximum 
capacity of a knapsack, determine the maximum value achievable by selecting a subset of the
 items such that the total weight of the selected items does not exceed the knapsack capacity W.



Each item can either be picked in its entirety or not picked at all (0-1 property). 
The goal is to maximize the sum of the values of the selected items while keeping the total weight within the knapsack's capacity.


Examples:
Input: val = [60, 100, 120], wt = [10, 20, 30], W = 50

Output: 220

Explanation: Select items with weights 20 and 30 for a total value of 100 + 120 = 220.

Input: val = [10, 40, 30, 50], wt = [5, 4, 6, 3], W = 10

Output: 90

Explanation: Select items with weights 4 and 3 for a total value of 40 + 50 = 90.

*/

#include <bits/stdc++.h>
using namespace std;

class Solution
{

    int solveKS(vector<int>& wt, vector<int>& val, int n, int W,int i){
        if(i<0 || W==0){
            return 0;
        }

        int v1=0;
        if(W>=wt[i]) v1=val[i]+solveKS(wt,val,n,W-wt[i],i-1);
        int v2=solveKS(wt,val,n,W,i-1);

        return max(v1,v2);

    }

public:
    int knapsack01(vector<int>& wt, vector<int>& val, int n, int W) {
        vector<vector<int>>dp(n,vector<int>(W+1,-1));
        return solveKS(wt,val,n,W,n-1);
    }

};