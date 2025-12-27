class Solution {
    int solve(vector<int>& nums ,int n,int i){
        if(i==n-1) return 0;
        int ways=10001;
        for(int j=1;j<=nums[i];j++){

            if(i+j<=n-1){
                ways=min(ways,solve(nums,n,i+j));
            }
        }
        return ways+1;
    }
public:
    int jump(vector<int>& nums) {
       return  solve(nums,nums.size(),0);
    }
};