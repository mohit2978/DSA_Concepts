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
# Why `exp--` is Optional in Optimized Binary Exponentiation

In the optimized version of the code, we don't need to explicitly write `exp--` because of the "Physics" of how **Integer Division** works in languages like C++, Java, and Python (floor division).

### 1. The "Hidden" Subtraction
When you perform `exp / 2` with an **odd integer**, the computer automatically "throws away" the remainder (the `.5`).

* **If `exp = 13`:** `13 / 2` results in **6**.
* **If `exp = 12`:** `12 / 2` results in **6**.

Mathematically, doing `exp / 2` when `exp` is 13 is the **exact same thing** as doing `(13 - 1) / 2`. The `-1` (which is what `exp--` does) is handled automatically by the truncation of integer division.

---

### 2. The Step-by-Step Logic Comparison

#### **The Manual Way (if/else)**
In the manual version, we treat the oddness as a separate state:
1.  **Is it odd?** Yes (13).
2.  **Make it even:** `exp--` (Result: 12).
3.  **Next loop:** Now that it's 12, divide by 2 (Result: 6).
*This takes **two** loop iterations to get from 13 to 6.*

#### **The Optimized Way (Single Flow)**
In the optimized version, we handle the collection and the reduction simultaneously:
1.  **Is it odd?** Yes (13). **Collect the power** (`ans = ans * base`).
2.  **Next step:** `exp / 2` (Result: 6).
*This takes **one** loop iteration to get from 13 to 6.*

---

### 3. Summary for your Notes

| Feature | `if/else` with `exp--` | Optimized `exp / 2` |
| :--- | :--- | :--- |
| **Logic** | Manual "Fixing" of numbers. | Continuous Bit-Scanning. |
| **Speed** | Slightly more loop turns. | Minimum possible loop turns. |
| **Math** | $(a^{13}) = a \cdot (a^{12})$ | $(a^{13})$: Collect $a^1$, then jump to $a^6$ state. |

**The Physics:** The jump from **13 directly to 6** covers both the "subtraction" and the "halving" in a single mechanical movement.

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

# The Physics of Binary Exponentiation

To understand why we only multiply `res` when the bit is `1`, but **always** square `a`, we need to look at the **"Value"** each bit represents.

### 1. The Binary Decomposition
Every number can be written as a sum of powers of 2. For example, the exponent **13** is `1101` in binary:

$$13 = (1 \cdot 2^3) + (1 \cdot 2^2) + (0 \cdot 2^1) + (1 \cdot 2^0)$$
$$13 = 8 + 4 + 0 + 1$$

Therefore:
$$a^{13} = a^8 \cdot a^4 \cdot a^0 \cdot a^1$$

---

### 2. The "Running Power" vs. The "Final Result"
Think of the two variables as having different jobs:

* **`a` (The Running Power):** Its job is to prepare the **"building blocks."** It starts as $a^1$, then becomes $a^2$, then $a^4$, then $a^8$, then $a^{16} \dots$ regardless of whether we need them or not. We **must** square `a` every time to keep up with the binary positions.
* **`res` (The Final Result):** Its job is to **"collect"** only the building blocks that are part of our exponent's binary representation.

---

### 3. The "Buffet" Analogy
Imagine you are at a buffet. The dishes are coming out in a specific order:

1.  **Appetizer** ($a^1$)
2.  **Salad** ($a^2$)
3.  **Soup** ($a^4$)
4.  **Main Course** ($a^8$)

* **The Kitchen:** The kitchen **always** prepares every dish in order (`a = a * a`) so they are ready for the next course.
* **Your Plate (`res`):** You only put the dish on your plate (`res *= a`) if your **"Order Ticket"** (`b`) has a **1** for that specific dish.

> **Note:** If your ticket for the "Salad" position is **0**, the kitchen still makes the salad (to get to the Soup), but you don't put it on your plate.

---

### 4. Summary Table

| Step | Bit of `b` | Action on `a` (Base) | Action on `res` (Result) |
| :--- | :--- | :--- | :--- |
| **Always** | - | `a = a * a` | - |
| **If Bit is 1** | `1` | (Prepared in previous step) | `res = res * a` |
| **If Bit is 0** | `0` | (Prepared in previous step) | *Do nothing* |

# Why square `a` every time, but only multiply `res` sometimes?

### 1. The Role of `a` (The Base)
`a` represents the "Value of the current bit position."
- Loop 1: $a^1$ (Bit 0)
- Loop 2: $a^2$ (Bit 1)
- Loop 3: $a^4$ (Bit 2)
- Loop 4: $a^8$ (Bit 3)
We square `a` every time because the bit positions always double in value ($1 \rightarrow 2 \rightarrow 4 \rightarrow 8$).

### 2. The Role of `res` (The Accumulator)
We only do `res *= a` if the current bit of the exponent `b` is `1`.
- If the bit is `1`: We "need" this power of 2 for our total exponent.
- If the bit is `0`: We skip this power, but we still square `a` so it's ready for the *next* bit position.

### Example: $a^5$ ($5 = 101_2$)
| Bit Position | Value | Exponent Bit | Action |
| :--- | :--- | :--- | :--- |
| Bit 0 ($2^0$) | $a^1$ | **1** | `res = res * a^1` |
| Bit 1 ($2^1$) | $a^2$ | **0** | *Skip!* (But still square $a^2 \rightarrow a^4$) |
| Bit 2 ($2^2$) | $a^4$ | **1** | `res = res * a^4` |
**Final Result:** $a^1 \cdot a^4 = a^5$

---

### . Dry Run: `power(3, 13)`
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

