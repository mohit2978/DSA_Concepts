# Notes 
![alt text](<004dijsktra bipartite_240205_000336.jpg>)
![alt text](<004dijsktra bipartite_240205_000336(1).jpg>) ![alt text](<004dijsktra bipartite_240205_000336(2).jpg>) 

### BFS solution

```cpp
class Solution{
 bool bfsCycle(int i,vector<int> adj[],int V,vector<bool>& vis){
    queue<int>q;
    q.push(i);
    while(q.size()>0){
        int v=q.front();
        q.pop();
        if(vis[v]==true) return true;
        vis[v]=true;
        for(auto nbr:adj[v]){
            if(vis[nbr]==false) q.push(nbr);
        }
    }
    return false;
 }
public:
    bool isCycle(int V, vector<int> adj[]) {
        vector<bool>vis(V,false);
        for(int i=0;i<V;i++){
            if(vis[i]==false){
               bool val= bfsCycle(i,adj,V,vis);
               if(val==true) return true;
            }
        }

        return false;
    }
};
```
### DFSsol

```cpp
class Solution{
 bool dfsCycle(int i,vector<int> adj[],int V,vector<bool>& vis,int par){
    vis[i]=true;
    for(auto nbr:adj[i]){
        if(vis[nbr]==false){
           bool val= dfsCycle(nbr,adj,V,vis,i);
           if(val==true) return true;
        }// If the neighbor is visited and it's NOT the parent, we found a cycle!
        else if (nbr != par) {
            return true;
        }
    }
    return false;
 }
public:
    bool isCycle(int V, vector<int> adj[]) {
        vector<bool>vis(V,false);
        for(int i=0;i<V;i++){
            if(vis[i]==false){
               bool val= dfsCycle(i,adj,V,vis,-1);
               if(val==true) return true;
            }
        }

        return false;
    }
};
```
Most recursive functions start with a base case, but in this specific algorithm, that first line(`if(vis[i]==true) return true`) actually becomes redundant (and slightly problematic) because of how we handle the neighbor loop.

Here is why you don't need it:

#### 1. The "Look Before You Leap" Strategy
In the corrected version of the code, we perform the "visited" check before making the recursive call.

```C++

for (auto nbr : adj[i]) {
    if (!vis[nbr]) { 
        // We only call the function if we KNOW vis[nbr] is false
        if (dfsCycle(nbr, adj, V, vis, i)) return true;
    } 
    else if (nbr != par) {
        // If it's already visited and NOT the parent, it's a cycle
        return true; 
    }
}
```
Because of the if `(!vis[nbr])` guard, the function dfsCycle will never be called with an i that is already visited. Therefore, checking it again at the very top of the function is redundant—it's like checking if a door is locked after you’ve already confirmed it's open and walked through it.


#### 2. Distinguishing Cycles from Back-Tracing

In an undirected graph, every edge is a two-way street. If you are at Node A and move to Node B, Node B's neighbor list contains Node A.

If you kept your original if(vis[i] == true) return true at the top, the moment the algorithm looks back from Node B to Node A, it would see Node A is "visited" and immediately declare a cycle.

By removing that top check and using the else if (nbr != par) logic inside the loop, you specifically tell the code:

"If I see a visited node and it's my parent, that's just the way I came in. Ignore it."

"If I see a visited node and it's not my parent, I've found a shortcut back to an earlier part of the path. That is a cycle."

### Summary
The check at the top is replaced by a more surgical check inside the loop that can tell the difference between a back-edge (a cycle) and the parent-edge (the path you are currently walking).

