# Notes

![alt text](<002coin change_231126_233809.jpg>)

![alt text](<002coin change_231126_233809(1).jpg>) ![alt text](<002coin change_231126_233809(2).jpg>) ![alt text](<002coin change_231126_233809(3).jpg>) ![alt text](<002coin change_231126_233809(4).jpg>) ![alt text](<002coin change_231126_233809(5).jpg>) 

```java
/* package codechef; // don't place package name! */

import java.util.*;
import java.lang.*;
import java.io.*;

/* Name of the class has to be "Main" only if the class is public. */
class Codechef
{
        public static int coinChangePermutation_IN(int[] coins, int tar, String psf) {
        if (tar == 0) {
            System.out.println(psf);
            return 1;
        }

        int count = 0;
        for (int i = 0; i < coins.length; i++) {
            if (tar - coins[i] >= 0) {
                count += coinChangePermutation_IN(coins, tar - coins[i], psf + coins[i] + " ");
            }
        }

        return count;

    }

	public static void main (String[] args) throws java.lang.Exception
	{
		int[] coins = { 2, 3, 5, 7 };
        int tar = 10;
        coinChangePermutation_IN(coins,tar,"");

	}
}


/*
Output:
2 2 2 2 2 
2 2 3 3 
2 3 2 3 
2 3 3 2 
2 3 5 
2 5 3 
3 2 2 3 
3 2 3 2 
3 2 5 
3 3 2 2 
3 5 2 
3 7 
5 2 3 
5 3 2 
5 5 
7 3 
*/
```

![alt text](<002coin change_231126_233809(6).jpg>) ![alt text](<002coin change_231126_233809(7).jpg>) ![alt text](<002coin change_231126_233809(8).jpg>) ![alt text](<002coin change_231126_233809(9).jpg>) ![alt text](<002coin change_231126_233809(10).jpg>) ![alt text](<002coin change_231126_233809(11).jpg>)
![alt text](<002coin change_231126_233809(12).jpg>) ![alt text](<002coin change_231126_233809(13).jpg>) ![alt text](<002coin change_231126_233809(14).jpg>) ![alt text](<002coin change_231126_233809(15).jpg>) ![alt text](<002coin change_231126_233809(16).jpg>) ![alt text](<002coin change_231126_233809(17).jpg>) ![alt text](<002coin change_231126_233809(18).jpg>) ![alt text](<002coin change_231126_233809(19).jpg>) ![alt text](<002coin change_231126_233809(20).jpg>) ![alt text](<002coin change_231126_233809(21).jpg>) 

### All 4

#### Way-1

```java

    public static int coinChangePermutation_IN(int[] coins, int tar, String psf) {
        if (tar == 0) {
            System.out.println(psf);
            return 1;
        }

        int count = 0;
        for (int i = 0; i < coins.length; i++) {
            if (tar - coins[i] >= 0) {
                count += coinChangePermutation_IN(coins, tar - coins[i], psf + coins[i] + " ");
            }
        }

        return count;

    }

    public static int coinChangeCombination_IN(int[] coins, int tar, int idx, String psf) {
        if (tar == 0) {
            System.out.println(psf);
            return 1;
        }

        int count = 0;
        for (int i = idx; i < coins.length; i++) {
            if (tar - coins[i] >= 0) {
                count += coinChangeCombination_IN(coins, tar - coins[i], i, psf + coins[i] + " ");
            }
        }
        return count;
    }

    public static int coinChangePermutation_Sin(int[] coins, int tar, String psf) {
        if (tar == 0) {
            System.out.println(psf);
            return 1;
        }

        int count = 0;
        for (int i = 0; i < coins.length; i++) {
            if (coins[i] > 0 && tar - coins[i] >= 0) {
                int val = coins[i];
                coins[i] = -coins[i];
                count += coinChangePermutation_Sin(coins, tar - val, psf + val + " ");
                coins[i] = -coins[i];
            }
        }

        return count;
    }

    public static int coinChangeCombination_Sin(int[] coins, int tar, int idx, String psf) {
        if (tar == 0) {
            System.out.println(psf);
            return 1;
        }

        int count = 0;
        for (int i = idx; i < coins.length; i++) {
            if (tar - coins[i] >= 0) {
                count += coinChangeCombination_Sin(coins, tar - coins[i], i + 1, psf + coins[i] + " ");
            }
        }
        return count;
    }


```
#### way-2 Subset or select non select way


