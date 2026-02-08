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
![alt text](<003 bfs_240306_014327(1).jpg>) ![alt text](<003 bfs_240306_014327(2).jpg>) ![alt text](<003 bfs_240306_014327(3).jpg>) ![alt text](<003 bfs_240306_014327(4).jpg>) ![alt text](<003 bfs_240306_014327(5).jpg>) ![alt text](<003 bfs_240306_014327(6).jpg>) ![alt text](<003 bfs_240306_014327(7).jpg>) ![alt text](<003 bfs_240306_014327(8).jpg>) ![alt text](<003 bfs_240306_014327(9).jpg>) ![alt text](<003 bfs_240306_014327(10).jpg>) ![alt text](<003 bfs_240306_014327(11).jpg>) ![alt text](<003 bfs_240306_014327(12).jpg>) ![alt text](<003 bfs_240306_014327(13).jpg>) ![alt text](<003 bfs_240306_014327(14).jpg>) ![alt text](<003 bfs_240306_014327(15).jpg>) ![alt text](<003 bfs_240306_014327(16).jpg>) ![alt text](<003 bfs_240306_014327(17).jpg>) ![alt text](<003 bfs_240306_014327(18).jpg>) ![alt text](<003 bfs_240306_014327(19).jpg>) ![alt text](<003 bfs_240306_014327(20).jpg>) ![alt text](<003 bfs_240306_014327(21).jpg>) ![alt text](<003 bfs_240306_014327(22).jpg>) ![alt text](<003 bfs_240306_014327(23).jpg>) 

# Shortest Distance in a Binary Maze
Given an n x m matrix grid where each cell contains either 0 or 1, determine the shortest distance between a source cell and a destination cell. You can move to an adjacent cell (up, down, left, or right) if that adjacent cell has a value of 1. The path can only be created out of cells containing 1. If the destination cell is not reachable from the source cell, return -1.


Example 1

Input: grid = [[1, 1, 1, 1],[1, 1, 0, 1],[1, 1, 1, 1],[1, 1, 0, 0],[1, 0, 0, 1]], source = [0, 1], destination = [2, 2]

Output: 3

Explanation: The shortest path from (0, 1) to (2, 2) is:

Move down to (1, 1)

Move down to (2, 1)

Move right to (2, 2)

Thus, the shortest distance is 3

Example 2

Input: grid = [[1, 1, 1, 1, 1],[1, 1, 1, 1, 1],[1, 1, 1, 1, 0],[1, 0, 1, 0, 1]], source = [0, 0], destination = [3, 4]

Output: -1

Explanation: 

Since, there is no path possible between the source cell and the destination cell, hence we return -1.


## Mycode

```cpp
#define P pair<int,int>
class Solution{
public:
    int shortestPath(vector<vector<int>> &grid, pair<int, int> source,
                     pair<int, int> destination) {
       int n=grid.size();
       int m=grid[0].size();
       int dest=destination.first*m+destination.second;
       if(source.first==destination.first && source.second==destination.second) return 0;
       if(grid[destination.first][destination.second]==0) return -1; 
       vector<vector<int>> dis={{1,0},{-1,0},{0,1},{0,-1}}; 
       queue<P> q;
       vector<vector<bool>>vis(n,vector<bool>(m,false));
       q.push({dest,0});
       while(q.size()>0){
        auto rem=q.front();
        int matno=rem.first;
        int r=matno/m;
        int c=matno%m;
        int d=rem.second;
        q.pop();
        if(r==source.first && c==source.second) return d;
        if(vis[r][c]==true) continue;
        vis[r][c]=true;
        for(int i=0;i<4;i++){
            int newr=r+dis[i][0];
            int newc=c+dis[i][1];
            if(newr>=0 && newr<n && newc>=0 && newc<m && grid[newr][newc]==1 && vis[newr][newc]==false){
                q.push({newr*m+newc,d+1});
            }
        }

       }
       return -1;
    }
};
```

Q--> why here we start from souce but in rotting oranges problem we start from destination??


### Why Single-Source and Multi-Source BFS Differ

This is a fantastic conceptual question! It touches on the core difference between **Single-Source BFS** and **Multi-Source BFS**. Here is the breakdown of why the strategies differ:

---

### 1. The Nature of the "Source"

* **Maze Problem (Shortest Path):** You are a single entity (like a rat in a maze). You start at one specific point (**Source**) and want to reach one specific point (**Destination**).
    * **Direction:** Source $\to$ Destination.
    * **Can we swap?** **YES!** Since the graph is undirected, the distance from $A \to B$ is exactly the same as $B \to A$. In your previous code, you actually started from the destination, which is mathematically valid. It only failed due to implementation bugs, not the direction.
* **Rotting Oranges Problem:** The "infection" (rot) starts at multiple locations simultaneously. Every orange that is currently rotten is a **Source** of the infection.
    * **Direction:** Rotten Oranges $\to$ Fresh Oranges.
    * **Can we swap?** **NO.** You cannot start BFS from a fresh orange because you don't know which rotten orange will reach it first. You must simulate the rot spreading from all sources at the same time, layer-by-layer.

---

### 2. Single-Source vs. Multi-Source BFS

| Feature | Maze Shortest Path | Rotting Oranges |
| :--- | :--- | :--- |
| **Type** | Single-Source BFS | **Multi-Source BFS** |
| **Queue Init** | `q.push(Source)` | `q.push(All_Rotten_Oranges)` |
| **Goal** | Find the shortest path to a specific target. | Find the time until the entire grid is covered. |
| **Logic** | "I am here. How many steps to get there?" | "We are all spreading. When does the last person get infected?" |

---

### Summary
In a **Multi-Source BFS**, you load the queue with every starting point at `time = 0`. This ensures that when the "waves" of BFS meet, the distance recorded at any node is the absolute shortest possible distance from *any* of the original sources.

**Would you like to see how to modify a standard BFS template to handle multiple sources efficiently?**




















