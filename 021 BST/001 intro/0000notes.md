# Notes

![alt text](001_bst231018_213407.jpg) ![alt text](001_bst231018_213407(1).jpg) ![alt text](001_bst231018_213407(2).jpg) ![alt text](001_bst231018_213407(3).jpg)
![alt text](001_bst231018_213407(4).jpg) ![alt text](001_bst231018_213407(5).jpg) ![alt text](001_bst231018_213407(6).jpg) ![alt text](001_bst231018_213407(7).jpg) ![alt text](001_bst231018_213407(8).jpg) ![alt text](001_bst231018_213407(9).jpg) ![alt text](001_bst231018_213407(10).jpg) ![alt text](001_bst231018_213407(11).jpg) ![alt text](001_bst231018_213407(12).jpg) ![alt text](001_bst231018_213407(13).jpg) ![alt text](001_bst231018_213407(14).jpg) ![alt text](001_bst231018_213407(15).jpg) ![alt text](001_bst231018_213407(16).jpg) ![alt text](001_bst231018_213407(17).jpg) ![alt text](001_bst231018_213407(18).jpg) ![alt text](001_bst231018_213407(19).jpg) ![alt text](001_bst231018_213407(20).jpg) ![alt text](001_bst231018_213407(21).jpg) ![alt text](001_bst231018_213407(22).jpg) ![alt text](001_bst231018_213407(23).jpg) ![alt text](001_bst231018_213407(24).jpg) ![alt text](001_bst231018_213407(25).jpg) ![alt text](001_bst231018_213407(26).jpg) ![alt text](001_bst231018_213407(27).jpg) ![alt text](001_bst231018_213407(28).jpg) ![alt text](001_bst231018_213407(29).jpg) ![alt text](001_bst231018_213407(30).jpg) 

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
