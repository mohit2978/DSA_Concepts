# Notes




![alt text](<008dsu problems_240113_014003.jpg>)



![alt text](<008dsu problems_240113_014003(1).jpg>) ![alt text](<008dsu problems_240113_014003(2).jpg>) ![alt text](<008dsu problems_240113_014003(3).jpg>) ![alt text](<008dsu problems_240113_014003(4).jpg>) ![alt text](<008dsu problems_240113_014003(5).jpg>) ![alt text](<008dsu problems_240113_014003(6).jpg>) ![alt text](<008dsu problems_240113_014003(7).jpg>) ![alt text](<008dsu problems_240113_014003(8).jpg>) ![alt text](<008dsu problems_240113_014003(9).jpg>) ![alt text](<008dsu problems_240113_014003(10).jpg>) ![alt text](<008dsu problems_240113_014003(11).jpg>) ![alt text](<008dsu problems_240113_014003(12).jpg>) ![alt text](<008dsu problems_240113_014003(13).jpg>) ![alt text](<008dsu problems_240113_014003(14).jpg>) ![alt text](<008dsu problems_240113_014003(15).jpg>) ![alt text](<008dsu problems_240113_014003(16).jpg>) ![alt text](<008dsu problems_240113_014003(17).jpg>) ![alt text](<008dsu problems_240113_014003(18).jpg>) ![alt text](<008dsu problems_240113_014003(19).jpg>) ![alt text](<008dsu problems_240113_014003(20).jpg>) ![alt text](<008dsu problems_240113_014003(21).jpg>) ![alt text](<008dsu problems_240113_014003(22).jpg>) ![alt text](<008dsu problems_240113_014003(23).jpg>) ![alt text](<008dsu problems_240113_014003(24).jpg>) ![alt text](<008dsu problems_240113_014003(25).jpg>) ![alt text](<008dsu problems_240113_014003(26).jpg>) ![alt text](<008dsu problems_240113_014003(27).jpg>) ![alt text](<008dsu problems_240113_014003(28).jpg>) ![alt text](<008dsu problems_240113_014003(29).jpg>) ![alt text](<008dsu problems_240113_014003(30).jpg>) ![alt text](<008dsu problems_240113_014003(31).jpg>) ![alt text](<008dsu problems_240113_014003(32).jpg>) ![alt text](<008dsu problems_240113_014003(33).jpg>) ![alt text](<008dsu problems_240113_014003(34).jpg>)




# Q--> 1319. Number of Operations to Make Network Connected

There are `n` computers numbered from `0` to `n - 1` connected by ethernet cables `connections` forming a network where `connections[i] = [ai, bi]` represents a connection between computers `ai` and `bi`. Any computer can reach any other computer directly or indirectly through the network.

You are given an initial computer network `connections`. You can extract certain cables between two directly connected computers, and place them between any pair of disconnected computers to make them directly connected.

Return the *minimum number of times* you need to do this in order to make all the computers connected. If it is not possible, return `-1`.

### Example 1:

**Input:** `n = 4`, `connections = [[0,1],[0,2],[1,2]]`
**Output:** `1`
**Explanation:** Remove cable between computer 1 and 2 and place between computers 1 and 3.

### Example 2:

**Input:** `n = 6`, `connections = [[0,1],[0,2],[0,3],[1,2],[1,3]]`
**Output:** `2`
**Explanation:** We need 2 extra cables to connect computers 4 and 5. We can extract cables `[1,2]` and `[1,3]` and use them to connect computers 4 and 5.

### Example 3:

**Input:** `n = 6`, `connections = [[0,1],[0,2],[0,3],[1,2]]`
**Output:** `-1`
**Explanation:** There are not enough cables to connect all computers.

### Constraints:

* `1 <= n <= 10^5`
* `1 <= connections.length <= min(n * (n - 1) / 2, 10^5)`
* `connections[i].length == 2`
* `0 <= ai, bi < n`
* `ai != bi`
* There are no repeated connections.
* No two computers are connected by more than one cable.


## My sol

