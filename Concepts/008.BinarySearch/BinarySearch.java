/*
Given a sorted array of integers nums with 0-based indexing, find the index of a specified target integer. If the target is found in the array, return its index. If the target is not found, return -1.
*/

class Solution {
    private int bs(int[]a ,int si,int ei,int tar){
        while(si<=ei){
            int mid=(si+ei)>>1;
            if(a[mid]==tar) return mid;
            else if(a[mid]>tar) ei=mid-1;
            else si=mid+1;
        }
        return -1;
    }
    public int search(int[] nums, int target) {
       int si=0;
       int ei=nums.length-1;
       return bs(nums,si,ei,target);
    }
}