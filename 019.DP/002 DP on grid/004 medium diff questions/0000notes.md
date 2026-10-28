
# Q1 Minimum XOR Path in a Grid

You are given an `m x n` integer matrix `grid`.

You start at the top-left cell `(0, 0)` and want to reach the bottom-right cell `(m - 1, n - 1)`. At each step, you can only move either **down** or **right**.

The **XOR value** of a path is the bitwise XOR of all the values of the cells visited along the path (including both the start and end cells).

Return the **minimum XOR value** of a path from `(0, 0)` to `(m - 1, n - 1)`.

---

### Examples

**Example 1:**
- **Input:** `grid = [[1, 2], [3, 4]]`
- **Output:** `6`
- **Explanation:**
  There are two valid paths from `(0, 0)` to `(1, 1)`:
  1. `(0, 0) -> (0, 1) -> (1, 1)` with XOR: `1 ^ 2 ^ 4 = 7`
  2. `(0, 0) -> (1, 0) -> (1, 1)` with XOR: `1 ^ 3 ^ 4 = 6`
  The minimum XOR value among all valid paths is `6`.

**Example 2:**
- **Input:** `grid = [[6, 7], [5, 8]]`
- **Output:** `9`
- **Explanation:**
  There are two valid paths from `(0, 0)` to `(1, 1)`:
  1. `(0, 0) -> (0, 1) -> (1, 1)` with XOR: `6 ^ 7 ^ 8 = 9`
  2. `(0, 0) -> (1, 0) -> (1, 1)` with XOR: `6 ^ 5 ^ 8 = 11`
  The minimum XOR value among all valid paths is `9`.

**Example 3:**
- **Input:** `grid = [[2, 7, 5]]`
- **Output:** `0`
- **Explanation:**
  There is only one valid path from `(0, 0)` to `(0, 2)`:
  - `(0, 0) -> (0, 1) -> (0, 2)` with XOR: `2 ^ 7 ^ 5 = 0`
  The minimum XOR value is `0`.

---

### Constraints

- `m == grid.length`
- `n == grid[i].length`
- `1 <= m, n <= 1000`
- `m * n <= 1000`
- `0 <= grid[i][j] <= 1023`

---

Link--> https://leetcode.com/problems/minimum-xor-path-in-a-grid/?envType=daily-question&envId=2026-10-28


![alt text](<Notewise-New note 2026-10-29-1.jpg>) ![alt text](<Notewise-New note 2026-10-29-2.jpg>) ![alt text](<Notewise-New note 2026-10-29-3.jpg>)
```java
class Solution {
    private Set<Integer> helper(int i, int j, int fi, int fj, List<List<Set<Integer>>> dp, int[][] grid) {
        if (i == fi && j == fj) {

            Set<Integer> set = dp.get(i).get(j);
            set.add(grid[i][j]);
            return set;
        }
        if (dp.get(i).get(j).size() !=0)
            return dp.get(i).get(j);

        Set<Integer> set = dp.get(i).get(j);
        Set<Integer> a1 = null;
        Set<Integer> a2 = null;
        if (i + 1 <= fi)
            a1 = helper(i + 1, j, fi, fj, dp, grid);
        if (j + 1 <= fj)
            a2 = helper(i, j + 1, fi, fj, dp, grid);
        if (a1!=null){
            var itr = a1.iterator();
        while (itr.hasNext()) {

            int val = itr.next();
            set.add(val ^ grid[i][j]);

        }
       
        }
        if(a2!=null){
             var itr2 = a2.iterator();
        while (itr2.hasNext()) {

            int val = itr2.next();
            set.add(val ^ grid[i][j]);

        }
        }
        return set;
    }

    public int minCost(int[][] grid) {
        int n = grid.length;
        int m = grid[0].length;
        List<List<Set<Integer>>> dp = new ArrayList<>(n);
        for (int i = 0; i < n; i++) {
            List<Set<Integer>> row = new ArrayList<>(m);
            for (int j = 0; j < m; j++) {
                row.add(new HashSet<>());
            }
            dp.add(row);
        }

        helper(0, 0, n - 1, m - 1, dp, grid);
        int ans = 1024;
        Set<Integer> set = dp.get(0).get(0);
        var itr = set.iterator();
        while (itr.hasNext()) {

            int val = itr.next();
            ans = Math.min(val, ans);
        }
        return ans;
    }
}
```

## Optimized code


```java
class Solution {
    private boolean[] helper(int i, int j, int fi, int fj, boolean[][][] dp, int[][] grid) {
        if (dp[i][j] != null) // proper memoization: dp[i][j] starts null and is set exactly once
            return dp[i][j];

        boolean[] set = new boolean[1024]; // bounded state space (grid values < 1024, XOR stays < 1024)

        if (i == fi && j == fj) {
            set[grid[i][j]] = true;
            dp[i][j] = set;
            return set;
        }

        boolean[] a1 = null;
        boolean[] a2 = null;
        if (i + 1 <= fi)
            a1 = helper(i + 1, j, fi, fj, dp, grid);
        if (j + 1 <= fj)
            a2 = helper(i, j + 1, fi, fj, dp, grid);

        if (a1 != null) {
            // direct array scan replaces HashSet iterator -> no boxing/hashing overhead
            for (int v = 0; v < 1024; v++)
                if (a1[v]) set[v ^ grid[i][j]] = true;
        }
        if (a2 != null) {
            for (int v = 0; v < 1024; v++)
                if (a2[v]) set[v ^ grid[i][j]] = true;
        }

        dp[i][j] = set;
        return set;
    }

    public int minCost(int[][] grid) {
        int n = grid.length;
        int m = grid[0].length;
        boolean[][][] dp = new boolean[n][m][]; // replaced List<List<Set<Integer>>> with primitive boolean array grid

        helper(0, 0, n - 1, m - 1, dp, grid);

        int ans = 1024;
        boolean[] set = dp[0][0];
        for (int v = 0; v < 1024; v++) {
            if (set[v]) {
                ans = v; // ascending scan -> first true value is already the minimum
                break;   // early exit, no need to scan remaining values
            }
        }
        return ans;
    }
}
```

