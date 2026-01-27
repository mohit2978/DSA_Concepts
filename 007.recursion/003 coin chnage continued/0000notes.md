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
# Combination Sum III

**Difficulty:** Medium  
**Category:** Recursion & Backtracking  

---

### Problem Statement

Determine all possible sets of **k** numbers that can be added together to equal **n**, while meeting the following requirements:

1.  Only the numerals **1 through 9** can be used.
2.  Each number can be used **at most once** in a single combination.

Return a list of every feasible combination. The combinations can be returned in any order, but the final list must not contain duplicate combinations.

---

### Examples

#### Example 1
**Input:** `k = 3`, `n = 7`  
**Output:** `[[1, 2, 4]]`  
**Explanation:** 1 + 2 + 4 = 7. There are no other valid combinations using 3 numbers from 1-9.

#### Example 2
**Input:** `k = 3`, `n = 9`  
**Output:** `[[1, 2, 6], [1, 3, 5], [2, 3, 4]]`  
**Explanation:** - 1 + 2 + 6 = 9  
- 1 + 3 + 5 = 9  
- 2 + 3 + 4 = 9  
There are no other valid combinations.

---

### Constraints

* `2 <= k <= 9`
* `1 <= n <= 60`

---

```cpp

class Solution {
    void solve(vector<int>& arr,int i ,vector<vector<int>>& res,vector<int>& tres,int tar,int lim){
        if(i==arr.size() || lim==0 ){
            if(tar==0 && lim==0){
                res.push_back(tres);
            }
            return;
        }
        if(tar>=arr[i]) {
            tres.push_back(arr[i]);
            solve(arr,i+1,res,tres,tar-arr[i],lim-1);
            tres.pop_back();
        }
        solve(arr,i+1,res,tres,tar,lim);
    }
public:
    vector<vector<int> > combinationSum3(int k, int n) {
        vector<int>cand={1,2,3,4,5,6,7,8,9};
    	vector<vector<int>>res;
        vector<int> tres;
        solve(cand,0,res,tres,n,k);
        return res;
    }
};
```

Complexity Review:

Time: $O(2^9 \times k)$ — We are essentially looking at all subsets of the numbers 1–9.

Space: $O(k)$ — The depth of the recursion tree is at most 9, and the tres vector stores $k$ elements.


```cpp
#include <bits/stdc++.h>
using namespace std;

class Solution {
private: 
    void func(int sum, int last, vector<int> &nums, int k, vector<vector<int>> &ans) {
        if(sum == 0 && nums.size() == k) {
            ans.push_back(nums);
            return; 
        }
        
        if(sum <= 0 || nums.size() > k) return; 

        for(int i = last; i <= 9; i++) {
            if(i <= sum) {
                nums.push_back(i); 
                func(sum - i, i + 1, nums, k, ans); 
                nums.pop_back(); 
            } else {
                break;
            }
        }
    } 
public:
    vector<vector<int>> combinationSum3(int k, int n) {
        vector<vector<int>> ans; 
        vector<int> nums; 
        func(n, 1, nums, k, ans);
        return ans; 
    }
};

int main() {
    Solution sol;
    int k = 3;
    int n = 7;
    vector<vector<int>> result = sol.combinationSum3(k, n);

    for (const auto& combination : result) {
        for (int num : combination) {
            cout << num << " ";
        }
        cout << endl;
    }

    return 0;
}
```

Same ques but another way!!! we have seen already two ways to do same type of ques!! 

It has same tc and sc as of above but no vector explicity here ,there also we do not need any explicit vector of 1 to 9
