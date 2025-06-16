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
            cur=new int[2][k+1];//need to add this else it will not work!!
        }
        return ahead[0][0];

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

/*
            ahead=cur;
            cur=new int[2][k+1];/

            Here need to create a new array each time!!
            In Buy and Sell2 optimized one there was no need
            see when cur and head points to same array
            in there if buy=0

            cur[0]=ahead[0]
            then buy=1 
            cur[1]=ahead[1];
            No problem

            now see buy=0
            cur[0]=-arr[ind]+ahead[1];
            this is cur value which is same as ahead[0] now what if
            cur[1]=arr[ind] +ahead[0];
            but ahead[0] is being updated already

*/
