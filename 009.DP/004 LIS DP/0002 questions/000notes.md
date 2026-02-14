# Notes

![alt text](<007 LIS_231121_163402.jpg>)
![alt text](<007 LIS_231121_163402(1).jpg>) ![alt text](<007 LIS_231121_163402(2).jpg>) ![alt text](<007 LIS_231121_163402(3).jpg>) ![alt text](<007 LIS_231121_163402(4).jpg>) ![alt text](<007 LIS_231121_163402(5).jpg>) ![alt text](<007 LIS_231121_163402(6).jpg>)

![alt text](<007 LIS_231121_163402(7).jpg>) ![alt text](<007 LIS_231121_163402(8).jpg>) ![alt text](<007 LIS_231121_163402(9).jpg>) ![alt text](<007 LIS_231121_163402(10).jpg>) ![alt text](<007 LIS_231121_163402(11).jpg>) ![alt text](<007 LIS_231121_163402(12).jpg>) ![alt text](<007 LIS_231121_163402(13).jpg>) ![alt text](<007 LIS_231121_163402(14).jpg>) ![alt text](<007 LIS_231121_163402(15).jpg>)


# C++ Binary Search Functions: `lower_bound` and `upper_bound`

Both functions are found in the `<algorithm>` header. They use binary search to find specific positions in a **sorted** range.

---

##  Core Logic Comparison

| Function | Condition | Description |
| :--- | :--- | :--- |
| **`std::lower_bound`** | `*it >= value` | Returns an iterator to the **first** element that is **not less** than the given value. |
| **`std::upper_bound`** | `*it > value` | Returns an iterator to the **first** element that is **strictly greater** than the given value. |


By mistake in upper notes we said upper bound is gretaer than or equal to but it is not ,it is lower bound

----

# Understanding `std::size_t` (The Return Type of `.size()`)

### 1. What is it?
`std::size_t` is an **unsigned integer type**. It is defined by the C++ standard to be large enough to represent the size of the largest possible object your computer's architecture can create.

* **On a 64-bit system:** It is usually an `unsigned long long` (8 bytes).
* **On a 32-bit system:** It is usually an `unsigned int` (4 bytes).



---

### 2. Why is it Unsigned?
Because a string or a container cannot have a "negative" number of elements. Using an unsigned type allows the range of the number to be twice as large as a signed type of the same bit-width.

> **The Range:**
> If an `int` goes from -2,147,483,648 to 2,147,483,647...
> A `size_t` of the same size goes from **0 to 4,294,967,295**.

---

### 3. The "Danger Zone": Underflow
The biggest mistake beginners make is subtracting two `.size()` values. Because they are unsigned, if the result should be negative, it "wraps around" to the maximum possible value of the type.

**Example:**
```cpp
string s = "abc"; // size 3
if (s.size() - 5 > 0) { 
    // This will actually be TRUE!
    // 3 - 5 becomes a massive positive number (e.g., 18,446,744,073,709,551,614)
}
```

never do

```cpp
 if(abs((int)s1.size()-(int)s2.size())>1) return false;
 ```

 Now see question
# Problem: Longest String Chain

### 1. Description
You are given an array of strings `words`. A word `s1` is a **predecessor** of word `s2` if and only if you can insert exactly one character anywhere in `s1` to make it equal to `s2`.

* For example, `"abc"` is a predecessor of `"abac"`, while `"cba"` is not a predecessor of `"bcad"`.

A **word chain** is a sequence of words `[word_1, word_2, ..., word_k]` where each `word_i` is a predecessor of `word_{i+1}` for all `1 <= i < k`. 

**Goal:** Return the length of the **longest possible word chain** that can be formed using words from the given list.

---

### 2. Constraints
* $1 \le words.length \le 1000$
* $1 \le words[i].length \le 16$
* `words[i]` only consists of lowercase English letters.

---
Example 1

