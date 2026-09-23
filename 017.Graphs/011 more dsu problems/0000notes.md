# Notes






![alt text](<010more dsu ques_240113_014521.jpg>)



![alt text](<010more dsu ques_240113_014521(1).jpg>) ![alt text](<010more dsu ques_240113_014521(2).jpg>) ![alt text](<010more dsu ques_240113_014521(3).jpg>) ![alt text](<010more dsu ques_240113_014521(4).jpg>) ![alt text](<010more dsu ques_240113_014521(5).jpg>) ![alt text](<010more dsu ques_240113_014521(6).jpg>) ![alt text](<010more dsu ques_240113_014521(7).jpg>) ![alt text](<010more dsu ques_240113_014521(8).jpg>) ![alt text](<010more dsu ques_240113_014521(9).jpg>) ![alt text](<010more dsu ques_240113_014521(10).jpg>) ![alt text](<010more dsu ques_240113_014521(11).jpg>) ![alt text](<010more dsu ques_240113_014521(12).jpg>) ![alt text](<010more dsu ques_240113_014521(13).jpg>) ![alt text](<010more dsu ques_240113_014521(14).jpg>) ![alt text](<010more dsu ques_240113_014521(15).jpg>) ![alt text](<010more dsu ques_240113_014521(16).jpg>) ![alt text](<010more dsu ques_240113_014521(17).jpg>) ![alt text](<010more dsu ques_240113_014521(18).jpg>) ![alt text](<010more dsu ques_240113_014521(19).jpg>) ![alt text](<010more dsu ques_240113_014521(20).jpg>) ![alt text](<010more dsu ques_240113_014521(21).jpg>) ![alt text](<010more dsu ques_240113_014521(22).jpg>) ![alt text](<010more dsu ques_240113_014521(23).jpg>) ![alt text](<010more dsu ques_240113_014521(24).jpg>) ![alt text](<010more dsu ques_240113_014521(25).jpg>) ![alt text](<010more dsu ques_240113_014521(26).jpg>) ![alt text](<010more dsu ques_240113_014521(27).jpg>)


# LC 947. Most Stones Removed with Same Row or Column

On a 2D plane, we place `n` stones at some integer coordinate points. Each coordinate point may have at most one stone.

A stone can be **removed** if it shares either **the same row** or **the same column** as another stone that has not been removed.

Given an array `stones` of length `n` where `stones[i] = [xi, yi]` represents the location of the `ith` stone, return the largest possible number of stones that can be removed.

### Example 1:

**Input:** `stones = [[0,0],[0,1],[1,0],[1,2],[2,1],[2,2]]`
**Output:** `5`
**Explanation:** One way to remove 5 stones is as follows:
1. Remove stone `[2,2]` because it shares the same row as `[2,1]`.
2. Remove stone `[2,1]` because it shares the same column as `[0,1]`.
3. Remove stone `[0,1]` because it shares the same row as `[0,0]`.
4. Remove stone `[1,2]` because it shares the same row as `[1,0]`.
5. Remove stone `[1,0]` because it shares the same column as `[0,0]`.
Stone `[0,0]` cannot be removed since it does not share a row/column with another stone still on the plane.

### Example 2:

**Input:** `stones = [[0,0],[0,2],[1,1],[2,0],[2,2]]`
**Output:** `3`
**Explanation:** One way to make 3 moves is as follows:
1. Remove stone `[2,2]` because it shares the same row as `[2,0]`.
2. Remove stone `[2,0]` because it shares the same column as `[0,0]`.
3. Remove stone `[0,2]` because it shares the same row as `[0,0]`.
Stones `[0,0]` and `[1,1]` cannot be removed since they do not share a row/column with another stone still on the plane.

### Example 3:

**Input:** `stones = [[0,0]]`
**Output:** `0`
**Explanation:** `[0,0]` is the only stone on the plane, so you cannot remove it.

### Constraints:

* `1 <= stones.length <= 1000`
* `0 <= xi, yi <= 10^4`
* No two stones are at the same coordinate point.

### My wrong approach 

