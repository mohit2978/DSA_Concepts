# Q1 Longest repaeating

![alt text](<02 longest reapeating_250711_225039.jpg>)

## Brute

```cpp
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int longestNonRepeatingSubstring(string &s) {
        int n = s.size(); 
        int maxLen = 0;    
        for (int i = 0; i < n; i++) {

            vector<int> hash(256, 0);  
            
            for (int j = i; j < n; j++) {

                if (hash[s[j]] == 1) break;  
                hash[s[j]] = 1;
                int len = j - i + 1;
                maxLen = max(maxLen, len);
            }
        }
        
        // Return the maximum length
        return maxLen; 
    }
};

int main() {
    string input = "cadbzabcd";
    
    //Create an instance of Solution class
    Solution sol;
    
    int length = sol.longestNonRepeatingSubstring(input);
    
    //Print the result
    cout << "Length of longest substring without repeating characters: " << length << endl;
    
    return 0;
}

```

### Wrong code

```cpp

#include <bits/stdc++.h>
using namespace std;

class Solution{
  public:
    int longestNonRepeatingSubstring(string& s){
        unordered_map<char,int>mp;
        int n=s.size();
        int res=0;
        int l=0;
        for(int r=0;r<n;r++){
           if(mp.find(s[r])==mp.end()) mp[s[r]]++;
           else {
            while(s[l]!=s[r]){
                mp[s[l]]--;
                l++;
            }
           }
           res=max(res,r-l+1);
        }
        return res;
    }
};
```

### Correct optimal

```cpp
#include <bits/stdc++.h>
using namespace std;

class Solution{
  public:
    int longestNonRepeatingSubstring(string& s){
        unordered_map<char,int>mp;
        int n=s.size();
        int res=0;
        int l=0;
        for(int r=0;r<n;r++){
            mp[s[r]]++;
            while(mp[s[r]]>1){
                mp[s[l]]--;
                l++;
            }
           res=max(res,r-l+1);
        }
        return res;
    }
};
```
# Q2 Maximum Points You Can Obtain from Cards

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