Input: words = ["a", "ab", "abc", "abcd", "abcde"]

Output: 5

Explanation: The longest chain is ["a", "ab", "abc", "abcd", "abcde"].

Each word in the chain is formed by adding exactly one character to the previous word.

---

Example 2

Input: words = ["dog", "dogs", "dots", "dot", "d", "do"]

Output: 4

Explanation: The longest chain is ["d", "do", "dot", "dots"].

Each word is formed by inserting one character into the previous word.
---

### 3. Example Walkthrough
**Input:** `words = ["a", "b", "ba", "bca", "bda", "bdca"]`

1.  **"a"** -> **"ba"** -> **"bca"** -> **"bdca"** (Length 4)
2.  **"a"** -> **"ba"** -> **"bda"** -> **"bdca"** (Length 4)
3.  **"b"** -> **"ba"** -> **"bca"** -> **"bdca"** (Length 4)

**Output:** `4`

## My first code

 ```cpp
class Solution {
    bool isWordiSuccesorWordj(string &s1,string &s2){
        if(abs((int)s1.size()-(int)s2.size())>1) return false;
        int diff=0;
        int i=0;int j=0;
        while(i<s1.size()){
            if(s1[i]==s2[j]){
                i++;
                j++;
            }else{
                diff++;
                i++;
            }
        }
        return diff==1;
    }
public:
    int longestStringChain(vector<string>& wor) {
        sort(wor.begin(),wor.end());
        int n=wor.size();
        int res=1;
        vector<int> dp(n,1);
        for(int i=1;i<n;i++){

            for(int j=i-1;j>=0;j--){
                if(isWordiSuccesorWordj(wor[i],wor[j])==true){
                    dp[i]=max(dp[i],dp[j]+1);
                }
            }

            res=max(dp[i],res);
        }

        return res;
    }
};

 ```

 Here isWordiSuccesorWordj

 This looks more like a "One Edit Distance" check.

The Bug: If s1 and s2 are the same length but have one different character (e.g., "pale" and "pate"), diff will be 1, but j will increment out of bounds.

What happens inside the while loop :

i=0, j=0: 'p' == 'p' (Match! i=1, j=1)

i=1, j=1: 'a' == 'a' (Match! i=2, j=2)

i=2, j=2: 'l' != 't' (Mismatch! diff=1, i=3)

i=3, j=2: 'e' != 't' (Mismatch! diff=2, i=4)

The loop ends, and it returns diff == 1.

it only increments j on a match. In "pale" vs "pate", once you hit a mismatch, j stops moving, but i keeps going, leading to multiple mismatches or out-of-bounds errors. 

The Logic Flaw: A "successor" is almost always defined as an insertion. This allows for replacement if you aren't careful with lengths.

 # Default Sort vs. Length Sort

### 1. Default Sort: `sort(wor.begin(), wor.end())`
- **Behavior:** Lexicographical order (Dictionary).
- **Comparison:** `s < t` compares characters.
- **Use Case:** Alphabetical listing or binary search readiness.

```cpp
vector<string> words = {"banana", "at", "apple", "dog"};
sort(words.begin(), words.end());
// Result: {"apple", "at", "banana", "dog"}
```

### 2. Custom Sort: `sort(wor.begin(), wor.end(), compare)`
- **Behavior:** Length-based order.
- **Comparison:** `s.size() < t.size()`.
- **Use Case:** Problems like **Word Ladders** or **Longest String Chain** where we must process shorter words before longer ones.

```cpp
bool static compare(string &s, string &t) {
    return s.size() < t.size();
}

vector<string> words = {"banana", "at", "apple", "dog"};
sort(words.begin(), words.end(), compare);
// Result: {"at", "dog", "apple", "banana"}
```

### 3. The `static` Keyword
In C++, `std::sort` requires a pointer to a function. A non-static member function has a hidden `this` pointer, which `std::sort` cannot handle. Declaring it `static` removes the `this` pointer requirement.

