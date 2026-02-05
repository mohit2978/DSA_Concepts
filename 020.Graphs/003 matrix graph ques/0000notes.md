# Notes

In the context of algorithms and data flow, **Push** and **Pull** describe who is responsible for moving the information. Think of it like the difference between a **Notification** and a **Google Search**.

---

### 1. The Push Mechanism (BFS Style)
In a **Push** system, the source of the data is in control. It "pushes" its information out to its neighbors as soon as it has something to give.

* **How it works:** "I am a **1**. My distance is **0**. Hey, neighbors! Since I am 0, you all are now **1**."
* **BFS Logic:** When we pop a node from the queue, we **push** the updated distance to its unvisited neighbors.
* **Analogy:** A **Radio Station**. The station broadcasts the signal out to every radio in the area. The radios don't have to do anything but be "on" (unvisited).

---

### 2. The Pull Mechanism (Brute Force Style)
In a **Pull** system, the "target" or "receiver" is in control. It reaches out to its neighbors and asks for information to figure out its own state.

* **How it works:** "I am a **0**. I don't know my distance. Let me ask my neighbor. Hey, do you know the distance? No? Let me ask the next neighbor..."
* **Naive Logic:** Iterating through every `0` and searching for a `1`. You are trying to **pull** the location of the nearest `1` into the current cell.
* **Analogy:** A **Google Search**. The information doesn't come to you; you have to go out and actively look for it.

---

### Comparison Table

| Feature | Push Mechanism (BFS) | Pull Mechanism (Naive) |
| :--- | :--- | :--- |
| **Control** | The **Source** (The 1s) | The **Target** (The 0s) |
| **Effort** | Work is done once per source. | Work is repeated for every target. |
| **Efficiency** | **High ($O(N)$):** Information spreads naturally. | **Low ($O(N^2)$):** Lots of redundant searching. |
| **Direction** | Source $\to$ Target | Target $\leftarrow$ Source |

---

### Why Multi-Source BFS is the Ultimate "Push"
Multi-Source BFS is efficient because it treats every source (every `1` in the grid) as a starting point of a "wave." These waves push outward simultaneously. When two waves meet, they stop because the "empty" space has already been filled by the fastest-moving wave.

This ensures that every node is updated by the **closest possible source** with zero wasted effort.



![alt text](<002matrix graph ques_240423_191737.jpg>)

 ![alt text](<002matrix graph ques_240423_191737(1).jpg>) ![alt text](<002matrix graph ques_240423_191737(2).jpg>) ![alt text](<002matrix graph ques_240423_191737(3).jpg>) ![alt text](<002matrix graph ques_240423_191737(4).jpg>) ![alt text](<002matrix graph ques_240423_191737(5).jpg>) ![alt text](<002matrix graph ques_240423_191737(6).jpg>) ![alt text](<002matrix graph ques_240423_191737(7).jpg>) ![alt text](<002matrix graph ques_240423_191737(8).jpg>) ![alt text](<002matrix graph ques_240423_191737(9).jpg>) ![alt text](<002matrix graph ques_240423_191737(10).jpg>) ![alt text](<002matrix graph ques_240423_191737(11).jpg>) ![alt text](<002matrix graph ques_240423_191737(12).jpg>) ![alt text](<002matrix graph ques_240423_191737(13).jpg>) 
 
 # Distance of nearest cell having one

**Medium**

Given a binary grid of size `n x m`. Find the distance of the nearest cell having **1** in the grid for each cell.

The distance is calculated as $|i_1 - i_2| + |j_1 - j_2|$, where $(i_1, j_1)$ are the row and column number of the current cell, and $(i_2, j_2)$ are the row and column number of the nearest cell having value **1**.

**Note:** There should be at least one cell with value **1** in the grid.

---

### Examples

