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