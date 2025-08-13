#include <bits/stdc++.h>
using namespace std;

class Solution{
private:
    //Function to find the maximum profit earned using recursion
    int func(int ind, int buy, int n, vector<int> &arr) {
        if (ind == n) {
            return 0;
        }

        int profit = 0;
        

        if (buy == 0) { 
            profit = max(0 + func(ind + 1, 0, n, arr), (-1)*arr[ind] + func(ind + 1, 1, n, arr));
        }
        

        if (buy == 1) { 
            profit = max(0 + func(ind + 1, 1, n, arr), arr[ind] + func(ind + 1, 0, n, arr));
        }

        return profit;
    }
public:
    //Function to calculate the maximum profit earned 
    int stockBuySell(vector<int> &arr, int n) {
        if (n == 0) 
            return 0;
        int ans = func(0, 0, n, arr);

        return ans;
    }
};
int main() {
    int n = 6;
    vector<int> arr = {7, 1, 5, 3, 6, 4};
    Solution sol;
    cout << "The maximum profit that can be generated is " << sol.stockBuySell(arr, n);

    return 0;
}


