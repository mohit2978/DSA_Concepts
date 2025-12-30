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


![alt text](<006 dsu intro_240113_013159(22).jpg>) ![alt text](<006 dsu intro_240113_013159(23).jpg>) ![alt text](<006 dsu intro_240113_013159(24).jpg>) ![alt text](<006 dsu intro_240113_013159(25).jpg>) ![alt text](<006 dsu intro_240113_013159(26).jpg>) ![alt text](<006 dsu intro_240113_013159(27).jpg>) ![alt text](<006 dsu intro_240113_013159(28).jpg>) ![alt text](<006 dsu intro_240113_013159(29).jpg>) ![alt text](<006 dsu intro_240113_013159(30).jpg>) ![alt text](<006 dsu intro_240113_013159(31).jpg>) ![alt text](<006 dsu intro_240113_013159(32).jpg>) ![alt text](<006 dsu intro_240113_013159(33).jpg>) ![alt text](<006 dsu intro_240113_013159(34).jpg>) ![alt text](<006 dsu intro_240113_013159(35).jpg>) ![alt text](<006 dsu intro_240113_013159(36).jpg>) ![alt text](<006 dsu intro_240113_013159(37).jpg>) ![alt text](<006 dsu intro_240113_013159(38).jpg>) ![alt text](<006 dsu intro_240113_013159(39).jpg>) ![alt text](<006 dsu intro_240113_013159(40).jpg>) ![alt text](<006 dsu intro_240113_013159(41).jpg>)

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








































