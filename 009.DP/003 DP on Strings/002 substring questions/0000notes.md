# Notes


![alt text](<005 dp on string_231121_163402.jpg>)


![alt text](<005 dp on string_231121_163402(1).jpg>) ![alt text](<005 dp on string_231121_163402(2).jpg>) ![alt text](<005 dp on string_231121_163402(3).jpg>) ![alt text](<005 dp on string_231121_163402(4).jpg>) ![alt text](<005 dp on string_231121_163402(5).jpg>) 

```java
class Solution {
  int MOD=1000000007;
  public int numDistinct_memo(String s1, String s2, int n, int m, int[][] dp) {
    if (m == 0) {
      return dp[n][m] = 1;
    }
    if (n == 0) {
      return dp[n][m] = 0;
    }
    if (dp[n][m] != -1) return dp[n][m];
    if (s1.charAt(n - 1) == s2.charAt(m - 1)) {

      int a1 = numDistinct_memo(s1, s2, n - 1, m - 1, dp);
      int a2 = numDistinct_memo(s1, s2, n - 1, m, dp);
      return dp[n][m] = (a1 + a2)%MOD;
    } else return dp[n][m] = numDistinct_memo(s1, s2, n - 1, m, dp);
  }

  public int distinctSubsequences(String s1, String s2) {
    int n = s1.length();
    int m = s2.length();
    int[][] dp = new int[n + 1][m + 1];
    for (int[] d : dp) {
      Arrays.fill(d, -1);
    }

    int res = numDistinct_memo(s1, s2, n, m, dp);
    return res;
  }
}

```

![alt text](<005 dp on string_231121_163402(6).jpg>) 

```java
class Solution {
    int MOD=1000000007;
  public int numDistinct_memo(String s1, String s2, int N, int M, int[][] dp) {
    for (int n = 0; n <= N; n++) {
      for (int m = 0; m <= M; m++) {
        if (m == 0) {
          dp[n][m] = 1;
          continue;
        }
        if (n == 0) {
          dp[n][m] = 0;
          continue;
        }

        if (s1.charAt(n - 1) == s2.charAt(m - 1)) {

          int a1 = dp[n - 1][m - 1];
          int a2 = dp[n - 1][m];
          dp[n][m] = (a1 + a2)%MOD;
        } else dp[n][m] = dp[n - 1][m];
      }
    }
    return dp[N][M];
  }

  public int distinctSubsequences(String s1, String s2) {
    int n = s1.length();
    int m = s2.length();
    int[][] dp = new int[n + 1][m + 1];
    for (int[] d : dp) {
      Arrays.fill(d, -1);
    }

    int res = numDistinct_memo(s1, s2, n, m, dp);

    return res;
  }
}

```


![alt text](<005 dp on string_231121_163402(7).jpg>) ![alt text](<005 dp on string_231121_163402(8).jpg>) ![alt text](<005 dp on string_231121_163402(9).jpg>) 

```cpp
class Solution {

public:
    string longestPalindrome(string s) {
        int n = s.length();
        int dp[n][n];
        int len = 0;
        int si = 0;
        int count = 0;
        for (int gap = 0; gap < n; gap++) {
            for (int i = 0, j = gap; j < n; i++, j++) {
                if (gap == 0)
                    dp[i][j] = 1;
                else if (gap == 1)
                    dp[i][j] = s[i] == s[j] ? 2 : 0;
                else
                    dp[i][j] = s[i] == s[j] && dp[i + 1][j - 1] != 0
                                   ? dp[i + 1][j - 1] + 2
                                   : 0;

                if (dp[i][j] > len) {
                    len = dp[i][j];
                    si = i;
                }
            }
        }

        return s.substr(si, len);
    }
};
```
Tc-> O($n^2$)
Sc-> O($n^2$)

Now we need SC O(1)


```java
class Solution {
    public int expand(String s,int L,int R){
        int l=L;
        int r=R;
        while(l>=0&&r<s.length()&&s.charAt(l)==s.charAt(r)){
            l--;
            r++;
        }
        return r-l-1;
    }
   
    public String longestPalindrome(String s) {
     if(s.length()==0) return "";
     if(s.length()==1) return s;
     int start=0;
     int end=0;
     for(int i=0;i<s.length();i++){
         int l1=expand(s,i,i);
         int l2=expand(s,i,i+1);
         int len=Math.max(l1,l2);
         if(len>end-start){
             start=i-(len-1)/2;
             end=i+len/2;
         }
     }
        return s.substring(start,end+1);
        
    }
}
```
## Longest Palindromic Substring — Complete Explanation

