import java.util.*;
class Solution {

    private int func(int ind, int buy, int n, int[] arr, int[][] dp) {

        if (ind == n) {
            return 0;
        }

        if (dp[ind][buy] != -1) {
            return dp[ind][buy];
        }
        int profit = 0;

        if (buy == 0) { 
            profit = Math.max(0 + func(ind + 1, 0, n, arr, dp)
            , (-1)*arr[ind] + func(ind + 1, 1, n, arr, dp));
        }
        

        if (buy == 1) { 
            profit = Math.max(0 + func(ind + 1, 1, n, arr, dp)
            , arr[ind] + func(ind + 1, 0, n, arr, dp));
        }

        return dp[ind][buy] = profit;
    }

    // Function to calculate the maximum profit earned 
    public int stockBuySell(int[] arr, int n) {
        if (n == 0) 
            return 0;
            
        int[][] dp = new int[n][2];
        for (int[] row : dp) {
            Arrays.fill(row, -1);
        }

        int ans = func(0, 0, n, arr, dp);
        return ans;
    }

    public static void main(String[] args) {
        int n = 6;
        int[] arr = {7, 1, 5, 3, 6, 4};
        Solution sol = new Solution();
        System.out.println("The maximum profit that can be generated is " + sol.stockBuySell(arr, n));
    }
}