**Example 1:** **Input:** `grid = [[0, 1, 1, 0], [1, 1, 0, 0], [0, 0, 1, 1]]`  
**Output:** `[[1, 0, 0, 1], [0, 0, 1, 1], [1, 1, 0, 0]]`  
**Explanation:** - Cell (0,0) has nearest 1 at (0,1). Distance = $|0-0| + |0-1| = 1$.
- Cell (0,1), (0,2), (1,0), (1,1), (2,2), (2,3) already contain 1, so their distance is 0.
- Cell (1,2) has nearest 1 at (0,2) or (1,1) or (2,2). Distance = 1.

**Example 2:** **Input:** `grid = [[1, 0, 1], [1, 1, 0], [1, 0, 0]]`  
**Output:** `[[0, 1, 0], [0, 0, 1], [0, 1, 2]]`

---

### Constraints

* $1 \le n, m \le 500$
* $grid[i][j]$ is either $0$ or $1$.
* There is at least one $1$ in the `grid`.

---

This is a classic Graph problem that is best solved using **Multi-Source BFS**.

### The Problem
* **Goal:** Given a binary grid of 0s and 1s, find the distance of the nearest 1 for every cell.
* **Distance Metric:** The number of steps (up, down, left, right) to reach the nearest 1.
* **Property:** If a cell contains 1, its distance is 0.

---

### Why Standard BFS Fails (Time Limit Exceeded)
A naive approach would be:
1. Iterate through every cell containing 0.
2. Start a fresh BFS from that cell until you find the closest 1.
3. **Complexity:** $O((N \times M)^2)$. For a $500 \times 500$ grid, this results in up to $6.25 \times 10^{10}$ operations, which is way too slow for most platforms.

---

### The Optimal Approach: Multi-Source BFS
Instead of searching from every 0 to find a 1, we think in reverse: **Flood fill from all 1s simultaneously.**

#### 1. Initialization:
* Create a `dist` matrix of the same size, initialized to `-1` (to represent "unvisited").
* Create a queue for BFS.
* **Scan the Grid:** If a cell is **1**, push it into the queue and set its `dist` to **0**. These are our "starting sources."

#### 2. The BFS:
* While the queue is not empty, pop a cell $(r, c)$.
* Check its 4 neighbors (Up, Down, Left, Right).
* **If a neighbor has not been visited yet (`dist == -1`):**
    * It means we reached this 0 for the first time from the nearest available 1.
    * Set `neighbor_dist = current_dist + 1`.
    * Push that neighbor to the queue.

---

### Why this works:
BFS guarantees that we explore level-by-level. The very first time we touch a cell containing 0, it **must** be via the shortest possible path from one of the starting sources (the 1s).

```cpp

#include <vector>
#include <queue>

using namespace std;

class Solution {
public:
    // Function to find distance of nearest 1 in the grid for each cell.
    vector<vector<int>> nearest(vector<vector<int>>& grid) {
        int n = grid.size();
        int m = grid[0].size();
        
        // Queue stores {row, col}
        queue<pair<int, int>> q;
        
        // Output matrix initialized to -1 (acts as visited array too)
        vector<vector<int>> dist(n, vector<int>(m, -1));
        
        // 1. Collect all sources (cells with 1)
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < m; j++) {
                if(grid[i][j] == 1) {
                    q.push({i, j});
                    dist[i][j] = 0; // Distance to itself is 0
                }
            }
        }
        
        // Direction vectors for moving Up, Right, Down, Left
        int dRow[] = {-1, 0, 1, 0};
        int dCol[] = {0, 1, 0, -1};
        
        // 2. Multi-Source BFS
        while(!q.empty()) {
            int r = q.front().first;
            int c = q.front().second;
            q.pop();
            
            // Check all 4 neighbors
            for(int i = 0; i < 4; i++) {
                int nr = r + dRow[i];
                int nc = c + dCol[i];
                
                // Check bounds and if unvisited
                if(nr >= 0 && nr < n && nc >= 0 && nc < m && dist[nr][nc] == -1) {
                    dist[nr][nc] = dist[r][c] + 1;
                    q.push({nr, nc});
                }
            }
        }
        
        return dist;
    }
};
```
### Complexity Analysis

