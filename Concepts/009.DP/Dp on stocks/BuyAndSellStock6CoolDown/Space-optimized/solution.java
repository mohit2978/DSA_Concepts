class Solution {
    
    private int func( int n, int[] arr,int k) {
        int[][] ahead = new int[2][k+1];
        int[][] cur = new int[2][k+1];

        for(int ind =n;ind>=0;ind--){
            for(int buy=0;buy<=1;buy++){
                for(int coolDown=0;coolDown<=k;coolDown++){
                        if (ind == n ){
                            cur[buy][coolDown]= 0;
                            continue;
                        }
                        int profit = 0;

                        if (buy == 0 && coolDown==0) { 
                            profit = Math.max( ahead[0][coolDown]// dont buy
                                , (-1)*arr[ind] + ahead[1][coolDown]);//buy
                        }
                            
                        if(coolDown!=0){
                            profit =ahead[0][coolDown-1];
                        }

                        if (buy == 1 && coolDown==0) { 
                            profit = Math.max(ahead[1][coolDown]// dont sell
                                , arr[ind] +ahead[0][coolDown+1]);//sell so increase cooldown
                         }

                        cur[buy][coolDown] = profit;
                }
            }
            ahead=cur;
        }
        return cur[0][0];

    }

    // Function to calculate the maximum profit earned 
    public int stockBuySell(int[] arr, int n) {
        if (n == 0) 
            return 0;
        int ans = func( n, arr,1);
        return ans;
    }
    public int maxProfit(int[] prices) {
        return stockBuySell(prices,prices.length);
    }
}

//Don't know what's wrong here 

//[1,2,3,0,2]
//output-4
//expected-3