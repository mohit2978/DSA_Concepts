# Accounts Merge

### Problem Description

Given a list of accounts where each element:

```cpp
accounts[i] = [name, email1, email2, ...]
```

represents an account belonging to `name`.

Two accounts belong to the **same person** if they share **at least one common email address**.

Your task is to merge all accounts belonging to the same person and return the merged accounts.

### Rules

* All accounts of the same person have the same name.
* Different people may have the same name.
* If two accounts share an email, they must be merged.
* The returned emails for each account must be sorted lexicographically.
* The order of returned accounts does not matter.

---

## Example 1

### Input

```cpp
accounts = [
    ["John","johnsmith@mail.com","john_newyork@mail.com"],
    ["John","johnsmith@mail.com","john00@mail.com"],
    ["Mary","mary@mail.com"],
    ["John","johnnybravo@mail.com"]
]
```

### Output

```cpp
[
    ["John","john00@mail.com","john_newyork@mail.com","johnsmith@mail.com"],
    ["Mary","mary@mail.com"],
    ["John","johnnybravo@mail.com"]
]
```

### Explanation

The first and second accounts share:

```cpp
johnsmith@mail.com
```

Therefore they belong to the same person and are merged.

---

## Example 2

### Input

```cpp
accounts = [
    ["Gabe","Gabe0@m.co","Gabe3@m.co","Gabe1@m.co"],
    ["Kevin","Kevin3@m.co","Kevin5@m.co","Kevin0@m.co"],
    ["Ethan","Ethan5@m.co","Ethan4@m.co","Ethan0@m.co"],
    ["Hanzo","Hanzo3@m.co","Hanzo1@m.co","Hanzo0@m.co"],
    ["Fern","Fern5@m.co","Fern1@m.co","Fern0@m.co"]
]
```

### Output

```cpp
[
    ["Ethan","Ethan0@m.co","Ethan4@m.co","Ethan5@m.co"],
    ["Gabe","Gabe0@m.co","Gabe1@m.co","Gabe3@m.co"],
    ["Hanzo","Hanzo0@m.co","Hanzo1@m.co","Hanzo3@m.co"],
    ["Kevin","Kevin0@m.co","Kevin3@m.co","Kevin5@m.co"],
    ["Fern","Fern0@m.co","Fern1@m.co","Fern5@m.co"]
]
```

No accounts share emails, so nothing is merged.

---

## Constraints

```cpp
1 <= accounts.length <= 1000

2 <= accounts[i].length <= 10

1 <= accounts[i][j].length <= 30

accounts[i][0] consists of English letters.

accounts[i][j] (for j > 0) is a valid email.

All emails within a single account are unique.

The total number of emails across all accounts is at most 10,000.
```

---

## Why DSU Works Here

Think of each **account index** as a node:

```cpp
0, 1, 2, 3, ...
```

Whenever two accounts share an email:

```cpp
Account 0 <-- johnsmith@mail.com --> Account 1
```

connect them using DSU:

```cpp
union(0, 1)
```

After processing all emails:

```cpp
findUPar(i)
```

tells you which accounts belong to the same person.

### Time Complexity

Let:

```cpp
N = number of accounts
M = total number of emails
```

Then:

```cpp
Building DSU      : O(M * α(N))
Grouping emails   : O(M * α(N))
Sorting emails    : O(M log M)
```

Overall:

```cpp
O(M log M)
```

where `α(N)` (inverse Ackermann function) is nearly constant.


```cpp
class DisjointSet {
   public:
    vector<int> rank, parent, size;

    // Constructor
    DisjointSet(int n) {
        rank.resize(n + 1, 0);
        parent.resize(n + 1);
        size.resize(n + 1);
        for (int i = 0; i <= n; i++) {
            parent[i] = i;
            size[i] = 1;
        }
    }

    // Function to find ultimate parent
    int findUPar(int node) {
        if (node == parent[node]) return node;
        return parent[node] = findUPar(parent[node]);
    }

    // Function to implement union by rank
    void unionByRank(int u, int v) {
        int ulp_u = findUPar(u);
        int ulp_v = findUPar(v);
        if (ulp_u == ulp_v) return;
        if (rank[ulp_u] < rank[ulp_v]) {
            parent[ulp_u] = ulp_v;
        } else if (rank[ulp_v] < rank[ulp_u]) {
            parent[ulp_v] = ulp_u;
        } else {
            parent[ulp_v] = ulp_u;
            rank[ulp_u]++;
        }
    }

    // Function to implement union by size
    void unionBySize(int u, int v) {
        int ulp_u = findUPar(u);
        int ulp_v = findUPar(v);
        if (ulp_u == ulp_v) return;
        if (size[ulp_u] < size[ulp_v]) {
            parent[ulp_u] = ulp_v;
            size[ulp_v] += size[ulp_u];
        } else {
            parent[ulp_v] = ulp_u;
            size[ulp_u] += size[ulp_v];
        }
    }
};

class Solution {
   public:
    vector<vector<string>> accountsMerge(vector<vector<string>> accounts) {
        int n = accounts.size();
        DisjointSet ds(n);
        unordered_map<string, int> mapMailNode;
        for (int i = 0; i < n; i++) {
            for (int j = 1; j < accounts[i].size(); j++) {
                string mail = accounts[i][j];

                if (mapMailNode.find(mail) == mapMailNode.end()) {
                    mapMailNode[mail] = i;
                }

                else {
                    ds.unionBySize(i, mapMailNode[mail]);
                }
            }
        }
        vector<string> mergedMail[n];
        for (auto it : mapMailNode) {
            string mail = it.first;
            int node = ds.findUPar(it.second);
            mergedMail[node].push_back(mail);
        }
        vector<vector<string>> ans;
        for (int i = 0; i < n; i++) {
            if (mergedMail[i].size() == 0) continue;
            sort(mergedMail[i].begin(), mergedMail[i].end());
            vector<string> temp;
            temp.push_back(accounts[i][0]);
            for (auto it : mergedMail[i]) {
                temp.push_back(it);
            }
            ans.push_back(temp);
        }
        sort(ans.begin(), ans.end());
        return ans;
    }
};
```




