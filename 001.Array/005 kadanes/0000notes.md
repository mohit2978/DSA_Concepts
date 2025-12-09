# Notes

## Q1 simple kadanes

![alt text](image.png)


![alt text](image-1.png)


in here qw choose whether we choose arr[i] singly or sum+arr[i] at every step,
arr[i] will be choosen anyway as we need subarray 

In subsequence we have choice to choose between arr[i] or not

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

## Q2 max produxt subarray

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

## Q3 Maximum Sum Circular Subarray

Link--> https://leetcode.com/problems/maximum-sum-circular-subarray/description/

Given a **circular integer array** `nums` of length `n`, return the **maximum possible sum** of a non-empty subarray of `nums`.

A **circular array** means the end of the array connects to the beginning of the array. Formally, the next element of `nums[i]` is `nums[(i + 1) % n]` and the previous element of `nums[i]` is `nums[(i - 1 + n) % n]`.

A subarray may only include each element of the fixed buffer `nums` **at most once**. Formally, for a subarray `nums[i], nums[i + 1], ..., nums[j]`, there does not exist $i \le k_1, k_2 \le j$ with $k_1 \pmod n = k_2 \pmod n$.

**Example 1:**
Input: `nums = [1,-2,3,-2]`
Output: `3`
Explanation: Subarray `[3]` has maximum sum 3.

**Example 2:**
Input: `nums = [5,-3,5]`
Output: `10`
Explanation: Subarray `[5,5]` has maximum sum 5 + 5 = 10.

**Example 3:**
Input: `nums = [-3,-2,-3]`
Output: `-2`
Explanation: Subarray `[-2]` has maximum sum -2.

**Constraints:**
- $n = \text{nums.length}$
- $1 \le n \le 3 \times 10^4$
- $-3 \times 10^4 \le \text{nums}[i] \le 3 \times 10^4$


```java
class Solution {
    public int maxSubarraySumCircular(int[] nums) {
        int cmax=nums[0];
        int cmin=nums[0];
        int gmax=nums[0];
        int gmin=nums[0];
        int sum=nums[0];
        for(int i=1;i<nums.length;i++){
            cmax=Math.max(cmax+nums[i],nums[i]);
            gmax=Math.max(gmax,cmax);
            
            cmin=Math.min(cmin+nums[i],nums[i]);
            gmin=Math.min(gmin,cmin);
            
            sum+=nums[i];
        }
        
        return sum==gmin?gmax:Math.max(gmax,sum-gmin);
    }
}
```