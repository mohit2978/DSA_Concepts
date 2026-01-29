![alt text](<03 fruit in a basket_250711_232853_1.jpg>) 

## Brute 
```cpp
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
```

![alt text](<03 fruit in a basket_250711_232853_2.jpg>) 
![alt text](<03 fruit in a basket_250711_232853_3.jpg>)

## Better
```cpp
#include <bits/stdc++.h>
using namespace std;

class Solution{
  public:
    int totalFruits(vector<int>& s){
        unordered_map<char,int>mp;
        int n=s.size();
        int res=0;
        int l=0;
        for(int r=0;r<n;r++){
            mp[s[r]]++;
            while(mp.size()>2){
                mp[s[l]]--;
                if(mp[s[l]]==0) mp.erase(s[l]);
                l++;
            }
           res=max(res,r-l+1);
        }
        return res;
    }
};
```

## Optimal

```cpp
#include <bits/stdc++.h>
using namespace std;
class Solution{
  public:
    int totalFruits(vector<int>& s){
        unordered_map<char,int>mp;
        int n=s.size();
        int res=0;
        int l=0;
        for(int r=0;r<n;r++){
            mp[s[r]]++;
            if(mp.size()>2){
                mp[s[l]]--;
                if(mp[s[l]]==0) mp.erase(s[l]);
                l++;
            }
           res=max(res,r-l+1);
        }
        return res;
    }
};
```