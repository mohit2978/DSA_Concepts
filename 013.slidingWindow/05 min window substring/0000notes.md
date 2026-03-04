# Notes

![alt text](<002sliding window variable subarray ques_240514_125143.jpg>)

A junior developer solves this problem using a `Set` and a `while` loop, shrinking the left pointer `i` one step at a time until the duplicate is gone. It works, but it takes $O(2N)$ time in the worst case because the left pointer crawls.

Your code uses a HashMap to achieve true $O(N)$ time by turning the left pointer into a teleporter. Here is the "Senior Engineer" breakdown of the two massive tricks hidden in this short block of code.

### Trick 1: The "Next Index" Teleporter (`j + 1`)

Look at what you are storing in the map:

```java
map.put(s.charAt(j), j + 1);
```
Most people naturally try to store the exact index `j`. But you stored `j + 1`. Why?

Because when you encounter a duplicate character, you don't want your new window to start at the old duplicate. You want it to start immediately *after* the old duplicate. By storing `j + 1`, you pre-calculate the exact landing spot for your left pointer `i`. When a collision happens, `i` teleports directly to the correct starting line, completely skipping the `while` loop crawl.

### Trick 2: The Backwards-Prevention Trap (`Math.max`)

This is the single line that separates a FAANG offer from a rejection:

```java
i = Math.max(map.get(s.charAt(j)), i);
```

Why do we need `Math.max`? Why can't we just say `i = map.get(s.charAt(j))`?

Because the HashMap remembers everything, even characters that are no longer inside your current window. If you aren't careful, the map will trick your left pointer into jumping backwards!

### The "abba" Death Trap (Dry Run)

Let's trace the string `"abba"` without the `Math.max` protection.

* **`j = 0` ('a'):** Map gets `('a', 1)`. `i` is 0. **Window: `[a]`**
* **`j = 1` ('b'):** Map gets `('b', 2)`. `i` is 0. **Window: `[ab]`**
* **`j = 2` ('b'):** Collision! The map says the next 'b' starts at index 2. So `i` jumps to 2. Map updates `('b', 3)`. **Window: `[b]`** (Valid!)
* **`j = 3` ('a'):** Collision! The map remembers seeing an 'a' and says its next index is 1.

**Without `Math.max`:** `i` jumps backward from 2 to 1! Your window is now from index 1 to 3: `"bba"`. This is invalid (it has two 'b's), and your code fails.

**With `Math.max`:** The code says, *"Wait, the old 'a' is at index 1, but my left pointer is already at index 2. I'm not going backward!"* `i = Math.max(1, 2)` so `i` stays at 2. Your window safely becomes `"ba"`.

### The Verdict

By combining `j + 1` (the teleporter) and `Math.max` (the directional lock), you have built a Sliding Window that only ever moves forward, and does it in massive leaps instead of tiny steps.

Let us see rajneesh way!!

![alt text](<002sliding window variable subarray ques_240514_125143(1).jpg>) ![alt text](<002sliding window variable subarray ques_240514_125143(2).jpg>) 

![alt text](<002sliding window variable subarray ques_240514_125143(3).jpg>)

## Mycode

```cpp
/*
Given a string s and an integer k.Find the length of the longest substring with at most k distinct characters.


Examples:
Input : s = "aababbcaacc" , k = 2

Output : 6

Explanation : The longest substring with at most two distinct characters is "aababb".

The length of the string 6.

Input : s = "abcddefg" , k = 3

Output : 4

Explanation : The longest substring with at most three distinct characters is "bcdd".

The length of the string 4.

Input : s = "abccab" , k = 4

Output:
6
*/


#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int kDistinctChar(string& s, int k) {
        unordered_map<char,int>mp;
        int n=s.size();
        int res=0;
        int l=0;
        for(int r=0;r<n;r++){
            mp[s[r]]++;
            if(mp.size()>k){
                mp[s[l]]--;
                if(mp[s[l]]==0) mp.erase(s[l]);
                l++;
            }
           res=max(res,r-l+1);
        }
        return res;
    }
};
```

## Striver code

