# Notes
![alt text](<002 dfs_240306_011019.jpg>)


 ![alt text](<002 dfs_240306_011019(1).jpg>) ![alt text](<002 dfs_240306_011019(2).jpg>) ![alt text](<002 dfs_240306_011019(3).jpg>) ![alt text](<002 dfs_240306_011019(4).jpg>) ![alt text](<002 dfs_240306_011019(5).jpg>) ![alt text](<002 dfs_240306_011019(6).jpg>)
 

 ## BFS way

```java
static List<List<Integer>> components(List<List<Integer>> graph) {
    boolean[] visited = new boolean[graph.size()];
    List<List<Integer>> answer = new ArrayList<>();

    for (int start = 0; start < graph.size(); start++) {
        if (visited[start]) continue;

        List<Integer> component = new ArrayList<>();
        Queue<Integer> queue = new ArrayDeque<>();
        visited[start] = true;
        queue.offer(start);

        while (!queue.isEmpty()) {
            int u = queue.poll();
            component.add(u);
            for (int v : graph.get(u)) {
                if (!visited[v]) {
                    visited[v] = true;
                    queue.offer(v);
                }
            }
        }
        answer.add(component);
    }
    return answer;
}
```

Example:

```text
[[0, 1, 2, 3], [5, 6], [7, 8, 9]]
```

- Number of components: `answer.size()`
- Time: $O(V+E)$
- Space: $O(V)$ excluding the returned output



#  Count Islands in a Binary Grid



A cell containing `1` is land and `0` is water. Connected land cells form one island.

```text
1 1 0 0 0
0 1 0 0 1
1 0 0 1 1
0 0 0 0 0
```

The instructor's key conversion is:

```text
land cell       → graph vertex
allowed move    → graph edge
island          → connected component
```

Now the familiar connected-components pattern applies: scan every cell; whenever an unvisited land cell is found, increment the answer and traverse its complete component.

## Approach 1 — DFS

The lecture implementation explores all eight surrounding positions. If a problem specifies only horizontal/vertical adjacency, replace the direction arrays with the four cardinal moves.

```java
static final int[] DR = {-1,-1,-1, 0,0, 1,1,1};
static final int[] DC = {-1, 0, 1,-1,1,-1,0,1};

static int countIslands(int[][] grid) {
    int rows = grid.length;
    int cols = grid[0].length;
    boolean[][] visited = new boolean[rows][cols];
    int islands = 0;

    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            if (grid[r][c] == 1 && !visited[r][c]) {
                islands++;
                dfs(grid, r, c, visited);
            }
        }
    }
    return islands;
}

static void dfs(int[][] grid, int r, int c, boolean[][] visited) {
    visited[r][c] = true;

    for (int k = 0; k < DR.length; k++) {
        int nr = r + DR[k];
        int nc = c + DC[k];
        if (inside(grid, nr, nc)
                && grid[nr][nc] == 1
                && !visited[nr][nc]) {
            dfs(grid, nr, nc, visited);
        }
    }
}

static boolean inside(int[][] grid, int r, int c) {
    return r >= 0 && r < grid.length && c >= 0 && c < grid[0].length;
}
```

## Approach 2 — BFS

Use a queue instead of recursion. This has the same asymptotic complexity and avoids a stack overflow on a very large island.

- Time: $O(RC)$
- Space: $O(RC)$ in the worst case

## Important modelling decision

Always read the adjacency rule:

- 4-direction: up, down, left, right
- 8-direction: also includes diagonals

The same matrix can have a different island count under these two definitions.

---

 
  ![alt text](<002 dfs_240306_011019(7).jpg>) ![alt text](<002 dfs_240306_011019(8).jpg>) ![alt text](<002 dfs_240306_011019(9).jpg>) ![alt text](<002 dfs_240306_011019(10).jpg>) ![alt text](<002 dfs_240306_011019(11).jpg>) ![alt text](<002 dfs_240306_011019(12).jpg>) ![alt text](<002 dfs_240306_011019(13).jpg>) ![alt text](<002 dfs_240306_011019(14).jpg>) ![alt text](<002 dfs_240306_011019(15).jpg>) ![alt text](<002 dfs_240306_011019(16).jpg>)





