# Q1 Problem Statement: Ninja's Training

Link--> https://takeuforward.org/plus/dsa/problems/ninja's-training?category=dynamic-programming&subcategory=2d-dp

### 1. Description
A Ninja is planning an **N-day** training schedule. On each day, the Ninja can perform any one of **three activities**:
1. **Running** (Activity 0)
2. **Fighting Practice** (Activity 1)
3. **Learning New Moves** (Activity 2)

Each activity has a specific number of **merit points** associated with it for each day. However, there is a constraint:
> **The Ninja cannot perform the same activity on two consecutive days.**

**Goal:** Your task is to find the **maximum total merit points** the Ninja can attain over the N days.

---

### 2. Input Format
- A 2D array `points` of size `N x 3`.
- `points[i][j]` represents the merit points for the $j^{th}$ activity on the $i^{th}$ day.

---

### 3. Example
**Input:**
`points = [[10, 40, 70], [20, 50, 80], [30, 60, 90]]`

**Output:** `210`

**Explanation:**
- **Day 0:** Ninja chooses Activity 2 (Merit = 70)
- **Day 1:** Ninja chooses Activity 1 (Merit = 50) — *Cannot choose Activity 2 again.*
- **Day 2:** Ninja chooses Activity 2 (Merit = 90) — *Cannot choose Activity 1 again.*
- **Total:** 70 + 50 + 90 = 210.

---

## Mysolution 

```cpp

class Solution {
public:
    int ninjaTraining(vector<vector<int>>& mat) {
        int n=mat.size();
        vector<vector<int>>dp(n,vector<int>(3,0));
        for(int i=0;i<3;i++) dp[0][i]=mat[0][i];

        for(int i=1;i<n;i++){
            dp[i][0]=mat[i][0]+max(dp[i-1][1],dp[i-1][2]);
            dp[i][1]=mat[i][1]+max(dp[i-1][0],dp[i-1][2]);
            dp[i][2]=mat[i][2]+max(dp[i-1][1],dp[i-1][0]);
        }
        return max({dp[n-1][0],dp[n-1][1],dp[n-1][2]});
    }
};
```
# Q2 Minimum failing path sum 2
![alt text](<003matrix dp_260207_165630_0.png>) 
![alt text](<003matrix dp_260207_165630_1.png>)

# Q3 Cherry Pickup II

You are given a `rows x cols` matrix `grid` representing a field of cherries where `grid[i][j]` represents the number of cherries that you can collect from the `(i, j)` cell.

You have two robots that can collect cherries for you:
* **Robot #1** is located at the top-left corner `(0, 0)`, and
* **Robot #2** is located at the top-right corner `(0, cols - 1)`.

Return the maximum number of cherries collection using both robots by following the rules below:
* From a cell `(i, j)`, robots can move to cell `(i + 1, j - 1)`, `(i + 1, j)`, or `(i + 1, j + 1)`.
* When any robot passes through a cell, It picks up all cherries, and the cell becomes an empty cell.
* When both robots stay in the same cell, only one takes the cherries.
* Both robots cannot move outside of the grid at any moment.
* Both robots should reach the bottom row in `grid`.

### Example 1:

**Input:** `grid = [[3,1,1],[2,5,1],[1,5,5],[2,1,1]]`  
**Output:** `24`  
**Explanation:** Cherries taken by Robot #1, (3 + 2 + 5 + 2) = 12.  
Cherries taken by Robot #2, (1 + 5 + 5 + 1) = 12.  
Total of cherries: 12 + 12 = 24.  

### Example 2:

**Input:** `grid = [[1,0,0,0,0,0,1],[2,0,0,0,0,3,0],[2,0,9,0,0,0,0],[0,3,0,5,4,0,0],[1,0,2,3,0,0,6]]`  
**Output:** `28`  
**Explanation:** Cherries taken by Robot #1, (1 + 9 + 5 + 2) = 17.  
Cherries taken by Robot #2, (1 + 3 + 4 + 3) = 11.  
Total of cherries: 17 + 11 = 28.  

### Constraints:

* `rows == grid.length`
* `cols == grid[i].length`
* `2 <= rows, cols <= 70`
* `0 <= grid[i][j] <= 100`

Q--> for this can i do first i go for first robot and then for 2nd robot , i will make cherry 0 after moving 1st robot so that 2nd robot get 0 for that cherry??

