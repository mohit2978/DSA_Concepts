#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    struct trip {
        int v, wt;
        trip(int v, int wt) : v(v), wt(wt) {}
    };

    vector<int> shortestPath(int n, int m, vector<vector<int>> &edges) {
        // Step 1: Create adjacency list
        vector<vector<trip>> graph(n + 1); // 1-based indexing

        // Step 2: Fill adjacency list from edge list
        for (int i = 0; i < m; i++) {
            int a = edges[i][0];
            int b = edges[i][1];
            int w = edges[i][2];

            // Undirected graph => add both directions
            graph[a].push_back(trip(b, w));
            graph[b].push_back(trip(a, w));
        }

        // Print adjacency list for testing
        for (int i = 1; i <= n; i++) {
            cout << i << " -> ";
            for (auto &t : graph[i]) {
                cout << "(" << t.v << "," << t.wt << ") ";
            }
            cout << "\n";
        }

        return {}; // empty list for now
    }
};

int main() {
    Solution sol;
    int n = 5, m = 6;
    vector<vector<int>> edges = {
        {1, 2, 2},
        {1, 4, 1},
        {2, 3, 4},
        {2, 5, 5},
        {3, 5, 1},
        {4, 3, 3}
    };

    sol.shortestPath(n, m, edges);
}
