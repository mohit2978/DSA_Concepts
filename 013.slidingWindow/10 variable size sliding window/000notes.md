# Notes
 
 ![alt text](<004variable size sliding window-map_240508_003646(8).jpg>)
  ![alt text](<004variable size sliding window-map_240508_003646(9).jpg>) 
  ![alt text](<004variable size sliding window-map_240508_003646(10).jpg>) 
  ![alt text](<004variable size sliding window-map_240508_003646(11).jpg>) 
  ![alt text](<004variable size sliding window-map_240508_003646(12).jpg>) 
  ![alt text](<004variable size sliding window-map_240508_003646(13).jpg>) ![alt text](<004variable size sliding window-map_240508_003646(14).jpg>)
  
  
  
  
![alt text](<004variable size sliding window-map_240508_003646(15).jpg>)

# Q Longest repaeating

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

 
  
  ![alt text](<004variable size sliding window-map_240508_003646(22).jpg>) ![alt text](<004variable size sliding window-map_240508_003646(23).jpg>) ![alt text](<004variable size sliding window-map_240508_003646(24).jpg>) ![alt text](<004variable size sliding window-map_240508_003646(25).jpg>) ![alt text](<004variable size sliding window-map_240508_003646(26).jpg>) ![alt text](<004variable size sliding window-map_240508_003646(27).jpg>) ![alt text](<004variable size sliding window-map_240508_003646(28).jpg>) ![alt text](<004variable size sliding window-map_240508_003646(29).jpg>) ![alt text](<004variable size sliding window-map_240508_003646(30).jpg>) ![alt text](<004variable size sliding window-map_240508_003646(31).jpg>)








![alt text](<004variable size sliding window-map_240508_003646(32).jpg>) ![alt text](<004variable size sliding window-map_240508_003646(33).jpg>) ![alt text](<004variable size sliding window-map_240508_003646(34).jpg>) ![alt text](<004variable size sliding window-map_240508_003646(35).jpg>)


# Q Number of Substrings Containing All Three Characters

**Difficulty:** Hard

## Problem Statement

Given a string `s`, consisting only of characters `'a'`, `'b'`, `'c'`. Find the number of substrings that contain at least one occurrence of all these characters `'a'`, `'b'`, `'c'`.

---

## Examples

**Example 1**
> **Input:** `s = "abcba"`
> **Output:** `5`
> **Explanation:** The substrings containing at least one occurrence of the characters `'a'`, `'b'`, `'c'` are `"abc"`, `"abcb"`, `"abcba"`, `"bcba"`, `"cba"`.

**Example 2**
> **Input:** `s = "ccabcc"`
> **Output:** `8`
> **Explanation:** The substrings containing at least one occurrence of the characters `'a'`, `'b'`, `'c'` are `"ccab"`, `"ccabc"`, `"ccabcc"`, `"cab"`, `"cabc"`, `"cabcc"`, `"abc"`, `"abcc"`.

---

## Quiz: Now your turn!

**Input:** `s = "abccba"`

**Output:**
Pick your answer:
* [ ] 4
* [ ] 9
* [ ] 7
* [ ] 5

*(Senior Engineer Hint: Do not use an $O(N^2)$ nested loop to check every substring; that will trigger a Time Limit Exceeded error with $5 \times 10^4$ characters. Use an $O(N)$ sliding window tracking the "last seen" index of each character. As you iterate through the string, the number of valid substrings ending at your current index `i` is exactly `1 + min(lastSeen['a'], lastSeen['b'], lastSeen['c'])`. This mathematically calculates the combinations without physically building the substrings!)*

---

## Constraints

* `1 <= s.length <= 5 * 10^4`
* `s` consists only of characters `'a'`, `'b'`, `'c'`.

## Number of Substrings Containing All Three Characters

### Quiz Answer First