```cpp
class Solution {
public:
    int maxRemove(vector<vector<int>>& stones, int n) {
        sort(stones.begin(),stones.end());
      unordered_map<int,int>xcor;
      unordered_map<int,int>ycor;
        for(auto cor:stones){
            xcor[cor[0]]++;
            ycor[cor[1]]++;
        }

        int ans=0;
        for(auto cor:stones){
            if(xcor[cor[0]]>1 ||ycor[cor[1]]>1){
                ans++;
                xcor[cor[0]]--;
                ycor[cor[1]]--;
            }
        }
        return ans;

    }
};
```

Welcome to **LeetCode 947: Most Stones Removed with Same Row or Column**. 



Your logic here is a classic "Greedy" approach. You are trying to count the frequencies and peel off the stones one by one if they share a row or column. But this approach holds a fatal flaw. 

Here is the "Senior Engineer" breakdown of why your code fails, and the paradigm shift required to solve it.

### The Flaw: The "Bridge" Trap
Your code assumes that the *order* in which you remove the stones doesn't matter, as long as the frequency is > 1. Let's dry run a simple example to see why this crashes.

**Imagine 3 stones:** `[[0,0], [0,1], [1,0]]`
They form an "L" shape. `[0,0]` is the cornerstone. 
The optimal move is to remove `[0,1]` and `[1,0]`, leaving `[0,0]` as the sole survivor. **Max removals = 2.**

Let's run your code on this:
1. **Initial Counts:** `x0=2, x1=1` | `y0=2, y1=1`
2. **Look at `[0,0]`:** `xcor[0]` is 2. The `if` condition is met! You remove `[0,0]`. 
   * `ans` becomes 1. 
   * `x0` drops to 1, `y0` drops to 1.
3. **Look at `[0,1]`:** `xcor[0]` is now 1. `ycor[1]` is 1. The `if` condition **fails**. It survives.
4. **Look at `[1,0]`:** `xcor[1]` is 1. `ycor[0]` is now 1. The `if` condition **fails**. It survives.

**Your output:** `1`. 
**Correct output:** `2`. 

**Why it failed:** By greedily removing the cornerstone `[0,0]` first, you destroyed the "bridge" that connected the other two stones. You stranded them in the ocean.

---

### The Paradigm Shift: Welcome to Graph Theory
To solve this, you must stop looking at these as individual coordinates in an array, and start looking at them as **Nodes in a Network**.

If a stone shares a row or a column with another stone, draw an invisible line (an **Edge**) between them. 
If you have a cluster of 5 stones all connected to each other by these invisible lines, they form a **Connected Component**. 

Here is the beautiful mathematical reality of this problem:
If you have a connected component of 5 stones, you can *always* carefully remove them one by one until exactly **1** stone is left. (You just have to avoid removing the bridges until the end).

Therefore, you don't need to simulate the removals at all! You just need this magic formula:
**`Max Removed Stones = (Total Number of Stones) - (Number of Connected Components)`**

If you have 6 stones, and they form 2 separate connected islands, you can reduce each island to 1 stone. 
Max Removed = `6 - 2 = 4`.

### The Weapons of Choice
To count "Connected Components" in a network, Senior Engineers reach for one of two Graph Theory tools:
1. **DFS / BFS:** Traverse the matrix and color the connected islands.
2. **Union-Find (Disjoint Set):** The absolute most optimized, elegant data structure specifically designed to group connected items together mathematically.


# The Union-Find (Disjoint Set) Architecture

To solve this problem perfectly, we need to stop thinking about individual coordinates and start thinking about **Network Components**. 

If two stones share a row or a column, they are connected. A group of connected stones forms an "Island" (or a Connected Component). The mathematical rule of this game is: **You can reduce every Island down to exactly 1 stone.**

Therefore, the formula to find the maximum number of removed stones is:
`Max Removed = (Total Stones) - (Number of Islands)`

To efficiently count these Islands, we use the **Union-Find** (Disjoint Set) data structure.

---

## The Two Mechanics of Union-Find

Union-Find is like a corporate management system. Every node starts as its own boss. When two nodes connect, one becomes the boss of the other. 

### 1. The `find(x)` Function
This function answers the question: *"Who is the absolute top-level boss of node X?"*
If node A reports to node B, and node B reports to node C, `find(A)` will return `C`.
* **The Optimization (Path Compression):** When `find(A)` discovers that `C` is the top boss, it instantly updates A to report directly to C. It flattens the hierarchy, making all future searches run in practically $O(1)$ time.

