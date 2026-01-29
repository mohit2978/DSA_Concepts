# The Euclidean Algorithm: Finding the GCD

The **Euclidean Algorithm** is an efficient method for finding the **Greatest Common Divisor (GCD)** of two numbers by repeatedly reducing the problem into smaller, more manageable pieces.

It is based on one simple observation: **The GCD of two numbers also divides their difference and their remainder.**

---

### 1. The Core Principle

If a number $d$ divides both $100$ and $80$, it must also divide the "gap" between them ($20$). 

Instead of just subtracting repeatedly (which can be slow), we use **division (modulo)** to jump many steps at once. 

**The Mathematical Rule:** $$GCD(a, b) = GCD(b, a \pmod b)$$

### The Logic of Divisibility

If $d$ is a common divisor of $a$ and $b$:
1. **$d$ divides $(a + b)$**
2. **$d$ divides $(a - b)$**
3. **$d$ divides $(a \pmod b)$**

**Analogy**: 
If you can build two towers of heights $a$ and $b$ using only blocks of height $d$, you can also build the difference of those towers or the remainder using those same blocks. You will never need to "cut" a block.

---

### 2. How it works (Step-by-Step)

Let's find $GCD(48, 18)$ using the logic of the algorithm:

| Step | Dividend ($b$) | Divisor ($a$) | Remainder ($b \pmod a$) | Logic |
| :--- | :--- | :--- | :--- | :--- |
| **1** | 48 | 18 | **12** | $48 = (18 \times 2) + \mathbf{12}$ |
| **2** | 18 | 12 | **6** | $18 = (12 \times 1) + \mathbf{6}$ |
| **3** | 12 | 6 | **0** | $12 = (6 \times 2) + \mathbf{0}$ |

**The result:** Since the remainder is now **0**, the last divisor used (**6**) is the GCD.

---

### 3. Why is it so fast?

In every step, the numbers get smaller very quickly. Mathematically, it is proven that the numbers decrease by at least half every two steps. 

* **Time Complexity**: $O(\log(\min(a, b)))$
* **Performance**: Even for massive 64-bit integers ($\approx 10^{18}$), it takes fewer than **100 iterations** to find the answer.

---

### 4. Implementation in Code

While you can use a `while` loop with a remainder variable, many developers prefer the **Recursive Version** because it matches the mathematical definition perfectly:

```cpp
int gcd(int a, int b) {
    // Base case: GCD(x, 0) is x because x divides 0 and x
    if (b == 0) return a; 
    
    // Recursive step: Replace a with b, and b with (a % b)
    return gcd(b, a % b); 
}
```
No need to swap bigger number it will automaticaly be swapped!!

Iterative approach

```cpp

int gcd(int a,int b){
    
    int divisor = a;
    int dividend = b;
    
    while(dividend % divisor != 0){
        int rem = dividend % divisor;
        dividend = divisor;
        divisor = rem;
    }
    
    return divisor;
}
```
# The Physics of GCD: The Linear Combination Rule

### 1. The Mathematical Foundation
If a number $d$ divides $a$ and $b$, it means $a$ and $b$ are simply multiples of $d$.
* $a = n \cdot d$ (where $n$ is an integer)
* $b = m \cdot d$ (where $m$ is an integer)

### 2. The Linear Combination Proof
A **Linear Combination** is any expression created by multiplying $a$ and $b$ by integers ($x$ and $y$) and adding them: $ax + by$.

**The Step-by-Step Substitution:**
1. Start with: $ax + by$
2. Substitute $a$ and $b$: $(n \cdot d)x + (m \cdot d)y$
3. **Factor out $d$ (The common DNA):** $d \cdot (nx + my)$
4. Since $(nx + my)$ is just another integer ($K$), we get: $d \cdot K$

> **The Core Law:** Because $ax + by$ can be written as $d \cdot K$, the divisor $d$ **must** divide any combination of $a$ and $b$.

---

### 3. Application: Why $a \% b$ works
The remainder $r$ (from $a \% b$) is defined as:
$$r = a - (q \cdot b)$$
*(where $q$ is the quotient)*

**The Logic:**
* This expression is a linear combination where $x = 1$ and $y = -q$.
* Because $d$ divides $a$ and $b$, it **must** divide the remainder $r$.
* This proves that $GCD(a, b)$ and $GCD(b, a \% b)$ share the **exact same set of divisors.**

