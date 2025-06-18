#include <bits/stdc++.h>
using namespace std;
/*
Time Complexity: O(2N), where N is the size of the given array.
Each element has two possibilities (include or exclude), resulting in 2N combinations.

Space Complexity: O(N)
The recursion stack space will take O(N). Note that if you consider the space used to return the output that the space complexity can go up to O(2N).
*/
class Solution {
private: 
    // Helper function to calculate subset sums
    void func(int ind, int sum, vector<int> &nums, vector<int> &ans) {

        if(ind == nums.size()) {
 
            ans.push_back(sum);
            return;
        }

        func(ind + 1, sum + nums[ind], nums, ans); 

        func(ind + 1, sum, nums, ans); 
    }

public:

    vector<int> subsetSums(vector<int>& nums) {
        vector<int> ans; 
 
        func(0, 0, nums, ans);
        return ans;
    }
};

int main() {

    vector<int> nums = {1, 2, 3};
    

    Solution sol;

    vector<int> result = sol.subsetSums(nums);
    

    cout << "Subset sums are: ";
    for (int sum : result) {
        cout << sum << " ";
    }
    cout << endl;

    return 0;
}
