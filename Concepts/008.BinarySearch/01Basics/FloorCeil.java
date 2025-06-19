/*
Given a sorted array nums and an integer x. Find the floor and ceil of x in nums.
The floor of x is the largest element in the array which is smaller than or equal to x.
The ceiling of x is the smallest element in the array greater than or equal to x. 
If no floor or ceil exists, output -1.
Input : nums =[3, 4, 4, 7, 8, 10], x= 5

Output: 4 7

Explanation: The floor of 5 in the array is 4, and the ceiling of 5 in the array is 7.

Input : nums =[3, 4, 4, 7, 8, 10], x= 8

Output: 8 8

Explanation: The floor of 8 in the array is 8, and the ceiling of 8 in the array is also 8.

*/

class Solution {
    private int findFloor(int[] arr,int x,int si,int ei){
        int ans=-1;
        while(si<=ei){
            int mid=(si+ei)/2;
            if(arr[mid]<=x){
                ans=arr[mid];
                si=mid+1;
            }else ei=mid-1;
        }
        return ans;
    }
    private int findCeil(int[] arr,int x,int si,int ei){
        int ans=-1;
        while(si<=ei){
            int mid=(si+ei)/2;
            if(arr[mid]>=x){
                ans=arr[mid];
                ei=mid-1;
            }else si=mid+1;
        }
        return ans;
    }
    public int[] getFloorAndCeil(int[] nums, int x) {
       int n=nums.length;
       int [] res=new int[2];
       res[0]=findFloor(nums,x,0,n-1);
       res[1]=findCeil(nums,x,0,n-1);
       return res;
    }
}