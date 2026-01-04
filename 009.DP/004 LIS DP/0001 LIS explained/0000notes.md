# Notes
![alt text](<006 LIS_231124_134844.jpg>)
![alt text](<006 LIS_231124_134844(1).jpg>) ![alt text](<006 LIS_231124_134844(2).jpg>) ![alt text](<006 LIS_231124_134844(3).jpg>) ![alt text](<006 LIS_231124_134844(4).jpg>) 
## O(n^2) approach


```cpp

class Solution {
public:
    int LIS(vector<int>& nums) {
        int n=nums.size();
        int res=1;
        vector<int> dp(n,1);
        for(int i=1;i<n;i++){

            for(int j=i-1;j>=0;j--){
                if(nums[i]>nums[j]){
                    dp[i]=max(dp[i],dp[j]+1);
                }
            }

            res=max(dp[i],res);
        }

        return res;
    }    
};

```

We know what subsequence is so har peeche vale element pe jake check kia hmne jo chota hai uski 
value add kr di

## O(nlogn) approach

```cpp

class Solution {
public:
    int LIS(vector<int>& nums) {
        int n=nums.size();
        vector<int> temp;
        temp.push_back(nums[0]);
        for(int i=1; i < n; i++) {
            if(nums[i] > temp.back()) 
                temp.push_back(nums[i]); 
            else {
                int ind = lower_bound(temp.begin(), temp.end(), nums[i]) -temp.begin();
                temp[ind] = nums[i];
            }    
            
        }
        return temp.size();
    }    
};

```

In C++, `std::lower_bound (from <algorithm>)` is used to find the first position in a sorted range where a given value x could be inserted without breaking the order.

Syntax-->`auto it = lower_bound(begin, end, x);`


begin, end → iterators of the range (must be sorted in ascending order).

x → the value you are searching for.

Returns an iterator pointing to the first element that is `≥ x.`

If all elements are `< x`, it returns end.

---

# Understanding the `temp` Array in LIS

A common point of confusion is thinking that `temp` stores the actual Longest Increasing Subsequence. **It does not.** Instead, it is a tool used in the **Patience Sorting** algorithm to track potential candidates.

---

## 1. What `temp[i]` Represents
The array `temp` serves as a record of the "best" (smallest) possible ending values for subsequences of various lengths.

* `temp[0]`: The smallest possible tail of an increasing subsequence of length **1**.
* `temp[1]`: The smallest possible tail of an increasing subsequence of length **2**.
* `temp[k]`: The smallest possible tail of an increasing subsequence of length **k+1**.

At the end of the algorithm, the **length** of `temp` is the length of the LIS, but the elements inside are often a "mangled" mix of numbers from different potential sequences.



---

## 2. A Concrete Example: Why `temp` is NOT the LIS
Let’s trace `nums = [3, 4, 1, 2]`. The actual LIS is `[3, 4]` or `[1, 2]`. Both have length **2**.

| Step | Num | Action | `temp` state | Explanation |
| :--- | :--- | :--- | :--- | :--- |
| 1 | **3** | Push back | `[3]` | Smallest tail for length 1 is 3. |
| 2 | **4** | Push back | `[3, 4]` | Smallest tail for length 2 is 4. |
| 3 | **1** | Replace 3 | `[1, 4]` | **1** is a "better" tail for length 1 than **3**. |
| 4 | **2** | Replace 4 | `[1, 2]` | **2** is a "better" tail for length 2 than **4**. |

### The Proof of "Mangled" Data
If the input was `[3, 10, 1]`:
1.  **Start:** `[3]`
2.  **Add 10:** `[3, 10]`
3.  **Add 1:** `temp` becomes `[1, 10]`

The LIS length is correctly **2**, but `[1, 10]` is **not** a valid subsequence because `10` appeared *before* `1` in the original array. This proves `temp` only tracks the "best" ending values to allow future numbers to extend the sequence.

