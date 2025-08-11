# Notes

## Bruteforce

```cpp
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        int i,j;
        vector<int>arr={-1,-1};
        for(i=0;i<nums.size();i++){
            for(j=i+1;j<nums.size();j++){
            if(nums[i]+nums[j]==target)
            {
             arr={i,j};
                break;}
            }
        
            if(arr[0]!=-1)
                break;
        }
    
    return arr;}
};
```

## Map Approach 

```java
class Solution {
    public int[] twoSum(int[] nums, int target) {
        int []res=new int[2];
        Map<Integer,Integer>mp=new HashMap<>();
        for(int i=0;i<nums.length;i++){
            int val=target-nums[i];
            if(mp.containsKey(val)==true){
                res[0]=i;
                res[1]=mp.get(val);
                return res;
            }
            mp.put(nums[i],i);
        }
        return new int[]{-1,-1};
    }
}
```

cannot use sorting one as order needs to be maintained as need to return indices!!


```cpp

class Solution {
    void fillMap(unordered_map<int,int>&mp,vector<int>& nums){
        for(int i=0;i<nums.size();i++){
            mp[nums[i]]=i;
        }
    }
public:
    vector<int> twoSum(vector<int>& nums, int t) {
        int n=nums.size();
        unordered_map<int,int>mp;
        fillMap(mp,nums);
        sort(nums.begin(),nums.end());
        int i=0,j=n-1;
        vector<int>res(2,0);
        while(i<j){
            int sum=nums[i]+nums[j];
            if(sum==t){
                res[0]=mp[nums[i]];
                res[1]=mp[nums[j]];
                return res;
            }
            if(sum<t) i++;
            else j--;
        }
        return res;
    }
};

```

Wont wrk for tc 

nums =[3,3],target=6

Output-->[1,1]

expected-->[0,1]