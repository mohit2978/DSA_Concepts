import java.util.*;

/*
An image is represented by a 2-D array of integers, each integer representing 
the pixel value of the image. Given a coordinate (sr, sc) representing the starting pixel (row and column)
 of the flood fill, and a pixel value newColor, "flood fill" the image.



To perform a flood fill, consider the starting pixel, plus any pixels connected 4-directionally 
to the starting pixel of the same colour as the starting pixel, plus any pixels connected 4-directionally
 to those pixels (also with the same colour as the starting pixel), and so on. Replace the colour of all of the aforementioned pixels with the newColor.

 Input: image = [ [1, 1, 1], [1, 1, 0], [1, 0, 1] ], sr = 1, sc = 1, newColor = 2

Output: [ [2, 2, 2], [2, 2, 0], [2, 0, 1] ]

Explanation: From the center of the image with position (sr, sc) = (1, 1) (i.e., the red pixel), all pixels connected by a path of the same color as the starting pixel (i.e., the blue pixels) are colored with the new color.

Note the bottom corner is not colored 2, because it is not 4-directionally connected to the starting pixel.

Input: image = [ [0, 1, 0], [1, 1, 0], [0, 0, 1] ], sr = 2, sc = 2, newColor = 3

Output: [ [0, 1, 0], [1, 1, 0], [0, 0, 3] ]

Explanation: Starting from the pixel at position (2, 2) (i.e., the blue pixel), we flood fill all adjacent pixels that have the same color as the starting pixel. In this case, only the pixel at position (2, 2) itself is of the same color. So, only that pixel gets colored with the new color, resulting in the updated image.
*/

class Solution {
    
    // DelRow and delCol for neighbors
    private int[] delRow = {-1, 0, 1, 0};
    private int[] delCol = {0, 1, 0, -1};
    
    /* Helper Function to check if a 
    pixel is within boundaries */
    private boolean isValid(int i, int j, 
                            int n, int m) {
                                
        // Return false if pixel is invalid
        if (i < 0 || i >= n) return false;
        if (j < 0 || j >= m) return false;
        
        // Return true if pixel is valid
        return true;
    }
    
    // Function to perform DFS traversal 
    private void dfs(int row, int col, int[][] ans, 
                     int[][] image, int newColor, 
                     int iniColor) {
                         
        // color with new color
        ans[row][col] = newColor;
        
        // Getting the dimensions of image
        int n = image.length;
        int m = image[0].length;
        
        // Traverse the 4 neighbors
        for (int i = 0; i < 4; i++) {
            // Coordinates of new pixel
            int nrow = row + delRow[i];
            int ncol = col + delCol[i];
            
            // check for valid, unvisited pixels
            // having same initial color
            if (isValid(nrow, ncol, n, m) && 
                image[nrow][ncol] == iniColor &&
                ans[nrow][ncol] != newColor) {
                    
                // Recursively perform DFS
                dfs(nrow, ncol, ans, image, 
                    newColor, iniColor);
            }
        }
    }
    
    public int[][] floodFill(int[][] image, int sr, 
                             int sc, int newColor) {
        // Store initial color
        int iniColor = image[sr][sc];
        
        // To store the updated image
        int[][] ans = new int[image.length][image[0].length];
        
        for (int i = 0; i < image.length; i++) {
            ans[i] = Arrays.copyOf(image[i], image[i].length);
        }
        
        // Start DFS traversal from start cell
        dfs(sr, sc, ans, image, newColor, iniColor);
        
        // Return the answer image
        return ans;
    }
    
    public static void main(String[] args) {
        int[][] image = {
            {1, 1, 1},
            {1, 1, 0},
            {1, 0, 1}
        };
        int sr = 1, sc = 1;
        int newColor = 2;
        
        // Creating an instance of Solution class
        Solution sol = new Solution();
        
        // Function call to find the number of islands in given grid
        int[][] ans = sol.floodFill(image, sr, sc, newColor);
        
        System.out.println("Image after performing flood fill algorithm:\n");
        
        for (int[] row : ans) {
            for (int col : row) {
                System.out.print(col + " ");
            }
            System.out.println();
        }
    }
}
