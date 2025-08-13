#include <bits/stdc++.h>
using namespace std;

class Solution{
private:
    //Function to find the maximum profit earned using memoization
    int func(int ind, int buy, int cap, int n, vector<int> &arr, vector<vector<vector<int>>>& dp) {
        // Base case 
        if (ind == n || cap == 0) {
            return 0;
        }
        /* If the result for this state has 
        already been calculated, return it*/
        if (dp[ind][buy][cap] != -1) {
            return dp[ind][buy][cap];
        }
        int profit = 0;
        
        // We can buy the stock
        if (buy == 0) { 
            profit = max(0 + func(ind + 1, 0, cap, n, arr, dp), (-1)*arr[ind] + func(ind + 1, 1, cap, n, arr, dp));
        }
        
        //We can sell the stock
        if (buy == 1) { 
            profit = max(0 + func(ind + 1, 1, cap, n, arr, dp), arr[ind] + func(ind + 1, 0, cap-1, n, arr, dp));
        }

        /* Store the value in dp array and
        return the calculated profit */
        return dp[ind][buy][cap] = profit;
    }
public:
    //Function to calculate the maximum profit earned 
    int stockBuySell(vector<int> &arr, int n, int k) {
        if (n == 0) 
            return 0;
            
        // Initialize a DP table to memoize results
        vector<vector<vector<int>>> dp(n, vector<vector<int>>(2, vector<int>(k+1, -1)));

        int ans = func(0, 0, k, n, arr, dp);
        
        //Return the maximum profit
        return ans;
    }
};
int main() {
    int n = 8;
    vector<int> arr = {3, 3, 5, 0, 0, 3, 1, 4};
    int k = 3;
    
    //Create an instance of Solution class
    Solution sol;

    // Call the stockBuySell function and print the result
    cout << "The maximum profit that can be generated is " << sol.stockBuySell(arr, n, k);

    return 0;
}


