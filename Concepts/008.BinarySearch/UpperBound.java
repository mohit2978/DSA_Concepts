/*
Given a sorted array of nums and an integer x, write a program to find the upper bound of x. The upper bound algorithm finds the first or the smallest index in a sorted array where the value at that index is greater than a given key i.e. x.

If no such index is found, return the size of the array.
*/

class Solution {
    private int bs(int[]a ,int si,int ei,int tar){
        int ans=a.length;
        while(si<=ei){
            int mid=(si+ei)>>1;
            if(a[mid]<=tar) si=mid+1;
            else if(a[mid]>tar){
                ans=mid;
                ei=mid-1;
            }
        }
        return ans;
    }
    public int upperBound(int[] nums, int x) {
        int si=0;
       int ei=nums.length-1;
       return bs(nums,si,ei,x);
    }
}
