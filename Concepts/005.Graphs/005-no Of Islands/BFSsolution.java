import java.util.*;

class BFSsolution {
    /* Function to determine if the cell
     is valid (within grid's boundaries) */
    private boolean isValid(int i, int j, 
                            int n, int m) {
                                
        if (i < 0 || i >= n) return false;
        if (j < 0 || j >= m) return false;
        
        // Return true if cell is valid
        return true;
    }
    
    private void bfs(int i, int j, boolean[][] vis, 
                     char[][] grid) {
                         
        // mark it visited
        vis[i][j] = true;
        
        // Queue required for BFS traversal
        Queue<int[]> q = new LinkedList<>();
        
        // push the node in queue
        q.add(new int[]{i, j}); 
        
        // Dimensions of grid
        int n = grid.length; 
        int m = grid[0].length; 
      
        // Until the queue becomes empty
        while (!q.isEmpty()) {
            // Get the cell from queue
            int[] cell = q.poll();
            
            // Determine it's row & column
            int row = cell[0];
            int col = cell[1];
            
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
                        q.add(new int[]{newRow, newCol});
                    }
                }
            }
        }
    }
    
    // Function to find the number of islands in given grid
    public int numIslands(char[][] grid) {
        // Size of the grid
        int n = grid.length;
        int m = grid[0].length;
        
        // Visited array
        boolean[][] vis = new boolean[n][m];
        
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

    public static void main(String[] args) {
        char[][] grid = {
            {'1', '1', '1', '0', '1'},
            {'1', '0', '0', '0', '0'},
            {'1', '1', '1', '0', '1'},
            {'0', '0', '0', '1', '1'}
        };
        
        // Creating an instance of Solution class
        Solution sol = new Solution();
        
        /* Function call to find the
        number of islands in given grid */
        int ans = sol.numIslands(grid);
        
        System.out.println("The total islands in given grids are: " + ans);
    }
}