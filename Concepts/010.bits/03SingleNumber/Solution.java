/*
Given an array of nums of n integers. Every integer in the array appears twice except one integer. Find the number that appeared once in the array.


Examples:
Input : nums = [1, 2, 2, 4, 3, 1, 4]

Output : 3

Explanation : The integer 3 has appeared only once.

Input : nums = [5]

Output : 5

Explanation : The integer 5 has appeared only once.

Input : nums = [1, 3, 10, 3, 5, 1, 5]

Output:
10

*/

public class Solution {
    public int singleNumber1(int[] nums) {
        int ans=0;
        for(int i=0;i<nums.length;i++){
            ans^=nums[i];
        }
        return ans;
    }
    public static void main(String[] args) {
        int[] nums = {1, 2, 2, 4, 3, 1, 4};

       Solution sol = new Solution(); 
        int ans = sol.singleNumber1(nums);
        
        System.out.println("The single number in given array is: " + ans);
        //The single number in given array is: 3
    }
}