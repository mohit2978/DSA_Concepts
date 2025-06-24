
import java.util.HashMap;

class Solution {
    public int subarraySum(int[] nums, int k) {
        int n = nums.length;
        HashMap<Integer, Integer> prefixSumMap = new HashMap<>();
        int currentPrefixSum = 0, subarrayCount = 0;
        prefixSumMap.put(0, 1);

            currentPrefixSum += nums[i];

            int sumToRemove = currentPrefixSum - k;


            subarrayCount += prefixSumMap.getOrDefault(sumToRemove, 0);

      
            prefixSumMap.put(currentPrefixSum, prefixSumMap.getOrDefault(currentPrefixSum, 0) + 1);
        }
        return subarrayCount;
    }

    public static void main(String[] args) {
        // Create an instance of the Solution class
        Solution solution = new Solution();
        int[] nums = {3, 1, 2, 4};
        int k = 6;
        // Function call to get the result
        int subarrayCount = solution.subarraySum(nums, k);
        System.out.println("The number of subarrays is: " + subarrayCount);
    }
}
