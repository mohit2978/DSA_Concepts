## Sliding Window — Complete Pattern Guide

### The Two Types of Sliding Window

```
Type 1 — FIXED size window
  window size k is given
  slide one step at a time
  add right element, remove left element

Type 2 — VARIABLE size window
  window size changes based on condition
  expand right always
  shrink left when condition violated or met
```

---

### The Fixed Window Template

```cpp
// find something in every window of size k
int l = 0;
// build first window
for (int r = 0; r < k; r++)
    // add s[r] to window

for (int r = k; r < n; r++) {
    // add s[r] (new right element)
    // remove s[l] (old left element)
    l++;
    // update answer
}
```

---

### The Variable Window Template

```cpp
int l = 0;
for (int r = 0; r < n; r++) {
    // expand: add s[r] to window

    // shrink: while condition violated
    while (condition violated) {
        // remove s[l] from window
        l++;
    }
    // update answer (window is now valid)
}
```

---

### All Common Patterns — One by One

---

#### Pattern 1 — Fixed Window Maximum/Minimum

**Problem:** Maximum sum subarray of size k

```
Logic:
  maintain running sum
  add new right element
  subtract old left element
  track maximum
```

```cpp
int maxSumSubarray(vector<int>& arr, int k) {
    int n = arr.size();
    int sum = 0, maxSum = 0;

    // build first window
    for (int i = 0; i < k; i++) sum += arr[i];
    maxSum = sum;

    for (int r = k; r < n; r++) {
        sum += arr[r];          // add new right
        sum -= arr[r - k];      // remove old left
        maxSum = max(maxSum, sum);
    }
    return maxSum;
}
```

```
arr = [2,1,5,1,3,2], k=3

window [2,1,5] = 8
window [1,5,1] = 7
window [5,1,3] = 9  ← max
window [1,3,2] = 6

answer = 9
```

---

#### Pattern 2 — Longest Window Satisfying Condition

**Problem:** Longest substring without repeating characters

```
Logic:
  expand right always
  when duplicate found → shrink left until no duplicate
  track maximum window size
```

```cpp
int lengthOfLongestSubstring(string s) {
    unordered_map<char, int> freq;
    int l = 0, maxLen = 0;

    for (int r = 0; r < s.size(); r++) {
        freq[s[r]]++;

        // shrink until no duplicate
        while (freq[s[r]] > 1) {
            freq[s[l]]--;
            l++;
        }
        maxLen = max(maxLen, r - l + 1);
    }
    return maxLen;
}
```

```
s = "abcabcbb"

r=0: window="a"     valid, len=1
r=1: window="ab"    valid, len=2
r=2: window="abc"   valid, len=3
r=3: window="abca"  'a' duplicate!
     shrink → l=1, window="bca" valid, len=3
r=4: window="bcab"  'b' duplicate!
     shrink → l=2, window="cab" valid, len=3
...
answer = 3
```

---

#### Pattern 3 — Count Windows Satisfying Condition

**Problem:** Number of substrings with all 3 chars 

```
Logic:
  when window becomes valid
  count += (n - r)  captures all valid extensions
  then shrink to find more valid windows
```

```cpp
// already covered — the key insight:
while (valid) {
    count += (n - r);   // all extensions of current window valid
    shrink left;
}
```

### Why `count += (n - r)`

---

### The Core Insight

```
When window [l, r] contains all 3 chars:
  extending it further RIGHT can only ADD more chars
  it will NEVER become invalid by growing right

So ALL substrings starting at l and ending at r, r+1, r+2...n-1
are valid too!
```

---

### Visualise It

```
s = "abcba",  n = 5
window [l=0, r=2] = "abc" ← just became valid

Extending right:
  [0,2] = "abc"   ✅ valid
  [0,3] = "abcb"  ✅ valid (still has a,b,c)
  [0,4] = "abcba" ✅ valid (still has a,b,c)

How many? = n - r = 5 - 2 = 3  ✅
```

---

### The Count Visually

```
s = a b c b a
    0 1 2 3 4

l=0, r=2 window is valid:

  [0,2]  "abc"   ← end at r
  [0,3]  "abcb"  ← end at r+1
  [0,4]  "abcba" ← end at r+2 = n-1

count = n - r
      = 5 - 2
      = 3

These are exactly the positions from r to n-1
that's (n-1) - r + 1 = n - r positions ✅
```

---

### Why Not `r - l + 1`

```
r - l + 1  counts substrings ENDING at r
           starting from l, l+1, l+2...r

n - r      counts substrings STARTING at l
           ending at r, r+1, r+2...n-1

Both count valid substrings but from DIFFERENT perspectives:

r-l+1 → how many left endpoints give valid window ending HERE
n-r   → how many right endpoints give valid window starting HERE
```

---

### Concrete Trace

```
s = "abcba", n=5

r=2, l=0, window="abc" valid:
  count += n-r = 5-2 = 3
  substrings: [0,2],[0,3],[0,4]
  shrink: l=1, window="bc" → not valid, exit while

r=3, l=1, window="bcb" → not valid

r=4, l=1, window="bcba" valid:
  count += 5-4 = 1  → [1,4]="bcba"
  shrink: l=2, window="cba" still valid!
  count += 5-4 = 1  → [2,4]="cba"
  shrink: l=3, window="ba" → not valid

Total = 3+1+1 = 5 ✅
```

---

### One Line Summary

```
n - r  =  number of valid right endpoints
           when left endpoint is fixed at l

Because adding more chars to the right
NEVER removes existing chars from the window
so validity only grows → all extensions valid
```

---

##### n-r also gives no of substring `[r,n)`??

Yes! Exactly right.

---

### Two Ways to See `n - r`

```
Way 1 — substrings STARTING at l, ending at r..n-1:
  [l, r], [l, r+1], [l, r+2] ... [l, n-1]
  count = (n-1) - r + 1 = n - r

Way 2 — positions from r to n-1:
  r, r+1, r+2 ... n-1
  count = n - r
```

