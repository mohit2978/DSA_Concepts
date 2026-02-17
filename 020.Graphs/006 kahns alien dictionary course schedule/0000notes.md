# Notes

![alt text](<005kahns aliendisctionary courseschedule_240307_120321.jpg>)

This problem is the classic **"Number of Connected Components"** graph problem. 

Since you've just mastered DFS/BFS and DSU, this is the perfect playground to see how both approaches solve the same problem. The problem gives you an Adjacency Matrix (`isConnected`), where `isConnected[i][j] = 1` means city $i$ and $j$ are connected. Your goal is to count how many isolated groups (provinces) exist.

---

### Approach 1: The "Component Counting" DFS

This uses the exact logic you learned today:

1.  **Create a `vis` array** of size $N$.
2.  **Loop through every city** from $0$ to $N-1$.
3.  **If a city is NOT visited**, it means you've found a **NEW Province**.
4.  **Start a traversal (DFS/BFS)** from that city to mark all connected cities in that province as visited.
5.  **Increment your counter.**

---

### Comparison of Methods

| Method | Logic | When to use? |
| :--- | :--- | :--- |
| **DFS / BFS** | Traverse as far as possible to "exhaust" a component. | Standard choice; very easy to implement. |
| **DSU** | `union(i, j)` for every connection; count unique roots at the end. | Best if the graph is **dynamic** (edges are being added over time). |

```cpp
class Solution {
private:
    // Standard DFS to visit all nodes in the current component
    void dfs(int node, vector<vector<int>>& isConnected, vector<bool>& vis) {
        vis[node] = true;
        
        // Traverse all possible neighbors
        for (int neighbor = 0; neighbor < isConnected.size(); neighbor++) {
            // Check if connected AND not visited yet
            if (isConnected[node][neighbor] == 1 && !vis[neighbor]) {
                dfs(neighbor, isConnected, vis);
            }
        }
    }

public:
    int findCircleNum(vector<vector<int>>& isConnected) {
        int n = isConnected.size();
        vector<bool> vis(n, false);
        int provinces = 0;

        // Iterate through every city
        for (int i = 0; i < n; i++) {
            // If we find an unvisited city, it's the "Head" of a new province
            if (!vis[i]) {
                provinces++;     // Found a new group
                dfs(i, isConnected, vis); // Mark the entire group as visited
            }
        }
        
        return provinces;
    }
};
```

Time Complexity: $O(N^2)$ (You visit every cell in the matrix once).

Space Complexity: $O(N)$ (Visited array + Recursion Stack).

## DSU code

```cpp
class Solution {
    vector<int> parent;
    vector<int> size;

    int find(int x) {
        if (parent[x] == x) return x;
        return parent[x] = find(parent[x]); // Path Compression
    }

    void unionSets(int x, int y) {
        int rootX = find(x);
        int rootY = find(y);
        
        if (rootX != rootY) {
            // Union by Size
            if (size[rootX] < size[rootY]) swap(rootX, rootY);
            parent[rootY] = rootX;
            size[rootX] += size[rootY];
        }
    }

public:
    int findCircleNum(vector<vector<int>>& isConnected) {
        int n = isConnected.size();
        parent.resize(n);
        size.resize(n, 1);
        
        // Initialize DSU
        for (int i = 0; i < n; i++) parent[i] = i;

        // Iterate strictly the Upper Triangle (to avoid duplicate checks)
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                if (isConnected[i][j] == 1) {
                    unionSets(i, j);
                }
            }
        }

        // Count unique parents (roots)
        int provinces = 0;
        for (int i = 0; i < n; i++) {
            if (parent[i] == i) provinces++;
        }
        return provinces;
    }
};
```
### Which one to use?

* **For Interviews:** **DFS/BFS (Approach 1)** is usually preferred here because the graph is static (given all at once) and the code is shorter and cleaner.
* **Use DSU if:** The graph is **dynamic** (e.g., "edges are being added one by one, tell me the province count after every addition").



## My code

```cpp
class Solution{
    void dfs(vector<bool>& vis,int v,vector<int> * graph,int n){
        vis[v]=true;
        for(int  nbr:graph[v]){
            if(vis[nbr]==false){
                dfs(vis,nbr,graph,n);
            }
        }
    }
public:
    int numProvinces(vector<vector<int>> adj) {
       int n=adj.size();
       vector<int> graph[n];
       for(int i=0;i<n;i++){
        for(int j=0;j<i;j++){
            if(adj[i][j]==1){
                graph[i].push_back(j);
                graph[j].push_back(i);
            }
        }
       }

        vector<bool> vis(n,false);
        int cnt=0;
        for(int i=0;i<n;i++){
            if(vis[i]==false){
                dfs(vis,i,graph,n);
                cnt++;
            } 
            
        }
        return cnt;

    }
};

```
This code is logically correct, but it uses a **Non-Standard C++ Feature** that might cause compilation errors in some interview environments (like Microsoft Visual Studio).

