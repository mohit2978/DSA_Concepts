class Solution {
    private void generatePowerSet(int[] a ,int n, List<Integer>res,int idx,int sum){
        if(idx==n){
            res.add(sum);
            return;
        }
        generatePowerSet(a,n,res,idx+1,sum);
        sum+=a[idx];
        generatePowerSet(a,n,res,idx+1,sum);
        
    }
    public void  powerSet(int[] nums, List<Integer>res) {
  
        generatePowerSet(nums,nums.length,res,0,0);
        
    }
    public List<Integer> subsetSums(int[] nums) {
       List<Integer>res=new ArrayList<>();
       powerSet(nums,res);
       return res;
    }
}