Both interpretations give the same number — just different ways of looking at it.

---

### Visualised

```
s = a b c b a     n=5
    0 1 2 3 4

l=0, r=2 window valid:

Way 1 — fix left=0, vary right endpoint:
  [0,2] [0,3] [0,4]
        ←── n-r = 3 ──→

Way 2 — positions from r to end:
  r=2, r=3, r=4
  that's indices [r, n)
  count = n - r = 3
```

---

### The Equivalence

```
"substrings starting at l, ending anywhere in [r, n-1]"
              ≡
"number of positions in [r, n)"
              ≡
n - r
```

---

### One Line

```
n - r  =  length of range [r, n)
       =  number of valid right endpoints
       =  number of valid substrings starting at current l
```

Your observation is the cleanest way to remember it — **`n - r` is simply the size of the range `[r, n)`**.


##### but according to question Number of substrings with all 3 chars which interpretattion to use??

### For This Problem — Way 1 is Correct

```
Question: count substrings containing ALL 3 chars

Window [l, r] just became valid (has a, b, c)

Fix LEFT endpoint at l
Vary RIGHT endpoint from r to n-1

[l, r]   = valid ✅ (just found)
[l, r+1] = valid ✅ (adding more chars keeps a,b,c)
[l, r+2] = valid ✅
...
[l, n-1] = valid ✅

count += n - r   ← all these substrings are valid
```

---

### Why Not Way 2

```
Way 2 says: "positions from r to n-1"
            or "substrings [r, ?]"

But that's not what we're counting.
We're counting substrings starting at l
not substrings starting at r.

[r, r]   = just one char  ❌ not valid
[r, r+1] = two chars      ❌ not valid
```

---

### The Intuition

```
s = "abcba"
      ^
      l=0, r=2 window="abc" valid

We found: starting at l=0
  how many ending positions make it valid?
  answer: all positions from r to n-1
  because extending right NEVER breaks validity

count += n - r = 3

Meaning:
  "abc"   [0,2] ✅
  "abcb"  [0,3] ✅
  "abcba" [0,4] ✅
```

---

### One Line

```
n - r  =  number of valid substrings
          with LEFT end fixed at l
          RIGHT end anywhere in [r, n-1]

Way 1 is correct because:
  we shrink l (left endpoint changes)
  r is the MINIMUM right endpoint for validity
  everything beyond r is automatically valid
```


#### Pattern 4 — Minimum Window Satisfying Condition

**Problem:** Minimum window substring containing all chars of t

```
Logic:
  expand right until window contains all of t
  then shrink left as much as possible
  track minimum window size
```

```cpp
string minWindow(string s, string t) {
    unordered_map<char,int> need, have;
    for (char c : t) need[c]++;

    int formed = 0, required = need.size();
    int l = 0, minLen = INT_MAX, start = 0;

    for (int r = 0; r < s.size(); r++) {
        char c = s[r];
        have[c]++;

        // check if this char's freq matches requirement
        if (need.count(c) && have[c] == need[c])
            formed++;

        // shrink while window satisfies condition
        while (formed == required) {
            // update minimum
            if (r - l + 1 < minLen) {
                minLen = r - l + 1;
                start = l;
            }
            // shrink left
            have[s[l]]--;
            if (need.count(s[l]) && have[s[l]] < need[s[l]])
                formed--;
            l++;
        }
    }
    return minLen == INT_MAX ? "" : s.substr(start, minLen);
}
```

```
s="ADOBECODEBANC", t="ABC"

expand until "ADOBEC" → has A,B,C ✅
shrink → "DOBEC" still has A? NO → stop, len=6
expand → "DOBECODEBA" → has A,B,C ✅
shrink → "OBECODEBA"→"BECODEBA"→"ECODEBA"→"CODEBA"→"ODEBA"→"DEBA"
       → "EBA" no C → stop, smallest="BANC" len=4
answer = "BANC"
```

---

#### Pattern 5 — Exactly K Condition

**Problem:** Subarrays with exactly k distinct characters

```
Logic:
  "exactly k" is hard directly
  use the trick:
  exactly(k) = atMost(k) - atMost(k-1)
```

```cpp
int atMost(string s, int k) {
    unordered_map<char,int> freq;
    int l = 0, count = 0;

    for (int r = 0; r < s.size(); r++) {
        freq[s[r]]++;

        while (freq.size() > k) {   // more than k distinct
            freq[s[l]]--;
            if (freq[s[l]] == 0) freq.erase(s[l]);
            l++;
        }
        count += r - l + 1;        // all windows ending at r
    }
    return count;
}

int exactlyK(string s, int k) {
    return atMost(s, k) - atMost(s, k-1);
}
```

```
Why r-l+1?
  window [l,r] valid
  substrings ending at r: [l,r],[l+1,r],...[r,r]
  = r-l+1 substrings all valid

Why atMost(k) - atMost(k-1) = exactly(k)?
  atMost(2) counts windows with 1 or 2 distinct
  atMost(1) counts windows with exactly 1 distinct
  difference = windows with exactly 2 distinct ✅
```

---

#### Pattern 6 — Fixed Window with Sliding Maximum

**Problem:** Maximum in every window of size k (sliding window maximum)

```
Logic:
  use a DEQUE (monotonic decreasing)
  front of deque = maximum of current window
  remove elements outside window from front
  remove smaller elements from back (they'll never be max)
```

```cpp
vector<int> maxSlidingWindow(vector<int>& arr, int k) {
    deque<int> dq;    // stores indices
    vector<int> result;

    for (int r = 0; r < arr.size(); r++) {
        // remove elements outside window
        if (!dq.empty() && dq.front() < r - k + 1)
            dq.pop_front();

        // remove smaller elements from back
        while (!dq.empty() && arr[dq.back()] < arr[r])
            dq.pop_back();

        dq.push_back(r);

        // window fully formed
        if (r >= k - 1)
            result.push_back(arr[dq.front()]);
    }
    return result;
}
```