![alt text](<004dijsktra bipartite_240205_000336(3).jpg>) ![alt text](<004dijsktra bipartite_240205_000336(4).jpg>) ![alt text](<004dijsktra bipartite_240205_000336(5).jpg>) ![alt text](<004dijsktra bipartite_240205_000336(6).jpg>) ![alt text](<004dijsktra bipartite_240205_000336(7).jpg>) ![alt text](<004dijsktra bipartite_240205_000336(8).jpg>) ![alt text](<004dijsktra bipartite_240205_000336(9).jpg>) ![alt text](<004dijsktra bipartite_240205_000336(10).jpg>) ![alt text](<004dijsktra bipartite_240205_000336(11).jpg>) ![alt text](<004dijsktra bipartite_240205_000336(12).jpg>) ![alt text](<004dijsktra bipartite_240205_000336(13).jpg>) ![alt text](<004dijsktra bipartite_240205_000336(14).jpg>) ![alt text](<004dijsktra bipartite_240205_000336(15).jpg>) ![alt text](<004dijsktra bipartite_240205_000336(16).jpg>) ![alt text](<004dijsktra bipartite_240205_000336(17).jpg>) ![alt text](<004dijsktra bipartite_240205_000336(18).jpg>) ![alt text](<004dijsktra bipartite_240205_000336(19).jpg>) ![alt text](<004dijsktra bipartite_240205_000336(20).jpg>) ![alt text](<004dijsktra bipartite_240205_000336(21).jpg>) ![alt text](<004dijsktra bipartite_240205_000336(22).jpg>) ![alt text](<004dijsktra bipartite_240205_000336(23).jpg>) ![alt text](<004dijsktra bipartite_240205_000336(24).jpg>)

```java
class Solution
{
    static class trip{
        int v;
        int wt;
        trip(int v,int wt){
            this.v=v;
            this.wt=wt;
        }
    }
    public  int[] dijkstra(int V, ArrayList<ArrayList<ArrayList<Integer>>> adj, int S)
    {
        PriorityQueue<trip> pq=new PriorityQueue<>((trip a,trip b)-> (a.wt-b.wt));
        pq.add(new trip(S ,0));
        boolean[] vis=new boolean[V];
        int[] res=new int[V];
        Arrays.fill(res, (int)1e9);
        while(pq.size()>0){
            trip rem=pq.remove();
            if(vis[rem.v]==true) continue;
            vis[rem.v]=true;
            res[rem.v]=rem.wt;
            for(var itr:adj.get(rem.v)){
                int nbr=itr.get(0);
                int w=itr.get(1);
                if(vis[nbr]==false){
                    pq.add(new trip(nbr,rem.wt+w));
                }
            }
        }
        
       return res;
    }
}

```
### Cpp code

```cpp
class Solution {
public:
    vector<int> dijkstra(int V, vector<vector<vector<int>>> &adj, int S) {
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        pq.push({0, S});
        
        vector<int> res(V, 1e9);
        vector<bool> vis(V, false);
        
        while(!pq.empty()) {
            int wt = pq.top().first;
            int v = pq.top().second;
            pq.pop();
            
            if(vis[v]) continue;
            vis[v] = true;
            res[v] = wt;
            
            for(auto &it : adj[v]) {
                int nbr = it[0];
                int w = it[1];
                if(!vis[nbr]) {
                    pq.push({wt + w, nbr});
                }
            }
        }
        return res;
    }
};
```

### "Blind Push" vs. "Edge Relaxation" in Dijkstra

The main difference between these two approaches lies in efficiency and the total number of items pushed into the Priority Queue (PQ).

---

### 1. Your Approach ("Blind Push")
In this version, you push a neighbor into the PQ every time you encounter an edge to an unvisited node, regardless of the path's quality.

* **The Logic:** `if (!vis[nbr]) { pq.push(...) }`
* **The Problem:** Suppose you have already found a path to **Node B** with a cost of **10**. Later, you find another path to **Node B** with a cost of **100**.
    * **Your code checks:** "Is B visited?" No.
    * **Action:** It pushes `{100, B}` into the PQ.
* **Result:** You now have a "trash" entry in your heap. While the algorithm will eventually discard it, these redundant entries waste memory and increase the $O(\log N)$ overhead for every subsequent heap operation.

---

### 2. The Standard Approach ("Edge Relaxation")
Standard Dijkstra only pushes a node into the PQ if the new path is **strictly better** (shorter) than the best path found so far.

* **The Logic:** `if (dist[u] + weight < dist[v]) { dist[v] = ...; pq.push(...); }`
* **The Benefit:** Using the same example (current best to B is 10, new path is 100):
    * **Standard code checks:** "Is 100 < 10?" No.
    * **Action:** It does nothing.
* **Result:** The "trash" path never enters the PQ. This keeps the heap size to a minimum, ensuring the algorithm runs at peak speed.

---

### Comparison Summary