```java
import java.util.*;

class Solution {

    public int kDistinctChar(String s, int k) {
        

        int n = s.length();  
        int maxLen = 0;  

        HashMap<Character, Integer> mpp = new HashMap<>();
        
        int l = 0, r = 0;
        
        while(r < n){
            char charR = s.charAt(r);
            mpp.put(charR, mpp.getOrDefault(charR, 0) + 1);
            if(mpp.size() > k){
                char charL = s.charAt(l);
                mpp.put(charL, mpp.get(charL) - 1);
                if(mpp.get(charL) == 0){
                    mpp.remove(charL);
                }
                l++;
            }
            if(mpp.size() <= k){
                maxLen = Math.max(maxLen, r - l + 1);
            }
            
            r++;
        }
        
        // Return the maximum length
        return maxLen;
    }

    public static void main(String[] args) {
        String s = "aaabbccd";  
        int k = 2;
        
        // Create an instance of Solution class
        Solution sol = new Solution();
        
        int length = sol.kDistinctChar(s, k);
        
        // Print the result
        System.out.println("Maximum length of substring with at most " + k + " distinct characters: " + length);
    }
}

```

![alt text](<002sliding window variable subarray ques_240514_125143(4).jpg>) ![alt text](<002sliding window variable subarray ques_240514_125143(5).jpg>) ![alt text](<002sliding window variable subarray ques_240514_125143(6).jpg>) ![alt text](<002sliding window variable subarray ques_240514_125143(7).jpg>) ![alt text](<002sliding window variable subarray ques_240514_125143(8).jpg>) ![alt text](<002sliding window variable subarray ques_240514_125143(9).jpg>) ![alt text](<002sliding window variable subarray ques_240514_125143(10).jpg>) ![alt text](<002sliding window variable subarray ques_240514_125143(11).jpg>) ![alt text](<002sliding window variable subarray ques_240514_125143(12).jpg>) 

```java
class Solution {
   public String minWindow(String s, String t) {

        int ns = s.length(), nt = t.length();
        if (ns < nt)
            return "";
        int[] freq = new int[128];
        for (int i = 0; i < nt; i++)
            freq[t.charAt(i)]++;

        int si = 0, ei = 0, count = nt, len = (int) 1e9, gsi = 0;

        while (ei < ns) {
            if (freq[s.charAt(ei++)]-- > 0)
                count--;

            while (count == 0) {
                if (ei - si < len) {
                    len = ei - si;
                    gsi = si;
                }

                if (freq[s.charAt(si++)]++ == 0)
                    count++;
            }
        }

        return len == (int) 1e9 ? "" : s.substring(gsi, gsi + len);
    }
}
```


![alt text](<002sliding window variable subarray ques_240514_125143(13).jpg>)

## Sumeet sir solution

![alt text](<004variable size sliding window-map_240508_003646.jpg>)


 ![alt text](<004variable size sliding window-map_240508_003646(1).jpg>) ![alt text](<004variable size sliding window-map_240508_003646(2).jpg>) ![alt text](<004variable size sliding window-map_240508_003646(3).jpg>) ![alt text](<004variable size sliding window-map_240508_003646(4).jpg>) ![alt text](<004variable size sliding window-map_240508_003646(5).jpg>) ![alt text](<004variable size sliding window-map_240508_003646(6).jpg>) ![alt text](<004variable size sliding window-map_240508_003646(7).jpg>) 
 
 Sol1--> sumeet sir
Sol2--> Rajneesh
 
# Sliding Window Architecture: The Ultimate Clash

This is the ultimate clash of architectures. You have just put a **"Whiteboard Concept" (Solution 1)** head-to-head against a **"Production-Grade Engine" (Solution 2)**.

Both codes solve the exact same problem using the same Sliding Window logic. However, if you ran these against a string of 100,000 characters, **Solution 2 would finish in milliseconds**, while Solution 1 would choke the server and trigger a **Time Limit Exceeded (TLE)** error.

Here is the "Senior Engineer" breakdown of why Solution 2 destroys Solution 1 in a real-world environment.

---

### 1. The Allocation Trap (Two Maps vs. One Array)

