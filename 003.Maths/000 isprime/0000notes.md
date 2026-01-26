# Basic

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












