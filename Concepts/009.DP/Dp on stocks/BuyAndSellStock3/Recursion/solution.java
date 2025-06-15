import java.util.*;

class Solution {
//now we can put capacity=anything like 3 buy and sell 4 buy and sell and so on for this have 2
    private int func(int ind, int buy, int cap, int n, int[] arr) {
 
        if (ind == n || cap == 0) {
            return 0;
        }

        int profit = 0;
        
        if (buy == 0) { 
            profit = Math.max(0 + func(ind + 1, 0, cap, n, arr)
            , (-1)*arr[ind] + func(ind + 1, 1, cap, n, arr));
        }
        
        // We can sell the stock
        if (buy == 1) { 
            profit = Math.max(0 + func(ind + 1, 1, cap, n, arr)
            , arr[ind] + func(ind + 1, 0, cap-1, n, arr));
        }

        return profit;
    }
 
    public int stockBuySell(int[]arr, int n) {
        if (n == 0) 
            return 0;

        int ans = func(0, 0, 2, n, arr);
        
        return ans;
    }

    public static void main(String[] args) {
        int n = 8;
        int[] arr = {3, 3, 5, 0, 0, 3, 1, 4};

        Solution sol = new Solution();
        System.out.println("The maximum profit that can be generated is " + sol.stockBuySell(arr, n));
    }
}
