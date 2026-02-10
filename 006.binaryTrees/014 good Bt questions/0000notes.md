# Q1 LC129. Sum Root to Leaf Numbers

### **Problem Link**
[Sum Root to Leaf Numbers - LeetCode](https://leetcode.com/problems/sum-root-to-leaf-numbers/description/)

---

### **Problem Statement**
You are given the `root` of a binary tree containing digits from `0` to `9` only.

Each root-to-leaf path in the tree represents a number.
- For example, the root-to-leaf path `1 -> 2 -> 3` represents the number `123`.

Return the **total sum of all root-to-leaf numbers**. Test cases are generated so that the answer will fit in a **32-bit** integer.

A **leaf** node is a node with no children.

---

### **Example 1**
**Input:** `root = [1, 2, 3]`  
**Output:** `25`  
**Explanation:** The root-to-leaf path `1->2` represents the number `12`.  
The root-to-leaf path `1->3` represents the number `13`.  
Therefore, sum = `12 + 13 = 25`.

### **Example 2**
**Input:** `root = [4, 9, 0, 5, 1]`  
**Output:** `1026`  
**Explanation:** The root-to-leaf path `4->9->5` represents the number `495`.  
The root-to-leaf path `4->9->1` represents the number `491`.  
The root-to-leaf path `4->0` represents the number `40`.  
Therefore, sum = `495 + 491 + 40 = 1026`.

---

### **Constraints**
- The number of nodes in the tree is in the range `[1, 1000]`.
- `0 <= Node.val <= 9`
- The depth of the tree will not exceed `10`.

---

```java
/**
 * Definition for a binary tree node.
 * public class TreeNode {
 *     int val;
 *     TreeNode left;
 *     TreeNode right;
 *     TreeNode() {}
 *     TreeNode(int val) { this.val = val; }
 *     TreeNode(int val, TreeNode left, TreeNode right) {
 *         this.val = val;
 *         this.left = left;
 *         this.right = right;
 *     }
 * }
 */
class Solution {
    int sum=0;
    private void helper(TreeNode node,int num,TreeNode par,TreeNode root){

        if(node.left==null && node.right==null){
            num=num*10+node.val;
            sum+=num;
            return;
        }
        
       
        num=num*10+node.val;
        if(node.left!=null )helper(node.left,num,node,root);
        if(node.right!=null )helper(node.right,num,node,root);
    }
    public int sumNumbers(TreeNode root) {
        helper(root,0,null,root);
        return sum;
    }
}
```
TC-->O(n)

# Q2 662. Maximum Width of Binary Tree

### **Problem Link**
[Maximum Width of Binary Tree - LeetCode](https://leetcode.com/problems/maximum-width-of-binary-tree/description/)

---

### **Problem Statement**
Given the `root` of a binary tree, return the **maximum width** of the given tree.

The **maximum width** of a tree is the maximum **width** among all levels.

The **width** of one level is defined as the length between the end-nodes (the leftmost and rightmost non-null nodes), where the null nodes between the end-nodes that would be present in a complete binary tree extending down to that level are also counted into the length calculation.

It is guaranteed that the answer will in the range of a **32-bit** signed integer.

---

### **Example 1**
**Input:** `root = [1, 3, 2, 5, 3, null, 9]`  
**Output:** `4`  
**Explanation:** The maximum width exists in the third level with length 4 (`5, 3, null, 9`).

### **Example 2**
**Input:** `root = [1, 3, 2, 5, null, null, 9, 6, null, 7]`  
**Output:** `7`  
**Explanation:** The maximum width exists in the fourth level with length 7 (`6, null, null, null, null, null, 7`).

### **Example 3**
**Input:** `root = [1, 3, 2, 5]`  
**Output:** `2`  
**Explanation:** The maximum width exists in the second level with length 2 (`3, 2`).

---

### **Constraints**
- The number of nodes in the tree is in the range `[1, 3000]`.
- `-100 <= Node.val <= 100`


```java
/**
 * Definition for a binary tree node.
 * public class TreeNode {
 *     int val;
 *     TreeNode left;
 *     TreeNode right;
 *     TreeNode() {}
 *     TreeNode(int val) { this.val = val; }
 *     TreeNode(int val, TreeNode left, TreeNode right) {
 *         this.val = val;
 *         this.left = left;
 *         this.right = right;
 *     }
 * }
 */
class Solution {
    class Pair{
        long min;
        long max;
        Pair(long min,long max){
            this.min=min;
            this.max=max;
        }
    }
    private void helper(TreeNode node ,int dep,long idx,Map<Integer,Pair>mp){
        if(node==null) return;
        helper(node.left,dep+1,2*idx,mp);
        helper(node.right,dep+1,2*idx+1,mp);
        if(mp.containsKey(dep)){
            Pair p=mp.get(dep);
            p.max=Math.max(idx,p.max);
        }else{
            mp.put(dep,new Pair(idx,idx));
        }
        Pair p=mp.get(dep);
        maxWidth=Math.max(maxWidth,p.max-p.min+1);
    }
    long maxWidth;
    public int widthOfBinaryTree(TreeNode root) {
        maxWidth=0;
        Map<Integer,Pair>mp=new HashMap<>();
        helper(root,1,1,mp);
        return (int)maxWidth;
    }
}
```
segment tree vala conecpt use kia hai assume kr do perfect BT hai 

```java

/**
 * Definition for a binary tree node.
 * public class TreeNode {
 *     int val;
 *     TreeNode left;
 *     TreeNode right;
 *     TreeNode() {}
 *     TreeNode(int val) { this.val = val; }
 *     TreeNode(int val, TreeNode left, TreeNode right) {
 *         this.val = val;
 *         this.left = left;
 *         this.right = right;
 *     }
 * }
 */
class Solution {
    class Pair{
        long min;
        long max;
        Pair(long min,long max){
            this.min=min;
            this.max=max;
        }
    }
    private void helper(TreeNode node ,int dep,long idx,Map<Integer,Pair>mp){
        if(node==null) return;
        helper(node.left,dep+1,2*idx+1,mp);
        helper(node.right,dep+1,2*idx+2,mp);
        if(mp.containsKey(dep)){
            Pair p=mp.get(dep);
            p.max=Math.max(idx,p.max);
        }else{
            mp.put(dep,new Pair(idx,idx));
        }
        Pair p=mp.get(dep);
        maxWidth=Math.max(maxWidth,p.max-p.min+1);
    }
    long maxWidth;
    public int widthOfBinaryTree(TreeNode root) {
        maxWidth=0;
        Map<Integer,Pair>mp=new HashMap<>();
        helper(root,1,1,mp);
        return (int)maxWidth;
    }
}
```
# Q Longest even sum path 

![alt text](image.png)


### Longest Path with Even Sum (Tree DP)

This is a classic **Tree Dynamic Programming (DP)** problem. The goal is to find the longest path (number of nodes) such that the sum of all node values in that path is even.

---

### The Logic
Since a path in a tree can "curve" through a node (going from the left child, up to the node, and down to the right child), we need to check every node to see if it can serve as the **"highest point" (anchor)** of the longest path.

For every node, we need to know two specific values from its children to make a decision:
1.  **`max_even_len`**: The longest path extending down into the subtree that has an **EVEN** sum.
2.  **`max_odd_len`**: The longest path extending down into the subtree that has an **ODD** sum.

We denote the return state of our recursive DFS call as a pair: `{max_even_len, max_odd_len}`.

---

### Transition Rules (Based on `node.val`)

How the current node affects the paths coming up from its children:

* **If `node.val` is EVEN:**
    * `Even + Even = Even`: Adding this node to an existing **Even** path keeps it **Even**.
    * `Even + Odd = Odd`: Adding this node to an existing **Odd** path keeps it **Odd**.
* **If `node.val` is ODD:**
    * `Odd + Even = Odd`: Adding this node to an existing **Even** path makes it **Odd**.
    * `Odd + Odd = Even`: Adding this node to an existing **Odd** path makes it **Even**.

---

### Combining Paths (The "Anchor" Step)
At each node, we try to connect a path coming from the left child and a path coming from the right child to form a larger path passing through the current node. We only update the global maximum if the total sum of the combined path is **Even**.

**Possible "Even" combinations at the anchor node:**
1.  `Left_Even + Right_Even + Current_Node` (if `node.val` is even)
2.  `Left_Odd + Right_Odd + Current_Node` (if `node.val` is even)
3.  `Left_Even + Right_Odd + Current_Node` (if `node.val` is odd)
4.  ...and so on for all permutations that result in an even total.

---

```cpp
class Solution {
    int ans;
    pair<int, int> dfs(TreeNode* root) {
        if (!root) return {0, -1e9};

        pair<int, int> left = dfs(root->left);
        pair<int, int> right = dfs(root->right);

        int le = left.first;
        int lo = left.second;
        int re = right.first;
        int ro = right.second;
        
        int me = -1e9, mo = -1e9;

        if (root->val % 2 == 0) {
            me = max(le, re) + 1;
            mo = max(lo, ro) + 1;

            if (le >= 0 && re >= 0) ans = max(ans, le + re + 1);
            if (lo >= 0 && ro >= 0) ans = max(ans, lo + ro + 1);
        } else {
            me = max(lo, ro) + 1;
            mo = max(le, re) + 1;

            if (le >= 0 && ro >= 0) ans = max(ans, le + ro + 1);
            if (lo >= 0 && re >= 0) ans = max(ans, lo + re + 1);
        }

        return {me, mo};
    }

public:
    int solve(TreeNode* root) {
        ans = 0;
        dfs(root);
        return ans;
    }
};
```
With comments

```cpp
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 * int val;
 * TreeNode *left;
 * TreeNode *right;
 * TreeNode() : val(0), left(nullptr), right(nullptr) {}
 * TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 * TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
    int maxPath = 0;
    const int INF = 1e9;

    // Returns a pair: {length of longest EVEN sum path, length of longest ODD sum path}
    // These paths must start at the current node and go downwards.
    pair<int, int> dfs(TreeNode* root) {
        if (!root) {
            // Base case: Null node.
            // Even sum path length is 0 (sum 0 is even).
            // Odd sum path is impossible (-INF).
            return {0, -INF};
        }

        pair<int, int> left = dfs(root->left);
        pair<int, int> right = dfs(root->right);

        int le = left.first;  // Left Even
        int lo = left.second; // Left Odd
        int re = right.first; // Right Even
        int ro = right.second;// Right Odd

        int myEven = -INF, myOdd = -INF;

        // --- Logic if Current Node is Even ---
        if (root->val % 2 == 0) {
            // Extend downward paths: Even+Even=Even, Odd+Even=Odd
            myEven = max(le, re) + 1;
            myOdd = max(lo, ro) + 1;

            // Anchor logic: Form a path L -> Node -> R
            // We need Total Sum to be Even.
            // Options: Even + Even + Even OR Odd + Even + Odd
            maxPath = max(maxPath, le + 1 + re);
            maxPath = max(maxPath, lo + 1 + ro);
        } 
        // --- Logic if Current Node is Odd ---
        else {
            // Extend downward paths: Odd+Odd=Even, Even+Odd=Odd
            // Note: Adding odd node flips the parity of the child's path
            myEven = max(lo, ro) + 1;
            myOdd = max(le, re) + 1;

            // Anchor logic: Form a path L -> Node -> R
            // We need Total Sum to be Even.
            // Options: Even + Odd + Odd OR Odd + Odd + Even
            maxPath = max(maxPath, le + 1 + ro);
            maxPath = max(maxPath, lo + 1 + re);
        }

        return {myEven, myOdd};
    }

public:
    int solve(TreeNode* root) {
        maxPath = 0;
        dfs(root);
        return maxPath;
    }
};
```

### Complexity Analysis
* **Time Complexity:** $O(N)$, where $N$ is the number of nodes. We visit each node once and perform constant-time math at each step.
* **Space Complexity:** $O(H)$, where $H$ is the height of the tree, due to the recursion stack.

### If conditions

### Parity Logic: Combining Odd Paths through an Even Node

This specific check happens when the current node's value is **EVEN**. The line `if (lo >= 0 && ro >= 0)` checks if we can form a valid path by connecting an **Odd Sum Path** from the left and an **Odd Sum Path** from the right.

---

### 1. The Math (Parity Logic)
We want the total path sum to be **Even**. Since the current node (root) is **Even**, we look at the paths coming from the subtrees:

$$\text{Total Sum} = \text{LeftSum} + \text{RootVal} + \text{RightSum}$$

If we choose **Odd** paths from both sides:
$$\text{Odd} + \text{Even} + \text{Odd} = \mathbf{Even}$$

Because $\text{Odd} + \text{Odd} = \text{Even}$, and $\text{Even} + \text{Even} = \text{Even}$, connecting two Odd paths via an Even node creates a perfectly valid **Even path**.

---

### 2. Why check `lo >= 0` and `ro >= 0`?
In implementation, we typically initialize variables like `lo` (left-odd) and `ro` (right-odd) to a very small negative number (e.g., `-1e9`) to represent an **"Impossible"** state (i.e., no such path exists).

* **The Problem:** If `lo` is negative, the left child does not have any path with an Odd sum. 
* **The Risk:** If we didn't check `lo >= 0`, we might accidentally calculate `-1e9 + -1e9 + 1`. This would result in a massive negative number, or if we mistakenly used `0` for impossible, we would be counting paths that don't actually exist.

---

### Summary
* **Context:** `root->val` is **Even**.
* **Goal:** Find a path passing *through* the root with an **Even** total sum.
* **Logic:** This line attempts to stitch together:
    > **Left Odd Path** $\longleftrightarrow$ **Even Root** $\longleftrightarrow$ **Right Odd Path**
* **Result:** The two "Odds" cancel each other out to make the total sum **Even**.

---

**Would you like me to show you the complementary logic for when the root's value is ODD?**

---
### Why this is Classed as DP on Trees

It is called **DP on Trees** because it follows the exact same mathematical structure as standard Dynamic Programming, just on a different data structure (a tree instead of an array).

Here is the breakdown of why this specific logic classifies as DP:

---

### 1. It Uses "States" ($DP[i]$)
In standard DP (like Climbing Stairs), you define a state `dp[i] = "Ways to reach step i"`. In this problem, we implicitly define a state for every node $u$:
* **`dp[u].even`**: Length of the longest path starting at $u$ and going down with an **even** sum.
* **`dp[u].odd`**: Length of the longest path starting at $u$ and going down with an **odd** sum.

This pair `{even, odd}` is the **DP State** for that node.

---

### 2. It Has a "Recurrence Relation" (Transition)
Just like $dp[i] = dp[i-1] + dp[i-2]$, the answer for the current node depends entirely on the optimal answers of its children.

**If the current node value is Even:**
* $dp[node].even = \max(dp[left].even, dp[right].even) + 1$
* $dp[node].odd = \max(dp[left].odd, dp[right].odd) + 1$

**If the current node value is Odd:**
* $dp[node].even = \max(dp[left].odd, dp[right].odd) + 1$
* $dp[node].odd = \max(dp[left].even, dp[right].even) + 1$

This formula allows us to build the solution **Bottom-Up** (from leaves to root), which is the core definition of DP.

---

### 3. Optimal Substructure
To solve the problem for the root, you don't need to know the exact details of every path in the subtrees. You only need the **summary** (the optimal lengths) from the left and right children. The optimal solution for the whole tree is built directly from the optimal solutions of its sub-parts (subtrees).

---

### Why People Get Confused
We usually associate DP with a `dp[][]` table or array. In Tree DP, the **Recursion Stack** acts as the DP table:
1.  When `dfs(left)` returns, that value is temporarily stored in memory.
2.  We use it immediately to compute the `root`'s value.
3.  Once the `root` returns, the `left` value is discarded because it has been "absorbed" into the parent's state.

Even though we don't explicitly write `vector<int> dp`, the logic is **pure Dynamic Programming**.

---
