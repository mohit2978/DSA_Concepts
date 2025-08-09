class Solution {

    static class trip {
        int v, wt;
        trip(int v, int wt) {
            this.v = v;
            this.wt = wt;
        }
    }

    public List<Integer> shortestPath(int n, int m, int[][] edges) {
        // Step 1: Create adjacency list
        List<trip>[] graph = new ArrayList[n + 1]; // 1-based indexing
        for (int i = 1; i <= n; i++) {
            graph[i] = new ArrayList<>();
        }

        // Step 2: Fill adjacency list from edge list
        for (int i = 0; i < m; i++) {
            int a = edges[i][0];
            int b = edges[i][1];
            int w = edges[i][2];

            // Undirected graph => add both directions
            graph[a].add(new trip(b, w));
            graph[b].add(new trip(a, w));
        }

        // ✅ Now `graph` is ready to be used with Dijkstra or any graph algorithm
        // You can test it by printing:
        for (int i = 1; i <= n; i++) {
            System.out.print(i + " -> ");
            for (trip t : graph[i]) {
                System.out.print("(" + t.v + "," + t.wt + ") ");
            }
            System.out.println();
        }

        // Just returning an empty list for now, as shortestPath logic is not implemented here
        return new ArrayList<>();
    }

    public static void main(String[] args) {
        Solution sol = new Solution();
        int n = 5, m = 6;
        int[][] edges = {
            {1, 2, 2},
            {1, 4, 1},
            {2, 3, 4},
            {2, 5, 5},
            {3, 5, 1},
            {4, 3, 3}
        };

        sol.shortestPath(n, m, edges);
    }
}
