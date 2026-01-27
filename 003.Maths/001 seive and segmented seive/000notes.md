# Notes
## Prime Till N

![img_1.png](img_1.png)

### Brute 

For each number check isprime or not

```cpp
#include <bits/stdc++.h>
using namespace std;

class Solution {
private:
    bool isPrime(int n) {
        int count = 0;
      
        for(int i = 1; i <= sqrt(n); ++i) {
            if(n % i == 0) {

                count = count + 1;
                if(n / i != i) {
                    count = count + 1;
                }
            }
        }

        if(count == 2) return true;

        return false;
    }
    
public:
    vector<int> primeTillN(int n){
        vector<int> primes;
        for (int i = 2; i <= n; i++) {
            if (isPrime(i)){
                primes.push_back(i);
            }
        }
        return primes;
    }
};

int main() {
    int n = 7;
    
    /* Creating an instance of 
    Solution class */
    Solution sol; 
    
    // Function call to get all primes till N
    vector<int> ans = sol.primeTillN(n);
    
    cout << "All primes till N are: " << endl;
    for(int i=0; i < ans.size(); i++) {
        cout << ans[i] << " ";
    }
    
    return 0;
}

```
### seive

```cpp

class Solution{
    public:
vector<int> primeTillN(int n) {
    vector<bool> isPrime(n + 1, true); 
    isPrime[0] = isPrime[1] = false;

    // Phase 1: Marking
    for(long long i = 2; i * i <= n; i++) {
        if(isPrime[i]) {
            for(long long val = i * i; val <= n; val += i) {
                isPrime[val] = false;
            }
        }
    } 

    // Phase 2: Collecting ALL primes up to n
    vector<int> ans;
    for(int i = 2; i <= n; i++) {
        if(isPrime[i]) ans.push_back(i);
    }
    return ans;
}
};

```

# Proof: Every Composite Number $C$ has a Prime Factor $p \le \sqrt{C}$

The efficiency of the **Sieve of Eratosthenes** is based on this mathematical property, which allows us to stop the marking process once the outer loop reaches $\sqrt{n}$.

---

### The Proof by Contradiction

1.  **Definition of a Composite Number**: Let $C$ be a composite number. By definition, it can be factored into two integers $a$ and $b$ such that $C = a \times b$, where $1 < a \le b < C$.
2.  **The Assumption**: Assume for the sake of contradiction that **both** factors are strictly greater than the square root of $C$:
    * $a > \sqrt{C}$
    * $b > \sqrt{C}$
3.  **The Multiplication**: If we multiply these two inequalities together:
    * $a \times b > \sqrt{C} \times \sqrt{C}$
    * $a \times b > C$
4.  **The Contradiction**: We started with the definition $a \times b = C$, but our assumption led us to $a \times b > C$. This is a mathematical contradiction.
5.  **Conclusion**: At least one of the factors must be less than or equal to $\sqrt{C}$ (i.e., $a \le \sqrt{C}$). Since any factor is either a prime or has prime factors of its own, $C$ must have a prime factor $p$ such that $p \le \sqrt{C}$.

---

### Why This Matters for DSA Interviews

* **Sieve Optimization**: This proof justifies why the outer loop of the sieve only needs to run while $i \times i \le n$.
* **Complete Marking**: By the time $i$ reaches $\sqrt{n}$, every composite number up to $n$ has already been marked by its smallest prime factor.
* **Complexity**: This logic is crucial for maintaining the $O(N \log \log N)$ time complexity required to handle up to $10^5$ queries efficiently.
* **Range Queries**: For range $[L, R]$, this precomputation allows for a **Prefix Sum** array that answers each query in $O(1)$ time.

---

# Optimization: Why the Inner Loop Starts at $i \times i$

In the **Sieve of Eratosthenes**, starting the inner loop at $i^2$ (or $i \times i$) is a critical optimization that prevents redundant operations and ensures each composite number is marked efficiently.

---

### 1. Avoiding Redundant Marking
For any prime number $i$, its multiples are:  
$2i, 3i, 4i, \dots, (i-1)i, i^2, (i+1)i, \dots$