| Feature | Blind Push | Edge Relaxation (Standard) |
| :--- | :--- | :--- |
| **PQ Size** | Large (Contains redundant paths) | **Small** (Only optimal paths) |
| **Heap Overhead** | Higher (More $O(\log N)$ ops) | **Lower** |
| **Memory** | Higher | **Efficient** |
| **Verdict** | Okay for beginners | **Recommended for Production/CP** |

---
## Relax edge code
```cpp

class Solution {
public:
    vector<int> dijkstra(int V, vector<vector<vector<int>>> &adj, int S) {
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        vector<int> dist(V, 1e9);

        dist[S] = 0;
        pq.push({0, S});

        while (!pq.empty()) {
            int d = pq.top().first;
            int node = pq.top().second;
            pq.pop();

            if (d > dist[node]) continue;

            for (auto &it : adj[node]) {
                int adjNode = it[0];
                int edgeWeight = it[1];

                if (d + edgeWeight < dist[adjNode]) {
                    dist[adjNode] = d + edgeWeight;
                    pq.push({dist[adjNode], adjNode});
                }
            }
        }
        return dist;
    }
};

```
### Dijkstra's Algorithm: Complexity Analysis

For the standard **Adjacency List + Min-Priority Queue (Binary Heap)** implementation, the complexities are as follows:

---

### Time Complexity: $O(E \log V)$

* **$E$:** Number of Edges
* **$V$:** Number of Vertices

**Why?**
1.  **Edge Traversal:** we traverse every edge in the graph at least once ($O(E)$).
2.  **Heap Operations:** For every edge, we might push a new node into the priority queue or update a distance.
3.  **Logarithmic Cost:** Inserting into or popping from a binary heap takes logarithmic time relative to the number of items. In the worst case, the heap can hold up to $E$ items (one for each edge).

> **The Math:** $E \times \log(E)$. Since $E \le V^2$ in a simple graph, $\log(E) \le \log(V^2)$, which is $2 \log(V)$. This simplifies the constant to $O(E \log V)$.

---

### Space Complexity: $O(V + E)$

* **$O(V + E)$:** To store the graph using an **Adjacency List**.
* **$O(V)$:** To store the `dist` array and the **priority_queue** (which, in a optimized implementation, stores at most $V$ nodes).

---

### Comparison of Implementations

| Implementation | Time Complexity | Best Use Case |
| :--- | :--- | :--- |
| **Binary Heap (Priority Queue)** | $O(E \log V)$ | **Sparse Graphs** (Most Interview Problems) |
| **Array (Naive)** | $O(V^2)$ | **Dense Graphs** (where $E \approx V^2$) |
| **Fibonacci Heap** | $O(E + V \log V)$ | Theoretical best (Often too complex for interviews) |

---


>Note: Dijkstra doesnt work for negative weights ,it only works for positive weights ,for negative weights we have bellman ford!!


# Q Get shortest path from 1 to n,given edge list

## My code

```cpp
class Solution {
public:
    vector<int> shortestPath(int n, int m, vector<vector<int>>& edges) {
        vector<vector<pair<int, int>>> adj(n + 1);
        for (auto& edge : edges) {
            adj[edge[0]].push_back({edge[1], edge[2]});
            adj[edge[1]].push_back({edge[0], edge[2]});
        }

        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        pq.push({0, 1});

        vector<int> dist(n + 1, 1e9);
        vector<int> par(n + 1);
        for (int i = 1; i <= n; i++) par[i] = i;
        dist[1] = 0;

        while (!pq.empty()) {
            int d = pq.top().first;
            int node = pq.top().second;
            pq.pop();

            if (d > dist[node]) continue;

            for (auto& it : adj[node]) {
                int nbr = it.first;
                int w = it.second;

                if (d + w < dist[nbr]) {
                    dist[nbr] = d + w;
                    par[nbr] = node;
                    pq.push({d + w, nbr});
                }
            }
        }

        if (par[n] == n) return {-1};

        vector<int> path;
        int node = n;
        while (par[node] != node) {
            path.push_back(node);
            node = par[node];
        }
        path.push_back(1);
        reverse(path.begin(), path.end());
        path.insert(path.begin(), dist[n]);
        
        return path;
    }
};
```
# Why `if (d > dist[node]) continue;`??

## Lazy Deletion in Dijkstra's Algorithm

