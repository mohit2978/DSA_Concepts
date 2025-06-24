
#include <bits/stdc++.h>
using namespace std;

class Solution{
public:
    int subarraySum(vector<int> &nums, int k){
        unordered_map<int,int> mp;
        int sum=0;
        int cnt=0;
        for(int n:nums){
            sum+=n;
            if(sum==k) cnt++;
            if(mp.find(sum-k)!=mp.end()) cnt+=mp[sum-k];
            mp[sum]++;
        }
        return cnt;
    }
};