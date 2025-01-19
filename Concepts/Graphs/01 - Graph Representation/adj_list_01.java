
import java.util.ArrayList;


public class adj_list_01{

    static class Graph{
        int V;

        // used this widely
        ArrayList<Integer>[] list;

        public Graph(int v){
            V = v;
            list = new ArrayList[v];
            for(int i = 0; i < v; i++){
                list[i] = new ArrayList<>();
            }
        }
        //no default parameter in java like cpp
        void addEdge(int i, int j, boolean unDirected){
            list[i].add(j);
            if(unDirected)
                list[j].add(i);
        }

        void printAdjList(){
            // Iterate over all the rows!!
            for(int i = 0; i < V; i++){
                System.out.print(i + " --> ");
                // Iterating over one row!
                for(int node: list[i]){
                    System.out.print(node + ", ");
                }

                System.out.println();
            }
        }
    }

    public static void main(String[] args){
        Graph g = new Graph(6);

        g.addEdge(0,1, true);
        g.addEdge(0,4, true);
        g.addEdge(2,1, true);
        g.addEdge(3,4, true);
        g.addEdge(4,5, true);
        g.addEdge(2,3, true);
        g.addEdge(3,5, true);
        g.printAdjList();

    }
}
/* Output:

0 --> 1, 4, 
1 --> 0, 2, 
2 --> 1, 3, 
3 --> 4, 2, 5, 
4 --> 0, 3, 5, 
5 --> 4, 3, 
*/
