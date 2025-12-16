# Minimum number of bracket reversals to make an expression balanced

>Note: Very easy just need to know formula

Given a string s consisting of only opening and closing brackets '(' and ')', find out the minimum number of reversals required to convert the string into a balanced expression.



If it is not possible to make the brackets balanced, return -1. A reversal means changing '(' to ')' or vice-versa.


Examples:
Input: s = ")(())((("

Output: 3



Explanation: One way to balance is:

"((())())". There is no balanced sequence

that can be formed in lesser reversals.

---

Input: s = "(()((()(())(("

Output: -1

Explanation: There's no way we can balance

this sequence of braces.

---

Constraints:
1 <= s.length <= 10^4

### Just see maths

$$\text{Reversals} = \frac{m+n}{2} + \frac{m \pmod 2}{2} + \frac{n \pmod 2}{2}$$

which simplifies to:

$$\text{Reversals} = \lceil \frac{m}{2} \rceil + \lceil \frac{n}{2} \rceil$$

---

$$\text{Reversals} = \left(\frac{\text{open}}{2}\right) + (\text{open} \pmod 2) + \left(\frac{\text{close}}{2}\right) + (\text{close} \pmod 2)$$

where $\text{open}$ is the number of unbalanced opening brackets, $n$, and $\text{close}$ is the number of unbalanced closing brackets, $m$)
This is a way to express the ceiling function $\lceil x/2 \rceil$ using integer division and the modulo operator, but it has a slight adjustment in standard implementations.

```cpp
class Solution {
public:
   
    int countRev(string s) {
        int n = s.length(); 
        
        /* If string is of odd length, it is not 
        possible to balance the paranthesis */
        if(n % 2) return -1;
        
        int open = 0, close = 0;
        
        for(int i=0; i < n; i++) {
            if(s[i] == '(') open++;
            else {
                if(open > 0) open--;
                else close++;
            }
        }

        int ans = (open / 2) + (open % 2) + (close / 2) + (close % 2);
        
        return ans; 
    }
};

```
Basically 

$$\text{Reversals} = \lceil \frac{m}{2} \rceil + \lceil \frac{n}{2} \rceil$$

m is no of open unbalanced brackets 

n is no of unbalanced closed brackets

now see 

$$\lceil \frac{x}{2} \rceil = \lfloor \frac{x}{2} \rfloor + (x \pmod 2)$$

## Proof by Cases (Using Positive Integers)

Case 1: When $x$ is Even ($x = 2k$)If $x$ is even, the remainder $x \pmod 2 = 0$.$$\begin{align*}
\text{LHS} &= \lceil \frac{2k}{2} \rceil = \lceil k \rceil = k \\
\text{RHS} &= \lfloor \frac{2k}{2} \rfloor + (2k \pmod 2) \\
&= \lfloor k \rfloor + 0 \\
&= k
\end{align*}$$Since $k = k$, the identity holds.

Case 2: When $x$ is Odd ($x = 2k + 1$)If $x$ is odd, the remainder $x \pmod 2 = 1$.$$\begin{align*}
\text{LHS} &= \lceil \frac{2k+1}{2} \rceil = \lceil k + \frac{1}{2} \rceil = k + 1 \\
\text{RHS} &= \lfloor \frac{2k+1}{2} \rfloor + ((2k+1) \pmod 2) \\
&= \lfloor k + \frac{1}{2} \rfloor + 1 \\
&= k + 1
\end{align*}$$Since $k + 1 = k + 1$, the identity holds.This identity is a neat trick used in integer-based algorithms to effectively perform the ceiling operation $\lceil \dots \rceil$ without relying on floating-point arithmetic.

Above one is only valid for ceil(x/2)
----
In general for ceil of (x/y) we use formula 

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
using namespace std;
int ceil_division_float(int numerator, int denominator) {
    if (denominator == 0) {
        cerr << "Error: Division by zero.\n";
        return -1;
    }

    // Cast numerator to double to force floating-point division
    double result = static_cast<double>(numerator) / denominator;

    // Calculate the ceiling and cast back to int
    return static_cast<int>(ceil(result));
}

int main() {
    int N1 = 11;
    int D1 = 5;
    
    int N2 = 10;
    int D2 = 5;

    int result1 = ceil_division_float(N1, D1);
    int result2 = ceil_division_float(N2, D2);

    cout << N1 << " / " << D1 << " ceiling is: " << result1 << "\n";
    cout << N2 << " / " << D2 << " ceiling is: " << result2 << "\n";

    return 0;
}
```

#### Recommendation
For competitive programming and scenarios prioritizing speed and purity, Method 1 (The Integer Formula) is usually preferred as it avoids the overhead and potential issues of floating-point math.







