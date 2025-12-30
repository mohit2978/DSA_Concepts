# Notes


```cpp

#include<iostream>
#include<list>
#include<queue>
using namespace std;


class Graph{

	int V;

	//widely used representation
	list<int> *l;

public:
	Graph(int v){
		V = v;
		l = new list<int>[V];
	}

	void addEdge(int i,int j,bool undir=true){
		l[i].push_back(j);
		if(undir){
			l[j].push_back(i);
		}
	}
	void bfs(int source){

		queue<int> q;
		//visited array all initialised to 0 initially
		bool *visited = new bool[V]{0};

		q.push(source);
		visited[source] = true;

		while(q.size()>0){
			
			int f = q.front();
			cout<<f <<endl;
			q.pop();

			//PUsh the nbrs of current node inside q if they are not already visited
			for(auto nbr : l[f]){
				if(!visited[nbr]){
					q.push(nbr);
					visited[nbr] = true;
				}
			}
		}
	}
	
	

};

int main(){
	Graph g(7);
	g.addEdge(0,1);
	g.addEdge(1,2);
	g.addEdge(2,3);
	g.addEdge(3,5);
	g.addEdge(5,6);
	g.addEdge(4,5);
	g.addEdge(0,4);
	g.addEdge(3,4);
	g.bfs(1);
	return 0;
}


```
![alt text](<003 bfs_240306_014327.jpg>)
![alt text](<003 bfs_240306_014327(1).jpg>) ![alt text](<003 bfs_240306_014327(2).jpg>) ![alt text](<003 bfs_240306_014327(3).jpg>) ![alt text](<003 bfs_240306_014327(4).jpg>) ![alt text](<003 bfs_240306_014327(5).jpg>) ![alt text](<003 bfs_240306_014327(6).jpg>) ![alt text](<003 bfs_240306_014327(7).jpg>) ![alt text](<003 bfs_240306_014327(8).jpg>) ![alt text](<003 bfs_240306_014327(9).jpg>) ![alt text](<003 bfs_240306_014327(10).jpg>) ![alt text](<003 bfs_240306_014327(11).jpg>) ![alt text](<003 bfs_240306_014327(12).jpg>) ![alt text](<003 bfs_240306_014327(13).jpg>) ![alt text](<003 bfs_240306_014327(14).jpg>) ![alt text](<003 bfs_240306_014327(15).jpg>) ![alt text](<003 bfs_240306_014327(16).jpg>) ![alt text](<003 bfs_240306_014327(17).jpg>) ![alt text](<003 bfs_240306_014327(18).jpg>) ![alt text](<003 bfs_240306_014327(19).jpg>) ![alt text](<003 bfs_240306_014327(20).jpg>) ![alt text](<003 bfs_240306_014327(21).jpg>) ![alt text](<003 bfs_240306_014327(22).jpg>) ![alt text](<003 bfs_240306_014327(23).jpg>) ![alt text](<003 bfs_240306_014327(24).jpg>) ![alt text](<003 bfs_240306_014327(25).jpg>) ![alt text](<003 bfs_240306_014327(26).jpg>)



