---

## 3. Why do we replace values? (The Power of `lower_bound`)
We use `lower_bound` to replace values because **smaller tails are objectively better**. 

Imagine you have two potential subsequences of length 2:
* Subsequence A: `[... , 10]`
* Subsequence B: `[... , 4]`

We prefer the tail `4`. Why? Because if the next number in the array is `5`:
* It **cannot** extend Subsequence A.
* It **can** extend Subsequence B to form a sequence of length 3.

By keeping the values in `temp` as low as possible, we maximize our chances of extending the sequence length with future numbers.



---

## 4. Summary
- **Purpose:** `temp` stores the smallest possible tail for every possible length.
- **Mechanism:** If `nums[i]` is larger than the largest tail, extend the LIS. Otherwise, use binary search to update an existing tail to a smaller value.
- **Final Result:** `temp.size()` gives the length, but not the elements.


----
### Applications of the `temp` Array Technique
The `temp` array (Patience Sorting) is highly specialized for $O(n \log n)$ sequence problems:

1. **Russian Doll Envelopes:** Sorting one dimension and performing LIS on the other.
2. **Longest Bitonic Subsequence:** Calculating LIS from both ends of the array.
3. **Minimum Piles:** The size of `temp` tells you the minimum number of non-increasing sequences needed to cover the array (Dilworth's Theorem).
4. **Box Stacking:** Finding the maximum height by treating box dimensions as a sequence.

**Rule of Thumb:** If the problem asks for the *length* of a subsequence based on *comparison* ($\geq$ or $>$), and $N > 10^4$, the `temp` array is your go-to tool.

---

# LIS: `lower_bound` vs `upper_bound`

In the standard Longest Increasing Subsequence problem, you are looking for a **strictly increasing** sequence. Using the optimal $O(n \log n)$ approach (Patience Sorting), the choice of binary search function is critical.

---

## 1. Comparison Table

| Feature | `lower_bound` | `upper_bound` |
| :--- | :--- | :--- |
| **Search Criteria** | First element $\geq$ target | First element $>$ target |
| **Effect on Duplicates** | Overwrites the existing equal value | Overwrites the next larger value |
| **Resulting Subsequence** | **Strictly Increasing** (1, 2, 3) | **Non-Decreasing** (1, 2, 2, 3) |

---

## 2. Why `upper_bound` fails for Strictly Increasing
If the problem asks for a strictly increasing subsequence, you cannot have two identical numbers. 

### Scenario: `nums = [2, 5, 2]`
1. `temp = [2]`
2. `temp = [2, 5]`
3. Next number is `2`.
   - **Using `lower_bound`**: It finds the first element $\geq 2$, which is the `2` at index 0. It replaces `2` with `2`. `temp` remains `[2, 5]`. **Correct.**
   - **Using `upper_bound`**: It finds the first element $> 2$, which is `5`. It replaces `5` with `2`. `temp` becomes `[2, 2]`. **Incorrect** (The sequence is no longer strictly increasing).



---

## 3. When to use `upper_bound`
You should switch to `upper_bound` only if the problem definition changes to **Longest Non-Decreasing Subsequence**. 

In that case, duplicates are allowed, so if you see another `2`, you don't want to overwrite the existing `2`; you want to add it to the sequence or overwrite the next value that is strictly larger.

---

## 4. The Correct Code (Strictly Increasing)
To keep your code strictly increasing, stay with `lower_bound`:

```cpp
int ind = lower_bound(temp.begin(), temp.end(), nums[i]) - temp.begin();
temp[ind] = nums[i];

## Extra About LIs

LIS can be solved by recursion memoization ,select not select way as we need 
subsequenece ,so select not select is way to get subsequence

```cpp
#include <bits/stdc++.h>
using namespace std;

class Solution {
private:

    int func(int i, int prevInd, vector<int> &arr) {
        if(i == arr.size() - 1) {
            if(prevInd == -1 || arr[prevInd] < arr[i]) return 1;
            return 0;
        }
        
        int notTake = func(i+1, prevInd, arr);
        
        int take = 0;
        // If no element is chosen till now
        if(prevInd == -1)
            take = func(i+1, i, arr) + 1;
        
        /* Else the current element can be 
        taken if it is strictly increasing */
        else if(arr[i] > arr[prevInd])
            take = func(i+1, i, arr) + 1;
        // Return the maximum length obtained from both cases
        return max(take, notTake);
    }
    
public:
    int LIS(vector<int>& nums) {
        return func(0, -1, nums);
    }    
};


int main() {
    vector<int> nums = {10, 9, 2, 5, 3, 7, 101, 18};
    Solution sol;
    int lengthOfLIS = sol.LIS(nums);

    cout << "The length of the LIS for the given array is: " << lengthOfLIS << endl;
    
    return 0;
}
```
Complexity Analysis:
Time Complexity: O(2^N), where N represents the number of elements in the given array.
In each function call, two recursive calls are made (take and not take) resulting in an exponential time complexity.

Space Complexity: O(N), because of the recursion stack space.

Apply memoization to this

```cpp
#include <bits/stdc++.h>
using namespace std;

class Solution {
private:
    // Helper function to find the length of LIS
    int func(int i, int prevInd, vector<int> &arr, vector<vector<int>> &dp) {
        
        // base case
        if(i == arr.size() - 1) {
            if(prevInd == -1 || arr[prevInd] < arr[i]) return 1;
            return 0;
        }
        
        // If subproblem is already calculated
        if(dp[i][prevInd + 1] != -1) return dp[i][prevInd + 1];
        
        // Not Take case
        int notTake = func(i+1, prevInd, arr, dp);
        
        int take = 0; // Take case
        
        // If no element is chosen till now
        if(prevInd == -1)
            take = func(i+1, i, arr, dp) + 1;
        
        /* Else the current element can be 
        taken if it is strictly increasing */
        else if(arr[i] > arr[prevInd])
            take = func(i+1, i, arr, dp) + 1;
        
        // Return the maximum length obtained from both cases
        return dp[i][prevInd + 1] = max(take, notTake);
    }
    
public:
    /* Function to find the longest increasing 
    subsequence in the given array */
    int LIS(vector<int>& nums) {
        int n = nums.size();
        
        // DP array
        vector<vector<int>> dp(n, vector<int>(n+1, -1));
        
        return func(0, -1, nums, dp);
    }    
};


int main() {
    vector<int> nums = {10, 9, 2, 5, 3, 7, 101, 18};
    
    // Creating an object of Solution class
    Solution sol;
    int lengthOfLIS = sol.LIS(nums);
    
    cout << "The length of the LIS for the given array is: " << lengthOfLIS << endl;
    
    return 0;
}


```


Print LIs O(n^2)

O(nlgn) cannot print LIS

```cpp

class Solution {
  public:
    vector<int> longestIncreasingSubsequence(vector<int>& nums) {
    int n=nums.size();
        int res=1;
        int resIdx=0;//should be zero for decreasing subsequence
        vector<int> dp(n,1);
        vector<int>par(n,0);
        for(int i=1;i<n;i++){
            par[i]=i;
            for(int j=i-1;j>=0;j--){
                if(nums[i]>nums[j]){
                    if(dp[j]+1>=dp[i]){
                        dp[i]=dp[j]+1;
                        par[i]=j;
                    }
                }
            }

            if(dp[i]>res){
                res=dp[i];
                resIdx=i;
            }
        }

        vector<int> resArr;

        int k=resIdx;

        while(par[k]!=k){
            resArr.push_back(nums[k]);
            k=par[k];
        }
         resArr.push_back(nums[k]);
        reverse(resArr.begin(),resArr.end());

        return resArr;
}
};

```


## Number of LIS 


```cpp

class Solution {
public:
    int numberOfLIS(vector<int> nums) {
        int n=nums.size();
        int res=1;
        vector<int> dp(n,1);
        vector<int>num(n,1);
        for(int i=1;i<n;i++){

            for(int j=i-1;j>=0;j--){
                if(nums[i]>nums[j]){
                    if(dp[j]+1>dp[i]){
                        dp[i]=dp[j]+1;
                        num[i]=num[j];
                    }else if(dp[j]+1==dp[i]){
                        num[i]+=num[j];
                    }
                }
            }

            res=max(dp[i],res);
        }
        int ans=0;
        for(int i=0;i<n;i++){
            if(dp[i]==res) ans+=num[i];
        }
        return ans;
    }
};

```

So both approaches are very important O(n^2) and O(nlgn)

![alt text](<006 LIS_231124_134844(5).jpg>) ![alt text](<006 LIS_231124_134844(6).jpg>) ![alt text](<006 LIS_231124_134844(7).jpg>) ![alt text](<006 LIS_231124_134844(8).jpg>)

## Longest Decreasing Subsequence (LDS)

### Approach 1: Right to Left (R to L)
This version calculates the LDS ending at index i by looking at elements to its right.

```java

public class Solution {
    public static int LDS(int[] arr) {
        int size = arr.length;
        int[] dp = new int[size];
        int maxlen = 0;
        
        // Iterating Right to Left
        for (int i = size - 1; i >= 0; i--) {
            dp[i] = 1; // Base case: every element is an LDS of length 1
            for (int j = i + 1; j < size; j++) {
                if (arr[j] < arr[i]) {
                    dp[i] = Math.max(dp[j] + 1, dp[i]);
                }
            }
            maxlen = Math.max(maxlen, dp[i]);
        }
        return maxlen;
    }
}

```
### Approach 2: Left to Right (L to R)
This version calculates the LDS ending at index i by looking at elements to its left.
```java

public class Solution {
    public static int LDS(int[] arr) {
        int size = arr.length;
        int[] dp = new int[size];
        int maxlen = 0;

        // Iterating Left to Right
        for (int i = 0; i < size; i++) {
            dp[i] = 1;
            for (int j = i - 1; j >= 0; j--) {
                if (arr[j] > arr[i]) {
                    dp[i] = Math.max(dp[j] + 1, dp[i]);
                }
            }
            maxlen = Math.max(maxlen, dp[i]);
        }
        return maxlen;
    }
}
```
## Longest Increasing Subsequence (LIS)
### Approach 1: Right to Left (R to L)
When moving backwards, an "increasing" sequence means the elements to the right must be larger than the current element.

```java
import java.util.ArrayList;

public class Solution {
    public static int LIS(ArrayList<Integer> heights, int n) {
        int maxlen = 0;
        int[] dp = new int[n];
        
        for (int i = n - 1; i >= 0; i--) {
            dp[i] = 1;
            for (int j = i + 1; j < n; j++) {
                if (heights.get(j) > heights.get(i)) {
                    dp[i] = Math.max(1 + dp[j], dp[i]);
                }
            }
            maxlen = Math.max(dp[i], maxlen);
        }
        return maxlen;
    }
}
```

### Approach 2: Left to Right (L to R)
This is the standard DP approach: for each element i, check all previous elements j to see if they can extend an increasing sequence.


```java
import java.util.ArrayList;

public class Solution {
    public static int LIS(ArrayList<Integer> heights, int n) {
        int maxlen = 0;
        int[] dp = new int[n];
        
        for (int i = 0; i < n; i++) {
            dp[i] = 1;
            for (int j = i - 1; j >= 0; j--) {
                if (heights.get(j) < heights.get(i)) {
                    dp[i] = Math.max(1 + dp[j], dp[i]);
                }
            }
            maxlen = Math.max(dp[i], maxlen);
        }
        return maxlen;
    }
}

```

# Analysis of LIS and LDS: 4 DP Approaches

Using the example array: **`arr = [10, 20, 10, 30, 20]`**

---

## 1. Longest Decreasing Subsequence (LDS)

### Approach 1: Right to Left (R to L)
- **Logic:** `dp[i]` stores the length of the longest decreasing subsequence **starting** at index `i` and extending to the right.
- **Example Trace:**
    - `dp[4]` (20): `[20]` → Length 1
    - `dp[3]` (30): `[30, 20]` → Length 2
    - `dp[2]` (10): `[10]` → Length 1
    - `dp[1]` (20): `[20, 10]` → Length 2
    - `dp[0]` (10): `[10]` → Length 1
- **Final Answer:** `max(dp)` = **2** (e.g., `[30, 20]`).

### Approach 2: Left to Right (L to R)
- **Logic:** `dp[i]` stores the length of the longest decreasing subsequence **ending** at index `i`.
- **Example Trace:**
    - `dp[0]` (10): `[10]` → Length 1
    - `dp[1]` (20): `[20]` → Length 1
    - `dp[2]` (10): `[20, 10]` → Length 2
    - `dp[3]` (30): `[30]` → Length 1
    - `dp[4]` (20): `[30, 20]` → Length 2
- **Final Answer:** `max(dp)` = **2** (e.g., `[20, 10]`).

---

## 2. Longest Increasing Subsequence (LIS)



### Approach 1: Right to Left (R to L)
- **Logic:** `dp[i]` stores the length of the longest increasing subsequence **starting** at index `i` and extending to the right.
- **Example Trace:**
    - `dp[4]` (20): `[20]` → Length 1
    - `dp[3]` (30): `[30]` → Length 1
    - `dp[2]` (10): `[10, 30]` or `[10, 20]` → Length 2
    - `dp[1]` (20): `[20, 30]` → Length 2
    - `dp[0]` (10): `[10, 20, 30]` → Length 3
- **Final Answer:** `max(dp)` = **3** (e.g., `[10, 20, 30]`).

### Approach 2: Left to Right (L to R)
- **Logic:** `dp[i]` stores the length of the longest increasing subsequence **ending** at index `i`.
- **Example Trace:**
    - `dp[0]` (10): `[10]` → Length 1
    - `dp[1]` (20): `[10, 20]` → Length 2
    - `dp[2]` (10): `[10]` → Length 1
    - `dp[3]` (30): `[10, 20, 30]` → Length 3
    - `dp[4]` (20): `[10, 20]` → Length 2
- **Final Answer:** `max(dp)` = **3** (e.g., `[10, 20, 30]`).

---

## Summary Table of Behaviours

| Code Type | Direction | Physical Meaning of `dp[i]` |
| :--- | :--- | :--- |
| **LDS (1)** | Right to Left | Max length of Decreasing sequence **starting** at `i`. |
| **LDS (2)** | Left to Right | Max length of Decreasing sequence **ending** at `i`. |
| **LIS (1)** | Right to Left | Max length of Increasing sequence **starting** at `i`. |
| **LIS (2)** | Left to Right | Max length of Increasing sequence **ending** at `i`. |



---
**Why calculate both?** The handwritten notes in your image suggest that passing these problems on platforms like Coding Ninjas/CodeStudio requires understanding these directional shifts. For example, to find the **Longest Bitonic Subsequence**, you combine LIS (L to R) and LDS (R to L).

 ![alt text](<006 LIS_231124_134844(9).jpg>) ![alt text](<006 LIS_231124_134844(10).jpg>) ![alt text](<006 LIS_231124_134844(11).jpg>) ![alt text](<006 LIS_231124_134844(12).jpg>) ![alt text](<006 LIS_231124_134844(13).jpg>) ![alt text](<006 LIS_231124_134844(14).jpg>) ![alt text](<006 LIS_231124_134844(15).jpg>)