```java
class Solution {
  public class DSU {
    int[] par;
    int[] rank;

    DSU(int v) {
      par = new int[v];
      rank = new int[v];
      for (int i = 0; i < par.length; i++) {
        par[i] = i;
        rank[i] = 0;
      }
    }


    public int find(int x) {
      if (x == par[x]) return x;
      int parent = find(par[x]);
      par[x] = parent; // for compression
      return parent;
    }

    public int getparent(int i) {
      return par[i];
    }

    public int connectedComponents() {
      int cnt = 0;
      for (int i = 0; i < par.length; i++) {
        if (par[i] == i) cnt++;
      }
      return cnt;
    }

    public void union(int x, int y) {
      if (rank[x] == rank[y]) {
        par[x] = y;
        rank[y]++;
      } else if (rank[x] < rank[y]) {
        par[x] = y;
      } else if (rank[x] > rank[y]) {
        par[y] = x;
      }
    }
  }

  private int findRedundantConnection(int n,int[][] edges) {
    DSU d = new DSU(n);
    int res = 0;
    for (int i = 0; i < edges.length; i++) {
      int v1 = edges[i][0];
      int v2 = edges[i][1];
      int p1 = d.find(v1);
      int p2 = d.find(v2);
      if (p1 != p2) {
        d.union(p1, p2);
      } else {
        res++;
      }
    }
    int comp = d.connectedComponents();
    return comp - res > 1 ? -1 : comp - 1;
  }

  public int solve(int n, int[][] Edge) {
    return findRedundantConnection(n,Edge);
  }
}

```

## Ai way 

Welcome to **LeetCode 1319: Number of Operations to Make Network Connected**.

You have fully grasped the Disjoint Set Union (DSU) architecture. You implemented both **Path Compression** and **Union by Rank**. Your math at the end (`comp - res > 1 ? -1 : comp - 1`) perfectly captures the relationship between redundant edges and disconnected islands. 

This code will pass all test cases. However, here is the "Senior Engineer" code review. We can completely eliminate the `res` variable, delete the `connectedComponents()` loop, and add an $O(1)$ early exit by leveraging a fundamental law of Graph Theory.

### The Law of Trees
To connect $N$ nodes into a single, fully connected network (a Tree), you need exactly **$N - 1$ edges**. 
* If you have fewer than $N - 1$ cables, it is mathematically impossible to connect all computers.
* If you have $N - 1$ or more cables, it is mathematically guaranteed that you can connect all computers (by unplugging the redundant ones and moving them).

### The $O(1)$ Early Exit
Because of this law, before you even initialize your DSU or loop through the matrix, you can just check the size of the `edges` array:
```java
if (edges.length < n - 1) return -1;
```
If this is true, you instantly save the CPU from doing any work. If it is false, you are guaranteed to have enough cables. You no longer need to keep track of the redundant cables (`res`). You only need to know how many islands are left!

### Dynamic Component Counting
Instead of running a `for` loop at the very end to count how many `par[i] == i` exist, we can track the components dynamically.
You start with $N$ disconnected computers (Components = $N$). Every time `union` successfully connects two different computers, the total number of components decreases by 1. 

### The Refactored Code

Here is how you write this solution to be as lean and mathematically optimal as possible:

```java
class Solution {
    class DSU {
        int[] par;
        int[] rank;
        int components; // Track dynamically

        DSU(int n) {
            par = new int[n];
            rank = new int[n];
            components = n; // Start with N isolated islands
            for (int i = 0; i < n; i++) {
                par[i] = i;
                rank[i] = 0;
            }
        }

        public int find(int x) {
            if (x == par[x]) return x;
            par[x] = find(par[x]); // Path compression
            return par[x];
        }

        public void union(int x, int y) {
            int p1 = find(x);
            int p2 = find(y);
            
            // If they are already connected, do nothing
            if (p1 == p2) return; 

            // Union by Rank
            if (rank[p1] < rank[p2]) {
                par[p1] = p2;
            } else if (rank[p1] > rank[p2]) {
                par[p2] = p1;
            } else {
                par[p1] = p2;
                rank[p2]++;
            }
            // A successful merge reduces total components by 1
            components--; 
        }
    }

    public int makeConnected(int n, int[][] edges) {
        // O(1) Math Check: Do we have enough cables?
        if (edges.length < n - 1) {
            return -1;
        }

        DSU d = new DSU(n);
        
        // Build the network
        for (int[] edge : edges) {
            d.union(edge[0], edge[1]);
        }
        
        // We need (Islands - 1) cables to connect the remaining islands.
        // We already know we have enough redundant cables because of our early exit check.
        return d.components - 1;
    }
}
```

### The Verdict
You traded a post-processing loop for a dynamic counter, and you replaced complex conditional logic at the end with a single $O(1)$ mathematical guardrail at the beginning. This is how you transition from just getting the "Accepted" green text to writing enterprise-grade optimizations.

>This is very good way of getting no of components !!!

It really is. It is one of those small architectural shifts that separates someone who just memorized the algorithm from someone who truly understands how the data structure breathes. 

By tracking it dynamically, you turn what used to be a completely separate $O(N)$ post-processing loop into a completely free, $O(1)$ state update that happens silently in the background.

Since you now have a flawless, highly optimized `DSU` class in your toolkit, you are actually 90% of the way to mastering **Minimum Spanning Trees (MST)**. 

The most famous algorithm for finding an MST (Kruskal's Algorithm) literally just takes the exact `DSU` class you just wrote and feeds a sorted list of edges into it. 






