* **Time Complexity: $O(N \times M)$**
    * We visit every cell in the grid exactly once. 
    * Each cell is pushed into and popped from the queue exactly once.
    * The constant work done for each cell (checking 4 neighbors) does not change the linear complexity relative to the number of cells.

* **Space Complexity: $O(N \times M)$**
    * **Distance Matrix:** We need an $N \times M$ matrix to store the result.
    * **Queue:** In the worst case (e.g., a grid full of 1s), the queue might hold nearly all $N \times M$ nodes at once.
    * **Visited Array:** If you use a separate `visited` matrix instead of checking `dist == -1`, that also takes $O(N \times M)$ space.

---

This is the most optimal complexity possible for this problem, as you must at least visit every cell to produce the output. 

### Similar Problem Note
If the problem was "01 Matrix" (LeetCode 542) where you need distance to the nearest 0, you simply swap the logic: put all 0s in the queue initially and search for 1s. The algorithm remains exactly the same.
 
 Q--> Why Not
```text
 for(int i = 0; i < n; i++) {
            for(int j = 0; j < m; j++) {
                if(grid[i][j] == 1) {
                  
                    dist[i][j] = 0; // Distance to itself is 0
                }else   q.push({i, j});
            }
        } and then when we pop from q  we put dist[r][c]
   ```     
 That approach will fail because of a logical **"Deadlock."**

When you use BFS, you must start with the nodes that have **Known Answers** (the 1s) and spread that answer to the nodes with **Unknown Answers** (the 0s). If you put the 0s in the queue first, here is exactly what goes wrong:

---

### 1. The Deadlock Scenario
Imagine this simple row of cells:
`[Cell A: 0]` — `[Cell B: 0]` — `[Cell C: 1]`

**Your Proposed Logic:**
1.  **Setup:**
    * Cell **C** is 1 $\to$ `dist[C] = 0`.
    * Cells **A** and **B** are 0 $\to$ **Push A and B into Queue.**
2.  **Process Queue:**
    * **Pop A:** You try to calculate A's distance. You look at its neighbor **B**.
    * **The Problem:** B is also a 0. We haven't solved B yet! 
    * **Result:** You are asking an "unknown" node for help. A cannot calculate its distance because B doesn't know its distance yet.

---

### 2. The "Empty Bucket" Analogy
* The **1s** are buckets full of water (Distance = 0).
* The **0s** are empty buckets (Distance = Unknown).
* **BFS** is the process of pouring water from full buckets to empty neighbors.

**Your approach:** You line up all the empty buckets (0s) first.
1.  You pick up the first empty bucket (**A**).
2.  You try to pour water into it from its neighbor (**B**).
3.  But **B** is also empty!
4.  **Result:** Nothing happens. The distance remains undefined.

---

### 3. The Correct Flow
To solve this, you must start where the "water" is:
1.  **Start at C (1):** It has water. Put it in Queue.
2.  **Pop C:** Pour water into neighbor **B**. 
3.  Now **B** becomes "1 step away". Push B into Queue.
4.  **Pop B:** Pour water into neighbor **A**. 
5.  Now **A** becomes "2 steps away".

---

### Summary Rule
In Multi-Source BFS, always fill the Queue with the **Fixed Values** (the Source of the signal).

* If measuring distance **TO 1s** $\to$ Push **1s**.
* If measuring distance **TO 0s** $\to$ Push **0s**.

**You cannot start BFS from the "Unknowns."**

### The Golden Rule of Multi-Source BFS

In any distance problem, whatever you want to measure distance **TO** goes in the Queue first.

