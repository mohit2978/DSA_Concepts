#include<bits/stdc++.h>
using namespace std;

class Solution {
private:

    int func(int ind, int sum, vector<int> &nums) {

        if (sum == 0) return 1;

        if (sum < 0 || ind == nums.size()) return 0;
   
        return func(ind + 1, sum - nums[ind], nums) + func(ind + 1, sum, nums);
    }

public:

    int countSubsequenceWithTargetSum(vector<int>& nums, int target) {
        return func(0, target, nums);
    }
};

int main() {
    Solution sol;
    vector<int> nums = {1, 2, 3, 4, 5};
    int target = 5;
    cout << "Number of subsequences with target sum " << target << ": "
         << sol.countSubsequenceWithTargetSum(nums, target) << endl;
    return 0;
}
