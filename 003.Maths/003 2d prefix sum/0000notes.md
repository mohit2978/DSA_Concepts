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