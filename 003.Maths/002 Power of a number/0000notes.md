# Notes
Example 1:
Input : x = 2.0000 , n = 10

Output : 1024.0000

Explanation : Answer = 2^10 => 1024.

Example 2
Input : x = 2.0000 , n = -2

Output : 0.2500

Explanation : Answer = 2^(-2) = 1/4 => 0.25.

Constraints:

-100.0 <= x <= 100.0

-2^31 <= n <= 2^31 - 1

-10^4 <= xn <= 10^4

Either x is not zero or n>0.

n is an integer.

Note:

In output print 6 digits places after decimal point.



### Power function 

```cpp
    long long Pow(int b, int exp) {
        long long ans = 1;
        long long base = b;
        
        // Exponentiation by squaring method
        while (exp > 0) {
            if (exp % 2) {
                exp--;
                ans = ans * base;
            } else {
                exp /= 2;
                base = base * base;
            }
        }
        return ans;
    }
```
>Note: use this widely in questions

 ## Binary Exponentiation (Exponentiation by Squaring)

This code implements an efficient algorithm to calculate $b^{exp}$ in $O(\log exp)$ time. Instead of multiplying the base by itself $exp$ times, it uses the properties of powers to "jump" to the result.

### How it Works
The logic relies on two mathematical identities:
1.  **If `exp` is even:** $b^{exp} = (b^2)^{exp/2}$
2.  **If `exp` is odd:** $b^{exp} = b \cdot b^{exp-1}$ (which makes the new exponent even).



---

### Dry Run: Calculating `Pow(3, 5)`
We want to find $3^5$. Initially: `ans = 1`, `base = 3`, `exp = 5`.

| Step | `exp` | Is `exp` Odd? | Action Taken | Updated `ans` | Updated `base` | Updated `exp` |
| :--- | :--- | :--- | :--- | :--- | :--- | :--- |
| **Start** | 5 | - | - | 1 | 3 | 5 |
| **Iter 1** | 5 | **Yes** | `ans = 1 * 3`; `exp--` | **3** | 3 | **4** |
| **Iter 2** | 4 | **No** | `exp /= 2`; `base = 3 * 3` | 3 | **9** | **2** |
| **Iter 3** | 2 | **No** | `exp /= 2`; `base = 9 * 9` | 3 | **81** | **1** |
| **Iter 4** | 1 | **Yes** | `ans = 3 * 81`; `exp--` | **243** | 81 | **0** |

**Final Result:** `243`

---

### Key Observations
* **Performance:** For $3^{1000}$, a standard loop takes 1,000 steps. This method takes ~10 steps ($log_2 1000 \approx 10$).
* **Data Types:** Using `long long` is essential. For example, $2^{60}$ is a massive number that will overflow a standard 32-bit integer.
* **The "Odd" Step:** When the exponent is odd, we "pull out" one instance of the base into our `ans` to make the remaining exponent even, allowing the squaring process to continue.

### Suggested Optimization
In your code, when `exp` is odd, you subtract 1 and wait for the next loop. You can streamline this by squaring the base and halving the exponent in every iteration, only multiplying `ans` when the exponent is odd:

```cpp
while (exp > 0) {
    if (exp % 2 != 0) { // If odd
        ans = ans * base;
    }
    base = base * base; // Square the base
    exp /= 2;           // Halve the exponent
}
```   

##  Optimized power function

```cpp
#include<iostream>
using namespace std;

int power(int a,int b){
     if(b==0) return 1;
        if(b<0){
            b=-b;
            a=1/a;
        }
    int res=1;
    while(b){
        if((b&1)==1){
            res*=a;
        }
        a=a*a;
        b=b>>1;
    }
    return res;
}
int main(){
    int a,b;
    a=5;
    b=5;
    cout<<power(a,b);
    return 0;
}

```

tc-->O(logn)

###  The Bitwise Logic
The `while(b)` loop continues as long as the exponent is greater than 0. It replaces standard arithmetic with two specific bitwise tricks:

* **`b & 1` (Check if Odd):** This replaces `b % 2 != 0`. It looks at the **LSB (Least Significant Bit)**. If it is 1, the number is odd.
* **`b >> 1` (Halve the exponent):** This replaces `b / 2`. It shifts all bits one position to the right, effectively dividing by 2.



---

### 3. Dry Run: `power(3, 13)`
To find $3^{13}$, we convert the exponent 13 to binary: **1101** ($8 + 4 + 0 + 1$).

| Step | `b` (Binary) | `b & 1` | Action | `res` | `a` (Base Squaring) |
| :--- | :--- | :--- | :--- | :--- | :--- |
| **Start** | 1101 (13) | — | — | 1 | 3 |
| **Iter 1** | 110**1** | **1 (Odd)** | `res *= 3` | **3** | $3^2 = 9$ |
| **Iter 2** | 011**0** | 0 (Even) | Skip `res` | 3 | $9^2 = 81$ |
| **Iter 3** | 001**1** | **1 (Odd)** | `res *= 81` | **243** | $81^2 = 6561$ |
| **Iter 4** | 000**1** | **1 (Odd)** | `res *= 6561` | **1,594,323** | $6561^2 = 43,046,721$ |
| **End** | 0000 | — | **Return res** | **1,594,323** | — |

**Result:** $3^{13} = 1,594,323$.

---

### Key Improvements
* **Speed:** Bitwise `&` and `>>` are typically faster than `%` and `/` at the hardware level because they map directly to CPU instructions.
* **Efficiency:** The algorithm only updates the result when a specific bit in the binary exponent is "on" (1), minimizing the number of multiplications.
* **Complexity:** It maintains the $O(\log b)$ time complexity, making it suitable for very large exponents that would time out in a linear loop.

### Modular Exponentiation

Modular exponentiation calculates $(base^{exp}) \pmod{mod}$. This is a cornerstone of cryptography (like RSA) because it allows you to calculate powers of massive numbers without them ever exceeding a certain limit, preventing **integer overflow**.

The logic is identical to Binary Exponentiation, but we apply the **Modulo Property of Multiplication** at every step:
$$(A \times B) \pmod C = [(A \pmod C) \times (B \pmod C)] \pmod C$$



---

### Implementation (C++)

```cpp
long long power(long long a, long long b, long long m) {
    long long res = 1;
    a %= m; // Handle cases where base 'a' is larger than 'm'
    
    while (b > 0) {
        // If the exponent bit is set (odd)
        if (b & 1) {
            res = (res * a) % m;
        }
        
        // Square the base and take modulo
        a = (a * a) % m;
        
        // Shift exponent right (divide by 2)
        b >>= 1;
    }
    return res;
}
```

