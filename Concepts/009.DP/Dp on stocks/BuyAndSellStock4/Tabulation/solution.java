class Solution {
        private int func(int n, int[] arr, int[][][] dp,int K) {
        for(int ind=n;ind>=0;ind--){
            for(int buy=0;buy<=1;buy++){
                for(int k=K;k>=0;k--){
                      if (ind == n||k==K) {
                            dp[ind][buy][k]= 0;
                            continue;
                        }
                      
                        int profit = 0;

                        if (buy == 0) { 
                            profit = Math.max(dp[ind + 1] [0] [k]
                            , (-1)*arr[ind] + dp[ind + 1][1][k]);
                        }

                                            
                        if (buy == 1) { 
                            profit = Math.max(dp[ind + 1] [1][k]
                            , arr[ind] + dp[ind + 1] [0][k+1]);
                        }

                      dp[ind][buy][k] = profit;  
                }
            }
        }

        return dp[0][0][0];
    }
//just k transactions very imilar to previous one
    public int stockBuySell4(int[] arr, int n,int k) {
        if (n == 0) 
            return 0;
            
        int[][][] dp = new int[n+1][2][k+1];
    

        int ans = func( n, arr, dp,k);
        return ans;
    }
    public int stockBuySell(int[] arr, int n, int k) {
       return stockBuySell4(arr,n,k);
    }
}

