#include<bits/stdc++.h>
using namespace std;

class Solution {
  int  dfs(int k,int l ,vector<vector<int>>&d,vector<vector<int>>& tri){
        int n=tri.size();
        int m=tri[n-1].size();
        vector<int> front(m, 0); 
        vector<int> cur(m, 0);  
        for(int j=m-1;j>=0;j--){
            front[j]=tri[n-1][j];
        }
        for(int i=tri.size()-2;i>=0;i-- ){
            for(int j=tri[i].size()-1;j>=0;j--){
                  int res=INT_MAX;
                   for(int m=0;m<2;m++){
                        //int newi=i+d[m][0];
                        int newj=j+d[m][1];
                        res= min(res,front[newj]+tri[i][j]);
                    }
                cur[j]=res;
            }
            front=cur;
        }
      
        return front[l];
    }
public:
    int minTriangleSum(vector<vector<int>>& triangle) {
        int n=triangle.size();
        int m=triangle[n-1].size();
        vector<vector<int>> d={{1,0},{1,1}};
        return dfs(0,0,d,triangle);
    }
};

int main() {
    vector<vector<int> > triangle{{1},
                                   {2, 3},
                                   {3, 6, 7},
                                   {8, 9, 6, 10}};
    
    //Create an instance of the Solution class
    Solution sol;
    
    // Call the minimumPathSum function and print result
    cout << sol.minTriangleSum(triangle);

    return 0;
}