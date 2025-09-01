# Notes

![alt text](RabinKarp_250620_195849_1.jpg) 
![alt text](RabinKarp_250620_195849_2.jpg) 
![alt text](RabinKarp_250620_195849_3.jpg)

```java

class Solution {
    public List<Integer> search(String pat, String txt) {
        int m=txt.length();
        int n=pat.length();

        int p=7;
        int mod=101;

        int txtHash=0;
        int patHash=0;
        
        int pRight=1;
        for(int i=0;i<n;i++){
            txtHash=(txtHash+((txt.charAt(i)-'a'+1)*pRight)%mod)%mod;
            patHash=(patHash+((pat.charAt(i)-'a'+1)*pRight)%mod)%mod;
            pRight=(pRight*p)%mod;
        }
        List<Integer> ans = new ArrayList<>();
        int pLeft=1;

        for(int i=0;i<=m-n;i++){
            if(txtHash==patHash){
                if(txt.substring(i,i+n).equals(pat))
                    ans.add(i);
            }

            if(i<m-n){//need to put else in 2ns statement i+n will be out of bound
                    
                txtHash=(txtHash-((txt.charAt(i)-'a'+1)*pLeft)%mod+mod)%mod;

                txtHash=(txtHash+((txt.charAt(i+n)-'a'+1)*pRight)%mod)%mod;
                patHash=(patHash*p)%mod;

                pRight=(pRight*p)%mod;
                pLeft=(pLeft*p)%mod;
            }
        }
        return ans;

    }
}

```

## Cpp code

```cpp

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
```