
## Q1. Rotate Array

### Question

Given an integer array `nums`, rotate the array to the right by `k` steps, where `k` is non-negative. The rotation must be performed in-place using `O(1)` extra space.

**Example 1**

```text
Input:  nums = [1,2,3,4,5,6,7], k = 3
Output: [5,6,7,1,2,3,4]

After 1 step: [7,1,2,3,4,5,6]
After 2 steps: [6,7,1,2,3,4,5]
After 3 steps: [5,6,7,1,2,3,4]
```

**Example 2**

```text
Input:  nums = [-1,-100,3,99], k = 2
Output: [3,99,-1,-100]
```

**Constraints**

- `1 <= nums.length <= 100000`
- `-2^31 <= nums[i] <= 2^31 - 1`
- `0 <= k <= 100000`

### Explanation

A positive `k` means rotate right; a negative rotation count would mean rotate left. Normalize the count with `k = ((k % n) + n) % n`, so it always lies in `[0, n - 1]`. Adding or subtracting `n` has no effect because a full rotation returns the array to its original state.

For a right rotation, reverse the complete array, reverse the first `k` elements, and finally reverse the remaining `n-k` elements. Reversal is used because directly shifting every element would either require extra memory or repeated movement.

![Dry run for rotating an array](<q1_rotate_array_dry_run.svg>)

### C++ Implementation

```cpp
class Solution {
    void reverseRange(vector<int>& nums, int left, int right) {
        while (left < right) {
            swap(nums[left++], nums[right--]);
        }
    }

public:
    void rotate(vector<int>& nums, int k) {
        int n = static_cast<int>(nums.size());
        k = ((k % n) + n) % n;

        reverseRange(nums, 0, n - 1);
        reverseRange(nums, 0, k - 1);
        reverseRange(nums, k, n - 1);
    }
};
```

### Java Implementation

```java
class Solution {
    private void swap(int[] nums, int i, int j) {
        int temp = nums[i];
        nums[i] = nums[j];
        nums[j] = temp;
    }

    private void reverse(int[] nums, int left, int right) {
        while (left < right) {
            swap(nums, left++, right--);
        }
    }

    public void rotate(int[] nums, int k) {
        int n = nums.length;
        k = ((k % n) + n) % n;

        reverse(nums, 0, n - 1);
        reverse(nums, 0, k - 1);
        reverse(nums, k, n - 1);
    }
}
```

### Time and Space Complexity

- **Time:** `O(n)`
- **Auxiliary space:** `O(1)`

---

## Q2. Segregate Negative and Non-Negative Elements

### Question

Given an integer array `arr`, rearrange it in-place so that every negative element appears before every non-negative element. The relative order within either group does not have to be preserved. Treat zero as non-negative.

**Example 1**

```text
Input:  arr = [4,-3,7,-1,0,-6,2]
Output: [-3,-1,-6,4,0,7,2]
```

Any arrangement in which all negative values precede all non-negative values is valid.

**Constraints**

- `1 <= arr.length <= 100000`
- `-10^9 <= arr[i] <= 10^9`

### Explanation

Maintain `boundary`, the last position occupied by a negative value, and scan from left to right. Whenever `arr[scan]` is negative, increment `boundary` and swap that value into the negative region. This is the same in-place partition idea later reused for sorting arrays containing only `0` and `1`.

![Dry run for segregating negative values](<q2_positive_negative_dry_run.svg>)

### C++ Implementation

```cpp
class Solution {
public:
    void segregateNegative(vector<int>& arr) {
        int boundary = -1;

        for (int scan = 0; scan < static_cast<int>(arr.size()); ++scan) {
            if (arr[scan] < 0) {
                swap(arr[++boundary], arr[scan]);
            }
        }
    }
};
```

### Java Implementation

