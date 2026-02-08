# Notes
![alt text](<002 continued revision _231121_163402.jpg>)

![alt text](<002 continued revision _231121_163402(1).jpg>) ![alt text](<002 continued revision _231121_163402(2).jpg>)

# Frog Jump with K Distances

### Problem Description
There are `n` stones and an array `height` where `height[i]` is the height of the $i^{th}$ stone. A frog is initially at the $1^{st}$ stone ($0^{th}$ index) and wants to reach the $n^{th}$ stone ($(n-1)^{th}$ index).

From the $i^{th}$ stone, the frog can jump to any stone $j$ such that $i + 1 \le j \le i + k$. The cost of a jump from the $i^{th}$ stone to the $j^{th}$ stone is $|height[i] - height[j]|$.

Your task is to find the minimum total cost required for the frog to reach the $n^{th}$ stone.

---

### Input Format
* An integer `n` representing the number of stones.
* An array `height` of size `n`.
* An integer `k` representing the maximum jump distance.

### Output Format
* Return the minimum total cost.

---

### Examples

**Example 1**
**Input:** `n = 4`, `height = [10, 30, 40, 50]`, `k = 2`  
**Output:** `40`  
**Explanation:** 1. Stone 0 to 1: $|10 - 30| = 20$
2. Stone 1 to 3: $|30 - 50| = 20$  
Total cost: $20 + 20 = 40$.

**Example 2**
**Input:** `n = 5`, `height = [10, 40, 50, 20, 60]`, `k = 3`  
**Output:** `50`  
**Explanation:**
1. Stone 0 to 1: $|10 - 40| = 30$
2. Stone 1 to 4: $|40 - 60| = 20$  
Total cost: $30 + 20 = 50$.

---

### Constraints
* $1 \le n \le 10^5$
* $1 \le k \le 100$
* $1 \le height[i] \le 10^4$


```cpp
class Solution {
    int helper(vector<int>& heights, int k,vector<int> &dp,int idx){
        if(idx==0){
            return dp[idx]= 0;
        }
        if(dp[idx]!=-1) return dp[idx];
        int val=1e9;;
        for(int i=1;i<=k && idx-i>=0;i++){
            int sum=abs(heights[idx]-heights[idx-i]);
            sum+=helper(heights,k,dp,idx-i);
            val=min(sum,val);
        }
        return dp[idx]=val;

    }
public:
    int frogJump(vector<int>& heights, int k) {
        int n=heights.size();
        vector<int> dp(n,-1);
        return helper(heights,k,dp,n-1);
    }
};


```

There is similar problem where frog takes 2 jumps only so just put k=2;

```cpp
class Solution {
public:
     int helper(vector<int>& heights, int k,vector<int> &dp,int idx){
        if(idx==0){
            return dp[idx]= 0;
        }
        if(dp[idx]!=-1) return dp[idx];
        int val=1e9;;
        for(int i=1;i<=k && idx-i>=0;i++){
            int sum=abs(heights[idx]-heights[idx-i]);
            sum+=helper(heights,k,dp,idx-i);
            val=min(sum,val);
        }
        return dp[idx]=val;

    }
    int frogJump(vector<int>& heights) {
        int n=heights.size();
        vector<int> dp(n,-1);
        return helper(heights,2,dp,n-1);
    }
};
```


 ![alt text](<002 continued revision _231121_163402(3).jpg>) ![alt text](<002 continued revision _231121_163402(4).jpg>) ![alt text](<002 continued revision _231121_163402(5).jpg>) ![alt text](<002 continued revision _231121_163402(6).jpg>) ![alt text](<002 continued revision _231121_163402(7).jpg>) ![alt text](<002 continued revision _231121_163402(8).jpg>) ![alt text](<002 continued revision _231121_163402(9).jpg>) ![alt text](<002 continued revision _231121_163402(10).jpg>) ![alt text](<002 continued revision _231121_163402(11).jpg>) ![alt text](<002 continued revision _231121_163402(12).jpg>) ![alt text](<002 continued revision _231121_163402(13).jpg>) ![alt text](<002 continued revision _231121_163402(14).jpg>) ![alt text](<002 continued revision _231121_163402(15).jpg>) ![alt text](<002 continued revision _231121_163402(16).jpg>) ![alt text](<002 continued revision _231121_163402(17).jpg>) ![alt text](<002 continued revision _231121_163402(18).jpg>) ![alt text](<002 continued revision _231121_163402(19).jpg>) ![alt text](<002 continued revision _231121_163402(20).jpg>) ![alt text](<002 continued revision _231121_163402(21).jpg>) ![alt text](<002 continued revision _231121_163402(22).jpg>) ![alt text](<002 continued revision _231121_163402(23).jpg>) ![alt text](<002 continued revision _231121_163402(24).jpg>) ![alt text](<002 continued revision _231121_163402(25).jpg>)