```java

    public static int coinChangePermutation_IN_Sub(int[] coins, int tar, int idx, String psf) {
        if (tar == 0 || idx == coins.length) {
            if (tar == 0) {
                System.out.println(psf);
                return 1;
            }
            return 0;
        }

        int count = 0;
        if (tar - coins[idx] >= 0)
            count += coinChangePermutation_IN_Sub(coins, tar - coins[idx], 0, psf + coins[idx] + " ");
        count += coinChangePermutation_IN_Sub(coins, tar, idx + 1, psf);

        return count;
    }

    public static int coinChangeCombination_IN_Sub(int[] coins, int tar, int idx, String psf) {
        if (tar == 0 || idx == coins.length) {
            if (tar == 0) {
                System.out.println(psf);
                return 1;
            }
            return 0;
        }

        int count = 0;
        if (tar - coins[idx] >= 0)
            count += coinChangeCombination_IN_Sub(coins, tar - coins[idx], idx, psf + coins[idx] + " ");
        count += coinChangeCombination_IN_Sub(coins, tar, idx + 1, psf);

        return count;
    }

    public static int coinChangeCombination_Sin_Sub(int[] coins, int tar, int idx, String psf) {
        if (tar == 0 || idx == coins.length) {
            if (tar == 0) {
                System.out.println(psf);
                return 1;
            }
            return 0;
        }

        int count = 0;

        if (tar - coins[idx] >= 0) {
            count += coinChangeCombination_Sin_Sub(coins, tar - coins[idx], idx + 1, psf + coins[idx] + " ");
        }
        count += coinChangeCombination_Sin_Sub(coins, tar, idx + 1, psf);

        return count;
    }

    public static int coinChangePermutation_Sin_Sub(int[] coins, int tar, int idx, String psf) {
        if (tar == 0 || idx == coins.length) {
            if (tar == 0) {
                System.out.println(psf);
                return 1;
            }
            return 0;
        }

        int count = 0;
        if (tar - coins[idx] >= 0) {
            int val = coins[idx];
            coins[idx] = -coins[idx];
            count += coinChangePermutation_IN_Sub(coins, tar - val, 0, psf + val + " ");
            coins[idx] = -coins[idx];
        }
        count += coinChangePermutation_IN_Sub(coins, tar, idx + 1, psf);

        return count;
    }


```

# Recursive Complexity Analysis: Coin Change Variations

When analyzing the time complexity of recursive algorithms like Coin Change, we focus on two primary factors: **Maximum Depth** of the recursion tree and the **Branching Factor** (number of choices at each node).

### Key Variables:
* $N$: Number of available coins.
* $T$: Target sum.
* $M$: Value of the smallest coin (determines the maximum depth).

---

### 1. Permutation (For-Loop) — $O(N^{T/M})$
In this approach, you are essentially filling "slots" in an ordered sequence.

* **Branching Factor:** At every single step, you loop from $0$ to $N-1$. This means every node in your recursion tree has **$N$ choices**.
* **Depth:** The longest possible path occurs if you repeatedly pick the smallest coin $M$. The maximum depth is **$T/M$**.
* **Total Work:** Imagine a tree where every node has $N$ children and is $T/M$ levels deep. The total number of nodes/leaves is $N \times N \times \dots$ repeated $T/M$ times, resulting in $O(N^{T/M})$.

---

### 2. Combination (For-Loop) — $O(\text{approx } N^{T/M})$
This is mathematically similar to the Permutation approach but with heavy structural pruning.

* **Branching Factor:** You still use a loop, but instead of starting at $0$, you start at the current index `idx`.
* **Logic:** By only picking coins at or after your current index, you eliminate all "backwards" permutations (e.g., if you pick coin 2, you can never pick coin 1 later in that branch).
* **Complexity:** While the upper bound is technically still exponential, the actual number of nodes visited is significantly lower. It is closer to the formula for combinations with replacement: $$\binom{N + T/M - 1}{T/M}$$

---