## Dry Run

### Input
```
accounts = [
  [0]: ["John", "a@gmail.com", "b@gmail.com"]
  [1]: ["John", "c@gmail.com", "a@gmail.com"]   ← shares a@ with [0]
  [2]: ["Mary", "d@gmail.com"]
]
n = 3,  DSU initialized: parent = [0, 1, 2]
```

---

## STEP 1 — Building `mapMailNode`

### i=0 (John's first account)

```
j=1 → mail = "a@gmail.com"
      mapMailNode.find("a@") == end()  → NOT FOUND
      mapMailNode["a@gmail.com"] = 0
```
```
j=2 → mail = "b@gmail.com"
      mapMailNode.find("b@") == end()  → NOT FOUND
      mapMailNode["b@gmail.com"] = 0
```
```
mapMailNode = {
  "a@gmail.com" → 0,
  "b@gmail.com" → 0
}
DSU parent = [0, 1, 2]   (no union yet)
```

---

### i=1 (John's second account)

```
j=1 → mail = "c@gmail.com"
      NOT FOUND
      mapMailNode["c@gmail.com"] = 1
```
```
j=2 → mail = "a@gmail.com"
      FOUND! mapMailNode["a@"] = 0
      → unionBySize(1, 0)
      → parent[1] = 0,  size[0] = 2
```
```
mapMailNode = {
  "a@gmail.com" → 0,
  "b@gmail.com" → 0,
  "c@gmail.com" → 1     ← note: map value stays 1, but DSU links 1→0
}
DSU parent = [0, 0, 2]   ← 1's parent is now 0
```

---

### i=2 (Mary's account)

```
j=1 → mail = "d@gmail.com"
      NOT FOUND
      mapMailNode["d@gmail.com"] = 2
```
```
mapMailNode = {
  "a@gmail.com" → 0,
  "b@gmail.com" → 0,
  "c@gmail.com" → 1,
  "d@gmail.com" → 2
}
DSU parent = [0, 0, 2]   (no change)
```

---

## STEP 2 — Building `mergedMail[]`

```
mergedMail[0] = []
mergedMail[1] = []
mergedMail[2] = []
```

Iterating over `mapMailNode`:

```
mail = "a@gmail.com", stored node = 0
       findUPar(0) = 0  → mergedMail[0].push("a@gmail.com")

mail = "b@gmail.com", stored node = 0
       findUPar(0) = 0  → mergedMail[0].push("b@gmail.com")

mail = "c@gmail.com", stored node = 1
       findUPar(1) → parent[1]=0 → findUPar(0)=0
       root = 0   → mergedMail[0].push("c@gmail.com")
                                  ↑
                          even though map said 1,
                          DSU says root is 0

mail = "d@gmail.com", stored node = 2
       findUPar(2) = 2  → mergedMail[2].push("d@gmail.com")
```

```
mergedMail[0] = ["a@gmail.com", "b@gmail.com", "c@gmail.com"]
mergedMail[1] = []     ← empty! (got absorbed into 0)
mergedMail[2] = ["d@gmail.com"]
```

---

## STEP 3 — Building Answer

```
i=0 → mergedMail[0] not empty
      sort → ["a@gmail.com", "b@gmail.com", "c@gmail.com"]
      name = accounts[0][0] = "John"
      temp = ["John", "a@gmail.com", "b@gmail.com", "c@gmail.com"]  ✓

i=1 → mergedMail[1] is EMPTY → skip

i=2 → mergedMail[2] not empty
      sort → ["d@gmail.com"]
      name = accounts[2][0] = "Mary"
      temp = ["Mary", "d@gmail.com"]  ✓
```

---

## Final Output
```
ans = [
  ["John", "a@gmail.com", "b@gmail.com", "c@gmail.com"],
  ["Mary", "d@gmail.com"]
]
```

