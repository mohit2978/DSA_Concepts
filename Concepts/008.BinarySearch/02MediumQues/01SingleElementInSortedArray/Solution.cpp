#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
  
    int singleNonDuplicate(vector<int>& nums) {
        int n = nums.size(); 
        
  
        if (n == 1) return nums[0];


        for (int i = 0; i < n; i++) {
          
            if (i == 0) {
                if (nums[i] != nums[i + 1])
                    return nums[i];
            }
    
            else if (i == n - 1) {
                if (nums[i] != nums[i - 1])
                    return nums[i];
            }
      
            else {
                if (nums[i] != nums[i - 1] && nums[i] != nums[i + 1])
                    return nums[i];
            }
        }

     
        return -1;
    }
};

int main() {
    vector<int> nums = {1, 1, 2, 2, 3, 3, 4};
    
    // Create an object of the Solution class.
    Solution sol;
    
    int ans = sol.singleNonDuplicate(nums);
    
    // Print the result.
    cout << "The single element is: " << ans << "\n";
    
    return 0;
}
