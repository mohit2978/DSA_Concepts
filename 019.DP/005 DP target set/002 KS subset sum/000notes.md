
# O/1 KS

 ![alt text](<009 target set_231121_163402(16).jpg>) ![alt text](<009 target set_231121_163402(17).jpg>) ![alt text](<009 target set_231121_163402(18).jpg>) ![alt text](<009 target set_231121_163402(19).jpg>) ![alt text](<009 target set_231121_163402(20).jpg>)

### Recursion

```cpp


#include <bits/stdc++.h>
using namespace std;

class Solution
{

    int solveKS(vector<int>& wt, vector<int>& val, int n, int W,int i){
        if(i<0 || W==0){
            return 0;
        }

        int v1=0;
        if(W>=wt[i]) v1=val[i]+solveKS(wt,val,n,W-wt[i],i-1);
        int v2=solveKS(wt,val,n,W,i-1);

        return max(v1,v2);

    }

public:
    int knapsack01(vector<int>& wt, vector<int>& val, int n, int W) {
        vector<vector<int>>dp(n,vector<int>(W+1,-1));
        return solveKS(wt,val,n,W,n-1);
    }

};
```

### Memoization
```cpp
#include <bits/stdc++.h>
using namespace std;

class Solution
{

    int solveKS(vector<int>& wt, vector<int>& val, int n, int W,int i,vector<vector<int>>&dp){
        if(i<0 || W==0){
            return 0;
        }
        if(dp[i][W]!=-1) return dp[i][W];

        int v1=0;
        if(W>=wt[i]) v1=val[i]+solveKS(wt,val,n,W-wt[i],i-1,dp);
        int v2=solveKS(wt,val,n,W,i-1,dp);

        return dp[i][W]=max(v1,v2);

    }

public:
    int knapsack01(vector<int>& wt, vector<int>& val, int n, int W) {
        vector<vector<int>>dp(n,vector<int>(W+1,-1));
        return solveKS(wt,val,n,W,n-1,dp);
    }

};
```



## We have extra base cases but to avoid that we use (n+1)(W+1) dp array 

This is much intuitive

```cpp
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int knapsack01(vector<int>& wt, vector<int>& val, int n, int W) {
        
        // STEP 1: Pad the DP table with an extra row (n + 1).
        // dp[0][...] naturally represents 0 items = 0 value.
        vector<vector<int>> dp(n + 1, vector<int>(W + 1, 0));

        // NO MANUAL BASE CASE NEEDED!
        
        // STEP 2: Start our item loop from 1. 
        // 'i' represents the number of items we are allowed to consider.
        for (int i = 1; i <= n; i++) {
            for (int j = 0; j <= W; j++) {
                
                // Option 1: Exclude the current item
                int exclude = dp[i - 1][j];

                // Option 2: Include the current item
                int include = 0;
                
                // STEP 3: Adjust the index for wt and val arrays to 'i - 1'.
                if (j >= wt[i - 1]) {
                    // THE ONLY DIFFERENCE FROM UNBOUNDED KNAPSACK:
                    // We look back at dp[i - 1] instead of dp[i] because we 
                    // only have ONE copy of this item. Once we take it, 
                    // we must move to the previous subset of items.
                    include = val[i - 1] + dp[i - 1][j - wt[i - 1]];
                }

                dp[i][j] = max(include, exclude);
            }
        }

        // Return the bottom-right corner of the padded table
        return dp[n][W]; 
    }
};
```


## Space Optimization — 0/1 Knapsack

### Why Space Can Be Optimized

```
dp[i][j] only depends on:
  dp[i-1][j]         ← directly above
  dp[i-1][j-wt[i-1]] ← above and to the left

We only ever look at the PREVIOUS row
Current row never looks at itself
→ we don't need the entire 2D table
→ just keep ONE row (previous row)
```

---

### The Key Insight

```
2D table:
      0    1    2    3    4    5   (capacity j)
i=0 [ 0    0    0    0    0    0 ]  ← previous row
i=1 [ 0    ?    ?    ?    ?    ? ]  ← current row
      ↑              ↑
   dp[i][j]     uses dp[i-1][j]
                and  dp[i-1][j-wt]

After filling row i=1:
  row i=0 is NEVER needed again
  throw it away, reuse the space
```

---

### Naive 1D Attempt — Why Forward Loop Fails