---

## Key Insight from Dry Run

```
"c@gmail.com" was stored in map as → 1
But findUPar(1) returned          → 0

This is the magic of DSU:
map tells us "which account first claimed this email"
DSU tells us "who is the root of that account's group"
```








## Time Complexity Analysis

### DisjointSet Operations
- **`findUPar`** → **O(α(n))** — nearly O(1) due to path compression
- **`unionBySize`** → **O(α(n))** — nearly O(1) due to union by size

where **α** is the inverse Ackermann function (effectively constant).

---

### `accountsMerge` — Step by Step

```
accounts = n accounts, each with at most m emails
Total emails across all accounts = E
```

#### Step 1 — Building `mapMailNode`
```cpp
for (int i = 0; i < n; i++)           // n accounts
    for (int j = 1; j < accounts[i].size(); j++)  // m emails each
```
- Iterates over all **E** emails total
- Each `unordered_map` lookup/insert → **O(L)** where L = avg email string length
- Each `unionBySize` → **O(α(n))**

**→ O(E · L)**

---

#### Step 2 — Building `mergedMail[]`
```cpp
for (auto it : mapMailNode)   // E unique emails
    int node = ds.findUPar(it.second);   // O(α(n))
    mergedMail[node].push_back(mail);
```
**→ O(E · L)**

---

#### Step 3 — Sorting & Building Answer
```cpp
for (int i = 0; i < n; i++)
    sort(mergedMail[i].begin(), mergedMail[i].end());
```
- Each component with `k` emails sorts in **O(k log k · L)**
- Summed across all components → **O(E log E · L)**

**→ O(E log E · L)**

---

### Overall Time Complexity

| Step | Complexity |
|------|-----------|
| Build mapMailNode | O(E · L) |
| Build mergedMail | O(E · L) |
| Sort emails + build answer | **O(E log E · L)** |
| **Total** | **O(E log E · L)** |

The **dominant term** is the sorting step.

---

### Simplified (if L treated as constant)

$$\boxed{O(E \log E)}$$

where **E** = total number of emails across all accounts.account `0`.




# Number of Islands — Online Queries



---

### Problem Statement

You are given an **n × m** grid, initially filled entirely with **water**.

You are given **q operations**, where each operation adds a **land cell** at position `[row, col]`.

After **each operation**, return the **number of islands** present in the grid.

> An **island** is a group of land cells connected **horizontally or vertically** (4-directional). Diagonal connections do NOT count.

---

### Example

```
n=3, m=3 (3x3 grid, all water initially)

Operations A = [[0,0], [0,1], [1,1], [1,0], [0,2]]
```

```
After [0,0]:        After [0,1]:        After [1,1]:
■ . .               ■ ■ .               ■ ■ .
. . .               . . .               . ■ .
. . .               . . .               . . .
islands = 1         islands = 1         islands = 1

After [1,0]:        After [0,2]:
■ ■ .               ■ ■ ■
■ ■ .               ■ ■ .
. . .               . . .
islands = 1         islands = 1
```

```
Output = [1, 1, 1, 1, 1]
```

---

### Another Example

```
n=3, m=3
A = [[0,0], [2,2], [0,1], [2,1]]
```

```
After [0,0]:        After [2,2]:        After [0,1]:
■ . .               ■ . .               ■ ■ .
. . .               . . .               . . .
. . ■               . . ■               . . ■
islands = 1         islands = 2         islands = 2
                    ↑ new isolated                    
                      island            

After [2,1]:
■ ■ .
. . .
. ■ ■
islands = 2    ← (2,1) joins (2,2) so still 2
```

```
Output = [1, 2, 2, 2]
```

---

### Input Format

```
n → number of rows
m → number of columns
A → list of q operations, each operation = [row, col]
```

### Output Format

```
A list of q integers where:
answer[i] = number of islands after (i+1)th operation
```

---

### Constraints

```
1 ≤ n, m ≤ 100
1 ≤ q ≤ n*m
0 ≤ row < n
0 ≤ col < m
Same cell may appear multiple times in A
```

---

### Key Observations

```
1. Grid starts as all water

2. Each operation turns one cell to land
   → if cell already land, island count doesn't change

3. New land cell can:
   Case 1: Have NO land neighbors → forms NEW island  (+1)
   Case 2: Have 1 land neighbor   → joins that island  (0)
   Case 3: Have 2+ land neighbors → may MERGE islands  (-k)

4. Answer needed after EVERY operation, not just the last
```

---

### Why DSU?

```
Normal BFS/DFS → O(n*m) per query → O(q*n*m) total → TOO SLOW

DSU → O(α(n*m)) per union/find → O(q*α(n*m)) total → FAST ✅

DSU lets us efficiently:
  → Add new cells (makeSet)
  → Merge neighboring islands (union)
  → Track island count (comp/cnt)
```


## 1st sol 