### The Core Idea — Expand Around Center

```
Every palindrome has a CENTER
Odd length:  "racecar" → center is 'e' (single char)
Even length: "abba"   → center is between 'b' and 'b'

Strategy:
  for each possible center
  expand outward while characters match
  track the longest palindrome found
```

---

### Why Two Cases (l1 and l2)

```
l1 = expand(s, i, i)      ← ODD length palindrome
     same index for L and R
     center = single character

     Example: "aba"
     center at 'b' (index 1)
     L=1, R=1 → both point to 'b'

l2 = expand(s, i, i+1)   ← EVEN length palindrome
     adjacent indices for L and R
     center = between two characters

     Example: "abba"
     center between 'b','b' (index 1,2)
     L=1, R=2 → point to both 'b's
```

---

### The Expand Function

```java
public int expand(String s, int L, int R) {
    int l = L;
    int r = R;

    while (l >= 0 && r < s.length() && s.charAt(l) == s.charAt(r)) {
        l--;    // expand left
        r++;    // expand right
    }

    return r - l - 1;   // length of palindrome found
}
```

**Trace on "racecar", center at 'e' (index 3):**

```
s = r  a  c  e  c  a  r
    0  1  2  3  4  5  6

L=3, R=3 (both at 'e')

Step 1: s[3]='e' == s[3]='e' → l=2, r=4
Step 2: s[2]='c' == s[4]='c' → l=1, r=5
Step 3: s[1]='a' == s[5]='a' → l=0, r=6
Step 4: s[0]='r' == s[6]='r' → l=-1, r=7
Step 5: l=-1 < 0 → STOP

return r - l - 1 = 7 - (-1) - 1 = 7 ✅
length of "racecar" = 7
```

---

### Why `r - l - 1`

```
When while loop exits:
  l and r have gone ONE STEP TOO FAR
  the palindrome is actually [l+1, r-1]

Length = (r-1) - (l+1) + 1
       = r - 1 - l - 1 + 1
       = r - l - 1  ✅

Example:
  l=-1, r=7
  palindrome = [l+1, r-1] = [0, 6]
  length = 6 - 0 + 1 = 7
  r - l - 1 = 7 - (-1) - 1 = 7 ✅
```

---

### The start and end Calculation

```java
if (len > end - start) {
    start = i - (len - 1) / 2;
    end   = i + len / 2;
}
```

Yes! Exactly right. Let me confirm this clearly.

---

### Why `expand(i, i)` Always Returns Odd Length

```
Start: l=i, r=i  (same position)

Initial state: window = [i, i] = 1 char
               length = 1  (ODD)

Each expansion:
  l--  and  r++
  window grows by 2 (one on each side)

  1 char → 3 chars → 5 chars → 7 chars...
  always ODD ✅
```

```
"racecar", center i=3:

step 0: [3,3]   = "e"       length=1  ← ODD
step 1: [2,4]   = "cec"     length=3  ← ODD
step 2: [1,5]   = "aceca"   length=5  ← ODD
step 3: [0,6]   = "racecar" length=7  ← ODD
```

---

### Why `expand(i, i+1)` Always Returns Even Length

```
Start: l=i, r=i+1  (adjacent positions)

Initial state: window = [i, i+1] = 2 chars
               length = 2  (EVEN) if they match
               length = 0  (special case) if no match

Each expansion:
  l--  and  r++
  window grows by 2

  0 → 2 → 4 → 6 → 8...
  always EVEN ✅
```

```
"abba", center i=1,2:

step 0: [1,2]   = "bb"   length=2  ← EVEN
step 1: [0,3]   = "abba" length=4  ← EVEN
step 2: [-1,4]  = stop
```

---

### The Special Case — `expand(i, i+1)` Returns 0

