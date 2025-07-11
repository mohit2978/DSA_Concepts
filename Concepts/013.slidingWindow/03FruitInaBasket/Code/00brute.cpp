#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int totalFruits(vector<int>& fruits) {
        int n = fruits.size();  
        int maxLen = 0;  
        for (int i = 0; i < n; i++) {
            unordered_set<int> set;  
           
            for (int j = i; j < n; j++) {
                set.insert(fruits[j]);  
                if (set.size() <= 2) {
                    int len = j - i + 1;
                    maxLen = max(maxLen, len);
                } else break;
            }
        }
        return maxLen;
    }
};

int main() {
    vector<int> input = {3, 3, 3, 1, 2, 1, 1, 2, 3, 3, 4};  
    
    // Create an instance of Solution class
    Solution sol;
    
    int length = sol.totalFruits(input);
    
    // Print the result
    cout << "Maximum fruits in the basket is: " << length << endl;
    
    return 0;
}