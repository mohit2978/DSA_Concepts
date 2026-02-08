# Notes

# Add a node to BST

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
# Deletion of node in BST 

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

 ![alt text](002bst_231018_213407(9).jpg) ![alt text](002bst_231018_213407(10).jpg) ![alt text](002bst_231018_213407(11).jpg) ![alt text](002bst_231018_213407(12).jpg) ![alt text](002bst_231018_213407(13).jpg) ![alt text](002bst_231018_213407(14).jpg) 


# Floor and Ceil in a BST

### **Problem Link**
[Floor and Ceil in a BST - TakeUForward](https://takeuforward.org/plus/dsa/problems/floor-and-ceil-in-a-bst)

---

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







