![alt text](<002 dfs_240306_011019(17).jpg>) ![alt text](<002 dfs_240306_011019(18).jpg>) ![alt text](<002 dfs_240306_011019(19).jpg>) ![alt text](<002 dfs_240306_011019(20).jpg>) ![alt text](<002 dfs_240306_011019(21).jpg>) ![alt text](<002 dfs_240306_011019(22).jpg>) ![alt text](<002 dfs_240306_011019(23).jpg>) ![alt text](<002 dfs_240306_011019(24).jpg>) ![alt text](<002 dfs_240306_011019(25).jpg>) ![alt text](<002 dfs_240306_011019(26).jpg>) ![alt text](<002 dfs_240306_011019(27).jpg>)




```cpp

#include <bits/stdc++.h>
using namespace std;

class Solution{
    bool canVisit( vector<vector<char>> &grid,vector<vector<bool>> &vis,int i ,int j){
        int n=grid.size();
        int m=grid[0].size();
        if(i>=0 && i<n && j>=0 && j<m && vis[i][j]==false && grid[i][j]=='1') return true;
        return false;
    }
    void solve (vector<vector<int>> &dir, vector<vector<char>> &grid,vector<vector<bool>> &vis,int i ,int j){
        vis[i][j]=true;
        for(int k=0;k<dir.size();k++){
            int newi=i+dir[k][0];
            int newj=j+dir[k][1];
            if(canVisit(grid,vis,newi,newj)==true){
               solve(dir,grid,vis,newi,newj);
            }
        }
    }
public:
    int numIslands(vector<vector<char>> &grid){
        vector<vector<int>>dir={{-1,0},{1,0},{0,1},{0,-1},{-1,1},{1,-1},{1,1},{-1,-1}};
        vector<vector<bool>> vis(grid.size(),vector<bool>(grid[0].size(),false));
        int cnt=0;
        for(int i=0;i<grid.size();i++){
            for(int j=0;j<grid[0].size();j++){
                if(canVisit(grid,vis,i,j)==true){
                    solve(dir,grid,vis,i,j);
                    cnt++;
                }
            }
        }
        return cnt;
    }
};


int main() {
    vector<vector<char>> grid = {
        {'1', '1', '1', '0', '1'},
        {'1', '0', '0', '0', '0'},
        {'1', '1', '1', '0', '1'},
        {'0', '0', '0', '1', '1'}
    };
    
    // Creating an instance of Solution class
    Solution sol;
    
    /* Function call to find the
    number of islands in given grid */
    int ans = sol.numIslands(grid);
    
    cout << "The total islands in given grids are: " << ans << endl;
    
    return 0;
}

```
### BFS solution
#### Cpp

```cpp
#include <bits/stdc++.h>
using namespace std;

class Solution {
private:
    
    /* Function to determine if the cell
     is valid (within grid's boundaries) */
    bool isValid(int i, int j, int n, int m) {
        if (i < 0 || i >= n) return false;
        if (j < 0 || j >= m) return false;
        
        // Return true if cell is valid
        return true;
    }
    
    void bfs(int i, int j, vector<vector<bool>>& vis, 
             vector<vector<char>>& grid) {

        // Mark the node as visited
        vis[i][j] = true;
        
        // Queue required for BFS traversal
        queue<pair<int, int>> q;
        
        // push the node in queue
        q.push({i, j});
        
        // Dimensions of grid
        int n = grid.size();
        int m = grid[0].size();
        
        // Until the queue becomes empty
        while (!q.empty()) {
            // Get the cell from queue
            pair<int, int> cell = q.front();
            q.pop();
            
            // Determine its row & column
            int row = cell.first;
            int col = cell.second;
            
            // Traverse the 8 neighbours
            for (int delRow = -1; delRow <= 1; delRow++) {
                for (int delCol = -1; delCol <= 1; delCol++) {
                    // Coordinates of new cell
                    int newRow = row + delRow;
                    int newCol = col + delCol;
                    
                    /* Check if the new cell is valid, 
                    unvisited, and a land cell */
                    if (isValid(newRow, newCol, n, m) 
                        && grid[newRow][newCol] == '1' 
                        && !vis[newRow][newCol]) {
                            
                        // Mark the node as visited
                        vis[newRow][newCol] = true;
                        
                        // Push new cell in queue
                        q.push({newRow, newCol});
                    }
                }
            }
        }
    }
    
public:
    // Function to find the number of islands in given grid
    int numIslands(vector<vector<char>>& grid) {
        // Size of the grid
        int n = grid.size();
        int m = grid[0].size();
        
        // Visited array
        vector<vector<bool>> vis(n, vector<bool>(m, false));
        
        // To store the count of islands
        int count = 0;
        
        // Traverse the grid
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                /* If not visited and is a land, 
                start a new traversal */
                if (!vis[i][j] && grid[i][j] == '1') {
                    count++;
                    bfs(i, j, vis, grid);
                }
            }
        }
        
        return count;
    }
};

int main() {
    vector<vector<char>> grid = {
        {'1', '1', '1', '0', '1'},
        {'1', '0', '0', '0', '0'},
        {'1', '1', '1', '0', '1'},
        {'0', '0', '0', '1', '1'}
    };
    
    // Creating an instance of Solution class
    Solution sol;
    
    /* Function call to find the
    number of islands in given grid */
    int ans = sol.numIslands(grid);
    
    cout << "The total islands in given grids are: " << ans << endl;
    
    return 0;
}

```


