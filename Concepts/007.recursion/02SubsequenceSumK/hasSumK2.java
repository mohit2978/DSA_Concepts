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
