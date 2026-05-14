# Reverse string

## Reverse every word in a string


Given an input string, containing upper-case and lower-case letters, digits, and spaces( ' ' ). A word is defined as a sequence of non-space characters. The words in s are separated by at least one space.



Return a string with the words in reverse order, concatenated by a single space.


Examples:
Input: s = "welcome to the jungle"



Output: "jungle the to welcome"



Explanation: The words in the input string are "welcome", "to", "the", and "jungle". Reversing the order of these words gives "jungle", "the", "to", and "welcome". The output string should have exactly one space between each word.

Input: s = " amazing coding skills "



Output: "skills coding amazing"



Explanation: The input string has leading and trailing spaces, as well as multiple spaces between the words "amazing", "coding", and "skills". After trimming the leading and trailing spaces and reducing the multiple spaces between words to a single space, the words are "amazing", "coding", and "skills". Reversing the order of these words gives "skills", "coding", and "amazing". The output string should not have any leading or trailing spaces and should have exactly one space between each word.

### Constraints:

* **String Length:** $1 \le \text{s.length} \le 10^4$
* **Character Set:** `s` contains English letters (upper-case and lower-case), digits, and spaces (`' '`).
* **Content Guarantee:** There is at least one word in `s`.

### Mycode

```cpp
class Solution {
public:
    string reverseWords(string s) {
       int n=s.size();
       int i=0;
       vector<string>strVec;
       while(i<n){
          while(i<n && s[i]==' ') i++;
          string str;
          while(i<n && s[i]!=' '){
              str.push_back(s[i++]);
          }
          if(str.size()>0) strVec.push_back(str);
          //if you do not put this then last vala empty space 
          //aaega as empty string and after reversal it will 
          //become first mai empty space for eg 2 if ke bina 
          //run krna
       }
      i=0;
      int j=strVec.size()-1;
      while(i<j){
        swap(strVec[i++],strVec[j--]);
      }
      string res;
      i=0;
      while(i<strVec.size()){
        res.append(strVec[i]);
        if(i!=strVec.size()-1) res.append(" ");
        i++;
      }
      return res;
    } 
};
```

## Very very imporatnt
see string methods 

| Method | Syntax | Description |
| :--- | :--- | :--- |
| **`append()`** | `str1.append(str2);` | Appends a whole string, a substring, a C-style string, or a specified number of characters to the end of `str1`. |
| **`+=` operator** | `str1 += str2;` | The simplest way to append a string, a single character, or a C-style string. |
| **`push_back()`** | `str1.push_back(ch);` | Appends a **single character** (`char`) to the end of the string. |
| **`+` operator** | `result = str1 + str2;` | Creates and returns a **new string** that is the concatenation of `str1` and `str2`. |

---
 #### here k is length 

| Scenario | C++ (`std::string::substr`) | Java (`String.substring`) | Example (Assuming s = "example" and i = 2) |
| :--- | :--- | :--- | :--- |
| **From the beginning (index 0) with a specific length ($k$)** | `s.substr(0, k)` | `s.substring(0, k)` | `s.substr(0, 3)` / `s.substring(0, 3)` returns "exa" |
| **From a starting index ($i$) to the end of the string** | `s.substr(i)` | `s.substring(i)` | `s.substr(2)` / `s.substring(2)` returns "ample" |
| **From a starting index ($i$) with a specific length ($k$)** | `s.substr(i, k)` | `s.substring(i, i + k)` | `s.substr(2, 3)` returns "amp" / `s.substring(2, 5)` returns "amp" |

---
### Now k is exclusive last index

🔢 Substring with Start and End IndicesThis table assumes:Start Index: $i$ (inclusive)

End Index: $k$ (exclusive - the index after the last character)
 
| Scenario                                 | C++ (std::string::substr) | Java (String.substring) | Example (Assuming s = "example", start index i=2, end index k=5) |
|------------------------------------------|----------------------------|---------------------------|-------------------------------------------------------------------|
| Extract substring from i to k (exclusive) | s.substr(i, k - i)         | s.substring(i, k)         | s.substr(2, 3) / s.substring(2, 5) returns "amp"                  |

### k is inclusive index

