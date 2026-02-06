# Q1 Rotate String



---

### **Problem Statement**
Given two strings `s` and `goal`, return `true` if and only if `s` can become `goal` after some number of **shifts** on `s`.

A **shift** on `s` consists of moving the leftmost character of `s` to the rightmost position.
- For example, if `s = "abcde"`, then it will be `"bcdea"` after one shift.

---

### **Example 1**
**Input:** `s = "abcde"`, `goal = "cdeab"`  
**Output:** `true`  
**Explanation:** - After 1st shift: `"bcdea"`  
- After 2nd shift: `"cdeab"`  
We can achieve the goal string after 2 shifts.

### **Example 2**
**Input:** `s = "abcde"`, `goal = "abced"`  
**Output:** `false`  
**Explanation:** No number of shifts on `"abcde"` can result in `"abced"`.

---

### **Constraints**
- `1 <= s.length, goal.length <= 100`
- `s` and `goal` consist of lowercase English letters.

---

### **Optimal Approach (String Concatenation)**
The most efficient way to solve this problem is to leverage a clever observation: if we concatenate a string with itself (`s + s`), the resulting string contains **all possible rotations** of the original string as substrings.

**Algorithm:**
1. First, check if the lengths of `s` and `goal` are equal. If they aren't, `s` can never be rotated into `goal`. Return `false`.
2. Create a new string `doubledS = s + s`.
3. Check if `goal` exists as a substring within `doubledS`.
4. If found, return `true`; otherwise, return `false`.

**Why it works:** For `s = "abcde"`, `s + s = "abcdeabcde"`.  
Substrings of length 5 are:  
- `"abcde"` (0 shifts)  
- `"bcdea"` (1 shift)  
- `"cdeab"` (2 shifts)  
- `"deabc"` (3 shifts)  
- `"eabcd"` (4 shifts)  

---
```cpp
class Solution {
public:
// Strings must be of the same length to be rotations of each other
    bool rotateString(string& s, string& goal) {
        if (s.length() != goal.length()) {
            return false;  
        }
        string doubledS = s + s;  // Concatenate s with itself
        return doubledS.find(goal) != string::npos;  // Check if goal is a substring of s + s
    }
};
```


### **Complexity Analysis**
- **Time Complexity:** $O(N)$, where $N$ is the length of the string. Concatenating strings takes $O(N)$ and the substring search (using efficient internal library functions like `contains` or `find`) typically runs in linear time.
- **Space Complexity:** $O(N)$, as we create a new string of length $2N$.



### How `string.find()` Works in C++

The `string.find()` function returns the starting index (position) of the first occurrence of the substring you are looking for. It returns a specific value based on two scenarios:

---

### 1. If the string IS found:
It returns the **index** (integer) where the substring begins. Indices in C++ strings start at **0**.





```cpp
string s = "banana";
int idx = s.find("nana"); 
// Returns 2 (because "nana" starts at index 2)
```
### 2. If the string is NOT found:
It returns a special constant called string::npos. While it is technically the largest possible value for size_t, it effectively acts as a "Not Found" flag.


```cpp
string s = "banana";
size_t idx = s.find("apple"); 
// Returns string::npos (Huge number, effectively "Not Found")
```



