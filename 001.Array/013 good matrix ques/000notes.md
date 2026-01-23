
Link---> https://leetcode.com/problems/maximum-matrix-sum/?envType=daily-question&envId=2026-01-05


# Q1 Maximum Matrix Sum

You are given an `n x n` integer `matrix`. You can do the following operation **any** number of times:

* Choose any two **adjacent** elements of `matrix` and **multiply** each of them by `-1`.

Two elements are considered **adjacent** if they share a **border**.

Your goal is to **maximize** the summation of the matrix's elements. Return the **maximum** sum of the matrix's elements using the operation any number of times.

---

### Example 1:
**Input:** `matrix = [[1,-1],[-1,1]]`  
**Output:** `4`  
**Explanation:** We can follow these steps to reach sum 4:
1. Multiply the 2 elements in the first row by -1: `[[-1,1],[-1,1]]`
2. Multiply the 2 elements in the first column by -1: `[[1,1],[1,1]]`

---

### Example 2:
**Input:** `matrix = [[1,2,3],[-1,-2,-3],[1,2,3]]`  
**Output:** `16`  
**Explanation:** We can follow these steps to reach sum 16:
1. Multiply the 2 last elements in the second row by -1: `[[1,2,3],[-1,2,3],[1,2,3]]`
2. Multiply the 2 elements in the first column by -1: `[[-1,2,3],[1,2,3],[1,2,3]]`
... (and so on)

---

### Constraints:
* `n == matrix.length == matrix[i].length`
* `2 <= n <= 250`
* `-10^5 <= matrix[i][j] <= 10^5`

# My first code

```cpp
class Solution {
    vector<vector<bool>> vis;
    long long gsum=-1e18;
    int visNo=0;
    vector<vector<int>> dir={{1,0},{-1,0},{0,1},{0,-1}};
    bool isSafeToVisit(int i,int j){
        if(i<0 ||i>=vis.size()|| j<0 || j>=vis[0].size() || vis[i][j]==true) return false;
        return true;
    }
    void dfs(vector<vector<int>>& mat ,long long sum,int i,int j){
        if(isSafeToVisit(i,j)==false) return ;
        int n=mat.size();
        int m=mat[0].size();
        visNo++;
        if(visNo==(n* m)){
            gsum=max(gsum,sum+mat[i][j]);
            visNo--;
            return;
        }
        vis[i][j]=true;
        
        for(int k=0;k<4;k++){
            int newi=i+dir[k][0];
            int newj=j+dir[k][1];
            if(isSafeToVisit(newi,newj)==false) continue;
            mat[i][j] *= -1;
            mat[newi][newj]=-1*mat[newi][newj];
            dfs(mat,sum+mat[i][j],newi,newj);
            mat[newi][newj]=-1*mat[newi][newj];
            mat[i][j] *= -1;
            dfs(mat,sum+mat[i][j],newi,newj);
        }
        visNo--;
        vis[i][j]=false;
    }
public:
    long long maxMatrixSum(vector<vector<int>>& matrix) {
        int n=matrix.size();
        int m=matrix[0].size();
        vis.resize(n,vector<bool>(m,false));
        long long sum=0;
        dfs(matrix,sum,0,0);
        return gsum;
    }

};
```

### The DFS Approach ($O(4^{N \times M})$)

Your DFS code is trying to find a path through the grid.

* **Decision Tree:** At every single cell, you are making a choice: "Should I go Up, Down, Left, or Right?" and "Should I flip the sign or not?"
* **Path Length:** Since you are visiting every cell, the path length is $N \times M$ (let's call this $K$).
* **Branching Factor:** At each of the $K$ steps, you have roughly 4 directions.
* **Total Work:** This creates a recursion tree with $4^K$ leaves.
* **The Reality:** For $N=250$, $K = 62,500$. The number $4^{62,500}$ is so large it has over 37,000 digits. A computer can only do about $10^8$ operations per second. This DFS would effectively run forever.

## Better code

```cpp
class Solution {
public:
    long long maxMatrixSum(vector<vector<int>>& matrix) {
        int minEl=1e5+1;
        int negativeElements=0;
        long long sum=0;
        for(auto v:matrix){
            for(auto el:v){
                sum+=abs(el);
                if(el<0) negativeElements++;
                minEl=min(minEl,abs(el));
            }
        }
        if(negativeElements%2==0) return sum;

        return sum-2*minEl;
    }
};
```

If negatives are odd, we must lose the smallest value twice 
     (once because we added it as positive, and once to make it negative

>Note:That is exactly the rule that makes the "Greedy" logic work! It sounds counter-intuitive at first, but because you can repeat this operation as many times as you want, the adjacency constraint effectively disappears.

>Here is the secret: You can move a negative sign from any cell to any other cell in the matrix without changing the total number of negative signs.As we can perform any number of times, so we can move negative cell to any other cell

>Note: so if odd negative signs we tryu to appear as negative sign is on min of (abs of all element)

tc->O(N*M) 