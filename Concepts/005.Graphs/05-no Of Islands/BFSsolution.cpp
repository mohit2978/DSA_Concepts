#include <bits/stdc++.h>
using namespace std;

class Solution {
private:
    
    /* Function to determine if the cell
     is valid (within grid's boundaries) */
    bool isValid(int i, int j, int n, int m) {
        if (i < 0 || i >= n) return false;
        if (j < 0 || j >= m) return false;
        
        // Return true if cell is valid
        return true;
    }
    
    void bfs(int i, int j, vector<vector<bool>>& vis, 
             vector<vector<char>>& grid) {

        // Mark the node as visited
        vis[i][j] = true;
        
        // Queue required for BFS traversal
        queue<pair<int, int>> q;
        
        // push the node in queue
        q.push({i, j});
        
        // Dimensions of grid
        int n = grid.size();
        int m = grid[0].size();
        
        // Until the queue becomes empty
        while (!q.empty()) {
            // Get the cell from queue
            pair<int, int> cell = q.front();
            q.pop();
            
            // Determine its row & column
            int row = cell.first;
            int col = cell.second;
            
            // Traverse the 8 neighbours
            for (int delRow = -1; delRow <= 1; delRow++) {
                for (int delCol = -1; delCol <= 1; delCol++) {
                    // Coordinates of new cell
                    int newRow = row + delRow;
                    int newCol = col + delCol;
                    
                    /* Check if the new cell is valid, 
                    unvisited, and a land cell */
                    if (isValid(newRow, newCol, n, m) 
                        && grid[newRow][newCol] == '1' 
                        && !vis[newRow][newCol]) {
                            
                        // Mark the node as visited
                        vis[newRow][newCol] = true;
                        
                        // Push new cell in queue
                        q.push({newRow, newCol});
                    }
                }
            }
        }
    }
    
public:
    // Function to find the number of islands in given grid
    int numIslands(vector<vector<char>>& grid) {
        // Size of the grid
        int n = grid.size();
        int m = grid[0].size();
        
        // Visited array
        vector<vector<bool>> vis(n, vector<bool>(m, false));
        
        // To store the count of islands
        int count = 0;
        
        // Traverse the grid
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                /* If not visited and is a land, 
                start a new traversal */
                if (!vis[i][j] && grid[i][j] == '1') {
                    count++;
                    bfs(i, j, vis, grid);
                }
            }
        }
        
        return count;
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