```cpp
class DisjointSet {
   public:
    vector<int> rank, parent, size;
    int comp;
    // Constructor
    DisjointSet(int n) {
        rank.resize(n + 1, 0);
        parent.resize(n + 1,-1);
        size.resize(n + 1,0);
        comp=0;
        
    }

    void makeSet(int node){
        if(parent[node]!=-1) return;
        parent[node]=node;
        size[node]=1;
        comp++;
    }    
    int getcomp(){
        return comp;
    }
    // Function to find ultimate parent
    int findUPar(int node) {
        if (node == parent[node]) return node;
        return parent[node] = findUPar(parent[node]);
    }

    // Function to implement union by rank
    void unionByRank(int u, int v) {
        int ulp_u = findUPar(u);
        int ulp_v = findUPar(v);
        if (ulp_u == ulp_v) return;
        if (rank[ulp_u] < rank[ulp_v]) {
            parent[ulp_u] = ulp_v;
        } else if (rank[ulp_v] < rank[ulp_u]) {
            parent[ulp_v] = ulp_u;
        } else {
            parent[ulp_v] = ulp_u;
            rank[ulp_u]++;
        }
        comp--;
    }

  
};


class Solution{
public:
vector<int> numOfIslands(int n, int m, vector<vector<int>> &A){
        DisjointSet dsu(n*m);
        vector<int> res;
        set<pair<int,int>> vis;
        vector<vector<int>> dir={{-1,0},{1,0},{0,1},{0,-1}};
        for(auto vec:A){
            int u=vec[0];
            int v=vec[1];
            int node=u*m+v; 
            dsu.makeSet(node);   
            for(int i=0;i<4;i++){
                int newu=u+dir[i][0];
                int newv=v+dir[i][1];
                if(newu>=0 && newu <n && newv>=0 && newv<m && vis.find({newu,newv})!=vis.end()){
                    int newnode=newu*m+newv;
                    dsu.unionByRank(node,newnode);
                }
            }
            vis.insert({u,v});
            res.push_back(dsu.getcomp());      
        }
        return res;
    }
};
```



## Refernce code

```cpp

class DisjointSet {
   public:
    vector<int> rank, parent, size;
    int comp;
    // Constructor
    DisjointSet(int n) {
        rank.resize(n + 1, 0);
        parent.resize(n + 1,-1);
        size.resize(n + 1,0);
        comp=0;
        
    }

    void makeSet(int node){
        if(parent[node]!=-1) return;
        parent[node]=node;
        size[node]=1;
        comp++;
    }    
    int getcomp(){
        return comp;
    }
    // Function to find ultimate parent
    int findUPar(int node) {
        if (node == parent[node]) return node;
        return parent[node] = findUPar(parent[node]);
    }

    // Function to implement union by rank
    void unionByRank(int u, int v) {
        int ulp_u = findUPar(u);
        int ulp_v = findUPar(v);
        if (ulp_u == ulp_v) return;
        if (rank[ulp_u] < rank[ulp_v]) {
            parent[ulp_u] = ulp_v;
        } else if (rank[ulp_v] < rank[ulp_u]) {
            parent[ulp_v] = ulp_u;
        } else {
            parent[ulp_v] = ulp_u;
            rank[ulp_u]++;
        }
        comp--;
    }

  
};


class Solution{
public:
vector<int> numOfIslands(int n, int m, vector<vector<int>> &A){
        DisjointSet dsu(n*m);
        vector<int> res;
        vector<bool>vis(n*m,false);
        vector<vector<int>> dir={{-1,0},{1,0},{0,1},{0,-1}};
        for(auto vec:A){
            int u=vec[0];
            int v=vec[1];
            int node=u*m+v; 
            dsu.makeSet(node);   
            for(int i=0;i<4;i++){
                int newu=u+dir[i][0];
                int newv=v+dir[i][1];
                 int newnode=newu*m+newv;
                if(newu>=0 && newu <n && newv>=0 && newv<m && vis[newnode]==true){
                   
                    dsu.unionByRank(node,newnode);
                }
            }
            vis[node]=true;
            res.push_back(dsu.getcomp());      
        }
        return res;
    }
};


```
## Time & Space Complexity

### Input Definition
```
n = rows, m = cols
q = number of operations (size of A)
Total cells = n*m
```

---

## TIME COMPLEXITY

### Step by Step — Your Code

#### 1. Each operation in A:
```cpp
dsu.makeSet(node)          → O(1)
vis.find({newu,newv})      → O(log q)  ← set lookup
vis.insert({u,v})          → O(log q)  ← set insert
unionByRank                → O(α(n*m))
findUPar                   → O(α(n*m))
```

#### 2. For each operation — 4 neighbors checked:
```
4 × O(log q)  +  4 × O(α(n*m))
= O(log q)  +  O(α(n*m))
= O(log q)          ← dominates since α is ~constant
```

#### 3. Total for q operations:
```
O(q × log q)
```

---

### Step by Step — Reference Code

#### 1. Each operation in A:
```cpp
vis[row][col] == 1         → O(1)  ← array lookup
cnt++ / cnt--              → O(1)
ds.findUPar(nodeNo)        → O(α(n*m))
ds.unionBySize             → O(α(n*m))
```