* **Solution 1 (Concept):** You used two entire `HashMaps` (`tmp` for target, `smp` for window). To check validity, you constantly compare the two. Furthermore, Java `HashMaps` require objects (`Character`, `Integer`), forcing the CPU to constantly "autobox" primitives, adding massive hidden latency.
* **Solution 2 (Engine):** It uses exactly **one primitive array** of size 128. How does it track requirements without a second array? **Negative numbers.**
    * It starts with the required count: `freq['A'] = 2`.
    * As the window expands over an 'A', it subtracts: `freq['A']--`.
    * If `freq['A']` hits 0, the requirement is met.
    * If `freq['A']` goes to -1, it means the window has a **surplus**.
    * By allowing the array to go negative, it completely eliminates the need for a second map!

---

### 2. The Garbage Collector Nightmare (`.substring`)

This is the fatal flaw of Solution 1. Seeing them side-by-side makes it glaringly obvious.

* **Solution 1:** Inside the `while` loop, you call `String ans = s.substring(i+1, j+1)`. If your window shrinks 10,000 times, you construct 10,000 brand new `String` objects in the heap just to check their length. The Java Garbage Collector will halt your program to clean up this mess.
* **Solution 2:** Look at its inner loop:
    ```java
    if (ei - si < len) {
        len = ei - si;
        gsi = si;
    }
    ```
    It does **zero** object creation. It only updates two integers: `len` (shortest length) and `gsi` (starting index). It calls `.substring()` **exactly once** at the very last line of the program.

---

### 3. The `count` Tracker (Addition vs. Subtraction)

* **Solution 1:** You start `valid = 0` and increment it when `smp` matches `tmp`. This requires clunky comparisons at every step to avoid over-counting surplus characters.
* **Solution 2:** It starts `count = t.length()` (total characters needed). Every time it hits a required character (`freq > 0`), it decrements `count`. When `count == 0`, the window is valid. It is mathematically cleaner and avoids complex boundary checks.

---

### The Final Verdict

* **Solution 1** is a fantastic **prototype**. If you were explaining the concept of a sliding window to a junior developer, your code is easier to read because it maps English logic directly to data structures.
* **Solution 2** is what gets you **hired at a FAANG company**. It shows a deep understanding of bare-metal memory, primitive arrays, ASCII indexing, and garbage collection avoidance.

### Time and Space Complexity (TC & SC) Breakdown

Let $N$ be the length of string `s` and $M$ be the length of string `t`. Here is how the two architectures compare mathematically.

---

### Solution 1: HashMap & Substring Approach
This approach demonstrates the danger of hidden linear operations. What looks like an $O(N)$ algorithm is actually **$O(N^2)$** in the worst case.

* **Time Complexity (TC): $O(N^2 + M)$**
    * Building the target map takes $O(M)$.
    * The outer loop $j$ moves $N$ times. The inner `while` loop moves $i$ up to $N$ times total across the whole execution. 
    * **The Killer:** Inside the `while` loop, you call `s.substring(i+1, j+1)`. Creating a substring is an $O(K)$ operation (where $K$ is the length of the window). If the window shrinks $N$ times, you are performing an $O(N)$ operation inside a loop that runs $O(N)$ times, skyrocketing the complexity.
* **Space Complexity (SC): $O(N)$**
    * The HashMaps take $O(1)$ auxiliary space (max 256 unique ASCII characters).
    * However, every `s.substring()` call allocates a new `String` on the heap. Peak memory usage reaches $O(N)$ before the Garbage Collector can intervene.

---

### Solution 2: Optimized Array Approach
This is the mathematically perfect version of the sliding window. Every operation inside the loops is strictly $O(1)$.

* **Time Complexity (TC): $O(N + M)$**
    * Building the `freq` array takes $O(M)$.
    * The `ei` pointer and `si` pointer each move from $0$ to $N$. Every character is processed exactly twice (once entering, once leaving).
    * Because you only update integers and read from a primitive array, operations are pure $O(1)$. The only string creation happens **once** at the very end, costing $O(N)$. Total time: $O(N + M)$.
* **Space Complexity (SC): $O(1)$ Auxiliary Space**
    * The `int[] freq = new int[128]` takes constant space regardless of input size.
    * There are no HashMaps, no Objects, and no intermediate Strings. Aside from the final result, it uses practically zero extra memory.

---

### The Big Takeaway

A Sliding Window guarantees that your pointers move in $O(N)$ total steps. However, if you place an expensive operation—like **sorting**, **deep copying**, or **`.substring()`**—inside that loop, you destroy the $O(N)$ advantage and revert to quadratic time.

