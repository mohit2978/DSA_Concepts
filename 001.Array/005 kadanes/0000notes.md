# Notes

![alt text](image.png)


![alt text](image-1.png)


```cpp

class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        int mxsum=-(1e4+1);
        int sum=-(1e4+1);
        for(int n:nums){
            sum=max(sum+n,n);
            mxsum=max(sum,mxsum);
        }
        return mxsum;
    }
};
```

see constarints above we have put -(10^4+1) as -(10^4) is max nums[i] can get 


if you put -(1e9) then something is added in it say -(1e9)+-(1e3) that will circle back in positive range and give positive answer so do not put any value ,just check for constarints


![alt text](image-2.png)


```cpp

class Solution {
public:
    int maxProduct(vector<int>& nums) {
        int mxp=nums[0];
        int mnp=nums[0];
        int prevmxp=nums[0];
        int prevmnp=nums[0];
        int n=nums.size();
        int res=nums[0];
        for(int i=1;i<n;i++){
            mxp=max({prevmxp*nums[i],prevmnp*nums[i],nums[i]});
            mnp=min({prevmxp*nums[i],prevmnp*nums[i],nums[i]});
            prevmnp=mnp;
            prevmxp=mxp;
            res=max(mxp,res);
        }

        return res;
    }
};
```
Time Complexity:O(n) due to a single for loop iterating through the input vector.

Space Complexity:O(1) as it uses a constant amount of extra space regardless of the input size.


now if you do not use prevmnp and prevmxp then see then code

```cpp

class Solution {
public:
    int maxProduct(vector<int>& nums) {
        int mxp=nums[0];
        int mnp=nums[0];
        int n=nums.size();
        int res=nums[0];
        for(int i=1;i<n;i++){
            mxp=max({mxp*nums[i],mnp*nums[i],nums[i]});
            mnp=min({mxp*nums[i],mnp*nums[i],nums[i]});
            res=max(mxp,res);
        }

        return res;
    }
};
```

i=1 we run this `mxp=max({mxp*nums[i],mnp*nums[i],nums[i]});` now when we run `mnp=min({mxp*nums[i],mnp*nums[i],nums[i]});` then mxp we just updated but we need prev mxp!! so thats why we store that in a variable.