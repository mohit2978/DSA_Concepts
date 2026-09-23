
## Q1  16. 3Sum Closest



Given an integer array `nums` of length `n` and an integer `target`, find three integers in `nums` such that the sum is closest to `target`.

Return *the sum of the three integers*.

You may assume that each input would have exactly one solution.

### Example 1:

```
Input: nums = [-1,2,1,-4], target = 1
Output: 2
Explanation: The sum that is closest to the target is 2. (-1 + 2 + 1 = 2).
```

### Example 2:

```
Input: nums = [0,0,0], target = 1
Output: 0
Explanation: The sum that is closest to the target is 0. (0 + 0 + 0 = 0).
```

### Constraints:

- `3 <= nums.length <= 500`
- `-1000 <= nums[i] <= 1000`
- `-10^4 <= target <= 10^4`




```cpp
class Solution {
    int twoSum (int l,int r,int tar,vector<int>& arr){
        int tres=arr[l]+arr[r];
        while(l<r){
            int sum=arr[l]+arr[r];
            if(sum==tar) return sum;
            if(sum<tar) l++;
            else r--;
            if(abs(tar-sum)< abs(tar-tres)) tres=sum;
        }
        return tres;
    }
public:
    int threeSumClosest(vector<int>& nums, int tar) {
        int n=nums.size();
        int res=accumulate(nums.begin(), nums.begin()+3, 0);
        if(n==3){
            return res;
        }
        sort(nums.begin(),nums.end());
        for(int i=0;i<n-2;i++){
            int val=twoSum(i+1,n-1,tar-nums[i],nums);
            int tres=val+nums[i];
            if(tres==tar) return tres;
            if(abs(tar-tres)< abs(tar-res)) res=tres; 
        }
        return res;
    }
};
```

tc-->O(n*n)
sc-->O(1)

## Others solution just same but easy

```java
class Solution {
    public int threeSumClosest(int[] nums, int target) {
        Arrays.sort(nums);
        int n = nums.length;
        int result = nums[0] + nums[1] + nums[2]; // Initial best guess

        for (int i = 0; i < n - 2; i++) {
            int left = i + 1, right = n - 1;

            while (left < right) {
                int sum = nums[i] + nums[left] + nums[right];

                if (Math.abs(target - sum) < Math.abs(target - result)) {
                    result = sum;
                }

                if (sum == target) return target;
                else if (sum < target) left++;
                else right--;
            }
        }

        return result;
    }
}
```