---

### 4. The Lego Analogy (Mental Model)
* **The Unit:** Imagine $d$ is a Lego brick of **size 2**.
* **Object A:** A stick of 10cm (made of 5 Lego bricks).
* **Object B:** A stick of 6cm (made of 3 Lego bricks).

**The Physics:**
If you combine, subtract, or cut these sticks, you are still only working with size-2 bricks.
* If you take 6cm away from 10cm, the remaining **4cm** is still made of two size-2 bricks.
* You can never produce a piece that is **not** a multiple of 2. 
* $d$ is the "DNA" that survives every operation.

---

### 5. Algorithmic Summary

| Step | Operation | Result |
| :--- | :--- | :--- |
| **Identity** | $GCD(a, b) = GCD(b, a \% b)$ | Mathematically identical divisors. |
| **Reduction** | $a \rightarrow (a \% b)$ | Numbers shrink rapidly toward zero. |
| **Convergence** | $GCD(b, \text{smaller})$ | The algorithm "crushes" the problem to find the GCD. |

---


Now question comes GCD(a,b)=GCD(b,a%b) but why not GCD(a,a%b)?

# Why b is the "Star" of the GCD Algorithm

Mathematically:
- CommonDivisors(a, b) == CommonDivisors(b, a % b)
- CommonDivisors(a, b) == CommonDivisors(a, a % b)

BUT, in the Algorithm:
1. **Convergence**: GCD(b, a % b) makes both terms smaller, leading to the base case faster.
2. **Correctness**: The base case `if (b == 0) return a` expects the divisor to be in the `a` position. If you never swap `b` into the `a` position, you'll eventually return the original large `a` instead of the divisor `b`.
3. **Constraint**: The GCD is limited by the smaller number. Keeping the smaller number ($b$) as the new "target" is more logical than keeping the large "source" ($a$).

# Subtraction vs. Modulo in the Euclidean Algorithm

Understanding the transition from subtraction to modulo is the key to understanding why the Euclidean Algorithm is so efficient.

---

### 1. The Correction: Is `a % b` the "Gap"?

* **Subtraction ($a - b$):** This represents the **actual gap** (distance) between two numbers.
* **Modulo ($a \% b$):** This is the **remainder** left over after you remove the "gap" $b$ from $a$ as many times as possible.

---

### 2. Why the "Gap" Logic Works

The original Euclidean Algorithm actually started by using simple subtraction. 

> **The Subtraction Theorem:** $$GCD(a, b) = GCD(b, a - b)$$

If a number $d$ divides both $a$ and $b$, it **must** divide the gap between them. However, subtraction is slow. For example, if you wanted to find $GCD(100, 2)$, you would have to perform the subtraction $100 - 2$ fifty times!

**Modulo ($a \% b$)** acts as a **"Fast-Forward" button**. Instead of subtracting $b$ one by one, `a % b` subtracts all possible "gaps" of $b$ at once, leaving only the tiny leftover piece (the remainder).

---

### 3. Visualizing the "Gap" vs. "Remainder"

Imagine finding the GCD of **10** and **3**:

#### The Subtraction Way (Slow Gap):
1.  $GCD(10, 3)$
2.  Gap is $10 - 3 = 7 \to GCD(7, 3)$
3.  Gap is $7 - 3 = 4 \to GCD(4, 3)$
4.  Gap is $4 - 3 = 1 \to GCD(1, 3)$
5.  *...Eventually, you reach 1.*

#### The Modulo Way (Fast Remainder):
1.  $GCD(10, 3)$
2.  $10 \% 3 = 1$ 
    *(This is like performing all the subtraction steps above in a single operation!)*
3.  $GCD(3, 1) \to 1$.

---

### 4. Summary for your Notes

-   **Subtraction Logic**: Based on the principle that a common divisor of two numbers must also divide their difference.
-   **Modulo Logic**: An optimized version of subtraction. It is mathematically equivalent but computationally much faster.
-   **Key Takeaway**: You can think of `a % b` as the **"Ultimate Gap"**—the smallest possible positive gap you can achieve by repeatedly subtracting $b$ from $a$.

# LCM

```cpp

class Solution {
    int GCD(int n1,int n2) {
        if(n2==0) return n1;
        return GCD(n2,n1%n2);
    }
public:
    int LCM(int n1,int n2) {
        return (n1*n2)/GCD(n1,n2);
    }
};
```

