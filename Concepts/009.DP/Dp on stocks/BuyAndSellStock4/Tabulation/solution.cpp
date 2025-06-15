#include <bits/stdc++.h>
using namespace std;

class Solution {
private:
    //Function to find the maximum profit using tabulation
    int func(vector<int>& arr, int n, int k) {

        vector<vector<vector<int>>> dp(n + 1, vector<vector<int>>(2, vector<int>(k+1, 0)));
        for (int ind = n - 1; ind >= 0; ind--) {
            
            for (int buy = 0; buy <= 1; buy++) {
                
                for (int cap = 1; cap <= k; cap++) {
                    
                    // We can buy the stock
                    if (buy == 0) { 
                        dp[ind][buy][cap] = max(0 + dp[ind + 1][0][cap],
                                               (-1)*arr[ind] + dp[ind + 1][1][cap]);
                    }
                    // We can sell the stock
                    if (buy == 1) { 
                        dp[ind][buy][cap] = max(0 + dp[ind + 1][1][cap],
                                               arr[ind] + dp[ind + 1][0][cap - 1]);
                    }
                }
            }
        }
        return dp[0][0][k];
    }
public:
    //Function to find the maximum profit
    int stockBuySell(vector<int> &arr, int n, int k){
        //Return the answer
        return func(arr, n, k);
    }
};

int main() {
    vector<int> prices = {3, 3, 5, 0, 0, 3, 1, 4};
    int n = prices.size();
    int k = 3;
    Solution sol; 

    cout << "The maximum profit that can be generated is " << sol.stockBuySell(prices, n, k) << endl;
    //Output:8
    return 0;
}
