# Notes

![alt text](<005kahns aliendisctionary courseschedule_240307_120321.jpg>)


 ![alt text](<005kahns aliendisctionary courseschedule_240307_120321(1).jpg>) ![alt text](<005kahns aliendisctionary courseschedule_240307_120321(2).jpg>) ![alt text](<005kahns aliendisctionary courseschedule_240307_120321(3).jpg>) ![alt text](<005kahns aliendisctionary courseschedule_240307_120321(4).jpg>) ![alt text](<005kahns aliendisctionary courseschedule_240307_120321(5).jpg>) ![alt text](<005kahns aliendisctionary courseschedule_240307_120321(6).jpg>) ![alt text](<005kahns aliendisctionary courseschedule_240307_120321(7).jpg>) ![alt text](<005kahns aliendisctionary courseschedule_240307_120321(8).jpg>) ![alt text](<005kahns aliendisctionary courseschedule_240307_120321(9).jpg>) ![alt text](<005kahns aliendisctionary courseschedule_240307_120321(10).jpg>)




![alt text](<005kahns aliendisctionary courseschedule_240307_120321(11).jpg>) ![alt text](<005kahns aliendisctionary courseschedule_240307_120321(12).jpg>) ![alt text](<005kahns aliendisctionary courseschedule_240307_120321(13).jpg>) ![alt text](<005kahns aliendisctionary courseschedule_240307_120321(14).jpg>) ![alt text](<005kahns aliendisctionary courseschedule_240307_120321(15).jpg>) ![alt text](<005kahns aliendisctionary courseschedule_240307_120321(16).jpg>) ![alt text](<005kahns aliendisctionary courseschedule_240307_120321(17).jpg>) ![alt text](<005kahns aliendisctionary courseschedule_240307_120321(18).jpg>) 


### Kahns algo cpp code
 
```cpp
class Solution{
public:
    vector<int> topoSort(int V, vector<int> adj[]){
        vector<int>indegree(V,0);
        for(int i=0;i<V;i++){
            for(auto el:adj[i]){
                indegree[el]++;
            }
        }
        queue<int>q;
        for(int i=0;i<V;i++){
            if(indegree[i]==0) q.push(i);
        }
        vector<int>res(V,0);
        int i=0;
        while(q.size()>0){
            int v=q.front();
            q.pop();
            res[i++]=v;
            for(int el:adj[v]){
                indegree[el]--;
                if(indegree[el]==0) q.push(el);
            }
        }
        return res;
    }
};


```

![alt text](<005kahns aliendisctionary courseschedule_240307_120321(19).jpg>) 
![alt text](<005kahns aliendisctionary courseschedule_240307_120321(20).jpg>) 
![alt text](<005kahns aliendisctionary courseschedule_240307_120321(21).jpg>) 
![alt text](<005kahns aliendisctionary courseschedule_240307_120321(22).jpg>) 
![alt text](<005kahns aliendisctionary courseschedule_240307_120321(23).jpg>) 
![alt text](<005kahns aliendisctionary courseschedule_240307_120321(24).jpg>) 








































