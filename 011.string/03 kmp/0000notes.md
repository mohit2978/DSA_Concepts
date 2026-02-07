![alt text](<Kmp algo_250701_234032_1.jpg>) 
![alt text](<Kmp algo_250701_234032_2.jpg>)
 ![alt text](<Kmp algo_250701_234032_3.jpg>)
  ![alt text](<Kmp algo_250701_234032_4.jpg>) 
  ![alt text](<Kmp algo_250701_234032_5.jpg>) 
  ![alt text](<Kmp algo_250701_234032_6.jpg>)
   ![alt text](<Kmp algo_250701_234032_7.jpg>)
    ![alt text](<Kmp algo_250701_234032_8.jpg>) 
    ![alt text](<Kmp algo_250701_234032_9.jpg>)
     ![alt text](<Kmp algo_250701_234032_10.jpg>)
      ![alt text](<Kmp algo_250701_234032_11.jpg>) 
      ![alt text](<Kmp algo_250701_234032_12.jpg>)


## AI code

It is easy to remember and same TC and SC!!
```cpp
class Solution {
    void computeLPS(vector<int>& lps, string s) {
        int len = 0;
        int i = 1;
        while (i < s.size()) {
            if (s[i] == s[len]) {
                len++;
                lps[i] = len;
                i++;
            } else {
                if (len != 0) {
                    len = lps[len - 1];
                } else {
                    lps[i] = 0;
                    i++;
                }
            }
        }
    }

   public:
    vector<int> search(string pat, string txt) {
        string s = pat + "$" + txt;
        int m = pat.size();
        int n = txt.size();
        vector<int> lps(s.size(), 0);
        computeLPS(lps, s);
        vector<int> ans;
        for (int i = m + 1; i < lps.size(); i++) {
            if (lps[i] == m) {
                ans.push_back(i - 2 * m);
            }
        }
        return ans;
    }
};
```
![alt text](Scanned_20260207-1607.jpg)

### The Logic of the Two Parts

Actually, there is a tiny but vital detail to correct there. In **0-based indexing**, the two parts are split slightly differently than `len + 1`:

* **The Prefix:** From index `0` up to `len - 1`.
* **The Suffix:** The part ending at your current index `i`.

---


If the length of our current match is **`len`**, the characters are distributed like this:

1.  **The Prefix (`0` to `len - 1`)**:
    If `len = 3`, the matched prefix characters are at indices `0, 1, 2`. 
    The **next** character we want to check in the prefix is at **Index 3**.
    Notice: **The next index we need IS the current length (`len`).**

2.  **The Suffix**:
    This is the part of the string ending at your current position `i`. We are checking if the character at `s[i]` can extend the prefix match we already have.

---

### The Magic of 0-Based Indexing

this is the most beautiful trick of 0-based indexing. Because indices start at 0, the variable representing the length of your current match serves a dual purpose:

* **If you have matched 0 characters:** The next character you need to check is at **Index 0**.
* **If you have matched 1 character ("A"):** The next character you need to check is at **Index 1**.
* **If you have matched 2 characters ("AB"):** The next character you need to check is at **Index 2**.

---

### The "Length is Index" Rule

In string algorithms like KMP or building a prefix table, `len` is effectively saying:
> **"I am the length of the prefix we have matched so far, AND I am the index of the very next character we need to look at."**

---

### Why this is powerful:
1.  **Cleaner Code:** You don't need to do `len + 1` or `len - 1` constantly, which reduces "Off-by-One" errors.
2.  **Automatic Pointer Alignment:** When a match is found, the length naturally points to the next slot in the array.
3.  **Logical Symmetry:** The relationship between the count of items and the position of the next item remains constant.


Algo:
1. if match then len++ ,lps[i]=len as len  poins to next location which needs to be matched!!
2. if no match 

    1. if len!=0 len=lps[len-1] 
    2. lps[i++]=0