```java
class Solution {
    public void segregateNegative(int[] arr) {
        int boundary = -1;

        for (int scan = 0; scan < arr.length; scan++) {
            if (arr[scan] < 0) {
                boundary++;
                int temp = arr[boundary];
                arr[boundary] = arr[scan];
                arr[scan] = temp;
            }
        }
    }
}
```

### Time and Space Complexity

- **Time:** `O(n)`
- **Auxiliary space:** `O(1)`

---

## Q3. Maximum Sum in the Configuration

### Question

Given a zero-indexed array `A` of length `N`, find the maximum possible value of:

```text
0 × A[0] + 1 × A[1] + ... + (N - 1) × A[N - 1]
```

You may rotate the array clockwise or counter-clockwise any number of times.

**Example 1**

```text
Input:  N = 4, A = [8,3,1,2]
Output: 29

Rotations and scores:
[8,3,1,2] -> 8×0 + 3×1 + 1×2 + 2×3 = 11
[3,1,2,8] -> 3×0 + 1×1 + 2×2 + 8×3 = 29
[1,2,8,3] -> 1×0 + 2×1 + 8×2 + 3×3 = 27
[2,8,3,1] -> 2×0 + 8×1 + 3×2 + 1×3 = 17
```

**Constraints**

- `1 <= N <= 10000`
- `1 <= A[i] < 1000`

### Explanation

Recomputing the complete weighted sum for every rotation takes `O(n^2)`. Instead, first calculate the total array sum `S` and the initial weighted sum `R0`.

For consecutive left rotations, the next score is:

```text
Ri = R(i - 1) - S + N × A[i - 1]
```

All values lose one from their index contribution, which subtracts `S`. The element moved from the front to the back gains `N` index positions relative to that subtraction, so add `N × A[i - 1]`. Thus each new rotation score takes constant time.


 ![alt text](<001basic ques segregate 0123 conatiner most wtr_231123_170649(17).jpg>) ![alt text](<001basic ques segregate 0123 conatiner most wtr_231123_170649(18).jpg>)
 
 
  ![alt text](<001basic ques segregate 0123 conatiner most wtr_231123_170649(19).jpg>) 


### C++ Implementation

```cpp
class Solution {
public:
    long long maxSum(const vector<int>& arr) {
        int n = static_cast<int>(arr.size());
        long long sum = 0;
        long long weighted = 0;

        for (int i = 0; i < n; ++i) {
            sum += arr[i];
            weighted += 1LL * i * arr[i];
        }

        long long answer = weighted;
        for (int i = 1; i < n; ++i) {
            weighted = weighted - sum + 1LL * n * arr[i - 1];
            answer = max(answer, weighted);
        }

        return answer;
    }
};
```

### Java Implementation

```java
class Solution {
    public long maxSum(int[] arr) {
        int n = arr.length;
        long sum = 0;
        long weighted = 0;

        for (int i = 0; i < n; i++) {
            sum += arr[i];
            weighted += (long) i * arr[i];
        }

        long answer = weighted;
        for (int i = 1; i < n; i++) {
            weighted = weighted - sum + (long) n * arr[i - 1];
            answer = Math.max(answer, weighted);
        }

        return answer;
    }
}
```

### Time and Space Complexity

- **Time:** `O(n)`
- **Auxiliary space:** `O(1)`

---

## Q4. Container With Most Water

### Question

You are given an integer array `height` of length `n`. There are `n` vertical lines; the endpoints of the line at index `i` are `(i, 0)` and `(i, height[i])`.

Choose two lines that, together with the x-axis, form a container holding the maximum possible amount of water. Return that maximum area. The container's sides may not be slanted.

**Example 1**

```text
Input:  height = [1,8,6,2,5,4,8,3,7]
Output: 49
Explanation: Lines at indices 1 and 8 give width 7 and height min(8,7) = 7.
             Area = 7 × 7 = 49.
```

**Example 2**

```text
Input:  height = [1,1]
Output: 1
```

**Constraints**

