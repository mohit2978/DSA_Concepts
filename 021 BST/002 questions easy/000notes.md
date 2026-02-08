# Notes

# Q1 Add a node to BST

![alt text](Scanned_20260208-1843-03.jpg)
## My code 1

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
public:
    TreeNode* insertIntoBST(TreeNode* root, int val) {
        if(root==nullptr) return root;
        if(root->left==nullptr && root->right==nullptr){
            if(val>root->data) root->right=new TreeNode(val);
            else root->left=new TreeNode(val);
            return root;
        }
        if(root->right==nullptr && val>root->data){
            root->right=new TreeNode(val);
            return root;
        }
        
        if(root->left==nullptr && val<root->data){
            root->left=new TreeNode(val);
            return root;
        }
        if(val>root->data) insertIntoBST(root->right,val);
        else insertIntoBST(root->left,val);
        return root;
    }
};
```
## Perfect code

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
public:
    TreeNode* insertIntoBST(TreeNode* root, int val) {
// 1. Base Case: We reached the correct insertion point
        if (root == nullptr) {
            return new TreeNode(val);
        }

        // 2. Navigation: Choose left or right
        if (val > root->data) {
            // Re-assign right child to catch the newly created node
            root->right = insertIntoBST(root->right, val);
        } else {
            // Re-assign left child to catch the newly created node
            root->left = insertIntoBST(root->left, val);
        }

        // 3. Return: Return the original root back up the stack
        return root;
    }
};
```
# Q2 Deletion of node in BST 
 
 ![alt text](Scanned_20260208-1843-04.jpg)
  ![alt text](Scanned_20260208-1843-05.jpg)
 Ai given idea i just written code

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
public:
    TreeNode* deleteNode(TreeNode* root, int key) {
        if(root==nullptr) return root;
        if(root->data==key){
            if(root->left==nullptr) return root->right;
            if(root->right==nullptr) return root->left;
            TreeNode *leftnode=root->left;
            TreeNode *rnode=root->right;
            TreeNode * lnode=leftnode;
            while(lnode->right!=nullptr){
                lnode=lnode->right;
            }
            lnode->right=rnode;
            return leftnode;
        }
        if(key>root->data) root->right=deleteNode(root->right,key);
        else root->left=deleteNode(root->left,key);
        return root;
    }
};
```
# Q3 target sum
 ![alt text](002bst_231018_213407(9).jpg) ![alt text](002bst_231018_213407(10).jpg) ![alt text](002bst_231018_213407(11).jpg) ![alt text](002bst_231018_213407(12).jpg) ![alt text](002bst_231018_213407(13).jpg) ![alt text](002bst_231018_213407(14).jpg) 


# Q4 Floor and Ceil in a BST



### **Problem Statement**
Given a binary search tree (BST) and a key, find the **floor** and **ceil** values of that key in the BST.

- **Floor Value:** The largest value in the BST that is smaller than or equal to the key.
- **Ceil Value:** The smallest value in the BST that is greater than or equal to the key.

If either the floor or ceil value does not exist, return -1 for that specific value.

---

### **Example 1**
**Input:** `root = [10, 5, 15, 2, 6]`, `key = 7`  
**Output:** `Floor: 6, Ceil: 10`  
**Explanation:** - The values in the BST are `{2, 5, 6, 10, 15}`.
- The largest value $\le 7$ is 6.
- The smallest value $\ge 7$ is 10.

### **Example 2**
**Input:** `root = [10, 5, 15, 2, 6]`, `key = 1`  
**Output:** `Floor: -1, Ceil: 2`  
**Explanation:** - There is no value $\le 1$ in the BST, so Floor is -1.
- The smallest value $\ge 1$ is 2.

---

### **Constraints**
- The number of nodes in the tree is in the range `[1, 10^5]`.
- `1 <= Node.val <= 10^9`
- `1 <= key <= 10^9`

---

![alt text](Scanned_20260208-1843-01.jpg) ![alt text](Scanned_20260208-1843-02.jpg)

Two pass solution
```cpp
/**
 * Definition for a binary tree node.
 * class TreeNode {
 *     int data;
 *     TreeNode *left;
 *     TreeNode *right;
 *      TreeNode(int val) : data(val) , left(nullptr) , right(nullptr) {}
 * };
 **/

class Solution{	
    int floorval=-1;
    int ceilval=1e7+1;
    void getFloor(TreeNode* root,int val){
        if(root==nullptr){
            return;
        }
        if(root->data==val){
            floorval=val;
            return;
        }
        else if(root->data<val){
            floorval=max(floorval,root->data);
            getFloor(root->right,val);
        }else getFloor(root->left,val);
    }
      void getCeil(TreeNode* root,int val){
        if(root==nullptr){
            return;
        }
        if(root->data==val){
            ceilval=val;
            return;
        }
        else if(root->data>val){
            ceilval=min(ceilval,root->data);
            getCeil(root->left,val);
        }else getCeil(root->right,val);
    }
	