```cpp
// WRONG for 0/1 knapsack
for (int i = 1; i <= n; i++) {
    for (int j = 0; j <= W; j++) {   // ← forward loop WRONG
        if (j >= wt[i-1])
            dp[j] = max(dp[j], val[i-1] + dp[j - wt[i-1]]);
    }
}
```

```
Problem:
  when we compute dp[j]
  dp[j - wt[i-1]] might already be UPDATED in this iteration
  meaning we used item i TWICE → unbounded knapsack behavior ❌

Example:
  wt=[2], val=[3], W=4

  Forward loop:
  j=2: dp[2] = max(0, 3+dp[0]) = 3   ← item 0 used once
  j=4: dp[4] = max(0, 3+dp[2]) = 6   ← dp[2] already updated!
                                         item 0 used TWICE ❌

  Correct answer = 3 (can only use item once)
```

---

### Fix — Reverse Loop

```cpp
// CORRECT for 0/1 knapsack
for (int i = 1; i <= n; i++) {
    for (int j = W; j >= wt[i-1]; j--) {   // ← reverse loop ✅
        dp[j] = max(dp[j], val[i-1] + dp[j - wt[i-1]]);
    }
}
```

```
Why reverse works:
  when we compute dp[j]
  dp[j - wt[i-1]] has NOT been updated yet in this iteration
  (we're going right to left, j-wt is always to the LEFT)
  so we're reading from PREVIOUS iteration = previous row ✅

Example:
  wt=[2], val=[3], W=4

  Reverse loop:
  j=4: dp[4] = max(0, 3+dp[2]) = 3   ← dp[2] still 0 (old) ✅
  j=3: dp[3] = max(0, 3+dp[1]) = 3   ← dp[1] still 0 (old) ✅
  j=2: dp[2] = max(0, 3+dp[0]) = 3   ← dp[0] still 0 (old) ✅

  Correct answer = 3 ✅
```

---

### The Optimized Code

```cpp
int knapsack01(vector<int>& wt, vector<int>& val, int n, int W) {

    // single 1D array instead of 2D
    vector<int> dp(W + 1, 0);

    for (int i = 1; i <= n; i++) {
        // traverse RIGHT TO LEFT — critical for 0/1 knapsack
        for (int j = W; j >= wt[i-1]; j--) {
            int exclude = dp[j];                          // don't take item i
            int include = val[i-1] + dp[j - wt[i-1]];   // take item i
            dp[j] = max(exclude, include);
        }
    }

    return dp[W];
}
```


---

### 2D vs 1D Comparison

```
items: wt=[1,3,4,5], val=[1,4,5,7], W=7

2D table:
      0  1  2  3  4  5  6  7
i=0 [ 0  0  0  0  0  0  0  0 ]
i=1 [ 0  1  1  1  1  1  1  1 ]
i=2 [ 0  1  1  4  5  5  5  5 ]
i=3 [ 0  1  1  4  5  6  6  9 ]
i=4 [ 0  1  1  4  5  7  8  9 ]

1D array progression:
init: [0  0  0  0  0  0  0  0]
i=1:  [0  1  1  1  1  1  1  1]
i=2:  [0  1  1  4  5  5  5  5]
i=3:  [0  1  1  4  5  6  6  9]
i=4:  [0  1  1  4  5  7  8  9]

IDENTICAL row by row ✅
```

---

### 0/1 vs Unbounded — The One Difference

```
0/1 Knapsack:       Unbounded Knapsack:
  each item once      each item unlimited times

for(j = W to wt):   for(j = wt to W):
  REVERSE loop          FORWARD loop

Reverse → reads old values → item used once   ✅
Forward → reads new values → item used again  ✅
```

---


Great observation! Let me explain clearly.

---

### What Unbounded Knapsack Means

```
0/1 Knapsack:      each item can be used AT MOST ONCE
Unbounded Knapsack: each item can be used ANY NUMBER of times
```

---

### The Forward Loop Accidentally Does Unbounded

```
wt=[2], val=[3], W=4

dp = [0, 0, 0, 0, 0]   initially

i=1 (wt=2, val=3), FORWARD loop j=2 to 4:

j=2: dp[2] = max(dp[2], val + dp[2-2])
           = max(0,     3   + dp[0])
           = max(0,     3   + 0)
           = 3
     dp = [0, 0, 3, 0, 0]

j=3: dp[3] = max(dp[3], val + dp[3-2])
           = max(0,     3   + dp[1])
           = max(0,     3   + 0)
           = 3
     dp = [0, 0, 3, 3, 0]

j=4: dp[4] = max(dp[4], val + dp[4-2])
           = max(0,     3   + dp[2])
           = max(0,     3   + 3)     ← dp[2]=3 ALREADY UPDATED!
           = 6
     dp = [0, 0, 3, 3, 6]
```