### 2. The `union(x, y)` Function
This function takes two nodes and connects their islands. 
It finds the top boss of `x` and the top boss of `y`. If they have different bosses, it means they are currently on separate islands. We link them by making one boss report to the other. When this happens, **the total number of islands decreases by 1.**

---

## The "Matrix to Graph" Trick (The 10001 Offset)

How do we union a Row and a Column? 
If a stone is at `[2, 2]`, we want to `union(Row 2, Column 2)`. But how does our algorithm know the difference between the integer `2` (the row) and the integer `2` (the column)? 

**The Shift:** The problem constraints say coordinates go up to `10^4` (10,000). We can safely distinguish columns from rows by simply adding `10001` to every column index. 
* Row 2 remains `2`.
* Column 2 becomes `10003`. 

Now, when we process stone `[2, 2]`, we simply call `union(2, 10003)`. 

---

## The C++ Implementation

Here is the highly optimized, FAANG-level $O(N)$ implementation.

```cpp
#include <vector>
#include <unordered_map>

using namespace std;

class Solution {
private:
    unordered_map<int, int> parent;
    int islands = 0;

    // Returns the ultimate root (boss) of x
    int find(int x) {
        // If we have never seen this row/col before, it becomes its own boss
        // and we have discovered a new isolated island.
        if (parent.find(x) == parent.end()) {
            parent[x] = x;
            islands++;
        }
        
        // Path Compression: Point directly to the top-level boss
        if (parent[x] != x) {
            parent[x] = find(parent[x]); 
        }
        
        return parent[x];
    }

    // Connects two nodes. If they merge, total islands decrease.
    void unite(int x, int y) {
        int rootX = find(x);
        int rootY = find(y);
        
        if (rootX != rootY) {
            parent[rootX] = rootY; // Make rootY the boss of rootX
            islands--;             // Two islands merged into one
        }
    }

public:
    int removeStones(vector<vector<int>>& stones) {
        for (auto& stone : stones) {
            int row = stone[0];
            int col = stone[1] + 10001; // Offset to prevent row/col collisions
            
            unite(row, col);
        }
        
        // Max removed is total stones minus the surviving single stones per island
        return stones.size() - islands;
    }
};
```



Q--> here we havent used union by rank or by size??

You have a phenomenal eye for detail. You caught the exact shortcut I took. 

You are 100% correct. In my `unite` function, I just blindly attached `rootX` to `rootY` (`parent[rootX] = rootY;`). I didn't check which island was bigger or deeper. 

Here is the "Senior Engineer" candid truth about why I omitted it, followed by the mathematically perfect code that includes it.

### The "Why": Path Compression is the Heavy Lifter
In a Disjoint Set, there are two optimizations:
1. **Path Compression (in `find`):** Flattens the tree during the search.
2. **Union by Size/Rank (in `union`):** Keeps the tree balanced during the merge.

In competitive programming and technical interviews, if you implement **Path Compression**, the tree flattens so aggressively that the time complexity drops to a near-constant $O(1)$. 

Because `N` in this LeetCode problem is only $1000$, adding Union by Size won't change the execution time by even a single millisecond. I left it out to keep the code footprint as small and readable as possible.

### The Architect's Upgrade: Union by Size
However, if you are building an enterprise system where $N = 1,000,000$, or if a FAANG interviewer explicitly asks for the *mathematically optimal* Disjoint Set, you **must** use Union by Size or Rank. 

Without it, an attacker could theoretically feed your system a worst-case dataset that forces your trees to become long linked lists *before* path compression has a chance to kick in.

Here is the exact same C++ implementation, upgraded with **Union by Size**. 

```cpp
#include <vector>
#include <unordered_map>

using namespace std;

class Solution {
private:
    unordered_map<int, int> parent;
    unordered_map<int, int> size; // NEW: Tracks the size of each island
    int islands = 0;

    int find(int x) {
        if (parent.find(x) == parent.end()) {
            parent[x] = x;
            size[x] = 1; // NEW: A newly discovered island has a size of 1
            islands++;
        }
        
        // Path Compression
        if (parent[x] != x) {
            parent[x] = find(parent[x]); 
        }
        
        return parent[x];
    }

    void unite(int x, int y) {
        int rootX = find(x);
        int rootY = find(y);
        
        if (rootX != rootY) {
            // UNION BY SIZE: Always attach the smaller island to the larger one
            if (size[rootX] < size[rootY]) {
                parent[rootX] = rootY;         // X reports to Y
                size[rootY] += size[rootX];    // Y's island grows by the size of X
            } else {
                parent[rootY] = rootX;         // Y reports to X
                size[rootX] += size[rootY];    // X's island grows by the size of Y
            }
            islands--; // Two islands merged into one
        }
    }

public:
    int removeStones(vector<vector<int>>& stones) {
        for (auto& stone : stones) {
            int row = stone[0];
            int col = stone[1] + 10001; 
            
            unite(row, col);
        }
        
        return stones.size() - islands;
    }
};
```

