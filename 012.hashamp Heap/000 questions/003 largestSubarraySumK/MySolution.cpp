
#include <bits/stdc++.h>
using namespace std;

class Solution{
public:
    int longestSubarray(vector<int> &nums, int k){
        unordered_map<int,int> mp;
        int sum=0;
        int res=0;
        for(int i=0;i<nums.size();i++){
            int n=nums[i];
            sum+=n;
            if(sum==k) res=max(res,i+1);
            if(mp.find(sum-k)!=mp.end()) res=max(i-mp[sum-k],res);
            if(mp.find(sum)==mp.end()) mp[sum]=i;
        }
        return res;
    }
};