If your compare function is inside a class (like in LeetCode), it must be static.

Non-static: Belong to an instance of the class. std::sort doesn't know which object to use to call the function.

Static: Belong to the class itself. std::sort can call it directly like a regular global function.

### Accepted solution

```cpp
class Solution {
    bool static compare(string &s, string &t) {
        return s.size() < t.size();
    }
    bool isWordiSuccesorWordj(string &s1,string &s2){
        if(s1.size()!=s2.size()+1) return false;
        int i=0;int j=0;
        while(i<s1.size()){
            if(s1[i]==s2[j]){
                i++;
                j++;
            }else{
                i++;
            }
        }
        if(i == s1.size() && j == s2.size()) return true;
        return false; // Return false otherwise
    }
public:
    int longestStringChain(vector<string>& wor) {
        sort(wor.begin(),wor.end(),compare);
        int n=wor.size();
        int res=1;
        vector<int> dp(n,1);
        for(int i=1;i<n;i++){

            for(int j=i-1;j>=0;j--){
                if(isWordiSuccesorWordj(wor[i],wor[j])==true){
                    dp[i]=max(dp[i],dp[j]+1);
                }
            }

            res=max(dp[i],res);
        }

        return res;
    }
};

```


## Q  Largest Divisible Subset

### Problem Statement
Given an array `nums` of positive integers, the task is to find the largest subset such that every pair `(a, b)` of elements in the subset satisfies `a % b == 0` or `b % a == 0`.

Return the subset in any order. If there are multiple solutions, return any one of them.

**Note:** As there can be multiple correct answers, the compiler returns 1 if the answer is valid, else 0.

### Examples

**Example 1**
```text
Input: nums = [3, 5, 10, 20]
Output: [5, 10, 20]
Explanation: The subset [5, 10, 20] satisfies the divisibility condition: 10 % 5 == 0 and 20 % 10 == 0.
```
**Example 2**
```text
Input: nums = [16, 8, 2, 4, 32]
Output: [2, 4, 8, 16, 32]
Explanation: The entire array forms a divisible subset since 32 % 16 == 0, 16 % 8 == 0, and so on.
```

### Constraints
- $1 \leq \text{nums.length} \leq 10^3$
- $1 \leq \text{nums}[i] \leq 10^6$

### My sol
```cpp
class Solution {
    void display(vector<int> &ans) {
        for (int el : ans) {
            cout << el << " ";
        }
    }

   public:
    vector<int> largestDivisibleSubset(vector<int> nums) {
        int n = nums.size();
        int idx = 0;
        sort(nums.begin(), nums.end());
        int res = 1;
        vector<vector<int>> dp(n, vector<int>(2, 0));
        dp[0][0] = 1;
        for (int i = 1; i < n; i++) {
            dp[i][0] = 1;
            dp[i][1] = i;
            for (int j = i - 1; j >= 0; j--) {
                if (nums[i] % nums[j] == 0) {
                    if (dp[j][0] + 1 > dp[i][0]) {
                        dp[i][0] = dp[j][0] + 1;
                        dp[i][1] = j;
                    }
                }
            }

            if (dp[i][0] > res) {
                res = dp[i][0];
                idx = i;
            }
        }
        int i = idx;
        vector<int> ans;
        while (dp[i][1] != i) {
            ans.push_back(nums[i]);
            i = dp[i][1];
        }
        ans.push_back(nums[i]);
        return ans;
    }
};

```

## Ai review

### Your current DP structure is `vector<vector<int>>`.

* **Issue:** In C++, a `vector<vector<int>>` is not contiguous in memory. Each inner vector (row) is allocated separately on the heap. This causes **cache misses** when accessing `dp[j][0]` because the CPU cannot predict the memory location of the next row effectively.
* **Fix:** Use **two separate 1D arrays** (or vectors). This keeps the data for each property contiguous in memory, maximizing cache locality and significantly speeding up the inner loop.

