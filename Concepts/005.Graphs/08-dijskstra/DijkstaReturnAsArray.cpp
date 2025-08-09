#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    struct Trip {
        int v;
        int wt;
        Trip(int v, int wt) : v(v), wt(wt) {}
    };

    vector<int> dijkstra(int V, vector<vector<vector<int>>>& adj, int S) {
        auto cmp = [](const Trip &a, const Trip &b) {
            return a.wt > b.wt; // min-heap
        };
        priority_queue<Trip, vector<Trip>, decltype(cmp)> pq(cmp);

        pq.push(Trip(S, 0));
        vector<bool> vis(V, false);
        vector<int> res(V, (int)1e9);

        while (!pq.empty()) {
            Trip rem = pq.top();
            pq.pop();

            if (vis[rem.v]) continue;
            vis[rem.v] = true;
            res[rem.v] = rem.wt;

            for (auto &itr : adj[rem.v]) {
                int nbr = itr[0];
                int w = itr[1];
                if (!vis[nbr]) {
                    pq.push(Trip(nbr, rem.wt + w));
                }
            }
        }

        return res;
    }
};

int main() {
    Solution sol;

    // Example: Graph with 5 vertices
    int V = 5;
    vector<vector<vector<int>>> adj(V);

    // Adding edges: u -> v (weight)
    adj[0].push_back({1, 2});
    adj[0].push_back({2, 4});
    adj[1].push_back({2, 1});
    adj[1].push_back({3, 7});
    adj[2].push_back({4, 3});
    adj[3].push_back({4, 1});

    int source = 0;
    vector<int> dist = sol.dijkstra(V, adj, source);

    cout << "Shortest distances from source " << source << ":\n";
    for (int d : dist) cout << d << " ";
    cout << endl;

    return 0;
}