```
When s[i] != s[i+1]:
  while condition fails immediately
  l=i, r=i+1 (no movement)

  return r - l - 1
       = (i+1) - i - 1
       = 0

0 is EVEN ✅ still consistent
means "no even palindrome centered here"
```

---

### So the Formula Always Works

```
l1 = expand(i, i)    → odd  length: 1,3,5,7...
l2 = expand(i, i+1)  → even length: 0,2,4,6...

len = max(l1, l2)

start = i - (len-1)/2
end   = i + len/2

For ODD len:
  (len-1)/2 == len/2     → symmetric around i ✅

For EVEN len:
  (len-1)/2 != len/2     → asymmetric, i is left-center ✅
```

---

### One Line Summary

```
expand(i, i)   → starts with 1 char  → grows by 2 → always ODD
expand(i, i+1) → starts with 2 chars → grows by 2 → always EVEN
                  (or 0 if first chars don't match)
```

Your intuition is perfectly correct — the parity is **fixed by the starting condition** and never changes during expansion.



>Note:Now remember (i,i) will give odd length as output and (i,i+1) even length!!

> we take max of both!!taking i as center!!

suppose from i is odd length palindrome and l is length!!

for odd length i in center so (l-1)/2 on both sides!!!

for even length i in center left i+1 on center right!!

l is length see `mnbcaddacbzx` left d is center left!! startinfg of palindrome i.e. left `b` is 3rd character to left from left d and right b is 4th character to right of left d!!

total length is 8!!

so on left (l-1)/2

and on right l/2

for when l is odd on right we need (l-1)/2 but l id odd so either (l-1)/2 or l/2 both works!!

So we use formula of even length always!!!



---

### Complexity

```
Time:  O(n²)
  n centers × O(n) expansion each

Space: O(1)
  only pointers, no extra array
```


```cpp
class Solution {
    int expand(string& s, int l, int r) {
        while (l >= 0 && r < s.size() && s[l] == s[r]) {
            l--;
            r++;
        }
        return r - l - 1;
    }

public:
    string longestPalindrome(string s) {
        if (s.size() == 0) return "";
        if (s.size() == 1) return s;

        int start = 0, end = 0;

        for (int i = 0; i < s.size(); i++) {
            int l1 = expand(s, i, i);       // odd length
            int l2 = expand(s, i, i + 1);   // even length
            int len = max(l1, l2);

            if (len > end - start) {
                start = i - (len - 1) / 2;
                end   = i + len / 2;
            }
        }

        return s.substr(start, end - start + 1);
    }
};
```

---

### One Difference from Java

```java
// Java
s.substring(start, end + 1)   // end+1 because exclusive
```

```cpp
// C++
s.substr(start, end - start + 1)
//              ↑ second param is LENGTH not end index
```

```
Java substring(start, end):   end is exclusive index
C++  substr(start, length):   second param is length

length = end - start + 1
```

---

### Everything Else is Same

```
expand logic     → identical
start/end calc   → identical
l1, l2, len      → identical
base cases       → identical
```

Only `string&` (pass by reference) added in C++ to avoid copying the string on every expand call.





## Longest common substring

![alt text](<005 dp on string_231121_163402(17).jpg>)





![alt text](<005 dp on string_231121_163402(18).jpg>) ![alt text](<005 dp on string_231121_163402(19).jpg>)


```cpp
class Solution{
    int func(string& s1, string& s2, int N, int M, vector<vector<int>>& dp) {
    int mxlen=0;

    for(int ind1=1;ind1<=N;ind1++){
      for(int ind2=1;ind2<=M;ind2++){
          if(s1[ind1-1]==s2[ind2-1]){
             dp[ind1][ind2]=1+dp[ind1-1][ind2 -1];
             mxlen=max(mxlen,dp[ind1][ind2]);
             }
      
      }
    }
      return mxlen;
   }
    public: 
    int longestCommonSubstr (string str1, string str2){
        int n = str1.size();
        int m = str2.size();

        vector<vector<int>> dp(n+1, vector<int>(m+1,0));
        //Return the result
        return func(str1, str2, n , m, dp);  
    }
};

```
Compare Loongest common Susbsequence and this clearly see below Longest common subsequence code


#### Longest common subsequence

