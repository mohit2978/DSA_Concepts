## Q1  Find the Smallest Divisor Given a Threshold

## Problem Description

Given an array of positive integers `nums` and an integer `threshold` (also referred to as `limit`), your task is to find the smallest positive integer divisor such that when you divide all the elements in the array by this divisor and sum up the results, the total sum is less than or equal to the `threshold` value.

**Important Note:** When dividing each element, the result **must be rounded up to the nearest integer** (i.e., you must use the ceiling function: $\left\lceil \frac{\text{num}}{\text{divisor}} \right\rceil$).

## Examples

**Example 1:**
- **Input:** `nums = [1, 2, 5, 9]`, `threshold = 6`
- **Output:** `5`
- **Explanation:**
    * If divisor is 4, sum = $\lceil 1/4 \rceil + \lceil 2/4 \rceil + \lceil 5/4 \rceil + \lceil 9/4 \rceil = 1 + 1 + 2 + 3 = 7$. (7 > 6, so 4 is too small)
    * If divisor is 5, sum = $\lceil 1/5 \rceil + \lceil 2/5 \rceil + \lceil 5/5 \rceil + \lceil 9/5 \rceil = 1 + 1 + 1 + 2 = 5$. (5 $\le$ 6, so 5 is the smallest valid divisor)

**Example 2:**
- **Input:** `nums = [2, 3, 5, 7, 11]`, `threshold = 11`
- **Output:** `3`

## Constraints

* `1 <= nums.length <= 5 * 10^4`
* `1 <= nums[i] <= 10^6`
* `nums.length <= threshold <= 10^6`


## Solution Explaination

$\sum (x[i]/div) \leq \text{limit}$ we need to find $\underline{\text{div}}$

---

**Base case:** if $\sum x[i] \leq \text{limit} \Rightarrow \text{div} = 1$


 if $\text{div} > \max(x[i])$
then $\sum x[i] \text{ /div} = 0$
But we need $\leq \text{limit}$ not to zero
& $\text{limit} \leq 10^6$

So at max  $\text{div} = \max(x[i])$

So for $2$ to $max(x[i])$ we need to check by **Binary Search** !!

```cpp

class Solution {
  bool min_div(int div,vector<int> &nums, int limit){
    int sum=0;
    for(int el:nums){
      sum+=((el+div-1)/div);
    }
    return sum<=limit;
  }
public:
  int smallestDivisor(vector<int> &nums, int limit) {
       
      long long sum=accumulate(nums.begin(),nums.end(),0);
      if(sum<=limit ) return 1;

      auto max_it=max_element(nums.begin(),nums.end());
      int max_el=*max_it;

      int si=2;
      int ei=max_el;
      int ans=INT_MAX;
      while(si<=ei){
        int mid=(si+ei)/2;

        if(min_div(mid,nums,limit)==true){
           ans=min(ans,mid);
           ei=mid-1;
        }else{
          si=mid+1;
        }

      }
      return ans;

    }
};
```


### Complexity Analysis
- Time Complexity
    O(n log m), where n is the size of nums and m is the maximum element in nums.
- Space Complexity
    O(1), excluding the input array.


    # Methods for Integer Ceiling Division $\left\lceil \frac{N}{D} \right\rceil$

Here are two primary methods for calculating the ceiling of a division between two positive integers ($N$ and $D$) in C++.

---

## Method 1: Mathematical Formula (Recommended for Integers)

This is the most efficient and widely used method as it relies only on **integer arithmetic**, avoiding the overhead and potential precision issues of floating-point numbers.

The formula is:
$$\text{Ceiling}(N, D) = \frac{N + D - 1}{D}$$
*(Note: The division operation used here is standard C++ integer division, which inherently performs the floor operation $\lfloor \cdot \rfloor$.)*

### How it Works:

* **Case 1: $N$ is Perfectly Divisible by $D$**
    * Example: $N=10, D=5$. $\frac{10}{5} = 2$.
    * Formula: $\frac{10 + 5 - 1}{5} = \frac{14}{5}$. Integer division gives $\lfloor 2.8 \rfloor = 2$. (Correct)

* **Case 2: $N$ is NOT Perfectly Divisible by $D$**
    * Example: $N=11, D=5$. $\lceil \frac{11}{5} \rceil = \lceil 2.2 \rceil = 3$.
    * Formula: $\frac{11 + 5 - 1}{5} = \frac{15}{5}$. Integer division gives $3$. (Correct)

### C++ Code Example (Method 1)

```cpp
#include <iostream>

long long ceil_division_integer(long long numerator, long long denominator) {
    // This formula works for positive numerator and positive denominator.
    if (denominator == 0) {
        // Handle division by zero error
        std::cerr << "Error: Division by zero.\n";
        return -1; 
    }
    
    // N + D - 1 / D
    return (numerator + denominator - 1) / denominator;
}

int main() {
    long long N1 = 11;
    long long D1 = 5; // Expected: ceil(2.2) = 3
    
    long long N2 = 10;
    long long D2 = 5; // Expected: ceil(2.0) = 2
    
    long long result1 = ceil_division_integer(N1, D1);
    long long result2 = ceil_division_integer(N2, D2);

    std::cout << N1 << " / " << D1 << " ceiling is: " << result1 << "\n";
    std::cout << N2 << " / " << D2 << " ceiling is: " << result2 << "\n";

    return 0;
}
```

## Method 2: Using Floating Point Conversion (`std::ceil`)

This method is more readable and uses the standard mathematical function, but it involves floating-point arithmetic, which is generally slightly slower and can sometimes introduce tiny precision errors (though highly unlikely in this simple context).

### Steps:

