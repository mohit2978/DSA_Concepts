# Q1. Dijkstra

```java
import java.util.*;

class DijkstraPaths {
    static class Edge {
        int nbr;
        int wt;

        Edge(int nbr, int wt) {
            this.nbr = nbr;
            this.wt = wt;
        }
    }

    static class Trip implements Comparable<Trip> {
        int v;
        String psf;
        int wt;

        Trip(int v, String psf, int wt) {
            this.v = v;
            this.psf = psf;
            this.wt = wt;
        }

        public int compareTo(Trip other) {
            if (this.wt > other.wt) return 1;
            else if (this.wt < other.wt) return -1;
            else return 0;
        }
    }

    static void printShortestPaths(List<List<Edge>> graph, int src) {
        PriorityQueue<Trip> pq = new PriorityQueue<>();
        pq.add(new Trip(src, src + "", 0));
        boolean[] vis = new boolean[graph.size()];

        while (!pq.isEmpty()) {
            Trip removed = pq.remove();
            if (vis[removed.v]) continue;
            vis[removed.v] = true;
            System.out.println(removed.v + " via " + removed.psf + " @ " + removed.wt);

            for (Edge e : graph.get(removed.v)) {
                if (!vis[e.nbr]) {
                    pq.add(new Trip(e.nbr, removed.psf + e.nbr, removed.wt + e.wt));
                }
            }
        }
    }

    public static void main(String[] args) {
        int[][] edges = {
            {0, 1, 10}, {0, 3, 40}, {1, 2, 10}, {2, 3, 10},
            {3, 4, 2}, {4, 5, 3}, {4, 6, 8}, {5, 6, 3}
        };
        List<List<Edge>> graph = new ArrayList<>();
        for (int i = 0; i < 7; i++) graph.add(new ArrayList<>());
        for (int[] e : edges) {
            graph.get(e[0]).add(new Edge(e[1], e[2]));
            graph.get(e[1]).add(new Edge(e[0], e[2]));
        }
        printShortestPaths(graph, 0);
    }
}
```


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

### Dijkstra with a Priority Queue of Triplets

The traversal resembles BFS, but replaces the FIFO queue with a min-priority queue ordered by total path weight. Each entry contains `(vertex, path-so-far, weight-so-far)`.

1. Insert the source with its own label as the path and weight zero.
2. Remove the entry with the smallest accumulated weight.
3. If its vertex was already visited, skip the entry.
4. Mark the vertex visited and print its path and weight.
5. For each unvisited neighbour, append that neighbour to the path and add the edge weight before inserting the new triplet.

Mark on removal, not on insertion: an expensive entry may be inserted before a cheaper route to the same vertex is discovered. The first non-skipped removal finalizes that vertex's distance. A later entry for the same vertex is ignored.

### Worked Example: Source `0`

Use this undirected weighted graph:

| Edge | Weight |
| --- | ---: |
| `0–1` | 10 |
| `0–3` | 40 |
| `1–2` | 10 |
| `2–3` | 10 |
| `3–4` | 2 |
| `4–5` | 3 |
| `4–6` | 8 |
| `5–6` | 3 |

The table lists heap entries in increasing weight order for readability; a binary heap's internal array is not fully sorted. An entry is shown as `(vertex, path, weight)`.

| Removal | Action | Heap after adding neighbours |
| --- | --- | --- |
| Initial state | Insert `(0, 0, 0)` | `(0, 0, 0)` |
| `(0, 0, 0)` | Finalize `0`; add `1` and `3` | `(1, 01, 10)`, `(3, 03, 40)` |
| `(1, 01, 10)` | Finalize `1`; skip visited `0`; add `2` | `(2, 012, 20)`, `(3, 03, 40)` |
| `(2, 012, 20)` | Finalize `2`; add the cheaper route to `3` | `(3, 0123, 30)`, `(3, 03, 40)` |
| `(3, 0123, 30)` | Finalize `3`; add `4` | `(4, 01234, 32)`, `(3, 03, 40)` |
| `(4, 01234, 32)` | Finalize `4`; add `5` and `6` | `(5, 012345, 35)`, `(3, 03, 40)`, `(6, 012346, 40)` |
| `(5, 012345, 35)` | Finalize `5`; add a cheaper route to `6` | `(6, 0123456, 38)`, `(3, 03, 40)`, `(6, 012346, 40)` |
| `(6, 0123456, 38)` | Finalize `6` | Two entries of weight `40` remain |
| The two weight-`40` entries | Both vertices are already visited; skip both | Empty |

The two entries of equal weight may be removed in either order without changing the answer. The shortest distance from `0` to `6` is `38`, using `0 → 1 → 2 → 3 → 4 → 5 → 6`.

```text
0 via 0 @ 0
1 via 01 @ 10
2 via 012 @ 20
3 via 0123 @ 30
4 via 01234 @ 32
5 via 012345 @ 35
6 via 0123456 @ 38
```

### Initializing the Path Correctly

The starting path must contain the actual source. In Java, use `new Trip(src, src + "", 0)`, not `new Trip(src, "0", 0)`. Hard-coding `"0"` gives the wrong printed path when the source is not zero, even though the stored source vertex and computed weights can still be correct.

An edge can be read using an index (`graph.get(v).get(i)`) or an enhanced loop (`for (Edge e : graph.get(v))`). Both use the same neighbour and weight. The triplet comparison orders entries by `wt`: return positive, negative, or zero according to whether this entry is heavier, lighter, or equal.


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

>Note: Dijkstra doesnt work for negative weights ,it only works for positive weights ,for negative weights we have bellman ford!!