# Why "Independent Pass" (Greedy) Fails: A Concrete Proof

Here is the exact mathematical proof of why the "Independent Pass" (Greedy) fails, using a concrete grid.

Let’s build a 3x4 Grid (3 Rows, 4 Columns).
* **Robot 1 (R1)** starts at the top-left `(0, 0)`.
* **Robot 2 (R2)** starts at the top-right `(0, 3)`.
* They can move down-left, straight down, or down-right.

Here is the cherry distribution:

```text
         Col 0   Col 1   Col 2   Col 3
Row 0: [   1,      0,      0,      1   ]  <-- Start Row
Row 1: [  50,     10,      0,      0   ]
Row 2: [   0,      0,    100,      0   ]
```
### Scenario 1: The Greedy "Independent" Approach (Your logic)

We let Robot 1 go first and find its absolute best path. It will act selfishly.

**Robot 1's Turn:**
* Starts at `(0, 0)`. Cherries = 1.
* It looks ahead and sees the massive 100 at `(2, 2)`.
* To reach it, it must step on `(1, 1)`.
* **R1 Path:** `(0,0) -> (1,1) -> (2,2)`
* **R1 Cherries:** 1 + 10 + 100 = **111 Cherries**.

Now, we set those eaten cherries to 0. The grid looks like this:

```text
         Col 0   Col 1   Col 2   Col 3
Row 0: [   0,      0,      0,      1   ]  <-- R2 starts here
Row 1: [  50,      0,      0,      0   ]
Row 2: [   0,      0,      0,      0   ]
```
**Robot 2's Turn:**
* Starts at `(0, 3)`. Cherries = 1.
* It looks for the best remaining path.
* It desperately wants that 50 at `(1, 0)`.
* **The Problem:** R2 is at Col 3. It can only move to Col 2, 3, or 4. It *cannot physically reach* Col 0 to get the 50!
* **R2 Path:** `(0,3) -> (1,2) -> (2,2)` (All zeros).
* **R2 Cherries:** 1 + 0 + 0 = **1 Cherry**.

**Total Greedy Score:** 111 (R1) + 1 (R2) = **112 Cherries**.

*Notice what happened:* R1 stole the 100, and because R2 spawned too far to the right, the 50 was completely wasted.

---

### Scenario 2: The Coordinated "DP" Approach (The Senior logic)

Instead of letting R1 be selfish, we move them simultaneously and optimize for the **Global Team Score**.

* **Row 0:** R1 is at `(0,0)`, R2 is at `(0,3)`. 
    * **Score** = 1 + 1 = 2.
* **Row 1:** R1 *deliberately* takes the "worse" path to `(1, 0)` to grab the 50. R2 moves to `(1, 2)` to position itself. 
    * **Score** = 50 + 0 = 50.
* **Row 2:** R1 moves straight down to `(2, 0)` (0 cherries). R2 moves straight down to `(2, 2)` and grabs the massive 100. 
    * **Score** = 0 + 100 = 100.

**Total Coordinated Score:** 2 + 50 + 100 = **152 Cherries**.

---

### The Verdict

| Approach | Total Cherries |
| :--- | :--- |
| **Greedy (Independent)** | **112** |
| **DP (Coordinated)** | **152** |

By doing independent passes, you left **40 cherries** on the table. Robot 1 taking its personal best path (111) actively destroyed the team's global best path (152). 

This is why you must use `dp[row][col_robot1][col_robot2]` to calculate every possible combination of their movements at the exact same time. You have to force Robot 1 to take a personal sacrifice (taking 50 instead of 111) so the team wins.


### The Correct Mental Model: "Simultaneous Movement"
The trick to this problem is realizing that since both robots move down one row at a time, they are always on the same row.
Instead of moving Robot 1 to the bottom and then starting Robot 2, you must move them row by row, at the exact same time.

### The 3D DP Solution (The Senior Approach)
Because they are always on the same row, you only need 3 variables to perfectly describe the state of the board at any given time:
* **`r`:** The current row they are both on.
* **`c1`:** The column of Robot 1.
* **`c2`:** The column of Robot 2.

**The DP State:** `dp[r][c1][c2]` = The maximum cherries both robots can collect from row `r` to the bottom, given R1 is at `c1` and R2 is at `c2`.

