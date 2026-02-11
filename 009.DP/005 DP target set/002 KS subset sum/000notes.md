# Notes

![alt text](<009 target set_231121_163402.jpg>)
![alt text](<009 target set_231121_163402(1).jpg>) 
![alt text](<009 target set_231121_163402(2).jpg>) 

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



![alt text](<009 target set_231121_163402(3).jpg>) ![alt text](<009 target set_231121_163402(4).jpg>) ![alt text](<009 target set_231121_163402(5).jpg>) ![alt text](<009 target set_231121_163402(6).jpg>) ![alt text](<009 target set_231121_163402(7).jpg>) ![alt text](<009 target set_231121_163402(8).jpg>) 


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


# O/1 KS

 ![alt text](<009 target set_231121_163402(16).jpg>) ![alt text](<009 target set_231121_163402(17).jpg>) ![alt text](<009 target set_231121_163402(18).jpg>) ![alt text](<009 target set_231121_163402(19).jpg>) ![alt text](<009 target set_231121_163402(20).jpg>)

### Recursion

```cpp
/*
Given two integer arrays, val and wt, each of size N, which represent the 
values and weights of N items respectively, and an integer W representing the maximum 
capacity of a knapsack, determine the maximum value achievable by selecting a subset of the
 items such that the total weight of the selected items does not exceed the knapsack capacity W.



Each item can either be picked in its entirety or not picked at all (0-1 property). 
The goal is to maximize the sum of the values of the selected items while keeping the total weight within the knapsack's capacity.


Examples:
Input: val = [60, 100, 120], wt = [10, 20, 30], W = 50

Output: 220

Explanation: Select items with weights 20 and 30 for a total value of 100 + 120 = 220.

Input: val = [10, 40, 30, 50], wt = [5, 4, 6, 3], W = 10

Output: 90

Explanation: Select items with weights 4 and 3 for a total value of 40 + 50 = 90.

*/

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
### tabulation

```cpp

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int knapsack01(vector<int>& wt, vector<int>& val, int n, int W) {
        // Initialize DP table with 0
        // dp[i][w] = max value using items up to index i and capacity w
        vector<vector<int>> dp(n, vector<int>(W + 1, 0));

        // Base Case: Fill the first row (item index 0)
        for (int j = wt[0]; j <= W; j++) {
            dp[0][j] = val[0];
        }

        // Fill the rest of the table
        for (int i = 1; i < n; i++) {
            for (int j = 0; j <= W; j++) {
                // Option 1: Not taking the current item
                int exclude = dp[i - 1][j];

                // Option 2: Taking the current item (if capacity allows)
                int include = 0;
                if (j >= wt[i]) {
                    include = val[i] + dp[i - 1][j - wt[i]];
                }

                dp[i][j] = max(include, exclude);
            }
        }

        return dp[n - 1][W];
    }
};

```

### Space optimized

Since each row only depends on the row directly above it, we can optimize the space from $O(N \times W)$ to $O(W)$ using a single 1D array.Crucial Note: When using a 1D array, we must iterate through weights backwards (from W down to wt[i]). This prevents us from using the same item multiple times in the same capacity (which would turn it into an Unbounded Knapsack problem).

```cpp

int knapsack01Optimized(vector<int>& wt, vector<int>& val, int n, int W) {
    vector<int> prev(W + 1, 0);

    // Initial base case for first item
    for (int j = wt[0]; j <= W; j++) prev[j] = val[0];

    for (int i = 1; i < n; i++) {
        // Iterate backwards to preserve values from the previous 'row'
        for (int j = W; j >= wt[i]; j--) {
            prev[j] = max(prev[j], val[i] + prev[j - wt[i]]);
        }
    }
    return prev[W];
}
```
# Handling Large Capacities in Knapsack Tabulation

When $W = 1000$, your DP table column size is determined by the total capacity, not the number of items.

## 1. The "Blank" Space Reality
If you have a capacity of **1000** but your only item has a weight of **500**:
- Indices `0` to `499` will stay `0` (you can't fit the item).
- Indices `500` to `1000` will all store the same value (the value of that one item).

In tabulation, we fill every single "blank" because the algorithm doesn't know which weights are reachable until it calculates them. This is the main difference between **Memoization** and **Tabulation**:

| Feature | Memoization (Top-Down) | Tabulation (Bottom-Up) |
| :--- | :--- | :--- |
| **Efficiency** | Only computes states that are actually reachable. | Computes **every** state from $0$ to $W$. |
| **Sparse Weights** | Better if $W$ is huge but weights are sparse. | Inefficient if $W$ is much larger than the sum of weights. |

---

## 2. When does this become a problem? (Complexity)
The complexity is $O(N \times W)$. 
- If $W = 1000$, it's fine.
- If $W = 10^6$, a 2D array `dp[N][10^6]` will likely cause a **Memory Limit Exceeded (MLE)** error.



---

## 3. How to fix "Blank" Space issues

### A. Space Optimization (1D Array)
As shown before, you should use a 1D array to save memory. Instead of `1000 * N` integers, you only store `1000` integers.

```cpp
vector<int> dp(W + 1, 0); // Only 1001 integers in memory
```
When the capacity $W$ is extremely large (e.g., $10^9$), a standard array or vector will cause a Memory Limit Exceeded (MLE) error. In such cases, you can use a Map-based Memoization approach. This ensures you only store values for the specific capacities actually reached during recursion, effectively ignoring the "blank" spaces.


```cpp

#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

class Solution {
    // We use a map where the key is a pair of (current index, remaining capacity)
    // This only stores states that are actually visited.
    map<pair<int, int>, int> dp;

