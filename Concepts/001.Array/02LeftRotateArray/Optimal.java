class Solution {
    private void reverseArray(int[] nums, int start, int end) {

        while (start < end) {
            int temp = nums[start];
            nums[start] = nums[end];
            nums[end] = temp;
            start++;
            end--;
        }
    }
    public void rotateArray(int[] nums, int k) {
        
        if(k>=nums.length) k=k%nums.length;
        if(nums.length<=1 || k==0) return;
        reverseArray(nums,0,k-1);
        reverseArray(nums,k,nums.length-1);
        reverseArray(nums,0,nums.length-1);
    }
}

/*
Complexity Analysis: 
Time Complexity: O(N), where N is the size of the array
As three reversals are performed taking O(k), O(N-k) and O(N) time respectively.

Space Complexity: O(1), as no extra space is used .
*/