* When the algorithm reaches prime $i$, all multiples of $i$ that are smaller than $i^2$ have **already been marked** as non-prime by primes smaller than $i$.
* **Example for $i = 5$:**
    * $2 \times 5 = 10$: Already marked by prime **2**.
    * $3 \times 5 = 15$: Already marked by prime **3**.
    * $4 \times 5 = 20$: Already marked by prime **2**.
    * The first multiple that has not been "sieved" yet is **$5 \times 5 = 25$**.

---

### 2. Connection to Outer Loop Limit
This optimization explains why the outer loop only needs to run while $i^2 \le n$:
* If $i^2 > n$, the inner loop (starting at $i^2$) would not execute a single time because the starting value already exceeds the limit $n$.
* Once $i$ exceeds $\sqrt{n}$, every composite number in the range has already been marked by at least one of its prime factors.

---

### 3. Impact on Complexity
* **Efficiency:** Starting at $i^2$ significantly reduces the number of inner-loop iterations, especially as $i$ increases.
* **Performance:** It is a key factor in maintaining the **$O(N \log \log N)$** time complexity.
* **Practicality:** This efficiency is necessary to precompute primes up to $10^6$ and answer $10^5$ queries using the **Prefix Sum** method.

---

### Summary for Interviews
> "We start the inner loop at $i^2$ because any multiple $k \times i$ (where $k < i$) would have already been marked by the prime factors of $k$. This avoids redundant work and allows us to handle large constraints like $10^6$ in near-linear time."

---
# Time Complexity Analysis: Sieve of Eratosthenes

The time complexity of the **Sieve of Eratosthenes** is **$O(N \log \log N)$**. While the nested loops might look like $O(N^2)$, the total work is much lower because the inner loop only runs for prime numbers.

---

### 1. The Summation of Work
The total number of operations is determined by how many times we mark numbers as "not prime" in the inner loop:
* For the prime **2**, we perform $N/2$ operations.
* For the prime **3**, we perform $N/3$ operations.
* For the prime **5**, we perform $N/5$ operations.
* This continues for all primes $p$ where $p \le \sqrt{N}$.

The total complexity is the sum of these operations:
$$Total\ Operations = N \times \left( \frac{1}{2} + \frac{1}{3} + \frac{1}{5} + \frac{1}{7} + \dots + \frac{1}{p} \right)$$

---

### 2. Mertens' Second Theorem
In mathematics, the sum of the reciprocals of prime numbers up to $N$ follows a specific growth pattern:
* The series $\sum_{p \le N} \frac{1}{p}$ is approximately equal to $\log(\log N)$.
* By multiplying this by the factor of $N$ from our outer loop, we arrive at the final complexity: **$O(N \log \log N)$**.

---

### 3. Practical Efficiency
The $\log \log N$ factor grows extremely slowly, making the algorithm nearly linear:
* **Slow Growth:** For $N = 10^6$ (the limit for this problem), $\log_2(10^6) \approx 20$, and $\log_2(20) \approx 4.3$.
* **Performance:** This near-linear performance is what makes the Sieve ideal for precomputing primes up to $10^6$ to handle $10^5$ queries.

---

### Summary for Interviews
> "The Sieve of Eratosthenes is $O(N \log \log N)$ because the inner loop runs $N/p$ times only for prime values of $p$. The sum of the reciprocals of primes converges to $\log \log N$, making this algorithm highly efficient for large constraints like $10^6$."

### Optimal

previously after marking prime we pushing into array but here we mark and on that prime number ,if nobody ahs marked that we push to ans


```cpp
class Solution {
public:
    vector<int> primeTillN(int n) {
        vector<bool> isPrime(n+1, true); 
        vector<int> ans;
        for(long long i=2; i <= n; i++) {
            if(isPrime[i]) {
                ans.push_back(i);
                for(long long val = i*i; val <= n; val += i) {
                    isPrime[val] = false;
                }
            }
        }  
        return ans;
    }
};

```



![img.png](img.png)