#### 2. For each operation — 4 neighbors checked:
```
4 × O(1)  +  4 × O(α(n*m))
= O(α(n*m))
≈ O(1)          ← α is effectively constant
```

#### 3. Total for q operations:
```
O(q × α(n*m))
≈ O(q)
```

---

### Time Complexity Comparison

| Operation | Your Code | Reference Code |
|-----------|-----------|----------------|
| vis lookup | O(log q) | O(1) |
| vis insert | O(log q) | O(1) |
| makeSet/union | O(α(n*m)) | O(α(n*m)) |
| **Per operation** | **O(log q)** | **O(α(n*m)) ≈ O(1)** |
| **Total** | **O(q log q)** | **O(q · α(n*m)) ≈ O(q)** |

✅ Reference is faster by **log q** factor

---

## SPACE COMPLEXITY

### Your Code

```
DSU arrays:
  rank[]   → O(n*m)
  parent[] → O(n*m)
  size[]   → O(n*m)

vis set    → O(q)      ← stores at most q pairs
dir[][]    → O(1)
res[]      → O(q)

Total → O(n*m + q)
```

---

### Reference Code

```
DSU arrays:
  rank[]   → O(n*m)
  parent[] → O(n*m)
  size[]   → O(n*m)

vis[][]    → O(n*m)    ← full grid array
ans[]      → O(q)
delRow[]   → O(1)
delCol[]   → O(1)

Total → O(n*m + q)
```

---

### Space Complexity Comparison

| Structure | Your Code | Reference Code |
|-----------|-----------|----------------|
| DSU arrays | O(n*m) | O(n*m) |
| Visited | O(q) | O(n*m) |
| Result array | O(q) | O(q) |
| **Total** | **O(n*m + q)** | **O(n*m + q)** |

```
Both are O(n*m + q) overall.

But there's a subtle difference:

Your code:    vis = O(q)    since set only stores added cells
Reference:    vis = O(n*m)  since full grid allocated upfront

If q << n*m → Your code uses LESS space for vis
If q ≈ n*m → Both roughly same
```

---

## Final Summary

```
        Time              Space
Your:   O(q log q)        O(n*m + q)
Ref:    O(q · α(n*m))     O(n*m + q)
           ≈ O(q)

Time  → Reference wins  (no log factor)
Space → Both same overall
        Your code saves space on vis when q << n*m
        Reference uses full grid regardless
```

So i just updated set by vis array 


## My final code

```cpp

class DisjointSet {
   public:
    vector<int> rank, parent, size;
    int comp;
    // Constructor
    DisjointSet(int n) {
        rank.resize(n + 1, 0);
        parent.resize(n + 1,-1);
        size.resize(n + 1,0);
        comp=0;
        
    }

    void makeSet(int node){
        if(parent[node]!=-1) return;
        parent[node]=node;
        size[node]=1;
        comp++;
    }    
    int getcomp(){
        return comp;
    }
    // Function to find ultimate parent
    int findUPar(int node) {
        if (node == parent[node]) return node;
        return parent[node] = findUPar(parent[node]);
    }

    // Function to implement union by rank
    void unionByRank(int u, int v) {
        int ulp_u = findUPar(u);
        int ulp_v = findUPar(v);
        if (ulp_u == ulp_v) return;
        if (rank[ulp_u] < rank[ulp_v]) {
            parent[ulp_u] = ulp_v;
        } else if (rank[ulp_v] < rank[ulp_u]) {
            parent[ulp_v] = ulp_u;
        } else {
            parent[ulp_v] = ulp_u;
            rank[ulp_u]++;
        }
        comp--;
    }

  
};


class Solution{
public:
vector<int> numOfIslands(int n, int m, vector<vector<int>> &A){
        DisjointSet dsu(n*m);
        vector<int> res;
        vector<bool>vis(n*m,false);
        vector<vector<int>> dir={{-1,0},{1,0},{0,1},{0,-1}};
        for(auto vec:A){
            int u=vec[0];
            int v=vec[1];
            int node=u*m+v; 
            dsu.makeSet(node);   
            for(int i=0;i<4;i++){
                int newu=u+dir[i][0];
                int newv=v+dir[i][1];
                 int newnode=newu*m+newv;
                if(newu>=0 && newu <n && newv>=0 && newv<m && vis[newnode]==true){
                   
                    dsu.unionByRank(node,newnode);
                }
            }
            vis[node]=true;
            res.push_back(dsu.getcomp());      
        }
        return res;
    }
};

```


## Code Review

You replaced `set<pair<int,int>>` with `vector<bool>` — let's verify everything.

---

### Change Made
```cpp
// Before (your old code)
set<pair<int,int>> vis;
vis.find({newu,newv}) != vis.end()   // O(log q)
vis.insert({u,v});

// Now (new code)
vector<bool> vis(n*m, false);
vis[newnode] == true                  // O(1) ✅
vis[node] = true;
```
✅ This is the **same approach as reference code** now, just flattened to 1D instead of 2D.