This is a critical optimization known as **"Lazy Deletion."**

Here is the "Senior Engineer" explanation of why that line is mandatory for performance, even though the algorithm works without it.

### 1. The Problem: Duplicate Entries
Standard C++ `priority_queue` does not support the `decrease_key` operation.
* **Ideal Dijkstra:** If we find a shorter path to a node already in the queue, we update its value.
* **Real (C++) Dijkstra:** We cannot update the value inside the heap. Instead, we just push a new pair `{new_dist, node}` into the queue.

**Result:** The Priority Queue ends up containing multiple versions of the same node.
* **Version 1:** `{10, NodeA}` (Old, worse path)
* **Version 2:** `{5, NodeA}` (New, better path)

### 2. The Execution Flow
1.  **Pop Version 2:** The min-heap pops `{5, NodeA}` first (because $5 < 10$).
2.  **Process:** You relax all neighbors of Node A using distance 5. `dist[NodeA]` is now finalized as 5.
3.  **Time Passes...**
4.  **Pop Version 1:** Eventually, the heap pops the "stale" entry `{10, NodeA}`.

### 3. The "Guard Clause"
**Without the line** `if (d > dist[node]) continue;`:
* You would take this outdated path (cost 10).
* You would iterate through all of Node A's neighbors again.
* You would try to relax edges using a suboptimal distance ($10 + weight$), which is waste of CPU cycles.

**With the Guard Clause:**
```cpp
// Popped: d = 10, node = A
// Current Best: dist[A] = 5

if (10 > 5) continue; // TRUE! Skip this garbage.
```

### Summary

