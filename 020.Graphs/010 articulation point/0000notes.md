# Notes







![alt text](<009 articulation pt_240113_014029.jpg>)




![alt text](<009 articulation pt_240113_014029(1).jpg>) ![alt text](<009 articulation pt_240113_014029(2).jpg>) ![alt text](<009 articulation pt_240113_014029(3).jpg>) ![alt text](<009 articulation pt_240113_014029(4).jpg>) ![alt text](<009 articulation pt_240113_014029(5).jpg>) ![alt text](<009 articulation pt_240113_014029(6).jpg>) ![alt text](<009 articulation pt_240113_014029(7).jpg>) ![alt text](<009 articulation pt_240113_014029(8).jpg>) ![alt text](<009 articulation pt_240113_014029(9).jpg>) ![alt text](<009 articulation pt_240113_014029(10).jpg>) ![alt text](<009 articulation pt_240113_014029(11).jpg>) ![alt text](<009 articulation pt_240113_014029(12).jpg>) ![alt text](<009 articulation pt_240113_014029(13).jpg>) ![alt text](<009 articulation pt_240113_014029(14).jpg>) ![alt text](<009 articulation pt_240113_014029(15).jpg>) ![alt text](<009 articulation pt_240113_014029(16).jpg>) ![alt text](<009 articulation pt_240113_014029(17).jpg>) ![alt text](<009 articulation pt_240113_014029(18).jpg>) ![alt text](<009 articulation pt_240113_014029(19).jpg>) ![alt text](<009 articulation pt_240113_014029(20).jpg>)

## Mycode

```cpp

class Solution {
    void findAPs(int u, int p, int& timer, vector<int> adj[], vector<int>& disc,
                 vector<int>& low, vector<bool>& isAP) {
        disc[u] = low[u] = ++timer;
        int children = 0;

        for (int v : adj[u]) {
            if (v == p) continue;  // Skip parent

            if (disc[v] != -1) {
                // Back-edge found: update low-link using discovery time of v
                low[u] = min(low[u], disc[v]);
            } else {
                // Tree-edge: recurse
                children++;
                findAPs(v, u, timer, adj, disc, low, isAP);

                // Check if subtree rooted at v has a back-link to u or its
                // ancestors
                low[u] = min(low[u], low[v]);

                // Condition for non-root nodes
                if (p != -1 && low[v] >= disc[u]) {
                    isAP[u] = true;
                }
            }
        }

        // Condition for root node
        if (p == -1 && children > 1) {
            isAP[u] = true;
        }
    }

   public:
    vector<int> articulationPoints(int n, vector<int> adj[]) {
        vector<int> disc(n, -1), low(n, -1);
        vector<bool> isAP(n,false);
        int timer = 0;

        // Run DFS for all components
        for (int i = 0; i < n; i++) {
            if (disc[i] == -1) {
                findAPs(i, -1, timer, adj, disc, low, isAP);
            }
        }
        vector<int> res;
        for (int i = 0; i < n; i++) {
            if (isAP[i] == true) res.push_back(i);
        }
        if (res.size() > 0)
            return res;
        else
            return {-1};
    }
};
```


### Tarjan's Algorithm for Articulation Points

An **Articulation Point** (or Cut Vertex) is a node in an undirected graph which, when removed, increases the number of connected components. Tarjan's algorithm finds all such points in $O(V + E)$ time using a single **DFS**.

---

### 1. Key Concepts: Discovery Time and Low Link

During DFS, we maintain two arrays:
* **`disc[u]` (Discovery Time):** The time at which node `u` was first visited.
* **`low[u]` (Low Link Value):** The lowest `disc` time reachable from `u` (including itself) using back-edges in the DFS tree.

---

### 2. The Logic (The Conditions)

A node `u` is an Articulation Point if it meets one of these two conditions:

#### Condition A: The Root Case
If `u` is the **root** of the DFS tree and has **more than one child** in the DFS tree.
* *Why?* If the root has two independent subtrees, removing the root will disconnect them.

#### Condition B: Non-Root Case
If `u` is **not the root** and has a child `v` such that no node in the subtree of `v` can reach `u` or any of `u`'s ancestors via a back-edge.
* **Formal Rule:** `low[v] >= disc[u]`

