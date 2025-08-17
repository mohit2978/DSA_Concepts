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