### The Issue: Variable Length Arrays (VLA)
The line `vector<int> graph[n];` tries to create a C-style array of vectors where the size `n` is a variable determined at runtime.

* **Standard C++:** Array sizes must be constant at compile time (e.g., `graph[100]`).
* **GCC/Clang:** Often allow this as an "extension," which is why it might pass on LeetCode but fail in other environments.
* **Best Practice:** Use a vector of vectors: `vector<vector<int>> graph(n);`.

### Corrected Code (Standard C++)
Here is the robust version. I also updated the DFS signature to accept the graph by reference (`&`) to avoid unnecessary copying.
## Ai code

```cpp

class Solution {
    // Pass graph by reference: vector<vector<int>>& graph
    void dfs(vector<bool>& vis, int v, vector<vector<int>>& graph) {
        vis[v] = true;
        for (int nbr : graph[v]) {
            if (!vis[nbr]) {
                dfs(vis, nbr, graph);
            }
        }
    }

public:
    int numProvinces(vector<vector<int>>& adj) {
        int n = adj.size();
        
        // Fix: Use vector of vectors instead of C-style array
        vector<vector<int>> graph(n);

        // Build Adjacency List
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < i; j++) { // Loop < i handles lower triangle (avoids duplicates)
                if (adj[i][j] == 1) {
                    graph[i].push_back(j);
                    graph[j].push_back(i);
                }
            }
        }

        vector<bool> vis(n, false);
        int cnt = 0;
        
        for (int i = 0; i < n; i++) {
            if (!vis[i]) {
                dfs(vis, i, graph);
                cnt++;
            } 
        }
        return cnt;
    }
};
```


  
  ---
  
  ![alt text](<005kahns aliendisctionary courseschedule_240307_120321(4).jpg>) ![alt text](<005kahns aliendisctionary courseschedule_240307_120321(5).jpg>) ![alt text](<005kahns aliendisctionary courseschedule_240307_120321(6).jpg>) ![alt text](<005kahns aliendisctionary courseschedule_240307_120321(7).jpg>) ![alt text](<005kahns aliendisctionary courseschedule_240307_120321(8).jpg>) ![alt text](<005kahns aliendisctionary courseschedule_240307_120321(9).jpg>) ![alt text](<005kahns aliendisctionary courseschedule_240307_120321(10).jpg>)




![alt text](<005kahns aliendisctionary courseschedule_240307_120321(11).jpg>) ![alt text](<005kahns aliendisctionary courseschedule_240307_120321(12).jpg>) ![alt text](<005kahns aliendisctionary courseschedule_240307_120321(13).jpg>) ![alt text](<005kahns aliendisctionary courseschedule_240307_120321(14).jpg>) ![alt text](<005kahns aliendisctionary courseschedule_240307_120321(15).jpg>) ![alt text](<005kahns aliendisctionary courseschedule_240307_120321(16).jpg>)  ![alt text](<005kahns aliendisctionary courseschedule_240307_120321(18).jpg>) 


### Kahns algo cpp code
 
```cpp
class Solution{
public:
    vector<int> topoSort(int V, vector<int> adj[]){
        vector<int>indegree(V,0);
        for(int i=0;i<V;i++){
            for(auto el:adj[i]){
                indegree[el]++;
            }
        }
        queue<int>q;
        for(int i=0;i<V;i++){
            if(indegree[i]==0) q.push(i);
        }
        vector<int>res(V,0);
        int i=0;
        while(q.size()>0){
            int v=q.front();
            q.pop();
            res[i++]=v;
            for(int el:adj[v]){
                indegree[el]--;
                if(indegree[el]==0) q.push(el);
            }
        }
        return res;
    }
};


```
![alt text](<005kahns aliendisctionary courseschedule_240307_120321(17).jpg>)
### Dtetect a cycle in directed graph 

```cpp
class Solution {
    bool topoSort(int V, vector<int> adj[]) {
        vector<int> indegree(V, 0);
        for (int i = 0; i < V; i++) {
            for (auto el : adj[i]) {
                indegree[el]++;
            }
        }
        queue<int> q;
        int cnt = 0;
        for (int i = 0; i < V; i++) {
            if (indegree[i] == 0) {
                cnt++;
                q.push(i);
            }
        }
        vector<int> res(V, 0);
        int i = 0;

        while (q.size() > 0) {
            int v = q.front();
            q.pop();
            res[i++] = v;
            for (int el : adj[v]) {
                indegree[el]--;
                if (indegree[el] == 0) {
                    q.push(el);
                    cnt++;
                }
            }
        }
        return cnt < V;
    }

   public:
    bool isCyclic(int N, vector<int> adj[]) { 
        return topoSort(N, adj); }
};

```