```cpp
vector<int> largestDivisibleSubset(vector<int>& nums) { // Pass by reference to avoid copy
    int n = nums.size();
    if (n == 0) return {};
    sort(nums.begin(), nums.end());
    
    // Optimization: Two 1D arrays instead of one 2D array
    vector<int> count(n, 1); 
    vector<int> prev(n);
    
    int maxLen = 1, maxIdx = 0;

    for (int i = 0; i < n; i++) {
        prev[i] = i; // Initialize parent to self
        for (int j = 0; j < i; j++) {
            if (nums[i] % nums[j] == 0 && count[j] + 1 > count[i]) {
                count[i] = count[j] + 1;
                prev[i] = j;
            }
        }
        
        if (count[i] > maxLen) {
            maxLen = count[i];
            maxIdx = i;
        }
    }

    vector<int> ans;
    while (prev[maxIdx] != maxIdx) {
        ans.push_back(nums[maxIdx]);
        maxIdx = prev[maxIdx];
    }
    ans.push_back(nums[maxIdx]); // Push the last element (root)
    return ans;
}
```
Can we optimize to O(nlog n)??


### The short answer is No, you cannot solve this in $O(N \log N)$.

This is a very common point of confusion because this problem looks almost identical to the **Longest Increasing Subsequence (LIS)** problem, which *can* be solved in $O(N \log N)$.

Here is the "Senior Engineer" breakdown of why the optimization works for LIS but fails for LDS.

### 1. Why LIS is $O(N \log N)$ (The "Greedy" Property)
In the Longest Increasing Subsequence problem, if you have two subsequences of length 3:
* **Sequence A** ends with 5.
* **Sequence B** ends with 100.

**Sequence A is strictly better.** Why? Because it is "easier" to extend. Any number that can come after 100 can also come after 5 (since $X > 100 \implies X > 5$). 

Because of this "smaller is always better" property, we can discard the 100 and just keep the 5. This allows us to use **Binary Search** to maintain a single "best candidates" list.

### 2. Why LDS fails this Property
In the Largest Divisible Subset, "smaller" is **NOT** always better. Imagine you have two subsets of length 2:
* **Subset A** ends with 6 (e.g., `[2, 6]`)
* **Subset B** ends with 8 (e.g., `[4, 8]`)

Which one is "better"? **Neither.**
* If the next number is 12, it works with 6 ($12 \% 6 == 0$) but **fails** with 8.
* If the next number is 16, it works with 8 ($16 \% 8 == 0$) but **fails** with 6.

You cannot discard the 8 just because 6 is smaller. They belong to different "divisibility chains" (multiples of 3 vs. multiples of 2). You have to track both possibilities independently, forcing you to check every previous element.

### 3. The "Pseudo" Optimization ($O(N \cdot \sqrt{V})$)
If the values of the numbers are small (e.g., `nums[i] <= 10^5`), you can optimize it, but not to $O(N \log N)$. Instead of checking `j` from `0` to `i-1` ($O(N^2)$), you can iterate through the **divisors** of `nums[i]`.

1. Map every value to its max subset length: `dp_map`.
2. For `nums[i] = 12`: Check `dp_map[1], dp_map[2], dp_map[3], dp_map[4], dp_map[6]`.
3. Take the `max + 1`.

**Complexity:** $O(N \cdot \text{number\_of\_divisors})$. For 32-bit integers, this is often faster than $N^2$ in practice, but mathematically it is not $O(N \log N)$.

### Summary for Interviews
> "Unlike LIS, where a smaller tail value is strictly superior, the Divisibility property is a **partial order**, not a total order. A tail of 6 is not 'better' than a tail of 8; they simply accept different future values. Therefore, we cannot use the Binary Search optimization, and we are stuck with $O(N^2)$ or $O(N \sqrt{V})$."

$O(N \sqrt{V})$ Approach!!