```cpp
//https://www.spoj.com/problems/TDPRIMES/
#include<bits/stdc++.h>
using namespace std;
int size=(int)1e8;
bool seive[(int)1e8];
void fio()
{
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    #ifndef ONLINE_JUDGE
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
    #endif
}
void seiveSol(){
   memset(seive,true,size);
    seive[0]=seive[1]=false;
    for(int i=2;i*i<=size;i++){
        if(seive[i]==true){
            for(int j=i*i;j<size;j+=i){
                seive[j]=false;
            }
        }
    }
    vector<int>prime;
    int cnt=1;
    for(int i=2;i<size;i++){
        if(seive[i]==true) {
            if(cnt%100==1){
                cout<<i<<endl;
            }
            cnt++;
        }
    }
}

int main(int argc, char const *argv[]) {
    fio();
    seiveSol();
    return 0;
}


```

# Count Primes in Range L to R

---

### Problem Statement
You are given a 2D array `queries` of dimension `n * 2`. Each entry `queries[i]` represents a range from `queries[i][0]` to `queries[i][1]` (inclusive of the endpoints).

Your task is to return an array containing the count of prime numbers present in each given range.

---

### Examples

#### Example 1
**Input:** `queries = [[2, 5], [4, 7]]`  
**Output:** `[3, 2]`  
**Explanation:** * The range 2 to 5 contains three prime numbers: 2, 3, 5.
* The range 4 to 7 contains two prime numbers: 5, 7.

#### Example 2
**Input:** `queries = [[1, 7], [3, 7]]`  
**Output:** `[4, 3]`  
**Explanation:** * The range 1 to 7 contains four prime numbers: 2, 3, 5, 7.
* The range 3 to 7 contains three prime numbers: 3, 5, 7.

---

### Constraints
* $1 \le n \le 10^5$
* $1 \le queries[i][0] \le queries[i][1] \le 10^6$

## Solution

```cpp

class Solution{
     vector<int>isPrime;
    void primeTillN() {
        isPrime[0]=isPrime[1]=0;
        for(long long i=2; i*i < 100001; i++) {
            if(isPrime[i]==1) {
                for(int val = i*i; val < 100001; val += i) {
                    isPrime[val] = 0;
                }
            }
        }  

    }
    void prefixSum(){
        for(int i=1;i<100001;i++){
            isPrime[i]+=isPrime[i-1];
        }
    }
    public:
        vector<int> primesInRange(vector<vector<int>>& queries){
            isPrime.resize(100001, 1); 
            primeTillN();
            prefixSum();
            vector<int> ans;
            for( auto q:queries){
                int l=q[0];
                int r=q[1];
                if (l == 0) ans.push_back(isPrime[r]);
                else ans.push_back(isPrime[r] - isPrime[l - 1]);
            }
            return ans;
        }
};
```
## Bitset seive

```cpp
#include <iostream>
#include <bitset>
#include <vector>

using namespace std;

// Bitset must have a size known at compile time
const int MAX_N = 1000000; 
bitset<MAX_N + 1> isPrime; 

void sieveByBitset() {
    // 1. Initialize: bitset starts with all 0s. 
    // We'll treat 1 as Prime and 0 as Not Prime.
    isPrime.set(); // Sets all bits to 1
    
    isPrime[0] = isPrime[1] = 0; // 0 and 1 are not prime

    for (long long i = 2; i * i <= MAX_N; i++) {
        if (isPrime.test(i)) { // Equivalent to isPrime[i] == 1
            for (long long val = i * i; val <= MAX_N; val += i) {
                isPrime.reset(val); // Sets bit to 0 (Not Prime)
            }
        }
    }
}

int main() {
    sieveByBitset();
    cout << "Is 7 prime? " << isPrime[7] << endl;
    cout << "Is 10 prime? " << isPrime[10] << endl;
}
```
###  Comparison Table

| Feature | `vector<int>` | `vector<bool>` | `std::bitset` |
| :--- | :--- | :--- | :--- |
| **Memory per element** | 32 bits (4 bytes) | ~1 bit (implementation dependent) | **Exactly 1 bit** |
| **Memory for $10^6$** | ~4,000 KB | ~125 KB | **~125 KB** |
| **Speed** | Standard | Slower (due to bit-packing) | **Fastest** |
| **Size flexibility** | Dynamic (Runtime) | Dynamic (Runtime) | **Static (Compile-time)** |

