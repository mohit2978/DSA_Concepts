import java.util.*;

class Solution {
    // Function to find the maximum profit earned using memoization
    private int func(int ind, int buy, int cap, int n, int[] arr, int[][][] dp) {
        // Base case 
        if (ind == n || cap == 0) {
            return 0;
        }
        /* If the result for this state has 
        already been calculated, return it*/
        if (dp[ind][buy][cap] != -1) {
            return dp[ind][buy][cap];
        }
        int profit = 0;
        
        // We can buy the stock
        if (buy == 0) { 
            profit = Math.max(0 + func(ind + 1, 0, cap, n, arr, dp), (-1)*arr[ind] + func(ind + 1, 1, cap, n, arr, dp));
        }
        
        // We can sell the stock
        if (buy == 1) { 
            profit = Math.max(0 + func(ind + 1, 1, cap, n, arr, dp), arr[ind] + func(ind + 1, 0, cap-1, n, arr, dp));
        }

        /* Store the value in dp array and
        return the calculated profit */
        return dp[ind][buy][cap] = profit;
    }

    // Function to calculate the maximum profit earned 
    public int stockBuySell(int[] arr, int n, int k) {
        if (n == 0) 
            return 0;
            
        // Declare a DP table to memoize results
        int[][][] dp = new int[n][2][k+1];
        
        // Initialize the dp array with -1
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < 2; j++) {
                Arrays.fill(dp[i][j], -1);
            }
        }

        int ans = func(0, 0, k, n, arr, dp);
        
        // Return the maximum profit
        return ans;
    }

    public static void main(String[] args) {
        int n = 8;
        int[] arr = {3, 3, 5, 0, 0, 3, 1, 4};
        int k = 3;
        
        // Create an instance of Solution class
        Solution sol = new Solution();

        // Call the stockBuySell function and print the result
        System.out.println("The maximum profit that can be generated is " + sol.stockBuySell(arr, n, k));
    }
}
