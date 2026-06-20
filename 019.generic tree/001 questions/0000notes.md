# Q1 3965. Finish Time of Tasks I
## Problem Description

LC https://leetcode.com/problems/finish-time-of-tasks-i/

You're given `n` tasks (0 to n-1) forming a tree rooted at task 0, described by `edges[i] = [ui, vi]` (ui is parent of vi). Each task `i` has a `baseTime[i]`.

Finish time is computed recursively:
- **Leaf task**: finish time = `baseTime[i]`
- **Non-leaf task**:
  - `earliest` = min finish time among children
  - `latest` = max finish time among children
  - `ownDuration` = `(latest - earliest) + baseTime[i]`
  - finish time = `latest + ownDuration`

Return the finish time of task 0.


## Examples

**Example 1:**
```
Input: n = 3, edges = [[0,1],[1,2]], baseTime = [9,5,3]
Output: 17
```
Explanation:
- Task 2 is a leaf → finish time = `baseTime[2]` = 3
- Task 1 has one child (task 2):
  - `earliest = latest = 3`
  - `ownDuration = (latest - earliest) + baseTime[1] = 0 + 5 = 5`
  - finish time of task 1 = `latest + ownDuration = 3 + 5 = 8`
- Task 0 has one child (task 1, finish time 8):
  - `earliest = latest = 8`
  - `ownDuration = (latest - earliest) + baseTime[0] = 0 + 9 = 9`
  - finish time of task 0 = `8 + 9 = 17`

**Example 2:**
```
Input: n = 3, edges = [[0,1],[0,2]], baseTime = [4,7,6]
Output: 12
```
Explanation:
- Task 1 is a leaf → finish time = `baseTime[1]` = 7
- Task 2 is a leaf → finish time = `baseTime[2]` = 6
- Task 0 has two children with finish times 7 and 6:
  - `earliest = 6, latest = 7`
  - `ownDuration = (latest - earliest) + baseTime[0] = (7 - 6) + 4 = 5`
  - finish time of task 0 = `latest + ownDuration = 7 + 5 = 12`

**Example 3:**
```
Input: n = 4, edges = [[0,1],[0,2],[2,3]], baseTime = [5,8,2,1]
Output: 18
```
Explanation:
- Task 1 is a leaf → finish time = `baseTime[1]` = 8
- Task 3 is a leaf → finish time = `baseTime[3]` = 1
- Task 2 has one child (task 3):
  - `earliest = latest = 1`
  - `ownDuration = (latest - earliest) + baseTime[2] = 0 + 2 = 2`
  - finish time of task 2 = `latest + ownDuration = 1 + 2 = 3`
- Task 0 has two children with finish times 8 and 3:
  - `earliest = 3, latest = 8`
  - `ownDuration = (latest - earliest) + baseTime[0] = (8 - 3) + 5 = 10`
  - finish time of task 0 = `latest + ownDuration = 8 + 10 = 18`

## Constraints

- `1 <= n <= 10^5`
- `edges.length == n - 1`
- `edges[i] == [ui, vi]`
- `0 <= ui, vi <= n - 1`
- `ui != vi`
- The input is generated such that `edges` represents a valid tree.
- `baseTime.length == n`
- `1 <= baseTime[i] <= 10^5`

## Analysis of the Solution

```cpp
class Solution {
    long long dfs(vector<vector<int>> &graph, vector<int>& baseTime, int u){
        if(graph[u].size()==0) return baseTime[u];
        long long ear=LONG_MAX;
        long long latest=LONG_MIN;

        for(int i=0;i<graph[u].size();i++){
            long long tres=dfs(graph,baseTime,graph[u][i]);
            ear=min(tres,ear);
            latest=max(latest,tres);
        }
        long long own=(latest-ear)+baseTime[u];
        return own+latest;
    }
public:
    long long finishTime(int n, vector<vector<int>>& edges, vector<int>& baseTime) {
        vector<vector<int>> graph(n);
        for(int i=0;i<edges.size();i++){
            int u=edges[i][0];
            int v=edges[i][1];
            graph[u].push_back(v);
        }
        return dfs(graph,baseTime,0);
    }
};
```

