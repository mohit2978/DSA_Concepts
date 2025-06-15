import java.util.*;

class Solution {

    private int func(int[] arr, int n, int fee) {

        int[] ahead = new int[2];
        int[] cur = new int[2];


        for (int ind = n - 1; ind >= 0; ind--) {
            

            for (int buy = 0; buy <= 1; buy++) {

                if (buy == 0) {
                    cur[buy] = Math.max(0 + ahead[0],(-1)*arr[ind] + ahead[1]);
                }

                if (buy == 1) {
                    cur[buy] = Math.max(0 + ahead[1],arr[ind]-fee + ahead[0]);
                }
            }
            ahead = cur;
        }

        // Return the maximum profit 
        return cur[0];
    }

    // Function to find out maximum profit
    public int stockBuySell(int[] arr, int n, int fee) {
        // Return the answer
        return func(arr, n, fee);
    }

    public static void main(String[] args) {
        int[] prices = {3, 3, 5, 0, 0, 3, 1, 4};
        int n = prices.length;
        int fee = 1;

        // Create an instance of the Solution class
        Solution sol = new Solution();

        // Call the function and print the result
        System.out.println("The maximum profit that can be generated is " + sol.stockBuySell(prices, n, fee));
    }
}
