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

![alt text](<009 target set_231121_163402(3).jpg>) ![alt text](<009 target set_231121_163402(4).jpg>) ![alt text](<009 target set_231121_163402(5).jpg>) ![alt text](<009 target set_231121_163402(6).jpg>) ![alt text](<009 target set_231121_163402(7).jpg>) ![alt text](<009 target set_231121_163402(8).jpg>) ![alt text](<009 target set_231121_163402(9).jpg>) ![alt text](<009 target set_231121_163402(10).jpg>) ![alt text](<009 target set_231121_163402(11).jpg>) ![alt text](<009 target set_231121_163402(12).jpg>) ![alt text](<009 target set_231121_163402(13).jpg>) ![alt text](<009 target set_231121_163402(14).jpg>) ![alt text](<009 target set_231121_163402(15).jpg>) ![alt text](<009 target set_231121_163402(16).jpg>) ![alt text](<009 target set_231121_163402(17).jpg>) ![alt text](<009 target set_231121_163402(18).jpg>) ![alt text](<009 target set_231121_163402(19).jpg>) ![alt text](<009 target set_231121_163402(20).jpg>)

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

![alt text](<009 target set_231121_163402(21).jpg>) ![alt text](<009 target set_231121_163402(22).jpg>) ![alt text](<009 target set_231121_163402(23).jpg>) ![alt text](<009 target set_231121_163402(24).jpg>) ![alt text](<009 target set_231121_163402(25).jpg>) ![alt text](<009 target set_231121_163402(26).jpg>) ![alt text](<009 target set_231121_163402(27).jpg>) ![alt text](<009 target set_231121_163402(28).jpg>) ![alt text](<009 target set_231121_163402(29).jpg>) ![alt text](<009 target set_231121_163402(30).jpg>) ![alt text](<009 target set_231121_163402(31).jpg>)








