# Notes

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

![alt text](<004single number ques_240508_113639(22).jpg>) ![alt text](<004single number ques_240508_113639(23).jpg>) ![alt text](<004single number ques_240508_113639(24).jpg>) ![alt text](<004single number ques_240508_113639(25).jpg>) ![alt text](<004single number ques_240508_113639(26).jpg>) ![alt text](<004single number ques_240508_113639(27).jpg>) ![alt text](<004single number ques_240508_113639(28).jpg>) ![alt text](<004single number ques_240508_113639(29).jpg>) 

## code solution

### Brute

```cpp
#include <bits/stdc++.h>
using namespace std;
/*
Given two integers start and goal. Flip the minimum number of bits of start integer to convert it into goal integer.



A bits flip in the number val is to choose any bit in binary representation of val and flipping it from either 0 to 1 or 1 to 0.

*/
class Solution{  
    int countBits(int n){
        int res=0;
        while(n!=0){
            res++;
            n=n>>1;
        }
        return res;
    } 
public:    
    int minBitsFlip(int start, int goal) { 
        if(start==goal) return 0;
        int n=countBits(max(start,goal));
        int bitCount=0;
        for(int i=0;i<n;i++){
            int stbit=(start &(1<<i));
            int gbit=(goal &(1<<i));
            if(stbit!=gbit) bitCount++;
        }
        return bitCount;
    }
};

```

### Better
```cpp
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int minBitsFlip(int start, int goal) {
        

        int num = start ^ goal;

        int count = 0;

        for(int i = 0; i < 32; i++) {
            count += (num & 1); 
            num = num >> 1;
        }
        return count;
    }
};

int main() {
    int start = 10, goal = 7;
    
    /* Creating an instance of 
    Solution class */
    Solution sol; 
    
    /* Function call to get the minimum
     bit flips to convert number */
    int ans = sol.minBitsFlip(start, goal);
    
    cout << "The minimum bit flips to convert number is: " << ans;
    
    return 0;
}


```
Code mentioned in image is better in counting ones

![alt text](<004single number ques_240508_113639(30).jpg>)



 ![alt text](<004single number ques_240508_113639(31).jpg>) ![alt text](<004single number ques_240508_113639(32).jpg>) ![alt text](<004single number ques_240508_113639(33).jpg>) 














