# Notes

![alt text](<009 target set_231121_163402.jpg>)
![alt text](<009 target set_231121_163402(1).jpg>) 
![alt text](<009 target set_231121_163402(2).jpg>) 

### Recursion
```cpp
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

```

### Memoization

```cpp
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
```

![alt text](<009 target set_231121_163402(3).jpg>) ![alt text](<009 target set_231121_163402(4).jpg>) ![alt text](<009 target set_231121_163402(5).jpg>) ![alt text](<009 target set_231121_163402(6).jpg>) ![alt text](<009 target set_231121_163402(7).jpg>) ![alt text](<009 target set_231121_163402(8).jpg>) ![alt text](<009 target set_231121_163402(9).jpg>) ![alt text](<009 target set_231121_163402(10).jpg>) ![alt text](<009 target set_231121_163402(11).jpg>) ![alt text](<009 target set_231121_163402(12).jpg>) ![alt text](<009 target set_231121_163402(13).jpg>) ![alt text](<009 target set_231121_163402(14).jpg>) ![alt text](<009 target set_231121_163402(15).jpg>) ![alt text](<009 target set_231121_163402(16).jpg>) ![alt text](<009 target set_231121_163402(17).jpg>) ![alt text](<009 target set_231121_163402(18).jpg>) ![alt text](<009 target set_231121_163402(19).jpg>) ![alt text](<009 target set_231121_163402(20).jpg>)

### Recursion

```cpp
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
```

### Memoization
```cpp
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
```


![alt text](<009 target set_231121_163402(21).jpg>) ![alt text](<009 target set_231121_163402(22).jpg>) ![alt text](<009 target set_231121_163402(23).jpg>) ![alt text](<009 target set_231121_163402(24).jpg>) ![alt text](<009 target set_231121_163402(25).jpg>) ![alt text](<009 target set_231121_163402(26).jpg>) ![alt text](<009 target set_231121_163402(27).jpg>) ![alt text](<009 target set_231121_163402(28).jpg>) ![alt text](<009 target set_231121_163402(29).jpg>) ![alt text](<009 target set_231121_163402(30).jpg>) ![alt text](<009 target set_231121_163402(31).jpg>)








