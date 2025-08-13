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