```
s = "abccba"

Valid substrings (must contain a,b,c all):
"abc"     [0,2] ✅
"abcc"    [0,3] ✅
"abccb"   [0,4] ✅
"abccba"  [0,5] ✅
"bccb"    [1,4] ❌ no 'a'
"bcca"  wait...
"ccb"     ❌ no 'a'
"bcc"     ❌ no 'a'
"bcb"  wait let me be systematic...

Starting at index 0: abc✅ abcc✅ abccb✅ abccba✅  = 4
Starting at index 1: bccba → bcc❌ bccb❌ bccba✅  = 1
Starting at index 2: ccba  → cc❌ ccb❌ ccba✅     = 1
Starting at index 3: cba   → c❌ cb❌ cba✅        = 1
Starting at index 4: ba    → none contain all 3   = 0
Starting at index 5: a     → none                 = 0

Total = 4+1+1+1 = 7
```

✅ **Answer: 7**

---

### Brute Force — O(n²)

```cpp
int numberOfSubstrings(string s) {
    int count = 0;
    int n = s.size();

    for (int i = 0; i < n; i++) {
        int freq[3] = {0, 0, 0};   // a, b, c counts

        for (int j = i; j < n; j++) {
            freq[s[j] - 'a']++;

            // all three present
            if (freq[0] && freq[1] && freq[2])
                count++;
        }
    }
    return count;
}
```

---

### Optimal — Sliding Window O(n)

**The key insight:**

```
When window [l, r] contains all 3 characters:
  ALL substrings from l to end of string are valid
  because extending right can only add more characters
  count += (n - r)

So instead of counting valid windows
count how many starting points have valid windows
```

```cpp
int numberOfSubstrings(string s) {
    int n = s.size();
    int count = 0;
    int freq[3] = {0, 0, 0};
    int l = 0;

    for (int r = 0; r < n; r++) {
        freq[s[r] - 'a']++;      // expand right

        // shrink left while window has all 3
        while (freq[0] && freq[1] && freq[2]) {
            count += (n - r);    // all substrings [l..r], [l..r+1]...[l..n-1] valid
            freq[s[l] - 'a']--;  // shrink left
            l++;
        }
    }
    return count;
}
```

---

### Why `count += (n - r)` Works

```
s = "abcba", n=5

When window [l=0, r=2] = "abc" is valid:
  substrings starting at l=0 ending at r=2,3,4 are all valid:
  "abc", "abcb", "abcba"
  that's n-r = 5-2 = 3 substrings

Then shrink: l=1, window="bc" → not valid, stop while loop

When r=3, window [l=1,r=3]="bcb" → not valid
When r=4, window [l=1,r=4]="bcba":
  valid! count += 5-4 = 1  → "bcba"
  shrink: l=2, window="cba" still valid! count += 5-4 = 1 → "cba"
  shrink: l=3, window="ba" → not valid, stop
```

---

### Dry Run — `s = "abccba"`

```
n=6, freq=[0,0,0], l=0, count=0

r=0: s[0]='a' → freq=[1,0,0]  not valid
r=1: s[1]='b' → freq=[1,1,0]  not valid
r=2: s[2]='c' → freq=[1,1,1]  valid!
  count += 6-2 = 4  → count=4
  remove s[0]='a' → freq=[0,1,1] l=1  not valid, exit while

r=3: s[3]='c' → freq=[0,1,2]  not valid
r=4: s[4]='b' → freq=[0,2,2]  not valid
r=5: s[5]='a' → freq=[1,2,2]  valid!
  count += 6-5 = 1  → count=5
  remove s[1]='b' → freq=[1,1,2] l=2  valid!
  count += 6-5 = 1  → count=6
  remove s[2]='c' → freq=[1,1,1] l=3  valid!
  count += 6-5 = 1  → count=7
  remove s[3]='c' → freq=[1,1,0] l=4  not valid, exit while

Final count = 7 ✅
```

---

### Complexity

| | Brute Force | Sliding Window |
|---|---|---|
| Time | O(n²) | O(n) |
| Space | O(1) | O(1) |
| n=50000 | 2.5 billion ops ❌ | 50000 ops ✅ |

---

### The Sliding Window Signal

```
"number of substrings satisfying some condition"
                    ↓
think sliding window

"at least" condition (not exactly):
  "at least one of each" → shrink when valid
  count += (n-r) captures all valid extensions

"exactly" condition:
  atLeast(k) - atLeast(k+1) trick
```