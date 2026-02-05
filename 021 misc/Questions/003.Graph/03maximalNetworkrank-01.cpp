#include <bits/stdc++.h>
using namespace std;

class Graph {
    int V;
    vector<vector<int>> adj; // Adjacency list

public:
    Graph(int v) {
        V = v;
        adj.resize(V); // Resize to hold V empty adjacency lists
    }

    void addEdge(int i, int j) {
        adj[i].push_back(j);
        adj[j].push_back(i);
    }

    int findMaxRank() {
        int maxRank = 0;

        // Iterate over all unique pairs of cities
        for (int i = 0; i < V; i++) {
            for (int j = i + 1; j < V; j++) {
                int rank = adj[i].size() + adj[j].size();

                // Check if there's a direct connection between i and j
                if (find(adj[i].begin(), adj[i].end(), j) != adj[i].end()) {
                    rank--; // Avoid double-counting the direct road
                }

                maxRank = max(maxRank, rank);
            }
        }
        return maxRank;
    }
};

int maximalNetworkRank(int n, vector<vector<int>> roads) {
    Graph graph(n);

    for (auto& road : roads) {
        graph.addEdge(road[0], road[1]);
    }

    return graph.findMaxRank();
}

int main() {
    int n = 4;
    vector<vector<int>> roads = {{0, 1}, {0, 3}, {1, 2}, {1, 3}};
    cout << "Maximal Network Rank: " << maximalNetworkRank(n, roads) << endl; // Output: 4
    return 0;
}
