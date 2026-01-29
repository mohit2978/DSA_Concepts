# Power set 

This can be acheieved by recusrion but let us see this way too

### Cpp code

```cpp
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:

    vector<vector<int>> powerSet(vector<int>& nums) {
        

        int n = nums.size();
    
        vector<vector<int>> ans;

        int count = (1 << n);
        

        for(int val = 0; val < count; val++) {
            

            vector<int> subset;
            
            for(int i=0; i < n; i++) {
                if(val & (1 << i)) {//In cpp this works but in java you need to put !=0
                    subset.push_back(nums[i]);
                }
            }

            ans.push_back(subset);
        }

        return ans;
    }
};
/*
In Java, the & operator performs a bitwise AND, but the result is still an int. Java expects a boolean expression inside an if statement, and:

i & (1 << j) returns an int, not a boolean

So this is a compilation error

so use if ((i & (1 << j)) != 0)  in java

In C/C++, it's fine to use just if (i & (1 << j)) because non-zero integers are treated as true, but Java is stricter and requires explicit boolean expressions.
*/

int main() {
    vector<int> nums = {1, 2, 3};

    Solution sol; 

    vector<vector<int>> ans = sol.powerSet(nums);
    
    sort(ans.begin(), ans.end());

    cout << "The power set for the given array is: " << endl;
    
    for(int i=0; i < ans.size(); i++) {
        for(int j=0; j < ans[i].size(); j++) {
            cout << ans[i][j] << " ";        
        }
        cout << endl;
    }
    
    return 0;
}

/*
Output:
1 
1 2 
1 2 3 
1 3 
2 
2 3 
3 
*/
```
### Java code

```java

import java.util.*;
class Solution {
    public List<List<Integer>> powerSet(int[] nums) {
        int n=nums.length;
        List<List<Integer>> res = new ArrayList<>();
        int limit=(1<<n);//2 to power n no of susbsets

        for(int i=0;i<limit;i++){//iterating over 0 to 2^n
            List<Integer>subset=new ArrayList<>();
            for(int j=0;j<n;j++){//iterating over n bits as n bits for 2^n
                
                if((i &(1<<j))!=0){
                    subset.add(nums[j]);
                }
            }
            res.add(subset);
        }
     return res;
    }
    public static void main(String[] args) {
        int[] nums = {1,2,3,4};
        Solution sol = new Solution(); 
        List<List<Integer>>res=sol.powerSet(nums);
        System.out.println(res);
/*
Output:
[[], [1], [2], [1, 2], [3], [1, 3], [2, 3], [1, 2, 3], [4], [1, 4], [2, 4], [1, 2, 4], [3, 4], [1, 3, 4], [2, 3, 4], [1, 2, 3, 4]]
*/

    }
 
}
/*
tc->(n*(2^n)) two loops outer one of 2^n and inner one for n
sc->O((2^n)*n) 2^n subset and each size on avg we take as n for worst case
*/
/*
{1,2,3} n=3 so no of elements in set =2^n=8
000={}
001={3}
010={2}
011={2,3}
100={1}
101={1,3}
110={1,2}
111={1,2,3}

i loop iterates over 0 to <2^n

j loop over n bits as for subset of n number we need n bits to represent number between 
0 to 2^n

if bit is 1 then add that number else not
*/
```
