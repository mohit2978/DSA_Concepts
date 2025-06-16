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