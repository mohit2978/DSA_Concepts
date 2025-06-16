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