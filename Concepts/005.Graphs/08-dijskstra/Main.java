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