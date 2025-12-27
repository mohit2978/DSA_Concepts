class Solution {
    //Leetcode 309 having cooldown=1 now in this can put cooldown of any k!!
    //TC-->O(N)
    private int func( int n, int[] arr, int[][][] dp,int k) {
        for(int ind =n;ind>=0;ind--){
            for(int buy=0;buy<=1;buy++){
                for(int coolDown=0;coolDown<=k;coolDown++){
                            if (ind == n) {
                               dp[ind][buy][coolDown]=0;
                               continue;
                            }

                            int profit = 0;

                            if (buy == 0 && coolDown==0) { 
                                profit = Math.max( dp[ind + 1][0][coolDown]// dont buy
                                , (-1)*arr[ind] + dp[ind + 1][ 1][coolDown]);//buy
                            }
                            
                            if(coolDown!=0){
                                profit =dp[ind + 1][0][coolDown-1];
                            }

                            if (buy == 1 && coolDown==0) { 
                                profit = Math.max(dp[ind + 1][1][coolDown]// dont sell
                                , arr[ind] + dp[ind + 1][0][coolDown+1]);//sell so increase cooldown
                            }

                         dp[ind][buy][coolDown] = profit;
                }
            }
        }
        return dp[0][0][0];

    }

    // Function to calculate the maximum profit earned 
    public int stockBuySell(int[] arr, int n,int coolDown) {
        if (n == 0) 
            return 0;

        int[][][] dp = new int[n+1][2][coolDown];

        int ans = func( n, arr, dp,1);
        return ans;
    }
    public int maxProfit(int[] prices) {
        return stockBuySell(prices,prices.length,2);
    }
}