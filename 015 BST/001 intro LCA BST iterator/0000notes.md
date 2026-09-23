##  Binary Search Tree Fundamentals

### BST property

For every node:

```text
All values in the left subtree  < node.val
All values in the right subtree > node.val
```

This ordering allows search-related operations to discard one entire subtree at every step.

### Height terminology

The lecture uses height measured in edges:

```java
height(null) = -1
height(leaf) = 0
```

If height is measured in nodes instead, use `height(null) = 0`.

---

## Size and Height

The BST property does not make size or height calculation faster because every node may need to be visited.

```java
static int size(TreeNode root) {
    if (root == null) {
        return 0;
    }

    return size(root.left) + size(root.right) + 1;
}

static int height(TreeNode root) {
    if (root == null) {
        return -1;
    }

    return Math.max(
            height(root.left),
            height(root.right)) + 1;
}
```

### Complexity

- Time: `O(n)`
- Recursion space: `O(h)`

---

## Minimum and Maximum in a BST

The minimum is the leftmost value.  
The maximum is the rightmost value.

```java
static int minimum(TreeNode root) {
    if (root == null) {
        throw new IllegalArgumentException("Tree is empty");
    }

    TreeNode current = root;

    while (current.left != null) {
        current = current.left;
    }

    return current.val;
}

static int maximum(TreeNode root) {
    if (root == null) {
        throw new IllegalArgumentException("Tree is empty");
    }

    TreeNode current = root;

    while (current.right != null) {
        current = current.right;
    }

    return current.val;
}
```

### Complexity

- Time: `O(h)`
- Iterative auxiliary space: `O(1)`

---

## Find a Value in a BST

At each node:

- equal: value found;
- target is larger: go right;
- target is smaller: go left.

```java
static boolean find(TreeNode root, int target) {
    TreeNode current = root;

    while (current != null) {
        if (current.val == target) {
            return true;
        } else if (current.val < target) {
            current = current.right;
        } else {
            current = current.left;
        }
    }

    return false;
}
```

### Complexity

- Balanced BST: `O(log n)`
- Skewed BST: `O(n)`
- In general: `O(h)`

---

## Root-to-Node Path in a BST

Unlike a general binary tree, there is no need to explore both subtrees.

```java
static List<TreeNode> rootToNodePath(
        TreeNode root,
        int target) {

    List<TreeNode> path = new ArrayList<>();
    TreeNode current = root;

    while (current != null) {
        path.add(current);

        if (current.val == target) {
            return path;
        } else if (current.val < target) {
            current = current.right;
        } else {
            current = current.left;
        }
    }

    // Target is absent, so do not return a partial path.
    path.clear();
    return path;
}
```

### Complexity

- Time: `O(h)`
- Path space: `O(h)`

---

## Lowest Common Ancestor in a BST

### Key observation

At the current node:

- if both targets are smaller, the LCA lies on the left;
- if both targets are larger, the LCA lies on the right;
- otherwise, the paths split and the current node is the LCA.

### Iterative solution

```java
static TreeNode lowestCommonAncestorBST(
        TreeNode root,
        TreeNode p,
        TreeNode q) {

    TreeNode current = root;

    while (current != null) {
        if (current.val < p.val && current.val < q.val) {
            current = current.right;
        } else if (current.val > p.val
                && current.val > q.val) {
            current = current.left;
        } else {
            return current;
        }
    }

    return null;
}
```

### When node existence is not guaranteed

The split point is only a valid answer if both values actually exist in its subtree:

```java
static TreeNode lowestCommonAncestorBSTChecked(
        TreeNode root,
        TreeNode p,
        TreeNode q) {

    TreeNode lca = lowestCommonAncestorBST(root, p, q);

    if (lca == null
            || !find(lca, p.val)
            || !find(lca, q.val)) {
        return null;
    }

    return lca;
}
```

LeetCode's standard BST LCA problem normally guarantees that both nodes exist, so this validation is not required there.

### Complexity

- Time: `O(h)`
- Iterative auxiliary space: `O(1)`
- Balanced BST: `O(log n)`
- Skewed BST: `O(n)`

---

## Binary Tree LCA vs BST LCA

| Property | General Binary Tree | Binary Search Tree |
|---|---|---|
| Ordering available | No | Yes |
| Need to inspect both subtrees | Possibly | No |
| Typical time | `O(n)` | `O(h)` |
| Main idea | Find targets using traversal | Find their split point |

# Q BST Iterator

### Problem Statement
Implement the `BSTIterator` class that represents an iterator over the in-order traversal of a binary search tree (BST):