### Why "Size" instead of "Rank"?
You can use either, but Senior Engineers usually prefer `Size` over `Rank` (height). 
Why? Because `Rank` gets completely distorted the second Path Compression runs (the height shrinks, but rank usually isn't updated to reflect it because it's computationally expensive). `Size`, on the other hand, is a concrete, tangible metric (the exact number of nodes in the component) that is extremely useful to have on hand for other complex Graph problems.


## Analyzing complexities


. Understanding *why* we add an optimization is just as important as knowing how to write it. 

When analyzing Union-Find, we measure the complexity of performing a single `find` or `union` operation. Here is the exact breakdown of the Time Complexity (TC) and Space Complexity (SC) before and after adding **Union by Size**, assuming we are already using **Path Compression**.

---

### Space Complexity (SC): The Trade-off
The Space Complexity is the easiest to measure because it represents the memory we allocate.

* **Before (Path Compression Only): $O(N)$**
    We only allocate memory for the `parent` map, which stores at most $2N$ keys (one for each unique row and column).
* **After (Path Compression + Union by Size): $O(N)$**
    We now allocate memory for the `parent` map *and* the `size` map. While we technically doubled our memory footprint ($2 \times O(N)$), in Big-O notation, we drop the constant. It remains **$O(N)$**.

**The Verdict:** You trade a tiny, constant amount of extra memory (the `size` array) to safeguard your system against catastrophic Time Complexity failures.

---

### Time Complexity (TC): The "Linked List" Trap
This is where the magic happens. To understand the difference, you have to understand the worst-case scenario: a malicious user feeding your algorithm data specifically designed to break it.

#### 1. Before (Path Compression Only)
* **Amortized Time:** $O(\log N)$
* **Worst-Case Single Operation:** $O(N)$

**Why?** Imagine I feed your program a perfectly sequential list of unions: `unite(1,2)`, `unite(2,3)`, `unite(3,4)`, `unite(4,5)`. 
Because you aren't checking sizes, 2 becomes the boss of 1. Then 3 becomes the boss of 2. Then 4 becomes the boss of 3. 
You have accidentally created a **Linked List**! 
If I now call `find(1)`, your code has to traverse all the way up the chain one by one. The height of the tree is $N$, so that single `find` operation takes **$O(N)$** time. *(Path compression will instantly flatten it after this first search, but that first search is still incredibly slow).*

#### 2. After (Path Compression + Union by Size)
* **Amortized Time:** $O(\alpha(N))$ 
* **Worst-Case Single Operation:** $O(\log N)$

**Why?** Union by Size makes the "Linked List" trap mathematically impossible. By forcing the smaller tree to always attach to the root of the larger tree, the trees stay incredibly wide and shallow. 
Even if Path Compression completely fails or hasn't run yet, the absolute maximum height the tree can ever reach is $\log_2(N)$. So the worst-case single search is capped at **$O(\log N)$**.

However, when you combine Union by Size with Path Compression, they work together to create a mathematical anomaly: the **Inverse Ackermann function, $\alpha(N)$**. 

The Ackermann function grows so fast that the *Inverse* Ackermann function grows so incredibly slowly that for any number $N$ smaller than the number of atoms in the observable universe, $\alpha(N)$ is less than or equal to $5$. 

Therefore, $O(\alpha(N))$ is practically identical to **$O(1)$ Constant Time**.

---

### The Senior Engineer Summary
* **Without Union by Size:** Your graph is vulnerable to becoming a Linked List. An attacker can force your operations to take $O(N)$ time.
* **With Union by Size:** Your graph is perfectly balanced. Your operations run in $O(\alpha(N))$ time, which is effectively instantaneous ($O(1)$), no matter how much data you feed it.





























