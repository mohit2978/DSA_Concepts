# Notes
![alt text](<0462d prefix sum intro_240517_185057.jpg>)
![alt text](<0462d prefix sum intro_240517_185057(1).jpg>) 
![alt text](<0462d prefix sum intro_240517_185057(2).jpg>)
 ![alt text](<0462d prefix sum intro_240517_185057(3).jpg>)
  ![alt text](<0462d prefix sum intro_240517_185057(4).jpg>) 
  ![alt text](<0462d prefix sum intro_240517_185057(5).jpg>)
   ![alt text](<0462d prefix sum intro_240517_185057(6).jpg>) 
   ![alt text](<0462d prefix sum intro_240517_185057(7).jpg>)
    ![alt text](<0462d prefix sum intro_240517_185057(8).jpg>)

    
```cpp
    class NumMatrix {
    private int[][] presum;
    public NumMatrix(int[][] mat) {
        presum=new int[mat.length][mat[0].length];
        for(int i=0;i<mat.length;i++){
            for(int j=0;j<mat[0].length;j++){
                int pre=mat[i][j];
                if(i-1>=0) pre+=presum[i-1][j];
                if(j-1>=0) pre+=presum[i][j-1];
                if(i-1>=0 && j-1>=0) pre-=presum[i-1][j-1];
                presum[i][j]=pre;
            }
        }
    }
    
    public int sumRegion(int row1, int col1, int row2, int col2) {
        int res=presum[row2][col2];
        if(row1-1>=0) res-=presum[row1-1][col2];
        if(col1-1>=0) res-=presum[row2][col1-1];
        if(row1-1>=0 && col1-1>=0) res+=presum[row1-1][col1-1];
        return res;
    }
}

```

![alt text](<0462d prefix sum intro_240517_185057(9).jpg>) 
![alt text](<0462d prefix sum intro_240517_185057(10).jpg>) 

# Q3 3212. Count Submatrices With Equal Frequency of X and Y

Link-->https://leetcode.com/problems/count-submatrices-with-equal-frequency-of-x-and-y/description/


**Difficulty:** Medium
**Topics:** Array, Matrix, Prefix Sum

---

### Problem Description

You are given a 2D character matrix `grid` where each cell `grid[i][j]` contains one of three possible values: `'X'`, `'Y'`, or `'.'`.

Your task is to count how many submatrices satisfy **ALL** of the following conditions:

1. The submatrix must include the top-left corner of the grid (position `grid[0][0]`).
2. The submatrix must contain an equal number of `'X'` and `'Y'` characters.
3. The submatrix must contain at least one `'X'` character.

---

### Examples

**Example 1:**

**Input:** `grid = [["X","Y","."],["Y",".","."]]`
**Output:** `3`
**Explanation:**
- The submatrix ending at `(0, 1)` contains one 'X' and one 'Y'.
- The submatrix ending at `(1, 0)` contains one 'X' and one 'Y'.
- The submatrix ending at `(1, 1)` contains one 'X' and one 'Y'.
All these submatrices include `grid[0][0]`, have equal 'X' and 'Y' counts, and at least one 'X'.

**Example 2:**

**Input:** `grid = [["X","X"],["X","Y"]]`
**Output:** `0`
**Explanation:** No submatrix starting at `(0, 0)` has the same number of 'X' and 'Y' characters.

**Example 3:**

**Input:** `grid = [[".","."],[".","."]]`
**Output:** `0`
**Explanation:** No submatrix starting at `(0, 0)` has at least one 'X' character.

---

### Constraints

- `1 <= grid.length, grid[i].length <= 1000`
- `grid[i][j]` is `'X'`, `'Y'`, or `'.'`.


## Solution

1. Use 2d prefix to get number of x and y in vectorof vector of pair
 as it is prefix sum so it always has a[0][0] so no need to worry for that 

2. now check for  equal x and y and freq(x)>0


```cpp
class Solution {
public:
    int numberOfSubmatrices(vector<vector<char>>& grid) {
        int n=grid.size();
        int m=grid[0].size();
        vector<vector<pair<int,int>>> freqcnt(n,vector<pair<int,int>>(m,{0,0}));
        int ans=0;
        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++){
                if(i-1>=0){
                    freqcnt[i][j].first+=freqcnt[i-1][j].first;
                    freqcnt[i][j].second+=freqcnt[i-1][j].second;
                }
                if(j-1>=0){
                    freqcnt[i][j].first+=freqcnt[i][j-1].first;
                    freqcnt[i][j].second+=freqcnt[i][j-1].second;
                }
                 if(i-1>=0 && j-1>=0){
                    freqcnt[i][j].first-=freqcnt[i-1][j-1].first;
                    freqcnt[i][j].second-=freqcnt[i-1][j-1].second;
                }
                if(grid[i][j]=='X'){
                    freqcnt[i][j].first++;
                }else if(grid[i][j]=='Y'){
                    freqcnt[i][j].second++;
                }

                if(freqcnt[i][j].first>0 && freqcnt[i][j].first==freqcnt[i][j].second) ans++;
            }
        }
        return ans;
    }
};

```

