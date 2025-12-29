#include <bits/stdc++.h>
using namespace std;

class Solution{
    bool canVisit( vector<vector<int>> &grid,vector<vector<bool>> &vis,int i ,int j,int oc){
        int n=grid.size();
        int m=grid[0].size();
        if(i>=0 && i<n && j>=0 && j<m && vis[i][j]==false && grid[i][j]==oc) return true;
        return false;
    }
    void solve (vector<vector<int>> &dir, vector<vector<int>> &grid,vector<vector<bool>> &vis,int i ,int j,int oc,int nc){
        vis[i][j]=true;
        grid[i][j]=nc;
        for(int k=0;k<dir.size();k++){
            int newi=i+dir[k][0];
            int newj=j+dir[k][1];
            if(canVisit(grid,vis,newi,newj,oc)==true){
               solve(dir,grid,vis,newi,newj,oc,nc);
            }
        }
    }
    public:
    vector<vector<int>> floodFill(vector<vector<int>> &img,
                                  int sr, int sc, int newColor) {
        vector<vector<int>>dir={{-1,0},{1,0},{0,1},{0,-1}};
        vector<vector<bool>> vis(img.size(),vector<bool>(img[0].size(),false));
        int oc=img[sr][sc];
        solve(dir,img,vis,sr,sc,oc,newColor);
        return img;
    }
};

int main() {
    vector<vector<int>> image = {
	    {1,1,1},
	    {1,1,0},
	    {1,0,1}
	};
    int sr = 1, sc = 1;
    int newColor = 2;
    
    int n = image.size();
    int m = image[0].size();
    
    /* Creating an instance of 
    Solution class */
    Solution sol; 
    
    /* Function call to find the 
    number of islands in given grid*/
    vector<vector<int>> ans = sol.floodFill(image, sr, sc, newColor);
    
    cout << "Image after performing flood fill algorithm: \n\n";
    
    for(int i=0; i < n; i++) {
        for(int j=0; j < m; j++) {
            cout << ans[i][j] << " "; 
        }
        cout << endl;
    }
    
    return 0;
}