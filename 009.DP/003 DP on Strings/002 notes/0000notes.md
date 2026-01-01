# Notes


![alt text](<005 dp on string_231121_163402.jpg>)


![alt text](<005 dp on string_231121_163402(1).jpg>) ![alt text](<005 dp on string_231121_163402(2).jpg>) ![alt text](<005 dp on string_231121_163402(3).jpg>) ![alt text](<005 dp on string_231121_163402(4).jpg>) ![alt text](<005 dp on string_231121_163402(5).jpg>) ![alt text](<005 dp on string_231121_163402(6).jpg>) ![alt text](<005 dp on string_231121_163402(7).jpg>) ![alt text](<005 dp on string_231121_163402(8).jpg>) ![alt text](<005 dp on string_231121_163402(9).jpg>) ![alt text](<005 dp on string_231121_163402(10).jpg>) ![alt text](<005 dp on string_231121_163402(11).jpg>) ![alt text](<005 dp on string_231121_163402(12).jpg>) ![alt text](<005 dp on string_231121_163402(13).jpg>) ![alt text](<005 dp on string_231121_163402(14).jpg>) ![alt text](<005 dp on string_231121_163402(15).jpg>) ![alt text](<005 dp on string_231121_163402(16).jpg>) ![alt text](<005 dp on string_231121_163402(17).jpg>)





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
















