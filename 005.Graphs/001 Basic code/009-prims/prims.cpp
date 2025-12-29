#include <bits/stdc++.h>
using namespace std;

/*
Time Complexity: O(ElogE) (where E is the number of edges in the graph)
In the worst case, the min-heap will store all the E edges, and insertion 
operation on the min-heap takes O(logE) time taking overall O(ElogE) time.

Space Complexity: O(E + V) (where V is the number of nodes in the graph)
The min-heap will store all edges in worst-case taking O(E) space and the
 visited array takes O(V) space.
*/
#define P pair<int,int>

class Solution{
public:

    // Function to get the sum of weights of edges in MST
    int spanningTree(int V, vector<vector<int>> adj[]) {
        priority_queue <P, vector<P>, greater<P>> pq;
        vector<int> visited(V, 0);
        pq.push({0,0});
    
        int sum = 0;
        while(!pq.empty()) {
            
            auto p = pq.top();
            pq.pop();
            
            int node = p.second; // Get the node
            int wt = p.first; // Get the edge weight
            if(visited[node] == 1) continue;

            visited[node] = 1;
            
            sum += wt;

            for(auto it : adj[node]) {
                int adjNode = it[0]; 
                int edgeWt = it[1];
                if(visited[adjNode] == 0) {
                    pq.push({edgeWt, adjNode});
                }
            }
        }
        
        // Return the weight of MST
        return sum;
    }
};


int main() {
    int V = 4;
    vector<vector<int>> edges = {
        {0, 1, 1},
        {1, 2, 2},
        {2, 3, 3},
        {0, 3, 4}
    };
    
    // Forming the adjacency list from edges
    vector<vector<int>> adj[4];
    for(auto it : edges) {
        int u = it[0];
        int v = it[1];
        int wt = it[2];
        
        adj[u].push_back({v, wt});
        adj[v].push_back({u, wt});
    }
    
    // Creating instance of Solution class
    Solution sol;
    
    /* Function call to get the sum 
    of weights of edges in MST */
    int ans = sol.spanningTree(V, adj);
    
    cout << "The sum of weights of edges in MST is: " << ans;
    
    return 0;
}