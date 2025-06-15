#include <bits/stdc++.h>
using namespace std;

class Solution {
private:
    //Another way
    int func(vector<int>& arr, int n) {

        vector<vector<int>> ahead(2, vector<int>(3, 0));
        vector<vector<int>> cur(2, vector<int>(3, 0));

        // Iterate backwards through the prices array
        for (int ind = n - 1; ind >= 0; ind--) {
            
            // buy can be 0 (buying) or 1 (selling)
            for (int buy = 0; buy <= 1; buy++) {
                
                /* cap represents the number of 
                transactions completed (can be 1 or 2)*/
                for (int cap = 1; cap <= 2; cap++) {
                    // We can buy the stock
                    if (buy == 0) { 
                        cur[buy][cap] = max(0 + ahead[0][cap], 
                                            -arr[ind] + ahead[1][cap]);
                    }
                    // We can sell the stock
                    if (buy == 1) { 
                        cur[buy][cap] = max(0 + ahead[1][cap],
                                            arr[ind] + ahead[0][cap - 1]);
                    }
                }
            }
            /* Update the ahead state with the
            current state for the next iteration
            very imp*/
            ahead = cur;
        }

        /* Return the maximum profit after completing
        2 transactions starting from index 0.*/
        return ahead[0][2];
    }
public:
    //Function to find out maximum profit
    int stockBuySell(vector<int> &arr, int n){
        //Return the answer
        return func(arr, n);
    }
};

int main() {
    vector<int> prices = {3, 3, 5, 0, 0, 3, 1, 4};
    int n = prices.size();

    Solution sol;
    cout << "The maximum profit that can be generated is " << sol.stockBuySell(prices, n) << endl;

    return 0;
}