| Problem Goal | What goes in Queue first? | Why? |
| :--- | :--- | :--- |
| **Find distance to nearest 1** | Put all **1s** | Because 1s are the "Source" of the distance (Dist=0). |
| **Find distance to nearest 0** | Put all **0s** | Because 0s are the "Source" of the distance (Dist=0). |
| **Find distance to nearest Fire** | Put all **Fire** | Because Fire is the source of the heat. |
| **Rotting Oranges** | Put all **Rotten Oranges** | Because rot is what "spreads" (Source). |

---

### Why this is non-negotiable
If you put the "targets" (the 0s) in the queue first, they are just waiting for information. BFS is a **push** mechanism, not a **pull** mechanism. You need a source to "push" the distance values outward to the rest of the graph.

>Note: This is reason why we push rotting oranges in queue in Rotten oranges!!




 ![alt text](<002matrix graph ques_240423_191737(14).jpg>) ![alt text](<002matrix graph ques_240423_191737(15).jpg>) ![alt text](<002matrix graph ques_240423_191737(16).jpg>) ![alt text](<002matrix graph ques_240423_191737(17).jpg>) ![alt text](<002matrix graph ques_240423_191737(18).jpg>) ![alt text](<002matrix graph ques_240423_191737(19).jpg>) 


## Approach 1

```java

class Solution {
    public int islandPerimeter(int[][] grid) {
        int perimeter = 0;
        int rows = grid.length;
        int cols = grid[0].length;

        for (int r = 0; r < rows; r++) {
            for (int c = 0; c < cols; c++) {
                if (grid[r][c] == 1) {
                    // 1. Start with 4 sides
                    perimeter += 4;

                    // 2. Check UP
                    // If there is land above, I lose my top side (-1)
                    if (r > 0 && grid[r - 1][c] == 1) {
                        perimeter -= 1;
                    }

                    // 3. Check DOWN
                    // If there is land below, I lose my bottom side (-1)
                    if (r + 1 < rows && grid[r + 1][c] == 1) {
                        perimeter -= 1;
                    }

                    // 4. Check LEFT
                    // If there is land to the left, I lose my left side (-1)
                    if (c > 0 && grid[r][c - 1] == 1) {
                        perimeter -= 1;
                    }

                    // 5. Check RIGHT
                    // If there is land to the right, I lose my right side (-1)
                    if (c + 1 < cols && grid[r][c + 1] == 1) {
                        perimeter -= 1;
                    }
                }
            }
        }
        return perimeter;
    }
}
```

## Approach 2 bit optmized

 
 ```java


class Solution {
    public int islandPerimeter(int[][] grid) {
        int perimeter = 0;
        int rows = grid.length;
        int cols = grid[0].length;

        for (int r = 0; r < rows; r++) {
            for (int c = 0; c < cols; c++) {
                if (grid[r][c] == 1) {
                    // Start by assuming this block adds 4 sides
                    perimeter += 4;

                    // Check Down neighbor
                    // If there is land below, they share an edge -> remove 2
                    if (r + 1 < rows && grid[r + 1][c] == 1) {
                        perimeter -= 2;
                    }

                    // Check Right neighbor
                    // If there is land to the right, they share an edge -> remove 2
                    if (c + 1 < cols && grid[r][c + 1] == 1) {
                        perimeter -= 2;
                    }
                }
            }
        }
        return perimeter;
    }
}
 ```
 This approach works by counting shared walls exactly once to avoid double counting. If you checked `r-1` (Up) and `c-1` (Left) as well as Down/Right, you would subtract the same wall twice, resulting in a wrong answer. 

Here is the breakdown of why this logic relies on **Traversal Order**:

---

### 1. The Traversal Order (Top-Left to Bottom-Right)
Your loops run from `r = 0` to `rows` and `c = 0` to `cols`. This means you visit cells in this order:
* **First Row:** (0,0) $\to$ (0,1) $\to$ (0,2)...
* **Second Row:** (1,0) $\to$ (1,1)...

