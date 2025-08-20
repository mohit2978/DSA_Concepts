# Notes

LIS (Longest Increasing subsequence)

O(n^2) approach


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
















