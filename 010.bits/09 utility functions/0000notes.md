# Notes


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































