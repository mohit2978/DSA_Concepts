# Notes

![alt text](<007 LIS_231121_163402.jpg>)
![alt text](<007 LIS_231121_163402(1).jpg>) ![alt text](<007 LIS_231121_163402(2).jpg>) ![alt text](<007 LIS_231121_163402(3).jpg>) ![alt text](<007 LIS_231121_163402(4).jpg>) ![alt text](<007 LIS_231121_163402(5).jpg>) ![alt text](<007 LIS_231121_163402(6).jpg>)

![alt text](<007 LIS_231121_163402(7).jpg>) ![alt text](<007 LIS_231121_163402(8).jpg>) ![alt text](<007 LIS_231121_163402(9).jpg>) ![alt text](<007 LIS_231121_163402(10).jpg>) ![alt text](<007 LIS_231121_163402(11).jpg>) ![alt text](<007 LIS_231121_163402(12).jpg>) ![alt text](<007 LIS_231121_163402(13).jpg>) ![alt text](<007 LIS_231121_163402(14).jpg>) ![alt text](<007 LIS_231121_163402(15).jpg>)


# C++ Binary Search Functions: `lower_bound` and `upper_bound`

Both functions are found in the `<algorithm>` header. They use binary search to find specific positions in a **sorted** range.

---

##  Core Logic Comparison

| Function | Condition | Description |
| :--- | :--- | :--- |
| **`std::lower_bound`** | `*it >= value` | Returns an iterator to the **first** element that is **not less** than the given value. |
| **`std::upper_bound`** | `*it > value` | Returns an iterator to the **first** element that is **strictly greater** than the given value. |


By mistake in upper notes we said upper bound is gretaer than or equal to but it is not ,it is lower bound

----

# Understanding `std::size_t` (The Return Type of `.size()`)

### 1. What is it?
`std::size_t` is an **unsigned integer type**. It is defined by the C++ standard to be large enough to represent the size of the largest possible object your computer's architecture can create.

* **On a 64-bit system:** It is usually an `unsigned long long` (8 bytes).
* **On a 32-bit system:** It is usually an `unsigned int` (4 bytes).



---

### 2. Why is it Unsigned?
Because a string or a container cannot have a "negative" number of elements. Using an unsigned type allows the range of the number to be twice as large as a signed type of the same bit-width.

> **The Range:**
> If an `int` goes from -2,147,483,648 to 2,147,483,647...
> A `size_t` of the same size goes from **0 to 4,294,967,295**.

---

### 3. The "Danger Zone": Underflow
The biggest mistake beginners make is subtracting two `.size()` values. Because they are unsigned, if the result should be negative, it "wraps around" to the maximum possible value of the type.

**Example:**
```cpp
string s = "abc"; // size 3
if (s.size() - 5 > 0) { 
    // This will actually be TRUE!
    // 3 - 5 becomes a massive positive number (e.g., 18,446,744,073,709,551,614)
}
```

never do

```cpp
 if(abs((int)s1.size()-(int)s2.size())>1) return false;
 ```

 Now see question
# Problem: Longest String Chain

### 1. Description
You are given an array of strings `words`. A word `s1` is a **predecessor** of word `s2` if and only if you can insert exactly one character anywhere in `s1` to make it equal to `s2`.

* For example, `"abc"` is a predecessor of `"abac"`, while `"cba"` is not a predecessor of `"bcad"`.

A **word chain** is a sequence of words `[word_1, word_2, ..., word_k]` where each `word_i` is a predecessor of `word_{i+1}` for all `1 <= i < k`. 

**Goal:** Return the length of the **longest possible word chain** that can be formed using words from the given list.

---

### 2. Constraints
* $1 \le words.length \le 1000$
* $1 \le words[i].length \le 16$
* `words[i]` only consists of lowercase English letters.

---
Example 1

Input: words = ["a", "ab", "abc", "abcd", "abcde"]

Output: 5

Explanation: The longest chain is ["a", "ab", "abc", "abcd", "abcde"].

Each word in the chain is formed by adding exactly one character to the previous word.

---

Example 2

Input: words = ["dog", "dogs", "dots", "dot", "d", "do"]

Output: 4

Explanation: The longest chain is ["d", "do", "dot", "dots"].

Each word is formed by inserting one character into the previous word.
---

### 3. Example Walkthrough
**Input:** `words = ["a", "b", "ba", "bca", "bda", "bdca"]`

