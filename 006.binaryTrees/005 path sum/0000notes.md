# Notes

![alt text](<005path sum _240401_000608.jpg>)

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
    int countNodes(TreeNode* root) { 
        if(root==nullptr) return 0;

        TreeNode* curr=root->left;
        int lh=0;
        while(curr!=nullptr){
            curr=curr->left;
            lh++;
        }

        curr=root->right;
        int rh=0;
        while(curr!=nullptr){
            curr=curr->right;
            rh++;
        }
        if(lh==rh) return (1<<(lh+1))-1;
        return countNodes(root->left)+countNodes(root->right)+1;
    }
};
```

![alt text](<005path sum _240401_000608(1).jpg>) ![alt text](<005path sum _240401_000608(2).jpg>) ![alt text](<005path sum _240401_000608(3).jpg>) ![alt text](<005path sum _240401_000608(4).jpg>) ![alt text](<005path sum _240401_000608(5).jpg>) ![alt text](<005path sum _240401_000608(6).jpg>) ![alt text](<005path sum _240401_000608(7).jpg>) ![alt text](<005path sum _240401_000608(8).jpg>) ![alt text](<005path sum _240401_000608(9).jpg>) ![alt text](<005path sum _240401_000608(10).jpg>) ![alt text](<005path sum _240401_000608(11).jpg>) ![alt text](<005path sum _240401_000608(12).jpg>) ![alt text](<005path sum _240401_000608(13).jpg>) ![alt text](<005path sum _240401_000608(14).jpg>) ![alt text](<005path sum _240401_000608(15).jpg>) ![alt text](<005path sum _240401_000608(16).jpg>) ![alt text](<005path sum _240401_000608(17).jpg>) ![alt text](<005path sum _240401_000608(18).jpg>) ![alt text](<005path sum _240401_000608(19).jpg>) 












