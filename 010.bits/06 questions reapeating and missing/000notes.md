
 ![alt text](002_231018_213632.jpg)
![alt text](002_231018_213632(1).jpg) ![alt text](002_231018_213632(2).jpg) ![alt text](002_231018_213632(3).jpg) ![alt text](002_231018_213632(4).jpg) ![alt text](002_231018_213632(5).jpg) ![alt text](002_231018_213632(6).jpg) ![alt text](002_231018_213632(7).jpg) ![alt text](002_231018_213632(8).jpg)














![alt text](002_231018_213632(9).jpg) ![alt text](002_231018_213632(10).jpg) ![alt text](002_231018_213632(11).jpg) ![alt text](002_231018_213632(12).jpg) ![alt text](002_231018_213632(13).jpg) ![alt text](002_231018_213632(14).jpg) ![alt text](002_231018_213632(15).jpg) ![alt text](002_231018_213632(16).jpg) ![alt text](002_231018_213632(17).jpg) ![alt text](002_231018_213632(18).jpg) ![alt text](002_231018_213632(19).jpg) ![alt text](002_231018_213632(20).jpg) ![alt text](002_231018_213632(21).jpg) ![alt text](002_231018_213632(22).jpg) ![alt text](002_231018_213632(23).jpg) ![alt text](002_231018_213632(24).jpg) ![alt text](002_231018_213632(25).jpg) ![alt text](002_231018_213632(26).jpg) ![alt text](002_231018_213632(27).jpg) ![alt text](002_231018_213632(28).jpg) ![alt text](002_231018_213632(29).jpg) ![alt text](002_231018_213632(30).jpg) ![alt text](002_231018_213632(31).jpg) ![alt text](002_231018_213632(32).jpg) ![alt text](002_231018_213632(33).jpg)

```cpp

class Solution {
public:
    vector<int> singleNumber(vector<int>& nums) {
        vector<int>res(2);
        unsigned int xor_val=0;
        for(int i=0;i<nums.size();i++){
            xor_val=xor_val^nums[i];
        }
        int rightMostSetMask=xor_val&-xor_val;
        int set1=0;
        int set0=0;
        for(int i=0;i<nums.size();i++){
            int dec_res=rightMostSetMask&nums[i];
            if(dec_res==0) set0=set0^nums[i];
            else set1=set1^nums[i];
        }
        res[0]=set0;
        res[1]=set1;
        return res;
    }
};
```

 ![alt text](002_231018_213632(34).jpg) ![alt text](002_231018_213632(35).jpg) ![alt text](002_231018_213632(36).jpg) ![alt text](002_231018_213632(37).jpg) ![alt text](002_231018_213632(38).jpg) ![alt text](002_231018_213632(39).jpg) 