- `n == height.length`
- `2 <= n <= 100000`
- `0 <= height[i] <= 10000`

### Explanation

Start with one pointer at each end, giving the maximum possible width. The water held by the two selected lines is:

```text
area = (right - left) × min(height[left], height[right])
```

After calculating the area, move the pointer at the shorter line. Moving the taller line cannot improve the height limit because the shorter line would remain, while the width would decrease. Moving the shorter line is the only move that might find a taller limiting side and compensate for the smaller width. If both heights are equal, either pointer may move.


  ![alt text](<001basic ques segregate 0123 conatiner most wtr_231123_170649(20).jpg>) 
  ![alt text](<001basic ques segregate 0123 conatiner most wtr_231123_170649(21).jpg>)
   ![alt text](<001basic ques segregate 0123 conatiner most wtr_231123_170649(22).jpg>) 
   ![alt text](<001basic ques segregate 0123 conatiner most wtr_231123_170649(23).jpg>)


### C++ Implementation

```cpp
class Solution {
public:
    int maxArea(vector<int>& height) {
        int left = 0;
        int right = static_cast<int>(height.size()) - 1;
        int best = 0;

        while (left < right) {
            int width = right - left;

            if (height[left] < height[right]) {
                best = max(best, height[left] * width);
                left++;
            } else {
                best = max(best, height[right] * width);
                right--;
            }
        }

        return best;
    }
};
```

### Java Implementation

```java
class Solution {
    public int maxArea(int[] height) {
        int left = 0;
        int right = height.length - 1;
        int best = 0;

        while (left < right) {
            int width = right - left;

            if (height[left] < height[right]) {
                best = Math.max(best, height[left] * width);
                left++;
            } else {
                best = Math.max(best, height[right] * width);
                right--;
            }
        }

        return best;
    }
}
```

### Time and Space Complexity

- **Time:** `O(n)`
- **Auxiliary space:** `O(1)`



## Q5. Trapping Rain Water


 ![alt text](<005min stk duplicate ltters trapping rain_231121_014732(7).jpg>) ![alt text](<005min stk duplicate ltters trapping rain_231121_014732(8).jpg>) ![alt text](<005min stk duplicate ltters trapping rain_231121_014732(9).jpg>) ![alt text](<005min stk duplicate ltters trapping rain_231121_014732(10).jpg>) ![alt text](<005min stk duplicate ltters trapping rain_231121_014732(11).jpg>) ![alt text](<005min stk duplicate ltters trapping rain_231121_014732(12).jpg>) ![alt text](<005min stk duplicate ltters trapping rain_231121_014732(13).jpg>) ![alt text](<005min stk duplicate ltters trapping rain_231121_014732(14).jpg>) ![alt text](<005min stk duplicate ltters trapping rain_231121_014732(15).jpg>) ![alt text](<005min stk duplicate ltters trapping rain_231121_014732(16).jpg>) ![alt text](<005min stk duplicate ltters trapping rain_231121_014732(17).jpg>) ![alt text](<005min stk duplicate ltters trapping rain_231121_014732(18).jpg>) ![alt text](<005min stk duplicate ltters trapping rain_231121_014732(19).jpg>) ![alt text](<005min stk duplicate ltters trapping rain_231121_014732(20).jpg>) ![alt text](<005min stk duplicate ltters trapping rain_231121_014732(21).jpg>) ![alt text](<005min stk duplicate ltters trapping rain_231121_014732(22).jpg>) 



```cpp
class Solution
{
public:
    int trap(vector<int> &arr){
        int n=arr.size();
        int i=0;
        int j=n-1;
        int lmax=0;
        int rmax=0;
        int water=0;
        while(i<j){
            lmax=max(arr[i],lmax);
            rmax=max(arr[j],rmax);

            water+=(lmax<rmax?(lmax-arr[i++]):(rmax-arr[j--]));
        }
        return water;

    }
};
```

