# Notes

![alt text](<002sliding window variable subarray ques_240514_125143.jpg>)
![alt text](<002sliding window variable subarray ques_240514_125143(1).jpg>) ![alt text](<002sliding window variable subarray ques_240514_125143(2).jpg>) ![alt text](<002sliding window variable subarray ques_240514_125143(3).jpg>) ![alt text](<002sliding window variable subarray ques_240514_125143(4).jpg>) ![alt text](<002sliding window variable subarray ques_240514_125143(5).jpg>) ![alt text](<002sliding window variable subarray ques_240514_125143(6).jpg>) ![alt text](<002sliding window variable subarray ques_240514_125143(7).jpg>) ![alt text](<002sliding window variable subarray ques_240514_125143(8).jpg>) ![alt text](<002sliding window variable subarray ques_240514_125143(9).jpg>) ![alt text](<002sliding window variable subarray ques_240514_125143(10).jpg>) ![alt text](<002sliding window variable subarray ques_240514_125143(11).jpg>) ![alt text](<002sliding window variable subarray ques_240514_125143(12).jpg>) 

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

