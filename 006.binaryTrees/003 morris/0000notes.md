# Notes
![alt text](003_morris.jpg)
![alt text](003_morris(1).jpg) ![alt text](003_morris(2).jpg) ![alt text](003_morris(3).jpg)
![alt text](003_morris(4).jpg) ![alt text](003_morris(5).jpg) ![alt text](003_morris(6).jpg) ![alt text](003_morris(7).jpg) ![alt text](003_morris(8).jpg) ![alt text](003_morris(9).jpg) ![alt text](003_morris(10).jpg) ![alt text](003_morris(11).jpg) ![alt text](003_morris(12).jpg) ![alt text](003_morris(13).jpg) ![alt text](003_morris(14).jpg) ![alt text](003_morris(15).jpg) ![alt text](003_morris(16).jpg) ![alt text](003_morris(17).jpg) ![alt text](003_morris(18).jpg) ![alt text](003_morris(19).jpg) ![alt text](003_morris(20).jpg) ![alt text](003_morris(21).jpg) ![alt text](003_morris(22).jpg) ![alt text](003_morris(23).jpg) ![alt text](003_morris(24).jpg) ![alt text](003_morris(25).jpg) ![alt text](003_morris(26).jpg) ![alt text](003_morris(27).jpg) ![alt text](003_morris(28).jpg) ![alt text](003_morris(29).jpg) 

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