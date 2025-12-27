class Solution {

    private int func( int n, int[] arr, int[][] dp) {
        for(int ind=n;ind>=0;ind--){
            for(int buy=0;buy<=1;buy++){
                   if (ind == n) {
                        dp[ind][buy]=0;
                        continue;
                    }

                    int profit = 0;

                    if (buy == 0) { 
                        profit = Math.max(dp[ind + 1] [0]
                        , (-1)*arr[ind] + dp[ind + 1] [1]);
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
    public int stockBuySell(int[] arr, int n) {
        if (n == 0) 
            return 0;
            
        int[][] dp = new int[n+1][2];

        int ans = func( n, arr, dp);
        return ans;
    }
        public static void main(String[] args) {
        int n = 6;
        int[] arr = {7, 1, 5, 3, 6, 4};
        
        // Create an instance of Solution class
        Solution sol = new Solution();

        // Call the stockBuySell function and print the result
        System.out.println("The maximum profit that can be generated is " + sol.stockBuySell(arr, n));
    }
}