## BFS and DFS

### Cpp
```cpp
#include <bits/stdc++.h>
using namespace std;

class Solution {
private:

	/* Helper function to perform BFS
	traversal from the node */
	void bfs(int node, vector<int> adj[], int vis[],
	         vector<int> &ans) {

		// Queue data structure
		queue<int> q;

		// Push the starting node
		q.push(node);

		// Until the queue is empty
		while(!q.empty()) {

			// Get the node
			int node = q.front();
			q.pop();

			// Add the node to answer
			ans.push_back(node);

			// Traverse for all its neighbours
			for(auto it : adj[node]) {

				/* If the neighbour has previously not been
				visited, store in Q and mark as visited */
				if(!vis[it]) {
					vis[it] = 1;
					q.push(it);
				}
			}
		}

		// Return
		return;
	}


	/* Helper function to recursively
	perform DFS from the node */
	void dfs(int node, vector<int> adj[], int vis[],
	         vector<int> &ans) {

		// Mark the node as visited
		vis[node] = 1;

		// Add the node to the result
		ans.push_back(node);

		// Traverse all its neighbours
		for(auto it : adj[node]) {

			// If the neighbour is not visited
			if(!vis[it]) {

				// Perform DFS recursively
				dfs(it, adj, vis, ans);
			}
		}
	}

public:

	/* Function to return a list containing
	the DFS traversal of the graph */
	vector<int> dfsOfGraph(int V, vector<int> adj[]) {
		// Visited array
		int vis[V] = {0};

		// Create a list to store DFS
		vector<int> ans;

		// Traverse all the nodes
		for(int i=0; i < V; i++) {

			// If the node is unvisited
			if(vis[i] == 0) {

				// Call DFS from that node
				dfs(i, adj, vis, ans);
			}
		}

		// Return the result
		return ans;
	}

	/* Function to return a list containing
	the BFS traversal of the graph */
	vector<int> bfsOfGraph(int V, vector<int> adj[]) {

		// Visited array
		int vis[V] = {0};

		// To store the result
		vector<int> ans;

		// Traverse all the nodes
		for(int i=0; i < V; i++) {

			// If the node is unvisited
			if(vis[i] == 0) {
			    
			    // Mark the node as visited
                vis[i] = 1;
                
				// Call BFS from that node
				bfs(i, adj, vis, ans);
			}
		}

		return ans;
	}
};



int main() {
	int  V = 5;
	vector<int> adj[] = {
		{2, 3, 1},
		{0},
		{0, 4},
		{0},
		{2}
	};

	// Creating instance of Solution class
	Solution sol;

	// Function call to get the BFS traversal of graph
	vector<int> bfs = sol.bfsOfGraph(V, adj);

	// Function call to get the BFS traversal of graph
	vector<int> dfs = sol.dfsOfGraph(V, adj);

	// Output
	cout << "The BFS traversal of the given graph is: ";
	for(int i=0; i < bfs.size(); i++) {
		cout << bfs[i] << " ";
	}
	cout << "\nThe DFS traversal of the given graph is: ";
	for(int i=0; i < dfs.size(); i++) {
		cout << dfs[i] << " ";
	}

	return 0;
}
```