#### The Logic:
* **The Overlap Check:**
    * If `c1 == c2` (they landed on the same cell), you only add the cherry amount once: `grid[r][c1]`.
    * If `c1 != c2`, they landed on different cells, so you add both: `grid[r][c1] + grid[r][c2]`.
* **The 9 Choices:**
    * Robot 1 can move 3 ways (down-left, down, down-right).
    * Robot 2 can move 3 ways.
    * Because they move simultaneously, for every single step, there are $3 \times 3 = 9$ possible combinations of moves.
    * You write a nested loop (or 9 if statements) to try all 9 moves, and take the `max()` of them.

### Summary
If you try to do Robot 1 -> Update Grid -> Robot 2, you are essentially guessing that Robot 1's best path happens to perfectly align with the global best path. In hard DP problems, the universe is rarely that kind.

You must explore their universes together using `dp[r][c1][c2]`.


## Recursive solution 

```cpp
class Solution {
    vector<int>dir={-1,0,1};
    bool isitsafe(vector<vector<int>>& mat,int r,int c1,int c2){
        int n=mat.size();
        int m=mat[0].size();

        if(r>=0 && r<n && c1>=0 && c1<m && c2>=0 && c2<m) return true;
        return false;
    }
    int helper(vector<vector<int>>& mat,int r,int c1,int c2,int n){
        if(r==n-1) {
            return c1==c2?mat[r][c1]:mat[r][c1]+mat[r][c2];
        }
        int ans=0;
        int newr=r+1;
        for(int i=0;i<3;i++){
            int newc1=c1+dir[i];
            for(int j=0;j<3;j++){
                int newc2=c2+dir[j];
                if(isitsafe(mat,newr,newc1,newc2)){
                    ans=max(ans,helper(mat,newr,newc1,newc2,n));
                }
            }

        }
        ans+=(c1==c2?mat[r][c1]:mat[r][c1]+mat[r][c2]);
        return ans;
    }
public:
    int cherryPickup(vector<vector<int>>& matrix) {
        int n=matrix.size();
        int m=matrix[0].size();
        return helper(matrix,0,0,m-1,n);
    }
};
```
## Memoized solution

```cpp
class Solution {
    vector<int>dir={-1,0,1};
    bool isitsafe(vector<vector<int>>& mat,int r,int c1,int c2){
        int n=mat.size();
        int m=mat[0].size();

        if(r>=0 && r<n && c1>=0 && c1<m && c2>=0 && c2<m) return true;
        return false;
    }
    int helper(vector<vector<int>>& mat,int r,int c1,int c2,int n,vector<vector<vector<int>>> &dp){
        if(r==n-1) {
            return dp[r][c1][c2]=c1==c2?mat[r][c1]:mat[r][c1]+mat[r][c2];
        }
        if(dp[r][c1][c2]!=-1) return dp[r][c1][c2];
        int ans=0;
        int newr=r+1;
        for(int i=0;i<3;i++){
            int newc1=c1+dir[i];
            for(int j=0;j<3;j++){
                int newc2=c2+dir[j];
                if(isitsafe(mat,newr,newc1,newc2)){
                    ans=max(ans,helper(mat,newr,newc1,newc2,n,dp));
                }
            }

        }
        ans+=(c1==c2?mat[r][c1]:mat[r][c1]+mat[r][c2]);
        return dp[r][c1][c2]=ans;
    }
public:
    int cherryPickup(vector<vector<int>>& matrix) {
        int n=matrix.size();
        int m=matrix[0].size();
        vector<vector<vector<int>>> dp(n,vector<vector<int>>(m,vector<int>(m,-1)));
        return helper(matrix,0,0,m-1,n,dp);
    }
};
```

This is exactly it. You absolutely nailed it.

This is a production-ready, optimal $O(N \cdot M^2)$ 3D DP solution.

You successfully took the concept of "Simultaneous Movement" and translated it perfectly into code. Here is the "Senior Engineer" code review of your solution, highlighting why it is excellent, and offering one tiny architectural tip for the future.

### What You Did Perfectly (The Highlights)

