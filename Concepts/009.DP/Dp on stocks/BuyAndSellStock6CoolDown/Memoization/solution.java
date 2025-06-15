class Solution {
    
    private int func(int ind, int buy, int n, int[] arr, int[][][] dp,int coolDown) {
    //Leetcode 309 having cooldown=1 now in this can put cooldown of any k!!
    //TC-->O(N)
        if (ind == n) {
            return 0;
        }

        if (dp[ind][buy][coolDown] != -1) {
            return dp[ind][buy][coolDown];
        }
        int profit = 0;

        if (buy == 0 && coolDown==0) { 
            profit = Math.max( func(ind + 1, 0, n, arr, dp,coolDown)// dont buy
            , (-1)*arr[ind] + func(ind + 1, 1, n, arr, dp,coolDown));//buy
        }
        
        if(coolDown!=0){
             profit = func(ind + 1, 0, n, arr, dp,coolDown-1);
        }

        if (buy == 1 && coolDown==0) { 
            profit = Math.max(0 + func(ind + 1, 1, n, arr, dp,coolDown)// dont sell
            , arr[ind] + func(ind + 1, 0, n, arr, dp,coolDown+1));//sell so increase cooldown
        }

        return dp[ind][buy][coolDown] = profit;
    }

    // Function to calculate the maximum profit earned 
    public int stockBuySell(int[] arr, int n,int coolDown) {
        if (n == 0) 
            return 0;

        int[][][] dp = new int[n][2][coolDown];

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < coolDown; j++) {
                Arrays.fill(dp[i][j], -1);
            }
        } 

        int ans = func(0, 0, n, arr, dp,0);
        return ans;
    }
    public int maxProfit(int[] prices) {
        return stockBuySell(prices,prices.length,2);
    }
}