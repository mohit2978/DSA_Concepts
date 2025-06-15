class Solution {
    private int func(int ind, int buy, int n, int[] arr, int[][][] dp,int k) {

        if (ind == n||k==2) {
            return 0;
        }

        if (dp[ind][buy][k] != -1) {
            return dp[ind][buy][k];
        }
        int profit = 0;

        if (buy == 0) { 
            profit = Math.max(0 + func(ind + 1, 0, n, arr, dp,k)
            , (-1)*arr[ind] + func(ind + 1, 1, n, arr, dp,k));
        }
        

        if (buy == 1) { 
            profit = Math.max(0 + func(ind + 1, 1, n, arr, dp,k)
            , arr[ind] + func(ind + 1, 0, n, arr, dp,k+1));
        }

        return dp[ind][buy][k] = profit;
    }
//3 states chnaging so 3-d DP
    public int stockBuySell(int[] arr, int n) {
        if (n == 0) 
            return 0;
            
        int[][][] dp = new int[n][2][3];
    
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < 2; j++) {
                Arrays.fill(dp[i][j], -1);
            }
        }

        int ans = func(0, 0, n, arr, dp,0);
        return ans;
    }
}

