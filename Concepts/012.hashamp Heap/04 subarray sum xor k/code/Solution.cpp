#include <bits/stdc++.h>
using namespace std;

class Solution{
public:
    int subarraysWithXorK(vector<int> &nums, int k) {
        int xorK=0;
        int cnt=0;
        unordered_map<int,int>mp;
        for(int n:nums){
            xorK=xorK^n;
            if(xorK==k) cnt++;
            if(mp.find(xorK^k)!=mp.end()) cnt+=mp[xorK^k];
            mp[xorK]++;
        }
        return cnt;
    }
};

/* 
 we know if a^b=c then can write a^c=b or b^c=a
 
 we have calculated xorK and suppose some value prev be a 

 so after a till xorK value be b

 so a^b=xorK

 Now b is our subarray's xor value let it be k so b we want to find 

 so a^k= xorK

 or can say xorK^k =a 

 so if we find out a then there be subarray that has value k from a to xorK

*/