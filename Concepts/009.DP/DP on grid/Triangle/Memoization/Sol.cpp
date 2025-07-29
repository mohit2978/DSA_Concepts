#include<bits/stdc++.h>
using namespace std;

class Solution {
  int  dfs(int i,int j ,vector<vector<int>>&d,vector<vector<int>>& tri,vector<vector<int>> &dp){
        if(i<0 || i>=tri.size() || j<0 || j>=tri[i].size()) return 0;
        if(i==tri.size()-1) return dp[i][j]=tri[i][j];
        if(dp[i][j]!=-1) return dp[i][j];
        int res=INT_MAX;
        for(int k=0;k<2;k++){
            int newi=i+d[k][0];
            int newj=j+d[k][1];
            res= min(res,dfs(newi,newj,d,tri,dp)+tri[i][j]);
        }
        return dp[i][j]= res;
    }
public:
    int minTriangleSum(vector<vector<int>>& triangle) {
        int n=triangle.size();
        int m=triangle[n-1].size();
        vector<vector<int>> d={{1,0},{1,1}};
        vector<vector<int>> dp(n,vector<int>(m,-1));
        return dfs(0,0,d,triangle,dp);
    }
};