# Q2. Get shortest path from 1 to n,given edge list

```java
class Solution {
  record Pair(int v, int wt) {}

  public List<Integer> shortestPath(int n, int m, int[][] edges) {
    List<List<Pair>> graph = new ArrayList<>(n + 1);
    for (int i = 0; i <= n; i++) {
      graph.add(new ArrayList<>());
    }
    for (int[] edge : edges) {
      int u = edge[0];
      int v = edge[1];
      int wt = edge[2];
      graph.get(u).add(new Pair(v, wt));
      graph.get(v).add(new Pair(u, wt));
    }

    PriorityQueue<Pair> pq = new PriorityQueue<>((a, b) -> Integer.compare(a.wt(), b.wt()));
    boolean[] vis = new boolean[n + 1];
    int[] par = new int[n + 1];
    for (int i = 1; i <= n; i++) par[i] = i;
    int[] dist = new int[n + 1];
    Arrays.fill(dist, Integer.MAX_VALUE);
    pq.add(new Pair(1, 0));

    while (!pq.isEmpty()) {
      Pair p = pq.poll();
      int v = p.v();
      if (vis[v] == true) continue;
      vis[v] = true;
      int wt = p.wt();
      for (Pair nbr : graph.get(v)) {
        if (!vis[nbr.v()] && wt + nbr.wt() < dist[nbr.v()]) {
          par[nbr.v()] = v;
          dist[nbr.v()] = wt + nbr.wt();
          pq.offer(new Pair(nbr.v(), wt + nbr.wt()));
        }
      }
    }
    if (par[n] == n) return new ArrayList<>(Arrays.asList(-1));
    List<Integer> path = new ArrayList<>();
    int node = n;
    while (par[node] != node) {
      path.add(node);
      node = par[node];
    }
    path.add(1);
    Collections.reverse(path);
    path.add(0, dist[n]);
    return path;
  }
}

```


---

## Relax edge code (Just to see)

Use this only when in OA not getting Submitted ,that will submit the code

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

### Java: Edge Relaxation

This matches the preceding C++ relaxation method: update the distance before insertion and ignore stale entries on removal. Each adjacency entry contains `[neighbour, weight]`. As in the existing C++ code, the `1_000_000_000` sentinel and integer arithmetic assume all required path costs fit below that sentinel without overflow.

```java
import java.util.*;

class DijkstraRelaxation {
    public int[] dijkstra(int V, ArrayList<ArrayList<ArrayList<Integer>>> adj, int S) {
        PriorityQueue<int[]> pq = new PriorityQueue<>((a, b) -> Integer.compare(a[0], b[0]));
        int[] dist = new int[V];
        Arrays.fill(dist, 1_000_000_000);
        dist[S] = 0;
        pq.add(new int[]{0, S});

        while (!pq.isEmpty()) {
            int[] entry = pq.remove();
            int d = entry[0];
            int node = entry[1];
            if (d > dist[node]) continue;

            for (ArrayList<Integer> edge : adj.get(node)) {
                int adjNode = edge.get(0);
                int edgeWeight = edge.get(1);
                if (d + edgeWeight < dist[adjNode]) {
                    dist[adjNode] = d + edgeWeight;
                    pq.add(new int[]{dist[adjNode], adjNode});
                }
            }
        }
        return dist;
    }
}
```




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



### The Stale Entry — Most Asked Interview Question

```cpp
if (d > dist[u]) continue;
```

When we updated `dist[3]` from 11 to 10, the old entry `{11, 3}` is **still sitting in the heap**. We cannot remove it. So when it gets popped:

```
d=11, dist[3]=10
11 > 10 → this is stale → skip ✅

Without this check:
we'd reprocess node 3 unnecessarily
push its neighbours again with wrong distances ❌
```

---

### Why Negative Weights Break Dijkstra

```
Graph: 0 →(4)→ 1 →(-10)→ 2
                0 →(2)→ 2

Dijkstra pops 2 with dist=2, marks it FINAL
Later finds path 0→1→2 = 4+(-10) = -6 which is BETTER
But node 2 is already finalised — too late ❌

Negative weights = use Bellman Ford instead
```

---

### Complexity

```
V = vertices, E = edges

Time:  O((V + E) log V)
         ↑           ↑
    each node    each edge push
    popped once  to heap = log V

Space: O(V + E)
         ↑    ↑
       dist  heap + adjacency list
```


### Two Valid Approaches

| | Your code | My code |
|---|---|---|
| Visited tracking | `vis[]` boolean array | `if(d > dist[u]) continue` |
| dist update | `res[v] = wt` when popped | `dist[v] = newDist` when pushing |
| Push condition | `if(!vis[nbr])` | `if(newDist < dist[v])` |
| Style | visited-based | distance-based |

Both are correct. Both are O((V+E) log V).


# Q4. Why `if (d > dist[node]) continue;`??

## Lazy Deletion in Dijkstra's Algorithm

This is a critical optimization known as **"Lazy Deletion."**


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


if (10 > 5) continue;
```

### Summary

* **Is it for Correctness?** No. Dijkstra will still give the right answer without it (redundant relaxations won't find a shorter path).
* **Is it for Complexity?** **YES.**
    * **With Check:** Each node is processed once. Complexity: $O(E \log V)$.
    * **Without Check:** Each edge pushing to the queue could trigger a process. Complexity degrades towards $O(E \cdot \text{Degree} \cdot \log E)$, which effectively makes it much slower on dense graphs.

> **Senior Tip:** This line converts the "Push duplicate" workaround from a memory leak into a valid $O(E \log V)$ implementation. **Always include it.**