#### End Index ($k$) is InclusiveThis means the character at index $k$ IS included in the result. You must adjust your code for both languages to accommodate this.

| Scenario                     | C++ (std::string::substr) | Java (String.substring) | Length Calculation | Example (s = "example", i = 2, k = 5)      | Result  |
|-----------------------------|----------------------------|--------------------------|---------------------|---------------------------------------------|---------|
| From i to k (Inclusive)     | s.substr(i, k - i + 1)     | s.substring(i, k + 1)    | Length = k − i + 1  | s.substr(2, 4) / s.substring(2, 6)         | "ampl"  |

## cpp function

```cpp
size_t start_index = i;
size_t end_index = k; // Exclusive end index

// The length is the difference between the indices
size_t length = end_index - start_index;

std::string result = s.substr(start_index, length);
```
The variable k (or end_index) is the exclusive end index, meaning:

- The character at index k is not included in the resulting substring (result).

- The substring stops immediately before the character at index k.

This convention is crucial because it makes calculating the length simple: it's just `end_index - start_index`.

| Index ($n$) | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 10 |
| :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: |
| Char | P | r | o | g | r | a | m | m | i | n | g |

```cpp
#include <iostream>
#include <string>

int main() {
    std::string s = "Programming";

    // 1. Define the indices
    size_t start_index = 3;  // i (Inclusive start)
    size_t end_index = 7;    // k (Exclusive end: stops BEFORE index 7)

    // 2. Calculate the Length
    size_t length = end_index - start_index;

    // length = 7 - 3 = 4

    // 3. Extract the substring
    std::string result = s.substr(start_index, length);

    std::cout << "Original String: " << s << std::endl;
    std::cout << "Start Index (i): " << start_index << std::endl;
    std::cout << "End Index (k, exclusive): " << end_index << std::endl;
    std::cout << "Calculated Length: " << length << std::endl;
    std::cout << "Resulting Substring: " << result << std::endl;
    
    // Output: Resulting Substring: gram
    
    return 0;
}
```

#### Output

```text
Original String: Programming
Start Index (i): 3
End Index (k, exclusive): 7
Calculated Length: 4
Resulting Substring: gram
```
Now our question code becomes

```cpp
class Solution {
public:
    string reverseWords(string s) {
       int n=s.size();
       int i=0;
       vector<string>strVec;
       while(i<n){
          while(i<n && s[i]==' ') i++;
          int k=i;//string str;
          while(i<n && s[i]!=' '){
              i++;
          }
         if(i!=k) strVec.push_back(s.substr(k,i-k));
       }
      i=0;
      int j=strVec.size()-1;
      while(i<j){
        swap(strVec[i++],strVec[j--]);
      }
      string res;
      i=0;
      while(i<strVec.size()){
        res.append(strVec[i]);
        if(i!=strVec.size()-1) res.append(" ");
        i++;
      }
      return res;
    } 
};
```

### Complexity Analysis:
- Time Complexity: O(n) (where n is the length of the input string)

    The input string is scanned once to extract words, taking O(n) time, where n is the length of the input string.
Each word is stored in a list and then concatenated in reverse order, which also takes O(n).


- Space Complexity: O(n)
The words list stores each extracted word, requiring O(k) space, where k is the total number of characters in all words (essentially O(n)).
The result string requires O(n) space as well.

Let us see sc with O(1) solution

```cpp
class Solution {
    void reverseString(string &s, int start, int end) {
        while (start < end) {
            swap(s[start++], s[end--]);
        }
    }
public:
    string reverseWords(string s) {
       int n=s.size();
       reverseString(s, 0, n - 1);
       int i=0,j=0,st=0,ed=0;
       //vector<string>strVec;
       while(i<n){
          while(i<n && s[i]==' ') i++;
          if(i==n) break;
          st=j;//string str;
          while(i<n && s[i]!=' '){
              s[j++]=s[i++];
          }
          ed=j-1;
          reverseString(s, st,ed);
         //if(i!=k) strVec.push_back(s.substr(k,i-k));
          if (i < n) {
              s[j++] = ' ';
            }
       }
      if (j > 0 && s[j - 1] == ' ') j--;
      return s.substr(0,j);
    } 
};
```


# Sort Characters by Frequency

