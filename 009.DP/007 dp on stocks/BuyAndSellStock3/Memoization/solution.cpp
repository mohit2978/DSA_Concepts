#include <bits/stdc++.h>
using namespace std;

class Solution{
private:
    int func(int ind, int buy, int cap, int n, vector<int> &arr, vector<vector<vector<int>>>& dp) {
        // Base case 
        if (ind == n || cap == 0) {
            return 0;
        }

        if (dp[ind][buy][cap] != -1) {
            return dp[ind][buy][cap];
        }
        int profit = 0;
        

        if (buy == 0) { 
            profit = max(0 + func(ind + 1, 0, cap, n, arr, dp), (-1)*arr[ind] + func(ind + 1, 1, cap, n, arr, dp));
        }

        if (buy == 1) { 
            profit = max(0 + func(ind + 1, 1, cap, n, arr, dp), arr[ind] + func(ind + 1, 0, cap-1, n, arr, dp));
        }

        return dp[ind][buy][cap] = profit;
    }
public:
    //Function to calculate the maximum profit earned 
    int stockBuySell(vector<int> &arr, int n) {
        if (n == 0) 
            return 0;

        vector<vector<vector<int>>> dp(n, vector<vector<int>>(2, vector<int>(3, -1)));

        int ans = func(0, 0, 2, n, arr, dp);

        return ans;
    }
};
int main() {
    int n = 8;
    vector<int> arr = {3, 3, 5, 0, 0, 3, 1, 4};

    Solution sol;
    cout << "The maximum profit that can be generated is " << sol.stockBuySell(arr, n);

    return 0;
}


