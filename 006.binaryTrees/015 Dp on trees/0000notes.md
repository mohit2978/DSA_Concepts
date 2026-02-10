# Notes

### Dynamic Programming (DP) on Trees

Dynamic Programming (DP) on Trees is a technique to solve problems where the answer for a node depends on the answers of its children. 

Think of it as **"DFS with return values."** Instead of just traversing the tree, every node asks its children for specific data, combines that data to calculate its own result, and then returns its result up to its parent.

---

### The Core Logic (Bottom-Up)
Since a parent node needs data from its children to make a decision, Tree DP almost always uses **Post-Order Traversal** (Left $\to$ Right $\to$ Root).

1.  **Base Case:** Leaf nodes calculate their value (trivial case) and return it.
2.  **Recursive Step:** An internal node collects values from all its children.
3.  **Transition:** The node applies logic (e.g., max, sum, if/else) to combine the children's values with its own value.

---

### Common Patterns

#### 1. The "Select or Ignore" Pattern (Vertex Cover / House Robber)
For every node `u`, you have two choices:
* **Choice 1: Include `u`** in the result. (Constraint: Usually means you cannot include `u`'s children).
* **Choice 2: Exclude `u`.** (Constraint: You are free to include or exclude children).

> **Example:** House Robber III (Max money, cannot rob parent and child).
> **State returned by node:** `pair<int, int> {withRoot, withoutRoot}`
> * `withRoot = node.val + sum(child.withoutRoot)`
> * `withoutRoot = sum(max(child.withRoot, child.withoutRoot))`

#### 2. The "Path" Pattern (Diameter / Max Path Sum)
For every node `u`, you calculate the best path passing through it.
* **Result at Node:** `left_path + right_path + node.val` (This updates a global maximum).
* **Return to Parent:** `max(left_path, right_path) + node.val` (You can only extend one branch up to the parent).

---

### Example Code: House Robber III (Select/Ignore)
Here is a clean template for the "Select or Ignore" pattern.

```cpp
struct Result {
    int includeNode;
    int excludeNode;
};

Result solve(TreeNode* root) {
    if (!root) return {0, 0};

    // Post-order traversal
    Result left = solve(root->left);
    Result right = solve(root->right);

    // If we include this node, we MUST exclude its children
    int include = root->val + left.excludeNode + right.excludeNode;

    // If we exclude this node, we can take the max of including or excluding children
    int exclude = max(left.includeNode, left.excludeNode) + 
                  max(right.includeNode, right.excludeNode);

    return {include, exclude};
}
```
### Why Tree DP is Distinct from Standard DP

* **No Explicit DP Table:** Unlike standard DP on arrays or grids (where you use `dp[i]` or `dp[i][j]`), we rarely store the state in a separate table or hash map. Because we visit each node exactly once in a bottom-up fashion, the **"DP table"** is essentially the values returned through the recursion call stack.
* **Time Complexity:** $O(N)$ — Every node and edge is processed exactly once.
* **Space Complexity:** $O(H)$ — This represents the height of the tree ($H$) for the recursion stack. In a balanced tree, this is $O(\log N)$, and in a skewed tree, it is $O(N)$.

---

### Summary for Interviews

If you encounter a tree problem asking for **"Maximum Sum," "Longest Path,"** or **"Minimum Cost"** subject to constraints (such as "no two adjacent nodes"), it is almost certainly **DP on Trees**.

To solve it, your primary job is to figure out:
> **"What specific values does the parent need to receive from its children to make its own decision?"**

---