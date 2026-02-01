
### Rolling Hash Overview

A **Rolling Hash** is a hashing technique that allows you to calculate the hash of a "sliding window" (like a substring) in **$O(1)$ constant time** by using the hash of the previous window.

Without a rolling hash, if you wanted to hash every substring of length $L$ in a string of length $N$, it would take $O(N \times L)$. With a rolling hash, it takes only **$O(N)$**.

---

### 1. The "Physics" of the Math
Imagine a string as a number in a specific **base** (usually a prime number larger than the alphabet size, like 31 or 53).

To move the window from `abcd` to `bcde`:
1.  **Remove** the first character (`a`).
2.  **Shift** the remaining value (`bcd`) to the left (multiply by the base).
3.  **Add** the new character (`e`).

### 2. The Formula
To compute the hash $H$ of a string $S$ of length $n$:
$$H = (S[0] \cdot P^{n-1} + S[1] \cdot P^{n-2} + \dots + S[n-1] \cdot P^0) \pmod M$$

formula is your wish  

* $P$: A prime base (e.g., 31 for lowercase English).
* $M$: A large prime modulo (e.g., $10^9 + 7$) to prevent overflow and reduce collisions.

---

### 3. Why is it useful? (The Rabin-Karp Algorithm)
Rolling hashes are most famously used in the **Rabin-Karp** string matching algorithm. If you are looking for a pattern $P$ in a long text $T$:

1.  Calculate the hash of $P$.
2.  Slide a window across $T$, calculating the rolling hash of the current window.
3.  If the hashes match, you've likely found the pattern (you then do a quick character check to be 100% sure).

# Rabin Karp

```cpp
vector<int> search(string pat, string txt) {
    int n = pat.length(), m = txt.length();
    if (n > m) return {};

    long long p = 31, mod = 1e9 + 7;
    long long hashPat = 0, hashText = 0, h = 1;

    // Precompute h = p^(n-1) % mod
    for (int i = 0; i < n - 1; i++) h = (h * p) % mod;

    // Initial hashes
    for (int i = 0; i < n; i++) {
        hashPat = (p * hashPat + (pat[i] - 'a' + 1)) % mod;
        hashText = (p * hashText + (txt[i] - 'a' + 1)) % mod;
    }

    vector<int> ans;
    for (int i = 0; i <= m - n; i++) {
        if (hashPat == hashText) {
            if (txt.substr(i, n) == pat) ans.push_back(i);
        }

        if (i < m - n) {
            // Standard Rolling: Remove leading, shift, add trailing
            hashText = (p * (hashText - (txt[i] - 'a' + 1) * h) + (txt[i + n] - 'a' + 1)) % mod;
            if (hashText < 0) hashText += mod;
        }
    }
    return ans;
}

```


See this 

```cpp
    for (int i = 0; i < n; i++) {
        hashPat = (p * hashPat + (pat[i] - 'a' + 1)) % mod;
        hashText = (p * hashText + (txt[i] - 'a' + 1)) % mod;
    }
```

abc is string pattern 

hashpat=0 initial

so i=0 hahspat=0*p+a

i=1 hashpat= p*hashpat + b = p*a +b

i=2 hahspat= p* (p*a+b)+c= p*p*a +p*b +c

suppose text is defg so  hashText=p*p*d+p*e+f

now we want to remove d hashtext- p*p*d  so that p*p* d is in h 

### Verification: Your Derivation is Correct

You are absolutely correct. You have effectively derived the formula for `h` yourself. Your logic holds up perfectly.

#### 1. The Derivation
* **Observation:** You found that the leading term (the first character `d`) is multiplied by $p$ twice: $p^2 \cdot d$.
* **Action:** To remove `d`, you rightly identified that you need to subtract $d \times p^2$.
* **Conclusion:** This means your precomputed value `h` must be equal to $p^2$.

**General Rule:** For a pattern of length $m$, the leading character is always multiplied by $P^{m-1}$. Therefore:
$$h = P^{m-1}$$

---

#### 2. The Full "Rolling" Math (Example: "def" $\to$ "efg")

Let's trace the math of moving the window from **"def"** to **"efg"**.

**Step 1: Start (Window "def")**
$$H_{old} = d \cdot p^2 + e \cdot p + f$$

