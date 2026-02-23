# Sliding Window: The Undisputed King of Off-By-One Errors (OBOEs)

Most candidates panic and start randomly adding `+1` or `-1` to their `left` and `right` pointers until the sample test case passes. But a Senior Engineer relies on strict mathematical definitions.

Here is the ultimate cheat sheet to never mess up a sliding window length calculation again.

### 1. The Golden Formula: Length = `right - left + 1`
If both `left` and `right` are inclusive (meaning they are pointing at actual elements in your window), the number of elements is always `right - left + 1`.
* **The Proof:** If `left` is at index 2 and `right` is at index 2, your window has exactly 1 element.
    * **Wrong Math:** 2 - 2 = 0.
    * **Right Math:** 2 - 2 + 1 = 1.
* **The Analogy:** Think of indices as fence posts. If you build a fence from post 5 to post 7, the distance is 2 meters, but you actually touched 3 posts (5, 6, and 7). You are counting posts, not distance.

### 2. Scenario A: The Fixed-Size Window (Size K)
* **Problem:** "Find the max sum of a subarray of size K."
* **The Trap:** Candidates often write `if (right == K)` to check if the window is full. This is wrong. If K = 3, the first window ends at index 2 (0, 1, 2).

**The Senior Template:**
Instead of tracking indices, always track the Length Formula.

```cpp
int left = 0, right = 0;
while (right < N) {
    // 1. Add current element to your state
    sum += arr[right];

    // 2. Check if window size has hit K
    if (right - left + 1 == K) {
        ans = max(ans, sum);       // Record answer
        sum -= arr[left];          // Remove left element from state
        left++;                    // Slide window forward
    }
    
    // 3. Expand the window
    right++;
}
```

### 3. Scenario B: The Variable-Size Window
* **Problem:** "Find the longest subarray with a sum <= target."
* **The Trap:** Calculating the length before making sure the window is valid, or incrementing `right` too early and calculating the length using the wrong `right` index.

**The Senior Template:**
Always follow this exact 4-step order. Do not mix them up.

```cpp
int left = 0, right = 0, max_len = 0;
while (right < N) {
    // Step 1: Add arr[right] to state
    sum += arr[right];

    // Step 2: If state is invalid, shrink from the left UNTIL valid
    while (sum > target && left <= right) {
        sum -= arr[left];
        left++;
    }

    // Step 3: NOW the window is 100% valid. Calculate length safely.
    max_len = max(max_len, right - left + 1);

    // Step 4: Expand window
    right++;
}
```

### 4. The "Length to Index" Reverse Math
Sometimes a problem asks you to extract a substring using `.substr(start_index, length)`.

* If you know your window spans from `left` to `right`, the length is `right - left + 1`.
    * **Example:** `string ans = s.substr(left, right - left + 1);`
* If a problem gives you a length and a start index, and you need to find the end index (inclusive):
    * **Formula:** `end = start + length - 1`.
    * **Example:** Start at index 4, length is 3. End = 4 + 3 - 1 = 6. (Indices 4, 5, 6).

### Summary of the Rules:
* Always use `[left, right]` as inclusive boundaries.
* Window size is always `right - left + 1`.
* In variable windows, always shrink *before* you calculate the max length.


Q--> so what if in interview i get off by 1 ??

# How to Handle Off-By-One Errors (OBOEs) in Interviews

If you find yourself stuck with an **Off-By-One** error in an interview, don't panic. How you handle it actually reveals more about your "Seniority" than getting it right the first time.

Here is the professional way to fix it without looking like you're guessing.

### 1. Own it immediately (Don't hide it)
If your test case fails with a result of 4 when it should be 5, don't just stare at the code and start adding `+1` everywhere. Say:
> "It looks like I have a classic Off-By-One error. Let me trace a tiny, 2-element example to see if my boundaries are inclusive or exclusive."