**Logic walkthrough:**

1. **Graph construction**: Since `edges[i] = [ui, vi]` means `ui` is the parent of `vi`, building `graph[u].push_back(v)` directly gives a child adjacency list — no need to worry about direction or build an undirected graph and track parents/visited, since the tree is already rooted and directed correctly. This is correct and a nice simplification.

2. **DFS base case**: If `graph[u]` is empty, `u` is a leaf, so return `baseTime[u]`. ✅ Matches problem definition.

3. **Recursive case**: For each child, recursively compute its finish time `tres`, then track the min (`ear`) and max (`latest`) across all children. Then:
   - `own = (latest - ear) + baseTime[u]` → matches `ownDuration`
   - return `own + latest` → matches `latest + ownDuration`
   
   This exactly mirrors the problem's formula. ✅

4. **Correctness check against examples**:
   - Example 1 (chain 0→1→2, baseTime=[9,5,3]): leaf 2 → 3; node 1: ear=latest=3, own=5, return 3+5=8; node 0: ear=latest=8, own=9, return 8+9=17. ✅ Matches expected output.
   - Example 3 also checks out following the same logic. ✅

5. **Data types**: Using `long long` for accumulation is safe given constraints (`n` up to 1e5, `baseTime[i]` up to 1e5), though even `int` would likely suffice since values don't compound multiplicatively — but `long long` is a safe choice and avoids any overflow concerns.

6. **Complexity**: This is a standard tree DFS, visiting each node exactly once and processing each edge once → **O(n) time, O(n) space** (including recursion stack and graph storage). This is optimal for this problem.

7. **Potential issue — recursion depth**: For `n` up to `10^5`, if the tree is heavily skewed (e.g., a long chain, as in Example 1's pattern), the recursion depth could reach ~10^5. This **could cause a stack overflow** in some environments/judges, since each stack frame holds local variables (`ear`, `latest`, `own`, `tres`, loop index) — though LeetCode's C++ judge typically allows fairly deep recursion (often fine up to 10^5 depth, but it's environment-dependent and a known risk for "size n linear chain" tree problems). An iterative post-order traversal would be a safer alternative if you hit a stack overflow / TLE-by-crash on the judge.

8. **Minor style note**: The class declaration is missing a trailing semicolon (`};`) in your pasted code — but that's likely just a copy-paste artifact, not a logic issue.

## Verdict

The solution is **logically correct** and directly translates the problem's recursive definition into code, with correct tree construction (using directed parent→child edges, avoiding the need for a separate `visited` array). It runs in optimal O(n) time and space. The only real risk is recursion depth on skewed/chain-like trees at `n = 10^5`, which could cause a stack overflow on some judges — worth keeping in mind if you see a runtime error rather than a wrong-answer verdict.

## Someone else solution!!

Itartive DFS

```cpp
class Solution {
public:
    long long finishTime(int n, vector<vector<int>>& edges, vector<int>& baseTime) {
        vector<vector<int>>adj(n);
        for(int i=0;i<edges.size();i++){
            int u=edges[i][0],v=edges[i][1];
            adj[u].push_back(v);
        }
        vector<int>temp;
        stack<int>st;st.push(0);
        while(!st.empty()){
            int u=st.top();st.pop();
            temp.push_back(u);
            for(int v:adj[u])st.push(v);
        }
        vector<long long>ft(n,0);

        for(int idx=temp.size()-1;idx>=0;idx--){
            int u=temp[idx];
            if(adj[u].size()==0)ft[u]=baseTime[u];
            else{
                long long mini=LLONG_MAX,maxi=0;
                for(int v:adj[u]){
                    long long f=ft[v];
                    mini=min(mini,f);
                    maxi=max(maxi,f);
                }
                 long long own=(maxi-mini)+baseTime[u];
             ft[u]=own+maxi;
            }
        }
       return ft[0]; 
    }
};
```