# Time Complexity: $O(V + E)$ Explained

The complexity $O(V + E)$ is common for both **Breadth-First Search (BFS)** and **Depth-First Search (DFS)** when using an **Adjacency List**.

### 1. The "V" (Vertices)
Every single node in the graph must be visited at least once to determine if it has neighbors or to process its data. 
* In **BFS**, each node is enqueued and dequeued exactly once.
* In **DFS**, each node is visited via one recursive call or stack push.
* **Work done:** $O(V)$.

### 2. The "E" (Edges)
Once you are "at" a node, you look at all its neighbors. In an adjacency list, this means iterating through the list of edges connected to that node.
* For every node you visit, you iterate over its specific edges.
* Over the entire course of the algorithm, **every edge is looked at exactly twice** (once from each end) in an undirected graph, or **exactly once** in a directed graph.
* **Work done:** $O(E)$.

---

### 3. Putting it Together
The total time is the sum of visiting all vertices and traversing all their edges:
$$Total\ Time = O(V) + O(E) = O(V + E)$$

---

### 4. Comparison: Adjacency List vs. Adjacency Matrix
The $O(V + E)$ complexity only holds if you use an **Adjacency List**. If you use an **Adjacency Matrix**, the complexity changes:

| Structure | Time Complexity | Why? |
| :--- | :--- | :--- |
| **Adjacency List** | $O(V + E)$ | You only visit actual existing connections. |
| **Adjacency Matrix** | $O(V^2)$ | For every node ($V$), you must scan an entire row of length $V$ to find neighbors, regardless of how many edges actually exist. |



---

### 5. Simple Analogy: The House Party
Imagine a party where **Vertices ($V$)** are people and **Edges ($E$)** are the handshakes between them.
1. To meet everyone (**BFS/DFS**), you must walk up to every person (**$V$**).
2. To know who everyone knows, you must observe every handshake (**$E$**).
3. If you do both, your "effort" is proportional to the number of people plus the number of handshakes.

---

### Summary for Interviews
> "The complexity is $O(V + E)$ because we visit every vertex exactly once and, for each vertex, we iterate over all its outgoing edges. Summing these up across the entire graph gives us total work proportional to the number of vertices plus the number of edges."

## Iterative DFS with an explicit stack

```java
static List<Integer> dfsIterative(int start, List<List<Integer>> graph) {
    boolean[] visited = new boolean[graph.size()];
    Deque<Integer> stack = new ArrayDeque<>();
    List<Integer> order = new ArrayList<>();
    stack.push(start);

    while (!stack.isEmpty()) {
        int u = stack.pop();
        if (visited[u]) continue;

        visited[u] = true;
        order.add(u);

        // Reverse iteration preserves the recursive order for this list.
        List<Integer> neighbours = graph.get(u);
        for (int i = neighbours.size() - 1; i >= 0; i--) {
            int v = neighbours.get(i);
            if (!visited[v]) stack.push(v);
        }
    }
    return order;
}
```

For both approaches:

- Time: $O(V+E)$
- Visited array: $O(V)$
- Recursion/stack: up to $O(V)$

Use iterative DFS when recursion depth could overflow Java's call stack.


#  Capture Regions Surrounded by `X`


Change an `O` to `X` only if its entire `O` component is surrounded by `X`.

```text
Before             After
X X X X            X X X X
X O O X            X X X X
X X O X            X X X X
X O X X            X O X X  ← boundary-connected, so it survives
```

Only `O` surrounded by `X` needs to be chnaged to `X`

## Approach 1 — Explore every `O` component separately

For each component, collect all cells and remember whether any touches the border. Flip the collected cells only if none touches the border.

- Correct, but requires repeated bookkeeping for every component.
- Time: $O(RC)$
- Space: $O(RC)$

## Approach 2 — Reverse the question

Instead of proving which cells are surrounded, find the cells that **cannot** be surrounded:

