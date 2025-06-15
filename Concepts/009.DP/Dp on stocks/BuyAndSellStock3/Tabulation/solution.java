class Solution {
    //tc->O(2*3*n) and same sc
    private int func(int n, int[] arr, int[][][] dp) {
        for(int ind=n;ind>=0;ind--){
            for(int buy=0;buy<=1;buy++){
                for(int k=2;k>=0;k--){
                      if (ind == n||k==2) {
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

    public int stockBuySell(int[] arr, int n) {
        if (n == 0) 
            return 0;
            
        int[][][] dp = new int[n+1][2][3];
    

        int ans = func( n, arr, dp);
        return ans;
    }
}