---

### 3. Step-by-Step Algorithm

1.  Initialize `disc` and `low` arrays with $-1$.
2.  Start DFS from an unvisited node.
3.  For every neighbor `v` of `u`:
    * **If `v` is the parent:** Skip it.
    * **If `v` is already visited:** This is a **back-edge**. Update `low[u] = min(low[u], disc[v])`.
    * **If `v` is not visited:**
        * Increment child count for `u`.
        * Recursively call `DFS(v, u)`.
        * On return, update `low[u] = min(low[u], low[v])`.
        * Check **Condition B:** If `low[v] >= disc[u]` and `u` is not root, `u` is an Articulation Point.
4.  After DFS finishes for root, check **Condition A:** If `u` is root and `children > 1`, `u` is an Articulation Point.

---

### 4. Complexity Summary

| Metric | Complexity | Explanation |
| :--- | :--- | :--- |
| **Time Complexity** | $O(V + E)$ | Based on a standard Depth First Search. |
| **Space Complexity** | $O(V)$ | To store `disc`, `low`, `parent`, and the adjacency list. |

---

### 5. Why `low[v] >= disc[u]`?

* If `low[v] < disc[u]`, it means there is a "back-door" (back-edge) from the subtree of `v` to an ancestor of `u`.
* If `low[v] == disc[u]`, the highest point `v` can reach is `u` itself. Removing `u` still disconnects `v`.
* If `low[v] > disc[u]`, `v` is stuck in its own subtree and can't even reach `u` without the tree edge.

 ![alt text](<009 articulation pt_240113_014029(21).jpg>) ![alt text](<009 articulation pt_240113_014029(22).jpg>) ![alt text](<009 articulation pt_240113_014029(23).jpg>) ![alt text](<009 articulation pt_240113_014029(24).jpg>) ![alt text](<009 articulation pt_240113_014029(25).jpg>) ![alt text](<009 articulation pt_240113_014029(26).jpg>) ![alt text](<009 articulation pt_240113_014029(27).jpg>)
 
 ```cpp
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/**
 * Tarjan's Algorithm for finding Articulation Points
 * Time Complexity: O(V + E)
 * Space Complexity: O(V)
 */

void findAPs(int u, int p, int& timer, vector<int> adj[], 
             vector<int>& disc, vector<int>& low, vector<bool>& isAP) {
    
    disc[u] = low[u] = ++timer;
    int children = 0;

    for (int v : adj[u]) {
        if (v == p) continue; // Skip parent

        if (disc[v] != -1) {
            // Back-edge found: update low-link using discovery time of v
            low[u] = min(low[u], disc[v]);
        } else {
            // Tree-edge: recurse
            children++;
            findAPs(v, u, timer, adj, disc, low, isAP);
            
            // Check if subtree rooted at v has a back-link to u or its ancestors
            low[u] = min(low[u], low[v]);

            // Condition for non-root nodes
            if (p != -1 && low[v] >= disc[u]) {
                isAP[u] = true;
            }
        }
    }

    // Condition for root node
    if (p == -1 && children > 1) {
        isAP[u] = true;
    }
}

int main() {
    int n, m; // n = nodes, m = edges
    cin >> n >> m;

    vector<int> adj[n];
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vector<int> disc(n, -1), low(n, -1);
    vector<bool> isAP(n, false);
    int timer = 0;

    // Run DFS for all components
    for (int i = 0; i < n; i++) {
        if (disc[i] == -1) {
            findAPs(i, -1, timer, adj, disc, low, isAP);
        }
    }

    // Output all Articulation Points
    cout << "Articulation Points: ";
    for (int i = 0; i < n; i++) {
        if (isAP[i]) cout << i << " ";
    }

    return 0;
}
```
 The `low` array (often called **Low-Link Value**) is the most critical part of Tarjan's algorithm. 

In simple terms: `low[u]` tells you the "highest" ancestor (earliest visited node) that node `u` can reach. It answers the question: *"If I start at node `u` and go down the DFS tree, can I find a back-path (back-edge) that lets me jump up to an ancestor of `u`?"*

