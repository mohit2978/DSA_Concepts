class Solution {
    private int sumOfeachSubset(int[] nums, int n,int k,int i,int sum){
        if(i==n) return sum==k?1:0;
        if(sum==k) return 1;

        return sumOfeachSubset(nums,n,k,i+1,sum+nums[i])
        +sumOfeachSubset(nums,n,k,i+1,sum);

      
    }
    private int check (int[] nums, int n,int k){
          return  sumOfeachSubset(nums,n,k,0,0);
    }
    public int countSubsequenceWithTargetSum(int[] nums, int k) {
        return check(nums,nums.length,k);
    }
}