class Solution {
    //My way
    private int func(int n, int[] arr, int[][][] dp,int K) {

     int[][] ahead = new int[2][K+1];
    int[][] cur = new int[2][K+1];

        for(int ind=n;ind>=0;ind--){
            for(int buy=0;buy<=1;buy++){
                for(int k=K;k>=0;k--){
                    //this BC is imp if you want to remove this start loop 
                    //of ind from n-1 amd k to K-1 see func2 that is also accepted
                        if (ind == n||k==K) {
                            cur[buy][k]= 0;
                            continue;
                        }
                        int profit = 0;

                        if (buy == 0) { 
                            profit = Math.max(ahead [0][k]
                            , (-1)*arr[ind] + ahead[1][k]);
                        }

                                            
                        if (buy == 1) { 
                            profit = Math.max(ahead [1][k]
                            , arr[ind] +ahead [0][k+1]);
                        }

                      cur[buy][k] = profit;  
                }
            }
            ahead=cur;
        }

        return cur[0][0];
    }

private int func2(int n, int[] arr, int[][][] dp,int K) {

     int[][] ahead = new int[2][K+1];
    int[][] cur = new int[2][K+1];

        for(int ind=n-1;ind>=0;ind--){
            for(int buy=0;buy<=1;buy++){
                for(int k=K-1;k>=0;k--){
                   
                        int profit = 0;

                        if (buy == 0) { 
                            profit = Math.max(ahead [0][k]
                            , (-1)*arr[ind] + ahead[1][k]);
                        }

                                            
                        if (buy == 1) { 
                            profit = Math.max(ahead [1][k]
                            , arr[ind] +ahead [0][k+1]);
                        }

                      cur[buy][k] = profit;  
                }
            }
            ahead=cur;
        }

        return cur[0][0];
    }


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

