# Notes


![alt text](<014bellman ford floyd warshall network flow_240423_222140.jpg>)



![alt text](<014bellman ford floyd warshall network flow_240423_222140(1).jpg>)
 ![alt text](<014bellman ford floyd warshall network flow_240423_222140(2).jpg>)
 ![alt text](<014bellman ford floyd warshall network flow_240423_222140(3).jpg>) 


 ```java


// User function Template for Java

/*
*   edges: vector of vectors which represents the graph
*   S: source vertex to start traversing graph with
*   V: number of vertices
*/
class Solution {
    static int[] bellman_ford(int V, ArrayList<ArrayList<Integer>> edges, int S) {
        // Write your code here
        int val=(int)1e8;
        int[] arr=new int[V];
        Arrays.fill(arr,val);
        arr[S]=0;
        for(int i=1;i<=V;i++){
            for(var edge:edges){
                int u=edge.get(0);
                int v=edge.get(1);
                int wt=edge.get(2);
                if(arr[u]==val) continue;
                if(i==V && arr[v]>arr[u]+wt) return new int[]{-1};
                arr[v]=Math.min(arr[v],wt+arr[u]);
            }
        }
        return arr;
    }
}
 ```
 ![alt text](<014bellman ford floyd warshall network flow_240423_222140(4).jpg>) ![alt text](<014bellman ford floyd warshall network flow_240423_222140(5).jpg>) ![alt text](<014bellman ford floyd warshall network flow_240423_222140(6).jpg>) ![alt text](<014bellman ford floyd warshall network flow_240423_222140(7).jpg>) ![alt text](<014bellman ford floyd warshall network flow_240423_222140(8).jpg>) ![alt text](<014bellman ford floyd warshall network flow_240423_222140(9).jpg>) ![alt text](<014bellman ford floyd warshall network flow_240423_222140(10).jpg>) ![alt text](<014bellman ford floyd warshall network flow_240423_222140(11).jpg>) ![alt text](<014bellman ford floyd warshall network flow_240423_222140(12).jpg>) 
 
 
 ![alt text](<014bellman ford floyd warshall network flow_240423_222140(13).jpg>) 
 
 ```java


//User function template for JAVA

class Solution
{
    public void shortest_distance(int[][] matrix)
    {
        for(int v=0;v<matrix.length;v++){
            for(int i=0;i<matrix.length;i++){
                for(int j=0;j<matrix[0].length;j++){
                    if(matrix[i][v]==-1||matrix[v][j]==-1||v==i|| v==j||i==j)
                        continue;
                    else if(matrix[i][j]==-1)
                        matrix[i][j]=matrix[i][v]+matrix[v][j];
                    else
                        matrix[i][j]=Math.min(matrix[i][j],matrix[i][v]+matrix[v][j]);
                }
            }
        }
    }
}
 ```
 
 ![alt text](<014bellman ford floyd warshall network flow_240423_222140(14).jpg>)
 
 
![alt text](<014bellman ford floyd warshall network flow_240423_222140(15).jpg>) 
 
 
 
 ![alt text](<014bellman ford floyd warshall network flow_240423_222140(16).jpg>) 
 
 
 
 
 ![alt text](<014bellman ford floyd warshall network flow_240423_222140(17).jpg>) ![alt text](<014bellman ford floyd warshall network flow_240423_222140(18).jpg>) ![alt text](<014bellman ford floyd warshall network flow_240423_222140(19).jpg>) ![alt text](<014bellman ford floyd warshall network flow_240423_222140(20).jpg>) ![alt text](<014bellman ford floyd warshall network flow_240423_222140(21).jpg>) ![alt text](<014bellman ford floyd warshall network flow_240423_222140(22).jpg>) ![alt text](<014bellman ford floyd warshall network flow_240423_222140(23).jpg>) ![alt text](<014bellman ford floyd warshall network flow_240423_222140(24).jpg>) 
 
 
 ```java

class Solution {
    public  class DSU{
        private int[] par;
        private int[] rank;
        
        DSU(int v){
            par=new int[v];
            rank=new int[v];
            Arrays.fill(par,-1);
        }
        public void makeSet(int v){
            par[v]=v;
            rank[v]=0;
        }
        public int getComp(){
            int comp=0;
            for(int i=0;i<par.length;i++){
                if(par[i]==i||par[i]==-1) comp++;
            }
            return comp;
        }
        public int find(int v){
            if(par[v]==-1) return -1;
            if(v==par[v]) return v;
            int parent=find(par[v]);
            par[v]=parent;
            return parent;
        }
        private void unionHelper(int p1,int p2){
            if(rank[p1]==rank[p2]){
                par[p1]=p2;
                rank[p2]++;
            }
            else if(rank[p1]<rank[p2]){
                par[p1]=p2;
            }
            else{
                par[p2]=p1;
            }
        }
        public int union(int v1,int v2){
            int p1=this.find(v1);
            int p2=this.find(v2);
            if(p1!=p2) {
                this.unionHelper(p1,p2);
                return 0;}
            else return 1;    
        }
    }   
    private int kruskalMST(int n,int[][] edges,int i,boolean taken){
        PriorityQueue<int[]>pq=new PriorityQueue<>((a,b)->(a[2]-b[2]));
        for(int j=0;j<edges.length;j++){
            if(i==j ) continue;
            pq.add(edges[j]);
        }
        DSU d=new DSU(n);
        for(int j=0;j<n;j++){
            d.makeSet(j);
        }
        int wt=0;
        if(taken==true){
             d.union(edges[i][0],edges[i][1]);
             wt+=edges[i][2];}
        
        while(pq.size()>0){
            int[] rem=pq.remove();
            if(d.union(rem[0],rem[1])==0) wt+=rem[2];
        }
        return d.getComp()==1?wt:Integer.MAX_VALUE;

    }
    public List<List<Integer>> findCriticalAndPseudoCriticalEdges(int n, int[][] edges) {
       // Arrays.sort(edges,(a,b)->(a[2]-b[2]));
        int mstWt=kruskalMST(n,edges,-1,false);
        List<List<Integer>>res=new ArrayList<>();
        for(int i=0;i<2;i++){
            List<Integer>v=new ArrayList<>();
            res.add(v);
        }
        for(int i=0;i<edges.length;i++){
            int w1=kruskalMST(n,edges,i,false);
            if(w1>mstWt) res.get(0).add(i);
            else {
                int w2=kruskalMST(n,edges,i,true);
                if(w2==mstWt) res.get(1).add(i);
               // System.out.println(i+" "+w1+" "+w2+" "+mstWt);
            }
        }
        return res;

    }
}
 ```
 
 
 ![alt text](<014bellman ford floyd warshall network flow_240423_222140(25).jpg>) ![alt text](<014bellman ford floyd warshall network flow_240423_222140(26).jpg>) ![alt text](<014bellman ford floyd warshall network flow_240423_222140(27).jpg>) 




