### 2. The "Atomic Example" Technique
Immediately pick the smallest possible input (usually size 1 or 2).
* **Example:** "Let's say the window is at `left = 0` and `right = 0`."
* **The Question:** "Does this window have 0 elements or 1 element?"
* **The Logic:** "My code says `right - left` which is 0. But index 0 has an element, so it should be 1. Therefore, I need `+1`."

### 3. Check the "Transition" Points
Off-By-One errors usually hide in the `while` loop condition or the initialization. Ask yourself these three questions out loud:
* **The Start:** Is `right` starting at 0 or 1?
* **The End:** Is the loop `while(right < n)` or `while(right <= n)`?
* **The Comparison:** If the window size is $K$, should I check `if(length == K)` or `if(length > K)`?

### 4. Use the "Fence Post" Analogy
Explain your logic to the interviewer using this mental model:
> "I'm treating these indices as **posts**, not the **gaps** between them. Since I want to count the posts from index $i$ to index $j$, I must use the formula $j - i + 1$."

### 5. Never "Double-Adjust"
A common mistake is adding `+1` to the length AND changing the loop to `<=` at the same time.
* **Senior Rule:** Change **one** thing, then re-trace your atomic example. If you change two things at once, you’ll likely create a new bug.

---

### The "Senior" Recovery Script
If you're still stuck, use this line:
> "To be safe and avoid OBOEs, I'll stick to a strict **inclusive boundary** $[left, right]$ policy. This means my length is always $right - left + 1$, and my loop ends at $n-1$. Let me adjust the logic to fit that contract."

This shows the interviewer you have a system for correctness, rather than just relying on luck.

Q-->so everywhere i can use r-l+1 rule to avoid confusion?

# How to Handle Off-By-One Errors (OBOEs) in Interviews

If you find yourself stuck with an **Off-By-One** error in an interview, don't panic. How you handle it actually reveals more about your "Seniority" than getting it right the first time.

Here is the professional way to fix it without looking like you're guessing.

### 1. Own it immediately (Don't hide it)
If your test case fails with a result of 4 when it should be 5, don't just stare at the code and start adding `+1` everywhere. Say:
> "It looks like I have a classic Off-By-One error. Let me trace a tiny, 2-element example to see if my boundaries are inclusive or exclusive."

### 2. The "Atomic Example" Technique
Immediately pick the smallest possible input (usually size 1 or 2).
* **Example:** "Let's say the window is at `left = 0` and `right = 0`."
* **The Question:** "Does this window have 0 elements or 1 element?"
* **The Logic:** "My code says `right - left` which is 0. But index 0 has an element, so it should be 1. Therefore, I need `+1`."

### 3. Check the "Transition" Points
Off-By-One errors usually hide in the `while` loop condition or the initialization. Ask yourself these three questions out loud:
* **The Start:** Is `right` starting at 0 or 1?
* **The End:** Is the loop `while(right < n)` or `while(right <= n)`?
* **The Comparison:** If the window size is $K$, should I check `if(length == K)` or `if(length > K)`?

### 4. Use the "Fence Post" Analogy
Explain your logic to the interviewer using this mental model:
> "I'm treating these indices as **posts**, not the **gaps** between them. Since I want to count the posts from index $i$ to index $j$, I must use the formula $j - i + 1$."

### 5. Never "Double-Adjust"
A common mistake is adding `+1` to the length AND changing the loop to `<=` at the same time.
* **Senior Rule:** Change **one** thing, then re-trace your atomic example. If you change two things at once, you’ll likely create a new bug.

---

### The "Senior" Recovery Script
If you're still stuck, use this line:
> "To be safe and avoid OBOEs, I'll stick to a strict **inclusive boundary** $[left, right]$ policy. This means my length is always $right - left + 1$, and my loop ends at $n-1$. Let me adjust the logic to fit that contract."

This shows the interviewer you have a system for correctness, rather than just relying on luck.


# Mastering Window Boundaries: `n - k` vs `n - k + 1`

Whether you use `<` or `<=` depends entirely on whether your loop variable represents the **Starting Index** of the window or the **Total Number of Shifts**.

### 1. The "Starting Index" Logic
If you are using a loop to find every possible starting position of a window of size `K` in a string/array of size `N`:

