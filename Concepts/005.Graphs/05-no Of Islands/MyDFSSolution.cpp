#include <bits/stdc++.h>
using namespace std;

class Solution{
    bool canVisit( vector<vector<char>> &grid,vector<vector<bool>> &vis,int i ,int j){
        int n=grid.size();
        int m=grid[0].size();
        if(i>=0 && i<n && j>=0 && j<m && vis[i][j]==false && grid[i][j]=='1') return true;
        return false;
    }
    void solve (vector<vector<int>> &dir, vector<vector<char>> &grid,vector<vector<bool>> &vis,int i ,int j){
        vis[i][j]=true;
        for(int k=0;k<dir.size();k++){
            int newi=i+dir[k][0];
            int newj=j+dir[k][1];
            if(canVisit(grid,vis,newi,newj)==true){
               solve(dir,grid,vis,newi,newj);
            }
        }
    }
public:
    int numIslands(vector<vector<char>> &grid){
        vector<vector<int>>dir={{-1,0},{1,0},{0,1},{0,-1},{-1,1},{1,-1},{1,1},{-1,-1}};
        vector<vector<bool>> vis(grid.size(),vector<bool>(grid[0].size(),false));
        int cnt=0;
        for(int i=0;i<grid.size();i++){
            for(int j=0;j<grid[0].size();j++){
                if(canVisit(grid,vis,i,j)==true){
                    solve(dir,grid,vis,i,j);
                    cnt++;
                }
            }
        }
        return cnt;
    }
};


int main() {
    vector<vector<char>> grid = {
        {'1', '1', '1', '0', '1'},
        {'1', '0', '0', '0', '0'},
        {'1', '1', '1', '0', '1'},
        {'0', '0', '0', '1', '1'}
    };
    
    // Creating an instance of Solution class
    Solution sol;
    
    /* Function call to find the
    number of islands in given grid */
    int ans = sol.numIslands(grid);
    
    cout << "The total islands in given grids are: " << ans << endl;
    
    return 0;
}
