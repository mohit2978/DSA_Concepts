#include<bits/stdc++.h>

using namespace std;

class Graph{

	int V;
	// array of list<int>
	vector<int>*l;

public:
	Graph(int v){
		V = v;
		l = new vector<int>[V];
	}

	void addEdge(int i,int j,bool undir=true){
		l[i].push_back(j);
		if(undir){
			l[j].push_back(i);
		}
	}

	void printAdjList(){
		
		for(int i=0;i<V;i++){
			cout<<i<<"-->";
			
			for(auto node:l[i]){
				cout << node <<",";
			}
			cout <<endl;

		}


	}

};

int main(){
	Graph g(6);
	g.addEdge(0,1);
	g.addEdge(0,4);
	g.addEdge(2,1);
	g.addEdge(3,4);
	g.addEdge(4,5);
	g.addEdge(2,3);
	g.addEdge(3,5);
	g.printAdjList();
	return 0;
}


/*Output:
0-->1,4,
1-->0,2,
2-->1,3,
3-->4,2,5,
4-->0,3,5,
5-->4,3,

*/





