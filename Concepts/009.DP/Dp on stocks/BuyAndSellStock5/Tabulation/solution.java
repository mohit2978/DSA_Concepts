class Solution {
    //just add fee to buy and sell2
    private int func(int n, int[] arr, int[][] dp,int fee) {
        for(int ind=n;ind>=0;ind--){
            for(int buy=0;buy<=1;buy++){
                   if (ind == n) {
                        dp[ind][buy]=0;
                        continue;
                    }

                    int profit = 0;

                    if (buy == 0) { 
                        profit = Math.max(dp[ind + 1] [0]
                        , (-1)*(arr[ind]+fee) + dp[ind + 1] [1]);
                    }
                    
                    if (buy == 1) { 
                        profit = Math.max(dp[ind+1][1]
                        , arr[ind] + dp[ind+1][0]);
                    }

                 dp[ind][buy] = profit;
            }
        }
        return dp[0][0];
    }
//just k transactions very imilar to previous one
    public int stockBuySell5(int[] arr, int n,int fee) {
        if (n == 0) 
            return 0;
            
        int[][] dp = new int[n+1][2];

        int ans = func( n, arr, dp,fee);
        return ans;
    }
    public int stockBuySell(int[] arr, int n, int fee) {
       return stockBuySell5(arr,n,fee);
    }
}