Because of this specific order, you only need to look **"Forward"** (Right and Down) to catch every connection.

---

### 2. Why we don't look "Back" (Up and Left)
Let's analyze a connection between two cells: **Cell A (0,0)** and **Cell B (0,1)**.

1.  **Loop is at Cell A (0,0):**
    * The code looks **Right** (`c+1`).
    * It sees Cell B.
    * It knows they share a wall.
    >* **Action:** It subtracts **2** from the perimeter immediately (1 side lost from A, 1 side lost from B).
    * The wall between A and B is now fully accounted for.
2.  **Loop moves to Cell B (0,1):**
    * The code looks Right and Down.
    * It does **NOT** look Left.
    * **Why?** Because the wall to the left (between B and A) was already removed when we processed Cell A.
    * If you looked Left here and subtracted 2 again, you would be removing the same wall twice.

---

### 3. The "Handshake" Analogy
Imagine the cells are people standing in a grid, and a "shared wall" is a handshake. We want to count total handshakes.

* **Your Code's Rule:** "Everyone, look only to your Right and Down. If there is a person there, shake hands."
* If A looks Right and shakes B's hand... that handshake is done.
* When the loop later reaches B, B does not need to look Left to shake A's hand again. It's the same handshake.

---

### Summary

| Strategy | Action per Cell | Subtract Value | Efficiency |
| :--- | :--- | :--- | :--- |
| **4 Directions** | Check Up, Down, Left, Right | Subtract **1** per neighbor | 4 checks (Standard) |
| **2 Directions** | Check Down and Right only | Subtract **2** per neighbor | **2 checks (Optimized)** |

**Note:** The 2-direction optimization only works if you are iterating through the grid in a linear fashion (like nested for-loops).

