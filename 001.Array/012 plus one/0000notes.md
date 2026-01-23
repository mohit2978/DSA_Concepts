# Notes

# 66. Plus One

**Difficulty:** Easy

## Problem Description

You are given a **large integer** represented as an integer array `digits`, where each `digits[i]` is the $i^{th}$ digit of the integer. The digits are ordered from most significant to least significant in left-to-right order. The large integer does not contain any leading `0`'s.

Increment the large integer by one and return *the resulting array of digits*.

### Example 1:
**Input:** `digits = [1,2,3]`  
**Output:** `[1,2,4]`  
**Explanation:** The array represents the integer 123.  
Incrementing by one gives 123 + 1 = 124.  
Thus, the result should be [1,2,4].

### Example 2:
**Input:** `digits = [4,3,2,1]`  
**Output:** `[4,3,2,2]`  
**Explanation:** The array represents the integer 4321.  
Incrementing by one gives 4321 + 1 = 4322.  
Thus, the result should be [4,3,2,2].

### Example 3:
**Input:** `digits = [9]`  
**Output:** `[1,0]`  
**Explanation:** The array represents the integer 9.  
Incrementing by one gives 9 + 1 = 10.  
Thus, the result should be [1,0].

## Constraints:
- `1 <= digits.length <= 100`
- `0 <= digits[i] <= 9`
- `digits` does not contain any leading `0`'s.


### My sol

```cpp
class Solution {
public:
    vector<int> plusOne(vector<int>& digits) {
        int n=digits.size();
        vector<int>res;
        int carry=0;
        digits[n-1]++;
        bool carryNeed=false;
        for(int i=n-1;i>=0;i--){
            int sum=digits[i];
            sum+=(carryNeed==true)?carry:0;
            int val=sum;
            carryNeed=false;
            if(sum>9){
                val=sum%10;
                carry=sum/10;
                carryNeed=true;
            }
            res.push_back(val);
        }
        if(carry>=0 && carryNeed==true) res.push_back(carry);
        reverse(res.begin(),res.end());
        return res;
    }
};

```

### Insert operation

```cpp
#include <vector>
#include <iostream>

int main() {
    std::vector<int> v = {10, 20, 30};

    // 1. Insert at the front
    v.insert(v.begin(), 5);      // Result: {5, 10, 20, 30}

    // 2. Insert at the back
    v.insert(v.end(), 40);       // Result: {5, 10, 20, 30, 40}

    // 3. Insert at index 2 (between 10 and 20)
    v.insert(v.begin() + 2, 15); // Result: {5, 10, 15, 20, 30, 40}

    return 0;
}
```

### Another possible solution

```cpp
//Approach (Simple follow Math Addition Principles)
//T.C : O(n) 
//S.C : O(1)
class Solution {
public:
    vector<int> plusOne(vector<int>& digits) {
        int n = digits.size();

        int i = n-1; //Start from LSB like usual math addition

        while(i >= 0) {
            if(digits[i] < 9) {
                digits[i] += 1;
                return digits;
            }

            //else we did get 9
            digits[i] = 0; //9+1 = 10
            i--;
        }

        digits.insert(begin(digits), 1); //1 is the carry forwarded till the end

        return digits;


    }
};
```