## DFS sol

```cpp
#include <bits/stdc++.h>
using namespace std;

class Solution {
private:

    // Function to perform DFS traversal
    bool dfs(int node, vector<int> adj[], 
             vector<bool> &visited, 
             vector<bool> &pathVisited) {
                 
        // Mark the node as path visited
        visited[node] = true;
        
        // Mark the node as path visited
        pathVisited[node] = true;
        
        // Traverse all the neighbors
        for(auto it : adj[node]) {
            
            /* If the neighbor is already visited 
            in the path, a cycle is detected */
            if(pathVisited[it]) 
                return true;
            
            /* Else if the node is unvisited, 
            perform DFS recursively from this node */
            else if(!visited[it]) {
                
                // If cycle is detected, return true
                if(dfs(it, adj, visited, pathVisited)) 
                    return true;
            }
        }
        
        // Remove the node from path 
        pathVisited[node] = false;
        
        // Return false if no cycle is detected
        return false;
    }
    
public:

    // Function to detect cycle in a directed graph.
    bool isCyclic(int V, vector<int> adj[]) {
        
        // Visited array
        vector<bool> visited(V, false);
        
        /* Array to mark nodes that are 
        visited in a particular path */
        vector<bool> pathVisited(V, false);
        
        // Traverse the graph
        for(int i=0; i<V; i++) {
            if(!visited[i]) {
                
                // If a cycle is found, return true
                if(dfs(i, adj, visited, pathVisited)) 
                    return true;
            }
        }
        
        /* Return false if no cycle is 
        detected in any component */
        return false;
    }
};

int main() {
    
    int V = 6;
    vector<int> adj[V] = {
        {1}, 
        {2, 5}, 
        {3}, 
        {4}, 
        {1},
        {} 
    };
    
    /* Creating an instance of 
    Solution class */
    Solution sol; 
    
    /* Function call to determine if cycle 
    exists in given directed graph */
    bool ans = sol.isCyclic(V, adj);
    
    // Output
    if(ans)
        cout << "The given directed graph contains a cycle.";
    else 
        cout << "The given directed graph does not contain a cycle.";
    
    return 0;
}
```

This is the classic **Kahn's Algorithm (BFS)** vs. **Backtracking (DFS)** debate for Directed Acyclic Graphs (DAGs).