---

### Full Code Check

**Constructor** ✅
```cpp
DisjointSet(int n) {
    rank.resize(n + 1, 0);
    parent.resize(n + 1,-1);
    size.resize(n + 1,0);
    comp=0;
}
```

**makeSet** ✅
```cpp
void makeSet(int node){
    if(parent[node]!=-1) return;  // duplicate guard
    parent[node]=node;
    size[node]=1;
    comp++;
}
```

**findUPar** ✅
```cpp
int findUPar(int node) {
    if (node == parent[node]) return node;
    return parent[node] = findUPar(parent[node]);
}
```

**unionByRank** ✅
```cpp
void unionByRank(int u, int v) {
    int ulp_u = findUPar(u);
    int ulp_v = findUPar(v);
    if (ulp_u == ulp_v) return;
    ...
    comp--;
}
```

**Main Logic** ✅
```cpp
int node = u*m+v;
dsu.makeSet(node);              // add cell, comp++

for(int i=0;i<4;i++){
    int newnode = newu*m+newv;
    if(bounds check && vis[newnode]==true){
        dsu.unionByRank(node,newnode);  // merge, comp--
    }
}
vis[node] = true;               // mark AFTER neighbor check ✅
res.push_back(dsu.getcomp());
```

---

### Dry Run
```
n=2, m=2,  A=[[0,0],[0,1],[1,0],[1,1]]
vis = [F, F, F, F]   (size n*m = 4)

[0,0] → node=0: makeSet(0), comp=1
        neighbors: none in vis
        vis=[T,F,F,F] → res=[1]

[0,1] → node=1: makeSet(1), comp=2
        neighbor (0,0)→node=0, vis[0]=T → union(1,0), comp=1
        vis=[T,T,F,F] → res=[1,1]

[1,0] → node=2: makeSet(2), comp=2
        neighbor (0,0)→node=0, vis[0]=T → union(2,0), comp=1
        vis=[T,T,T,F] → res=[1,1,1]

[1,1] → node=3: makeSet(3), comp=2
        neighbor (0,1)→node=1, vis[1]=T → union(3,1), comp=1
        neighbor (1,0)→node=2, vis[2]=T → union(3,2)
                                           same root → skip
        vis=[T,T,T,T] → res=[1,1,1,1] ✓
```

---

### Complexity After Fix

| | Your New Code | Reference Code |
|--|--------------|----------------|
| vis lookup | O(1) ✅ | O(1) ✅ |
| vis space | O(n\*m) | O(n\*m) |
| Time total | **O(q·α(n\*m))** | **O(q·α(n\*m))** |
| Space total | **O(n\*m + q)** | **O(n\*m + q)** |

---

### Final Verdict
```
✅ Code is correct
✅ Now matches reference code's time complexity
✅ vis[node]=true placed correctly after neighbor loop
✅ Duplicate cell handled by makeSet guard
✅ All edge cases covered
```
**Your new code is essentially equivalent to the reference code in both correctness and complexity.**

---

























## Making a Large Island

---

### Intuition

```
Brute Force idea:
  Try flipping each 0 → 1
  Run BFS/DFS to find largest island
  → O(n²) flips × O(n²) BFS = O(n⁴)  TOO SLOW

Better idea with DSU:
  Step 1: Build DSU for all existing 1s → track island sizes
  Step 2: For each 0, look at its 4 neighbors
          → sum sizes of DISTINCT islands around it + 1
  Step 3: Return maximum
  → O(n²)  FAST ✅
```

---

### Algorithm

```
Step 1: Assign each island a unique component ID
        Track size of each component in DSU

Step 2: For every cell with 0:
        → check 4 neighbors
        → collect DISTINCT component roots
        → answer = 1 + sum of their sizes

Step 3: Edge case — if no 0 exists, return n*n
```

---

### Dry Run

```
grid = [[1,1,0],
        [0,0,1],
        [1,0,1]]

n=3, m=3
node = row*m + col
```

#### Step 1 — Build DSU for all 1s

```
Process all 1s and union neighbors:

(0,0)→node 0, (0,1)→node 1  : union(0,1)   → same island
(1,2)→node 5, (0,2) is 0    : no union
(2,0)→node 6                : alone
(2,2)→node 8, (1,2)→node 5  : union(8,5)

DSU state:
  Component A: {0,1}      → root=1, size=2   [(0,0),(0,1)]
  Component B: {5,8}      → root=5, size=2   [(1,2),(2,2)]
  Component C: {6}        → root=6, size=1   [(2,0)]
```

#### Step 2 — Check each 0

```
0 cells: (0,2), (1,0), (1,1), (2,1)
```

```
(0,2) → node 2:
  neighbors:
    (0,1)→node 1 → is 1 → root=1, size=2   ← Component A
    (1,2)→node 5 → is 1 → root=5, size=2   ← Component B
    (-1,2) → out of bounds
    (0,3)  → out of bounds
  distinct roots = {1, 5}
  answer = 1 + size[1] + size[5] = 1+2+2 = 5 ✓
```

