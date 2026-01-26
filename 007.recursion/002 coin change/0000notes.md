# Notes

![alt text](<002coin change_231126_233809.jpg>)

![alt text](<002coin change_231126_233809(1).jpg>) ![alt text](<002coin change_231126_233809(2).jpg>) ![alt text](<002coin change_231126_233809(3).jpg>) ![alt text](<002coin change_231126_233809(4).jpg>) ![alt text](<002coin change_231126_233809(5).jpg>) 

```java
/* package codechef; // don't place package name! */

import java.util.*;
import java.lang.*;
import java.io.*;

/* Name of the class has to be "Main" only if the class is public. */
class Codechef
{
        public static int coinChangePermutation_IN(int[] coins, int tar, String psf) {
        if (tar == 0) {
            System.out.println(psf);
            return 1;
        }

        int count = 0;
        for (int i = 0; i < coins.length; i++) {
            if (tar - coins[i] >= 0) {
                count += coinChangePermutation_IN(coins, tar - coins[i], psf + coins[i] + " ");
            }
        }

        return count;

    }

	public static void main (String[] args) throws java.lang.Exception
	{
		int[] coins = { 2, 3, 5, 7 };
        int tar = 10;
        coinChangePermutation_IN(coins,tar,"");

	}
}


/*
Output:
2 2 2 2 2 
2 2 3 3 
2 3 2 3 
2 3 3 2 
2 3 5 
2 5 3 
3 2 2 3 
3 2 3 2 
3 2 5 
3 3 2 2 
3 5 2 
3 7 
5 2 3 
5 3 2 
5 5 
7 3 
*/
```

![alt text](<002coin change_231126_233809(6).jpg>) ![alt text](<002coin change_231126_233809(7).jpg>) ![alt text](<002coin change_231126_233809(8).jpg>) ![alt text](<002coin change_231126_233809(9).jpg>) ![alt text](<002coin change_231126_233809(10).jpg>) ![alt text](<002coin change_231126_233809(11).jpg>)
![alt text](<002coin change_231126_233809(12).jpg>) ![alt text](<002coin change_231126_233809(13).jpg>) ![alt text](<002coin change_231126_233809(14).jpg>) ![alt text](<002coin change_231126_233809(15).jpg>) ![alt text](<002coin change_231126_233809(16).jpg>) ![alt text](<002coin change_231126_233809(17).jpg>) ![alt text](<002coin change_231126_233809(18).jpg>) ![alt text](<002coin change_231126_233809(19).jpg>) ![alt text](<002coin change_231126_233809(20).jpg>) ![alt text](<002coin change_231126_233809(21).jpg>) 

### All 4

#### Way-1

```java

    public static int coinChangePermutation_IN(int[] coins, int tar, String psf) {
        if (tar == 0) {
            System.out.println(psf);
            return 1;
        }

        int count = 0;
        for (int i = 0; i < coins.length; i++) {
            if (tar - coins[i] >= 0) {
                count += coinChangePermutation_IN(coins, tar - coins[i], psf + coins[i] + " ");
            }
        }

        return count;

    }

    public static int coinChangeCombination_IN(int[] coins, int tar, int idx, String psf) {
        if (tar == 0) {
            System.out.println(psf);
            return 1;
        }

        int count = 0;
        for (int i = idx; i < coins.length; i++) {
            if (tar - coins[i] >= 0) {
                count += coinChangeCombination_IN(coins, tar - coins[i], i, psf + coins[i] + " ");
            }
        }
        return count;
    }

    public static int coinChangePermutation_Sin(int[] coins, int tar, String psf) {
        if (tar == 0) {
            System.out.println(psf);
            return 1;
        }

        int count = 0;
        for (int i = 0; i < coins.length; i++) {
            if (coins[i] > 0 && tar - coins[i] >= 0) {
                int val = coins[i];
                coins[i] = -coins[i];
                count += coinChangePermutation_Sin(coins, tar - val, psf + val + " ");
                coins[i] = -coins[i];
            }
        }

        return count;
    }

    public static int coinChangeCombination_Sin(int[] coins, int tar, int idx, String psf) {
        if (tar == 0) {
            System.out.println(psf);
            return 1;
        }

        int count = 0;
        for (int i = idx; i < coins.length; i++) {
            if (tar - coins[i] >= 0) {
                count += coinChangeCombination_Sin(coins, tar - coins[i], i + 1, psf + coins[i] + " ");
            }
        }
        return count;
    }


```
#### way-2 Subset or select non select way