```
arr=[1,3,-1,-3,5,3,6,7], k=3

r=0: dq=[0]
r=1: 3>1 → pop 0, dq=[1]
r=2: dq=[1,2]  window formed → max=arr[1]=3
r=3: dq=[1,2,3] → max=arr[1]=3
r=4: 5>all → dq=[4] → max=5
r=5: dq=[4,5] → max=5
r=6: 6>all → dq=[6] → max=6
r=7: 7>all → dq=[7] → max=7

result=[3,3,5,5,6,7]
```
### `dq.front() < r - k + 1`

This is the **window boundary check** in sliding window maximum.

---

### What dq Stores

```cpp
deque<int> dq;   // stores INDICES not values
```

---

### What `r - k + 1` Means

```
current right pointer = r
window size           = k
window spans          = [r-k+1, r]

r - k + 1  =  leftmost valid index of current window

Example: r=5, k=3
  window = [5-3+1, 5] = [3, 5]
  leftmost valid index = 3
  any index < 3 is OUTSIDE the window
```

---

### What the Condition Means

```cpp
if (dq.front() < r - k + 1)
    dq.pop_front();
```

```
dq.front() = index of current maximum candidate

if that index < leftmost valid index:
  that element has SLID OUT of the window
  it's no longer in range [r-k+1, r]
  remove it from front of deque
```

---

### Concrete Example

```
arr = [1, 3, -1, -3, 5, 3, 6, 7]
k   = 3

r=4 (arr[4]=5):
  window = [4-3+1, 4] = [2, 4]
  leftmost valid = 2

  dq.front() = 1  (index of element 3)
  1 < 2?  YES → element at index 1 is outside window
  pop it ✅

r=5 (arr[5]=3):
  window = [5-3+1, 5] = [3, 5]
  leftmost valid = 3

  dq.front() = 2  (index of element -1)
  2 < 3?  YES → outside window → pop ✅
```

---

### Visualised

```
arr = 1  3  -1  -3  5  3  6  7
idx = 0  1   2   3  4  5  6  7

r=4, k=3, window=[2,4]:

  outside  │  inside window
  ─────────┼────────────────
  0  1     │  2   3   4
           │ -1  -3   5
           ↑
     r-k+1 = 2
     anything left of here is expired
```

---

### One Line Summary

```
r - k + 1  =  left boundary of current window

dq.front() < r - k + 1
           =  "is the maximum candidate outside the window?"
           =  YES → expired → remove from deque
```
---

### The Master Decision Table

```
Read the problem
      ↓
Fixed window size k?
  YES → fixed template, maintain running state
  NO  ↓
Find LONGEST window?
  YES → expand right, shrink when VIOLATED, ans=max(r-l+1)
  NO  ↓
Find SHORTEST window?
  YES → expand until VALID, shrink while VALID, ans=min(r-l+1)
  NO  ↓
COUNT windows?
  "at least" → shrink when valid, count+=(n-r) or count+=(r-l+1)
  "exactly k" → atMost(k) - atMost(k-1)
  "at most"  → count+=(r-l+1) directly
```

---

### Signal Words in Problems

| Problem says | Pattern |
|---|---|
| "maximum sum of size k" | fixed window |
| "longest substring without..." | variable, shrink on violation |
| "minimum window containing..." | variable, shrink on valid |
| "number of subarrays with at least..." | count += (n-r) |
| "number of subarrays with exactly k" | atMost(k)-atMost(k-1) |
| "maximum in every window of size k" | monotonic deque |
| "longest subarray with sum ≤ k" | variable, shrink on violation |

---

### The Count Formula Explained Once and For All

```
count += (r - l + 1)   →  count all windows ENDING at r
count += (n - r)       →  count all windows STARTING at l

When to use which?

(r-l+1): when window is valid and you want
          to count all valid substrings ending at r
          [l..r], [l+1..r], ..., [r..r]

(n-r):   when window is valid and you want
          to count all valid substrings starting at l
          [l..r], [l..r+1], ..., [l..n-1]

Both count exactly the right things
just from different perspectives
```

---

### Common Mistakes

```
Mistake 1: updating answer inside while loop
  wrong  → misses some windows
  right  → update AFTER while loop (longest)
           OR inside while loop (shortest/count)

Mistake 2: wrong window size formula
  size = r - l + 1   ← both endpoints inclusive ✅
  size = r - l       ← off by one ❌

Mistake 3: not restoring state when shrinking
  always undo the effect of removing s[l]
  freq[s[l]]--  before l++

Mistake 4: using wrong condition
  "at least 1" → shrink when valid (count extensions)
  "at most k"  → shrink when violated (count current window)
  easy to swap these ❌
```



# Sliding Window vs. Two Pointers (The Physical Difference)

One of the most common points of confusion is distinguishing these two patterns because they both use two variables (usually `i` and `j` or `left` and `right`). The easiest way to tell them apart is by their **Physical Motion**.

---

### 1. Sliding Window: The "Caterpillar" 🐛

In a Sliding Window, the two pointers move in the **same direction**. They maintain a "window" of data between them.

* **The Motion:** The `right` pointer expands the window to find a solution, and the `left` pointer shrinks the window to keep it valid (or to find the minimum size).
* **The Goal:** To find a **subarray** (contiguous block) that meets a condition.
* **Key Problems:**
    * Maximum sum subarray of size $K$.
    * Smallest subarray with a sum $\ge X$.
    * Longest substring without repeating characters.
* **Visual:** `[ L ------> R ] ------>`
    * *The whole window "slides" or "crawls" across the array from left to right.*

---

### 2. Two Pointers: The "Pincer Maneuver" ⚔️

In the classic Two-Pointer pattern, the pointers move **toward each other** from opposite ends.

