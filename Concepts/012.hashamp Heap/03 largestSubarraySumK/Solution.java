
import java.util.*;

class Solution {
    public int longestSubarray(int[] nums, int k) {
        int n = nums.length;

        Map<Integer, Integer> preSumMap = new HashMap<>();
        int sum = 0;
        int maxLen = 0;
        for (int i = 0; i < n; i++) {
            sum += nums[i];
            if (sum == k) {
                maxLen = Math.max(maxLen, i + 1);
            }
            int rem = sum - k;
            if (preSumMap.containsKey(rem)) {
                int len = i - preSumMap.get(rem);
                maxLen = Math.max(maxLen, len);
            }
            if (!preSumMap.containsKey(sum)) {
                preSumMap.put(sum, i);
            }
        }

        return maxLen;
    }

    public static void main(String[] args) {
        int[] nums = { -1, 1, 1 };
        int k = 1;

        // Create an instance of the Solution class
        Solution solution = new Solution();
        // Function call to get the result
        int len = solution.longestSubarray(nums, k);
        
        System.out.println("The length of the longest subarray is: " + len);
    }
}
