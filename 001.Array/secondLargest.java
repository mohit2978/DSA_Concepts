class Solution {
    //two loops O(N)+O(N)
    public int secondLargestElement1(int[] nums) {
        int max1=nums[0];
        for(int i=1;i<nums.length;i++){
            if(nums[i]>max1) max1=nums[i];
        }

        int max2=Integer.MIN_VALUE;
        for(int i=0;i<nums.length;i++){
            if(nums[i]==max1) continue;
            if(nums[i]>max2) max2=nums[i];
        }
        return max2==Integer.MIN_VALUE?-1:max2;
    }
    //one loop O(N)
    public int secondLargestElement(int[] nums) {
        if (nums.length < 2) {
          return -1;
        }
        int largest = Integer.MIN_VALUE;
        int secondLargest = Integer.MIN_VALUE;
        for (int i = 0; i < nums.length; i++) {

            if (nums[i] > largest) {
                 secondLargest = largest;
                largest = nums[i];
            } 
            else if (nums[i] > secondLargest && nums[i] != largest) {
                secondLargest = nums[i];
            }

        }

        return secondLargest == Integer.MIN_VALUE ?  -1 : secondLargest;
}
}