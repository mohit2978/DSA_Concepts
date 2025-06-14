class Solution {
   /*
   Given an array arr of n integers, where arr[i] represents price of the stock on the ith day. Determine the maximum profit achievable by buying and selling the stock at most once. 
    The stock should be purchased before selling it, and both actions cannot occur on the same day.
   */
    public int stockBuySell1(int[] arr, int n) {
        int maxProfit = 0;
        int mini = arr[0]; 
        for (int i = 1; i < n; i++) {
            int curProfit = arr[i] - mini; 
            maxProfit = Math.max(maxProfit, curProfit); 
            mini = Math.min(mini, arr[i]); 
        }
        return maxProfit; 
    }
}