DFS approach we return 1 when we get to corner
```cpp
int getPerimeter(vector<vector<int>>& grid, int r, int c) {
    // If we go out of bounds or hit water, that's 1 unit of perimeter
    if (r < 0 || r >= grid.size() || c < 0 || c >= grid[0].size() || grid[r][c] == 0) {
        return 1;
    }
    
    // If we hit already visited land, don't count it again
    if (grid[r][c] == -1) return 0;
    
    // Mark as visited (using -1 to save space)
    grid[r][c] = -1;
    
    int count = 0;
    count += getPerimeter(grid, r + 1, c); // Down
    count += getPerimeter(grid, r - 1, c); // Up
    count += getPerimeter(grid, r, c + 1); // Right
    count += getPerimeter(grid, r, c - 1); // Left
    
    return count;
}
```
 
 ![alt text](<002matrix graph ques_240423_191737(20).jpg>) ![alt text](<002matrix graph ques_240423_191737(21).jpg>)
 
 ```java

class Solution {
    public int dfs(int [][]grid,int[][] dir,boolean[][] vis,int i,int j){
        int area=0;
         vis[i][j]=true;
        for(int diri=0;diri<4;diri++){
            int newi=i+dir[diri][0];
            int newj=j+dir[diri][1];
            if(newi>=0 && newj>=0 && newi<grid.length && newj<grid[0].length && vis[newi][newj]==false && grid[newi][newj]==1){
                
                area+=(dfs(grid,dir,vis,newi,newj)+1);
            }
            
        }
        return area;
    }
    public int maxAreaOfIsland(int[][] grid) {
        int [][] dir={{0,1},{0,-1},{-1,0},{1,0}};
        boolean [][] vis=new boolean[grid.length][grid[0].length];
        int maxarea=0;
        int area=0;
        for(int i=0;i<grid.length;i++){
            for(int j=0;j<grid[0].length;j++){
                if(grid[i][j]==1 && vis[i][j]==false){
                    area=dfs(grid,dir,vis,i,j)+1;
                    maxarea=Math.max(area,maxarea);
                }
            }
        }
        return maxarea;
    }
}
 ```
 
  ![alt text](<002matrix graph ques_240423_191737(22).jpg>) ![alt text](<002matrix graph ques_240423_191737(23).jpg>) ![alt text](<002matrix graph ques_240423_191737(24).jpg>) ![alt text](<002matrix graph ques_240423_191737(25).jpg>) ![alt text](<002matrix graph ques_240423_191737(26).jpg>) ![alt text](<002matrix graph ques_240423_191737(27).jpg>) ![alt text](<002matrix graph ques_240423_191737(28).jpg>) 
  
  ```cpp
class Solution {
    vector<vector<int>> dist;
   int nearest(vector<vector<int>>& grid) {
        int n = grid.size();
        int m = grid[0].size();
        
        // Queue stores {row, col}
        queue<pair<int, int>> q;
        
        // Output matrix initialized to -1 (acts as visited array too)
      dist.resize(n, vector<int>(m, -1));
        
        // 1. Collect all sources (cells with 1)
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < m; j++) {
                if(grid[i][j] == 1) {
                    q.push({i, j});
                    dist[i][j] = 0; // Distance to itself is 0
                }
            }
        }
        
        if(q.size()==0 || q.size()== n*m) return -1;
        // Direction vectors for moving Up, Right, Down, Left
        int dRow[] = {-1, 0, 1, 0};
        int dCol[] = {0, 1, 0, -1};
        
        // 2. Multi-Source BFS
        while(!q.empty()) {
            int r = q.front().first;
            int c = q.front().second;
            q.pop();
            
            // Check all 4 neighbors
            for(int i = 0; i < 4; i++) {
                int nr = r + dRow[i];
                int nc = c + dCol[i];
                
                // Check bounds and if unvisited
                if(nr >= 0 && nr < n && nc >= 0 && nc < m && dist[nr][nc] == -1) {
                    dist[nr][nc] = dist[r][c] + 1;
                    q.push({nr, nc});
                }
            }
        }
        
        return 1;
    
    }
public:
    int maxDistance(vector<vector<int>>& grid) {
        if(nearest(grid)==-1) return -1;
        int mx=0;
        for(int i=0;i<dist.size();i++){
            for(int j=0;j<dist[0].size();j++){
                mx=max(mx,dist[i][j]);
            }
        }
        return mx;
    }
};

  ```
   same as nearest ,only cases we have put if all 1's and all 0's
  
  ![alt text](<002matrix graph ques_240423_191737(29).jpg>) ![alt text](<002matrix graph ques_240423_191737(30).jpg>) ![alt text](<002matrix graph ques_240423_191737(31).jpg>) ![alt text](<002matrix graph ques_240423_191737(32).jpg>) ![alt text](<002matrix graph ques_240423_191737(33).jpg>) ![alt text](<002matrix graph ques_240423_191737(34).jpg>) ![alt text](<002matrix graph ques_240423_191737(35).jpg>) ![alt text](<002matrix graph ques_240423_191737(36).jpg>) ![alt text](<002matrix graph ques_240423_191737(37).jpg>) ![alt text](<002matrix graph ques_240423_191737(38).jpg>) ![alt text](<002matrix graph ques_240423_191737(39).jpg>) ![alt text](<002matrix graph ques_240423_191737(40).jpg>) ![alt text](<002matrix graph ques_240423_191737(41).jpg>) ![alt text](<002matrix graph ques_240423_191737(42).jpg>)






![alt text](<002matrix graph ques_240423_191737(43).jpg>) ![alt text](<002matrix graph ques_240423_191737(44).jpg>) ![alt text](<002matrix graph ques_240423_191737(45).jpg>)

