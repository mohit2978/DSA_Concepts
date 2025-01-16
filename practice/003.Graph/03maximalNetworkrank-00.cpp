#include<bits/stdc++.h>
using namespace std;
/*
There is an infrastructure of n cities with some number of roads connecting these cities. Each roads[i] = [ai, bi] indicates that there is a bidirectional road between cities ai and bi.

The network rank of two different cities is defined as the total number of directly connected roads to either city. If a road is directly connected to both cities, it is only counted once.

The maximal network rank of the infrastructure is the maximum network rank of all pairs of different cities.

Given the integer n and the array roads, return the maximal network rank of the entire infrastructure.

Here we need to calculate for every city!!
*/
class Graph{

	int V;
	vector<int> *l;

public:
	Graph(int v){
		V = v;
		l = new vector<int>[V];
	}

	void addEdge(int i,int j){
		l[i].push_back(j);
		l[j].push_back(i);
	}
    int findMaxRank(){
        int res=0;
        for(int i=0;i<V;i++){
            for(int j=i+1;j<V;j++){
              int tres=l[i].size()+l[j].size();
              if (find(l[i].begin(), l[i].end(), j) != l[i].end()) {
                    tres--;
                }
                if(tres>res) res=tres;    
            }
        }
        return res;
    }


};
int maximalNetworkRank(int n, vector<vector<int>> roads) {
 
    Graph graph(n);
    for(auto v:roads){
        graph.addEdge(v[0],v[1]);
    }
    return graph.findMaxRank();
}