1.  Cast one of the integers to a `double` or `float`.
2.  Perform the division.
3.  Use `std::ceil()` from the `<cmath>` header.
4.  Cast the result back to an integer type.

### C++ Code Example (Method 2)

```cpp
#include <iostream>
#include <cmath> // Required for std::ceil

int ceil_division_float(int numerator, int denominator) {
    if (denominator == 0) {
        std::cerr << "Error: Division by zero.\n";
        return -1;
    }

    // Cast numerator to double to force floating-point division
    double result = static_cast<double>(numerator) / denominator;

    // Calculate the ceiling and cast back to int
    return static_cast<int>(std::ceil(result));
}

int main() {
    int N1 = 11;
    int D1 = 5;
    
    int N2 = 10;
    int D2 = 5;

    int result1 = ceil_division_float(N1, D1);
    int result2 = ceil_division_float(N2, D2);

    std::cout << N1 << " / " << D1 << " ceiling is: " << result1 << "\n";
    std::cout << N2 << " / " << D2 << " ceiling is: " << result2 << "\n";

    return 0;
}
```
![alt text](<005bs min max problems_231231_215058.jpg>)

 ![alt text](<005bs min max problems_231231_215058(1).jpg>) ![alt text](<005bs min max problems_231231_215058(2).jpg>) ![alt text](<005bs min max problems_231231_215058(3).jpg>) ![alt text](<005bs min max problems_231231_215058(4).jpg>) ![alt text](<005bs min max problems_231231_215058(5).jpg>) ![alt text](<005bs min max problems_231231_215058(6).jpg>) ![alt text](<005bs min max problems_231231_215058(7).jpg>) ![alt text](<005bs min max problems_231231_215058(8).jpg>) ![alt text](<005bs min max problems_231231_215058(9).jpg>) ![alt text](<005bs min max problems_231231_215058(10).jpg>) ![alt text](<005bs min max problems_231231_215058(11).jpg>) ![alt text](<005bs min max problems_231231_215058(12).jpg>) ![alt text](<005bs min max problems_231231_215058(13).jpg>) ![alt text](<005bs min max problems_231231_215058(14).jpg>) ![alt text](<005bs min max problems_231231_215058(15).jpg>) ![alt text](<005bs min max problems_231231_215058(16).jpg>) ![alt text](<005bs min max problems_231231_215058(17).jpg>) ![alt text](<005bs min max problems_231231_215058(18).jpg>) ![alt text](<005bs min max problems_231231_215058(19).jpg>) ![alt text](<005bs min max problems_231231_215058(20).jpg>) ![alt text](<005bs min max problems_231231_215058(21).jpg>) ![alt text](<005bs min max problems_231231_215058(22).jpg>) ![alt text](<005bs min max problems_231231_215058(23).jpg>) ![alt text](<005bs min max problems_231231_215058(24).jpg>) ![alt text](<005bs min max problems_231231_215058(25).jpg>) ![alt text](<005bs min max problems_231231_215058(26).jpg>) ![alt text](<005bs min max problems_231231_215058(27).jpg>) ![alt text](<005bs min max problems_231231_215058(28).jpg>) ![alt text](<005bs min max problems_231231_215058(29).jpg>) ![alt text](<005bs min max problems_231231_215058(30).jpg>) ![alt text](<005bs min max problems_231231_215058(31).jpg>) ![alt text](<005bs min max problems_231231_215058(32).jpg>)

 ![alt text](<005bs min max problems_231231_215058(33).jpg>) ![alt text](<005bs min max problems_231231_215058(34).jpg>) 
 
  ## Square root
 same code but now we see si<=ei ,now we need to increment or decement si and  ei ,we cannot keep si=mid or ei=mid now as now on si=ei when we dont chnage and keep si=mid then it will never be change and be in TLE.

so we keep si=mid+1 and at last return (si-1)

```cpp
class Solution {
public:
    int mySqrt(int x) {
        if(x==0 ||x==1) return x;
        int si=1;
        int ei=x-1;
        while(si<=ei){
            int mid=(si+ei)/2;
            if(mid>(x/mid)) ei=mid-1;
            else si=mid+1;
        }
        return (si-1);
    }
};
```
 
 ![alt text](<005bs min max problems_231231_215058(35).jpg>) 
 


 ![alt text](<005bs min max problems_231231_215058(36).jpg>) ![alt text](<005bs min max problems_231231_215058(37).jpg>) ![alt text](<005bs min max problems_231231_215058(38).jpg>) ![alt text](<005bs min max problems_231231_215058(39).jpg>) ![alt text](<005bs min max problems_231231_215058(40).jpg>) ![alt text](<005bs min max problems_231231_215058(41).jpg>) ![alt text](<005bs min max problems_231231_215058(42).jpg>) ![alt text](<005bs min max problems_231231_215058(43).jpg>) ![alt text](<005bs min max problems_231231_215058(44).jpg>) ![alt text](<005bs min max problems_231231_215058(45).jpg>) ![alt text](<005bs min max problems_231231_215058(46).jpg>) ![alt text](<005bs min max problems_231231_215058(47).jpg>) ![alt text](<005bs min max problems_231231_215058(48).jpg>) ![alt text](<005bs min max problems_231231_215058(49).jpg>) ![alt text](<005bs min max problems_231231_215058(50).jpg>) ![alt text](<005bs min max problems_231231_215058(51).jpg>) ![alt text](<005bs min max problems_231231_215058(52).jpg>) ![alt text](<005bs min max problems_231231_215058(53).jpg>) ![alt text](<005bs min max problems_231231_215058(54).jpg>) ![alt text](<005bs min max problems_231231_215058(55).jpg>) ![alt text](<005bs min max problems_231231_215058(56).jpg>) ![alt text](<005bs min max problems_231231_215058(57).jpg>)