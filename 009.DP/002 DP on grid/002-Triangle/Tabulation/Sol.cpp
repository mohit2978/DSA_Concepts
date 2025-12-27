#include<bits/stdc++.h>
using namespace std;

class Solution {
  int  dfs(int k,int l ,vector<vector<int>>&d,vector<vector<int>>& tri,vector<vector<int>> &dp){
        for(int i=tri.size()-1;i>=0;i-- ){
            for(int j=tri[i].size()-1;j>=0;j--){
                  if(i==tri.size()-1) {
                     dp[i][j]=tri[i][j];
                    continue;
                  }
                  int res=INT_MAX;
                   for(int m=0;m<2;m++){
                        int newi=i+d[m][0];
                        int newj=j+d[m][1];
                        res= min(res,dp[newi][newj]+tri[i][j]);
                    }
                dp[i][j]=res;
            }
        }
      
        return dp[k][l];
    }
public:
    int minTriangleSum(vector<vector<int>>& triangle) {
        int n=triangle.size();
        int m=triangle[n-1].size();
        vector<vector<int>> d={{1,0},{1,1}};
        vector<vector<int>> dp(n,vector<int>(m,0));
        return dfs(0,0,d,triangle,dp);
    }
};