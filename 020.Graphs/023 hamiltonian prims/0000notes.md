# Notes


![alt text](<005hamiltonian and prims intro_240212_134806.jpg>)



![alt text](<005hamiltonian and prims intro_240212_134806(1).jpg>) ![alt text](<005hamiltonian and prims intro_240212_134806(2).jpg>) ![alt text](<005hamiltonian and prims intro_240212_134806(3).jpg>) ![alt text](<005hamiltonian and prims intro_240212_134806(4).jpg>) ![alt text](<005hamiltonian and prims intro_240212_134806(5).jpg>) ![alt text](<005hamiltonian and prims intro_240212_134806(6).jpg>) ![alt text](<005hamiltonian and prims intro_240212_134806(7).jpg>) ![alt text](<005hamiltonian and prims intro_240212_134806(8).jpg>) ![alt text](<005hamiltonian and prims intro_240212_134806(9).jpg>) ![alt text](<005hamiltonian and prims intro_240212_134806(10).jpg>) ![alt text](<005hamiltonian and prims intro_240212_134806(11).jpg>) ![alt text](<005hamiltonian and prims intro_240212_134806(12).jpg>) ![alt text](<005hamiltonian and prims intro_240212_134806(13).jpg>) ![alt text](<005hamiltonian and prims intro_240212_134806(14).jpg>) ![alt text](<005hamiltonian and prims intro_240212_134806(15).jpg>) ![alt text](<005hamiltonian and prims intro_240212_134806(16).jpg>) ![alt text](<005hamiltonian and prims intro_240212_134806(17).jpg>) ![alt text](<005hamiltonian and prims intro_240212_134806(18).jpg>) ![alt text](<005hamiltonian and prims intro_240212_134806(19).jpg>) ![alt text](<005hamiltonian and prims intro_240212_134806(20).jpg>) ![alt text](<005hamiltonian and prims intro_240212_134806(21).jpg>) ![alt text](<005hamiltonian and prims intro_240212_134806(22).jpg>) ![alt text](<005hamiltonian and prims intro_240212_134806(23).jpg>) ![alt text](<005hamiltonian and prims intro_240212_134806(24).jpg>) ![alt text](<005hamiltonian and prims intro_240212_134806(25).jpg>) ![alt text](<005hamiltonian and prims intro_240212_134806(26).jpg>) ![alt text](<005hamiltonian and prims intro_240212_134806(27).jpg>) ![alt text](<005hamiltonian and prims intro_240212_134806(28).jpg>) ![alt text](<005hamiltonian and prims intro_240212_134806(29).jpg>) ![alt text](<005hamiltonian and prims intro_240212_134806(30).jpg>) ![alt text](<005hamiltonian and prims intro_240212_134806(31).jpg>) ![alt text](<005hamiltonian and prims intro_240212_134806(32).jpg>) ![alt text](<005hamiltonian and prims intro_240212_134806(33).jpg>)


### Dijkstara

#### java


```java
class Solution
{
    static class trip{
        int v;
        int wt;
        trip(int v,int wt){
            this.v=v;
            this.wt=wt;
        }
    }
    public  int[] dijkstra(int V, ArrayList<ArrayList<ArrayList<Integer>>> adj, int S)
    {
        PriorityQueue<trip> pq=new PriorityQueue<>((trip a,trip b)-> (a.wt-b.wt));
        pq.add(new trip(S ,0));
        boolean[] vis=new boolean[V];
        int[] res=new int[V];

        // if nit reachable return infinity
        Arrays.fill(res, (int)1e9);
        while(pq.size()>0){
            trip rem=pq.remove();
            if(vis[rem.v]==true) continue;
            vis[rem.v]=true;
            res[rem.v]=rem.wt;
            for(var itr:adj.get(rem.v)){
                int nbr=itr.get(0);
                int w=itr.get(1);
                if(vis[nbr]==false){
                    pq.add(new trip(nbr,rem.wt+w));
                }
            }
        }
        
       return res;
    }
}

```

----
#### java2

