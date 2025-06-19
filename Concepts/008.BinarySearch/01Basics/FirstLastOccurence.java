/*
Given an array of integers nums sorted in non-decreasing order, 
find the starting and ending position of a given target value. If the target is not found in the array, return [-1, -1].


Examples:
Input: nums = [5, 7, 7, 8, 8, 10], target = 8

Output: [3, 4]

Explanation:The target is 8, and it appears in the array at indices 3 and 4, so the output is [3,4]

Input: nums = [5, 7, 7, 8, 8, 10], target = 6

Output: [-1, -1]

Expalantion: The target is 6, which is not present in the array. Therefore, the output is [-1, -1].
*/

class Solution {
    private int findFirst(int[] arr,int x,int si,int ei){
        int ans=-1;
        while(si<=ei){
            int mid=(si+ei)/2;
            if(arr[mid]==x){
                ans=mid;
                ei=mid-1;
            }else if(arr[mid]>x) ei=mid-1;
            else si=mid+1;
        }
        return ans;
    }
    private int findLast(int[] arr,int x,int si,int ei){
        int ans=-1;
        while(si<=ei){
            int mid=(si+ei)/2;
            if(arr[mid]==x){
                ans=mid;
                si=mid+1;
            }else if(arr[mid]>x) ei=mid-1;
            else si=mid+1;
        
        }
        return ans;
    }
    public int[] searchRange(int[] nums, int x) {
        int n=nums.length;
       int [] res=new int[2];
       res[0]=findFirst(nums,x,0,n-1);
       res[1]=findLast(nums,x,0,n-1);
       return res;
    }
}