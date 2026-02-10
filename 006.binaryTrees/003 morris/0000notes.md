# Notes
![alt text](003_morris.jpg)
![alt text](003_morris(1).jpg) ![alt text](003_morris(2).jpg) ![alt text](003_morris(3).jpg)
![alt text](003_morris(4).jpg) ![alt text](003_morris(5).jpg) ![alt text](003_morris(6).jpg) ![alt text](003_morris(7).jpg) ![alt text](003_morris(8).jpg) ![alt text](003_morris(9).jpg) ![alt text](003_morris(10).jpg) 


---

See this code is of Find inorder predecessor and succesor in BST 

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
### Scope Difference (The "Ancestor" Problem)

**1. General Predecessor (Global):**
* If a node has no left child, its "Predecessor" is actually one of its **ancestors (parents)** further up the tree.
* **Example:** In a tree `1 -> 2` (2 is the right child), the predecessor of 2 is 1. Standard logic usually requires a stack or parent pointers to find this.

**2. Morris Predecessor (Local):**
* The Morris algorithm only looks for a predecessor **inside the left subtree**.
* If `curr->left` is `NULL`, Morris says "No predecessor logic needed here," and simply moves to the right.
* It does **not** attempt to find the ancestor-predecessor.



### In the context of the Morris Traversal algorithm, the "Predecessor" logic never looks up to ancestors. It is strictly limited to the Left Subtree.

Here is the precise distinction that confirms your statement:

---

### 1. General Inorder Predecessor (The Mathematical Definition)
If you ask for the inorder predecessor of a node `X`:

* **Case A (Has Left Child):** It is the **rightmost** node in `X`'s left subtree.
* **Case B (No Left Child):** It is the **nearest ancestor** where `X` is in the right subtree.

---

### 2. Morris Predecessor (The Algorithmic Step)
The helper function inside Morris Traversal `getPredecessor(curr)` only handles **Case A**.

* **Logic:** It goes to `curr->left`, then keeps going right until the end.

#### Why no Ancestors?
If `curr` has **no left child (Case B)**, the Morris algorithm **doesn't look for a predecessor at all.**
* It simply says: *"No left child? Okay, print curr and move to `curr->right`."*
* It relies on the **thread** created previously (by the ancestor) to have brought us here, but it does not actively search back for that ancestor.


![alt text](003_morris(11).jpg) ![alt text](003_morris(12).jpg) ![alt text](003_morris(13).jpg) ![alt text](003_morris(14).jpg) ![alt text](003_morris(15).jpg) ![alt text](003_morris(16).jpg) ![alt text](003_morris(17).jpg) ![alt text](003_morris(18).jpg) ![alt text](003_morris(19).jpg) ![alt text](003_morris(20).jpg) ![alt text](003_morris(21).jpg) ![alt text](003_morris(22).jpg) ![alt text](003_morris(23).jpg) ![alt text](003_morris(24).jpg) ![alt text](003_morris(25).jpg) ![alt text](003_morris(26).jpg) ![alt text](003_morris(27).jpg) ![alt text](003_morris(28).jpg) ![alt text](003_morris(29).jpg) 

### Inorder morris
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
#include<bits/stdc++.h>
using namespace std;

// Definition for a binary tree node.
  struct TreeNode {
      int data;
      TreeNode *left;
      TreeNode *right;
       TreeNode(int val) : data(val) , left(nullptr) , right(nullptr) {}
};

class Solution {
private:
TreeNode * getInorderPredecessor(TreeNode * node){
    //inorder predecessor in left then rightmost of that left
    TreeNode *tnode=node->left;

    //tnode->right if already traversed then node  else null  if not already traversed
    while(tnode->right!=nullptr && tnode->right!=node) tnode=tnode->right;

    return tnode;
}
public:
    vector<int> getInorder(TreeNode* root) {
    	vector<int> res;
        TreeNode * curr=root;
        while(curr!=nullptr){
            if(curr->left==nullptr){
                res.push_back(curr->data);
                curr=curr->right;
            }else {
                TreeNode *inorderPredecessor=getInorderPredecessor(curr);
                if(inorderPredecessor->right==nullptr){
                    //need to traverse

                    //res.push_back(curr->data);
                    inorderPredecessor->right=curr;
                    curr=curr->left;
                }else{
                    //already traversed

                    inorderPredecessor->right=nullptr;

                    //as inorder is L N R so to print current node if left tree is there we must
                    //travel left tree so that's why putting the data here

                    //if it was preorder then need to uncomment line 45 as that is N L R 
                    // so node 1st traversed then we go to left subtree so print in untraversed part
                    res.push_back(curr->data);
                    curr=curr->right;
                }
            }
        }
        return res;
    }
};

int main() {
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->left = new TreeNode(4);
    root->left->right = new TreeNode(5);
    root->left->right->right = new TreeNode(6);

    Solution sol;
    vector<int> inorder = sol.getInorder(root);

    cout << "Binary Tree Morris Inorder Traversal: ";
    for (int val : inorder) {
        cout << val << " ";
    }
    cout << endl;

    return 0;
}

```