```java

    public static int coinChangePermutation_IN_Sub(int[] coins, int tar, int idx, String psf) {
        if (tar == 0 || idx == coins.length) {
            if (tar == 0) {
                System.out.println(psf);
                return 1;
            }
            return 0;
        }

        int count = 0;
        if (tar - coins[idx] >= 0)
            count += coinChangePermutation_IN_Sub(coins, tar - coins[idx], 0, psf + coins[idx] + " ");
        count += coinChangePermutation_IN_Sub(coins, tar, idx + 1, psf);

        return count;
    }

    public static int coinChangeCombination_IN_Sub(int[] coins, int tar, int idx, String psf) {
        if (tar == 0 || idx == coins.length) {
            if (tar == 0) {
                System.out.println(psf);
                return 1;
            }
            return 0;
        }

        int count = 0;
        if (tar - coins[idx] >= 0)
            count += coinChangeCombination_IN_Sub(coins, tar - coins[idx], idx, psf + coins[idx] + " ");
        count += coinChangeCombination_IN_Sub(coins, tar, idx + 1, psf);

        return count;
    }

    public static int coinChangeCombination_Sin_Sub(int[] coins, int tar, int idx, String psf) {
        if (tar == 0 || idx == coins.length) {
            if (tar == 0) {
                System.out.println(psf);
                return 1;
            }
            return 0;
        }

        int count = 0;

        if (tar - coins[idx] >= 0) {
            count += coinChangeCombination_Sin_Sub(coins, tar - coins[idx], idx + 1, psf + coins[idx] + " ");
        }
        count += coinChangeCombination_Sin_Sub(coins, tar, idx + 1, psf);

        return count;
    }

    public static int coinChangePermutation_Sin_Sub(int[] coins, int tar, int idx, String psf) {
        if (tar == 0 || idx == coins.length) {
            if (tar == 0) {
                System.out.println(psf);
                return 1;
            }
            return 0;
        }

        int count = 0;
        if (tar - coins[idx] >= 0) {
            int val = coins[idx];
            coins[idx] = -coins[idx];
            count += coinChangePermutation_IN_Sub(coins, tar - val, 0, psf + val + " ");
            coins[idx] = -coins[idx];
        }
        count += coinChangePermutation_IN_Sub(coins, tar, idx + 1, psf);

        return count;
    }


```

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

----
## Count no of subsets or subsequence having sum K

### Cpp
```cpp
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


```

### Java

```java
class Solution {
    private int sumOfeachSubset(int[] nums, int n,int k,int i,int sum){
        if(i==n) return sum==k?1:0;
        if(sum==k) return 1;

        return sumOfeachSubset(nums,n,k,i+1,sum+nums[i])
        +sumOfeachSubset(nums,n,k,i+1,sum);

      
    }
    private int check (int[] nums, int n,int k){
          return  sumOfeachSubset(nums,n,k,0,0);
    }
    public int countSubsequenceWithTargetSum(int[] nums, int k) {
        return check(nums,nums.length,k);
    }
}

```

### Cehck whether k sum can be reached by subset 

#### Cpp
```cpp
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

```
#### Java

```java
class Solution {
    private boolean sumOfeachSubset(int[] nums, int n,int k,int i,int sum){
        if(i==n) return sum==k;
        if(sum==k) return true;

        boolean v1=sumOfeachSubset(nums,n,k,i+1,sum+nums[i]);
        if(v1==true) return true;
        boolean v2=sumOfeachSubset(nums,n,k,i+1,sum);
        if(v2==true) return true;

         return false;  
    }
    private boolean check (int[] nums, int n,int k){
          return  sumOfeachSubset(nums,n,k,0,0);
    }
    public boolean checkSubsequenceSum(int[] nums, int k) {
         return check (nums,nums.length,k);
    }
}
```

#### Java

```java
class Solution {
    /*
    Time Complexity O(2n) - Each item has two choices (include or exclude), leading to an exponential number of combinations.

    Space Complexity: O(n) - The maximum depth of the recursive call stack is equal to the number of items.
    */
    public boolean solve(int i, int n, int[] arr, int k) {

        if (k == 0) {
            return true;
        }

        if (k < 0) {
            return false;
        }

        if (i == n) {
            return k == 0;
        }

        return solve(i + 1, n, arr, k - arr[i]) || solve(i + 1, n, arr, k);
    }

    // This method initiates the recursive process
    public boolean checkSubsequenceSum(int[] nums, int target) {
        int n = nums.length; 
        return solve(0, n, nums, target); 
    }

    // Main method to test the solution
    public static void main(String[] args) {
        Solution sol = new Solution();
        int[] nums = {1, 2, 3, 4};
        int target = 5;
        System.out.println(sol.checkSubsequenceSum(nums, target)); // Expected output: true
    }
}

```