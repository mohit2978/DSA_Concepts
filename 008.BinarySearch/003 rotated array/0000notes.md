# Notes

## Q1 Search in Rotated Sorted Array I

Given an integer array `nums`, sorted in ascending order (with distinct values) and a target value `k`. The array is rotated at some pivot point that is unknown.

Find the index at which `k` is present, and if `k` is not present, return `-1`.

## Examples

**Example 1:**
- **Input:** `nums = [4, 5, 6, 7, 0, 1, 2]`, `k = 0`
- **Output:** `4`
- **Explanation:** The target `0` is present at index 4 in the array.

**Example 2:**
- **Input:** `nums = [4, 5, 6, 7, 0, 1, 2]`, `k = 3`
- **Output:** `-1`
- **Explanation:** The target `3` is not present in the given array.

## Constraints

* `1 <= nums.length <= 10^4`
* `-10^4 <= nums[i] <= 10^4`
* All values of `nums` are unique.
* `nums` is an ascending array that is possibly rotated.
* `-10^4 <= k <= 10^4`

***


```cpp
class Solution {

    int bs(vector<int> &nums, int target,int low ,int high){
        int n=nums.size();
        while(low<=high){
            int mid=(low+high)/2;
            if(nums[mid]==target) return mid;
            // Check if the left part is sorted
            if (nums[low] <= nums[mid]) {
                if (nums[low] <= target && target <= nums[mid]) {
                    // Target exists in the left sorted part
                    high = mid - 1 ;
                } else {
                    // Target does not exist in the left sorted part
                    low = mid + 1;
                }
            } else {
                // Check if the right part is sorted
                if (nums[mid] <= target && target <= nums[high]) {
                    // Target exists in the right sorted part
                    low = mid + 1;
                } else {
                    // Target does not exist in the right sorted part
                    high = mid - 1;
                }
        }
        }
        return -1;
    }
public:
    int search(vector<int> &nums, int k) {
       return bs(nums,k,0,nums.size()-1);
    }
};

```

## Q2 Find min in sorted array

Given an integer array nums of size N, sorted in ascending order with distinct values, and then rotated an unknown number of times (between 1 and N), find the minimum element in the array.

---
Example 1

Input : nums = [4, 5, 6, 7, 0, 1, 2, 3]

Output: 0

Explanation: Here, the element 0 is the minimum element in the array.

---
Example 2

Input : nums = [3, 4, 5, 1, 2]

Output: 1

Explanation:Here, the element 1 is the minimum element in the array.

---
Example 3

Input : nums = [4, 5, 6, 7, -7, 1, 2, 3]

Output:

-7

---
Constraints

n == nums.length

 1 <= n <= $10^4$

 -$10^4$ <= nums[i] <= $10^4$

 All the integers of nums are unique.
 nums is sorted and rotated between 1 and n times.

```cpp
class Solution {

public:
    int findMin(vector<int> &arr)  {
      int si=0;
      int ei=arr.size()-1;
       int ans = INT_MAX;  
      while(si<=ei){
        int mid=(si+ei)/2;
        if(arr[mid]>=arr[si]){
            ans = min(ans, arr[si]);  
            si=mid+1;
        }else{
            ans = min(ans, arr[mid]);  
            ei=mid-1;
        }
      }
      return ans;
    }
};
```
![alt text](<003rotated array_240105_131613.jpg>)
 ![alt text](<003rotated array_240105_131613(1).jpg>) ![alt text](<003rotated array_240105_131613(2).jpg>) ![alt text](<003rotated array_240105_131613(3).jpg>) ![alt text](<003rotated array_240105_131613(4).jpg>) ![alt text](<003rotated array_240105_131613(5).jpg>) ![alt text](<003rotated array_240105_131613(6).jpg>) ![alt text](<003rotated array_240105_131613(7).jpg>) ![alt text](<003rotated array_240105_131613(8).jpg>)

![alt text](<003rotated array_240105_131613(9).jpg>) 

![alt text](<003rotated array_240105_131613(10).jpg>) ![alt text](<003rotated array_240105_131613(11).jpg>) ![alt text](<003rotated array_240105_131613(12).jpg>) ![alt text](<003rotated array_240105_131613(13).jpg>) ![alt text](<003rotated array_240105_131613(14).jpg>) ![alt text](<003rotated array_240105_131613(15).jpg>) ![alt text](<003rotated array_240105_131613(16).jpg>) ![alt text](<003rotated array_240105_131613(17).jpg>) ![alt text](<003rotated array_240105_131613(18).jpg>) ![alt text](<003rotated array_240105_131613(19).jpg>) ![alt text](<003rotated array_240105_131613(20).jpg>) ![alt text](<003rotated array_240105_131613(21).jpg>)


