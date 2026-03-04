# Sliding Window: The Accordion Logic

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