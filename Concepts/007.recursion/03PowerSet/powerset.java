//Another way to generate power set one was by bits 
//both have same TC 
//can see in bits power set
class Solution {
    private void generatePowerSet(int[] a ,int n,List<List<Integer>> res, List<Integer>tres,int idx){
        if(idx==n){
            res.add(new ArrayList<>(tres));
            return;
        }
        tres.add(a[idx]);
        generatePowerSet(a,n,res,tres,idx+1);
        tres.remove(tres.size()-1);
        generatePowerSet(a,n,res,tres,idx+1);
    }
    public List<List<Integer>> powerSet(int[] nums) {
        List<List<Integer>> res=new ArrayList<>();
        List<Integer>tres=new ArrayList<>();
        generatePowerSet(nums,nums.length,res,tres,0);
        return res;
    }
}