**What just happened?**

```
dp[2] = 3 means "used item once at capacity 2"
dp[4] used dp[2] which was UPDATED in THIS iteration
     = "used item once at cap 2" + "use item again at cap 4"
     = item used TWICE ❌

This is EXACTLY unbounded knapsack behavior:
  "I can use same item again and again"
  dp[4] = 6 = using wt=2,val=3 item TWICE
```

---

### Unbounded Knapsack Intentionally Does This

```cpp
// Unbounded Knapsack — FORWARD loop intentional
for (int j = wt; j <= W; j++) {
    dp[j] = max(dp[j], val + dp[j - wt]);
}

// reading UPDATED values = reusing same item ✅ for unbounded
```

```
j=2: dp[2] = 3    (used item once)
j=4: dp[4] = 6    (used item twice) ← CORRECT for unbounded!
j=6: dp[6] = 9    (used item three times) ← CORRECT for unbounded!
```

---

### Reverse Loop Prevents This

```
wt=[2], val=[3], W=4

REVERSE loop j=4 to 2:

j=4: dp[4] = max(dp[4], val + dp[4-2])
           = max(0,     3   + dp[2])
           = max(0,     3   + 0)     ← dp[2] NOT YET updated ✅
           = 3

j=3: dp[3] = max(dp[3], val + dp[3-2])
           = max(0,     3   + dp[1])
           = max(0,     3   + 0)
           = 3

j=2: dp[2] = max(dp[2], val + dp[2-2])
           = max(0,     3   + dp[0])
           = max(0,     3   + 0)
           = 3

dp = [0, 0, 3, 3, 3]

answer = dp[4] = 3 ✅ item used only once
```

---

### Side by Side

```
Same item: wt=2, val=3, W=4

FORWARD (unbounded behavior):        REVERSE (0/1 behavior):
j=2: dp[2] = 3  (used once)         j=4: dp[4] = 3  (reads old dp[2]=0)
j=4: dp[4] = 6  (used TWICE ❌)     j=2: dp[2] = 3  (reads old dp[0]=0)

reads NEW dp[2]=3                    reads OLD dp[2]=0
= current row value                  = previous row value
= item reused ❌                     = item used once ✅
```

---

### The Core Reason

```
FORWARD loop:
  when computing dp[j]
  dp[j-wt] is to the LEFT
  already computed in THIS iteration
  = CURRENT row value
  = same item already counted
  = unbounded behavior ❌

REVERSE loop:
  when computing dp[j]
  dp[j-wt] is to the LEFT
  NOT yet computed in THIS iteration
  = PREVIOUS row value (old value)
  = same item NOT yet counted
  = 0/1 behavior ✅
```

---

### One Line Summary

```
Forward → reads updated values → item counted again → unbounded
Reverse → reads old values     → item counted once  → 0/1

The ONLY difference between 0/1 and unbounded
1D space optimized versions is:
  j from W  downto wt  → 0/1 knapsack
  j from wt upto   W   → unbounded knapsack
```

### Complexity

| | 2D Version | 1D Optimized |
|---|---|---|
| Time | O(n × W) | O(n × W) |
| Space | O(n × W) | O(W) |

Space reduced from O(n×W) to O(W) — same time complexity.




![alt text](<009 target set_231121_163402(21).jpg>) ![alt text](<009 target set_231121_163402(22).jpg>)

## Memoization

```cpp
class Solution
{
    int solveKS(vector<int>& wt, vector<int>& val, int n, int W,int i,vector<vector<int>>&dp){
        if(i<0 || W==0){
            return 0;
        }
        if(dp[i][W]!=-1) return dp[i][W];

        int v1=0;
        if(W>=wt[i]) v1=val[i]+solveKS(wt,val,n,W-wt[i],i,dp);
        int v2=solveKS(wt,val,n,W,i-1,dp);

        return dp[i][W]=max(v1,v2);

    }
    public:
   int unboundedKnapsack(vector<int>& wt, vector<int>& val, int n, int W) {
        vector<vector<int>>dp(n,vector<int>(W+1,-1));
        return solveKS(wt,val,n,W,n-1,dp);
       }
};


```
 bs jha select kia hai vha bhi aage mt bdna!!


## Tabulation

This tbaulation has nothing to do with above memoized approach!! 
This is just change made in 0-1 KS (n+1)(W+1) tabualtion approach!!