```
(1,0) → node 3:
  neighbors:
    (0,0)→node 0 → is 1 → root=1, size=2   ← Component A
    (2,0)→node 6 → is 1 → root=6, size=1   ← Component C
    (1,1)→node 4 → is 0
    (1,-1) → out of bounds
  distinct roots = {1, 6}
  answer = 1 + 2 + 1 = 4
```

```
(1,1) → node 4:
  neighbors:
    (0,1)→node 1 → is 1 → root=1, size=2   ← Component A
    (2,1)→node 7 → is 0
    (1,0)→node 3 → is 0
    (1,2)→node 5 → is 1 → root=5, size=2   ← Component B
  distinct roots = {1, 5}
  answer = 1 + 2 + 2 = 5
```

```
(2,1) → node 7:
  neighbors:
    (1,1)→node 4 → is 0
    (3,1) → out of bounds
    (2,0)→node 6 → is 1 → root=6, size=1   ← Component C
    (2,2)→node 8 → is 1 → root=5, size=2   ← Component B
  distinct roots = {6, 5}
  answer = 1 + 1 + 2 = 4
```

```
Maximum = 5
```

---

### Why DISTINCT roots matter

```
grid = [[1,0,1],
        [1,0,1],
        [1,1,1]]

Flipping center (1,1):
  neighbors: (0,1)=0, (2,1)=1, (1,0)=1, (1,2)=1

  (2,1), (1,0), (1,2) are all 1s
  BUT (1,0) and (2,1) might be SAME island already!

  If we don't check distinct roots:
    count same island TWICE → WRONG answer

  Set of roots ensures each island counted ONCE ✅
```

---

### Code without distinct root

```cpp
class DisjointSet {
   public:
    vector<int> rank, parent, size;

    // Constructor
    DisjointSet(int n) {
        rank.resize(n + 1, 0);
        parent.resize(n + 1);
        size.resize(n + 1);
        for (int i = 0; i <= n; i++) {
            parent[i] = i;
            size[i] = 1;
        }
    }

    // Function to find ultimate parent
    int findUPar(int node) {
        if (node == parent[node]) return node;
        return parent[node] = findUPar(parent[node]);
    }

    // Function to implement union by size
    void unionBySize(int u, int v) {
        int ulp_u = findUPar(u);
        int ulp_v = findUPar(v);
        if (ulp_u == ulp_v) return;
        if (size[ulp_u] < size[ulp_v]) {
            parent[ulp_u] = ulp_v;
            size[ulp_v] += size[ulp_u];
        } else {
            parent[ulp_v] = ulp_u;
            size[ulp_u] += size[ulp_v];
        }
    }
};

class Solution {
   public:
    int largestIsland(vector<vector<int>>& grid) {
        int n = grid.size();
        DisjointSet ds(n * n);
        vector<vector<int>> dir = {{-1, 0}, {1, 0}, {0, 1}, {0, -1}};

        // Step 1: Union all existing 1s
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 0) continue;
                for (auto d : dir) {
                    int ni = i + d[0];
                    int nj = j + d[1];
                    if (ni >= 0 && ni < n && nj >= 0 && nj < n &&
                        grid[ni][nj] == 1) {
                        ds.unionBySize(i * n + j, ni * n + nj);
                    }
                }
            }
        }

        // Step 2: Try flipping each 0
        int ans = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 1) {
                    // Edge case: all 1s, no 0 to flip
                    ans = max(ans, ds.size[ds.findUPar(i * n + j)]);
                    continue;
                }
                int total = 1;
                for (auto d : dir) {
                    int ni = i + d[0];
                    int nj = j + d[1];
                    if (ni >= 0 && ni < n && nj >= 0 && nj < n &&
                        grid[ni][nj] == 1) {
                        total += ds.size[ds.findUPar(ni * n + nj)];
                    }
                }
                ans = max(ans, total);
            }
        }
        return ans;
    }
};

```

## Code Review

### The Bug — Missing Distinct Roots Check

```cpp
// Step 2: Try flipping each 0
int total = 1;
for (auto d : dir) {
    int ni = i + d[0];
    int nj = j + d[1];
    if (ni >= 0 && ni < n && nj >= 0 && nj < n &&
        grid[ni][nj] == 1) {
        total += ds.size[ds.findUPar(ni * n + nj)];  // ← BUG HERE
    }
}
```

**Problem:** Two neighbors can belong to the **same island** — you'd count that island's size **twice**.

---

### Bug Dry Run

```
grid = [[1, 1],
        [1, 0]]

n=2
After Step 1 unions:
  (0,0)=0, (0,1)=1, (1,0)=2  all connected
  root = 0,  size[0] = 3
```

