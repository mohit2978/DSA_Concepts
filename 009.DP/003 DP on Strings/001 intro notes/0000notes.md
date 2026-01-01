# Notes
![alt text](<004 dp on string_231121_163402.jpg>)
![alt text](<004 dp on string_231121_163402(1).jpg>) ![alt text](<004 dp on string_231121_163402(2).jpg>)
![alt text](<004 dp on string_231121_163402(3).jpg>) ![alt text](<004 dp on string_231121_163402(4).jpg>) ![alt text](<004 dp on string_231121_163402(5).jpg>) ![alt text](<004 dp on string_231121_163402(6).jpg>) ![alt text](<004 dp on string_231121_163402(7).jpg>) 

##  LCS Memoization

```cpp
class Solution {
   int func(string& s1, string& s2, int ind1, int ind2, vector<vector<int>>& dp) {

    if (ind1 < 0 || ind2 < 0) return 0;
    if (dp[ind1][ind2] != -1) return dp[ind1][ind2];
    if(s1[ind1]==s2[ind2]) 
      return dp[ind1][ind2]=1+func(s1, s2, ind1-1, ind2 -1, dp);
    else 
      return dp[ind1][ind2]=max(func(s1, s2, ind1, ind2 -1, dp),func(s1, s2, ind1-1, ind2, dp));
   }
  public:
    int lcs(string str1, string str2) {
        int n = str1.size();
        int m = str2.size();

        vector<vector<int>> dp(n, vector<int>(m, -1));
        //Return the result
        return func(str1, str2, n - 1, m - 1, dp);
    }
};

```

## Tabulation

isse tabulation mai dikkat aaegi ab ind1-1,ind2-1 alag se handle krna pdega so no 

```cpp
class Solution {
   int func(string& s1, string& s2, int Nm1, int Mm1, vector<vector<int>>& dp) {

    for(int ind1=0;ind1<=Nm1;ind1++){
      for(int ind2=0;ind2<=Mm1;ind2++){
          if(s1[ind1]==s2[ind2]) dp[ind1][ind2]=1+dp[ind1-1][ind2 -1];
          else dp[ind1][ind2]=max(dp[ind1][ ind2 -1],dp[ ind1-1][ ind2]);
      }
    }
      return dp[Nm1][Mm1];
   }
  public:
    int lcs(string str1, string str2) {
        int n = str1.size();
        int m = str2.size();

        vector<vector<int>> dp(n, vector<int>(m, -1));
        //Return the result
        return func(str1, str2, n - 1, m - 1, dp);
    }
};


```
instead make  dp array of string.size()+1, in recusrion avoid less than zero vali condition as tabulation mai handle krna difficult rehta usko 

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


![alt text](Scanned_20260101-2121.jpg)

![alt text](Scanned_20260101-2134.jpg)

![alt text](<004 dp on string_231121_163402(8).jpg>) ![alt text](<004 dp on string_231121_163402(9).jpg>) ![alt text](<004 dp on string_231121_163402(10).jpg>) ![alt text](<004 dp on string_231121_163402(11).jpg>) ![alt text](<004 dp on string_231121_163402(12).jpg>) ![alt text](<004 dp on string_231121_163402(13).jpg>) ![alt text](<004 dp on string_231121_163402(14).jpg>) ![alt text](<004 dp on string_231121_163402(15).jpg>) ![alt text](<004 dp on string_231121_163402(16).jpg>) ![alt text](<004 dp on string_231121_163402(17).jpg>) ![alt text](<004 dp on string_231121_163402(18).jpg>) ![alt text](<004 dp on string_231121_163402(19).jpg>) 