	public:
		vector<int> floorCeilOfBST(TreeNode* root,int key){
			getFloor(root,key);
            getCeil(root,key);
			ceilval=(ceilval==1e7+1)?-1:ceilval;
            return {floorval,ceilval};
		}
};
```

One pass solution

```cpp
/**
 * Definition for a binary tree node.
 * class TreeNode {
 *     int data;
 *     TreeNode *left;
 *     TreeNode *right;
 *      TreeNode(int val) : data(val) , left(nullptr) , right(nullptr) {}
 * };
 **/

class Solution{	
    int floorval=-1;
    int ceilval=1e7+1;
      void getCeil(TreeNode* root,int val){
        if(root==nullptr){
            return;
        }
        if(root->data==val){
            ceilval=val;
			floorval=val;
            return;
        }
        else if(root->data>val){
            ceilval=min(ceilval,root->data);
            getCeil(root->left,val);
        }else {
			floorval=max(floorval,root->data);
			getCeil(root->right,val);
		}
    }
	
	public:
		vector<int> floorCeilOfBST(TreeNode* root,int key){
			//getFloor(root,key);
            getCeil(root,key);
			ceilval=(ceilval==1e7+1)?-1:ceilval;
            return {floorval,ceilval};
		}
};
```
# Q5 Inorder Successor and Predecessor in BST



---

### **Problem Statement**
Given a binary search tree (BST) and a key, find the **Inorder Successor** and **Inorder Predecessor** of the given key in the BST.

- **Inorder Predecessor:** The node with the largest value that is strictly smaller than the key.
- **Inorder Successor:** The node with the smallest value that is strictly greater than the key.

If either the predecessor or successor does not exist, return -1 for that specific value.

---

### **Example 1**
**Input:** `root = [10, 5, 15, 2, 6, 12, 20]`, `key = 10`  
**Output:** `Predecessor: 6, Successor: 12`  
**Explanation:** - Inorder traversal: `[2, 5, 6, 10, 12, 15, 20]`
- Node before 10 is 6.
- Node after 10 is 12.

### **Example 2**
**Input:** `root = [10, 5, 15, 2, 6, 12, 20]`, `key = 2`  
**Output:** `Predecessor: -1, Successor: 5`  
**Explanation:** - Inorder traversal: `[2, 5, 6, 10, 12, 15, 20]`
- 2 is the first node, so Predecessor is -1.
- Node after 2 is 5.

---

### **Constraints**
- The number of nodes in the tree is in the range `[1, 10^5]`.
- `1 <= Node.val <= 10^9`
- `1 <= key <= 10^9`

---
Brute--> get inorder get inorder succesor and predecessor

Better--> 3 traversals 

See in morris traversal it is morris predecessor which we use, there we need to go from bottom left to next up!! But here we using general predecessor 

if we have child then normal morris predecessor 

if not then our parent is our predecesoor if we are on right of our parent ,and if we are on left than parent is our succesor

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
    TreeNode* ancpred = nullptr;
    TreeNode* ancsucc = nullptr;
    TreeNode* inorderPred(TreeNode* node) {
        if (node->left == nullptr) return nullptr;
        TreeNode* curr = node->left;
        while (curr->right != nullptr) curr = curr->right;
        return curr;
    }
    TreeNode* inorderSucc(TreeNode* node) {
        if (node->right == nullptr) return nullptr;
        TreeNode* curr = node->right;
        while (curr->left != nullptr) curr = curr->left;
        return curr;
    }
    TreeNode* find(TreeNode* root, int val) {
        if (root == nullptr) return root;
        if (val == root->data) return root;
        if (val > root->data) {
            ancpred = root;
            return find(root->right, val);
        } else {
            ancsucc = root;
            return find(root->left, val);
        }
    }

   public:
    vector<int> succPredBST(TreeNode* root, int key) {
        TreeNode* node = find(root, key);
        vector<int> res(2, -1);
		if(node==nullptr) return res;
        TreeNode* pred = inorderPred(node);
        TreeNode* succ = inorderSucc(node);
        if (pred != nullptr)
            res[0] = pred->data;
        else if (ancpred != nullptr)
            res[0] = ancpred->data;
        if (succ != nullptr)
            res[1] = succ->data;
        else if (ancsucc != nullptr)
            res[1] = ancsucc->data;
        return res;
    }
};
```



