```
Flipping (1,1) → node 3:
  neighbors:
    (0,1) → node 1 → root = findUPar(1) = 0, size[0] = 3
    (1,0) → node 2 → root = findUPar(2) = 0, size[0] = 3
                              ↑ SAME ROOT!

total = 1 + 3 + 3 = 7   ← WRONG ❌
correct = 1 + 3 = 4     ← RIGHT ✅
```

---

### Fix — Use a Set for Distinct Roots

```cpp
// Step 2: Try flipping each 0
int ans = 0;
for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
        if (grid[i][j] == 1) {
            ans = max(ans, ds.size[ds.findUPar(i * n + j)]);
            continue;
        }
        set<int> distinctRoots;          // ← ADD THIS
        int total = 1;
        for (auto d : dir) {
            int ni = i + d[0];
            int nj = j + d[1];
            if (ni >= 0 && ni < n && nj >= 0 && nj < n &&
                grid[ni][nj] == 1) {
                int root = ds.findUPar(ni * n + nj);
                if(distinctRoots.find(root) == distinctRoots.end()){
                    distinctRoots.insert(root);   // ← only count once
                    total += ds.size[root];
                }
            }
        }
        ans = max(ans, total);
    }
}
```

---

### When Does Bug Trigger?

```
Bug triggers when a 0 cell has 2+ neighbors
belonging to the SAME island

Safe cases (bug doesn't matter):
  . 1 .          each neighbor is isolated
  1 0 1    →     all different islands → no double count
  . 1 .

Bug triggers:
  1 1 .
  1 0 .    →     (0,0),(0,1),(1,0) all same island
  . . .          flipping (1,1) counts that island 2-3x
```

---



---

### Summary

| | Your Code | Fixed Code |
|--|-----------|------------|
| Same island counted twice | ❌ Yes | ✅ No |
| Distinct root check | ❌ Missing | ✅ Set used |
| Edge case (all 1s) | ✅ Handled | ✅ Handled |
| Step 1 unions | ✅ Correct | ✅ Correct |

```
Only one fix needed:
  Track distinct roots using a set
  Add size only if root not already seen
```

### correct code

```cpp
class DisjointSet {
   public:
    vector<int> rank, parent, size;

    // Constructor
    DisjointSet(int n) {
        rank.resize(n + 1, 0);
        parent.resize(n + 1);
        size.resize(n + 1);
        for (int i = 0; i <= n; i++) {
            parent[i] = i;
            size[i] = 1;
        }
    }

    // Function to find ultimate parent
    int findUPar(int node) {
        if (node == parent[node]) return node;
        return parent[node] = findUPar(parent[node]);
    }

    // Function to implement union by size
    void unionBySize(int u, int v) {
        int ulp_u = findUPar(u);
        int ulp_v = findUPar(v);
        if (ulp_u == ulp_v) return;
        if (size[ulp_u] < size[ulp_v]) {
            parent[ulp_u] = ulp_v;
            size[ulp_v] += size[ulp_u];
        } else {
            parent[ulp_v] = ulp_u;
            size[ulp_u] += size[ulp_v];
        }
    }
};

class Solution {
   public:
    int largestIsland(vector<vector<int>>& grid) {
        int n = grid.size();
        DisjointSet ds(n * n);
        vector<vector<int>> dir = {{-1, 0}, {1, 0}, {0, 1}, {0, -1}};

        // Step 1: Union all existing 1s
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 0) continue;
                for (auto d : dir) {
                    int ni = i + d[0];
                    int nj = j + d[1];
                    if (ni >= 0 && ni < n && nj >= 0 && nj < n &&
                        grid[ni][nj] == 1) {
                        ds.unionBySize(i * n + j, ni * n + nj);
                    }
                }
            }
        }

        // Step 2: Try flipping each 0
        int ans = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 1) {
                    // Edge case: all 1s, no 0 to flip
                    ans = max(ans, ds.size[ds.findUPar(i * n + j)]);
                    continue;
                }
                int total = 1;
                set<int> distinctRoots;
                for (auto d : dir) {
                    int ni = i + d[0];
                    int nj = j + d[1];
                    if (ni >= 0 && ni < n && nj >= 0 && nj < n &&
                        grid[ni][nj] == 1) {
                        int root = ds.findUPar(ni * n + nj);
                        if (distinctRoots.find(root) == distinctRoots.end()) {
                            distinctRoots.insert(root);  // ← only count once
                            total += ds.size[root];
                        }
                    }
                }
                ans = max(ans, total);
            }
        }
        return ans;
    }
};

```

---

### Complexity

```
N = n*n = total cells

Time:
  Step 1 (union all 1s)   → O(N × α(N)) ≈ O(N)
  Step 2 (check all 0s)   → O(N × 4)    = O(N)
  set operations inside   → O(4 log 4)  = O(1)  ← at most 4 neighbors
  ─────────────────────────────────────────────
  Total                   → O(N) = O(n²)

Space:
  DSU arrays              → O(N)
  distinctRoots set       → O(4) = O(1)  ← at most 4 neighbors
  ─────────────────────────────────────────────
  Total                   → O(N) = O(n²)
```