```cpp
class Solution {
	public:
	int knapSack(vector<int>& val, vector<int>& wt, int W) {
		int n = wt.size();
		vector<vector<int>> dp(n + 1, vector<int>(W + 1, 0));
		
		// Fill the rest of the table
		for (int i = 1; i <= n; i++) {
			for (int j = 0; j <= W; j++) {
				
				// Option 1: Not taking the current item
				int exclude = dp[i - 1][j];
				
				// Option 2: Taking the current item (if capacity allows)
				int include = 0;
				if (j >= wt[i - 1]) {
					include = val[i - 1] + dp[i][j - wt[i - 1]];
				}
				
				dp[i][j] = max(include, exclude);
			}
		}
		
		return dp[n][W];
		
	}
};
```

## Subset sum

![alt text](<009 target set_231121_163402.jpg>)

### Recursion
```cpp
#include <bits/stdc++.h>
using namespace std;

class Solution{ 
    bool subsetSum(vector<int>&arr, int tar,int i){
        if(i==arr.size() || tar==0){
            return tar==0?true:false;
        }

        bool v1=false;
        bool v2=false;

        if(tar>=arr[i]) v1=subsetSum(arr,tar-arr[i],i+1);
        v2=subsetSum(arr,tar,i+1);

        return v1 |v2;

    }  
public:
    bool isSubsetSum(vector<int>arr, int target){

        return subsetSum(arr,target,0);
    }
};

```

### Memoization

```cpp
#include <bits/stdc++.h>
using namespace std;

class Solution{ 
    bool subsetSum(vector<int>&arr, int tar,int i,vector<vector<int>> &dp){
        if(i==arr.size() || tar==0){
            return dp[i][tar]=(tar==0?true:false);
        }

        if(dp[i][tar]!=-1) return dp[i][tar];
        bool v1=false;
        bool v2=false;

        if(tar>=arr[i]) v1=subsetSum(arr,tar-arr[i],i+1,dp);
        v2=subsetSum(arr,tar,i+1,dp);

        return dp[i][tar]=v1 |v2;

    }  
public:
    bool isSubsetSum(vector<int>arr, int target){
        vector<vector<int>> dp(arr.size()+1, vector<int>(target + 1, -1));
        return subsetSum(arr,target,0,dp);
    }
};
```

## Tabulation 

```cpp
#include <bits/stdc++.h>
using namespace std;

class Solution {
private:
    bool func(int n, int target, vector<int> &arr) {
        vector<vector<bool>> dp(n, vector<bool>(target + 1, false));

        for (int i = 0; i < n; i++) {
            dp[i][0] = true;
        }

        if (arr[0] <= target) {
            dp[0][arr[0]] = true;
        }

        for (int ind = 1; ind < n; ind++) {
            for (int i = 1; i <= target; i++) {
                bool notTaken = dp[ind - 1][i];
                bool taken = false;
                if (arr[ind] <= i) {
                    taken = dp[ind - 1][i - arr[ind]];
                }
                dp[ind][i] = notTaken || taken;
            }
        }

        return dp[n - 1][target];
    }
public:
    int isSubsetSum(vector<int> arr, int target) {
        return func(arr.size(), target, arr);
    }
};

int main() {
    vector<int> arr = {1, 2, 3, 4};
    int target = 4;

    Solution sol;

    if (sol.isSubsetSum(arr, target))
        cout << "Subset with the given target found";
    else
        cout << "Subset with the given target not found";

    return 0;
}
```
Remember tabulation of this problem it can be used in many other problems!!


## Tabulation using 0-1 KS approach

```cpp
class Solution {
  public:
    bool isSubsetSum(vector<int>& arr, int sum) {
        int n = arr.size();
		vector<vector<bool>> dp(n + 1, vector<bool>(sum + 1, false));
		
		//base case as can make zero sum without selecting any elemeny
		for(int i=0;i<=n;i++) dp[i][0]=true;
		

		for (int i = 1; i <= n; i++) {
			for (int j = 0; j <= sum; j++) {
				
				// Option 1: Not taking the current item
				bool exclude = dp[i - 1][j];
				
				// Option 2: Taking the current item (if capacity allows)
				int include = 0;
				if (j >= arr[i - 1]) {
					include =  dp[i-1][j - arr[i - 1]];
				}
				
				dp[i][j] = include| exclude;
			}
		}
		
		return dp[n][sum];
        
    }
};
```

