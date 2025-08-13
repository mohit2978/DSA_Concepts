// https://leetcode.com/problems/triangle/description/

class Solution {
public:
    int minimumTotal(vector<vector<int>>& tri) {
        if (tri.empty()) return 0;
         if (tri[0].empty()) return 0;
        if(tri.size()==0) return tri[0][0];
        vector<vector<int>> dp;
        dp.resize(tri.size());  // Resize outer vector based on the size of tri

        for (int i = 0; i < tri.size(); i++) {
            dp[i].resize(tri[tri.size()-1].size(), 10001);  // Resize each inner vector based on the corresponding row of tri
        }

        for(int i=0;i<tri.size();i++){
            for(int j=0;j<tri[i].size();j++){
                if(i==0) {
                    dp[i][j]=tri[i][j];
                
                }else{
                    dp[i][j]=10001;
                }
            }
        }

        for(int i=1;i<tri.size();i++){
            for(int j=0;j<tri[i].size();j++){
                int lres=dp[i-1][j];
                int rres=10001;
                if(j>0) rres=dp[i-1][j-1];
                dp[i][j]=min(lres,rres)+tri[i][j];
            }
        }
        int res=10001;
        for(int j=0;j<tri[tri.size()-1].size();j++){
            res=min(res,dp[tri.size()-1][j]);
        }

     
        return res;
    }
};