## Sliding window # Sliding Window: The Accordion Logic

The goal of a Sliding Window is to convert an **$O(N^2)$** "brute force" solution (checking all subarrays) into an **$O(N)$** "linear" solution.

### 1. The Two Main Types
* **Fixed Window**: The size (K) is constant (e.g., "Find the max sum of any subarray of size 3"). 
    * *Logic*: Just slide the window by adding the new element and removing the old one.
* **Dynamic Window**: The size changes based on a condition (e.g., "Find the longest subarray with sum $\le K$").
    * *Logic*: Expand `right` until the condition breaks, then shrink `left` until it's valid again.

### 2. Why is it $O(N)$?
Even though there is a `while` loop inside a `while` loop, each pointer (`left` and `right`) only moves from index `0` to `N` **exactly once**. 
- Total operations $\approx 2N$, which is **$O(N)$**.

### 3. The "State" of the Window
The window's "State" can be anything:
- A `sum` (for numbers).
- A `HashMap` or `Frequency Array` (for counting unique characters).
- A `count` of zeros (for "Max consecutive ones" problems).


### statoc sliding window
```cpp
long long slidingWindow(vector<int>& arr, int k) {
    long long currentSum = 0;
    long long maxSum = 0;

    // 1. "Build the Base" (Like pre-calculating base primes)
    for(int i = 0; i < k; i++) {
        currentSum += arr[i];
    }
    maxSum = currentSum;

    // 2. "The Slide" (Like moving the segment from [L, R] to the next block)
    for(int i = k; i < arr.size(); i++) {
        // Add the "Entering" element (Right side of window)
        // Subtract the "Exiting" element (Left side of window)
        currentSum += arr[i] - arr[i - k];
        
        // 3. Update the Result
        maxSum = max(maxSum, currentSum);
    }
    return maxSum;
}
```

### Dynamic sliding window

```cpp

int slidingWindow(vector<int>& nums, int k) {
    int left = 0, right = 0;
    int currentSum = 0;
    int maxLength = 0;

    while (right < nums.size()) {
        // 1. Expand the window
        currentSum += nums[right];

        // 2. Squeeze the window if it's invalid
        while (currentSum > k) {
            currentSum -= nums[left];
            left++;
        }

        // 3. Record the result (Window is now valid)
        maxLength = max(maxLength, right - left + 1);

        // 4. Move to the next element
        right++;
    }
    return maxLength;
}
```

![alt text](<012 ptr sliding window_250711_223007_1.jpg>) 
![alt text](<012 ptr sliding window_250711_223007_2.jpg>) 
![alt text](<012 ptr sliding window_250711_223007_3.jpg>)
 ![alt text](<012 ptr sliding window_250711_223007_4.jpg>) 
 ![alt text](<012 ptr sliding window_250711_223007_5.jpg>)
  ![alt text](<012 ptr sliding window_250711_223007_6.jpg>) 
  ![alt text](<012 ptr sliding window_250711_223007_7.jpg>) 
  ![alt text](<012 ptr sliding window_250711_223007_8.jpg>)

  # The "Off-By-One" Cheat Sheet: Fencepost Logic

This is the most common cause of errors in coding interviews. Think of it as the **"Fencepost Problem"**: if you have a 10-meter fence with a post every 1 meter, how many posts do you have? (Answer: 11).

Here is the "Physics" of the three primary boundary formulas:

---

### 1. `right - left + 1` (The "Count" Formula)
**When to use:** When you need the **total number of elements** inside the current window, including both the `left` and `right` indices.

* **Logic**: If `left = 2` and `right = 4`, your window contains indices `{2, 3, 4}`.
* **Calculation**: $4 - 2 = 2$ (this represents the *gaps* between the posts), so you add $+1$ to count the posts (elements) themselves.
* **Common in**: Sliding Window problems like "Find the length of the longest/shortest subarray."

### 2. `right - left` (The "Distance" or "Exclusive" Formula)
**When to use:** When you want the **distance** between two points, or when the `right` pointer is already pointing **one past** the end of your valid window.

* **Logic A (Distance)**: How many steps do I take to get from `left` to `right`?
* **Logic B (Half-Open Interval)**: In C++ STL (like `end() - begin()`), the `end` is exclusive. If `right` is the first *invalid* index, then `right - left` correctly counts the valid elements before it.
* **Common in**: Finding the width of a gap or using a "Lead Scout" pointer that has already moved to the next element.

### 3. `right - left - 1` (The "Between" Formula)
**When to use:** When you want to count only the elements **in between** two boundaries, excluding both the `left` and `right` posts.

