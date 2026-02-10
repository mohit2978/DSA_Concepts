# Q1 LC129. Sum Root to Leaf Numbers

### **Problem Link**
[Sum Root to Leaf Numbers - LeetCode](https://leetcode.com/problems/sum-root-to-leaf-numbers/description/)

---

### **Problem Statement**
You are given the `root` of a binary tree containing digits from `0` to `9` only.

Each root-to-leaf path in the tree represents a number.
- For example, the root-to-leaf path `1 -> 2 -> 3` represents the number `123`.

Return the **total sum of all root-to-leaf numbers**. Test cases are generated so that the answer will fit in a **32-bit** integer.

A **leaf** node is a node with no children.

---

### **Example 1**
**Input:** `root = [1, 2, 3]`  
**Output:** `25`  
**Explanation:** The root-to-leaf path `1->2` represents the number `12`.  
The root-to-leaf path `1->3` represents the number `13`.  
Therefore, sum = `12 + 13 = 25`.

### **Example 2**
**Input:** `root = [4, 9, 0, 5, 1]`  
**Output:** `1026`  
**Explanation:** The root-to-leaf path `4->9->5` represents the number `495`.  
The root-to-leaf path `4->9->1` represents the number `491`.  
The root-to-leaf path `4->0` represents the number `40`.  
Therefore, sum = `495 + 491 + 40 = 1026`.

---

### **Constraints**
- The number of nodes in the tree is in the range `[1, 1000]`.
- `0 <= Node.val <= 9`
- The depth of the tree will not exceed `10`.

---

```java
/**
 * Definition for a binary tree node.
 * public class TreeNode {
 *     int val;
 *     TreeNode left;
 *     TreeNode right;
 *     TreeNode() {}
 *     TreeNode(int val) { this.val = val; }
 *     TreeNode(int val, TreeNode left, TreeNode right) {
 *         this.val = val;
 *         this.left = left;
 *         this.right = right;
 *     }
 * }
 */
class Solution {
    int sum=0;
    private void helper(TreeNode node,int num,TreeNode par,TreeNode root){

        if(node.left==null && node.right==null){
            num=num*10+node.val;
            sum+=num;
            return;
        }
        
       
        num=num*10+node.val;
        if(node.left!=null )helper(node.left,num,node,root);
        if(node.right!=null )helper(node.right,num,node,root);
    }
    public int sumNumbers(TreeNode root) {
        helper(root,0,null,root);
        return sum;
    }
}
```
TC-->O(n)

# Q2 662. Maximum Width of Binary Tree

### **Problem Link**
[Maximum Width of Binary Tree - LeetCode](https://leetcode.com/problems/maximum-width-of-binary-tree/description/)

---

### **Problem Statement**
Given the `root` of a binary tree, return the **maximum width** of the given tree.

The **maximum width** of a tree is the maximum **width** among all levels.

The **width** of one level is defined as the length between the end-nodes (the leftmost and rightmost non-null nodes), where the null nodes between the end-nodes that would be present in a complete binary tree extending down to that level are also counted into the length calculation.

It is guaranteed that the answer will in the range of a **32-bit** signed integer.

---

### **Example 1**
**Input:** `root = [1, 3, 2, 5, 3, null, 9]`  
**Output:** `4`  
**Explanation:** The maximum width exists in the third level with length 4 (`5, 3, null, 9`).

### **Example 2**
**Input:** `root = [1, 3, 2, 5, null, null, 9, 6, null, 7]`  
**Output:** `7`  
**Explanation:** The maximum width exists in the fourth level with length 7 (`6, null, null, null, null, null, 7`).

### **Example 3**
**Input:** `root = [1, 3, 2, 5]`  
**Output:** `2`  
**Explanation:** The maximum width exists in the second level with length 2 (`3, 2`).

---

### **Constraints**
- The number of nodes in the tree is in the range `[1, 3000]`.
- `-100 <= Node.val <= 100`


```java
/**
 * Definition for a binary tree node.
 * public class TreeNode {
 *     int val;
 *     TreeNode left;
 *     TreeNode right;
 *     TreeNode() {}
 *     TreeNode(int val) { this.val = val; }
 *     TreeNode(int val, TreeNode left, TreeNode right) {
 *         this.val = val;
 *         this.left = left;
 *         this.right = right;
 *     }
 * }
 */
class Solution {
    class Pair{
        long min;
        long max;
        Pair(long min,long max){
            this.min=min;
            this.max=max;
        }
    }
    private void helper(TreeNode node ,int dep,long idx,Map<Integer,Pair>mp){
        if(node==null) return;
        helper(node.left,dep+1,2*idx,mp);
        helper(node.right,dep+1,2*idx+1,mp);
        if(mp.containsKey(dep)){
            Pair p=mp.get(dep);
            p.max=Math.max(idx,p.max);
        }else{
            mp.put(dep,new Pair(idx,idx));
        }
        Pair p=mp.get(dep);
        maxWidth=Math.max(maxWidth,p.max-p.min+1);
    }
    long maxWidth;
    public int widthOfBinaryTree(TreeNode root) {
        maxWidth=0;
        Map<Integer,Pair>mp=new HashMap<>();
        helper(root,1,1,mp);
        return (int)maxWidth;
    }
}
```
segment tree vala conecpt use kia hai assume kr do perfect BT hai 

```java

/**
 * Definition for a binary tree node.
 * public class TreeNode {
 *     int val;
 *     TreeNode left;
 *     TreeNode right;
 *     TreeNode() {}
 *     TreeNode(int val) { this.val = val; }
 *     TreeNode(int val, TreeNode left, TreeNode right) {
 *         this.val = val;
 *         this.left = left;
 *         this.right = right;
 *     }
 * }
 */
class Solution {
    class Pair{
        long min;
        long max;
        Pair(long min,long max){
            this.min=min;
            this.max=max;
        }
    }
    private void helper(TreeNode node ,int dep,long idx,Map<Integer,Pair>mp){
        if(node==null) return;
        helper(node.left,dep+1,2*idx+1,mp);
        helper(node.right,dep+1,2*idx+2,mp);
        if(mp.containsKey(dep)){
            Pair p=mp.get(dep);
            p.max=Math.max(idx,p.max);
        }else{
            mp.put(dep,new Pair(idx,idx));
        }
        Pair p=mp.get(dep);
        maxWidth=Math.max(maxWidth,p.max-p.min+1);
    }
    long maxWidth;
    public int widthOfBinaryTree(TreeNode root) {
        maxWidth=0;
        Map<Integer,Pair>mp=new HashMap<>();
        helper(root,1,1,mp);
        return (int)maxWidth;
    }
}
```
# Q Longest even sum path 

![alt text](image.png)