**Step 2: Remove Leading 'd'**
We subtract $(d \times h)$ where $h = p^2$.
$$Temp = H_{old} - (d \cdot p^2)$$
$$Temp = (d \cdot p^2 + e \cdot p + f) - (d \cdot p^2) = e \cdot p + f$$

**Step 3: Shift Left (Multiply by p)**
$$Temp \times p = (e \cdot p + f) \times p = e \cdot p^2 + f \cdot p$$
*(Notice how 'e' has now moved to the highest spot, $p^2$)*

**Step 4: Add New 'g'**
$$H_{new} = (e \cdot p^2 + f \cdot p) + g$$

**Result:**
$$H_{new} = e \cdot p^2 + f \cdot p + g$$
This matches the formula for **"efg"** perfectly.

---

#### 3. Summary
* **Pattern Length:** $m = 3$
* **Highest Power:** $p^{m-1} = p^2$
* **Value of `h`:** $p^2$

### Rabin-Karp Dry Run: "abcdefgh" vs "cde"

#### 1. The Hash Function Used
We are using the **Polynomial Rolling Hash**.

* **Formula:** $H = (C_0 \cdot P^{m-1} + C_1 \cdot P^{m-2} + \dots + C_{m-1} \cdot P^0) \pmod M$
* **Physics:** Treat the string like a number in base $P$.
    * 'a' = 1, 'b' = 2, 'c' = 3, 'd' = 4, 'e' = 5 ...
    * **Base ($P$):** 31
    * **Modulo ($M$):** Ignored for simplicity (assume values don't overflow).

#### 2. The Setup
* **Text (`txt`):** `"abcdefgh"` ($N=8$)
* **Pattern (`pat`):** `"cde"` ($M=3$)
* **Multiplier (`h`):** $P^{M-1} = 31^{3-1} = 31^2 = \mathbf{961}$.

---

#### 3. Step-by-Step Dry Run

**Step A: Calculate Initial Hashes**

* **Pattern Hash (`pat`: "cde"):**
    * Calculation: $3 \cdot 31^2 + 4 \cdot 31^1 + 5 \cdot 31^0$
    * Math: $3(961) + 4(31) + 5 = 2883 + 124 + 5$
    * **`hashPat` = 3012**

* **First Text Window (`txt[0...2]`: "abc"):**
    * Calculation: $1 \cdot 31^2 + 2 \cdot 31^1 + 3 \cdot 31^0$
    * Math: $1(961) + 2(31) + 3 = 961 + 62 + 3$
    * **`hashText` = 1026**

---

**Step B: The Sliding Loop**

* **Iteration `i = 0` (Window: "abc")**
    1.  **Compare:** Is `hashText` (1026) == `hashPat` (3012)? **No.**
    2.  **Roll (Move Window Right):**
        * We need to move from **"abc"** $\to$ **"bcd"**.
        * **Remove Leading ('a'=1):** $1026 - (1 \cdot 961) = 65$
        * **Shift Left (Multiply by 31):** $65 \cdot 31 = 2015$
        * **Add Trailing ('d'=4):** $2015 + 4 = 2019$
        * **New `hashText` = 2019**

* **Iteration `i = 1` (Window: "bcd")**
    1.  **Compare:** Is `hashText` (2019) == `hashPat` (3012)? **No.**
    2.  **Roll (Move Window Right):**
        * We need to move from **"bcd"** $\to$ **"cde"**.
        * **Remove Leading ('b'=2):** $2019 - (2 \cdot 961) = 2019 - 1922 = 97$
        * **Shift Left (Multiply by 31):** $97 \cdot 31 = 3007$
        * **Add Trailing ('e'=5):** $3007 + 5 = 3012$
        * **New `hashText` = 3012**

* **Iteration `i = 2` (Window: "cde")**
    1.  **Compare:** Is `hashText` (3012) == `hashPat` (3012)? **YES!**
    2.  **Verify:** `txt.substr(2, 3)` is "cde". Matches `pat`.
    3.  **Result:** Found match at **index 2**.

---

#### Summary of the "Rolling" Physics
Notice how we transformed "abc" (1026) to "bcd" (2019) using only math, without re-scanning the string.

1.  **Current Value:** `[1, 2, 3]` (base 31)
2.  **Subtract High:** `[0, 2, 3]`
3.  **Shift Left:** `[2, 3, 0]`
4.  **Add Low:** `[2, 3, 4]`

This $O(1)$ update is why Rabin-Karp is fast.

