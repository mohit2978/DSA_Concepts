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