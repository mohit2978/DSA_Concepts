#include <bits/stdc++.h>
using namespace std;

class Solution {
private: 
    // Function for BFS traversal
    void bfs(int node, vector<int> adjLs[], int vis[]) {
        
        // Mark the node as visited
        vis[node] = 1;
        
        queue <int> q;
        q.push(node); 
        while(!q.empty()) {
            // Get the node
            int i = q.front();
            q.pop();
            
            // Traverse its unvisited neighbours
            for(auto adjNodes: adjLs[i]) {
                
                if(vis[adjNodes] != 1) {
                    vis[adjNodes] = 1;
                    q.push(adjNodes);
                }
            }
        }
        
    }

    // Function for DFS traversal  
    void dfs(int node, vector<int> adjLs[], int vis[]) {
        
        vis[node] = 1; 
        for(auto it: adjLs[node]) {
            
            if(!vis[it]) {
                // Recursively perform DFS
                dfs(it, adjLs, vis); 
            }
        }
    }
    
public:

    /* find the number of 
    connected components in the given graph */
    int findNumberOfComponent(int E, int V, vector<vector<int>> &edges) {
        
        // To store adjacency list
        vector<int> adjLs[V];
        
        // Add edges to adjacency list 
        for(int i=0; i < E; i++) {
            adjLs[edges[i][0]].push_back(edges[i][1]);
            adjLs[edges[i][1]].push_back(edges[i][0]);
        }
        
        // Visited array
        int vis[V] = {0}; 
        
        // Variable to store number of components
        int cnt = 0; 
        
        // Start Traversal
        for(int i=0; i < V; i++) {
            // If the node is not visited
            if(!vis[i]) {
                // Increment counter
                cnt++;
                
                /* Start traversal from current 
                node using any traversal */
                bfs(i, adjLs, vis); 
                //dfs(i, adjLs, vis);
            }
        }
        
        // Return the count
        return cnt; 
    }
};

int main() {
    int V = 4, E = 2;
    vector<vector<int>> edges = {
        {0, 1},
        {1, 2}
    };
    
    /* Creating an instance of 
    Solution class */
    Solution sol; 
    
    /* Function call to find the number of 
    connected components in the given graph */
    int ans = sol.findNumberOfComponent(E, V, edges);
    
    cout << "The number of components in the given graph is: " << ans;
    
    return 0;
}