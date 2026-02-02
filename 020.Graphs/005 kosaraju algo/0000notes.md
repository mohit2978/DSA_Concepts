# Notes





![alt text](004kosaraju_240112_103625.jpg)




![alt text](004kosaraju_240112_103625(1).jpg) ![alt text](004kosaraju_240112_103625(2).jpg) ![alt text](004kosaraju_240112_103625(3).jpg) ![alt text](004kosaraju_240112_103625(4).jpg) ![alt text](004kosaraju_240112_103625(5).jpg) ![alt text](004kosaraju_240112_103625(6).jpg) ![alt text](004kosaraju_240112_103625(7).jpg) ![alt text](004kosaraju_240112_103625(8).jpg) ![alt text](004kosaraju_240112_103625(9).jpg) ![alt text](004kosaraju_240112_103625(10).jpg) ![alt text](004kosaraju_240112_103625(11).jpg) ![alt text](004kosaraju_240112_103625(12).jpg) ![alt text](004kosaraju_240112_103625(13).jpg)


```java


//User function Template for Java


class Solution
{
    private void dfs(int v,ArrayList<ArrayList<Integer>> adj,int[] vis,LinkedList<Integer>stk){
        vis[v]=1;
        for(var v1:adj.get(v)){
            if(vis[v1]==0){
                dfs(v1,adj,vis,stk);
                    
            }
        }
        
        stk.addFirst(v);
    }
       private void dfs2(int v,ArrayList<ArrayList<Integer>> adj,int[] vis){
        vis[v]=2;
        for(var v1:adj.get(v)){
            if(vis[v1]==1){
                dfs2(v1,adj,vis);
                    
            }
        }
        
    }
    private void transpose(ArrayList<ArrayList<Integer>> adj,ArrayList<ArrayList<Integer>> adj2){
       for(int i=0;i<adj.size();i++){
           for(int n:adj.get(i)){
               adj2.get(n).add(i);
           }
       }
    }
    //Function to find number of strongly connected components in the graph.
    public int kosaraju(int V, ArrayList<ArrayList<Integer>> adj)
    {
        LinkedList<Integer>stk=new LinkedList<>();
        int[] vis=new int[V+1];
        for(int v=0;v<V;v++){
            if(vis[v]==0){
                dfs(v,adj,vis,stk);
            }
        }
        ArrayList<ArrayList<Integer>> adj2=new ArrayList<>();
        for(int v=0;v<adj.size();v++){
            adj2.add(new ArrayList<>());
        }
        transpose(adj,adj2);
        int count=0;
        while(stk.size()>0){
            int el=stk.removeFirst();
            if(vis[el]==1){
                dfs2(el,adj2,vis);
                count++;
            }
        }
        return count;
    }
}
```

 ![alt text](004kosaraju_240112_103625(14).jpg) ![alt text](004kosaraju_240112_103625(15).jpg) ![alt text](004kosaraju_240112_103625(16).jpg) ![alt text](004kosaraju_240112_103625(17).jpg) ![alt text](004kosaraju_240112_103625(18).jpg) ![alt text](004kosaraju_240112_103625(19).jpg) ![alt text](004kosaraju_240112_103625(20).jpg) ![alt text](004kosaraju_240112_103625(21).jpg) ![alt text](004kosaraju_240112_103625(22).jpg) ![alt text](004kosaraju_240112_103625(23).jpg) ![alt text](004kosaraju_240112_103625(24).jpg) ![alt text](004kosaraju_240112_103625(25).jpg) ![alt text](004kosaraju_240112_103625(26).jpg) ![alt text](004kosaraju_240112_103625(27).jpg) ![alt text](004kosaraju_240112_103625(28).jpg) ![alt text](004kosaraju_240112_103625(29).jpg) ![alt text](004kosaraju_240112_103625(30).jpg) ![alt text](004kosaraju_240112_103625(31).jpg) ![alt text](004kosaraju_240112_103625(32).jpg) ![alt text](004kosaraju_240112_103625(33).jpg) ![alt text](004kosaraju_240112_103625(34).jpg) ![alt text](004kosaraju_240112_103625(35).jpg) ![alt text](004kosaraju_240112_103625(36).jpg) ![alt text](004kosaraju_240112_103625(37).jpg) ![alt text](004kosaraju_240112_103625(38).jpg) ![alt text](004kosaraju_240112_103625(39).jpg) ![alt text](004kosaraju_240112_103625(40).jpg)







































