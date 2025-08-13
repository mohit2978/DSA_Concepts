#include <bits/stdc++.h>
using namespace std;

class Solution {
private:
    // Compute the Longest prefix suffix array for the combined string
    vector<int> computeLPS(string s) {
        int n = s.size(); // size of string
        
        // To store the longest prefix suffix
        vector<int> LPS(n, 0);
        
        int i = 1, j = 0;
        
        // Iterate on the string
        while(i < n) {
            // If the character matches
            if(s[i] == s[j]) {
                LPS[i] = j+1;
                i++, j++;
            }
            
            // Otherwise
            else {
                // Trace back j pointer till it does not match
                while(j > 0 && s[i] != s[j]) {
                    j = LPS[j-1];
                }
                
                // If a match is found
                if(s[i] == s[j]) {
                    LPS[i] = j+1;
                    j++;
                }
                i += 1;
            }
        }
        
        return LPS; // Return the computed LPS array
    }
    
public:
    // Function to find all indices of pattern in text
    vector<int> search(string pattern, string text)   {
        string s = pattern + '$' + text; // Combined string
        
        // Function call to find the Z array for the combined string
        vector<int> LPS = computeLPS(s);
        
        // Length of pattern and text
        int n = text.size(), m = pattern.size();
        
        // To store the result
        vector<int> ans;
        
        // Iterate on the combined string after the delimiter
        for(int i = m+1; i < s.size(); i++) {
            if(LPS[i] == m) ans.push_back(i - 2*m);
        }
        
        return ans;
    }
};

int main() {
    string text = "xyzabxyzabxyz";
    string pattern = "xyz";
    
    // Creating an instance of the solution class
    Solution sol;
    
    // Function call to find all indices of pattern in text
    vector<int> ans = sol.search(pattern, text);
    
    for(auto ind : ans) cout << ind << " ";
    return 0;
}