---

### Why use Bitset for "Primes in Range L to R"?

The problem has a limit of $10^6$.
* Using `int isPrime[1000001]` takes **4 MB**.
* Using `bitset<1000001>` takes **125 KB**.

In an interview, if you are asked to handle $10^7$ or $10^8$ range queries, a standard `int` array might hit **Memory Limit Exceeded (MLE)**, while a `bitset` will pass easily.

---

### Summary for an Interviewer

> "I used `std::bitset` to optimize the space complexity. Since we only need a true/false flag, a bitset allows us to store each flag in exactly 1 bit. This makes the sieve significantly more cache-friendly and reduces the memory footprint by 32x compared to a standard integer array."

### Memory Limits and Data Structure Selection

| Data Structure | Size (N) for 256MB Limit | Memory per Element |
| :--- | :--- | :--- |
| `vector<int>` | ~64 Million | 4 Bytes |
| `vector<long long>` | ~32 Million | 8 Bytes |
| `vector<bool>` | ~2 Billion | ~1 Bit |
| `std::bitset<N>` | ~2 Billion | **Exactly 1 Bit** |

---

### When to use `std::bitset`
1. **Size is Fixed:** Known at compile time (e.g., `const int MAX = 1e6`).
2. **Global Declaration:** Always declare large bitsets globally to avoid **Stack Overflow**.
3. **Speed:** Bitset is significantly faster for operations like counting set bits (`.count()`) or checking if any bits are set (`.any()`).
4. **Cache Efficiency:** Its compact nature makes it highly cache-friendly for algorithms like the Sieve.


### Key Constraints for `bitset` vs `vector`

* **Static vs. Dynamic Allocation:**
    * `bitset<1000000> b;` declared inside a function is stored on the **Stack**. Since the stack is usually limited (often 1MB to 8MB depending on the system), declaring a massive bitset locally will likely cause a **Stack Overflow**.
    * **The Fix:** Always declare large bitsets as **global variables** or use the `static` keyword. This moves the data to the **Data Segment**, which has a much larger capacity than the stack.

* **Runtime Input:**
    * A `std::bitset` requires its size to be a `constexpr` (known at compile time). If the size $N$ is provided by the user at runtime (e.g., `cin >> n;`), you **cannot** use `std::bitset`.
    * **The Fix:** In cases where the size is dynamic, you must use `vector<bool>` or `boost::dynamic_bitset`.

---

### Summary for an Interviewer

> "While `std::bitset` is highly efficient, it has two main constraints: it requires a compile-time constant for its size, and it is stack-allocated by default. To safely use a large bitset for a Sieve, I declare it globally to avoid stack overflow and ensure the size is predefined based on the problem's maximum constraints."

# Bitset operations

