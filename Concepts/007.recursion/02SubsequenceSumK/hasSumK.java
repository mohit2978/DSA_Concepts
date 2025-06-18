class Solution {
    private boolean sumOfeachSubset(int[] nums, int n,int k,int i,int sum){
        if(i==n) return sum==k;
        if(sum==k) return true;

        boolean v1=sumOfeachSubset(nums,n,k,i+1,sum+nums[i]);
        if(v1==true) return true;
        boolean v2=sumOfeachSubset(nums,n,k,i+1,sum);
        if(v2==true) return true;

         return false;  
    }
    private boolean check (int[] nums, int n,int k){
          return  sumOfeachSubset(nums,n,k,0,0);
    }
    public boolean checkSubsequenceSum(int[] nums, int k) {
         return check (nums,nums.length,k);
    }
}