### 3. Permutation (Subsequence) — $O(2^{N \times T/M})$
The subsequence approach usually has a fixed branching factor of **2** (Pick or Don't Pick).

* **The Catch:** In the Permutation Subsequence implementation, every time you "Pick" a coin, you **reset the index back to 0** (e.g., `... tar - val, 0, ...`).
* **Why so high?:** Because you reset to 0, you aren't just deciding on $N$ coins once. You are potentially deciding on $N$ coins over and over again for every unit of the target sum.
* **Structure:** This creates a massive binary tree where the "Pick" branch is much more "expensive" than the "Exclude" branch. This leads to a much larger state space than the for-loop version because the `idx` state is constantly restarting.

---

### 4. Combination (Subsequence) — $O(2^{N + T/M})$
This is the core logic used in the **Unbounded Knapsack** problem.

* **Branching Factor:** Fixed at **2** (Pick or Don't Pick).
* **Path Length:** * To reach the end of the array, you must "Exclude" **$N$ times**.
    * To reach the target sum, you can "Pick" at most **$T/M$ times**.
* **Logic:** Any single path from the root to a leaf can be at most $N + T/M$ steps long. Since it is a binary tree, the total nodes are proportional to $2^{\text{path length}}$. This is significantly more efficient than the Permutation Subsequence because the index never resets; it only stays or moves forward.

---

### Complexity Summary Table

| Approach | Pattern | Branching Factor | Max Depth | Complexity |
| :--- | :--- | :--- | :--- | :--- |
| **For-Loop** | Permutation | $N$ | $T/M$ | $O(N^{T/M})$ |
| **For-Loop** | Combination | Up to $N$ | $T/M$ | $O(\text{approx } N^{T/M})$ |
| **Subsequence** | Permutation | 2 | $N \times T/M$ | $O(2^{N \times T/M})$ |
| **Subsequence** | Combination | 2 | $N + T/M$ | $O(2^{N + T/M})$ |


# Comprehensive Comparison: For-Loop vs. Subsequence Approach

The way we structure recursion significantly impacts the "Shape" of the state space tree. Below is a deep dive into the conceptual differences and the time complexity for **Single Use (Sin)** variations.

---

### 1. Conceptual Comparison

| Feature | For-Loop Approach | Subsequence Approach |
| :--- | :--- | :--- |
| **Philosophy** | **"Slot-Based":** We ask, "Which of the $N$ available items should I put in this current position?" | **"Decision-Based":** We look at one specific item and ask, "Do I take this or leave it?" |
| **Branching Factor** | **Variable ($N$):** A node can have many children (one for each coin in the loop). | **Fixed (2):** A node always has exactly two children (Pick/Don't Pick). |
| **Tree Depth** | **Shallower:** The depth is limited by how many items fit in the target (or $N$ for single use). | **Deeper:** We must visit every item index, making the depth proportional to $N$. |
| **DP Mapping** | Usually maps to **1D DP** (e.g., `dp[target]`). | Usually maps to **2D DP** (e.g., `dp[index][target]`). |

---

### 2. Time Complexity (TC) Analysis: Single Use (Sin)

In **Single Use** scenarios, the total number of items $N$ is the primary constraint on the depth of the tree.

#### 5. Permutation (For-Loop) — $O(N!)$
* **Logic:** To fill the 1st slot, you have $N$ choices. Once a coin is used (marked), the 2nd slot has $N-1$ choices, the 3rd has $N-2$, and so on.
* **Math:** $N \times (N-1) \times (N-2) \dots \times 1 = N!$. This represents all possible orderings of the set.

#### 6. Combination (For-Loop) — $O(2^N)$
* **Logic:** Because you only move forward (`i = idx to N-1`), you are essentially generating all subsets.
* **Math:** The total number of subsets of a set of size $N$ is $2^N$. Even though it's a loop, the restriction to move forward prunes the $N!$ permutation tree down to a power-set tree.

#### 7. Permutation (Subsequence) — $O(N!)$
* **Logic:** Even though you are using a "Pick/Don't Pick" structure, the "Pick" branch **resets the index to 0** to look for the next coin. 
* **Math:** Because you can jump back to any unused coin at any time, you are still exploring all possible permutations. The binary decisions effectively map out the same $N!$ paths as the for-loop approach.

#### 8. Combination (Subsequence) — $O(2^N)$
* **Logic:** This is the classic "Subsequence" tree. At each of the $N$ items, you have 2 choices.
* **Math:** A binary tree where every path is $N$ levels deep has $2^N$ leaf nodes. This is the standard complexity for problems like *Subset Sum* or *0/1 Knapsack*.

---

### 3. Time Complexity (TC) Analysis: Infinite Supply (IN)

In **Infinite Supply** scenarios, the target $T$ and minimum coin value $M$ determine the depth.

| Method | Time Complexity | Explanation |
| :--- | :--- | :--- |
| **1. Permutation (Loop)** | $O(N^{T/M})$ | Every level has $N$ choices; max levels = $T/M$. |
| **2. Combination (Loop)** | $O(\text{approx } N^{T/M})$ | Loop starts at `idx`, pruning the search space, but the upper bound remains exponential. |
| **3. Permutation (Sub)** | $O(2^{N \times T/M})$ | Resetting index to 0 on every "Pick" creates a massive state space proportional to target. |
| **4. Combination (Sub)** | $O(2^{N + T/M})$ | The path is bounded: move right $N$ times OR pick $T/M$ times. |

---

### Summary Table for Interviews

| Variation | Approach | Supply | Complexity |
| :--- | :--- | :--- | :--- |
| **Permutation** | Any | Single | $O(N!)$ |
| **Combination** | Any | Single | $O(2^N)$ |
| **Permutation** | For-Loop | Infinite | $O(N^{T/M})$ |
| **Combination** | Subseq | Infinite | $O(2^{N + T/M})$ |


### Memoized approach
To transform these exponential recursive solutions ($O(2^N)$ or $O(2^{N+T})$) into polynomial time ($O(N \times T)$), we use Memoization.Memoization stores the result of a specific state (idx, target) in a 2D array so that if the recursion visits the same state again, it returns the answer instantly.

```java

public static int coinChangeCombination_IN_Memo(int[] coins, int tar, int idx, int[][] dp) {
    // Base Case
    if (tar == 0) return 1;
    if (idx == coins.length) return 0;

    // 1. Check if already calculated
    if (dp[idx][tar] != -1) return dp[idx][tar];

    int count = 0;

    // 2. Inclusion (Pick): Stay at same idx for infinite supply
    if (tar - coins[idx] >= 0) {
        count += coinChangeCombination_IN_Memo(coins, tar - coins[idx], idx, dp);
    }

    // 3. Exclusion (Don't Pick): Move to next coin
    count += coinChangeCombination_IN_Memo(coins, tar, idx + 1, dp);

    // 4. Store and return
    return dp[idx][tar] = count;
}
```

Provided with a goal integer target and an array of unique integer candidates, provide a list of all possible combinations of candidates in which the selected numbers add up to the target. The combinations can be returned in any order.



A candidate may be selected from the pool an infinite number of times. There are two distinct combinations if the frequency of at least one of the selected figures differs.



The test cases are created so that, for the given input, there are fewer than 150 possible combinations that add up to the target.

If there is no possible subsequences then return empty vector.

Examples:
---
Input : candidates = [2, 3, 5, 4] , target = 7

Output : [ [2, 2, 3] , [3, 4] , [5, 2] ]

Explanation :

2 and 3 are candidates, and 2 + 2 + 3 = 7. Note that 2 can be used multiple times.

5 and 2 are candidates, and 5 + 2 = 7.

3 and 4 are candidates, and 3 + 4 = 7.

There are total three combinations.

---

Input : candidates = [2], target = 1

Output : []

Explanation : There is no way we can choose the candidates to sum up to target.

Constraints:
----
1 <= candidates.length <= 30
2 <= candidates[i] <= 40
All elements of candidates are distinct.
1 <= target <= 40

```cpp
class Solution {
    void solve(vector<int>& arr,int i ,vector<vector<int>>& res,vector<int>& tres,int tar){
        if(i==arr.size() || tar==0 ){
            if(tar==0){
                res.push_back(tres);
            }
            return;
        }
        if(tar>=arr[i]) {
            tres.push_back(arr[i]);
            solve(arr,i,res,tres,tar-arr[i]);
            tres.pop_back();
        }
        solve(arr,i+1,res,tres,tar);
    }
public:
    vector<vector<int>> combinationSum(vector<int>& cand, int tar) {
        vector<vector<int>>res;
        vector<int> tres;
        solve(cand,0,res,tres,tar);
        return res;

    }
};
```
>Note: Unlike java here no neeed of new array to push in res

Time Complexity:The time complexity is O(N^(T/M + 1)), where N is the number of candidates, T is the target value, and M is the minimum value among the candidates.

Space Complexity:The space complexity is O(T/M), where T is the target value, and M is the minimum value among the candidates. This is primarily due to the maximum depth of the recursion stack.

----
## Count no of subsets or subsequence having sum K

### Cpp
```cpp
#include<bits/stdc++.h>
using namespace std;

class Solution {
private:

    int func(int ind, int sum, vector<int> &nums) {

        if (sum == 0) return 1;

        if (sum < 0 || ind == nums.size()) return 0;
   
        return func(ind + 1, sum - nums[ind], nums) + func(ind + 1, sum, nums);
    }

public:

    int countSubsequenceWithTargetSum(vector<int>& nums, int target) {
        return func(0, target, nums);
    }
};

int main() {
    Solution sol;
    vector<int> nums = {1, 2, 3, 4, 5};
    int target = 5;
    cout << "Number of subsequences with target sum " << target << ": "
         << sol.countSubsequenceWithTargetSum(nums, target) << endl;
    return 0;
}


```

### Java

```java
class Solution {
    private int sumOfeachSubset(int[] nums, int n,int k,int i,int sum){
        if(i==n) return sum==k?1:0;
        if(sum==k) return 1;

        return sumOfeachSubset(nums,n,k,i+1,sum+nums[i])
        +sumOfeachSubset(nums,n,k,i+1,sum);

      
    }
    private int check (int[] nums, int n,int k){
          return  sumOfeachSubset(nums,n,k,0,0);
    }
    public int countSubsequenceWithTargetSum(int[] nums, int k) {
        return check(nums,nums.length,k);
    }
}

```

### Cehck whether k sum can be reached by subset 

#### Cpp
```cpp
#include <bits/stdc++.h>
using namespace std;

class Solution {
private:
  
    bool func(int ind, int sum, std::vector<int> &nums) {

        if (ind == nums.size()) {
            return sum == 0;
        }
    
        return func(ind + 1, sum - nums[ind], nums) | func(ind + 1, sum, nums);//see difference in  | in java and cpp
    }

public:

    bool checkSubsequenceSum(std::vector<int>& nums, int target) {
        return func(0, target, nums)
    }
};

// Main function to test the solution
int main() {
    Solution sol;
    std::vector<int> nums = {1, 2, 3, 4};
    int target = 5;
    std::cout << sol.checkSubsequenceSum(nums, target); // Expected output: true
    return 0;
}

```
#### Java

```java
class Solution {
    private boolean sumOfeachSubset(int[] nums, int n,int k,int i,int sum){
        if(i==n) return sum==k;
        if(sum==k) return true;

        boolean v1=sumOfeachSubset(nums,n,k,i+1,sum+nums[i]);
        if(v1==true) return true;
        boolean v2=sumOfeachSubset(nums,n,k,i+1,sum);
        if(v2==true) return true;

         return false;  
    }
    private boolean check (int[] nums, int n,int k){
          return  sumOfeachSubset(nums,n,k,0,0);
    }
    public boolean checkSubsequenceSum(int[] nums, int k) {
         return check (nums,nums.length,k);
    }
}
```

#### Java

```java
class Solution {
    /*
    Time Complexity O(2n) - Each item has two choices (include or exclude), leading to an exponential number of combinations.

    Space Complexity: O(n) - The maximum depth of the recursive call stack is equal to the number of items.
    */
    public boolean solve(int i, int n, int[] arr, int k) {

        if (k == 0) {
            return true;
        }

        if (k < 0) {
            return false;
        }

        if (i == n) {
            return k == 0;
        }

        return solve(i + 1, n, arr, k - arr[i]) || solve(i + 1, n, arr, k);
    }

    // This method initiates the recursive process
    public boolean checkSubsequenceSum(int[] nums, int target) {
        int n = nums.length; 
        return solve(0, n, nums, target); 
    }

    // Main method to test the solution
    public static void main(String[] args) {
        Solution sol = new Solution();
        int[] nums = {1, 2, 3, 4};
        int target = 5;
        System.out.println(sol.checkSubsequenceSum(nums, target)); // Expected output: true
    }
}

```