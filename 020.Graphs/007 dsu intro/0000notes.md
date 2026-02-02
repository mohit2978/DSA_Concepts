# Notes





![alt text](<006 dsu intro_240113_013159.jpg>)



![alt text](<006 dsu intro_240113_013159(1).jpg>) ![alt text](<006 dsu intro_240113_013159(2).jpg>) ![alt text](<006 dsu intro_240113_013159(3).jpg>) ![alt text](<006 dsu intro_240113_013159(4).jpg>) ![alt text](<006 dsu intro_240113_013159(5).jpg>) ![alt text](<006 dsu intro_240113_013159(6).jpg>) ![alt text](<006 dsu intro_240113_013159(7).jpg>) ![alt text](<006 dsu intro_240113_013159(8).jpg>) ![alt text](<006 dsu intro_240113_013159(9).jpg>) ![alt text](<006 dsu intro_240113_013159(10).jpg>) ![alt text](<006 dsu intro_240113_013159(11).jpg>) ![alt text](<006 dsu intro_240113_013159(12).jpg>) ![alt text](<006 dsu intro_240113_013159(13).jpg>) ![alt text](<006 dsu intro_240113_013159(14).jpg>) ![alt text](<006 dsu intro_240113_013159(15).jpg>) ![alt text](<006 dsu intro_240113_013159(16).jpg>) ![alt text](<006 dsu intro_240113_013159(17).jpg>) ![alt text](<006 dsu intro_240113_013159(18).jpg>) ![alt text](<006 dsu intro_240113_013159(19).jpg>) ![alt text](<006 dsu intro_240113_013159(20).jpg>) ![alt text](<006 dsu intro_240113_013159(21).jpg>) 

```java
//Link--> https://www.geeksforgeeks.org/problems/detect-cycle-using-dsu/1

class Solution
{
    //Function to detect cycle using DSU in an undirected graph.
      class DSU{
       int[] par;
       int[] rank;
       DSU(int v){
         par=new int[v];
         rank=new int[v];
         for(int i=0;i<par.length;i++){
             par[i]=i;
             rank[i]=0;
         }
       }
       public int find(int x){
           if(x==par[x]) return x;
           int parent= find(par[x]);
           if(par[x]!=parent) par[x]=parent;//for compression
           return parent;
       }
       
       public void union(int u,int v){
            int x=findPar(u);
            int y=findPar(v);
           if(rank[x]==rank[y]){
               par[x]=y;
               rank[y]++;
           }
           else if(rank[x]<rank[y]){// to remember ,remember less than pe same order
               par[x]=y;
           }
           else if(rank[x]>rank[y]){//greater than pe last vala phle
               par[y]=x;
           }
       }
   }
    public int detectCycle(int V, ArrayList<ArrayList<Integer>> adj)
    {
        DSU d=new DSU(adj.size());
        
       for(int i=0;i<adj.size();i++){
            for(var v:adj.get(i)){
                int srcPar=d.find(i);
                int destPar=d.find(v);
                if(v>i){ if(srcPar==destPar) return 1;}
                  d.union(srcPar,destPar); 
                    
                  
            }
        }
        return 0; 
    }
}

```
## Is connected code only but have union by size too Cpp code

```cpp
class DisjointSet {
    vector<int>par;
    vector<int>rank;
    vector<int> sz;
public:
    DisjointSet(int n) {
     par.resize(n);
     rank.resize(n,0);
     sz.resize(n,1);
     for(int i=0;i<n;i++) par[i]=i;
    }
    int findPar(int x){
           if(x==par[x]) return x;
           int parent= findPar(par[x]);
           if(par[x]!=parent) par[x]=parent;//for compression
           return parent;
       }

    bool isConnected(int u, int v) {
        return (findPar(u) == findPar(v));
    }

    void unionByRank(int u, int v) {
        int x=findPar(u);
        int y=findPar(v);
        if(x==y) return;
        if(rank[x]==rank[y]){
               par[x]=y;
               rank[y]++;
           }
           else if(rank[x]<rank[y]){
               par[x]=y;
           }
           else if(rank[x]>rank[y]){
               par[y]=x;
           }
    }

    void unionBySize(int u, int v) {
       
       int ulp_u = findPar(u);
       int ulp_v = findPar(v);
       if (ulp_u == ulp_v) return;
    
       if (sz[ulp_u] < sz[ulp_v]) {
           par[ulp_u] = ulp_v;
           sz[ulp_v] += sz[ulp_u];
       }
       else {
           par[ulp_v] = ulp_u;
           sz[ulp_u] += sz[ulp_v];
           
       }
    }
};

```
### The Logic of Union by Rank

The `rank` variable essentially represents the **Height (or Depth)** of the tree.

