# Notes
 
 ![alt text](<004variable size sliding window-map_240508_003646(8).jpg>)
  ![alt text](<004variable size sliding window-map_240508_003646(9).jpg>) 
  ![alt text](<004variable size sliding window-map_240508_003646(10).jpg>) 
  ![alt text](<004variable size sliding window-map_240508_003646(11).jpg>) 
  ![alt text](<004variable size sliding window-map_240508_003646(12).jpg>) 
  ![alt text](<004variable size sliding window-map_240508_003646(13).jpg>) ![alt text](<004variable size sliding window-map_240508_003646(14).jpg>)
  
  
  
  
![alt text](<004variable size sliding window-map_240508_003646(15).jpg>)

# Q Longest repaeating

![alt text](<02 longest reapeating_250711_225039.jpg>)

## Brute

```cpp
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

```

### Wrong code

```cpp

#include <bits/stdc++.h>
using namespace std;

class Solution{
  public:
    int longestNonRepeatingSubstring(string& s){
        unordered_map<char,int>mp;
        int n=s.size();
        int res=0;
        int l=0;
        for(int r=0;r<n;r++){
           if(mp.find(s[r])==mp.end()) mp[s[r]]++;
           else {
            while(s[l]!=s[r]){
                mp[s[l]]--;
                l++;
            }
           }
           res=max(res,r-l+1);
        }
        return res;
    }
};
```

### Correct optimal

```cpp
#include <bits/stdc++.h>
using namespace std;

class Solution{
  public:
    int longestNonRepeatingSubstring(string& s){
        unordered_map<char,int>mp;
        int n=s.size();
        int res=0;
        int l=0;
        for(int r=0;r<n;r++){
            mp[s[r]]++;
            while(mp[s[r]]>1){
                mp[s[l]]--;
                l++;
            }
           res=max(res,r-l+1);
        }
        return res;
    }
};
```

 
  
  ![alt text](<004variable size sliding window-map_240508_003646(22).jpg>) ![alt text](<004variable size sliding window-map_240508_003646(23).jpg>) ![alt text](<004variable size sliding window-map_240508_003646(24).jpg>) ![alt text](<004variable size sliding window-map_240508_003646(25).jpg>) ![alt text](<004variable size sliding window-map_240508_003646(26).jpg>) ![alt text](<004variable size sliding window-map_240508_003646(27).jpg>) ![alt text](<004variable size sliding window-map_240508_003646(28).jpg>) ![alt text](<004variable size sliding window-map_240508_003646(29).jpg>) ![alt text](<004variable size sliding window-map_240508_003646(30).jpg>) ![alt text](<004variable size sliding window-map_240508_003646(31).jpg>)








![alt text](<004variable size sliding window-map_240508_003646(32).jpg>) ![alt text](<004variable size sliding window-map_240508_003646(33).jpg>) ![alt text](<004variable size sliding window-map_240508_003646(34).jpg>) ![alt text](<004variable size sliding window-map_240508_003646(35).jpg>)


