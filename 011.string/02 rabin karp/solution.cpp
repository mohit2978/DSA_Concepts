#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    // Function to find the starting index of all occurrences of pattern in text
    vector<int> search(string pat, string txt) {
        int n = pat.length();
        int m = txt.length();
        
        // Primes for Rabin karp algorithm
        int p = 7, mod = 101;
        
     
        int hashPat = 0, hashText = 0;
        
        int pRight = 1, pLeft = 1;
        
        // Computing the initial hash values
        for(int i=0; i < n; i++) {
            hashPat += ((pat[i]-'a'+1) * pRight) % mod;
            hashText += ((txt[i]-'a'+1) * pRight) % mod;
            pRight = (pRight * p) % mod;
        }
     
        vector<int> ans;
        
      
        for(int i=0; i <= m-n; i++) {
            
            // If the hash value matches
            if(hashPat == hashText) {
                // Add the index of the result if the substring matches
                if(txt.substr(i, n) == pat) ans.push_back(i);
            }
            
            // Updating the hash values
            hashText = (hashText - ((txt[i] - 'a'+1) * pLeft) % mod + mod) % mod;
            hashText = (hashText + ((txt[i+n] - 'a'+1) * pRight) % mod) % mod;
            hashPat = (hashPat * p) % mod;
            
            // Updating the prime multiples
            pLeft = (pLeft * p) % mod;
            pRight = (pRight * p) % mod;
        }
        
        return ans; 
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
    
    return 0;
}

/*
The starting indices of all occureneces of abc in ababcabcababc are: 2 5 10 
*/