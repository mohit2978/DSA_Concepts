# Check if a tree is a BST or not

### **Problem Link**
[Check if a tree is a BST or not - TUF+](https://takeuforward.org/plus/dsa/problems/check-if-a-tree-is-a-bst-or-not)

---

### **Problem Statement**
Given the root node of a binary tree, return `true` if the given binary tree is a **binary search tree (BST)**, otherwise return `false`.

A valid BST is defined as follows:
- The **left subtree** of a node contains only nodes with keys **strictly less than** the node's key.
- The **right subtree** of a node contains only nodes with keys **strictly greater than** the node's key.
- Both the left and right subtrees must also be binary search trees.

---

### **Example 1**
**Input:** `root = [5, 3, 6, 2, 4, null, 7]`  
**Output:** `true`  
**Explanation:** For every node, all nodes in the left subtree are smaller and all nodes in the right subtree are larger.

### **Example 2**
**Input:** `root = [5, 3, 6, 4, 2, null, 7]`  
**Output:** `false`  
**Explanation:** The root node's value is 5. In its left subtree, there is a node with value 4 (correct), but there is also a structure where the BST rule is violated deeper (e.g., if a node in the left subtree is larger than the root). Specifically, in this example, the placement of 4 and 2 violates the property.

---

### **Constraints**
- The number of nodes in the tree is in the range `[1, 10^4]`.
- `-2^31 <= Node.val <= 2^31 - 1`

---

## Wrong code

```cpp

class Solution {
   public:
    bool isBST(TreeNode* root) {
        if (root == nullptr) return true;
        if (root->left != nullptr && root->data <= root->left->data) return false;
		if (root->right != nullptr && root->data >= root->right->data) return false;
		return isBST(root->left) & isBST(root->right);
		 }
};
```

```text
      5
     / \
    1   8
       / \
      3   9

 ```     
The Problem:Look at node 3. It is in the Right Subtree of 5.

BST Rule: Everything in the right subtree of 5 must be $> 5$.Reality: $3 < 5$.Verdict: This is NOT a BST. Your code misses this because it never compares 3 against 5.

### **Intuition (Recursive Range Approach)**
A common mistake is to only check if a node is greater than its left child and smaller than its right child. This is **insufficient** because a node in the left subtree could still be larger than the original root.

To solve this, we must ensure every node stays within a valid **Range [min, max]**:
1. Initially, the root can be any value: `(-infinity, +infinity)`.
2. When moving to the **left child**, the maximum allowed value becomes the current node's value (since all nodes in the left must be smaller than the parent).
3. When moving to the **right child**, the minimum allowed value becomes the current node's value (since all nodes in the right must be larger than the parent).

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

class Solution {
    bool helper(TreeNode* node, long long min, long long max) {
        if (node == nullptr) return true;
        if (node->data <= min || node->data >= max) return false;
        return helper(node->left, min, node->data) &
               helper(node->right, node->data, max);
    }

   public:
    bool isBST(TreeNode* root) {
        if (root == nullptr) return true;
        return helper(root, LLONG_MIN, LLONG_MAX);
    }
};
```

---

### **Complexity Analysis**
- **Time Complexity:** $O(N)$, where $N$ is the number of nodes in the tree. We visit each node exactly once.
- **Space Complexity:** $O(H)$, where $H$ is the height of the tree, representing the maximum depth of the recursion stack. In the worst case (skewed tree), this is $O(N)$.


![alt text](<006path sum and construction of bt_240401_000658(11).jpg>) ![alt text](<006path sum and construction of bt_240401_000658(12).jpg>) ![alt text](<006path sum and construction of bt_240401_000658(13).jpg>) ![alt text](<006path sum and construction of bt_240401_000658(14).jpg>) ![alt text](<006path sum and construction of bt_240401_000658(15).jpg>)



![alt text](<006path sum and construction of bt_240401_000658(16).jpg>) ![alt text](<006path sum and construction of bt_240401_000658(17).jpg>) ![alt text](<006path sum and construction of bt_240401_000658(18).jpg>) ![alt text](<006path sum and construction of bt_240401_000658(19).jpg>) ![alt text](<006path sum and construction of bt_240401_000658(20).jpg>) ![alt text](<006path sum and construction of bt_240401_000658(21).jpg>) ![alt text](<006path sum and construction of bt_240401_000658(22).jpg>) 

---

![alt text](<007populating right validate bst closest element_240401_000753(19).jpg>) ![alt text](<007populating right validate bst closest element_240401_000753(20).jpg>) ![alt text](<007populating right validate bst closest element_240401_000753(21).jpg>)

---

![alt text](<008bt cameras hard_240401_000825(20).jpg>) ![alt text](<008bt cameras hard_240401_000825(21).jpg>) ![alt text](<008bt cameras hard_240401_000825(22).jpg>) ![alt text](<008bt cameras hard_240401_000825(23).jpg>) ![alt text](<008bt cameras hard_240401_000825(24).jpg>)

---

 ![alt text](<011serialise and kth smallest _240401_001010(8).jpg>) ![alt text](<011serialise and kth smallest _240401_001010(9).jpg>)