* **The 3D State:** `dp[r][c1][c2]`. You successfully locked the robots into the same row `r`, eliminating the need for a 4th dimension (`r2`), saving massive amounts of memory and time.
* **The 9 Combinations:** Your nested `for(i=0...3)` and `for(j=0...3)` elegantly generates all 9 possible futures.
* **The Overlap Resolution:** `c1 == c2 ? mat[r][c1] : mat[r][c1] + mat[r][c2]`. This perfectly handles the core trick of the problem without duplicating code.

### The "Senior Engineer" Polish (Micro-Optimizations)

Your code works flawlessly, but here is a structural pattern you will see in top-tier competitive programming that makes the code slightly cleaner to read.

**The "Poison" Out-of-Bounds Pattern:**

Right now, you check `isitsafe` before making the recursive call. This is totally fine, but it means you wrap your core logic in an `if` statement.

Instead, you can push the safety check to the very top of the helper function and return a "poison" value (a massive negative number). This immediately kills any invalid recursive branches without needing an `if` statement around your calls.

Here is how a Senior would slightly refactor your helper function for maximum cleanliness:


```cpp
int helper(vector<vector<int>>& mat, int r, int c1, int c2, int n, int m, vector<vector<vector<int>>> &dp) {
    // 1. Out of Bounds Base Case (The "Poison")
    // If they step off the board, return a massive negative number 
    // so this path is guaranteed to lose the max() comparison.
    if (c1 < 0 || c1 >= m || c2 < 0 || c2 >= m) {
        return -1e9; 
    }

    // 2. Destination Base Case
    if (r == n - 1) {
        return (c1 == c2) ? mat[r][c1] : mat[r][c1] + mat[r][c2];
    }

    // 3. Memoization
    if (dp[r][c1][c2] != -1) return dp[r][c1][c2];

    // 4. Recursive Step
    int maxi = -1e9;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            // No safety check needed here anymore! Just call it.
            int ans = helper(mat, r + 1, c1 + dir[i], c2 + dir[j], n, m, dp);
            maxi = max(maxi, ans);
        }
    }

    // 5. Add current row's cherries and return
    int currentCherries = (c1 == c2) ? mat[r][c1] : mat[r][c1] + mat[r][c2];
    return dp[r][c1][c2] = maxi + currentCherries;
}
```
### Why use the `-1e9` poison trick?
* It removes the `isitsafe` helper function completely.
* It removes the `if(isitsafe)` check inside the double loop.
* If a problem allows moving Left/Right/Up (where you can get trapped), returning `0` for an invalid path is dangerous because `0` might be a valid score. Returning `-1e9` guarantees the path is mathematically destroyed.

### Final Verdict
**Your solution is a Pass/Hire.** You proved you can handle overlapping multi-agent DP states.

## Tabulation 

```cpp
class Solution {
    vector<int> dir = {-1, 0, 1};
    bool isitsafe(vector<vector<int>>& mat, int r, int c1, int c2) {
        int n = mat.size();
        int m = mat[0].size();

        if (r >= 0 && r < n && c1 >= 0 && c1 < m && c2 >= 0 && c2 < m)
            return true;
        return false;
    }
    int helper(vector<vector<int>>& mat, int R, int C1, int C2, int n,
               vector<vector<vector<int>>>& dp) {
        for (int r = n - 1; r >= 0; r--) {
            for (int c1 = 0; c1 < mat[0].size(); c1++) {
                for (int c2 = 0; c2 < mat[0].size(); c2++) {
                    if (r == n - 1) {
                        dp[r][c1][c2] =
                            (c1 == c2 ? mat[r][c1] : mat[r][c1] + mat[r][c2]);
                        continue;
                    }
                    int ans = 0;
                    int newr = r + 1;
                    for (int i = 0; i < 3; i++) {
                        int newc1 = c1 + dir[i];
                        for (int j = 0; j < 3; j++) {
                            int newc2 = c2 + dir[j];
                            if (isitsafe(mat, newr, newc1, newc2)) {
                                ans = max(ans, dp[newr][newc1][newc2]);
                            }
                        }
                    }
                    ans += (c1 == c2 ? mat[r][c1] : mat[r][c1] + mat[r][c2]);
                    dp[r][c1][c2] = ans;
                }
            }
        }
        return dp[R][C1][C2];
    }

   public:
    int cherryPickup(vector<vector<int>>& matrix) {
        int n = matrix.size();
        int m = matrix[0].size();
        vector<vector<vector<int>>> dp(
            n, vector<vector<int>>(m, vector<int>(m, -1)));
        return helper(matrix, 0, 0, m - 1, n, dp);
    }
};
```
This is a massive leap forward. You have successfully translated the Top-Down (Recursive) logic into Bottom-Up Tabulation.