# Q4--> 3070. Count Submatrices with Top-Left Element and Sum Less Than k

You are given a **0-indexed** integer matrix `grid` and an integer `k`.

Return the number of submatrices that contain the top-left element of the grid, and have a sum less than or equal to `k`.

### Example 1:

**Input:** `grid = [[7,6,3],[6,6,1]], k = 18`
**Output:** `4`
**Explanation:** There are only 4 submatrices, shown in the image above, that contain the top-left element of grid, and have a sum less than or equal to 18.

### Example 2:

**Input:** `grid = [[7,2,9],[1,5,0],[2,6,6]], k = 20`
**Output:** `6`
**Explanation:** There are only 6 submatrices, shown in the image above, that contain the top-left element of grid, and have a sum less than or equal to 20.

### Constraints:

* `m == grid.length`
* `n == grid[i].length`
* `1 <= n, m <= 1000`
* `0 <= grid[i][j] <= 1000`
* `1 <= k <= 10^9`

As it needs top-left element so it is hint to use 2d prefix sum 

```java
class Solution {
     private int[][] presum;
      public int cntNumMatrix(int[][] mat,int k) {
        int cnt=0;
        presum=new int[mat.length][mat[0].length];
        for(int i=0;i<mat.length;i++){
            for(int j=0;j<mat[0].length;j++){
                int pre=mat[i][j];
                if(i-1>=0) pre+=presum[i-1][j];
                if(j-1>=0) pre+=presum[i][j-1];
                if(i-1>=0 && j-1>=0) pre-=presum[i-1][j-1];
                presum[i][j]=pre;
                if(presum[i][j]<=k) cnt++;
            }
        }
        return cnt;
    }
    
    public int countSubmatrices(int[][] grid, int k) {
        return cntNumMatrix(grid,k);
    }
}
```



Your logic here is flawless. You correctly identified that a submatrix starting at `(0,0)` and ending at `(i,j)` can be calculated using the classic Inclusion-Exclusion Principle formula: 
`Current Cell + Top Area + Left Area - Top-Left Overlap`

Your solution runs in **$O(M \times N)$ Time** and **$O(M \times N)$ Space**, which is an accepted, optimal approach. 

However, here is the "Senior Engineer" code review. We can optimize this even further to make it run in **$O(1)$ Space** and save thousands of unnecessary CPU cycles by looking closely at the problem constraints.

### 1. The Space Optimization ($O(1)$ Memory)
You are currently allocating a brand new `presum` matrix that is the exact same size as the input `grid`. If the matrix is massive, this doubles our memory footprint.

Because your algorithm processes strictly top-to-bottom, left-to-right, we never need the original value of a cell once we've calculated its prefix sum. This means we can just **overwrite the input `grid` directly**. We turn `grid` into our `presum` array, dropping our extra space down to absolutely zero ($O(1)$).

### 2. The Early Exit (The CPU Saver)
Look closely at the problem constraints: `0 <= grid[i][j] <= 1000`. 
**There are no negative numbers.**

Because there are no negative numbers, the prefix sum is **strictly non-decreasing**. As you move right across a row, the sum can only get bigger or stay the same. It can never shrink.

What happens if `k = 18`, and at `grid[2][2]` the prefix sum reaches `20`? 
In your current code, the inner loop keeps going to `j = 3, 4, 5...`, doing math and checking `if (pre <= k)`. But we *know* mathematically that every cell to the right will also be `> 18`. We can just `break` the inner loop completely and immediately jump to the next row!

### The Refactored Code (In-Place & Early Exit)

Here is how a Senior Engineer writes this to be as lean and fast as mathematically possible:

```java
class Solution {
    public int countSubmatrices(int[][] grid, int k) {
        int cnt = 0;
        int m = grid.length;
        int n = grid[0].length;
        
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                
                // Calculate 2D Prefix Sum IN-PLACE
                if (i > 0) grid[i][j] += grid[i - 1][j];
                if (j > 0) grid[i][j] += grid[i][j - 1];
                if (i > 0 && j > 0) grid[i][j] -= grid[i - 1][j - 1];
                
                // Check condition
                if (grid[i][j] <= k) {
                    cnt++;
                } else {
                    // The sum exceeded k. 
                    // Since there are no negative numbers, moving right will only increase the sum.
                    // Stop checking the rest of this row immediately!
                    break;
                }
            }
        }
        return cnt;
    }
}
```

### The Verdict
By combining In-Place modification and the `break` statement, you transform a standard $O(M \times N)$ solution into one that uses zero extra memory and actively short-circuits to avoid dead computations. 

