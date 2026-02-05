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


The differentiation relies entirely on whether the neighbor $v$ has been seen before (visited) at the moment we look at it from $u$. Here is the exact logic breakdown:

---

### 1. The Parent Check (Crucial Step)
First, we must ignore the edge we just came from. In an undirected graph, if you came from `parent` to $u$, there is trivially an edge from $u$ back to `parent`. This is not a "Back Edge" (it doesn't form a cycle); it's just the same road viewed from the other end.

> **The Rule:** "Don't look back at where I came from."

---

### 2. Differentiating Tree vs. Back Edge
Once we know $v$ is not the parent, we look at `disc[v]` (Discovery Time):

#### A. Tree Edge
* **Condition:** `if (disc[v] == -1)` (or `!visited[v]`)
* **Meaning:** "I have never seen node $v$ before."
* **Implication:** This edge ($u, v$) represents the first time discovering $v$. We make $u$ the parent of $v$ and move down. This edge becomes part of the "DFS Tree" structure.
* **Action:** Recurse into $v$.

#### B. Back Edge
* **Condition:** `if (disc[v] != -1)` (Node is already visited)
* **Meaning:** "I have seen $v$ before!"
* **Implication:** Since $v$ is visited (and it's not my parent), $v$ must be an ancestor somewhere above me in the recursion stack. This edge ($u, v$) connects a descendant back to an ancestor, **creating a cycle**.
* **Action:** Update `low[u] = min(low[u], disc[v])`.

---

### Visual Summary
Imagine exploring a maze with a ball of string (**DFS**):

* **Parent Edge:** You hold the string leading back to exactly where you just were. You ignore this direction.
* **Tree Edge:** You see a dark, unexplored tunnel. You walk into it, unwinding your string as you go.
* **Back Edge:** You see a tunnel, shine your light, and see your own string already passing through there from much earlier. You don't walk through it; you just note: *"Aha! I found a shortcut back to a place I've already been."*

---

### Summary Table

| Edge Type | Status of $v$ | Interpretation | Update Logic |
| :--- | :--- | :--- | :--- |
| **Parent** | `v == p` | The road I just took. | Ignore. |
| **Tree** | `disc[v] == -1` | A brand new discovery. | `low[u] = min(low[u], low[v])` |
| **Back** | `disc[v] != -1` | A cycle/shortcut to an ancestor. | `low[u] = min(low[u], disc[v])` |

---



### Let's use the "Time Portal" Analogy. 
This maps perfectly because DFS is literally a timeline (a timer). Imagine you are a **Time Traveler**.

* **`disc[u]` (The Current Year):** The year you are standing in right now.
* **`low[u]` (The Record):** The earliest year (furthest past) you can send a message to.

---

### 1. The Back Edge: "Finding a Fixed Portal"
**Situation:** You are currently in the year 2025 (Node $u$). You look around and find a magic portal (**Back Edge**) that connects directly to your grandfather, who is in the year 1950 (Node $v$).

* **The Logic:** "I found a portal. It goes to 1950."
* **The Update:** `low[u] = 1950`.
* **Why `disc[v]`?** Because the portal has a fixed destination. It drops you in 1950. Period. You cannot ask the portal, "Where does Grandpa go on his vacations?" You only know the portal takes you to 1950.
* **Code Translation:** `low[u] = min(low[u], disc[v])`

---

### 2. The Tree Edge: "The Scout's Report"
**Situation:** You are in the year 2025 (Node $u$). You send your apprentice (Node $v$) forward to the year 2026 to explore. The apprentice explores the future and eventually comes back to you with a report.

* **The Apprentice says:** "Master! While exploring the future, I found a wormhole that leads all the way back to the year 1800!" (Note: This means `low[v]` is 1800).
* **The Logic:** "If my apprentice can reach 1800, and I control my apprentice, then I can effectively reach 1800 too (by passing the message through them)."
* **The Update:** `low[u] = 1800`.
* **Why `low[v]`?** Because you are inheriting the success of your subordinate. You aren't just looking at the year 2026 (`disc[v]`); you are looking at the *result* of their journey (`low[v]`).
* **Code Translation:** `low[u] = min(low[u], low[v])`

---

### Summary Difference

| Scenario | What you say | Why? |
| :--- | :--- | :--- |
| **Back Edge** | "I see the year 1950 right in front of me." | It is a direct observation of a specific time (`disc[v]`). |
| **Tree Edge** | "My apprentice found a way to 1800." | It is a report of the best result found by someone else (`low[v]`). |

---

### The "Fatal Error" (Why not swap?)
If you swapped them and used `low[v]` for the Back Edge (Grandfather):
1.  You would be standing in 2025.
2.  You see the portal to Grandpa (1950).
3.  Grandpa knows a guy in 1900 (`low[grandpa]`).

If you take `low[grandpa]`, you are claiming: **"I can reach 1900 directly from 2025."**

**This is a LIE.** You can't. You can only reach Grandpa (1950). If Grandpa dies (is removed), your connection to 1900 is broken. The algorithm needs to know that Grandpa is the **bottleneck**. If you pretend you can bypass him to reach 1900, you will fail to identify him as an **Articulation Point**.

### 1. The Parent: "The Boss" (Total Respect / Don't Ask)
* **Code:** `if (v == p) continue;`
* **The Logic:** You literally came from your Parent. That is the path that brought you into existence.
* **Why we ignore:** If you asked your Parent "Hey, can you take me higher?", they would say "I am the one who sent you here!"
* **The Cheat:** `low[u]` is about finding a *second* path (a back-door) to an ancestor. The path to your parent is the first path (the front door). If you count the front door as a "secret escape route," you are lying to yourself. So, we ignore the parent completely to look for *new* paths.

---

### 2. The Back Edge: "The Elder" (Respect their Station)
* **Code:** `low[u] = min(low[u], disc[v]);`
* **The Analogy:** You bump into an Ancestor (someone with a lower `disc` number than you).
* **The Logic:** You bow to them. You acknowledge exactly who they are (`disc[v]`).
* **Why `disc`?** You say, "I see Elder #3." You do not ask them for their contacts (`low[v]`). That would be disrespectful (and buggy!). You only know you have a direct line to them specifically.

---

### 3. The Child: "The Apprentice" (Demand Results)
* **Code:** `low[u] = min(low[u], low[v]);`
* **The Analogy:** This is your subordinate. You sent them out to do the work.
* **The Logic:** When they return, you don't ask "Who are you?" (you know who they are). You ask: "What did you find?"
* **Why `low`?** You want their results. If your apprentice found a secret tunnel to the year 1800 (`low[v]`), you take credit for it immediately: "My team found a way to 1800."

---

### Summary Table: The Family Hierarchy

| Relationship | Who is it? | Code | Your Attitude |
| :--- | :--- | :--- | :--- |
| **Parent** | The Boss | `continue` | **Ignore.** "I already know you. You are the front door." |
| **Back Edge** | The Elder | `min(..., disc[v])` | **Acknowledge.** "I see you, Elder. I will note your location." |
| **Child** | The Apprentice | `min(..., low[v])` | **Exploit.** "Give me your report. I will take credit for your discoveries." |

---

### Final Rule
Information (`low` values) only flows **UP** from children to parents. It never flows down from ancestors (Back Edges) or down from parents.

Q---> 

```text
 if (p != -1 && low[v] >= disc[u]) {
                    isAP[u] = true;
                } why we decide on only 1 child we should let whole loop run till every child explore maybe some other child has way to parent

 ```

 ans--> if we have multiple child and we on first child only we see first child cant reach to u's parent  i.e. `low[v]>=disc[u]` so we can say that u is AP ,if we remove u parent of u and child of u be separate!!              

---

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





