```java
// Online Java Compiler
// Use this editor to write, compile and run your Java code online
import java.util.*;
class Main {
    static class trip{
        int v;
        int wt;
        String psf;
        trip(int v,int wt,String psf){
            this.v=v;
            this.wt=wt;
            this.psf=psf;
        }
        
        @Override
        public String toString() {
            return "shortest path to src to "+ v + " path = " + wt + " path=" + psf;
        }
    }
    public static void printShortestPaths(List<List<int[]>> g,int src){
        PriorityQueue<trip> pq=new PriorityQueue<>((trip a,trip b)-> (a.wt-b.wt));
        pq.add(new trip(src ,0, src +""));
        boolean[] vis=new boolean[g.size()];
        
        while(pq.size()>0){
            trip rem=pq.remove();
            if(vis[rem.v]==true) continue;
            vis[rem.v]=true;
            System.out.println(rem);
            for(int[] itr:g.get(rem.v)){
                int nbr=itr[0];
                int w=itr[1];
                if(vis[nbr]==false){
                    pq.add(new trip(nbr,rem.wt+w,rem.psf+","+nbr));
                }
            }
        }
        
        
    }
    public static void main(String[] args) {
        // ===== TEST CASE 1 =====
        // Graph from example:
        // A(0) -4- B(1) -1- C(2) -3- E(4)
        //  \15/         \2/   \1/
        //    C(2)       D(3)---E(4)
        int n1 = 5; // A=0, B=1, C=2, D=3, E=4
        List<List<int[]>> graph1 = new ArrayList<>();
        for (int i = 0; i < n1; i++) graph1.add(new ArrayList<>());
        addEdge(graph1, 0, 1, 4);
        addEdge(graph1, 0, 2, 15);
        addEdge(graph1, 1, 2, 1);
        addEdge(graph1, 1, 3, 2);
        addEdge(graph1, 2, 4, 3);
        addEdge(graph1, 3, 4, 1);

        System.out.println("Test Case 1:");
        printShortestPaths(graph1, 0);

        // ===== TEST CASE 2 =====
        // Simple triangle
        // A(0) -5- B(1)
        // B(1) -2- C(2)
        // A(0) -9- C(2)
        int n2 = 3;
        List<List<int[]>> graph2 = new ArrayList<>();
        for (int i = 0; i < n2; i++) graph2.add(new ArrayList<>());
        addEdge(graph2, 0, 1, 5);
        addEdge(graph2, 1, 2, 2);
        addEdge(graph2, 0, 2, 9);

        System.out.println("\nTest Case 2:");
        printShortestPaths(graph2, 0);

        // ===== TEST CASE 3 =====
        // Linear chain: A -2- B -2- C -2- D
        int n3 = 4;
        List<List<int[]>> graph3 = new ArrayList<>();
        for (int i = 0; i < n3; i++) graph3.add(new ArrayList<>());
        addEdge(graph3, 0, 1, 2);
        addEdge(graph3, 1, 2, 2);
        addEdge(graph3, 2, 3, 2);

        System.out.println("\nTest Case 3:");
        printShortestPaths(graph3, 0);
    }

    // Helper: add undirected edge
    static void addEdge(List<List<int[]>> graph, int u, int v, int w) {
        graph.get(u).add(new int[]{v, w});
        graph.get(v).add(new int[]{u, w});
    }
}



/*
Test Case 1:
shortest path to src to 0 path = 0 path=0
shortest path to src to 1 path = 4 path=0,1
shortest path to src to 2 path = 5 path=0,1,2
shortest path to src to 3 path = 6 path=0,1,3
shortest path to src to 4 path = 7 path=0,1,3,4

Test Case 2:
shortest path to src to 0 path = 0 path=0
shortest path to src to 1 path = 5 path=0,1
shortest path to src to 2 path = 7 path=0,1,2

Test Case 3:
shortest path to src to 0 path = 0 path=0
shortest path to src to 1 path = 2 path=0,1
shortest path to src to 2 path = 4 path=0,1,2
shortest path to src to 3 path = 6 path=0,1,2,3

=== Code Execution Successful ===
*/
```
#### Cpp
```cpp
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

```

### Prims

#### java

```java
class Solution {
    static class trip{
        int v;
        int wt;
        trip(int v,int wt){
            this.v=v;
            this.wt=wt;
        }
    }
    public int spanningTree(int V, List<List<List<Integer>>> adj) {
        PriorityQueue<trip> pq=new PriorityQueue<>((trip a,trip b)-> (a.wt-b.wt));
        pq.add(new trip(0 ,0));
        boolean[] vis=new boolean[V];
        int wt=0;
        while(pq.size()>0){
            trip rem=pq.remove();
            if(vis[rem.v]==true) continue;
            vis[rem.v]=true;
            wt+=rem.wt;
            for(var itr:adj.get(rem.v)){
                int nbr=itr.get(0);
                int w=itr.get(1);
                if(vis[nbr]==false){
                    pq.add(new trip(nbr,w));
                }
            }
        }
        
       return wt;
    }
}


```

#### Cpp
```cpp
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
```