* **The Motion:** `left` starts at index `0`, `right` starts at index `n-1`. They move inward based on a comparison.
* **The Goal:** To find a **pair** or a **triplet** in a **sorted** array.
* **Key Problems:**
    * Two Sum II (Sorted array).
    * Reverse an array / Palindrome check.
    * Container With Most Water.
    * 3Sum.
* **Visual:** `L ------>      <------ R`
    * *The pointers "pinch" the data until they meet in the middle.*

---

### 3. Comparison Table

| Feature | Sliding Window | Two Pointers (Pincer) |
| :--- | :--- | :--- |
| **Direction** | Same direction (Left to Right). | Opposite directions (Inward). |
| **Data Structure** | Usually any array/string. | Usually **Sorted** arrays. |
| **Mental Model** | A "Moving Frame" or "Curtain." | A "Search Space Reduction." |
| **Focus** | Continuous **Subarrays**. | Specific **Pairs/Elements**. |

---

### 4. Summary for your Notes

* **Sliding Window (The Caterpillar):** Use this when the question asks for the "longest," "shortest," or "sum of" a **contiguous** block.
* **Two Pointers (The Pincer):** Use this when the array is **sorted** and you need to find elements that sum up to a target or satisfy a boundary condition.

# When to use which Pattern?

### Use Sliding Window when:
1. The problem mentions **contiguous** elements (a subarray or substring).
2. You need to find a **range** that satisfies a certain property (sum, distinct count).
3. The array is **unsorted**, but the relative order matters.

### Use Two Pointers (Pincer) when:
1. The array is **sorted** (or you can sort it).
2. You are looking for **distinct elements** (a pair, triplet) that meet a target.
3. You need to compare elements from the **ends** toward the middle.
4. You are dealing with **Symmetry** (Palindromes).

### The "Golden Rule"
- **Contiguous Block?** -> Sliding Window.
- **Sorted Pair?** -> Two Pointers.

# The Missing Piece: Why Nobody Told You This

### 1. The "Hidden" Logic of Sliding Window
- It is actually a **Search for a Range**.
- You use it when the elements **must be neighbors**. 
- If you break the neighbor rule, the "window" shatters.

### 2. The "Hidden" Logic of Two Pointers
- It is actually an **Optimization of Brute Force**.
- Instead of checking every pair ($O(N^2)$), you use the **Sorted property** to realize that if `Left + Right` is too big, then `Right` is too big for **every** other number on the left.
- You are "killing" thousands of possibilities with a single move.

### 3. How to decide in 5 seconds:
- **"Give me a window/block"** -> Sliding Window.
- **"Find me a couple/pair"** -> Two Pointers.

![alt text](<012 ptr sliding window_250711_223007_3.jpg>)
 ![alt text](<012 ptr sliding window_250711_223007_4.jpg>) 
 ![alt text](<012 ptr sliding window_250711_223007_5.jpg>)
  ![alt text](<012 ptr sliding window_250711_223007_6.jpg>) 
  ![alt text](<012 ptr sliding window_250711_223007_7.jpg>)



## Complete Explanation of All 5 Images

---

## Image 1 — Variable Window Algorithm

### The Problem
```
Find longest subarray with sum <= k
```

### Why We Need Left and Right Pointers
```
We need TWO pointers (left and right)
otherwise we cannot:
  expand the window (right moves)
  shrink the window (left moves)
  remove previous results
```

### The Code Explained

```java
int largestSubarraySum(int[] arr, int k) {
    int n = arr.length;
    int l = 0;
    int sum = 0;
    int mxLength = 0;

    for (int r = 0; r < n; r++) {
        sum += arr[r];              // EXPAND — add right element

        while (sum > k) {           // condition VIOLATED
            sum -= arr[l];          // SHRINK — remove left element
            l++;                    // move left pointer right
        }

        if (sum <= k) {             // condition SATISFIED
            mxLength = max(mxLength, r - l + 1);
        }
    }
    return mxLength;
}
```

### The Expansion and Contraction Model

```
Expand  → keep adding arr[r] until condition met
Contract → remove arr[l] until condition is true again

This is the CORE of variable sliding window:

  r moves right ALWAYS   (expand)
  l moves right ONLY when condition violated (contract)

Example:
arr = [1, 2, 3, 4, 5], k=7

r=0: sum=1  <=7 ✅  window=[0,0] len=1
r=1: sum=3  <=7 ✅  window=[0,1] len=2
r=2: sum=6  <=7 ✅  window=[0,2] len=3
r=3: sum=10 >7  ❌  shrink:
     remove arr[0]=1 → sum=9 >7 l=1
     remove arr[1]=2 → sum=7 <=7 l=2 ✅
     window=[2,3] len=2
r=4: sum=12 >7  ❌  shrink:
     remove arr[2]=3 → sum=9 >7 l=3
     remove arr[3]=4 → sum=5 <=7 l=4 ✅
     window=[4,4] len=1

mxLength = 3 ✅
```

---

## Image 2 — Generic Variable Size Algorithm Template

### The Template

```java
int varSizeAlgo(int[] arr) {
    int some_property = 0;    // tracks window state
    int n = arr.length;
    int res = 0;
    int l = 0;

    for (int r = 0; r < n; r++) {
        // STEP 1: Add arr[r] to res (expand)
        Add arr[r] to res;

        // STEP 2: Shrink while property not satisfied
        while (some_property not satisfying condition) {
            Remove arr[l] from res;   // undo left element
            l++;                      // shrink window
        }

        // STEP 3: Compute result after valid window found
        res = some computation on (r, l);
    }

    return res;
}
```

### Complexity
```
Time:  O(n)  — each element added once, removed once
Space: O(1)  — only pointers and sum
```

### Why Brute Force is O(n²)

```
Brute force for substring/subarray:
  generate ALL subarrays → check condition

for (int i = 0; i < n; i++)
    for (int j = i+1; j < n; j++)
        checkCondition(arr, i, j)

Two nested loops = O(n²)

Sliding window = O(n) by avoiding re-processing
```

