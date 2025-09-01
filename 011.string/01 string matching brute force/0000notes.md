# Notes

### Cpp

```cpp

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

```
---

### Java


```java
import java.util.*;

public class Solution {
    // Function to find the starting index of all occurrences of pattern in text
    public List<Integer> search(String pat, String txt) {
        int n = pat.length();
        int m = txt.length();

        // List to store the result
        List<Integer> ans = new ArrayList<>();

        // Traverse the text string
        for (int i = 0; i <= m - n; i++) {
            boolean flag = true;

            // Check for every character in pattern
            for (int j = 0; j < n; j++) {

                // If characters does not match
                if (txt.charAt(i + j) != pat.charAt(j)) {
                    flag = false; // Set the flag as false
                    break;
                }
            }

            // if the pattern is found, store the index
            if (flag) ans.add(i);
        }

        return ans; // Return the stored result
    }
        public static void main(String[] args) {
        String txt = "ababcabcababc";
        String pat = "abc";

        // Creating an instance of Solution class
        Solution sol = new Solution();

        /* Function call to find the starting index
           of all occurrences of pattern in text */
        List<Integer> ans = sol.search(pat, txt);

        // Output
        System.out.print("The starting indices of all occurrences of " + pat + " in " + txt + " are: ");
        for (int it : ans) System.out.print(it + " ");
    }
}

/* 
The starting indices of all occurrences of abc in ababcabcababc are: 2 5 10 
*/

/*
Complexity Analysis:
Time Complexity: O((M-N)*N) 
The outer loop iterates (M-N+1) times. For each position, the inner loop
 (the character-by-character comparison between the pattern and text) takes O(N) time in the worst case. taking overall O(M*N) time.

Space Complexity: O(K), because the code uses a constant space and the output list requires O(K) space where K is the number of times the pattern appears in the text.
*/
```

