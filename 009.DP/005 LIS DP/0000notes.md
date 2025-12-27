# Notes

LIS (Longest Increasing subsequence)

## O(n^2) approach


```cpp

class Solution {
public:
    int LIS(vector<int>& nums) {
        int n=nums.size();
        int res=1;
        vector<int> dp(n,1);
        for(int i=1;i<n;i++){

            for(int j=i-1;j>=0;j--){
                if(nums[i]>nums[j]){
                    dp[i]=max(dp[i],dp[j]+1);
                }
            }

            res=max(dp[i],res);
        }

        return res;
    }    
};

```

We know what subsequence is so har peeche vale element pe jake check kia hmne jo chota hai uski 
value add kr di

## O(nlogn) approach

```cpp

class Solution {
public:
    int LIS(vector<int>& nums) {
        int n=nums.size();
        vector<int> temp;
        temp.push_back(nums[0]);
        for(int i=1; i < n; i++) {
            if(nums[i] > temp.back()) 
                temp.push_back(nums[i]); 
            else {
                int ind = lower_bound(temp.begin(), temp.end(), nums[i]) -temp.begin();
                temp[ind] = nums[i];
            }    
            
        }
        return temp.size();
    }    
};

````

In C++, `std::lower_bound (from <algorithm>)` is used to find the first position in a sorted range where a given value x could be inserted without breaking the order.

Syntax-->`auto it = lower_bound(begin, end, x);`


begin, end → iterators of the range (must be sorted in ascending order).

x → the value you are searching for.

Returns an iterator pointing to the first element that is `≥ x.`

If all elements are `< x`, it returns end.



## Extra About LIs

LIS can be solved by recursion memoization ,select not select way as we need 
subsequenece ,so select not select is way to get subsequence

```cpp
#include <bits/stdc++.h>
using namespace std;

class Solution {
private:

    int func(int i, int prevInd, vector<int> &arr) {
        if(i == arr.size() - 1) {
            if(prevInd == -1 || arr[prevInd] < arr[i]) return 1;
            return 0;
        }
        
        int notTake = func(i+1, prevInd, arr);
        
        int take = 0;
        // If no element is chosen till now
        if(prevInd == -1)
            take = func(i+1, i, arr) + 1;
        
        /* Else the current element can be 
        taken if it is strictly increasing */
        else if(arr[i] > arr[prevInd])
            take = func(i+1, i, arr) + 1;
        // Return the maximum length obtained from both cases
        return max(take, notTake);
    }
    
public:
    int LIS(vector<int>& nums) {
        return func(0, -1, nums);
    }    
};


int main() {
    vector<int> nums = {10, 9, 2, 5, 3, 7, 101, 18};
    Solution sol;
    int lengthOfLIS = sol.LIS(nums);

    cout << "The length of the LIS for the given array is: " << lengthOfLIS << endl;
    
    return 0;
}
```
Complexity Analysis:
Time Complexity: O(2^N), where N represents the number of elements in the given array.
In each function call, two recursive calls are made (take and not take) resulting in an exponential time complexity.

Space Complexity: O(N), because of the recursion stack space.

Apply memoization to this

```cpp
#include <bits/stdc++.h>
using namespace std;

class Solution {
private:
    // Helper function to find the length of LIS
    int func(int i, int prevInd, vector<int> &arr, vector<vector<int>> &dp) {
        
        // base case
        if(i == arr.size() - 1) {
            if(prevInd == -1 || arr[prevInd] < arr[i]) return 1;
            return 0;
        }
        
        // If subproblem is already calculated
        if(dp[i][prevInd + 1] != -1) return dp[i][prevInd + 1];
        
        // Not Take case
        int notTake = func(i+1, prevInd, arr, dp);
        
        int take = 0; // Take case
        
        // If no element is chosen till now
        if(prevInd == -1)
            take = func(i+1, i, arr, dp) + 1;
        
        /* Else the current element can be 
        taken if it is strictly increasing */
        else if(arr[i] > arr[prevInd])
            take = func(i+1, i, arr, dp) + 1;
        
        // Return the maximum length obtained from both cases
        return dp[i][prevInd + 1] = max(take, notTake);
    }
    
public:
    /* Function to find the longest increasing 
    subsequence in the given array */
    int LIS(vector<int>& nums) {
        int n = nums.size();
        
        // DP array
        vector<vector<int>> dp(n, vector<int>(n+1, -1));
        
        return func(0, -1, nums, dp);
    }    
};


int main() {
    vector<int> nums = {10, 9, 2, 5, 3, 7, 101, 18};
    
    // Creating an object of Solution class
    Solution sol;
    int lengthOfLIS = sol.LIS(nums);
    
    cout << "The length of the LIS for the given array is: " << lengthOfLIS << endl;
    
    return 0;
}


```


Print LIs O(n^2)

O(nlgn) cannot print LIS

```cpp

class Solution {
  public:
    vector<int> longestIncreasingSubsequence(vector<int>& nums) {
    int n=nums.size();
        int res=1;
        int resIdx=0;//should be zero for decreasing subsequence
        vector<int> dp(n,1);
        vector<int>par(n,0);
        for(int i=1;i<n;i++){
            par[i]=i;
            for(int j=i-1;j>=0;j--){
                if(nums[i]>nums[j]){
                    if(dp[j]+1>=dp[i]){
                        dp[i]=dp[j]+1;
                        par[i]=j;
                    }
                }
            }

            if(dp[i]>res){
                res=dp[i];
                resIdx=i;
            }
        }

        vector<int> resArr;

        int k=resIdx;

        while(par[k]!=k){
            resArr.push_back(nums[k]);
            k=par[k];
        }
         resArr.push_back(nums[k]);
        reverse(resArr.begin(),resArr.end());

        return resArr;
}
};

```


## Number of LIS 


```cpp

class Solution {
public:
    int numberOfLIS(vector<int> nums) {
        int n=nums.size();
        int res=1;
        vector<int> dp(n,1);
        vector<int>num(n,1);
        for(int i=1;i<n;i++){

            for(int j=i-1;j>=0;j--){
                if(nums[i]>nums[j]){
                    if(dp[j]+1>dp[i]){
                        dp[i]=dp[j]+1;
                        num[i]=num[j];
                    }else if(dp[j]+1==dp[i]){
                        num[i]+=num[j];
                    }
                }
            }

            res=max(dp[i],res);
        }
        int ans=0;
        for(int i=0;i<n;i++){
            if(dp[i]==res) ans+=num[i];
        }
        return ans;
    }
};

```

So both approaches are very important O(n^2) and O(nlgn)






