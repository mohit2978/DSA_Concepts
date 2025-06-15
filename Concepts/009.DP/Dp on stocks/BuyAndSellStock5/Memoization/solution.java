class Solution {
    //just copy from Buy and sell2 and add up fee!!        
    private int func(int ind, int buy, int n, int[] arr, int[][] dp,int fee) {

        if (ind == n) {
            return 0;
        }

        if (dp[ind][buy] != -1) {
            return dp[ind][buy];
        }
        int profit = 0;

        if (buy == 0) { 
            profit = Math.max(0 + func(ind + 1, 0, n, arr, dp,fee)
            , (-1)*(arr[ind]+fee) + func(ind + 1, 1, n, arr, dp,fee));
        }
        

        if (buy == 1) { 
            profit = Math.max(0 + func(ind + 1, 1, n, arr, dp,fee)
            , arr[ind] + func(ind + 1, 0, n, arr, dp,fee));
        }

        return dp[ind][buy] = profit;
    }
    public int stockBuySell5(int[] arr, int n,int fee) {
        if (n == 0) 
            return 0;
            
        int[][] dp = new int[n][2];
        for (int[] row : dp) {
            Arrays.fill(row, -1);
        }

        int ans = func(0, 0, n, arr, dp,fee);
        return ans;
    }
    public int stockBuySell(int[] arr, int n, int fee) {
       return stockBuySell5(arr,n,fee);
    }
}