---

## Image 3 — Optimal Trick (while → if)

### Brute Force O(n²)

```
for (int i = 0; i < n; i++)
    for (int j = i+1; j < n; j++)
        checkCondition(arr, i, j)
```

### Variable Length Sliding Window O(2n)

```
Two pointers = two passes at most
  r does n steps    (expansion)
  l does n steps    (contraction)
total = n + n = 2n = O(n)
```

### The KEY Optimization — while → if

This is the most important insight in image 3:

```
Standard approach uses WHILE loop:

while (sum > k) {
    sum -= arr[l];
    l++;
}

This shrinks until condition is satisfied
Window can shrink MULTIPLE times per step
```

```
Optimal approach uses IF:

if (sum > k) {
    sum -= arr[l];
    l++;
}

Only shrinks by ONE step per r increment
```

**Why is IF valid here?**

```
We want MAXIMUM length subarray
Once we find a valid window of length 3:
  we should NEVER shrink below length 3
  because we're looking for LONGER windows

So when sum > k:
  shrink by exactly 1 (not more)
  this maintains the current max length
  and looks for longer windows

"We set length 3, now we need max length
 so we should NOT shrink to length 2"

"Optimal is not to go beyond max length"

"Instead of contracting by a while loop
 we check by if() so that we check for
 length > max length ONLY"
```

### Concrete Example

```
arr=[2,1,5,1,3,2], k=7
Finding LONGEST subarray with sum <= k

WITH WHILE (finds correct answer but shrinks unnecessarily):
r=0: sum=2 window=[0,0] len=1
r=1: sum=3 window=[0,1] len=2
r=2: sum=8>7 → while: remove 2→sum=6 l=1
     window=[1,2] len=2 mxLen=2
r=3: sum=7 window=[1,3] len=3 mxLen=3
r=4: sum=10>7 → while: remove 1→sum=9>7 l=2
               remove 5→sum=4 l=3
     window=[3,4] len=2  ← shrunk too much!
r=5: sum=6 window=[3,5] len=3 mxLen=3

WITH IF (optimal — never shrinks below max):
r=0: sum=2 window=[0,0] len=1
r=1: sum=3 window=[0,1] len=2
r=2: sum=8>7 → if: remove 2→sum=6 l=1
     window=[1,2] len=2 mxLen=2
r=3: sum=7 window=[1,3] len=3 mxLen=3
r=4: sum=10>7 → if: remove 1→sum=9 l=2
     window=[2,4] len=3 mxLen=3  ← didn't shrink below 3!
r=5: sum=11>7 → if: remove 5→sum=6 l=3
     window=[3,5] len=3 mxLen=3

Same answer, IF version never explores smaller windows
→ strictly more efficient
```

---

## Image 4 — The if vs while Decision

### The Code with IF

```java
int largestSubarraySum(int[] arr, int k) {
    int n = arr.length;
    int l = 0;
    int sum = 0;
    int mxLength = 0;

    for (int r = 0; r < n; r++) {
        sum += arr[r];

        if (sum > k) {              // ← IF not WHILE
            sum -= arr[l];
            l++;
        }

        if (sum <= k) {
            mxLength = max(mxLength, r - l + 1);
        }
    }
    return mxLength;
}
```

### Time Complexity

```
O(n) — r moves from 0 to n-1 once
       l moves at most n times total
       = O(2n) = O(n)
```

### When to Use WHILE vs IF

```
USE WHILE when:
  you need the ACTUAL subarray or its content
  not just the length
  you need to process every valid window fully
  problem asks for minimum window

  while (condition violated) {
      shrink
  }
  → window is always valid after while loop

USE IF when:
  you only need MAXIMUM LENGTH
  you never want to shrink below current max
  saves time by skipping unnecessary shrinking

  if (condition violated) {
      shrink by 1
  }
  → window stays at max length or grows

"We can do this while change to if, if
 we need subarray not the length of
 largest subarray. You need to think can
 we use if or not"
```

---

## Image 5 — Counting Subarrays (exactly = atMost trick)

### The Problem

```
Count number of subarrays with sum = K
```

### Why Direct Sliding Window Fails for Exactly K

```
Sliding window easily handles:
  sum <= k   (shrink when violated)
  sum >= k   (shrink when satisfied)

But for EXACTLY k:
  if sum > k → shrink
  if sum < k → can't shrink (makes it worse)
  if sum = k → count it, but then what?
  → can't directly apply sliding window
```

### The Trick — atMost Decomposition

```
number of subarrays with sum EXACTLY k
=
number of subarrays with sum <= k    (call this x)
MINUS
number of subarrays with sum <= k-1  (call this y)

answer = x - y
```

**Why does this work?**

```
subarrays with sum <= k   includes:
  sum = 0, 1, 2, ... k-1, k

subarrays with sum <= k-1 includes:
  sum = 0, 1, 2, ... k-1

difference = subarrays with sum exactly k ✅
```

### The Code

```cpp
int atMost(vector<int>& arr, int k) {
    if (k < 0) return 0;      // guard for negative k
    int l = 0, sum = 0, count = 0;

    for (int r = 0; r < arr.size(); r++) {
        sum += arr[r];

        while (sum > k) {
            sum -= arr[l];
            l++;
        }
        count += r - l + 1;   // all windows ending at r
    }
    return count;
}

int exactlyK(vector<int>& arr, int k) {
    return atMost(arr, k) - atMost(arr, k-1);
}
```

### Concrete Example