```cpp
#include <iostream>
#include <bitset>
#include <string>

using namespace std;

int main() {
    // 1. Initialization
    // Size must be a compile-time constant
    bitset<8> b1;               // [0,0,0,0,0,0,0,0] - initialized to 0s
    bitset<8> b2(42);           // [0,0,1,0,1,0,1,0] - from integer
    bitset<8> b3("1100");       // [0,0,0,0,1,1,0,0] - from string (starts from right)

    cout << "Initial b2 (42): " << b2 << endl;

    // 2. Individual Bit Manipulation
    b1[0] = 1;                  // Set bit at index 0 using array notation
    b1.set(1);                  // Set bit at index 1 to 1
    b1.set(2, 0);               // Set bit at index 2 to 0
    b1.reset(1);                // Reset bit at index 1 to 0
    b1.flip(7);                 // Toggle bit at index 7

    cout << "Modified b1: " << b1 << endl;

    // 3. Status Checks
    cout << "Is any bit set in b2? " << b2.any() << endl;
    cout << "Are all bits set in b2? " << b2.all() << endl;
    cout << "Are no bits set in b2? " << b2.none() << endl;
    cout << "How many bits are set? " << b2.count() << endl;
    cout << "Value of bit at index 3: " << b2.test(3) << endl; // Safe access with range check

    // 4. Bulk Operations
    b1.set();                   // Sets ALL bits to 1
    b1.reset();                 // Sets ALL bits to 0
    b1.flip();                  // Flips ALL bits

    // 5. Bitwise Operations (Works like integers)
    bitset<8> mask1("11110000");
    bitset<8> mask2("10101010");

    cout << "AND: " << (mask1 & mask2) << endl;
    cout << "OR:  " << (mask1 | mask2) << endl;
    cout << "XOR: " << (mask1 ^ mask2) << endl;
    cout << "NOT: " << (~mask1) << endl;
    cout << "Shift Left: " << (mask1 << 2) << endl;

    // 6. Conversion
    unsigned long ulongVal = b2.to_ulong();
    string strVal = b2.to_string();
    
    cout << "As Ulong: " << ulongVal << endl;
    cout << "As String: " << strVal << endl;

    // 7. Large Bitset Example (Global/Static Segment)
    static bitset<1000000> largeSieve; // 1 million bits
    largeSieve.set();
    cout << "Large Bitset size in bytes: " << sizeof(largeSieve) << " bytes" << endl;

    return 0;
}
```

# Segmented seive

## Myversion

```cpp

#include<bits/stdc++.h>
using namespace std;
int size=(int)1e5;
bool seive[(int)1e5];
void fio()
{
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    #ifndef ONLINE_JUDGE
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
    #endif
}
vector<int>prime;
void seiveSol(){
   memset(seive,true,size);
    seive[0]=seive[1]=false;
    for(int i=2;i*i<=size;i++){
        if(seive[i]==true){
            for(int j=i*i;j<size;j+=i){
                seive[j]=false;
            }
        }
    }

    for(int i=2;i<size;i++){
        if(seive[i]==true) {
           prime.push_back(i);
        }
    }
}
void segmentedSeive(int m,int n){
    bool dummy[n-m+1];
    memset(dummy,true,n-m+1);
    if(m==1) dummy[0]=false;
    for(auto pr:prime){
        int firstMultiple=(m/pr)*pr;
        if(firstMultiple<m) firstMultiple+=pr;
        firstMultiple=max(firstMultiple,pr*pr);
        if(firstMultiple>n) break;
        for(int i=firstMultiple;i<=n;i+=pr){
            if(dummy[i-m]==true) dummy[i-m]=false;
        }
    }
    for(int i=m;i<=n;i++){
        if(dummy[i-m]==true){
            cout<<i<<endl;
        }
    }
}
void solve(){
    int tc;
    cin>>tc;
    seiveSol();
    for(int t=0;t<tc;t++){
        int l,r;
        cin>>l>>r;
        segmentedSeive(l,r);
        cout<<endl;
    }
}

int main(int argc, char const *argv[]) {
    fio();
    solve();
    return 0;
}

```


### Bugs 

### 1. The `firstMultiple` Logic Fix
Your current logic:
```cpp
firstMultiple = max(firstMultiple, pr * pr);
```
While pr * pr is a great optimization for the Simple Sieve, in the Segmented Sieve, it can cause an integer overflow if pr is around $10^6$ (because $10^6 \times 10^6 = 10^{12}$, which exceeds the capacity of a 32-bit int).

Better way:Only start at pr * pr if $pr \times pr \le n$. Otherwise, you might overflow or skip the range entirely. Also, ensure you use long long for all calculations involving numbers up to $10^{12}$ to avoid wrapping around.


2. Variable Length Arrays (VLA)
```C++
bool dummy[n - m + 1]; // Potential Stack Overflow
```

In C++, declaring a large array inside a function puts it on the Stack. The stack is a very limited memory region (usually 1MB to 8MB). If $n - m + 1$ is $10^6$, this takes significant space; if you have multiple recursive calls or even tighter limits, your program will crash.The Fix: Use vector<bool> dummy(n - m + 1, true);. This stores the data on the Heap, which is much larger and safer for arrays of this size.