### Here is the $O(N \cdot \sqrt{V})$ approach.

This approach flips the logic: instead of looking back at all previous indices $j$ (which depends on $N$), we look at the divisors of the current number (which depends on the value $V$).

### When to use this?

| Approach | Best Use Case | Constraint Example |
| :--- | :--- | :--- |
| **$O(N^2)$ Approach** | Best when $N$ is small but values can be huge. | $N \leq 2000$, $V = 10^9$ |
| **$O(N \cdot \sqrt{V})$ Approach** | Best when $N$ is huge but values are relatively small. | $N = 10^5$, $V \leq 10^6$ |
```cpp
#include <vector>
#include <algorithm>
#include <unordered_map>

using namespace std;

class Solution {
public:
    vector<int> largestDivisibleSubset(vector<int>& nums) {
        // 1. Sort is mandatory so we process smaller divisors first
        sort(nums.begin(), nums.end());
        
        // dp[val] = Length of largest subset ending with value 'val'
        unordered_map<int, int> dp;
        // parent[val] = The value that comes before 'val' in the chain
        unordered_map<int, int> parent;
        
        int maxLen = 0;
        int maxVal = -1;
        
        for (int x : nums) {
            dp[x] = 1;       // Base case: element itself
            parent[x] = -1;  // No parent initially
            
            // 2. Iterate all divisors of x up to sqrt(x)
            for (int d = 1; d * d <= x; ++d) {
                if (x % d == 0) {
                    // Check divisor 'd'
                    if (dp.count(d) && dp[d] + 1 > dp[x]) {
                        dp[x] = dp[d] + 1;
                        parent[x] = d;
                    }
                    
                    // Check divisor 'x/d' (the pair of d)
                    int d2 = x / d;
                    if (d2 != d && dp.count(d2) && dp[d2] + 1 > dp[x]) {
                        dp[x] = dp[d2] + 1;
                        parent[x] = d2;
                    }
                }
            }
            
            // Track the global maximum
            if (dp[x] > maxLen) {
                maxLen = dp[x];
                maxVal = x;
            }
        }
        
        // 3. Reconstruct the path using the parent map
        vector<int> ans;
        while (maxVal != -1) {
            ans.push_back(maxVal);
            maxVal = parent[maxVal];
        }
        
        return ans;
    }
};
```

### The Logic Breakdown

**1. The Map instead of Array**
Since we are iterating by **Value** ($V$), not Index, we can't use a simple DP array unless we make it size $V_{max}$ (which could be huge).
* **Solution:** Use a Hash Map (`unordered_map`).
* `dp[12] = 3` means "The largest subset ending with value 12 has length 3."

**2. The Divisor Loop ($\sqrt{V}$)**
For a number like $x = 12$, we don't scan the whole array. We only generate its mathematical factors: $1, 2, 3, 4, 6$.
We check the map: *"Hey, have I seen a subset ending in 6?"* If `dp[6]` exists, we know 12 is divisible by 6, so we can attach 12 to that chain.
* **New Length** = `dp[6] + 1`.

**3. Why Sort?**
Sorting ensures that when we process 12, we have already processed 1, 2, 3, 4, and 6. The map is guaranteed to have the correct answers for all smaller numbers.

### Performance Analysis
* **Time Complexity:** $O(N \cdot \sqrt{V_{max}})$. For every number, we do a square root loop.
* **Space Complexity:** $O(N)$. We store every number in the map.

---

### "Senior Engineer" Verdict
In an interview, you should mention this:
> "If the input values are bounded (e.g., $10^6$), this approach is faster because $\sqrt{10^6} = 1000$, which is constant. However, if values can go up to $2 \cdot 10^9$ (max integer), $\sqrt{V} \approx 45,000$, which might be slower than $N$ if $N$ is small. I would stick to the $O(N^2)$ approach for standard inputs but switch to this one if $N$ is very large and $V$ is small."