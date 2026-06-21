# Notes
![alt text](<002 dfs_240306_011019.jpg>)


 ![alt text](<002 dfs_240306_011019(1).jpg>) ![alt text](<002 dfs_240306_011019(2).jpg>) ![alt text](<002 dfs_240306_011019(3).jpg>) ![alt text](<002 dfs_240306_011019(4).jpg>) ![alt text](<002 dfs_240306_011019(5).jpg>) ![alt text](<002 dfs_240306_011019(6).jpg>)
 
 ```cpp
#include<iostream>
#include<list>
#include<queue>
using namespace std;


class Graph{

	int V;
	list<int> *l;

public:
	Graph(int v){
		V = v;
		l = new list<int>[V];
	}

	void addEdge(int i,int j,bool undir=true){
		l[i].push_back(j);
		if(undir){
			l[j].push_back(i);
		}
	}
	void dfsHelper(int node,bool *visited){
		visited[node] = true;
		cout<<node<<",";

		//make a dfs call on all its unvisited neighbours
		for(int nbr : l[node]){
			if(!visited[nbr]){
				dfsHelper(nbr,visited);
			}
		}
		return;

	}

	void dfs(int source){
		bool *visited = new bool[V]{0};
		dfsHelper(source,visited);
	}
};

int main(){
	Graph g(7);
	g.addEdge(0,1);
	g.addEdge(1,2);
	g.addEdge(2,3);
	g.addEdge(3,5);
	g.addEdge(5,6);
	g.addEdge(4,5);
	g.addEdge(0,4);
	g.addEdge(3,4);
	g.dfs(1);
	return 0;
}

 ```
 
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
#### Java
```java
import java.util.*;

class BFSsolution {
    /* Function to determine if the cell
     is valid (within grid's boundaries) */
    private boolean isValid(int i, int j, 
                            int n, int m) {
                                
        if (i < 0 || i >= n) return false;
        if (j < 0 || j >= m) return false;
        
        // Return true if cell is valid
        return true;
    }
    
    private void bfs(int i, int j, boolean[][] vis, 
                     char[][] grid) {
                         
        // mark it visited
        vis[i][j] = true;
        
        // Queue required for BFS traversal
        Queue<int[]> q = new LinkedList<>();
        
        // push the node in queue
        q.add(new int[]{i, j}); 
        
        // Dimensions of grid
        int n = grid.length; 
        int m = grid[0].length; 
      
        // Until the queue becomes empty
        while (!q.isEmpty()) {
            // Get the cell from queue
            int[] cell = q.poll();
            
            // Determine it's row & column
            int row = cell[0];
            int col = cell[1];
            
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
                        q.add(new int[]{newRow, newCol});
                    }
                }
            }
        }
    }
    
    // Function to find the number of islands in given grid
    public int numIslands(char[][] grid) {
        // Size of the grid
        int n = grid.length;
        int m = grid[0].length;
        
        // Visited array
        boolean[][] vis = new boolean[n][m];
        
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

    public static void main(String[] args) {
        char[][] grid = {
            {'1', '1', '1', '0', '1'},
            {'1', '0', '0', '0', '0'},
            {'1', '1', '1', '0', '1'},
            {'0', '0', '0', '1', '1'}
        };
        
        // Creating an instance of Solution class
        Solution sol = new Solution();
        
        /* Function call to find the
        number of islands in given grid */
        int ans = sol.numIslands(grid);
        
        System.out.println("The total islands in given grids are: " + ans);
    }
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

### java
```java

import java.util.*;

class Solution {

    private void dfs(int node, List<List<Integer>> adj, boolean[] vis, List<Integer> ans) {
        vis[node] = true;
        ans.add(node);

        for (int neighbor : adj.get(node)) {
            if (!vis[neighbor]) {
                dfs(neighbor, adj, vis, ans);
            }
        }
    }

    public List<Integer> dfsOfGraph(int V, List<List<Integer>> adj) {
        boolean[] vis = new boolean[V];
        List<Integer> ans = new ArrayList<>();

        for (int i = 0; i < V; i++) {
            if (!vis[i]) {
                dfs(i, adj, vis, ans);
            }
        }

        return ans;
    }

    private void bfs(int node, List<List<Integer>> adj, boolean[] vis, List<Integer> ans) {
        Queue<Integer> q = new LinkedList<>();
        q.add(node);
        vis[node] = true;

        while (!q.isEmpty()) {
            int current = q.poll();
            ans.add(current);

            for (int neighbor : adj.get(current)) {
                if (!vis[neighbor]) {
                    vis[neighbor] = true;
                    q.add(neighbor);
                }
            }
        }
    }

    public List<Integer> bfsOfGraph(int V, List<List<Integer>> adj) {
        boolean[] vis = new boolean[V];
        List<Integer> ans = new ArrayList<>();

        for (int i = 0; i < V; i++) {
            if (!vis[i]) {
                bfs(i, adj, vis, ans);
            }
        }

        return ans;
    }
}

class Main {
    public static void main(String[] args) {
        int V = 5;
        List<List<Integer>> adj = new ArrayList<>();
        for (int i = 0; i < V; i++) {
            adj.add(new ArrayList<>());
        }
        adj.get(0).addAll(Arrays.asList(2, 3, 1));
        adj.get(1).add(0);
        adj.get(2).addAll(Arrays.asList(0, 4));
        adj.get(3).add(0);
        adj.get(4).add(2);

        Solution sol = new Solution();

        List<Integer> bfs = sol.bfsOfGraph(V, adj);
        List<Integer> dfs = sol.dfsOfGraph(V, adj);

        System.out.println("The BFS traversal of the given graph is: " + bfs);
        System.out.println("The DFS traversal of the given graph is: " + dfs);
    }
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

