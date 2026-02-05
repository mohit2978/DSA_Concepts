An **"Infinite Array"** in coding interviews doesn't mean the computer has infinite memory. It is a theoretical concept used to test if you can search without knowing the size ($N$).

### The Constraint
* You have an array (or data stream), but you are **not allowed** to use `.size()` or `.length`.
* You only have a function `get(index)` that returns the value at that index.
* If you go out of bounds, it might throw an error or return a sentinel value (like `INT_MAX`).

---

### The Problem
Standard Binary Search requires a `low` and a `high`.
* `low` is obviously 0.
* **But what is `high`?** You can't set `high = arr.size() - 1` because you don't know the size. 
* If you guess `high = 1,000,000`, it might be too small (if the target is at 2 million) or too big (if the array is size 5 and you crash).

---

### The Solution: "Exponential Search"
Since we can't start big and shrink down, we start small and **grow exponentially** until we bound the target.

#### Step 1: Find the Range (low and high)
We act like a **"Galloping Horse."** We start with a tiny window and keep doubling it until the target is trapped inside.
1.  Start with `low = 0`, `high = 1`.
2.  **Ask:** "Is my target smaller than `arr[high]`?"
3.  **If No (Target is bigger):** It means the target is further to the right. We need to expand our search.
    * **Action:** Double the range. `high = high * 2`.
4.  Repeat until `target <= arr[high]`.
5.  Once this condition is met, we know the target lies somewhere between the *previous* high and the *current* high.

#### Step 2: Standard Binary Search
Now that we have established a valid `low` and `high`, we just run standard Binary Search within that range.

---

### Complexity Analysis
* **Time Complexity:** $O(\log T)$, where $T$ is the index of the target. 
    * Finding the range takes $O(\log T)$ steps because we double the index each time.
    * The subsequent Binary Search also takes $O(\log T)$.
* **Space Complexity:** $O(1)$.

---

### Summary Rule
Don't guess a random large number for `high`. **Find it dynamically** by doubling. This ensures your search is always proportional to the position of the target, no matter how "infinite" the array is.


```cpp
/**
 * // This is the ArrayReader's API interface.
 * // You should not implement it, or speculate about its implementation
 * class ArrayReader {
 * public:
 * int get(int index);
 * };
 */

class Solution {
public:
    int search(const ArrayReader& reader, int target) {
        int low = 0;
        int high = 1;

        // Step 1: Find the Range (Exponential Expansion)
        // Keep doubling 'high' until we overshoot the target.
        // We also check if reader.get(high) is INT_MAX to stop expanding if we hit the "end".
        while (reader.get(high) < target) {
            low = high;      // Move low to the previous high (optimization)
            high = high * 2; // Double the range
        }

        // Step 2: Standard Binary Search within [low, high]
        while (low <= high) {
            int mid = low + (high - low) / 2;
            int val = reader.get(mid);

            if (val == target) return mid;
            
            if (val < target) {
                low = mid + 1;
            } else {
                high = mid - 1;
            }
        }
        
        return -1;
    }
};
```
### Why is this efficient?

You might think doubling `high` takes a long time, but because it grows exponentially, it is extremely fast. Consider how quickly the search space expands:

* **Iteration 1:** Range [0, 1]
* **Iteration 2:** Range [0, 2]
* **Iteration 10:** Range [0, 1,024]
* **Iteration 20:** Range [0, 1,048,576] (Over 1 Million)
* **Iteration 30:** Range [0, 1,073,741,824] (Over 1 Billion)

Even if the target is located at **index 1 Billion**, you only need approximately **30 doubling steps** to bound the range, and then another **30 binary search steps** to pinpoint the exact index.

---

### Complexity Analysis

* **Time Complexity: $O(\log T)$**
    * $T$ is the actual index of the target.
    * This is significantly faster than a linear scan, which would take $O(T)$ time.
    * The total time is basically $2 \times \log T$, which simplifies to $O(\log T)$.

* **Space Complexity: $O(1)$**
    * We only store a few integer variables (`low`, `high`, `mid`), regardless of how large the index $T$ is.

---

### Summary
Exponential Search (or "Galloping Search") is the gold standard for searching in unbounded or unknown data streams. It allows us to maintain the logarithmic efficiency of Binary Search even when the "Right" boundary is a mystery.

Would you like to see how we handle the `get(index)` function returning an "Out of Bounds" error during the doubling phase?

Would you like me to show you the C++ code for this "Galloping" logic (LeetCode 702)?