class Solution {
    private int func(int n, int[] arr) {
        int[][] ahead = new int[2][3];
        int[][] cur = new int[2][3];
        for(int ind=n;ind>=0;ind--){
            for(int buy=0;buy<=1;buy++){
                for(int k=2;k>=0;k--){
                      if (ind == n||k==2) {
                            ahead[buy][k]= 0;
                            continue;
                        }
                      
                        int profit = 0;

                        if (buy == 0) { 
                            profit = Math.max(ahead[0] [k]
                            , (-1)*arr[ind] + ahead[1][k]);
                        }

                                            
                        if (buy == 1) { 
                            profit = Math.max(ahead [1][k]
                            , arr[ind] +ahead[0][k+1]);
                        }

                      cur[buy][k] = profit;  
                }
            }
            ahead=cur;
        }

        return cur[0][0];
    }

    public int stockBuySell(int[] arr, int n) {
        if (n == 0) 
            return 0;
            
    

        int ans = func( n, arr);
        return ans;
    }
}

