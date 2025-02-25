class Solution {
    public int[] sortedSquares(int[] nums) {
        int [] res=new int[nums.length];
        int i=0;
        int j=nums.length-1;
        int resptr=j;
        while(i<=j){
            int sqi=nums[i]*nums[i];
            int sqj=nums[j]*nums[j];
            if(sqi>sqj){
                res[resptr]=sqi;
                i++;
            }
            else{
                res[resptr]=sqj;
                j--;
                
            }
            resptr--;
        }
        return res;
    }
}