Here is a ladder for each form, easiest first. The first problem in each is the "template" problem, so start there. I'm only certain about the numbers and titles, so open each one to check the exact constraints.

## Form 1: Prefix (1D), `dp[i]` over the first `i` elements

| # | Problem | Difficulty | What the "last piece" is |
|---|---|---|---|
| 91 | Decode Ways | Medium | last 1 or 2 digits |
| 139 | Word Break | Medium | last word |
| 2369 | Check if There is a Valid Partition For The Array | Medium | last 2 or 3 elements |
| 1043 | Partition Array for Maximum Sum | Medium | last block of length <= k |
| 1105 | Filling Bookcase Shelves | Medium | last shelf |
| 132 | Palindrome Partitioning II | Hard | last palindrome |
| 1416 | Restore The Array | Hard | last number (your counting problem, on a string) |

**Start with 91.** It has only two choices per step, so you can focus on the recursion → memo flow.

## Form 2: Prefix with a part count, `dp[i][k]`

| # | Problem | Difficulty | Notes |
|---|---|---|---|
| 410 | Split Array Largest Sum | Hard | the template: min of max |
| 1335 | Minimum Difficulty of a Job Schedule | Hard | exactly d days, cost = max of each day |
| 813 | Largest Sum of Averages | Medium | at most k groups |
| 1278 | Palindrome Partitioning III | Hard | cost(j, i) needs its own precompute |
| 1478 | Allocate Mailboxes | Hard | cost(j, i) = distance to median |
| 2478 | Number of Beautiful Partitions | Hard | counting version with a size rule |

**Start with 410.** Then 813 is the same shape with a different cost.

## Form 3: Interval, split between elements, `dp[i][j]` over `k` in `[i, j-1]`

| # | Problem | Difficulty | Notes |
|---|---|---|---|
| 241 | Different Ways to Add Parentheses | Medium | split at every operator |
| 96 | Unique Binary Search Trees | Medium | split at the root |
| 1130 | Minimum Cost Tree From Leaf Values | Medium | split into left and right subtrees |
| 664 | Strange Printer | Hard | `dp[i][k] + dp[k+1][j]`, minus 1 if the ends match |
| 1000 | Minimum Cost to Merge Stones | Hard | adds a third dimension for the number of piles |
| 87 | Scramble String | Hard | 3D state `(i, j, length)` |

Matrix Chain Multiplication and Boolean Parenthesization are the classic template problems, but they are on GeeksforGeeks, not LeetCode. 241 is the closest LeetCode match to Boolean Parenthesization.

**Start with 241**, then do MCM from GfG for the pure form.

One correction to my earlier message: I listed Strange Printer under Form 4. It fits Form 3 better, because it splits between elements.

## Form 4: Interval, `k` is the last element handled

| # | Problem | Difficulty | What `k` means |
|---|---|---|---|
| 1547 | Minimum Cost to Cut a Stick | Hard | the last cut made |
| 312 | Burst Balloons | Hard | the last balloon burst |
| 375 | Guess Number Higher or Lower II | Medium | the guess you pick |
| 1039 | Minimum Score Triangulation of Polygon | Medium | the third vertex of the triangle on edge `i-j` |
| 546 | Remove Boxes | Hard | last box group, plus an extra dimension |

**Start with 375.** It is Medium and shows the "pick `k`, then solve the two sides independently" idea clearly. Then 1547 and 312 are the main event.

## Suggested order

1. **Form 1:** 91 → 139 → 1043 → 132
2. **Form 2:** 410 → 813 → 1335
3. **Form 3:** 241 → 96 → 1130 → 664
4. **Form 4:** 375 → 1547 → 312 → 1039

For each problem we do the same four steps: recursion, memoization, tabulation, optimization.


Every form is the same formula with three blanks to fill in:

```
dp[state] = BEST over choices of ( dp[smaller state(s)]  ⊕  cost of the choice )
```

- **BEST** is min, max, sum (counting), or OR (feasibility).
- **⊕** is `+`, `max`, or `*`, depending on the problem.
- **Base case** is the state with nothing left to partition.

## Form 1: Prefix (1D)

**State:** `dp[i]` = answer for the first `i` elements.

```
dp[i] = BEST over j in [0, i-1] (where piece j..i-1 is valid) of ( dp[j] ⊕ cost(j, i) )
dp[0] = base (empty prefix)          answer = dp[n]
```

```java
// recursion (prefix version: last piece is a[j..i-1])
long f(int i) {
    if (i == 0) return BASE;
    long best = INVALID;
    for (int j = i - 1; j >= 0; j--) {
        if (!valid(j, i)) continue;
        best = better(best, combine(f(j), cost(j, i)));
    }
    return best;
}
// memo: add memo[i] check and save. Tabulation: for i = 1..n, same loops with dp[j].
```

