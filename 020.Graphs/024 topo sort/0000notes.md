# Notes
![alt text](<006prims code topo sort_240306_010053.jpg>)
![alt text](<006prims code topo sort_240306_010053(1).jpg>) ![alt text](<006prims code topo sort_240306_010053(2).jpg>) ![alt text](<006prims code topo sort_240306_010053(3).jpg>) ![alt text](<006prims code topo sort_240306_010053(4).jpg>) 



![alt text](<006prims code topo sort_240306_010053(5).jpg>) 



![alt text](<006prims code topo sort_240306_010053(6).jpg>) 

```java

public static void dfs_topo(int src, boolean[] vis, Stack<Integer> st) {
    vis[src] = true;
    for (Edge e : graph[src]) {
        if (!vis[e.v])
            dfs_topo(e.v, vis, st);
    }
    // Post-order: Add to stack after all dependencies are visited
    st.push(src);
}

public static void topologicalSort() {
    boolean[] vis = new boolean[N];
    Stack<Integer> st = new Stack<>();
    for (int i = 0; i < N; i++) {
        if (!vis[i]) {
            dfs_topo(i, vis, st);
        }
    }

    // Print or collect the result
    while (!st.isEmpty()) {
        System.out.print(st.pop() + " ");
    }
}
```
or 

```java
    public static void dfs_topo(int src, boolean[] vis, ArrayList<Integer> ans) {
        vis[src] = true;
        for (Edge e : graph[src]) {
            if (!vis[e.v])
                dfs_topo(e.v, vis, ans);
        }

        ans.add(src);
    }

    public static void topologicalSort() {
        boolean[] vis = new boolean[N];
        ArrayList<Integer> ans = new ArrayList<>();
        for (int i = 0; i < N; i++) {
            if (!vis[i]) {
                dfs_topo(i, vis, ans);
            }
        }

        Collections.reverse(ans);
    }

```
## Kahns algo or BFS topo sort

```java

public static ArrayList<Integer> kahnTopo(int N, ArrayList<Edge>[] graph) {
    int[] inDegree = new int[N];
    ArrayList<Integer> ans = new ArrayList<>();
    Queue<Integer> q = new LinkedList<>();

    // 1. Calculate In-degrees
    for (int i = 0; i < N; i++) {
        for (Edge e : graph[i]) {
            inDegree[e.v]++;
        }
    }

    // 2. Add nodes with 0 in-degree to Queue
    for (int i = 0; i < N; i++) {
        if (inDegree[i] == 0) q.add(i);
    }

    // 3. Standard BFS
    while (!q.isEmpty()) {
        int curr = q.poll();
        ans.add(curr);

        for (Edge e : graph[curr]) {
            inDegree[e.v]--; // "Remove" the dependency
            if (inDegree[e.v] == 0) {
                q.add(e.v);
            }
        }
    }

    // Cycle Check: If ans doesn't contain all nodes, there's a cycle
    if (ans.size() != N) return new ArrayList<>(); 

    return ans;
}
```

Topological Sort (whether via DFS or Kahn's) only exists for DAGs. If a graph has even one cycle, a complete topological ordering is mathematically impossible.

Which one should you use?
- Use DFS if you need a quick, recursive solution and you are 100% sure the graph is a DAG.

- Use Kahn's if you need to detect cycles easily or if you want the "lexicographically smallest" topological sort (by using a PriorityQueue instead of a regular Queue)



![alt text](<006prims code topo sort_240306_010053(7).jpg>) ![alt text](<006prims code topo sort_240306_010053(8).jpg>) ![alt text](<006prims code topo sort_240306_010053(9).jpg>)
![alt text](<006prims code topo sort_240306_010053(10).jpg>) ![alt text](<006prims code topo sort_240306_010053(11).jpg>) ![alt text](<006prims code topo sort_240306_010053(12).jpg>) ![alt text](<006prims code topo sort_240306_010053(13).jpg>) ![alt text](<006prims code topo sort_240306_010053(14).jpg>) ![alt text](<006prims code topo sort_240306_010053(15).jpg>) ![alt text](<006prims code topo sort_240306_010053(16).jpg>) ![alt text](<006prims code topo sort_240306_010053(17).jpg>) ![alt text](<006prims code topo sort_240306_010053(18).jpg>) ![alt text](<006prims code topo sort_240306_010053(19).jpg>) ![alt text](<006prims code topo sort_240306_010053(20).jpg>) ![alt text](<006prims code topo sort_240306_010053(21).jpg>) ![alt text](<006prims code topo sort_240306_010053(22).jpg>) ![alt text](<006prims code topo sort_240306_010053(23).jpg>) ![alt text](<006prims code topo sort_240306_010053(24).jpg>) ![alt text](<006prims code topo sort_240306_010053(25).jpg>) ![alt text](<006prims code topo sort_240306_010053(26).jpg>) 