    int solve(vector<int>& wt, vector<int>& val, int i, int W) {
        // Base Case: No items left or no capacity left
        if (i < 0 || W <= 0) {
            return 0;
        }

        // Check if the state (i, W) has already been computed
        if (dp.find({i, W}) != dp.end()) {
            return dp[{i, W}];
        }

        // Option 1: Exclude the current item
        int exclude = solve(wt, val, i - 1, W);

        // Option 2: Include the current item (if capacity allows)
        int include = 0;
        if (W >= wt[i]) {
            include = val[i] + solve(wt, val, i - 1, W - wt[i]);
        }

        // Store and return the result for this specific state
        return dp[{i, W}] = max(include, exclude);
    }

public:
    int knapsackLargeW(vector<int>& wt, vector<int>& val, int n, int W) {
        dp.clear();
        return solve(wt, val, n - 1, W);
    }
};
```

###  Why this solves the "Blank Space" problem
Memory Efficiency:

 Instead of allocating $1000 \times N$ integers, the map only stores entries for $(i, W)$ pairs that the recursion actually touches.Handling Sparsity: If you have a capacity of $10^9$ but only 5 items, the recursion depth is small ($N=5$), and the number of entries in the map will be very low compared to a billion-sized array.

### Map-Based Knapsack (Sparse DP)
For cases where $W$ is very large (e.g., $10^9$), use a `map<pair<int, int>, int>` to avoid $O(W)$ space.

1. **State Storage:** Instead of `dp[N][W]`, we use `map.find({index, capacity})`.
2. **Selective Computation:** This avoids calculating every capacity from $0$ to $1000$ if those specific weights are never reached.
3. **Overhead:** Note that `std::map` has a $O(\log N)$ lookup overhead compared to $O(1)$ for an array, so only use this if $W$ exceeds memory limits.



# Why You Should Avoid Using Maps for DP (Unless Necessary)

While a `std::map` or `unordered_map` is useful for handling massive, sparse state spaces, it is generally considered inferior to arrays or vectors for standard Competitive Programming and interview problems.

---

## 1. Time Complexity & Constant Factors
The most immediate reason is the performance hit taken during lookups.

* **Array/Vector Access ($O(1)$):** Accessing `dp[i][j]` is a single memory offset calculation. It is incredibly fast.
* **`std::map` Access ($O(\log N)$):** Maps are typically balanced Red-Black Trees. Every time you check a state, the CPU must traverse multiple nodes, performing comparisons at each level.
* **`std::unordered_map` Access ($O(1)$ Average):** While theoretically $O(1)$, the overhead of computing a **hash function** for a `pair<int, int>` is much slower than simple array indexing. In the worst case (hash collisions), it can degrade to $O(N)$.

[Image of a comparison chart between array access time and tree-based map lookup time]

---

## 2. Memory Overhead per Entry
Maps are "heavy" data structures. An array is just a contiguous block of values, but a map stores a lot of metadata for every single state.

| Feature | Array/Vector | `std::map` (Red-Black Tree) |
| :--- | :--- | :--- |
| **Data Stored** | Just the value (e.g., 4 bytes for an `int`). | Key + Value + 3 Pointers (Left, Right, Parent) + Color bit. |
| **Total Memory** | ~4 bytes per entry. | ~32-48 bytes per entry. |

**The Result:** Even if you have fewer states in a map, each state consumes **8 to 12 times more memory** than an array entry. If your DP table is relatively dense, a map will cause a **Memory Limit Exceeded (MLE)** much faster than an array.

---

## 3. CPU Cache Locality (The "Hidden" Speed Killer)
Modern CPUs are designed to be fast when data is **contiguous** (next to each other in memory).

* **Arrays:** Because they are contiguous, the CPU can "prefetch" the next values into the L1/L2 cache before you even ask for them.
* **Maps:** Nodes are scattered all over the heap memory. Every time you follow a pointer to a new map node, you likely trigger a **"Cache Miss,"** forcing the CPU to wait for data to arrive from the much slower RAM.

[Image of a diagram showing cache locality in a contiguous array vs. scattered memory nodes in a map]

---

## 4. When is a Map Actually Better?
You should only use a map when the state space is **extremely sparse and large**.

> **Example:** You have a capacity $W = 10^9$, but you only have $N = 20$ items. 
> - An array of $10^9$ is impossible (it would take ~4GB).
> - The total number of reachable states $(i, W)$ is likely only a few thousand. 
> - In this specific case, the memory savings of the map outweigh the speed penalties.

---

## Summary Table

| Requirement | Use Array/Vector | Use Map/Unordered_Map |
| :--- | :--- | :--- |
| **Speed** | ⭐⭐⭐⭐⭐ (Fastest) | ⭐⭐ (Slower) |
| **Memory** | Efficient for dense data | Efficient for sparse data |
| **Implementation** | Simple indexing | Requires custom hash for pairs |
| **Standard Choice** | **Always Start Here** | **Only use as a last resort** |

[Image of a decision tree for choosing between array-based DP and map-based DP based on constraints]

![alt text](<009 target set_231121_163402(21).jpg>) ![alt text](<009 target set_231121_163402(22).jpg>)


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


 ![alt text](<009 target set_231121_163402(23).jpg>) ![alt text](<009 target set_231121_163402(24).jpg>) ![alt text](<009 target set_231121_163402(25).jpg>) ![alt text](<009 target set_231121_163402(26).jpg>) ![alt text](<009 target set_231121_163402(27).jpg>) ![alt text](<009 target set_231121_163402(28).jpg>) ![alt text](<009 target set_231121_163402(29).jpg>) ![alt text](<009 target set_231121_163402(30).jpg>) ![alt text](<009 target set_231121_163402(31).jpg>)








