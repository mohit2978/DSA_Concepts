![alt text](<Kmp algo_250701_234032_1.jpg>) 
![alt text](<Kmp algo_250701_234032_2.jpg>)
 ![alt text](<Kmp algo_250701_234032_3.jpg>)
  ![alt text](<Kmp algo_250701_234032_4.jpg>) 
  ![alt text](<Kmp algo_250701_234032_5.jpg>) 
  ![alt text](<Kmp algo_250701_234032_6.jpg>)
   ![alt text](<Kmp algo_250701_234032_7.jpg>)
    ![alt text](<Kmp algo_250701_234032_8.jpg>) 
    ![alt text](<Kmp algo_250701_234032_9.jpg>)
     ![alt text](<Kmp algo_250701_234032_10.jpg>)
      ![alt text](<Kmp algo_250701_234032_11.jpg>) 
      ![alt text](<Kmp algo_250701_234032_12.jpg>)

## Cpp code

```cpp
#include <bits/stdc++.h>
using namespace std;

class Solution{
        void computeLPS(vector<int>&lps,string &s){
             int i=1;
             int j=0;
             while(i<s.size()){
                if(s[i]==s[j]){
                    lps[i]=j+1;
                    i++;
                    j++;
                }else{
                    while(j!=0 && s[i]!=s[j]){
                        j=lps[j-1];
                    }
                    if(s[i]==s[j]){
                        lps[i]=j+1;
                        j++;
                    }
                    i++;
                }
             }
        }
    public:
        vector <int> search(string pat, string txt){
         string s=pat +"$"+txt;
         int m=pat.size();
         int n=txt.size();
         vector<int>lps(s.size(),0);
         computeLPS(lps,s);
         vector<int> ans;
         for(int i=m+1;i<lps.size();i++){
            if(lps[i]==m){
                ans.push_back(i-2*m);
            }
         }
         return ans;
        }
};

```
---

### Java 

```java

import java.util.*;

class Solution {
    // Compute the Longest prefix suffix array for the combined string
    private int[] computeLPS(String s) {
        int n = s.length(); // size of string

        // To store the longest prefix suffix
        int[] LPS = new int[n];

        int i = 1, j = 0;

        // Iterate on the string
        while (i < n) {
            // If the character matches
            if (s.charAt(i) == s.charAt(j)) {
                LPS[i] = j + 1;
                i++;
                j++;
            }

            // Otherwise
            else {
                // Trace back j pointer till it does not match
                while (j > 0 && s.charAt(i) != s.charAt(j)) {
                    j = LPS[j - 1];
                }

                // If a match is found
                if (s.charAt(i) == s.charAt(j)) {
                    LPS[i] = j + 1;
                    j++;
                }
                i += 1;
            }
        }

        return LPS; // Return the computed LPS array
    }

    // Function to find all indices of pattern in text
    public List<Integer> search(String pattern, String text) {
        String s = pattern + '$' + text; // Combined string
        int[] LPS = computeLPS(s);
        int n = text.length(), m = pattern.length();
        List<Integer> ans = new ArrayList<>();
        for (int i = m + 1; i < s.length(); i++) {
            if (LPS[i] == m) ans.add(i - 2 * m);
        }

        return ans;
    }
}

class Main {
    public static void main(String[] args) {
        String text = "xyzabxyzabxyz";
        String pattern = "xyz";

        // Creating an instance of the solution class
        Solution sol = new Solution();

        // Function call to find all indices of pattern in text
        List<Integer> ans = sol.search(pattern, text);

        for (int ind : ans) System.out.print(ind + " ");
    }
}

```