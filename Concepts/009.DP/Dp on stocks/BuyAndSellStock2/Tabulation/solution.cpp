
#include <bits/stdc++.h>
using namespace std;

class Solution{
private:
 
    int func(vector<int> &arr, int n) {

        vector<vector<int>> dp(n + 1, vector<int>(2, -1));
        dp[n][0] = dp[n][1] = 0;
        for (int ind = n - 1; ind >= 0; ind--) {
            for (int buy = 0; buy <= 1; buy++) {
                   int profit=0;
                if (buy == 0) { 
                    profit = max(0 + dp[ind + 1][0], (-1)*arr[ind] + dp[ind + 1][1]);
                }
            
                // We can sell the stock
                if (buy == 1) { 
                    profit = max(0 + dp[ind + 1][1], arr[ind] + dp[ind + 1][0]);
                }

                dp[ind][buy] = profit;
            }
        }

        /* The maximum profit is stored in
        dp[0][0] after all calculations not put max(dp[0][0],dp[0][1])
        as result be in 0,0 as buy kia nhi toh sell kaise kr doge*/
        return dp[0][0];
    }
public:

    int stockBuySell(vector<int> &arr, int n){
        //Return the maximum profit
        return func(arr, n);
    }
};
int main() {
    int n = 6;
    vector<int> arr = {7, 1, 5, 3, 6, 4};
    
    //Create an instance of Solution class
    Solution sol;

    // Call the getMaximumProfit function and print the result
    cout << "The maximum profit that can be generated is " << sol.stockBuySell(arr, n);

    return 0;
}