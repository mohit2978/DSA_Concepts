# Notes
Provided with a goal integer target and an array of unique integer candidates, provide a list of all possible combinations of candidates in which the selected numbers add up to the target. The combinations can be returned in any order.



A candidate may be selected from the pool an infinite number of times. There are two distinct combinations if the frequency of at least one of the selected figures differs.



The test cases are created so that, for the given input, there are fewer than 150 possible combinations that add up to the target.

If there is no possible subsequences then return empty vector.

Examples:
---
Input : candidates = [2, 3, 5, 4] , target = 7

Output : [ [2, 2, 3] , [3, 4] , [5, 2] ]

Explanation :

2 and 3 are candidates, and 2 + 2 + 3 = 7. Note that 2 can be used multiple times.

5 and 2 are candidates, and 5 + 2 = 7.

3 and 4 are candidates, and 3 + 4 = 7.

There are total three combinations.

---

Input : candidates = [2], target = 1

Output : []

Explanation : There is no way we can choose the candidates to sum up to target.

Constraints:
----
1 <= candidates.length <= 30
2 <= candidates[i] <= 40
All elements of candidates are distinct.
1 <= target <= 40

```cpp
class Solution {
    void solve(vector<int>& arr,int i ,vector<vector<int>>& res,vector<int>& tres,int tar){
        if(i==arr.size() || tar==0 ){
            if(tar==0){
                res.push_back(tres);
            }
            return;
        }
        if(tar>=arr[i]) {
            tres.push_back(arr[i]);
            solve(arr,i,res,tres,tar-arr[i]);
            tres.pop_back();
        }
        solve(arr,i+1,res,tres,tar);
    }
public:
    vector<vector<int>> combinationSum(vector<int>& cand, int tar) {
        vector<vector<int>>res;
        vector<int> tres;
        solve(cand,0,res,tres,tar);
        return res;

    }
};
```
>Note: Unlike java here no neeed of new array to push in res

Time Complexity:The time complexity is O(N^(T/M + 1)), where N is the number of candidates, T is the target value, and M is the minimum value among the candidates.

Space Complexity:The space complexity is O(T/M), where T is the target value, and M is the minimum value among the candidates. This is primarily due to the maximum depth of the recursion stack.