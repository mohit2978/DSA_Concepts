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













