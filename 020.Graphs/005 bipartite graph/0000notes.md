# Is Bipartite

![alt text](<004dijsktra bipartite_240205_000336.jpg>)
![alt text](<004dijsktra bipartite_240205_000336(1).jpg>) ![alt text](<004dijsktra bipartite_240205_000336(2).jpg>) 

### BFS solution

```cpp
class Solution{
 bool bfsCycle(int i,vector<int> adj[],int V,vector<bool>& vis){
    queue<int>q;
    q.push(i);
    while(q.size()>0){
        int v=q.front();
        q.pop();
        if(vis[v]==true) return true;
        vis[v]=true;
        for(auto nbr:adj[v]){
            if(vis[nbr]==false) q.push(nbr);
        }
    }
    return false;
 }
public:
    bool isCycle(int V, vector<int> adj[]) {
        vector<bool>vis(V,false);
        for(int i=0;i<V;i++){
            if(vis[i]==false){
               bool val= bfsCycle(i,adj,V,vis);
               if(val==true) return true;
            }
        }

        return false;
    }
};
```
### DFSsol

```cpp
class Solution{
 bool dfsCycle(int i,vector<int> adj[],int V,vector<bool>& vis,int par){
    vis[i]=true;
    for(auto nbr:adj[i]){
        if(vis[nbr]==false){
           bool val= dfsCycle(nbr,adj,V,vis,i);
           if(val==true) return true;
        }// If the neighbor is visited and it's NOT the parent, we found a cycle!
        else if (nbr != par) {
            return true;
        }
    }
    return false;
 }
public:
    bool isCycle(int V, vector<int> adj[]) {
        vector<bool>vis(V,false);
        for(int i=0;i<V;i++){
            if(vis[i]==false){
               bool val= dfsCycle(i,adj,V,vis,-1);
               if(val==true) return true;
            }
        }

        return false;
    }
};
```
Most recursive functions start with a base case, but in this specific algorithm, that first line(`if(vis[i]==true) return true`) actually becomes redundant (and slightly problematic) because of how we handle the neighbor loop.

Here is why you don't need it:

#### 1. The "Look Before You Leap" Strategy
In the corrected version of the code, we perform the "visited" check before making the recursive call.

```C++

for (auto nbr : adj[i]) {
    if (!vis[nbr]) { 
        // We only call the function if we KNOW vis[nbr] is false
        if (dfsCycle(nbr, adj, V, vis, i)) return true;
    } 
    else if (nbr != par) {
        // If it's already visited and NOT the parent, it's a cycle
        return true; 
    }
}
```
Because of the if `(!vis[nbr])` guard, the function dfsCycle will never be called with an i that is already visited. Therefore, checking it again at the very top of the function is redundant—it's like checking if a door is locked after you’ve already confirmed it's open and walked through it.


#### 2. Distinguishing Cycles from Back-Tracing

In an undirected graph, every edge is a two-way street. If you are at Node A and move to Node B, Node B's neighbor list contains Node A.

If you kept your original if(vis[i] == true) return true at the top, the moment the algorithm looks back from Node B to Node A, it would see Node A is "visited" and immediately declare a cycle.

By removing that top check and using the else if (nbr != par) logic inside the loop, you specifically tell the code:

"If I see a visited node and it's my parent, that's just the way I came in. Ignore it."

"If I see a visited node and it's not my parent, I've found a shortcut back to an earlier part of the path. That is a cycle."

### Summary
The check at the top is replaced by a more surgical check inside the loop that can tell the difference between a back-edge (a cycle) and the parent-edge (the path you are currently walking).

![alt text](<004dijsktra bipartite_240205_000336(3).jpg>) ![alt text](<004dijsktra bipartite_240205_000336(4).jpg>) ![alt text](<004dijsktra bipartite_240205_000336(5).jpg>) ![alt text](<004dijsktra bipartite_240205_000336(6).jpg>) ![alt text](<004dijsktra bipartite_240205_000336(7).jpg>) ![alt text](<004dijsktra bipartite_240205_000336(8).jpg>) ![alt text](<004dijsktra bipartite_240205_000336(9).jpg>)



 
 
  ![alt text](<004dijsktra bipartite_240205_000336(12).jpg>) ![alt text](<004dijsktra bipartite_240205_000336(13).jpg>) ![alt text](<004dijsktra bipartite_240205_000336(14).jpg>) ![alt text](<004dijsktra bipartite_240205_000336(15).jpg>) ![alt text](<004dijsktra bipartite_240205_000336(16).jpg>) ![alt text](<004dijsktra bipartite_240205_000336(17).jpg>) 


### BFS solution

```java
class Solution {
     public static class Pair{
      int v;
      int lvl;
      Pair(int v,int lvl){
         this.v=v;
         this.lvl=lvl;
      }
   }
    public boolean isBipartite(int[][] graph) {
        
    int[] lvl=new int[graph.length];
    boolean[] vis=new boolean[graph.length];
    LinkedList<Pair>q=new LinkedList<>();
    for(int v=0;v<graph.length;v++){
       if(vis[v]==false){
       q.addLast(new Pair(v,1));
       while(q.size()>0){
          Pair removed=q.remove();
          if(vis[removed.v]==true) {
              if(lvl[removed.v]==removed.lvl)
              continue;
              else {
                 return false;
              }
           }
          else lvl[removed.v]=removed.lvl;
          
          vis[removed.v]=true;
          for(int i=0;i<graph[removed.v].length;i++){
            if(vis[graph[removed.v][i]]==false){
               q.addLast(new Pair(graph[removed.v][i],removed.lvl+1));
            }
         }
         
      } 
   }
      }
    return true;
    }
}
```

Non-cycle --> Always bipartite 

even len cycle --> Always Bipartite

Odd len cycle--> non-bipartite

even len cycle--> last vertex visited at odd level 

odd len cycle --> last vertex visted at even level

so in old len cycle prev level will not be same as current level henec not be bipartite.


## sol 2 Coloring solution 

 
 ### Cpp

 ```cpp
class Solution{
    bool traverseDFS( vector<int>graph[],vector<int>&vis,int v,int color){
        vis[v]=color;
        for(auto nbr:graph[v]){
            if(vis[nbr]==0){
                bool isbip=traverseDFS(graph,vis,nbr,-1*color);
                if(isbip==false) return false;
            }
            else {
                int oldcolor=vis[nbr];
                int newcolor=-1*color;
                if(oldcolor!=newcolor) return false;
            }
        }
        return true;

    }
 
public:
    bool isBipartite(int V, vector<int> adj[])  {
        vector<int>vis(V);
        for(int v=0;v<V;v++){
            if(vis[v]==0){
                bool isbipartite=traverseDFS(adj,vis,v,1);
                if(isbipartite==false)
                    return false;
  
                    }
            }
        return true;
    }
};

 ```
 ### Java

```java
class Solution {

    public boolean traverseDFS(int[][]graph,int[] vis,int v,int color){
        vis[v]=color;
        for(var nbr:graph[v]){
            if(vis[nbr]==0){
                boolean isbip=traverseDFS(graph,vis,nbr,-1*color);
                if(isbip==false) return false;
            }
            else {
                int oldcolor=vis[nbr];
                int newcolor=-1*color;
                if(oldcolor!=newcolor) return false;
            }
        }
        return true;

    }
 
    

    public boolean isBipartite(int[][] graph) {
        
        int [] vis=new int[graph.length];
        for(int v=0;v<graph.length;v++){
            if(vis[v]==0){
                boolean isbipartite=traverseDFS(graph,vis,v,1);
                if(isbipartite==false)
                    return false;
  
                    }
            }
        return true;
    }
}
```