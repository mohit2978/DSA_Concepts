#include<bits/stdc++.h>
using namespace std;


class Node{
public:
	string name;
	list<string> nbrs;

	Node(string name){
		this->name = name;
	}
};

class Graph{
	//Node Name -- Pointer to Node Object
	//m is map having string key and Node pointer to node it is directed to
	
	unordered_map<string,Node*> m;
public:
	Graph(vector<string> cities){
		for(auto city : cities){
			m[city] = new Node(city);
		}
	}

	void addEdge(string x,string y,bool undir=false){
		m[x]->nbrs.push_back(y);
		if(undir){
			m[y]->nbrs.push_back(x);
		}
	}

	void printAdjList(){
		for(auto cityPair : m){
			auto city = cityPair.first;
			cout<<city<<"-->";
			Node *node = cityPair.second;
			for(auto nbr : node->nbrs){
				cout<<nbr<<",";
			}
			cout<<endl;
		}
	}
};


int main(){
	vector<string> cities = {"Delhi","London","Paris","New York"};
	Graph g(cities);
	g.addEdge("Delhi","London",true);
	g.addEdge("New York","London",true);
	g.addEdge("Delhi","Paris",true);
	g.addEdge("Paris","New York",true);

	g.printAdjList();
	

	return 0;
}

/*if undirected=false
Output:
New York-->London,
Paris-->New York,
Delhi-->London,Paris,
London-->
*/

/*
If undirected=true
Output:
New York-->London,Paris,
Paris-->Delhi,New York,
Delhi-->London,Paris,
London-->Delhi,New York,
*/