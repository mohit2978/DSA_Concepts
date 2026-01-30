# Notes

![alt text](image.png)

![alt text](image-1.png)

```cpp
class NumArray {
    vector<int> segtree;
    int n;

    void buildTree(vector<int>& nums, int s, int e, int i) {
        if (s == e) {
            segtree[i] = nums[s];
            return;
        }
        int mid = s + (e - s) / 2;
        buildTree(nums, s, mid, 2 * i + 1);
        buildTree(nums, mid + 1, e, 2 * i + 2);
        segtree[i] = segtree[2 * i + 1] + segtree[2 * i + 2];
    }

    void updateTree(int idx, int val, int s, int e, int i) {
        if (s == e) {
            segtree[i] = val;
            return;
        }
        int mid = s + (e - s) / 2;
        if (idx <= mid) updateTree(idx, val, s, mid, 2 * i + 1);
        else updateTree(idx, val, mid + 1, e, 2 * i + 2);
        segtree[i] = segtree[2 * i + 1] + segtree[2 * i + 2];
    }

    int getSum(int l, int r, int s, int e, int i) {
        if (r < s || e < l) return 0; // No overlap
        if (l <= s && e <= r) return segtree[i]; // Total overlap

        int mid = s + (e - s) / 2;
        return getSum(l, r, s, mid, 2 * i + 1) + getSum(l, r, mid + 1, e, 2 * i + 2);
    }

public:
    NumArray(vector<int>& nums) {
        n = nums.size();
        if (n > 0) {
            segtree.assign(4 * n, 0);
            buildTree(nums, 0, n - 1, 0);
        }
    }

    void update(int index, int val) {
        if (n > 0) updateTree(index, val, 0, n - 1, 0);
    }

    int sumRange(int left, int right) {
        if (n == 0) return 0;
        return getSum(left, right, 0, n - 1, 0);
    }
};

/**
 * Your NumArray object will be instantiated and called as such:
 * NumArray* obj = new NumArray(nums);
 * obj->update(index,val);
 * int param_2 = obj->sumRange(left,right);
 */
 ```

 ## Segment Tree Query: The "Search and Combine" Mission

The `sumRange` query works by decomposing your target range $[L, R]$ into a few precomputed "blocks" (nodes) that already exist in the tree. Instead of summing every single index, you are just summing the values of a few strategic nodes.

---

### 1. The Three Scenarios (Node vs. Target)
When the algorithm visits a node covering range $[S, E]$, it makes a decision based on how it overlaps with your target $[L, R]$:

* **No Overlap (The "Dead End"):** * *Condition:* $E < L$ or $S > R$.
    * *Action:* Return **0**. This branch of the tree contains nothing useful for your sum.
* **Total Overlap (The "Shortcut"):** * *Condition:* $L \le S$ and $E \le R$.
    * *Action:* Return **the value stored in the node**. You’ve found a perfect "block" that fits entirely inside your target.
* **Partial Overlap (The "Split"):** * *Condition:* Neither of the above.
    * *Action:* **Split the search.** Query the left child and the right child, then return their sum.



---

### 2. Walkthrough: Querying Range [2, 6]
Imagine an array of size 8 (indices 0–7). You want the sum from **2 to 6**.

1.  **Root (0–7):** Overlaps partially. **Split.**
2.  **Left Child (0–3):** Overlaps partially. **Split.**
    * **Node (0–1):** No overlap. Returns **0**.
    * **Node (2–3):** **Total overlap!** Returns precomputed sum of index 2 and 3.
3.  **Right Child (4–7):** Overlaps partially. **Split.**
    * **Node (4–5):** **Total overlap!** Returns precomputed sum of index 4 and 5.
    * **Node (6–7):** Overlaps partially. **Split.**
        * **Node (6):** **Total overlap!** Returns value at index 6.
        * **Node (7):** No overlap. Returns **0**.

**Final Result:** `Sum(2-3) + Sum(4-5) + Val(6)`. You only had to touch 3 "summary" nodes instead of 5 individual elements.



---

### 3. Efficiency: Why $O(\log N)$?
In a standard array, a range sum could take $O(N)$ time if you have to visit every element. In a Segment Tree:
* The tree height is $\log N$.
* At each level, you visit at most **4 nodes**.
* This ensures that even for an array of 1,000,000 elements, you only need to look at about 60–80 nodes to find any range sum.
Sometimes no need of update so can use this way 


## How to Remember Segment Tree Query Conditions

The easiest way to remember these is to think of it as a **"Security Checkpoint"** where the node has to prove its relationship to your target range $[L, R]$.

---

### 1. The "Out of Bounds" Check (No Overlap)
**Logic:** If the node's territory is entirely to the left of your target, or entirely to the right, it’s useless.
* **Mnemonic:** *"If my End is before your Start, or my Start is after your End, I'm out."*
* **Code:** `if (e < l || s > r) return 0;`



---

### 2. The "Perfect Fit" Check (Total Overlap)
**Logic:** If the node's territory is **inside** your target, the node's stored sum is exactly what you need.
* **Mnemonic:** *"If my territory is wrapped inside yours, I'll just give you my sum."*
* **The Trap:** People often flip this and check if the target is inside the node. **Don't do that.** You want to know if the *Node* $[S, E]$ is small enough to fit inside the *Target* $[L, R]$.
* **Code:** `if (s >= l && e <= r) return segtree[i];`



---

### 3. The "Split" (Partial Overlap)
**Logic:** If you didn't pass the first two checks, you are partially in and partially out. You can't give a final answer yet.
* **Mnemonic:** *"I’m only halfway there; let me ask my kids."*
* **Code:** Recursive calls to left and right children.



---

### Summary Cheat Sheet Table

| Scenario | Relation ($S, E$ vs $L, R$) | Mnemonic | Return Value |
| :--- | :--- | :--- | :--- |
| **No Overlap** | $E < L$ OR $S > R$ | "I'm outside." | `0` |
| **Total Overlap** | $S \ge L$ AND $E \le R$ | "I'm inside." | `segtree[i]` |
| **Partial Overlap**| Anything else | "Split me." | `Query(Left) + Query(Right)` |

```cpp

class Solution {
    void buildSegmentTree(int i, int l, int r, vector<int>& segmentTree, int arr[]) {
        if(l == r) {
            segmentTree[i] = arr[l];
            return;
        }
        
        int mid = l + (r-l)/2;
        buildSegmentTree(2*i+1, l, mid, segmentTree, arr);
        buildSegmentTree(2*i+2, mid+1, r, segmentTree, arr);
        segmentTree[i] = segmentTree[2*i + 1] + segmentTree[2*i + 2];
    }
    
    int querySegmentTree(int start, int end, int i, int l, int r, vector<int>& segmentTree) {
        if(l > end || r < start) {
            return 0;
        }
        
        if(l >= start && r <= end) {
            return segmentTree[i];
        }
        
        int mid = l + (r-l)/2;
        return querySegmentTree(start, end, 2*i+1, l,    mid, segmentTree) + 
               querySegmentTree(start, end, 2*i+2, mid+1, r, segmentTree);
    }
  public:
    vector<int> querySum(int n, int arr[], int q, int queries[]) {
               vector<int> segmentTree(4*n);
        
        buildSegmentTree(0, 0, n-1, segmentTree, arr);
        
        vector<int> result;
        for(int i = 0; i < 2*q; i+=2) {
            int start = queries[i]-1;   //Input is in 1 base indexing
            int end   = queries[i+1]-1; //Input is in 1 based indexing
            
            result.push_back(querySegmentTree(start, end, 0, 0, n-1, segmentTree));
        }
        
        return result;

        
    }
```







