The goal of **Union by Rank** is to keep the trees as flat (short) as possible to ensure fast search operations.

Here is the visual breakdown of why rank only increases when they are equal.

#### 1. Case: Different Ranks (`rank[x] < rank[y]`)
Imagine:
* **Tree X:** A small tree of height 2.
* **Tree Y:** A tall tree of height 10.

**Action:** We attach the root of **X** to the root of **Y**.
* **Visual:** The small tree (X) becomes a sub-branch of the big tree (Y).
* **Result:** The total height of Y does **not** increase. The new branch (X) only reaches down to depth $2+1 = 3$, which is still much shorter than Y's existing depth of 10.
* **Rank Change:** None. `rank[y]` stays 10.

#### 2. Case: Equal Ranks (`rank[x] == rank[y]`)
Imagine:
* **Tree X:** Height 5.
* **Tree Y:** Height 5.

**Action:** We attach the root of **X** to the root of **Y**.
* **Visual:** You are placing one tree "underneath" the root of the other.
* **Result:**
    * The root of X becomes a child of Y.
    * Every node in X is now **one step deeper** than it was before.
    * Since X was already at the maximum height (5), pushing it down by one step makes the total height **6**.
* **Rank Change:** `rank[y]` must increase by **1**.

### Summary
* **Short attached to Tall:** The "ceiling" doesn't change.
* **Tall attached to Tall:** You are stacking them, so the height grows by exactly 1.

![alt text](<006 dsu intro_240113_013159(22).jpg>)
 ![alt text](<006 dsu intro_240113_013159(23).jpg>)
![alt text](<006 dsu intro_240113_013159(24).jpg>)
![alt text](<006 dsu intro_240113_013159(25).jpg>) 

### Union by Rank vs. Union by Size

Both are optimization strategies to keep the Disjoint Set Union (DSU) trees **flat**.
Without these optimizations, the tree could look like a linked list (Height $N$), making operations $O(N)$.
With either optimization + Path Compression, operations become **$O(\alpha(N))$** (nearly constant).

---

#### 1. Union by Rank (Based on Height)
**Concept:**
* **Rank** $\approx$ **Height** of the tree.
* **Strategy:** Always attach the **Shorter** tree to the **Taller** tree.
* **Why?** Attaching a short tree under a tall root usually doesn't increase the total height.

**Logic:**
```cpp
if (rank[u] < rank[v]) {
    parent[u] = v;          // Attach short to tall
} else if (rank[v] < rank[u]) {
    parent[v] = u;          // Attach short to tall
} else {
    parent[u] = v;          // Same height?
    rank[v]++;              // Height increases by 1
}
```
* **Pros:** Slightly more intuitive regarding tree depth.
* **Cons:** The "Rank" is only an upper bound. Once you use Path Compression, the rank is no longer the true height, but we don't bother correcting it because it still works as a relative measure.

### 2. Union by Size (Based on Node Count)

**Concept:**
* **Size** = Number of nodes in the component.
* **Strategy:** Always attach the **Smaller** tree (fewer nodes) to the **Larger** tree.
* **Why?** We want to minimize the number of nodes that get "moved" to a new parent.

**Logic:**
```cpp
if (size[u] < size[v]) {
    parent[u] = v;          // Attach small to big
    size[v] += size[u];     // Add sizes
} else {
    parent[v] = u;
    size[u] += size[v];     // Add sizes
}
```
* **Pros:**
    * **More Info:** You always know exactly how many nodes are in a connected component. This is extremely useful for many CP problems (e.g., "Find the size of the largest group").
    * **Simple Update:** You always just add `size[a] + size[b]`. No "if equal" edge cases.

### Comparison Summary

| Feature | Union by Rank | Union by Size |
| :--- | :--- | :--- |
| **Metric** | Approximate Height | Exact Node Count |
| **Update Rule** | Increment only if rank is equal | Always sum: `size[root] += size[child]` |
| **Usefulness** | Just for efficiency | Efficiency + Component Size Info |
| **Code Simplicity** | Medium (requires 3 branches) | High (requires 2 branches) |


![alt text](<006 dsu intro_240113_013159(26).jpg>) ![alt text](<006 dsu intro_240113_013159(27).jpg>) ![alt text](<006 dsu intro_240113_013159(28).jpg>) ![alt text](<006 dsu intro_240113_013159(29).jpg>) ![alt text](<006 dsu intro_240113_013159(30).jpg>) ![alt text](<006 dsu intro_240113_013159(31).jpg>) ![alt text](<006 dsu intro_240113_013159(32).jpg>) ![alt text](<006 dsu intro_240113_013159(33).jpg>) ![alt text](<006 dsu intro_240113_013159(34).jpg>) ![alt text](<006 dsu intro_240113_013159(35).jpg>) ![alt text](<006 dsu intro_240113_013159(36).jpg>) ![alt text](<006 dsu intro_240113_013159(37).jpg>) ![alt text](<006 dsu intro_240113_013159(38).jpg>) 