## Count subset with sum K

```cpp
class Solution{
	int MOD=1e9+7;
	    int subsetSum(vector<int>&arr, int tar,int i,vector<vector<int>> &dp){
        if(i==arr.size() || tar==0){
            return dp[i][tar]=(tar==0?1:0);
        }

        if(dp[i][tar]!=-1) return dp[i][tar];
        int cnt=0;
        if(tar>=arr[i]) cnt=(cnt+subsetSum(arr,tar-arr[i],i+1,dp))%MOD;
        cnt=(cnt+subsetSum(arr,tar,i+1,dp))%MOD;

        return dp[i][tar]=cnt;

    }  
	public:
	int perfectSum(vector<int>&arr, int K){
   		vector<vector<int>> dp(arr.size()+1, vector<int>(K + 1, -1));
        return subsetSum(arr,K,0,dp);
	}
};

```





![alt text](<009 target set_231121_163402(7).jpg>) ![alt text](<009 target set_231121_163402(8).jpg>) 


```cpp
class Solution {
    bool subsetSum(vector<int> &arr, int tar, int i, vector<vector<int>> &dp) {
        if (i == arr.size() || tar == 0) {
            return dp[i][tar] = (tar == 0 ? true : false);
        }

        if (dp[i][tar] != -1) return dp[i][tar];
        bool v1 = false;
        bool v2 = false;

        if (tar >= arr[i]) v1 = subsetSum(arr, tar - arr[i], i + 1, dp);
        v2 = subsetSum(arr, tar, i + 1, dp);

        return dp[i][tar] = v1 | v2;
    }

    bool isSubsetSum(vector<int> arr, int target) {
        vector<vector<int>> dp(arr.size() + 1, vector<int>(target + 1, -1));
        return subsetSum(arr, target, 0, dp);
    }

   public:
    bool equalPartition(int n, vector<int> arr) {
        int sum = accumulate(arr.begin(), arr.end(),0);
        if (sum % 2 == 1) return false;
        return isSubsetSum(arr,sum/2);
    }
};

```




![alt text](<009 target set_231121_163402(9).jpg>) ![alt text](<009 target set_231121_163402(10).jpg>) 

# Partition a set into two subsets with minimum absolute sum difference

### Problem Statement
Given an array `arr` of `n` integers, partition the array into two subsets such that the absolute difference between their sums is minimized.

### Examples

**Example 1:**
```text
Input: arr = [1, 7, 14, 5]
Output: 1
Explanation: The array can be partitioned as [1, 7, 5] and [14], with an absolute difference of 1.
```
### Constraints
- $1 \leq n \cdot \text{sum of array elements} \leq 10^6$
- $0 < \text{arr}[i] \leq 10^4$

```cpp
class Solution {
    bool subsetSum(vector<int> &arr, int tar, int i, vector<vector<int>> &dp) {
        if (i == arr.size() || tar == 0) {
            return dp[i][tar] = (tar == 0 ? true : false);
        }

        if (dp[i][tar] != -1) return dp[i][tar];
        bool v1 = false;
        bool v2 = false;

        if (tar >= arr[i]) v1 = subsetSum(arr, tar - arr[i], i + 1, dp);
        v2 = subsetSum(arr, tar, i + 1, dp);

        return dp[i][tar] = v1 | v2;
    }

    int isSubsetSum(vector<int> arr, int target) {
        vector<vector<int>> dp(arr.size() + 1, vector<int>(target + 1, -1));
        for (int i = 0; i <= target / 2; i++) {
            subsetSum(arr, i, 0, dp);
        }
        int ans = 1e9;
        for (int i = 0; i <= target / 2; i++) {
            if (dp[0][i] == true) ans = min(target - 2 * i, ans);
        }
        return ans;
    }

   public:
    int minDifference(vector<int> &arr, int n) {
        int sum = accumulate(arr.begin(), arr.end(), 0);
        return isSubsetSum(arr, sum);
    }
};

```
Why i have this 
```cpp
 for (int i = 0; i <= target / 2; i++) {
            subsetSum(arr, i, 0, dp);
        }
```

### The "Lazy" Nature of Recursion (Memoization)

If we call `subsetSum(arr, sum, 0, dp)` once.

**Problem:** Top-Down DP (Recursion) is **"lazy."** It only computes the states necessary to find if `sum` is possible. It does **not** explore every possible subset sum.

