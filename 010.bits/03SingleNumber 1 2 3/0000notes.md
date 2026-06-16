# Single Number -1

Given an array of nums of n integers. Every integer in the array appears twice except one integer. Find the number that appeared once in the array.


Examples:
Input : nums = [1, 2, 2, 4, 3, 1, 4]

Output : 3

Explanation : The integer 3 has appeared only once.

Input : nums = [5]

Output : 5

Explanation : The integer 5 has appeared only once.

Input : nums = [1, 3, 10, 3, 5, 1, 5]

Output:
10

```java
public class Solution {
    public int singleNumber1(int[] nums) {
        int ans=0;
        for(int i=0;i<nums.length;i++){
            ans^=nums[i];
        }
        return ans;
    }
    public static void main(String[] args) {
        int[] nums = {1, 2, 2, 4, 3, 1, 4};

       Solution sol = new Solution(); 
        int ans = sol.singleNumber1(nums);
        
        System.out.println("The single number in given array is: " + ans);
        //The single number in given array is: 3
    }
}

```

If array was sorted then we could have used binary seearch!!!

# Single Number II

### Problem Statement
Given an integer array `nums` where every element appears **three times** except for one, which appears **exactly once**. Find the single element and return it.

You must implement a solution with a **linear runtime complexity** $O(n)$ and use only **constant extra space** $O(1)$.

---

### Example 1
**Input:** `nums = [2, 2, 3, 2]`  
**Output:** `3`

### Example 2
**Input:** `nums = [0, 1, 0, 1, 0, 1, 99]`  
**Output:** `99`

---

### Constraints
* $1 \le \text{nums.length} \le 3 \times 10^4$
* $-2^{31} \le \text{nums}[i] \le 2^{31} - 1$
* Each element in `nums` appears exactly three times except for one element which appears once.

![alt text](<004single number ques_240508_113639.jpg>)
 ![alt text](<004single number ques_240508_113639(1).jpg>) ![alt text](<004single number ques_240508_113639(2).jpg>) ![alt text](<004single number ques_240508_113639(3).jpg>) ![alt text](<004single number ques_240508_113639(4).jpg>) ![alt text](<004single number ques_240508_113639(5).jpg>) ![alt text](<004single number ques_240508_113639(6).jpg>) ![alt text](<004single number ques_240508_113639(7).jpg>) ![alt text](<004single number ques_240508_113639(8).jpg>) ![alt text](<004single number ques_240508_113639(9).jpg>) ![alt text](<004single number ques_240508_113639(10).jpg>) ![alt text](<004single number ques_240508_113639(11).jpg>) ![alt text](<004single number ques_240508_113639(12).jpg>) ![alt text](<004single number ques_240508_113639(13).jpg>) ![alt text](<004single number ques_240508_113639(14).jpg>) ![alt text](<004single number ques_240508_113639(15).jpg>) ![alt text](<004single number ques_240508_113639(16).jpg>) ![alt text](<004single number ques_240508_113639(17).jpg>) ![alt text](<004single number ques_240508_113639(18).jpg>) ![alt text](<004single number ques_240508_113639(19).jpg>) ![alt text](<004single number ques_240508_113639(20).jpg>) ![alt text](<004single number ques_240508_113639(21).jpg>) 

 So approach was to get all (3n+1) bits count



```cpp
class Solution {
public:
    int singleNumber(vector<int>& arr) {        
        int tn=-1;
        int tnp1=0;
        int tnp2=0;
        for(int val:arr){
            int cbtn = val & tn;
            int cbtnp1 = val & tnp1;
            int cbtnp2 = val & tnp2;
            
            tn=tn & ~cbtn;
            tnp1=tnp1 & ~cbtnp1;
            tnp2=tnp2 & ~cbtnp2;
            
            tn=tn | cbtnp2;
            tnp1=tnp1 | cbtn;
            tnp2=tnp2 | cbtnp1;
        }
        return tnp1;
    }
};
```

# Single Number III

### Problem Statement
Given an integer array `nums` of length `n`, every integer in the array appears **twice** except for **two integers** which appear only once. Identify and return the two integers that appear only once in the array.

You can return the two numbers in **any order**.

---

### Example 1
**Input:** `nums = [1, 2, 1, 3, 5, 2]`  
**Output:** `[3, 5]`  
**Explanation:** The integers 3 and 5 have appeared only once.

### Example 2
**Input:** `nums = [-1, 0]`  
**Output:** `[-1, 0]`  
**Explanation:** Both -1 and 0 appear only once.

### Example 3
**Input:** `nums = [0, 1]`  
**Output:** `[0, 1]`

---

### Constraints
* $2 \le \text{nums.length} \le 10^5$
* $-2^{31} \le \text{nums}[i] \le 2^{31} - 1$
* Every integer in the array appears twice except for two integers that appear only once.

![alt text](002_231018_213632(26).jpg) ![alt text](002_231018_213632(27).jpg) ![alt text](002_231018_213632(28).jpg) ![alt text](002_231018_213632(29).jpg) ![alt text](002_231018_213632(30).jpg) ![alt text](002_231018_213632(31).jpg) ![alt text](002_231018_213632(32).jpg) ![alt text](002_231018_213632(33).jpg)



```cpp
class Solution{	
	public:		
		vector<int> singleNumber(vector<int>& nums){
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
        res[0]=set0<set1?set0:set1;
        res[1]=set0<set1?set1:set0;
        return res;
		}
};
```

Here only difference is we put sorted way in resultant array