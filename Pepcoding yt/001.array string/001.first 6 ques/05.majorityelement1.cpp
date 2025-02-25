class Solution {
    public:
        int majorityElement(vector<int>& nums) {
            int n=nums.size();
            int count=1;
            int v=nums[0];
            for(int i=1;i<n;i++){
                if(nums[i]==v) count++;
                else{
                    count--;
                    if(count==0){
                        count=1;
                        v=nums[i];
                    }
                }
            }
            return v;
            
            
        }
    };