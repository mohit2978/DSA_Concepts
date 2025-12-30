#include <bits/stdc++.h>
using namespace std;

class Solution {
private:
    // DelRow and delCol for neighbors
    vector<int> delRow = {-1, 0, 1, 0};
    vector<int> delCol = {0, 1, 0, -1};
    
    /* Helper Function to check if a 
    cell is within boundaries */
    bool isValid(int &i, int &j, 
                 int &n, int &m) {
        
        // Return false if cell is invalid
        if(i < 0 || i >= n) return false;
        if(j < 0 || j >= m) return false;
        
        // Return true if cell is valid
        return true;
    }
    
    // Function to perform BFS traversal 
    void bfs(vector<vector<int>> &grid,
             queue<pair<int,int>> &q,
             vector<vector<bool>> &vis) {
        
        // Getting the dimensions of image
        int n = grid.size();
        int m = grid[0].size(); 
        
        // Until the queue is empty
        while(!q.empty()) {
            // Get the cell from queue
            auto cell = q.front();
            q.pop();
            
            // Get its coordinates
            int row = cell.first;
            int col = cell.second;
            
            // Traverse its 4 neighbors
            for(int i=0; i < 4; i++) {
                
                // Coordinates of new cell
                int nRow = row + delRow[i]; 
                int nCol = col + delCol[i]; 
                
                /* check for valid, unvisited 
                and land cells */
                if(isValid(nRow, nCol, n, m) && 
                   grid[nRow][nCol] == 1 
                   && vis[nRow][nCol] == false) {
                    
                    /* Mark the new cell as visited
                    and add it to the queue */
                    vis[nRow][nCol] = true;
                    q.push({nRow, nCol});
                }
            }
        }
    }
    
public:
    // Function to find number of enclaves 
    int numberOfEnclaves(vector<vector<int>> &grid) {
        
        // Get the dimensions of grid
        int n = grid.size();
        int m = grid[0].size();
        
        // Queue for BFS traversal
        queue <pair<int,int>> q;
        
        // Visited array
        vector<vector<bool>> vis(n, vector<bool>(m, false));
        
        /* Traverse the grid and add 
        the border land cells to queue */
        for(int i=0; i < n; i++) {
            for(int j=0; j < m; j++) {
                
                /* If the land cell is at
                border, add it to queue */
                if((i == 0 || i == n-1 ||
                    j == 0 || j == m-1) &&
                    grid[i][j] == 1) {
                    
                    vis[i][j] = true;
                    q.push({i, j});
                }
            }
        }
       
        /* Perform the bfs traversal 
        from border land cells */
        bfs(grid, q, vis);
        
        // Count to store number of enclaves
        int count = 0;
        
        // Traverse the grid
        for(int i=0; i < n; i++) {
            for(int j=0; j < m; j++){
                
                /* If cell is a land cell and
                 unvisited, update the count */
                if(grid[i][j] == 1 && !vis[i][j])
                    count++;
            }
        }
        
        // Return count as answer
        return count;
    }
};

int main() {
    vector<vector<int>> grid = {
        {0, 0, 0, 1}, 
        {1, 0, 1, 0}, 
        {0, 0, 1, 0}, 
        {0, 0, 0, 0}
	};
    
    /* Creating an instance of 
    Solution class */
    Solution sol; 
    
    // Function call to get number of enclaves
    int ans = sol.numberOfEnclaves(grid);
    
    cout << "The number of enclaves in given grid are: " << ans;
    return 0;
}