```
arr = [1, 2, 3], k = 3

atMost(arr, 3):
  r=0: sum=1<=3, count += 1 = 1   subarrays: [1]
  r=1: sum=3<=3, count += 2 = 3   subarrays: [2],[1,2]
  r=2: sum=6>3 → shrink:
       remove 1→sum=5>3 l=1
       remove 2→sum=3<=3 l=2
       count += 1 = 4              subarrays: [3]
  total x = 4

atMost(arr, 2):
  r=0: sum=1<=2, count += 1 = 1   subarrays: [1]
  r=1: sum=3>2 → remove 1→sum=2 l=1
       count += 1 = 2              subarrays: [2]
  r=2: sum=5>2 → remove 2→sum=3>2 l=2
       remove 3→sum=0? wait sum=3-2=... let me redo
       sum=2+3=5>2 → remove arr[1]=2→sum=3>2 l=2
       → remove arr[2]=3→sum=0 l=3
       count += 0 = 2
  total y = 2

answer = x - y = 4 - 2 = 2

Subarrays with sum exactly 3:
  [1,2] = 3 ✅
  [3]   = 3 ✅
  count = 2 ✅
```

---

## Summary of All 5 Images

| Image | Topic | Key Takeaway |
|---|---|---|
| 1 | Variable window basics | Expand right always, shrink left when violated |
| 2 | Generic template | while(not satisfied) shrink, then compute |
| 3 | while vs if concept | Use if for max length — never shrink below max |
| 4 | if version code | O(n) optimal, think whether if or while needed |
| 5 | Counting exactly k | atMost(k) - atMost(k-1) = exactly k |

```
The progression across 5 images:

Image 1,2 → learn the expansion/contraction model
Image 3,4 → optimise it (while → if for max length)
Image 5   → extend it (counting with atMost trick)

These 5 images together cover
90% of all sliding window interview problems
```



## While vs If — Complete Explanation

### The Setup

```
arr = [1, 2, 1, 3, 2], k = 4
Find LONGEST subarray with sum <= 4
```

---

## WITH WHILE LOOP

```cpp
for (int r = 0; r < n; r++) {
    sum += arr[r];

    while (sum > k) {    // shrink as much as needed
        sum -= arr[l];
        l++;
    }
    mxLen = max(mxLen, r - l + 1);
}
```

### Full Trace

```
arr = [1, 2, 1, 3, 2]
       0  1  2  3  4     k=4, n=5

l=0, sum=0, mxLen=0
```

```
r=0: sum = 0+1 = 1
     while 1>4? NO
     window = [0,0] = "1"     len=1  mxLen=1

r=1: sum = 1+2 = 3
     while 3>4? NO
     window = [0,1] = "1,2"   len=2  mxLen=2

r=2: sum = 3+1 = 4
     while 4>4? NO
     window = [0,2] = "1,2,1" len=3  mxLen=3

r=3: sum = 4+3 = 7
     while 7>4? YES
       remove arr[0]=1 → sum=6  l=1
     while 6>4? YES
       remove arr[1]=2 → sum=4  l=2
     while 4>4? NO  → exit while
     window = [2,3] = "1,3"    len=2  mxLen=3

     ↑ window SHRUNK from size 3 to size 2
       we already know mxLen=3
       shrinking to 2 gives us NO new information
       this work was WASTED ❌

r=4: sum = 4+2 = 6
     while 6>4? YES
       remove arr[2]=1 → sum=5  l=3
     while 5>4? YES
       remove arr[3]=3 → sum=2  l=4
     while 2>4? NO → exit while
     window = [4,4] = "2"      len=1  mxLen=3

     ↑ window shrunk to size 1
       again wasted work ❌

Final mxLen = 3 ✅
```

### What While Loop Does

```
arr =  1   2   1   3   2
       ↑           ↑
       l=0         r=3  sum=7 > 4

while loop shrinks:
  step 1: remove 1 → l=1  sum=6  still >4
  step 2: remove 2 → l=2  sum=4  ok stop

window went from size 4 → size 2
           ┌─────────┐
  1   2  [1   3]  2
          l=2  r=3
          size = 2

We ALREADY had size 3 before
Going to size 2 is going BACKWARDS
This is wasted computation ❌
```

---

## WITH IF

```cpp
for (int r = 0; r < n; r++) {
    sum += arr[r];

    if (sum > k) {      // shrink by EXACTLY ONE
        sum -= arr[l];
        l++;
    }
    mxLen = max(mxLen, r - l + 1);
}
```

### Full Trace

```
arr = [1, 2, 1, 3, 2]
       0  1  2  3  4     k=4, n=5

l=0, sum=0, mxLen=0
```

```
r=0: sum = 0+1 = 1
     if 1>4? NO
     window = [0,0] len=1  mxLen=1

r=1: sum = 1+2 = 3
     if 3>4? NO
     window = [0,1] len=2  mxLen=2

r=2: sum = 3+1 = 4
     if 4>4? NO
     window = [0,2] len=3  mxLen=3

r=3: sum = 4+3 = 7
     if 7>4? YES
       remove arr[0]=1 → sum=6  l=1
       ← only ONE removal, stop
     window = [1,3] = "2,1,3"  len=3  mxLen=3

     ↑ window stayed at size 3!
       sum=6 > 4 but we don't care
       we only need to find LONGER windows
       size 3 is not longer than mxLen=3
       so no point shrinking further ✅

r=4: sum = 6+2 = 8
     if 8>4? YES
       remove arr[1]=2 → sum=6  l=2
       ← only ONE removal, stop
     window = [2,4] = "1,3,2"  len=3  mxLen=3

     ↑ window still size 3
       sum=6 > 4 still invalid
       but window length = mxLen
       we need LONGER to improve answer
       so no benefit in shrinking more ✅

Final mxLen = 3 ✅
```

---

## Side by Side Comparison

```
arr = [1, 2, 1, 3, 2],  k=4

WHILE loop windows:          IF loop windows:
─────────────────────        ─────────────────
r=0: [0,0] size=1            r=0: [0,0] size=1
r=1: [0,1] size=2            r=1: [0,1] size=2
r=2: [0,2] size=3 ← max      r=2: [0,2] size=3 ← max
r=3: [2,3] size=2 ← SHRUNK   r=3: [1,3] size=3 ← STAYS
r=4: [4,4] size=1 ← SHRUNK   r=4: [2,4] size=3 ← STAYS
```