* **Logic**: You have two boundaries (like two walls), and you want to know how much empty space is in the middle.
* **Calculation**: If `left = 2` and `right = 4`, the only element *between* them is index `{3}`. $4 - 2 - 1 = 1$.
* **Common in**: Palindrome problems (expanding from center) or finding the length of a gap between two obstacles.

---

### Summary Table

| Formula | What it counts | Visual Example (L=2, R=5) | Result |
| :--- | :--- | :--- | :--- |
| **`R - L + 1`** | **Inclusive**: Both L and R are counted. | `[2, 3, 4, 5]` | 4 |
| **`R - L`** | **Half-Open**: L is counted, R is not. | `[2, 3, 4] ... 5` | 3 |
| **`R - L - 1`** | **Exclusive**: Neither L nor R are counted. | `2 ... [3, 4] ... 5` | 2 |

> **Pro-Tip for Interviews**: If you get confused under pressure, use a tiny test case. If your window is from index 0 to 0, how many elements are there? `0 - 0 + 1 = 1`. (Correct). If you used `R - L`, you'd get 0. This check saves you from failing the test cases!

why middle space r-l-1 gives -1 when r =l=0 ,it should give 0 as no elements in between?

# The "Middle Space" Safety Rule

Formula: `R - L - 1`

- **Condition**: Only use this when `R > L`. 
- **The Logic**: If the indices are neighbors (e.g., 0 and 1), the result is `0`. 
- **The Logic**: If the indices have a gap (e.g., 0 and 2), the result is `1`.

**Interview Hack**: 
If you ever see a negative result using these formulas, it means your pointers have **crossed** or are **overlapping**, and the "window" or "gap" technically doesn't exist.

# The "Train Station" Analogy for Index Math

This analogy helps you visualize the physics of the three main boundary formulas without getting lost in the math. Imagine a train track with stations numbered **0, 1, 2, 3, 4, 5...**

---

### 1. `R - L + 1` (The staion Count)
**Scenario:** You are a ticket inspector. You want to know how many stations are in your zone from **Station 2** to **Station 5**.

* **The Action:** You stand at Station 2 and count every station as the train passes: "Station 2, Station 3, Station 4, Station 5."
* **The Result:** You counted **4** stations.
* **The Formula:** $5 - 2 + 1 = 4$
* **Key Idea:** **INCLUSIVE**. You count every "stop" where the train actually sits.
* **Common Use:** Finding the length of a subarray or substring.

### 2. `R - L` (The Fuel/Distance)
**Scenario:** You are the train driver. You want to know how much fuel you need to get from **Station 2** to **Station 5**.

* **The Action:** Fuel is burned for the **gaps** between stations, not for the stations themselves. You move from 2→3 (1 unit), 3→4 (1 unit), and 4→5 (1 unit).
* **The Result:** You traveled **3** units of distance.
* **The Formula:** $5 - 2 = 3$
* **Key Idea:** **DISPLACEMENT**. You are counting the "jumps" or "steps" between the points.
* **Common Use:** Finding the distance between elements or handling exclusive-end ranges.

### 3. `R - L - 1` (The "In-Between" Tunnel)
**Scenario:** There is a tunnel that starts **after** Station 2 and ends **before** Station 5. How many stations are **inside** the dark tunnel?

* **The Action:** Station 2 is outside in the sun. Station 5 is outside in the sun. Only the stations strictly in the middle are in the tunnel.
* **The Result:** Only Station 3 and Station 4 are in the tunnel. That's **2** stations.
* **The Formula:** $5 - 2 - 1 = 2$
* **Key Idea:** **EXCLUSIVE**. You remove both "end-posts" to see what is left in the center.
* **Common Use:** Finding the number of elements between two boundaries (e.g., expanding from a center in palindromes).

---

### Summary Table

| Formula | Role | Mental Hack | Result (2 to 5) |
| :--- | :--- | :--- | :--- |
| **`R - L + 1`** | **The Station** | Count every stop. | 4 |
| **`R - L`** | **The Driver** | Count the fuel/gaps. | 3 |
| **`R - L - 1`** | **The Tunnel** | Count only what's between. | 2 |

> **Emergency Mental Check**:
> Test on 0 and 1:
> * **Passenger**: "Station 0, Station 1" → **2** ($1-0+1$)
> * **Driver**: "One jump from 0 to 1" → **1** ($1-0$)
> * **Tunnel**: "Nothing between 0 and 1" → **0** ($1-0-1$)