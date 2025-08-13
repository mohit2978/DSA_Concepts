#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int longestNonRepeatingSubstring(string &s) {
        int n = s.size(); 
        int maxLen = 0;    
        for (int i = 0; i < n; i++) {

            vector<int> hash(256, 0);  
            
            for (int j = i; j < n; j++) {

                if (hash[s[j]] == 1) break;  
                hash[s[j]] = 1;
                int len = j - i + 1;
                maxLen = max(maxLen, len);
            }
        }
        
        // Return the maximum length
        return maxLen; 
    }
};

int main() {
    string input = "cadbzabcd";
    
    //Create an instance of Solution class
    Solution sol;
    
    int length = sol.longestNonRepeatingSubstring(input);
    
    //Print the result
    cout << "Length of longest substring without repeating characters: " << length << endl;
    
    return 0;
}