1. Start DFS/BFS from every boundary `O`.
2. Mark every `O` reachable from them as safe.
3. Scan the board:
   - unmarked `O` → `X`
   - marked safe cell → `O`

```java
static void capture(char[][] board) {
    int rows = board.length;
    int cols = board[0].length;

    for (int r = 0; r < rows; r++) {
        markSafe(board, r, 0);
        markSafe(board, r, cols - 1);
    }
    for (int c = 0; c < cols; c++) {
        markSafe(board, 0, c);
        markSafe(board, rows - 1, c);
    }

    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            if (board[r][c] == 'O') board[r][c] = 'X';
            else if (board[r][c] == '#') board[r][c] = 'O';
        }
    }
}

static void markSafe(char[][] board, int r, int c) {
    if (r < 0 || r == board.length || c < 0 || c == board[0].length
            || board[r][c] != 'O') {
        return;
    }
    board[r][c] = '#';
    markSafe(board, r - 1, c);
    markSafe(board, r + 1, c);
    markSafe(board, r, c - 1);
    markSafe(board, r, c + 1);
}
```

- Time: $O(RC)$
- Recursion/queue space: $O(RC)$ worst case

The logic works because a region is uncapturable **if and only if** it is connected to a boundary `O`.



#  How Can We Tell Whether an Undirected Graph Is a Tree?



An undirected graph is a tree exactly when it is:

1. connected, and
2. acyclic.

Equivalent tests for a graph with $V$ vertices include:

$$
\text{connected and }E=V-1.
$$

## Approach 1 — DFS connectivity plus cycle detection

Run DFS from one vertex, reject a back edge to a non-parent, then ensure every vertex was visited.

## Approach 2 — Edge count plus connectivity

If $E\ne V-1$, immediately return false. Then one BFS/DFS is enough to test connectivity.

```java
static boolean isTree(List<List<Integer>> graph, int undirectedEdges) {
    int n = graph.size();
    if (n == 0 || undirectedEdges != n - 1) return false;

    boolean[] visited = new boolean[n];
    Queue<Integer> queue = new ArrayDeque<>();
    visited[0] = true;
    queue.offer(0);
    int seen = 0;

    while (!queue.isEmpty()) {
        int u = queue.poll();
        seen++;
        for (int v : graph.get(u)) {
            if (!visited[v]) {
                visited[v] = true;
                queue.offer(v);
            }
        }
    }
    return seen == n;
}
```

- Time: $O(V+E)$
- Space: $O(V)$



#  How Do We Detect a Cycle in an Undirected Graph?



In an undirected graph, every edge is stored twice. While DFS goes from `u` to `v`, the adjacency list of `v` naturally contains `u`. That immediate return edge is not a cycle, so DFS remembers the parent.

```text
        0
       / \
      1 — 2

DFS path 0 → 1 → 2
At 2, neighbour 0 is visited and is not parent 1 ⇒ cycle.
parent means immediate parent,

else if some other alrady visited node is visted again then its cycle
```

```java
static boolean hasUndirectedCycle(List<List<Integer>> graph) {
    boolean[] visited = new boolean[graph.size()];
    for (int u = 0; u < graph.size(); u++) {
        if (!visited[u] && dfsCycle(u, -1, graph, visited)) {
            return true;
        }
    }
    return false;
}

static boolean dfsCycle(
        int u, int parent,
        List<List<Integer>> graph,
        boolean[] visited) {

    visited[u] = true;
    for (int v : graph.get(u)) {
        if (!visited[v]) {
            if (dfsCycle(v, u, graph, visited)) return true;
        } else if (v != parent) {
            return true;
        }
    }
    return false;
}
```

- Time: $O(V+E)$
- Space: $O(V)$

## Why this test is different for directed graphs

In a directed graph, an edge to any previously visited vertex is not automatically a cycle. Directed DFS needs three states—or a recursion-stack flag—to distinguish an ancestor from a vertex whose exploration has already finished.

## Common mistakes

- Check every component, not only vertex `0`.
- Pass the current vertex as the child's parent.
- Do not apply the parent-only rule to directed graphs.
- Parallel edges require care: two edges between the same vertices form a length-two cycle in a multigraph.