### Why `vector<bool>` is safer than `bool dummy[N]`

1.  **Memory Location (Heap vs. Stack)**: 
    * Standard arrays are allocated on the **Stack**, which is very small (usually 1MB–8MB). Large sieves will cause a **Stack Overflow**.
    * `vector` data is stored on the **Heap**, which can handle hundreds of megabytes safely.

2.  **Bit-Packing Optimization**: 
    * C++ optimizes `vector<bool>` to use only **1 bit per element**. 
    * A standard `bool` array uses **8 bits (1 byte) per element**. 
    * This makes `vector<bool>` **8 times more memory-efficient**, allowing you to handle much larger ranges within the same memory limit.

3.  **Dynamic Sizing**: 
    * Standard C++ does not officially support Variable Length Arrays (VLAs) like `bool arr[n]`. Using them is "undefined behavior" in many compilers. 
    * `vector` is the official, safe way to handle arrays where the size is only known at runtime.

3. The memset Size Bug

```C++
memset(seive, true, size); 
```
memset works on bytes, not elements. It fills each byte of memory with the specified value. Since a bool in C++ is typically 1 byte, this happens to work in your specific case. However, if you ever changed seive to an int array (where an int is 4 bytes), memset would fill each individual byte of the integer, resulting in a corrupted value like 16843009 instead of 1.

Better way: Use fill(seive, seive + size, true); or seive.assign(size, true);. these are type-safe and work correctly regardless of the data type.

### Why `resize()` is not a substitute for `fill()` or `assign()`

* **The Problem:** `vector::resize(n, value)` only applies the `value` to **newly** added elements. If the vector is already size `n` or larger, the existing elements remain unchanged.
* **The Risk:** In a Sieve implementation used across multiple test cases, `resize()` will fail to reset previous "false" (not prime) entries back to "true".

**Correct Alternatives:**
1.  **`v.assign(size, true)`**: Resizes the vector AND sets every single element to `true`. This is the most robust method for vectors.
2.  **`fill(v.begin(), v.end(), true)`**: Leaves the size as is but overwrites every current element with `true`.
3.  **`v = vector<bool>(size, true)`**: Creates a brand new vector and replaces the old one (clean but slightly more overhead).

## Ai version

```cpp
#include <bits/stdc++.h>
using namespace std;

// Use long long for ranges up to 10^12
typedef long long ll;

const int MAX_SQRT = 100001; 
bool sieve[MAX_SQRT];
vector<int> primes;

void sieveSol() {
    fill(sieve, sieve + MAX_SQRT, true);
    sieve[0] = sieve[1] = false;
    for (ll i = 2; i * i < MAX_SQRT; i++) {
        if (sieve[i]) {
            for (ll j = i * i; j < MAX_SQRT; j += i)
                sieve[j] = false;
        }
    }
    for (int i = 2; i < MAX_SQRT; i++) {
        if (sieve[i]) primes.push_back(i);
    }
}

void segmentedSieve(ll m, ll n) {
    // Use vector to allocate on HEAP, not stack
    vector<bool> dummy(n - m + 1, true);
    
    if (m == 1) dummy[0] = false;

    for (int pr : primes) {
        // Optimization: if pr*pr > n, no more multiples to mark
        if ((ll)pr * pr > n) break;

        // Find first multiple of pr >= m
        ll firstMultiple = (m / pr) * pr;
        if (firstMultiple < m) firstMultiple += pr;

        // Ensure we don't mark the prime itself
        // (e.g., if m=2, pr=2, don't mark 2 as false)
        for (ll j = max((ll)pr * pr, firstMultiple); j <= n; j += pr) {
            dummy[j - m] = false;
        }
    }

    for (ll i = m; i <= n; i++) {
        if (dummy[i - m]) cout << i << "\n";
    }
}

void solve() {
    sieveSol(); // Precompute primes once
    int tc;
    if (!(cin >> tc)) return;
    while (tc--) {
        ll l, r;
        cin >> l >> r;
        segmentedSieve(l, r);
        if (tc > 0) cout << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    solve();
    return 0;
}
```