* **Is it for Correctness?** No. Dijkstra will still give the right answer without it (redundant relaxations won't find a shorter path).
* **Is it for Complexity?** **YES.**
    * **With Check:** Each node is processed once. Complexity: $O(E \log V)$.
    * **Without Check:** Each edge pushing to the queue could trigger a process. Complexity degrades towards $O(E \cdot \text{Degree} \cdot \log E)$, which effectively makes it much slower on dense graphs.

> **Senior Tip:** This line converts the "Push duplicate" workaround from a memory leak into a valid $O(E \log V)$ implementation. **Always include it.**

## Striver code
```cpp
#define P pair<int,int>

class Solution {
public:

    vector<int> shortestPath(int n, int m, 
                vector<vector<int>> &edges) {
        vector<P> adj[n + 1];
        
        for (auto it : edges) {
            adj[it[0]].push_back({it[1], it[2]});
            adj[it[1]].push_back({it[0], it[2]});
        }
        priority_queue<P, vector<P>, greater<P>> pq;
        vector<int> dist(n + 1, 1e9);
        vector<int> parent(n + 1);
        for (int i = 1; i <= n; i++)
            parent[i] = i;
        dist[1] = 0;
        pq.push({0, 1});//0 is weight 1 is vertex
        
        while (!pq.empty())
        {
           
            auto it = pq.top();
            pq.pop();
            
            int node = it.second; // node
            int dis = it.first; // distance

        
            for (auto it : adj[node]) {
                
                int adjNode = it.first; // node
                int edWt = it.second; // edge weight


                if (dis + edWt < dist[adjNode]) {
                    

                    dist[adjNode] = dis + edWt;
                    pq.push({dis + edWt, adjNode});
                    parent[adjNode] = node;
                }
            }
        }
        if (dist[n] == 1e9)
            return {-1};


        vector<int> path;
        int node = n;
        while (parent[node] != node) {

            path.push_back(node); 
            node = parent[node];
        }

        path.push_back(1);//as on 1 par[1]=1 so never push_backed  1 in loop
        reverse(path.begin(), path.end());
        path.insert(path.begin(), dist[n]);//added distance at first as ques demands

        return path;
    }
};

```
# The "Senior Engineer" Breakdown: Disadvantages of Dijkstra's Algorithm

Here is the "Senior Engineer" breakdown of the disadvantages of Dijkstra's Algorithm, ranging from the obvious to the nuanced.

### 1. The Critical Failure: Negative Edges
This is the most famous limitation.
* **The Issue:** Dijkstra assumes that adding an edge always increases (or keeps constant) the path length. This allows it to "finalize" a node once visited.
* **The Consequence:** If you have negative weights, Dijkstra's "Greedy" approach settles on a suboptimal path because it never looks back to correct itself.
* **The Fix:** Use **Bellman-Ford** ($O(V \cdot E)$) or **SPFA** (Shortest Path Faster Algorithm).

### 2. It is "Blind" (Uninformed Search)
Dijkstra explores the graph like a expanding circle (or spilling water). It searches in all directions equally, even if the target is clearly to the East.
* **The Waste:** If you are finding a path from New York to London, Dijkstra will waste time calculating paths to South Africa and Tokyo because it doesn't know where London is.
* **The Fix:** Use **A* (A-Star) Search**. It uses a "Heuristic" (like Euclidean distance) to prioritize nodes that move towards the target, making it much faster for point-to-point pathfinding.

### 3. Overkill for Unweighted Graphs
If all edge weights are 1 (or equal), Dijkstra is overkill.
* **The Overhead:** Dijkstra uses a Priority Queue (Min-Heap), which adds a $\log V$ factor to every operation.
* **The Fix:** Use standard **BFS (Breadth-First Search)**. It runs in $O(V + E)$ compared to Dijkstra's $O(E \log V)$.

### 4. Overkill for DAGs (Directed Acyclic Graphs)
If you know for a fact your graph has no cycles (e.g., a dependency graph or project schedule), Dijkstra is too slow.
* **The Fix:** You can find the shortest path in a DAG using **Topological Sort + Linear Scan** in just $O(V + E)$ time.

### Summary Table

| Scenario | Dijkstra's Disadvantage | Better Alternative |
| :--- | :--- | :--- |
| **Negative Edges** | Returns wrong answer. | Bellman-Ford |
| **Target Known** | Wastes time searching opposite directions. | A* (A-Star) |
| **Unweighted Graph** | Unnecessary $\log V$ overhead. | BFS |
| **No Cycles (DAG)** | Slower than linear time. | Topological Sort |


# Why Dijkstra's Algorithm Fails with Negative Weights

The core reason Dijkstra's algorithm fails with negative weights is because it is a **Greedy Algorithm** that makes a permanent decision based on local information.

It assumes that once a node is processed (finalized), its shortest path is found and will never change. Negative weights break this assumption.

### The "Greedy" Flaw
Dijkstra follows this logic:
1.  Pick the unvisited node with the smallest distance (let's call it $U$).
2.  Mark $U$ as visited/finalized.
3.  Relax its neighbors.

**The Logic:** "Since $U$ is the closest node right now, and all edge weights are positive, there is no way I can go to a distant node $V$, take an edge back to $U$, and find a shorter path. Adding positive numbers only makes paths longer."

**The Failure:** A negative edge allows a path to get shorter as you add more edges. Dijkstra doesn't account for this "time travel" effect where a longer path suddenly becomes cheaper.

---

### A Concrete Counter-Example
Imagine a graph with Nodes A, B, and C. Start at A.
* **A → B** (Cost: 2)
* **A → C** (Cost: 5)
* **C → B** (Cost: -10)

**Correct Shortest Path to B:**
$A \to C \to B = 5 + (-10) = -5$.

**How Dijkstra Fails:**
1.  **Start at A:**
    * Distance to A: 0
    * PQ: `{ (A, 0) }`
2.  **Pop A:**
    * Relax neighbors:
    * B: 2
    * C: 5
    * PQ: `{ (B, 2), (C, 5) }`
3.  **Pop B (Cost 2):**
    * **CRITICAL ERROR:** Dijkstra sees B has the smallest distance (2 vs 5). It pops B and marks it as **Visited**.
    * Dijkstra declares: "The shortest path to B is 2."
    * It will never check B again.
4.  **Pop C (Cost 5):**
    * C is visited.
    * Relax neighbor B: New path $A \to C \to B$ is $5 + (-10) = -5$.
    * Since B is already marked "Visited", Dijkstra (standard version) ignores this update.

**Result:** Dijkstra returns **2**, but the answer is **-5**.

---

### What algorithm should you use instead?
If your graph has negative edges (but no negative cycles), you must use **Bellman-Ford**.

* **Dijkstra:** $O(E \log V)$ — Fast, assumes non-negative weights.
* **Bellman-Ford:** $O(V \cdot E)$ — Slower, works with negative weights, detects negative cycles.