```
WHILE: window size goes 1→2→3→2→1
                              ↑ ↑
                        wasted shrinking

IF:    window size goes 1→2→3→3→3
                              ↑ ↑
                        never goes back
```

---

## The Key Insight Visualised

```
WHILE mindset:
  "keep window VALID at all times"
  "sum must always be <= k"

  consequence:
  window shrinks below current max
  explores smaller windows unnecessarily

IF mindset:
  "only grow the window"
  "shrink by 1 to maintain current size"
  "never explore windows smaller than current max"

  consequence:
  window size is monotonically non-decreasing
  never goes backwards
  every step either grows or stays same
```

---

## What IF Actually Does

```
IF guarantees:
  window size at step r  >=  window size at step r-1

Why?
  r moves right → window expands by 1
  if invalid → l moves right → window stays same size
  if valid   → l stays       → window grows by 1

So window size can only:
  INCREASE by 1  (valid, l stays)
  STAY SAME      (invalid, l moves once)
  NEVER DECREASE ✅
```

---

## Operations Count

```
arr = [1,2,1,3,2], k=4

WHILE loop:
  r=0: 0 shrinks
  r=1: 0 shrinks
  r=2: 0 shrinks
  r=3: 2 shrinks  ← extra work
  r=4: 2 shrinks  ← extra work
  Total shrink ops = 4

IF loop:
  r=0: 0 shrinks
  r=1: 0 shrinks
  r=2: 0 shrinks
  r=3: 1 shrink
  r=4: 1 shrink
  Total shrink ops = 2

IF does HALF the work here ✅
For larger inputs difference grows even more
```

---

## When Each Should Be Used

```
USE WHILE when:
  need actual valid window at each step
  minimum window problem
  need to process every valid state
  sum/count must be correct after each r

  Example: minimum window substring
           need smallest valid window
           must shrink as much as possible ✅

USE IF when:
  only need MAXIMUM LENGTH
  don't need window to be valid at every step
  just need to track if a longer window exists

  Example: longest subarray sum <= k
           once we find length 3
           never need to go back to length 2 ✅
```

---

## One Line Summary

```
WHILE  →  "keep window always valid"
           can shrink multiple times
           window size can decrease
           needed when validity matters at each step

IF     →  "never shrink below current max"
           shrinks at most once per step
           window size never decreases
           optimal when only max length needed
```


# Q Maximum Points You Can Obtain from Cards

There are several cards **arranged in a row**, and each card has an associated number of points. The points are given in the integer array `cardPoints`.

In one step, you can take one card from either the **beginning** or the **end** of the row. You must take exactly `k` cards.

Your score is the sum of the points of the cards you have taken.

Given the integer array `cardPoints` and the integer `k`, return the **maximum score** you can obtain.

---

### Examples

**Example 1:**
**Input:** `cardPoints = [1, 2, 3, 4, 5, 6, 1]`, `k = 3`  
**Output:** `12`  
**Explanation:** After the first step, your score will always be 1. However, choosing the rightmost card first will maximize your total score. The optimal strategy is to take the three cards on the right, giving a final score of `1 + 6 + 5 = 12`.

**Example 2:**
**Input:** `cardPoints = [2, 2, 2]`, `k = 2`  
**Output:** `4`  
**Explanation:** Regardless of which two cards you take, your score will always be 4.

**Example 3:**
**Input:** `cardPoints = [9, 7, 7, 9, 7, 7, 9]`, `k = 7`  
**Output:** `55`  
**Explanation:** You must take all the cards. Your score is the sum of points of all cards.

---

### Constraints
- `1 <= cardPoints.length <= 10^5`
- `1 <= cardPoints[i] <= 10^4`
- `1 <= k <= cardPoints.length`


## Wrong code

```cpp
class Solution{
  public:
    int maxScore(vector<int>& arr , int k){
        int n=arr.size();
        if(k==n) return accumulate(arr.begin(),arr.end(),0);
        int i=0;
        int j=n-1;
        int sum=0;
        while(i<=j){
          if(k==0) return sum;
          int val=(arr[i]>arr[j])?arr[i]:arr[j];
          sum+=val;
          val==arr[i]?i++:j--;
          k--;
    }
      return sum;
    }
};
```

# The "Greedy Trap" in Two-Pointer Problems

This problem is the perfect example of why a simple **Greedy Pincer Maneuver** often fails. It feels logical to say: *"I want the biggest score, so at every step, I'll just pick the larger of the two ends."*

However, the "Physics" of the problem dictates that being greedy **now** might prevent you from getting a much larger number **later**.

---

### 1. The "Hidden Treasure" Problem
Consider the array `arr = [10, 1, 100, 1]` with `k = 2`.

**Your Greedy Logic:**
* **Step 1:** Compare `10` (left) and `1` (right). Pick **10**.
* **Step 2:** Compare `1` (left) and `1` (right). Pick **1**.
* **Total Score:** $10 + 1 = 11$.

**The Optimal Way:**
* If you had picked the `1` on the **right** first, you would have "unlocked" the **100**!
* **Step 1:** Pick `1` (right).
* **Step 2:** Pick `100` (new right).
* **Optimal Score:** $1 + 100 = 101$.

> **Conclusion:** A small number can act as a "shield" for a massive number behind it. Greedy logic is blind to what lies behind the immediate ends.

---

### 2. The Real Strategy: The "Accordion" (Sliding Window)
Instead of picking elements one by one, look at the problem through its **Inverse Physics**:

* If you must take exactly $k$ elements from the ends, you are essentially **leaving behind** a contiguous block of $n - k$ elements in the middle.
* To **maximize** the $k$ elements you take, you must **minimize** the sum of the window you leave behind.

### 3. Summary of the Logic

