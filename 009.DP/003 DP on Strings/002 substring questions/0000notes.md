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


![alt text](<005 dp on string_231121_163402(7).jpg>) ![alt text](<005 dp on string_231121_163402(8).jpg>) ![alt text](<005 dp on string_231121_163402(9).jpg>) ![alt text](<005 dp on string_231121_163402(10).jpg>) ![alt text](<005 dp on string_231121_163402(11).jpg>) ![alt text](<005 dp on string_231121_163402(12).jpg>) ![alt text](<005 dp on string_231121_163402(13).jpg>) ![alt text](<005 dp on string_231121_163402(14).jpg>) ![alt text](<005 dp on string_231121_163402(15).jpg>) ![alt text](<005 dp on string_231121_163402(16).jpg>) ![alt text](<005 dp on string_231121_163402(17).jpg>)





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