* `BSTIterator(TreeNode root)` Initializes an object of the `BSTIterator` class. The root of the BST is given as part of the constructor. The pointer should be initialized to a non-existent number smaller than any element in the BST.
* `boolean hasNext()` Returns `true` if there exists a number in the traversal to the right of the pointer, otherwise returns `false`.
* `int next()` Moves the pointer to the right, then returns the number at the pointer.

Notice that by initializing the pointer to a non-existent smallest number, the first call to the `next()` will return the smallest element in the BST.

Assume that the `next()` calls will always be valid. That is, there will be at least a next number in the in-order traversal when `next()` is called.

### Examples

**Example 1:**

```text
Input: ["BSTIterator", "next", "next", "hasNext", "next", "hasNext", "next", "hasNext", "next", "hasNext"], root = [7, 3, 15, null, null, 9, 20]
Output: [3, 7, true, 9, true, 15, true, 20, false]
Explanation:
BSTIterator bSTIterator = new BSTIterator([7, 3, 15, null, null, 9, 20]);
bSTIterator.next();    // return 3
bSTIterator.next();    // return 7
bSTIterator.hasNext(); // return True
bSTIterator.next();    // return 9
bSTIterator.hasNext(); // return True
bSTIterator.next();    // return 15
bSTIterator.hasNext(); // return True
bSTIterator.next();    // return 20
bSTIterator.hasNext(); // return False
```

**Example 2:**

```text
Input: ["BSTIterator", "next", "next", "next", "hasNext", "next", "hasNext"], root = [7, 3, 15, null, null, 9, 20]
Output: [3, 7, 9, true, 15, true]
Explanation:
BSTIterator bSTIterator = new BSTIterator([7, 3, 15, null, null, 9, 20]);
bSTIterator.next();    // return 3
bSTIterator.next();    // return 7
bSTIterator.next();    // return 9
bSTIterator.hasNext(); // return True
bSTIterator.next();    // return 15
bSTIterator.hasNext(); // return True
```

### Constraints
- $1 \leq \text{Number of Nodes} \leq 10^4$
- At most $10^4$ calls will be made to `next` and `hasNext`.
- $0 \leq \text{Node.val} \leq 10^5$

Brute--> get inorder and store in array and now u can move anywhere

Optimal 

While a previous approach used **O(N)** space complexity, it can be optimized to **O(H)** space complexity, where **H** is the height of the tree, by utilizing the properties of a Binary Search Tree (BST). This method creates an iterator that uses a stack to manage the traversal, resulting in efficient **O(1)** time complexity for the `next()` and `hasNext()` operations. By initially traversing to the leftmost node and maintaining a stack of nodes, the BST can be iterated over efficiently.

### Approach

**Constructor `BSTIterator(TreeNode root)`:**
* Use a **stack** (Last In First Out) within the constructor.
* Start from the root and traverse to the leftmost node, pushing each encountered node onto the stack.

**`next()` function:**
* Pop the top element from the stack.
* Move to the right subtree of the popped node and traverse down its left subtree, pushing encountered nodes onto the stack.
* Return the value of the popped node.

**`hasNext()` function:**
* Check if the stack is not empty.
* If the stack contains elements, return `true`, indicating there are more nodes to iterate over.
* If the stack is empty, return `false`, indicating there are no more nodes to iterate over.

```cpp
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int data;
 *     TreeNode *left;
 *     TreeNode *right;
 *      TreeNode(int val) : data(val) , left(nullptr) , right(nullptr) {}
 * };
 **/

class BSTIterator{
    stack<TreeNode * >stk;
	public:
		BSTIterator(TreeNode* root){
			TreeNode * curr=root;
            while(curr!=nullptr){
                stk.push(curr);
                curr=curr->left;
            }
		}
		
		bool hasNext(){
			if(!stk.empty()) return true;
            return false;
		}
		
		int next(){
            if(stk.empty()) return -1;
            TreeNode * node=stk.top();
            stk.pop();
            TreeNode * curr=node->right;
             while(curr!=nullptr){
                stk.push(curr);
                curr=curr->left;
            }
            return node->data;
		}
};

/**
 * Your BSTIterator object will be instantiated and called as such:
 * BSTIterator* obj = new BSTIterator(root);
 * int param_1 = obj->next();
 * bool param_2 = obj->hasNext();
 */
 ```

 ### Complexity Analysis

* **Time Complexity:** $O(1)$
    * `next()` and `hasNext()` occur in constant time on average. Although pushing elements onto the stack during traversal to the leftmost node and during subsequent traversals can take $O(H)$ in a single call, the amortized time complexity across all calls is $O(1)$ because every node is pushed and popped exactly once.
* **Space Complexity:** $O(H)$
    * Where $H$ is the height of the tree. This is because, in the worst case, the stack can contain all the nodes from the root to the leftmost leaf node.
