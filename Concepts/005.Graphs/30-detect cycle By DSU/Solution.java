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