---

### 1. The Formal Definition
`low[u]` is the lowest `disc` (discovery time) value reachable from `u` (including itself) in the DFS tree, possibly using a **back-edge** (but not the direct parent-child edge in reverse).

---

### 2. How `low[u]` is Calculated
Think of `low[u]` as a "best escape route" value. We want it to be as small as possible (smaller time = older ancestor = higher up in the tree).

* **Initialization:** When you first visit `u`, you can definitely reach yourself.
    > `low[u] = disc[u]`
* **Back-Edge Found (Cycle detected):** If `u` has a neighbor `v` that is already visited (and isn't `u`'s parent), it means `u` found a "secret tunnel" back up the tree.
    > `low[u] = min(low[u], disc[v])`
    * *Translation:* "I can reach node `v`, so I can reach `v`'s discovery time."
* **Tree-Edge Return (Recursive update):** After DFS returns from a child `v`, `u` checks if the child found a path to an ancestor.
    > `low[u] = min(low[u], low[v])`
    * *Translation:* "If my child `v` can reach an ancestor way up there, then I can reach it too (via `v`)."

---

### 3. Why `low` Determines Articulation Points
The logic for finding an Articulation Point relies entirely on comparing `low` and `disc`.

**The Critical Condition:**
If `u` is the parent and `v` is the child, and we see:
$$low[v] \ge disc[u]$$

* **What this means:** The "lowest" node `v` can reach is `u` itself (or something below `u`).
* **Implication:** There is **NO** back-edge from `v` (or `v`'s subtree) that goes above `u`.
* **Result:** `u` is a bottleneck. If you remove `u`, `v` will be completely cut off from the rest of the ancestors. Therefore, `u` is an Articulation Point.

---

### Visual Example
Imagine a graph: **1 — 2 — 3** (Linear) vs **1 — 2 — 3 — 1** (Cycle).

* **Case A: Linear (1-2-3)**
    * Node 3: `disc=3`, `low=3` (Can't go anywhere).
    * Node 2: Child (3) returns `low=3`. Node 2 compares its `disc(2)` vs child's `low(3)`.
    * Since `low[3] (3) >= disc[2] (2)`, removing 2 disconnects 3. **2 is an AP.**

* **Case B: Cycle (1-2-3-1)**
    * Node 3: Has edge to 1. `low[3]` updates to `disc[1]` (which is 1).
    * Node 2: Child (3) returns `low=1`.
    * Since `low[3] (1) < disc[2] (2)`, removing 2 does **NOT** disconnect 3 (because 3 can still reach 1 directly). **2 is NOT an AP.**
 
  ![alt text](<009 articulation pt_240113_014029(28).jpg>) ![alt text](<009 articulation pt_240113_014029(29).jpg>) ![alt text](<009 articulation pt_240113_014029(30).jpg>) ![alt text](<009 articulation pt_240113_014029(31).jpg>) ![alt text](<009 articulation pt_240113_014029(32).jpg>) ![alt text](<009 articulation pt_240113_014029(33).jpg>) ![alt text](<009 articulation pt_240113_014029(34).jpg>) ![alt text](<009 articulation pt_240113_014029(35).jpg>) ![alt text](<009 articulation pt_240113_014029(36).jpg>) ![alt text](<009 articulation pt_240113_014029(37).jpg>) ![alt text](<009 articulation pt_240113_014029(38).jpg>) ![alt text](<009 articulation pt_240113_014029(39).jpg>) ![alt text](<009 articulation pt_240113_014029(40).jpg>) ![alt text](<009 articulation pt_240113_014029(41).jpg>) ![alt text](<009 articulation pt_240113_014029(42).jpg>) ![alt text](<009 articulation pt_240113_014029(43).jpg>) ![alt text](<009 articulation pt_240113_014029(44).jpg>) ![alt text](<009 articulation pt_240113_014029(45).jpg>) ![alt text](<009 articulation pt_240113_014029(46).jpg>) ![alt text](<009 articulation pt_240113_014029(47).jpg>) ![alt text](<009 articulation pt_240113_014029(48).jpg>)





































