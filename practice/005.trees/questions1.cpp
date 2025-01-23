#include <bits/stdc++.h>
using namespace std;

// Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {

    private:
    bool isMirror(TreeNode *p ,TreeNode *q){
        if(p==nullptr && q==nullptr) return true;
        if(p==nullptr || q== nullptr) return false;
        if(p->val != q->val) return false;
        return isMirror(p->left,q->right) && isMirror(p->right ,q->left);
    }


public:
    int maxDepth(TreeNode* root) {
        if(root==nullptr) return 0;
        return max(maxDepth(root->left),maxDepth(root->right))+1;
    }

    //check if two trees are identical
    bool isSameTree(TreeNode* p, TreeNode* q) {
        if(p==nullptr && q==nullptr) return true;
        if(p==nullptr || q==nullptr ) return false;
        if(p->val!=q->val) return false;
        bool lres=isSameTree(p->left,q->left);
        bool rres=isSameTree(p->right,q->right);
        return lres & rres;
    }

       bool isSymmetric(TreeNode* root) {
        if(root==nullptr|| (root->left==nullptr && root->right==nullptr)) return true;
        return isMirror (root->left,root->right);
    }
};

int main() {
    // Example usage
    Solution solution;

    // Creating two sample trees
    TreeNode* tree1 = new TreeNode(1);
    tree1->left = new TreeNode(2);
    tree1->right = new TreeNode(3);

    TreeNode* tree2 = new TreeNode(1);
    tree2->left = new TreeNode(2);
    tree2->right = new TreeNode(3);

    // Checking if the trees are identical
    bool result = solution.isSameTree(tree1, tree2);
    cout << "Are the trees identical? " << result << endl;  // Output: 1 (true)

    // Clean up
    delete tree1->left;
    delete tree1->right;
    delete tree1;
    delete tree2->left;
    delete tree2->right;
    delete tree2;

    return 0;
}