```cpp
class Solution {
   int func(string& s1, string& s2, int N, int M, vector<vector<int>>& dp) {

    for(int ind1=0;ind1<=N;ind1++){
      for(int ind2=0;ind2<=M;ind2++){
          if(ind1==0||ind2==0){
            dp[ind1][ind2]=0;
            continue;
          }
          if(s1[ind1-1]==s2[ind2-1]) dp[ind1][ind2]=1+dp[ind1-1][ind2 -1];
          else dp[ind1][ind2]=max(dp[ind1][ ind2 -1],dp[ ind1-1][ ind2]);
      }
    }
      return dp[N][M];
   }
  public:
    int lcs(string str1, string str2) {
        int n = str1.size();
        int m = str2.size();

        vector<vector<int>> dp(n+1, vector<int>(m+1, -1));
        //Return the result
        return func(str1, str2, n , m, dp);
    }
};

```
Substring vala isi se liya hai bs else hta dia loop 1 se start kia and maxelne lena pda answer daalne ke lie as answer aaega nhi dp[n][m] mai


 ![alt text](<005 dp on string_231121_163402(20).jpg>) ![alt text](<005 dp on string_231121_163402(21).jpg>) ![alt text](<005 dp on string_231121_163402(22).jpg>)


# Q LC1092. Shortest Common Supersequence

Given two strings `str1` and `str2`, return the shortest string that has both `str1` and `str2` as **subsequences**. If there are multiple valid strings, return **any** of them.

A string `s` is a **subsequence** of string `t` if deleting some number of characters from `t` (possibly `0`) results in the string `s`.

### Example 1:

**Input:** str1 = "abac", str2 = "cab"  
**Output:** "cabac"  
**Explanation:** `str1` = "abac" is a subsequence of "cabac" because we can delete the first "c".  
`str2` = "cab" is a subsequence of "cabac" because we can delete the last "ac".  
The answer provided is the shortest such string that satisfies these properties.

### Example 2:

**Input:** str1 = "aaaaaaaa", str2 = "aaaaaaaa"  
**Output:** "aaaaaaaa"  

### Constraints:

* `1 <= str1.length, str2.length <= 1000`
* `str1` and `str2` consist of lowercase English letters.


```cpp
class Solution{
public:
    //Function to fund the shortest common supersequence
    string shortestCommonSupersequence(string str1, string str2) {
        int n = str1.size();
        int m = str2.size();

        // Create a DP table with dimensions (n+1) x (m+1) initialized to 0
        vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));

        // Initialize the first row and column of the DP table
        for (int i = 0; i <= n; i++) {
            dp[i][0] = 0;
        }
        for (int i = 0; i <= m; i++) {
            dp[0][i] = 0;
        }

        // Fill the DP table
        for (int ind1 = 1; ind1 <= n; ind1++) {
            for (int ind2 = 1; ind2 <= m; ind2++) {
                if (str1[ind1 - 1] == str2[ind2 - 1])
                    dp[ind1][ind2] = 1 + dp[ind1 - 1][ind2 - 1]; 
                else
                    dp[ind1][ind2] = max(dp[ind1 - 1][ind2], dp[ind1][ind2 - 1]); 
            }
        }

        // Reconstruct the shortest supersequence from the DP table
        int len = dp[n][m];
        int i = n;
        int j = m;

        int index = len - 1;
        string ans = "";

        // Build the shortest supersequence by backtracking
        while (i > 0 && j > 0) {
            if (str1[i - 1] == str2[j - 1]) {
                ans += str1[i - 1]; 
                index--;
                i--;
                j--;
            } else if (dp[i - 1][j] > dp[i][j - 1]) {
                ans += str1[i - 1]; 
                i--;
            } else {
                ans += str2[j - 1]; 
                j--;
            }
        }

        // Add remaining characters from str1 or str2
        while (i > 0) {
            ans += str1[i - 1];
            i--;
        }
        while (j > 0) {
            ans += str2[j - 1];
            j--;
        }

        // Reverse the result since we built it backwards
        reverse(ans.begin(), ans.end());
        return ans;
    }
};
```

Here we need to get actual string but if we only need length of `Shortest common Susequence ` we can get by `s1.size()+s2.size()-lcs[s1.size()][s2.size()]`