1.  **"a"** -> **"ba"** -> **"bca"** -> **"bdca"** (Length 4)
2.  **"a"** -> **"ba"** -> **"bda"** -> **"bdca"** (Length 4)
3.  **"b"** -> **"ba"** -> **"bca"** -> **"bdca"** (Length 4)

**Output:** `4`

## My first code

 ```cpp
class Solution {
    bool isWordiSuccesorWordj(string &s1,string &s2){
        if(abs((int)s1.size()-(int)s2.size())>1) return false;
        int diff=0;
        int i=0;int j=0;
        while(i<s1.size()){
            if(s1[i]==s2[j]){
                i++;
                j++;
            }else{
                diff++;
                i++;
            }
        }
        return diff==1;
    }
public:
    int longestStringChain(vector<string>& wor) {
        sort(wor.begin(),wor.end());
        int n=wor.size();
        int res=1;
        vector<int> dp(n,1);
        for(int i=1;i<n;i++){

            for(int j=i-1;j>=0;j--){
                if(isWordiSuccesorWordj(wor[i],wor[j])==true){
                    dp[i]=max(dp[i],dp[j]+1);
                }
            }

            res=max(dp[i],res);
        }

        return res;
    }
};

 ```

 Here isWordiSuccesorWordj

 This looks more like a "One Edit Distance" check.

The Bug: If s1 and s2 are the same length but have one different character (e.g., "pale" and "pate"), diff will be 1, but j will increment out of bounds.

What happens inside the while loop :

i=0, j=0: 'p' == 'p' (Match! i=1, j=1)

i=1, j=1: 'a' == 'a' (Match! i=2, j=2)

i=2, j=2: 'l' != 't' (Mismatch! diff=1, i=3)

i=3, j=2: 'e' != 't' (Mismatch! diff=2, i=4)

The loop ends, and it returns diff == 1.

it only increments j on a match. In "pale" vs "pate", once you hit a mismatch, j stops moving, but i keeps going, leading to multiple mismatches or out-of-bounds errors. 

The Logic Flaw: A "successor" is almost always defined as an insertion. This allows for replacement if you aren't careful with lengths.

 # Default Sort vs. Length Sort

### 1. Default Sort: `sort(wor.begin(), wor.end())`
- **Behavior:** Lexicographical order (Dictionary).
- **Comparison:** `s < t` compares characters.
- **Use Case:** Alphabetical listing or binary search readiness.

```cpp
vector<string> words = {"banana", "at", "apple", "dog"};
sort(words.begin(), words.end());
// Result: {"apple", "at", "banana", "dog"}
```

### 2. Custom Sort: `sort(wor.begin(), wor.end(), compare)`
- **Behavior:** Length-based order.
- **Comparison:** `s.size() < t.size()`.
- **Use Case:** Problems like **Word Ladders** or **Longest String Chain** where we must process shorter words before longer ones.

```cpp
bool static compare(string &s, string &t) {
    return s.size() < t.size();
}

vector<string> words = {"banana", "at", "apple", "dog"};
sort(words.begin(), words.end(), compare);
// Result: {"at", "dog", "apple", "banana"}
```

### 3. The `static` Keyword
In C++, `std::sort` requires a pointer to a function. A non-static member function has a hidden `this` pointer, which `std::sort` cannot handle. Declaring it `static` removes the `this` pointer requirement.

If your compare function is inside a class (like in LeetCode), it must be static.

Non-static: Belong to an instance of the class. std::sort doesn't know which object to use to call the function.

Static: Belong to the class itself. std::sort can call it directly like a regular global function.

### Accepted solution

```cpp
class Solution {
    bool static compare(string &s, string &t) {
        return s.size() < t.size();
    }
    bool isWordiSuccesorWordj(string &s1,string &s2){
        if(s1.size()!=s2.size()+1) return false;
        int i=0;int j=0;
        while(i<s1.size()){
            if(s1[i]==s2[j]){
                i++;
                j++;
            }else{
                i++;
            }
        }
        if(i == s1.size() && j == s2.size()) return true;
        return false; // Return false otherwise
    }
public:
    int longestStringChain(vector<string>& wor) {
        sort(wor.begin(),wor.end(),compare);
        int n=wor.size();
        int res=1;
        vector<int> dp(n,1);
        for(int i=1;i<n;i++){

            for(int j=i-1;j>=0;j--){
                if(isWordiSuccesorWordj(wor[i],wor[j])==true){
                    dp[i]=max(dp[i],dp[j]+1);
                }
            }

            res=max(dp[i],res);
        }

        return res;
    }
};

```