```java

class Solution {
    class trip implements Comparable<trip>{
        int i;
        int j;
        int cost;
        trip(int i,int j,int cost){
            this.i=i;
            this.j=j;
            this.cost=cost;
        }
        public int compareTo(trip o){
            return this.cost-o.cost;
        }
        
    }
    public int swimInWater(int[][] mat) {
         int res=0;
         boolean [][] vis=new boolean [mat.length][mat[0].length];
        int[][] dir={{0,1},{0,-1},{1,0},{-1,0}};
        
        PriorityQueue<trip>pq=new PriorityQueue<>();
        pq.add(new trip(0,0,mat[0][0]));
        res=mat[0][0];
        
        while(pq.size()>0){
            trip rem=pq.remove();
            if(vis[rem.i][rem.j]==true) continue;
          
            vis[rem.i][rem.j]=true;
            if(res<rem.cost){
                res=rem.cost;
            }
           
            for(int i=0;i<4;i++){
                int dr=rem.i+dir[i][0];
                int dc=rem.j+dir[i][1];
                if(dr>=0 && dr<mat.length && dc>=0 && dc<mat[0].length && vis[dr][dc]==false){
                    if(dr==mat.length-1 &&dc==mat[0].length-1){
                        res=Math.max(res,mat[dr][dc]);
                        return res;
                    }
                    pq.add(new trip(dr,dc,mat[dr][dc]));
                }
            }
            
        }
        return res;
        
    }
}
```

## Java using lambda

```java
import java.util.PriorityQueue;

class Solution {
    class trip {
        int i;
        int j;
        int cost;
        trip(int i, int j, int cost) {
            this.i = i;
            this.j = j;
            this.cost = cost;
        }
    }

    public int swimInWater(int[][] mat) {
        int n = mat.length;
        boolean[][] vis = new boolean[n][n];
        int[][] dir = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

        PriorityQueue<trip> pq = new PriorityQueue<>((a, b) -> a.cost - b.cost);
        pq.add(new trip(0, 0, mat[0][0]));
        int res = 0;

        while (pq.size() > 0) {
            trip rem = pq.remove();
            
            if (vis[rem.i][rem.j]) continue;
            vis[rem.i][rem.j] = true;
            
            res = Math.max(res, rem.cost);
            
            if (rem.i == n - 1 && rem.j == n - 1) {
                return res;
            }

            for (int i = 0; i < 4; i++) {
                int dr = rem.i + dir[i][0];
                int dc = rem.j + dir[i][1];
                
                if (dr >= 0 && dr < n && dc >= 0 && dc < n && !vis[dr][dc]) {
                    pq.add(new trip(dr, dc, mat[dr][dc]));
                }
            }
        }
        return res;
    }
}
```
### Cpp

```cpp
`#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

class Solution {
    struct Trip {
        int r;
        int c;
        int cost;
        
        bool operator>(const Trip& other) const {
            return cost > other.cost;
        }
    };

public:
    int swimInWater(vector<vector<int>>& grid) {
        int n = grid.size();
        vector<vector<bool>> vis(n, vector<bool>(n, false));
        int dir[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
        
        priority_queue<Trip, vector<Trip>, greater<Trip>> pq;
        pq.push({0, 0, grid[0][0]});
        
        int res = 0;
        
        while (!pq.empty()) {
            Trip rem = pq.top();
            pq.pop();
            
            if (vis[rem.r][rem.c]) continue;
            vis[rem.r][rem.c] = true;
            
            res = max(res, rem.cost);
            
            if (rem.r == n - 1 && rem.c == n - 1) return res;
            
            for (int i = 0; i < 4; i++) {
                int dr = rem.r + dir[i][0];
                int dc = rem.c + dir[i][1];
                
                if (dr >= 0 && dr < n && dc >= 0 && dc < n && !vis[dr][dc]) {
                    pq.push({dr, dc, grid[dr][dc]});
                }
            }
        }
        return res;
    }
};
```

 ![alt text](<002matrix graph ques_240423_191737(46).jpg>) ![alt text](<002matrix graph ques_240423_191737(47).jpg>)










































