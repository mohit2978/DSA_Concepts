#include <bits/stdc++.h>
using namespace std;

class Solution {
private:
  
    bool func(int ind, int sum, std::vector<int> &nums) {

        if (ind == nums.size()) {
            return sum == 0;
        }
    
        return func(ind + 1, sum - nums[ind], nums) | func(ind + 1, sum, nums);//see difference in  | in java and cpp
    }

public:

    bool checkSubsequenceSum(std::vector<int>& nums, int target) {
        return func(0, target, nums)
    }
};

// Main function to test the solution
int main() {
    Solution sol;
    std::vector<int> nums = {1, 2, 3, 4};
    int target = 5;
    std::cout << sol.checkSubsequenceSum(nums, target); // Expected output: true
    return 0;
}