**Difficulty:** Easy

## Problem Statement

You are given a string `s`. Return the array of unique characters, sorted by highest to lowest occurring characters.

If two or more characters have the same frequency, then arrange them in alphabetic order.

## Examples

**Example 1**
> **Input:** `s = "tree"`
> **Output:** `['e', 'r', 't']`
> **Explanation:** > The occurrences of each character are as shown below:
> * `e` --> 2
> * `r` --> 1
> * `t` --> 1
> 
> The `r` and `t` have the same occurrences, so we arrange them by alphabetic order.

**Example 2**
> **Input:** `s = "raaaajj"`
> **Output:** `['a', 'j', 'r']`
> **Explanation:** > The occurrences of each character are as shown below:
> * `a` --> 4
> * `j` --> 2
> * `r` --> 1

**Example 3 (Quiz)**
> **Input:** `s = "bbccddaaa"`
> **Output:** `['a', 'b', 'c', 'd']`
> **Explanation:** > * `a` --> 3
> * `b` --> 2
> * `c` --> 2
> * `d` --> 2
> 
> `a` has the highest frequency. `b`, `c`, and `d` are tied, so they are arranged in alphabetic order.

## Constraints

* `1 <= s.length <= 10^5`
* `s` consists of only lowercase English characters.



```cpp
class Solution {
   public:
    vector<char> frequencySort(string& s) {
        vector<pair<char, int>> v(26, {' ', 0});
        for (char ch : s) {
            int val = ch - 'a';
            if (v[val].first ==' ') v[val].first = ch;
            v[val].second++;
        }

        sort(v.begin(), v.end(),
             [](const auto& a, const auto& b) { 
                return a.second!=b.second?a.second >b.second:a.first<b.first; 
                });
    
        vector<char> res;

        int i=0;

        while(i<v.size() && v[i].first!=' '){
            res.push_back(v[i].first);
            i++;
        }
        return res;
    
    }


};
```
## Time & Space Complexity Analysis

### Time Complexity — O(n)

Breaking down each part:

```cpp
// PART 1 — frequency counting
for (char ch : s) {        // O(n) — iterate every character once
    int val = ch - 'a';
    if (v[val].first == ' ') v[val].first = ch;
    v[val].second++;
}
```

```cpp
// PART 2 — sorting
sort(v.begin(), v.end(), ...);   // O(26 log 26) = O(1)
//   ↑ always exactly 26 elements regardless of input size
//   sorting a FIXED size array = constant time
```

```cpp
// PART 3 — collecting results
while (i < v.size() && v[i].first != ' ') {  // O(26) = O(1)
    res.push_back(v[i].first);                // at most 26 unique chars
    i++;
}
```

**Total:**
```
O(n) + O(26 log 26) + O(26)
= O(n) + O(1)      + O(1)
= O(n)
```

The entire complexity is dominated by the single pass through the string.

---

### Space Complexity — O(1)

```cpp
vector<pair<char, int>> v(26, {' ', 0});  // always exactly 26 pairs
                                          // fixed regardless of input
vector<char> res;                         // at most 26 chars
                                          // fixed regardless of input
```

**Total:**
```
O(26) + O(26) = O(1)

No matter if s has 10 chars or 100,000 chars
→ memory usage NEVER changes
→ truly constant space
```

---

### The Key Insight

```
Why O(1) space despite large input?

Constraint: only lowercase English letters
→ max 26 unique characters EVER
→ array size is bounded by alphabet, not input

Same reason sort is O(1):
→ you never sort more than 26 elements
→ input size has zero effect on sort time
```

---

### Summary Table

| Part | Time | Space | Why constant? |
|---|---|---|---|
| Frequency count | O(n) | O(1) | array fixed at 26 |
| Sort | O(1) | O(1) | always 26 elements |
| Collect result | O(1) | O(1) | at most 26 chars |
| **Total** | **O(n)** | **O(1)** | alphabet is finite |

> The trick that makes this O(1) space is using a **fixed-size array indexed by character** instead of a hashmap. A hashmap would be O(k) where k = unique chars — still bounded by 26 here, but the intent is less clear. The fixed array makes the O(1) guarantee explicit and obvious.

