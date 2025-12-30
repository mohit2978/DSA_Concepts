import java.util.*;

class Solution {
    public int longestSubarray(int[] nums, int k) {
        int n = nums.length;

        int maxLen = 0;
        int left = 0, right = 0;
        int sum = nums[0];
        while (right < n) {
            while (left <= right && sum > k) {
                sum -= nums[left];
                left++;
            }
            if (sum == k) {
                maxLen = Math.max(maxLen, right - left + 1);
            }

            right++;
            if (right < n) sum += nums[right];
        }

        return maxLen;
    }
}

class Main {
    public static void main(String[] args) {
        int[] nums = {10, 5, 2, 7, 1, 9};
        int k = 15;

        // Creating an object of Solution class
        Solution sol = new Solution();

        /* Function call to find the length
        of longest subarray having sum k */
        int ans = sol.longestSubarray(nums, k);

        System.out.println("The length of longest subarray having sum k is: " + ans);
    }
}


/*
Time Complexity: O(N), where N is the size of the array.
There are two pointers left and right which traverse the array at once taking linear time.

Space Complexity: O(1), as only a couple of variables are used.
*/

/*
This logic assumes that if the sum > k, shrinking the window from the left will eventually reduce the sum to k or less.

This is only guaranteed when all elements are positive or zero.

So the algorithm behaves predictably in such cases.

int[] nums = {5, -2, 3, 1}; 
int k = 7;
Correct subarray: {5, -2, 3, 1} → sum = 7

But your code will shrink when sum > 7 without waiting for future negative values.

Try running it — you'll see it won’t find this subarray.
 */