| Approach | Logic | Why it Fails/Works |
| :--- | :--- | :--- |
| **Greedy** | Pick the larger of `arr[left]` or `arr[right]`. | **Fails:** It can't see the "Hidden Treasure" behind small numbers. |
| **Sliding Window** | Find the minimum sum of a window of size $(n-k)$. | **Works:** It views the array globally and finds the best "cut." |
| **Prefix/Suffix** | Compare all $k+1$ possible combinations of Left/Right splits. | **Works:** It mathematically exhausts every valid way to pick $k$ cards. |

# How to Spot and Avoid the Greedy Trap

To avoid the **Greedy Trap**, you have to change how you look at the "Physics" of the problem. In competitive programming, greedy works only when a local choice doesn't negatively affect future possibilities. In this problem, your choice **unlocks** new values, which is a massive red flag for Greedy.

### 1. The "Hidden Boss" Test
Whenever you are tempted to pick the largest available number, ask yourself:
> *"Is it possible that picking a smaller number now unlocks a much larger number ('The Hidden Boss') later?"*

If the answer is **Yes**, Greedy is likely wrong. You need to look at the entire range of possibilities, not just the immediate ones.

---

### 2. Look for the "Complement" (The Inverse Physics)
This is the secret weapon of Senior Engineers. Instead of looking at what you **take**, look at what you **leave behind**.

* **Problem:** Maximize $k$ elements from the ends.
* **Inverse:** Minimize $n - k$ elements in the middle.

Because the $n - k$ elements must be **contiguous** (a solid block), the problem becomes a standard **Sliding Window** problem. Sliding Window is almost always more reliable than Greedy for "range" problems.

---

### 3. The "Prefix-Suffix" Mirror
If you must take elements from both ends, visualize your options as a fixed set of combinations. You can only take:
* $k$ from Left, $0$ from Right
* $k-1$ from Left, $1$ from Right
* ...
* $0$ from Left, $k$ from Right

There are only **$k + 1$** possible combinations. Since $k$ is at most $n$, you can simply check all $k + 1$ combinations in $O(k)$ time!

---

### 4. Summary for your Notes

| Strategy | Mental Model | Best Used When... |
| :--- | :--- | :--- |
| **The Hidden Boss Test** | Look for "bait" numbers. | You feel tempted to pick the maximum immediately. |
| **Inverse Physics** | Minimize the remainder. | You need to pick from ends (leaving a middle window). |
| **Prefix-Suffix Mirror** | Total split combinations. | $k$ is small and the choices are restricted to ends. |


## Correct code

```cpp
class Solution{
  public:
    int maxScore(vector<int>& cardPoints , int k){
      int n = cardPoints.size();
      int lSum = 0, rSum = 0, maxScore = 0;

        // Step 1: Initially, take all k cards from the LEFT
        for (int i = 0; i < k; i++) {
            lSum += cardPoints[i];
        }
        maxScore = lSum;

        // Step 2: One by one, "transfer" a card from the left to the right
        int rightIndex = n - 1;
        for (int i = k - 1; i >= 0; i--) {
            lSum -= cardPoints[i];       // Remove from left
            rSum += cardPoints[rightIndex]; // Add from right
            rightIndex--;

            maxScore = max(maxScore, lSum + rSum);
        }

        return maxScore;
    }
};
```
# Prefix-Suffix Swapping: The "Balance Scale" Logic

This approach avoids the greedy trap by treating the problem as a **Sliding Split**. Instead of trying to "choose" cards one by one like a greedy player, this algorithm acts like a balance scale that shifts weight from the left side of the array to the right side.

### 1. The Strategy: The "Sliding Split"
The core realization is that if you take $k$ cards, there are only **$k+1$ possible valid combinations**. This code systematically checks all of these combinations and remembers the best one:

* **$k$** from Left, **$0$** from Right
* **$k-1$** from Left, **$1$** from Right
* ...
* **$0$** from Left, **$k$** from Right

---

### 2. Step-by-Step "Physics"

#### **Phase 1: The Initial State (All Left)**
The code starts by assuming the best strategy might be to take the first $k$ cards from the beginning.
```cpp
for (int i = 0; i < k; i++) lSum += cardPoints[i];
```
### Visualizing the Shift ($k=3$)

The algorithm starts with all cards on the left and systematically "swaps" them for cards on the right. This ensures every possible combination is checked.

| Step | Left Hand | Right Hand | Total Cards |
| :--- | :--- | :--- | :--- |
| **Initial** | `[L1, L2, L3]` | `[ ]` | 3 |
| **Step 1** | `[L1, L2]` | `[R1]` | 3 |
| **Step 2** | `[L1]` | `[R1, R2]` | 3 |
| **Step 3** | `[ ]` | `[R1, R2, R3]` | 3 |

---

### **Phase 2: The "Transfer" (Shifting Weight)**

Now, the algorithm begins moving cards. It removes the **rightmost** card from your "left-side hand" and replaces it with a card from the **far-right** of the original array.

```cpp
lSum -= cardPoints[i];           // Drop the "last" left card
rSum += cardPoints[rightIndex];  // Pick up the "newest" right card
```

### Conclusion
In every step, the algorithm calculates the new lSum + rSum and updates the maxScore. Because it evaluates every possible "split" point between the prefix and the suffix, it is impossible for a "hidden" high-value card to be missed. Unlike the greedy approach, which only looks at the immediate next step, this "Balance Scale" method looks at the total possible sum for every valid configuration.

### Complexity Analysis
Time Complexity

O(k) The first loop iterates k times to calculate the initial sum of the leftmost k cards. The second loop also iterates k times, performing constant time operations (subtraction, addition, comparison, decrement) within each iteration. Therefore, the total time complexity is dominated by these two loops, resulting in O(k).

Space Complexity

O(1) The algorithm uses a few integer variables (n, lSum, rSum, maxScore, rightIndex, i) to store intermediate values and loop counters. The amount of memory used by these variables does not depend on the input size (n or k). Thus, the space complexity is constant, O(1).