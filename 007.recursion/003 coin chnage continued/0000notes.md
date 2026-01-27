# Notes
![alt text](<003 Coin change continued _231126_234039.jpg>)
![alt text](<003 Coin change continued _231126_234039(1).jpg>) ![alt text](<003 Coin change continued _231126_234039(2).jpg>) ![alt text](<003 Coin change continued _231126_234039(3).jpg>) ![alt text](<003 Coin change continued _231126_234039(4).jpg>) ![alt text](<003 Coin change continued _231126_234039(5).jpg>) ![alt text](<003 Coin change continued _231126_234039(6).jpg>) ![alt text](<003 Coin change continued _231126_234039(7).jpg>) ![alt text](<003 Coin change continued _231126_234039(8).jpg>) ![alt text](<003 Coin change continued _231126_234039(9).jpg>) ![alt text](<003 Coin change continued _231126_234039(10).jpg>) ![alt text](<003 Coin change continued _231126_234039(11).jpg>) ![alt text](<003 Coin change continued _231126_234039(12).jpg>) ![alt text](<003 Coin change continued _231126_234039(13).jpg>) ![alt text](<003 Coin change continued _231126_234039(14).jpg>) ![alt text](<003 Coin change continued _231126_234039(15).jpg>) ![alt text](<003 Coin change continued _231126_234039(16).jpg>) ![alt text](<003 Coin change continued _231126_234039(17).jpg>) ![alt text](<003 Coin change continued _231126_234039(18).jpg>) ![alt text](<003 Coin change continued _231126_234039(19).jpg>) ![alt text](<003 Coin change continued _231126_234039(20).jpg>) 

## Another good solution

```cpp

class Solution {
        void func(int ind, int sum, vector<int> &nums, 
              vector<int> &candidates, vector<vector<int>> &ans) {
        if(sum == 0) {
            ans.push_back(nums);
            return;
        }
        if(sum < 0 || ind == candidates.size()) return; 

        nums.push_back(candidates[ind]); 

        func(ind + 1, sum - candidates[ind], nums, candidates, ans); 
        nums.pop_back(); 
        for(int i = ind + 1; i < candidates.size(); i++) {
            if(candidates[i] != candidates[ind]) {
                func(i, sum, nums, candidates, ans); 
                break; 
            }
        }
    }
public:
    vector<vector<int> > combinationSum2(vector<int>& arr, int tar) {
        vector<vector<int>> ans; 
        vector<int> nums; 
        sort(arr.begin(), arr.end()); 
        func(0, tar, nums, arr, ans);

        return ans; 
    }
};
```

![alt text](<003 Coin change continued _231126_234039(21).jpg>) ![alt text](<003 Coin change continued _231126_234039(22).jpg>) ![alt text](<003 Coin change continued _231126_234039(23).jpg>) ![alt text](<003 Coin change continued _231126_234039(24).jpg>)

![alt text](<003 Coin change continued _231126_234039(25).jpg>) ![alt text](<003 Coin change continued _231126_234039(26).jpg>) ![alt text](<003 Coin change continued _231126_234039(27).jpg>) ![alt text](<003 Coin change continued _231126_234039(28).jpg>) ![alt text](<003 Coin change continued _231126_234039(29).jpg>) ![alt text](<003 Coin change continued _231126_234039(30).jpg>)