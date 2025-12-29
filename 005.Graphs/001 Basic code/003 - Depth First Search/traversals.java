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