The complexity depends entirely on which optimizations you use.

### The Short Answer (With Optimizations)
For all practical purposes (Competitive Programming and Real World), DSU operations are **Almost Constant Time**.

$$O(\alpha(N)) \approx O(1)$$

### Detailed Complexity Table

| Approach | `find(x)` | `union(x, y)` | Explanation |
| :--- | :--- | :--- | :--- |
| **Naive (No Optimizations)** | $O(N)$ | $O(N)$ | The tree can become a skew line (Linked List). |
| **Only Path Compression** | $O(\log N)$ | $O(\log N)$ | Flattens tree during queries. |
| **Only Union by Rank/Size** | $O(\log N)$ | $O(\log N)$ | Keeps tree balanced (height $\le \log N$). |
| **Both Combined** | $O(\alpha(N))$ | $O(\alpha(N))$ | The "Inverse Ackermann" complexity. |

### What is $\alpha(N)$? (Inverse Ackermann Function)

The function $\alpha(N)$ grows extremely slowly. It is the inverse of the Ackermann function $A(n, n)$, which grows incredibly fast.

* For $N = 10^{600}$ (number of atoms in the universe is only $10^{80}$), $\alpha(N) \le 4$.
* For any value of $N$ you will ever see in a computer, $\alpha(N) \le 4$.

So, while theoretically it is not $O(1)$, practically it behaves exactly like $O(1)$.

### Space Complexity

**$O(N)$**

We simply store `parent[]` and `rank[]`/`size[]` arrays of size $N$.

### Summary
Always implement both **Path Compression** and **Union by Rank/Size** to guarantee the $O(\alpha(N))$ time complexity.




![alt text](<006 dsu intro_240113_013159(39).jpg>) ![alt text](<006 dsu intro_240113_013159(40).jpg>) ![alt text](<006 dsu intro_240113_013159(41).jpg>)

```java

class Solution {
 public class DSU{
       int[] par;
       int[] rank;
       DSU(int v){
         par=new int[v];
         rank=new int[v];
         for(int i=0;i<par.length;i++){
             par[i]=-1;
             rank[i]=0;
         }
       }
       public void makeset(int i){
           par[i]=i;
       }
       public int find(int x){
           if(x==par[x]) return x;
           int parent= find(par[x]);
           par[x]=parent;//for compression
           return parent;
       }
       public int getparent(int i){
           return par[i];
       }
       
       public void union(int x,int y){
           if(rank[x]==rank[y]){
               par[x]=y;
               rank[y]++;
           }
           else if(rank[x]<rank[y]){
               par[x]=y;
           }
           else if(rank[x]>rank[y]){
               par[y]=x;
           }
       }
        }
    public int[] findRedundantConnection(int[][] edges) {
        DSU d=new DSU(edges.length+1);
        int[] res=new int[2];
        for(int i=0;i<edges.length;i++){
            int v1=edges[i][0];
            int v2=edges[i][1];
            
            if(d.getparent(v1)==-1){
                d.makeset(v1);
            }
              if(d.getparent(v2)==-1){
                d.makeset(v2);
            }
            int p1=d.find(v1);
            int p2=d.find(v2);
            if(p1!=p2){
                d.union(p1,p2);
            }
            else{
                res[0]=v1;
                res[1]=v2;
                return res;
            }
        }
        return res;
    }
}


```




 ![alt text](<006 dsu intro_240113_013159(42).jpg>) ![alt text](<006 dsu intro_240113_013159(43).jpg>) ![alt text](<006 dsu intro_240113_013159(44).jpg>) ![alt text](<006 dsu intro_240113_013159(45).jpg>) ![alt text](<006 dsu intro_240113_013159(46).jpg>) ![alt text](<006 dsu intro_240113_013159(47).jpg>) ![alt text](<006 dsu intro_240113_013159(48).jpg>) ![alt text](<006 dsu intro_240113_013159(49).jpg>) ![alt text](<006 dsu intro_240113_013159(50).jpg>) ![alt text](<006 dsu intro_240113_013159(51).jpg>) ![alt text](<006 dsu intro_240113_013159(52).jpg>) ![alt text](<006 dsu intro_240113_013159(53).jpg>) ![alt text](<006 dsu intro_240113_013159(54).jpg>) ![alt text](<006 dsu intro_240113_013159(55).jpg>) ![alt text](<006 dsu intro_240113_013159(56).jpg>) ![alt text](<006 dsu intro_240113_013159(57).jpg>)








