**Example:**
* If you have `[1, 10]` and `sum = 11`.
* The recursion checks `11 - 1 = 10`, then `10 - 10 = 0`. It finds a path.
* It **never** checks if `sum = 5` is possible because the path to 11 never required asking *"Can I make 5?"*.

**Consequence:** Your DP table will have `-1` (unvisited) for many valid sums that just weren't part of the path to the total sum.


It will be accepted in interviews but AI suggested 
```cpp

int isSubsetSum(vector<int> arr, int target) {
    // Initialize DP table with -1
    // Size is [N+1][Sum+1]
    vector<vector<int>> dp(arr.size() + 1, vector<int>(target + 1, -1));
    
    int minDiff = 1e9;

    // Loop through all possible sums from 0 to Sum/2
    for (int i = 0; i <= target / 2; i++) {
        // DIRECTLY check if this sum 'i' is possible
        if (subsetSum(arr, i, 0, dp) == true) {
            // If possible, calculate the difference
            int s1 = i;
            int s2 = target - i;
            minDiff = min(minDiff, abs(s2 - s1));
        }
    }
    return minDiff;
}
```
# Count partitions with given difference

### Problem Statement
Given an array `arr` of `n` integers and an integer `diff`, count the number of ways to partition the array into two subsets $S_1$ and $S_2$ such that:

$$|S_1 - S_2| = \text{diff} \quad \text{and} \quad S_1 \geq S_2$$

Where $|S_1|$ and $|S_2|$ are the sum of subsets $S_1$ and $S_2$ respectively.

Return the result modulo $10^9 + 7$.

**Note:** A partition means that the union of $S_1$ and $S_2$ is the original array, and no element is left out or used twice — every element of the array belongs to exactly one of the two subsets.

---

### Examples

**Example 1**
```text
Input: arr = [1, 1, 2, 3], diff = 1
Output: 3
Explanation: The subsets are:
- [1, 2] and [1, 3]
- [1, 3] and [1, 2]
- [1, 1, 2] and [3]
```
### Example 2
```text
Input: arr = [1, 2, 3, 4], diff = 2
Output: 2
Explanation: The subsets are:
- [1, 3] and [2, 4]
- [1, 2, 3] and [4]
```
### Constraints
- $1 \leq n \leq 200$
- $0 \leq d \leq 10^4$
- $0 \leq \text{arr}[i] \leq 50$
### solution

#### Wrong code
```cpp
#include <bits/stdc++.h>
using namespace std;

class Solution {
    int MOD=1e9+7;
      int subsetSum(vector<int>&arr, int tar,int i,vector<vector<int>> &dp){
        if(i==arr.size() || tar==0){
            return dp[i][tar]=(tar==0?1:0);
        }

        if(dp[i][tar]!=-1) return dp[i][tar];
        int cnt=0;
        if(tar>=arr[i]) cnt=(cnt+subsetSum(arr,tar-arr[i],i+1,dp))%MOD;
        cnt=(cnt+subsetSum(arr,tar,i+1,dp))%MOD;

        return dp[i][tar]=cnt;

    }  
  int perfectSum(vector<int>&arr, int K){
      vector<vector<int>> dp(arr.size()+1, vector<int>(K + 1, -1));
        return subsetSum(arr,K,0,dp);
  }
  public:
   int countPartitions(int n, int diff, vector<int>& arr) {
        int sum=accumulate(arr.begin(),arr.end(),0);
        int tar=(sum+diff)/2;
        return perfectSum(arr,tar);
    }
};
```
### This code has 2 logical bugs that will cause it to fail on standard test cases (especially those involving zeros or odd sums).

Here is the breakdown of the errors and the corrected code.

---

### 1. The "Zeros" Trap (Critical Bug)
**Your base case is:** `if (i == arr.size() || tar == 0)`

* **The Bug:** You stop as soon as `tar == 0`.
* **The Scenario:** Imagine `arr = [0, 0, 1]` and `target = 1`.
    * If you pick `1`, target becomes `0`. Your code returns `1` immediately.
    * It misses the fact that you can also include the zeros! (e.g., `{1}`, `{0,1}`, `{0,0,1}`, etc.).
* **The Fix:** Do not stop when `tar == 0`. You must traverse the entire array (`i == n`) to ensure you count all combinations of zeros.

---

### 2. The "Odd Sum" Check (Wrong Answer)
**You calculate** `tar = (sum + diff) / 2`.

* **The Bug:** Integer division truncates.
* **The Scenario:** Sum = 10, Diff = 3. $(10+3)/2$ becomes 6. But mathematically, $2 \cdot S_1 = 13$, which is impossible for integers.
* **The Fix:** You must check if `((sum + diff) % 2 != 0)` and return `0`.