You correctly identified that since the robots start at row `0` and move to row `n-1`, your tabulation must build the answer backwards from `n-1` up to `0`.

Here is the "Senior Engineer" review of this code, why it is great, and the Final Boss Optimization that this specific code structure unlocks.

### 1. What You Did Perfectly

* **The Base Case Initialization:** You neatly handled the last row (`r == n-1`) right inside the loop and used `continue`. This prevents out-of-bounds errors on `r+1`.
* **The Loop Reversal:** You correctly inverted the row loop `for (int r = n - 1; r >= 0; r--)`. This is the hallmark of Tabulation.
* **The Answer Extraction:** Returning `dp[0][0][m-1]` (or `dp[R][C1][C2]`) correctly pulls the final computed value for the exact starting positions.

### 2. The Final Boss: Space Optimization ($O(N \cdot M^2) \rightarrow O(M^2)$)

Your code is fast, but it still allocates a 3D array: `vector<vector<vector<int>>> dp(n, ...)`.

Look very closely at this line in your code:
```cpp
ans = max(ans, dp[newr][newc1][newc2]);
```

Notice that `newr` is always `r + 1`.

* When calculating **Row 2**, you only look at **Row 3**.
* When calculating **Row 1**, you only look at **Row 2**. Row 3 is completely useless now.

**The Secret:** You do not need an $N \times M \times M$ array. You only need two $M \times M$ arrays:
* `front` (representing `r + 1`)
* `curr` (representing `r`)

### How to upgrade your code to $O(M^2)$ Space:
Here is how a Senior Engineer takes your exact logic and strips away the $N$ dimension.
## Space optimized

```cpp
class Solution {
public:
    int cherryPickup(vector<vector<int>>& matrix) {
        int n = matrix.size();
        int m = matrix[0].size();
        
        // Instead of 3D, we only use two 2D arrays!
        vector<vector<int>> front(m, vector<int>(m, 0));
        vector<vector<int>> curr(m, vector<int>(m, 0));

        // 1. Base Case (Last Row)
        for (int c1 = 0; c1 < m; c1++) {
            for (int c2 = 0; c2 < m; c2++) {
                front[c1][c2] = (c1 == c2) ? matrix[n - 1][c1] : matrix[n - 1][c1] + matrix[n - 1][c2];
            }
        }

        // 2. Build Upwards
        vector<int> dir = {-1, 0, 1};
        for (int r = n - 2; r >= 0; r--) { // Start from n-2
            for (int c1 = 0; c1 < m; c1++) {
                for (int c2 = 0; c2 < m; c2++) {
                    
                    int maxi = -1e9; // Safe default for invalid paths
                    
                    // The 9 Combinations
                    for (int i = 0; i < 3; i++) {
                        for (int j = 0; j < 3; j++) {
                            int newc1 = c1 + dir[i];
                            int newc2 = c2 + dir[j];
                            
                            // Check Bounds
                            if (newc1 >= 0 && newc1 < m && newc2 >= 0 && newc2 < m) {
                                // Notice we look at 'front' instead of dp[r+1]
                                maxi = max(maxi, front[newc1][newc2]); 
                            }
                        }
                    }
                    
                    // Add current row cherries
                    int currentCherries = (c1 == c2) ? matrix[r][c1] : matrix[r][c1] + matrix[r][c2];
                    curr[c1][c2] = maxi + currentCherries;
                }
            }
            // Move 'curr' to 'front' for the next row iteration
            front = curr; 
        }

        // The answer for row 0, starting at cols 0 and m-1
        return front[0][m - 1]; 
    }
};
```
### The Evolution of a DP Master

Look at the journey you just took for this problem:

* **Greedy (Failed):** Realized robots must move simultaneously.
* **Recursion + Memoization:** Built a 3D state `[r][c1][c2]` and optimized the CPU addition overhead.
* **Tabulation:** Reversed the loops to build it Bottom-Up.
* **Space Optimization:** Realized `r` only needs `r+1`, deleting an entire dimension to reach $O(M^2)$ space.

**This is exactly how DP is meant to be learned.**