**Loop order:** `i` increasing. **Time:** O(n²), or O(n) with a sliding window or running max.

## Form 2: Prefix with part count (2D)

**State:** `dp[i][c]` = answer for the first `i` elements using exactly `c` parts.

```
dp[i][c] = BEST over j in [c-1, i-1] of ( dp[j][c-1] ⊕ cost(j, i) )
dp[0][0] = base, every other dp[0][*] and dp[*][0] (i>0) = INVALID
answer = dp[n][K]
```

```java
long f(int i, int c) {
    if (c == 0) return i == 0 ? BASE : INVALID;
    if (i == 0) return INVALID;
    long best = INVALID;
    for (int j = i - 1; j >= 0; j--)
        best = better(best, combine(f(j, c - 1), cost(j, i)));
    return best;
}
```

**Loop order:** `c` outer (1..K), `i` inner (increasing). **Time:** O(n²·K). **Common optimizations:** binary search on the answer (410), divide-and-conquer optimization, or a rolling 1D array since layer `c` only reads layer `c-1`.

## Form 3: Interval, split between elements

**State:** `dp[i][j]` = answer for the range `i..j`.

```
dp[i][j] = BEST over k in [i, j-1] of ( dp[i][k] ⊕ dp[k+1][j] ⊕ merge(i, k, j) )
dp[i][i] = base (single element)     answer = dp[0][n-1]
```

```java
long f(int i, int j) {
    if (i == j) return BASE;
    if (memo[i][j] != UNSET) return memo[i][j];
    long best = INVALID;
    for (int k = i; k < j; k++)
        best = better(best, combine(f(i, k), f(k + 1, j), merge(i, k, j)));
    return memo[i][j] = best;
}

// tabulation: shorter ranges first
for (int len = 2; len <= n; len++)
    for (int i = 0; i + len - 1 < n; i++) {
        int j = i + len - 1;
        dp[i][j] = INVALID;
        for (int k = i; k < j; k++)
            dp[i][j] = better(dp[i][j], combine(dp[i][k], dp[k + 1][j], merge(i, k, j)));
    }
```

**Loop order:** by increasing length (or `i` descending, `j` ascending). **Time:** O(n³). **Example:** MCM, where `merge = arr[i-1]*arr[k]*arr[j]`.

## Form 4: Interval, `k` is the last element handled

**State:** `dp[i][j]` = answer for the range `i..j`, with the neighbors outside it fixed.

```
dp[i][j] = BEST over k in [i, j] of ( dp[i][k-1] ⊕ dp[k+1][j] ⊕ value(i, k, j) )
dp[i][j] = 0 when i > j (empty range)     answer = dp[0][n-1] (or dp[1][n] after padding)
```

```java
long f(int i, int j) {
    if (i > j) return 0;                       // empty range
    if (memo[i][j] != UNSET) return memo[i][j];
    long best = INVALID;
    for (int k = i; k <= j; k++)               // k is the LAST one handled
        best = better(best, combine(f(i, k - 1), f(k + 1, j), value(i, k, j)));
    return memo[i][j] = best;
}
```

`value(i, k, j)` is what `k` costs or earns when everything else in `i..j` is already gone, so it depends on the fixed borders. For Burst Balloons it is `a[i-1] * a[k] * a[j+1]`, with `a` padded by 1 on both ends.

**Loop order:** by increasing length, same as Form 3. **Time:** O(n³).

## Side-by-side

| | State | Choice | Base | Fill order | Time |
|---|---|---|---|---|---|
| 1 | `dp[i]` | start `j` of last piece | `dp[0]` | `i` up | O(n²) |
| 2 | `dp[i][c]` | start `j` of last piece | `dp[0][0]` | `c`, then `i` up | O(n²K) |
| 3 | `dp[i][j]` | split `k` between `k` and `k+1` | `dp[i][i]` | length up | O(n³) |
| 4 | `dp[i][j]` | last element `k` handled | `dp[i][j]=0` if `i>j` | length up | O(n³) |

## Three questions to fill in the blanks

1. **State:** what does the smaller problem look like (a prefix, a prefix plus a count, or a range)?
2. **Choice:** what am I trying, a start, a split, or the last element?
3. **Combine:** how do I merge the sub-answers with the cost of my choice (`+`, `max`, `*`, count)?

## Two traps shared by all forms

- **Two markers.** Use `UNSET` for "not computed yet" and `INVALID` (or `NEG`) for "computed, impossible", otherwise impossible states get recomputed or leak into the answer.
- **Form 3 vs Form 4.** If the two sides still depend on each other after the cut (as in Burst Balloons, where neighbors change), "split between" fails. Switch to "last one handled" so the neighbors stay fixed.

Say "start" and we'll begin with LeetCode 91 (Decode Ways) using Form 1: recursion first, then memo.