# Isprime

```cpp
class Solution{	
	bool isPrime(int n){
		if(n==1 ) return false;
		for(int i=2;i*i<=n;i++){
			if(n%i==0) return false;
		}
		return true;
	}
	public:
		bool checkPrime(int num){
			return isPrime(num);
		}
};

```



## Perfect

```cpp
bool isPrime(int n) {
    if (n <= 1) return false;
    if (n <= 3) return true;
    if (n % 2 == 0 || n % 3 == 0) return false;

    // We skip even numbers and multiples of 3
    for (int i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0)
            return false;
    }
    return true;
}
```


## How the Optimization Works

### The Mathematical Logic
Every integer can be represented as one of the following for some integer $k$:

* **$6k$**: Divisible by 6 (and 2 and 3).
* **$6k + 1$**: **Potential Prime**.
* **$6k + 2$**: Divisible by 2 (even).
* **$6k + 3$**: Divisible by 3.
* **$6k + 4$**: Divisible by 2 (even).
* **$6k + 5$**: **Potential Prime** (this is mathematically the same as $6(k+1) - 1$).

Since any number divisible by 2 or 3 is not prime (except for the numbers 2 and 3 themselves), we only need to check divisors that fall into the $6k \pm 1$ categories.



### The Loop Mechanics
In the loop `for (int i = 5; i * i <= n; i += 6)`:

* **First Iteration ($k=1$):** Checks `i` (5) and `i + 2` (7).
* **Second Iteration ($k=2$):** Checks `i` (11) and `i + 2` (13).
* **Third Iteration ($k=3$):** Checks `i` (17) and `i + 2` (19).

By jumping by 6, we skip 6, 8, 9, 10, 12, 14, 15, 16, etc., significantly reducing the number of modulo operations and improving performance.

---

## Why we use `n % i` and `n % (i + 2)`

In the **$6k \pm 1$** optimization, we use these two specific checks because they represent the only two positions in every block of six numbers that aren't already divisible by **2** or **3**.

Since our function rules out multiples of 2 and 3 at the very beginning, we only need to test `n` against other potential divisors that aren't multiples of those two numbers.

---

### 1. The "Gaps" Between Multiples of 2 and 3
If you look at any sequence of 6 numbers (a "block"), four out of those six are guaranteed to be multiples of 2 or 3. 

Let's look at the block from **6 to 11** ($k=1$):
* **6**: Divisible by 2 and 3
* **7**: **Potential Factor ($6k + 1$)** -> Checked by `i + 2`
* **8**: Divisible by 2
* **9**: Divisible by 3
* **10**: Divisible by 2
* **11**: **Potential Factor ($6k + 5$ or $6k - 1$)** -> Checked by `i`



### 2. How the Loop Maps to This
The loop starts at `i = 5` and increments by `6` each time. This allows us to check two numbers at once:

* **`n % i`**: Checks the **$6k - 1$** position (5, 11, 17, 23...).
* **`n % (i + 2)`**: Checks the **$6k + 1$** position (7, 13, 19, 25...).

### 3. Why skip the others?
We skip `i + 1`, `i + 3`, and `i + 4` because:
* `i + 1` (e.g., $5+1=6$) is a multiple of 2 and 3.
* `i + 3` (e.g., $5+3=8$) is a multiple of 2.
* `i + 4` (e.g., $5+4=9$) is a multiple of 3.

If `n` was divisible by any of these, it would have been caught by the initial `if (n % 2 == 0 || n % 3 == 0)` check. Testing them again inside the loop would be redundant.

---

### Efficiency Summary Table

| $k$ | `i` ($6k-1$) | `i + 2` ($6k+1$) | Numbers Skipped (Already ruled out) |
| :--- | :--- | :--- | :--- |
| **1** | 5 | 7 | 6, 8, 9, 10 |
| **2** | 11 | 13 | 12, 14, 15, 16 |
| **3** | 17 | 19 | 18, 20, 21, 22 |

##  When to Use This

* **One-off Primality Checks:** Use this method when you only need to check a few numbers or when the input $n$ is very large (up to $10^{14}$ for a 64-bit `long long`).
* **Range Checks (Sieve of Eratosthenes):** If you need to check primality for thousands of numbers in a range (e.g., all primes up to $10^6$), use a Sieve. It pre-computes the values so checks become $O(1)$.