* **The Math:** If the string has length `N` and the window has length `K`, the **last valid starting index** is `N - K`.
* **The Proof:** String "HELLO" (`N=5`), Window size `K=3`.
    * Index 0: "HEL" (Valid)
    * Index 1: "ELL" (Valid)
    * Index 2: "LLO" (Valid, this is `5 - 3 = 2`)
    * Index 3: "LO?" (Invalid - out of bounds)

**The Correct Code:**
```cpp
// Using <= (Inclusive of the last valid index)
for (int i = 0; i <= (int)s.size() - k; i++) { 
    // i will go up to exactly N-K
}

// OR using < (Exclusive of the first invalid index)
for (int i = 0; i < (int)s.size() - k + 1; i++) {
    // i will stop at N-K
}
```



### 2. The "Total Windows" Formula
If a problem asks how many possible windows of size `K` exist in a sequence of size `N`:
* **Formula:** `Total Windows = N - K + 1`
* **Example:** In "HELLO" (5), there are `5 - 3 + 1 = 3` windows of size 3.

### 3. Comparison Table: `<` vs `<=`

| Approach | Loop Condition | Logic |
| :--- | :--- | :--- |
| **Inclusive (`<=`)** | `i <= n - k` | `n - k` is the **last index** that can fit a full window. You must include it. |
| **Exclusive (`<`)** | `i < n - k + 1` | You want to stop **just before** you hit the first invalid index (`n - k + 1`). |

### 4. How to decide in an interview?
Don't rely on memory; use the **"Same Size" Mental Trace**:

1.  **Pick a tiny example:** String `"ABC"` (`N=3`), Window size `K=3`.
2.  **Determine the goal:** There is exactly **one** window, and its starting index is **0**.
3.  **Test `<=`:** `i <= 3 - 3` $\to$ `i <= 0`. Loop runs for `i=0`. **(Correct)**
4.  **Test `<`:** `i < 3 - 3` $\to$ `i < 0`. Loop never runs. **(Wrong)**

### Summary Cheat Sheet
* **Last valid starting index:** `n - k`
* **Total number of windows:** `n - k + 1`
* **Loop condition:** `i <= n - k`

# Q 1461. Check If a String Contains All Binary Codes of Size K

Given a binary string `s` and an integer `k`, return `true` if every binary code of length `k` is a substring of `s`. Otherwise, return `false`.

### Example 1:

**Input:** `s = "00110110", k = 2`  
**Output:** `true`  
**Explanation:** The binary codes of length 2 are "00", "01", "10" and "11". They can be all found as substrings at indices 0, 1, 3 and 2 respectively.

### Example 2:

**Input:** `s = "0110", k = 1`  
**Output:** `true`  
**Explanation:** The binary codes of length 1 are "0" and "1", it is clear that both exist as a substring.

### Example 3:

**Input:** `s = "0110", k = 2`  
**Output:** `false`  
**Explanation:** The binary code "00" is of length 2 and does not exist in the array.

### Constraints:

* `1 <= s.length <= 5 * 10^5`
* `s[i]` is either `'0'` or `'1'`.
* `1 <= k <= 20`

```cpp
class Solution {
public:
    bool hasAllCodes(string s, int k) {
        if(s.size()<k) return false;
        unordered_set<string> set;
        for(int i=0;i<=s.size()-k;i++){
           set.insert( s.substr(i,k));
        }
        return set.size()==(1<<k);
    }
};
```
Here i was using  less than k so code was not getting last string!!



* **Very imp Pro Tip:** Always handle the case where `n < k` before the loop starts to avoid logic errors.
> **⚠️ The "Unsigned" Trap (C++ Specific):**
> `s.size()` returns an **unsigned** integer (`size_t`). If `s.size()` is smaller than `k`, `s.size() - k` will not be a negative number; it will **underflow** into a massive positive number (e.g., 4,294,967,295). Your loop will run forever and crash.
> **Senior Fix:** Always cast to int: `(int)s.size() - k`.



