# Notes



![alt text](<003rotated array_240105_131613.jpg>)
 ![alt text](<003rotated array_240105_131613(1).jpg>) ![alt text](<003rotated array_240105_131613(2).jpg>) ![alt text](<003rotated array_240105_131613(3).jpg>) ![alt text](<003rotated array_240105_131613(4).jpg>) ![alt text](<003rotated array_240105_131613(5).jpg>) 
 
 
 ## Q Search in Rotated Sorted Array I

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


seee

```cpp
            if (nums[low] <= nums[mid]) {///condition 1
                
            } else {//condition 2 nums[lo]>nums[mid]
               
        }
        }
```        
we know array is rotated 

part 1 sorted ,part 2 sorted

mid in part1  and lo in part 1 then offcourse condition 1 met

mid in part 2 and low in part2 then also condition met 


If the array has distinct numbers (no duplicates), then the condition `nums[low] <= nums[mid]`guarantees that the range from low to mid is perfectly sorted.

mid in part 2 and low in part1 then in condition 2

condition 2 means from low to some j is sorted increasing and j to mid is increasing and we dont consider lo to mid we are seeing in that mid to high part

You have hit the nail on the head. That is exactly what the `else` part represents. When `nums[low] > nums[mid]`, the left side is **"Broken."**

---

### 1. Your Analysis of the Broken Left Side
You described it perfectly: *"from low to some j is sorted increasing and j to mid is increasing."*

This is exactly right. The Left side contains the **Cliff**.
* **Part 1 (low to j):** Climbs up to the peak (Maximum).
* **The Drop:** Falls from $j$ to $j+1$.
* **Part 2 (j+1 to mid):** Climbs up from the bottom (Minimum).

**Visual:** `[7, 8, 0, 1]` ($low=7, mid=1$)
* $7 \to 8$ is your first increasing part.
* $0 \to 1$ is your second increasing part.
* But $7 \to 1$ overall is **Unsorted**.

---

### 2. Why we focus on "mid to high"
Because the Left side is "messy" (it has two separate sorted chunks), it is hard to check if our `target` is there with a single `if` statement.

However, since the Cliff is on the Left, the **Right Side** (mid to high) **MUST** be clean. It is a single, continuous, sorted line. It is very easy to check:
> `if (nums[mid] < target && target <= nums[high])`

---

### 3. The Logic Flow
The thought process inside the `else` block is:
1.  **Analyze Right Side:** "I know mid to high is perfectly sorted."
2.  **Check Right Side:** "Is my target in this nice, sorted range?"
3.  **Decision:**
    * **Yes:** "Great, go Right (`low = mid + 1`)."
    * **No:** "If it's not in the sorted Right side, it must be in the messy Left side. I have no choice but to go back into the mess (`high = mid - 1`)."

---

### Summary
* **IF Block:** Left is Clean, Right is Messy. $\to$ **Check Left.**
* **ELSE Block:** Left is Messy (Broken), Right is Clean. $\to$ **Check Right.**


 
 ![alt text](<003rotated array_240105_131613(6).jpg>) ![alt text](<003rotated array_240105_131613(7).jpg>) ![alt text](<003rotated array_240105_131613(8).jpg>)

![alt text](<003rotated array_240105_131613(9).jpg>) 

![alt text](<003rotated array_240105_131613(10).jpg>) 


```cpp

class Solution {
        int bs(vector<int> &nums, int target,int low ,int high){
        int n=nums.size();
        while(low<=high){
            int mid=(low+high)/2;
            if(nums[mid]==target ||target==nums[low]) return true;
            // Check if the left part is sorted
            if (nums[low] < nums[mid]) {
                if (nums[low] <= target && target <= nums[mid]) {
                    // Target exists in the left sorted part
                    high = mid - 1 ;
                } else {
                    // Target does not exist in the left sorted part
                    low = mid + 1;
                }
            } else if (nums[mid] < nums[high]) {
                // Check if the right part is sorted
                if (nums[mid] <= target && target <= nums[high]) {
                    // Target exists in the right sorted part
                    low = mid + 1;
                } else {
                    // Target does not exist in the right sorted part
                    high = mid - 1;
                }
        } else low++;
        }
        return false;
    }
public:
    bool searchInARotatedSortedArrayII(vector<int> &nums, int k)  {
      return bs(nums,k,0,nums.size()-1);
    }
};
```


![alt text](<003rotated array_240105_131613(11).jpg>) ![alt text](<003rotated array_240105_131613(12).jpg>) ![alt text](<003rotated array_240105_131613(13).jpg>)

## Q Find min in sorted array

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



 ![alt text](<003rotated array_240105_131613(14).jpg>) ![alt text](<003rotated array_240105_131613(15).jpg>) ![alt text](<003rotated array_240105_131613(16).jpg>) ![alt text](<003rotated array_240105_131613(17).jpg>) ![alt text](<003rotated array_240105_131613(18).jpg>) 
![alt text](<003rotated array_240105_131613(19).jpg>)

```java
class Solution {
    public int peakIndexInMountainArray(int[] arr) {
         int n=arr.length;
        int lo=0;
        int hi=n-1;
        while(lo<hi){
            int mid=(lo+hi)/2;

            if(mid>0&&mid<n){
                if(arr[mid]>arr[mid-1]&& arr[mid]>arr[mid+1]) return mid;
                else if(arr[mid]<arr[mid-1] && arr[mid]>arr[mid+1]) hi=mid-1; 
                else lo=mid+1;
            }
            else   if(mid==0){
                return arr[0]>arr[1]?0:1;
            }
            else if(mid==n-2){//this is not required as covered by mid>0 &&mid<n 1st if iske bina bhi submit hora
                return arr[n-1]>arr[n-2]?n-1:n-2;
            }
   
        }
        return lo;
      }
}
```

Complexity Analysis: 
Time Complexity:O(logN), N is size of the given array. As binary search is being used to find the minimum.

Space Complexity: As no additional space is used, so the Space Complexity is O(1).

 ![alt text](<003rotated array_240105_131613(20).jpg>) 
![alt text](<003rotated array_240105_131613(21).jpg>)




## QFind how many time array is rotated

Given an integer array nums of size n, sorted in ascending order with distinct values. The array has been right rotated an unknown number of times, between 0 and n-1 (including). Determine the number of rotations performed on the array.

---

Example 1

Input : nums = [4, 5, 6, 7, 0, 1, 2, 3]

Output: 4

Explanation: The original array should be [0, 1, 2, 3, 4, 5, 6, 7]. So, we can notice that the array has been rotated 4 times.

---

Example 2

Input: nums = [3, 4, 5, 1, 2]

Output: 3

Explanation: The original array should be [1, 2, 3, 4, 5]. So, we can notice that the array has been rotated 3 times.

---

Example 3

Input: nums = [4, 5, 1, 2]

Output:

2

----

Constraints

 - n == nums.length
 - 1 <= n <= $10^4$
 - -$10^4$ <= nums[i] <= $10^4$
 - All the integers of nums are unique.


```cpp
class Solution {
public:
    int findKRotation(vector<int> &arr)  {
        int si=0;
      int ei=arr.size()-1;
       int ans = INT_MAX;  
       int index=-1;
      while(si<=ei){
        int mid=(si+ei)/2;
        if(arr[mid]>=arr[si]){
            if(arr[si]<ans){
                ans=arr[si];
                index=si;
            }
            si=mid+1;
        }else{
            if(arr[mid]<ans){
                ans=arr[mid];
                index=mid;
            }
            ei=mid-1;
        }
      }
      return index;
    }
};
```
