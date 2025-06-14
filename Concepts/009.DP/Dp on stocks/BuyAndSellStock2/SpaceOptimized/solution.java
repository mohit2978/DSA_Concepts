class Solution {

    private int func( int n, int[] arr) {
        int[] ahead = new int[2];
        int[] cur = new int[2];
        for(int ind=n;ind>=0;ind--){
            for(int buy=0;buy<=1;buy++){
                   if (ind == n) {
                        ahead[buy]=0;
                        continue;
                    }

                    int profit = 0;

                    if (buy == 0) { 
                        profit = Math.max(ahead [0]
                        , (-1)*arr[ind] + ahead [1]);
                    }
                    
                    if (buy == 1) { 
                        profit = Math.max(ahead[1]
                        , arr[ind] +ahead[0]);
                    }

                 cur[buy] = profit;
            }
            ahead=cur;
        }
        return cur[0];
    }
    /**
     * when we do ahead=cur refernce to old ahead is lost 
     * so now ahead and curr refect to same array after ind=n so we 
     * are not updaing cur in if condition we putting variable profit and 
     * updating it afterwards
     */
    public int stockBuySell(int[] arr, int n) {
        if (n == 0) 
            return 0;
        int ans = func( n, arr);
        return ans;
    }
}