Given your constraint $N \le 10^4$, both are mathematically efficient ($O(V+E)$), but **Solution 1 (Kahn's BFS)** is the superior "Software Engineering" choice for modern interviews.

### 1. The Stability Factor (Stack Overflow)
As we discussed previously with Trees, DFS relies on the **System Recursion Stack**.
* **Solution 2 (DFS):** If the graph is just a long line (e.g., $1 \to 2 \to 3 \dots \to 10^4$), your recursion depth will be $10,000$. On many systems (like some GFG or LeetCode test runners), the default stack limit is small. This can trigger a **Stack Overflow crash**.
* **Solution 1 (BFS):** Uses a queue on the **Heap**. The heap is gigabytes in size. It will never crash, even if the graph is a straight line of $10^6$ nodes.

### 2. The Logic: Why BFS works for Cycles
Kahn's algorithm is based on a simple fact: A directed cycle has no "start" (node with indegree 0).
* If a graph has a cycle, the indegree of nodes in that cycle will never hit 0.
* Consequently, those nodes never enter the queue.
* Therefore, the total count of nodes processed (`cnt`) will be less than the total nodes in the graph ($V$).
* This logic is extremely clean and avoids the need for a separate `pathVisited` array.

### 3. Complexity Comparison

| Feature | Solution 1 (BFS/Kahn's) | Solution 2 (DFS) |
| :--- | :--- | :--- |
| **Time** | $O(V + E)$ | $O(V + E)$ |
| **Space** | $O(V)$ (Queue + Indegree) | $O(V)$ (Visited + PathVisited + Recursion) |
| **Safety** | **High** (Iterative) | **Low** (Recursion risk) |
| **Utility** | Also gives you the **Sorted Order** | Only tells you **Yes/No** |

![alt text](<005kahns aliendisctionary courseschedule_240307_120321(19).jpg>) 

# Course Schedule I

There are a total of **N** tasks, labeled from **0** to **N-1**.

Given an array `arr` where `arr[i] = [a, b]` indicates that you must take course **b** first if you want to take course **a**.

Find if it is possible to finish all tasks.

### Example 1

**Input:** `N = 4, arr = [[1,0],[2,1],[3,2]]`

**Output:** `True`

**Explanation:**
It is possible to finish all the tasks in the order: `0 -> 1 -> 2 -> 3`.
First, we will finish task 0. Then we will finish task 1, task 2, and task 3.

### Example 2

**Input:** `N = 4, arr = [[0,1],[3,2],[1,3],[3,0]]`

**Output:** `False`

**Explanation:**
It is impossible to finish all the tasks. Let's analyze the pairs:
* For pair `{0, 1}` -> we need to finish task 1 first and then task 0. (order: `1 -> 0`).
* For pair `{3, 2}` -> we need to finish task 2 first and then task 3. (order: `2 -> 3`).
* For pair `{1, 3}` -> we need to finish task 3 first and then task 1. (order: `3 -> 1`).
* But for pair `{3, 0}` -> we need to finish task 0 first and then task 3 but task 0 requires task 1 and task 1 requires task 3. So, it is not possible to finish all the tasks (Cycle Detected).

### Constraints

* `1 <= N <= 2000`
* `0 <= arr.length <= 5000`
* `arr[i].length == 2`
* `0 <= arr[i][0], arr[i][1] < N`
* All the pairs `arr[i]` are unique.



```cpp
class Solution {
   public:
    bool canFinish(int N, vector<vector<int>> arr) {
        vector<vector<int>> graph(N);
        for (auto edge : arr) {
            int u = edge[0];
            int v = edge[1];
            graph[v].push_back(u);
        }
        vector<int> indegree(N, 0);
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < graph[i].size(); j++) {
                indegree[graph[i][j]]++;
            }
        }
        int cnt = 0;
        queue<int> q;
        for (int i = 0; i < N; i++) {
            if (indegree[i] == 0) {
                q.push(i);
                cnt++;
            }
        }
        while (q.size() > 0) {
            int rem = q.front();
            q.pop();

            for (int j = 0; j < graph[rem].size(); j++) {
                indegree[graph[rem][j]]--;
                if (indegree[graph[rem][j]] == 0) {
                    cnt++;
                    q.push(graph[rem][j]);
                }
            }
        }
        return cnt == N;
    }
};
```





![alt text](<005kahns aliendisctionary courseschedule_240307_120321(20).jpg>) 

```cpp
class Solution {
   public:
    vector<int> findOrder(int N, vector<vector<int>> arr) {
        vector<vector<int>> graph(N);
        for (auto edge : arr) {
            int u = edge[0];
            int v = edge[1];
            graph[v].push_back(u);
        }
        vector<int> indegree(N, 0);
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < graph[i].size(); j++) {
                indegree[graph[i][j]]++;
            }
        }
        vector<int> ans(N,0);
        int i=0;
        queue<int> q;
        for (int i = 0; i < N; i++) {
            if (indegree[i] == 0) {
                q.push(i);
                
            }
        }
        while (q.size() > 0) {
            int rem = q.front();
            q.pop();
            ans[i++]=rem;
            for (int j = 0; j < graph[rem].size(); j++) {
                indegree[graph[rem][j]]--;
                if (indegree[graph[rem][j]] == 0) {
                    q.push(graph[rem][j]);
                }
            }
        }
        
        return i==N?ans:vector<int>();
    }
};

```

## Ai review

```cpp
class Solution {
public:
    vector<int> findOrder(int N, vector<vector<int>>& prerequisites) {
        vector<vector<int>> graph(N);
        vector<int> indegree(N, 0);
        
        // 1. Build Graph & Indegree in ONE pass
        // Prereq[1] is the dependency, Prereq[0] is the target
        // Edge: Dependency -> Target
        for (auto& edge : prerequisites) {
            graph[edge[1]].push_back(edge[0]);
            indegree[edge[0]]++;
        }
        
        // 2. Queue for 0-indegree nodes
        queue<int> q;
        for (int i = 0; i < N; i++) {
            if (indegree[i] == 0) q.push(i);
        }
        
        // 3. Process
        vector<int> ans;
        while (!q.empty()) {
            int curr = q.front();
            q.pop();
            ans.push_back(curr);
            
            for (int neighbor : graph[curr]) {
                indegree[neighbor]--;
                if (indegree[neighbor] == 0) {
                    q.push(neighbor);
                }
            }
        }
        
        // 4. Cycle Check (Did we process everyone?)
        if (ans.size() == N) return ans;
        return {};
    }
};
````








































