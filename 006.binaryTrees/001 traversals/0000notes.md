# Notes

## Normal tree
```cpp

#include <bits/stdc++.h>

using namespace std;

class Node {
    public: Node * left;
    Node * right;
    int val;

    Node(int val) {
        this -> val = val;
        this -> left = nullptr;
        this -> right = nullptr;
    }
};

Node * binaryTree() {

    int x;
    cout << "Enter node value" << "\n";
    cin >> x;
    if (x == -1) return nullptr;
    Node * node = new Node(x);

    cout << "Enter left value";
    node -> left = binaryTree();

    cout << "Enter right value";
    node -> right = binaryTree();

    return node;

}

void inorderTraversal(vector < int > & vec, Node * node) {
    if (node == nullptr) return;

    inorderTraversal(vec, node -> left);
    vec.push_back(node -> val);
    inorderTraversal(vec, node -> right);
}

void print(vector < int > & v) {

    for (int i = 0; i < v.size(); i++) {
        cout << v[i] << ",";
    }
}

int main() {
    Node * root = binaryTree();

    vector < int > vec;
    inorderTraversal(vec, root);
    print(vec);
    return 0;
}
```
![alt text](001_traversals_easy_med.jpg)
![alt text](001_traversals_easy_med(1).jpg) ![alt text](001_traversals_easy_med(2).jpg) ![alt text](001_traversals_easy_med(3).jpg) ![alt text](001_traversals_easy_med(4).jpg) ![alt text](001_traversals_easy_med(5).jpg) ![alt text](001_traversals_easy_med(6).jpg) ![alt text](001_traversals_easy_med(7).jpg) ![alt text](001_traversals_easy_med(8).jpg) ![alt text](001_traversals_easy_med(9).jpg)



 ![alt text](001_traversals_easy_med(10).jpg) 
 ![alt text](001_traversals_easy_med(11).jpg) 
 
 ```cpp
#include<bits/stdc++.h>
using namespace std;
struct Node
{
    int data;
    Node* left;
    Node* right;
};
class Solution {
    public:
      // Function to return a list of nodes visible from the top view
      // from left to right in Binary Tree.
      vector<int> topView(Node *root) {
          vector<int> res;
          unordered_map<int,Node*>mp;
          queue<pair<Node*,int>>q;
          int left=0,right=0;
          q.push({root,0});
          while(q.size()>0){
              int sz=q.size();
              while(sz-->0){
                  pair<Node*,int> rem=q.front();
                  q.pop();
                  if(mp.find(rem.second)!=mp.end()){
                      mp[rem.second]=rem.first;
                  }
                  if(rem.second<left) left=rem.second;
                  if(rem.second>right) right=rem.second;
                  if(rem.first->left!=nullptr){
                      q.push({rem.first->left,rem.second-1});
                  }
                   if(rem.first->right!=nullptr){
                      q.push({rem.first->right,rem.second+1});
                  }
              }
          }
          
          for(int i=left;i<=right;i++){
              res.push_back(mp[i]->data);
          }
          return res;
          
    }
}
```
 
 ![alt text](001_traversals_easy_med(12).jpg) ![alt text](001_traversals_easy_med(13).jpg) ![alt text](001_traversals_easy_med(14).jpg) ![alt text](001_traversals_easy_med(15).jpg) ![alt text](001_traversals_easy_med(16).jpg) ![alt text](001_traversals_easy_med(17).jpg) ![alt text](001_traversals_easy_med(18).jpg) ![alt text](001_traversals_easy_med(19).jpg) 