#### Right code
```cpp
#include <bits/stdc++.h>
using namespace std;

class Solution {
  	int MOD=1e9+7;
	    int subsetSum(vector<int>&arr, int tar,int i,vector<vector<int>> &dp){
        if(i==arr.size() ){
            return dp[i][tar]=(tar==0?1:0);
        }

        if(dp[i][tar]!=-1) return dp[i][tar];
        int cnt=0;
        if(tar>=arr[i]) cnt=(cnt+subsetSum(arr,tar-arr[i],i+1,dp))%MOD;
        cnt=(cnt+subsetSum(arr,tar,i+1,dp))%MOD;

        return dp[i][tar]=cnt;

    }  
	int perfectSum(vector<int>&arr, int K){
   		vector<vector<int>> dp(arr.size()+1, vector<int>(K + 1, -1));
        return subsetSum(arr,K,0,dp);
	}
  public:
   int countPartitions(int n, int diff, vector<int>& arr) {
        int sum=accumulate(arr.begin(),arr.end(),0);
        if ((sum + diff) % 2 != 0 || diff > sum) return 0;
        int tar=(sum+diff)/2;
        return perfectSum(arr,tar);
    }
};
```

# Target sum

![alt text](<009 target set_231121_163402(11).jpg>)

Same as above question

```cpp
class Solution {
  	int MOD=1e9+7;
	    int subsetSum(vector<int>&arr, int tar,int i,vector<vector<int>> &dp){
        if(i==arr.size() ){
            return dp[i][tar]=(tar==0?1:0);
        }

        if(dp[i][tar]!=-1) return dp[i][tar];
        int cnt=0;
        if(tar>=arr[i]) cnt=(cnt+subsetSum(arr,tar-arr[i],i+1,dp))%MOD;
        cnt=(cnt+subsetSum(arr,tar,i+1,dp))%MOD;

        return dp[i][tar]=cnt;

    }  
	int perfectSum(vector<int>&arr, int K){
   		vector<vector<int>> dp(arr.size()+1, vector<int>(K + 1, -1));
        return subsetSum(arr,K,0,dp);
	}

   int countPartitions( int diff, vector<int>& arr) {
        int sum=accumulate(arr.begin(),arr.end(),0);
        if ((sum + diff) % 2 != 0 || diff > sum) return 0;
        int tar=(sum+diff)/2;
        return perfectSum(arr,tar);
    } 
  public:
  int targetSum(int n, int target, vector<int>& arr) {
       return countPartitions(target,arr);
 }
};

```
### The "Negative Target" Crash

* **The Bug:** In LeetCode 494, the target can be negative (e.g., `target = -10`).
* **The Math:** If `target` is negative, `sum + target` might be negative.

**Example:**
* `arr = [1]`, `target = -5`.
* `sum = 1`.
* `tar = (1 + (-5)) / 2 = -2`.

* **The Crash:** You initialize `vector<int>(tar + 1)`. If `tar` is negative, this throws a `std::length_error` or crash.
* **The Fix:** You must check if `sum + diff < 0` (or equivalently `abs(target) > sum`) and return `0`.

Now let us see rajneesh way!!

 ![alt text](<009 target set_231121_163402(12).jpg>) ![alt text](<009 target set_231121_163402(13).jpg>) ![alt text](<009 target set_231121_163402(14).jpg>) 

# Lc 322 seen in prev lec
## Minimum Coins



---

### **Problem Statement**
Given an integer array of `coins` representing coins of different denominations and an integer `amount` representing a total amount of money.

Return the **fewest number of coins** that are needed to make up that amount.

If that amount of money cannot be made up by any combination of the coins, return `-1`.

**Note:** You may assume that you have an infinite number of each kind of coin.

---

### **Examples**

**Example 1**
```text
Input: coins = [1, 2, 5], amount = 11
Output: 3
Explanation: 11 = 5 + 5 + 1. We need 3 coins to make up the amount 11.
```
### Example 2
```text
Input: coins = [2, 5], amount = 3
Output: -1
Explanation: It's not possible to make amount 3 with coins 2 and 5.
Since we can't combine the coin 2 and 5 to make the amount 3, the output is -1.
```
### Constraints
- $1 \leq n \leq 100$
- $1 \leq \text{coins}[i], \text{amount} \leq 10^3$

