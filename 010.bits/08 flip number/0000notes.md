# Notes

Single number 3 code but done in 02!!

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




## Some extra 

```cpp
int getMSB(int n) {
    if (n == 0) return 0;

    n |= n >> 1;
    n |= n >> 2;
    n |= n >> 4;
    n |= n >> 8;
    n |= n >> 16; 
    // Now n is of the form 00011111...
    
    // To get just the MSB:
    return (n + 1) >> 1;
}
```
we have number like `1...`

`n|=n>>1` it copies MSB to 2nd MSB now number is `11...`

`n|=n>>2` it copies MSB to 2nd MSB now number is `1111...`

`n|=n>>4` it copies MSB to 2nd MSB now number is `11111111...`

`n|=n>>8` it copies MSB to 2nd MSB now number is `1111111111111111...`

if we do not have that much bits it will not do anything like number is `101010`

`n|=n>>1` makes n=111111



after all operations we get all 1's from MSB of number to LSB ,we know all 1's is $2^n$-1


Now if we do `(n+1)` we get next power of 2 that is $2^n$

now we do `(n+1)>>1` we get 2^(n-1)


after bits operation n is one less than next power of 2

so we add that one!!

To get current power just shift by 1 bits to right!









































