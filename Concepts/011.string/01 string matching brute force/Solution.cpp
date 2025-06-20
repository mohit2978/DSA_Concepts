#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    // Function to find the starting index of all occurrences of pattern in text
    vector<int> search(string pat, string txt) {
        int n = pat.length();
        int m = txt.length();
        
   
        vector<int> ans;
        
        for(int i=0; i <= m-n; i++) {
            bool flag = true;
            
            // Check for every character in pattern
            for(int j=0; j < n; j++) {
                
                // If characters does not match
                if(txt[i+j] != pat[j]) {
                    flag = false; // Set the flag as false
                    break;
                }
            }
            
            if(flag) ans.push_back(i);
        }
        
        return ans; // Return the stored result
    } 
};

int main(){
    string txt = "ababcabcababc";
    string pat = "abc";
    
    
    Solution sol; 
    

    vector<int> ans = sol.search(pat, txt);

    cout << "The starting indices of all occureneces of "
         << pat << " in " << txt << " are: ";
    for(auto it : ans) cout << it << " ";
    // The starting indices of all occureneces of abc in ababcabcababc are: 2 5 10 
    return 0;
}

/*
Complexity Analysis:
Time Complexity: O((M-N)*N) 
The outer loop iterates (M-N+1) times. For each position, the inner loop
 (the character-by-character comparison between the pattern and text) takes O(N) time in the worst case. taking overall O(M*N) time.

Space Complexity: O(K), because the code uses a constant space and the output list requires O(K) space where K is the number of times the pattern appears in the text.
*/