using subsetsum Function
```cpp
class Solution {
    int subsetSum(vector<int>& arr, int tar, int i, vector<vector<int>>& dp) {
        if (i == arr.size() || tar == 0) {
            return dp[i][tar] = (tar == 0 ? 0 : 1e4);
        }

        if (dp[i][tar] != 1e4) return dp[i][tar];
        int cnt1 = 1e4,cnt2=1e4;
        if (tar >= arr[i])
            cnt1 =  subsetSum(arr, tar - arr[i], i , dp)+1;
        cnt2 =  subsetSum(arr, tar, i + 1, dp);

        return dp[i][tar] = min(cnt1,cnt2) ;
    }
    int perfectSum(vector<int>& arr, int K) {
        vector<vector<int>> dp(arr.size() + 1, vector<int>(K + 1, 1e4));
        return subsetSum(arr, K, 0, dp);
    }

   public:
    int MinimumCoins(vector<int>& coins, int amount) {
		int val=perfectSum(coins,amount);
		return (val==1e4)?-1 :val;
	}
};
```
## LC 518

```cpp
class Solution {
    int MOD = 1e9 + 7;
    int subsetSum(vector<int>& arr, int tar, int i, vector<vector<int>>& dp) {
        if (i == arr.size() || tar == 0) {
            return dp[i][tar] = (tar == 0 ? 1 : 0);
        }

        if (dp[i][tar] != -1) return dp[i][tar];
        int cnt = 0;
        if (tar >= arr[i])
            cnt = (cnt + subsetSum(arr, tar - arr[i], i, dp)) % MOD;
        cnt = (cnt + subsetSum(arr, tar, i + 1, dp)) % MOD;

        return dp[i][tar] = cnt;
    }
    int perfectSum(vector<int>& arr, int K) {
        vector<vector<int>> dp(arr.size() + 1, vector<int>(K + 1, -1));
        return subsetSum(arr, K, 0, dp);
    }

   public:
    int count(vector<int>& coins, int N, int amount) {
        int val = perfectSum(coins, amount);
        return val;
    }
};

```


 ![alt text](<009 target set_231121_163402(25).jpg>) ![alt text](<009 target set_231121_163402(26).jpg>) ![alt text](<009 target set_231121_163402(27).jpg>) ![alt text](<009 target set_231121_163402(28).jpg>) ![alt text](<009 target set_231121_163402(29).jpg>) 
 
 ## Rod cutting

 ![alt text](<009 target set_231121_163402(30).jpg>)

Here cust have vlaue like KS unbounded !! We need to fill N but cust value !!! price[0] has cut value 1!! We need to tell maximum price we can get!!!

```java
class Solution {
  static int ks_memo(int[] price, int[] cuts, int n, int size, int[][] dp) {
    if (n == 0 || size == 0) {
      return dp[n][size] = 0;
    }
    if (dp[n][size] != -1) return dp[n][size];
    int max = (int) -1e8;
    if (n - cuts[size - 1] >= 0) {
      max = Math.max(max, ks_memo(price, cuts, n - cuts[size - 1], size, dp) + price[size - 1]);
    }
    max = Math.max(max, ks_memo(price, cuts, n, size - 1, dp));
    return dp[n][size] = max;
  }

  public int RodCutting(int price[], int size) {
    int n = price.length;
    int[] cuts = new int[n];
    int val = 1;
    for (int i = 0; i < n; i++) {
      cuts[i] = val;
      val++;
    }
    int[][] dp = new int[n + 1][size + 1];
    for (int[] d : dp) {
      Arrays.fill(d, -1);
    }
    return ks_memo(price, cuts, n, size, dp);
  }
}

```

Above we have made a cuts[i] array but thta can be reduced if we we (n+1)(W+1) KS type!! as there index will denoted the cut[i] value!!

 When i submitted again size was also not given as parameter!!!
```cpp
class Solution {
  public:
    int cutRod(vector<int> &price) {
        int n = price.size();
		vector<vector<int>> dp(n + 1, vector<int>(n + 1, 0));
		
		// Fill the rest of the table
		for (int i = 1; i <= n; i++) {
			for (int j = 0; j <= n; j++) {
				
				// Option 1: Not taking the current item
				int exclude = dp[i - 1][j];
				
				// Option 2: Taking the current item (if capacity allows)
				int include = 0;
				if (j >= i) {
					include = price[i - 1] + dp[i][j - i];
				}
				
				dp[i][j] = max(include, exclude);
			}
		}
		
		return dp[n][n];
        
    }
};
```