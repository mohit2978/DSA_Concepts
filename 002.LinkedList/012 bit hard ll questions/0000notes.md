# Rotate a Linked List

**Problem Statement:**
Given the head of a singly linked list, rotate the list to the right by `k` places.

For each rotation, the last node of the list moves to the front, and this process is repeated `k` times.

---

### Examples

**Example 1:**
* **Input:** `head = [1, 2, 3, 4, 5]`, `k = 2`
* **Output:** `[4, 5, 1, 2, 3]`
* **Explanation:**
    * Rotate 1: `[5, 1, 2, 3, 4]`
    * Rotate 2: `[4, 5, 1, 2, 3]`

**Example 2:**
* **Input:** `head = [0, 1, 2]`, `k = 4`
* **Output:** `[2, 0, 1]`
* **Explanation:**
    * Rotate 1: `[2, 0, 1]`
    * Rotate 2: `[1, 2, 0]`
    * Rotate 3: `[0, 1, 2]`
    * Rotate 4: `[2, 0, 1]`
    * **Note:** Rotating by $k=4$ on a list of length 3 is equivalent to rotating by $k \% 3 = 1$.

---

### Constraints
* $0 \le \text{Number of nodes} \le 10^5$
* $-10^9 \le \text{Node.val} \le 10^9$
* $0 \le k \le 2 \times 10^9$

---
## My sol
```cpp
/*
Definition of singly linked list:
struct ListNode
{
    int val;
    ListNode *next;
    ListNode()
    {
        val = 0;
        next = NULL;
    }
    ListNode(int data1)
    {
        val = data1;
        next = NULL;
    }
    ListNode(int data1, ListNode *next1)
    {
        val = data1;
        next = next1;
    }
};
*/

class Solution {
    ListNode* getNthFromEnd(ListNode* head, int n) {
      
        ListNode * first=head;
        while(n--){
            first=first->next;
        }
        ListNode * sec=head;

        while(first){
            first=first->next;
            sec=sec->next;
        }
        
        return sec;
    }
    ListNode * rotate (ListNode * curr,ListNode *prev,ListNode * head){
        prev->next=nullptr;
        ListNode * temp=curr;
        while(temp->next!=nullptr) temp=temp->next;
        temp->next=head;
        head=curr;
        return head;
    }
public:
    ListNode* rotateRight(ListNode* head, int k) {
        if(head==nullptr ||head->next==nullptr ||k==0) return head;
        int len=0;
        ListNode *temp=head;
        while(temp!=nullptr){
            len++;
            temp=temp->next;
        }
        if(k>len) k=k%len;
        if(k==0) return head;
        ListNode *nthfromEnd= getNthFromEnd(head,k);

        ListNode *curr=head;
        while(curr->next!=nthfromEnd) curr=curr->next;
        return rotate(nthfromEnd,curr,head);
    }
};
```

# Logic Analysis: Rotate Right (The Multi-Pass Approach)

Your implementation uses a "Physical Displacement" logic. Instead of treating the list as a circle, you find the exact node that needs to become the new head and the node that needs to become the new tail.

---

### 1. Component Breakdown

#### A. `getNthFromEnd(head, n)`
This is the **Two-Pointer (Tortoise and Hare)** strategy.
* **The Gap**: You move the `first` pointer `n` steps ahead.
* **The Slide**: You then move `first` and `sec` together. When `first` hits the end (NULL), `sec` is exactly `n` nodes from the end.
* **Result**: This returns the node that will become the **New Head**.

#### B. `rotate(curr, prev, head)`
This is the "Surgery" phase.
* **Sever**: `prev->next = nullptr` cuts the link, creating the **New Tail**.
* **Connect**: It traverses from `curr` to the old tail and connects it to the old `head`.
* **Update**: Returns `curr` as the new starting point of the list.

#### C. `rotateRight(head, k)`
The "Control Tower" logic.
* **Edge Cases**: Handles empty lists, single nodes, or $k=0$ immediately.
* **Length & Modulo**: Finds the length to handle $k > len$ (using $k = k \% len$).
* **Finding the Cut**: Uses `getNthFromEnd` to find the new head, and then uses a `while` loop to find the node right before it (`curr`) to perform the cut.

---

### 2. Execution Walkthrough ($N=5, K=2$)
**List**: `1 -> 2 -> 3 -> 4 -> 5`

1. **Len calculation**: `len = 5`.
2. **Modulo**: `2 % 5 = 2`.
3. **getNthFromEnd(2)**:
   - `first` moves to 3.
   - `first` and `sec` move together until `first` is NULL.
   - `sec` lands on **4**. (`nthfromEnd = 4`).
4. **Finding `curr`**:
   - `curr` starts at head and stops when `curr->next == 4`.
   - `curr` lands on **3**.
5. **The Surgery (`rotate`)**:
   - `3->next = nullptr` (3 is the new tail).
   - Node 5 (old tail) is found and `5->next = 1` (old head).
   - Return **4** as the new head.
**Final List**: `4 -> 5 -> 1 -> 2 -> 3`

---

### 3. Summary for your Notes

| Feature | Analysis |
| :--- | :--- |
| **Logic Type** | "Search and Cut" (Multi-Pass) |
| **Time Complexity** | $O(N)$ — You traverse for length, then for the Nth node, then for the node before it, then for the tail. |
| **Space Complexity** | $O(1)$ — Only pointer manipulation, no extra memory. |
| **Strengths** | Very modular; uses the `getNthFromEnd` pattern which is a common interview favorite. |
| **Weaknesses** | Performs multiple passes over the list. The "Circular" method (connecting tail to head first) is slightly more concise. |

---

### 4. Pro-Tip for the Interview
The interviewer might ask: **"Your `rotate` function searches for the tail again. Could you have found the tail earlier?"**
* **Your Answer**: "Yes! During the first length-calculation pass, I could store the tail pointer. This would save one $O(N)$ traversal inside the `rotate` function."


### Optimal Approach Intuition
1. **Find the Length**: Traverse the list to find its length ($L$) and the tail node.
2. **Handle Large K**: If $k \ge L$, the effective rotations needed are $k \% L$. If $k \% L = 0$, the list remains unchanged.
3. **Make it Circular**: Connect the tail node to the head node to create a circular linked list.
4. **Find the New Tail**: The new tail will be at the $(L - k)^{th}$ node from the start.
5. **Break the Circle**: Set the `next` of the $(L - k)^{th}$ node as the new head and set the $(L - k)^{th}$ node's `next` to `NULL`.


```cpp
class Solution {
public:
    ListNode* rotateRight(ListNode* head, int k) {
        if (!head || !head->next || k == 0) return head;

        // 1. Find length and the ACTUAL tail node
        int len = 1; // Start at 1 because we stop at the last node
        ListNode* tail = head;
        while (tail->next) {
            len++;
            tail = tail->next;
        }

        // 2. Handle cases where k >= len
        k = k % len;
        if (k == 0) return head;

        // 3. Connect tail to head to make a circle
        tail->next = head;

        // 4. Find the new tail: it's at (len - k) steps from head
        // To get to the new tail, we jump (len - k - 1) times
        //as we can see in mysolution its kth from end means len-kth from begining
        int stepsToNewTail = len - k;
        ListNode* newTail = head;
        for (int i = 0; i < stepsToNewTail - 1; i++) {
            newTail = newTail->next;
        }

        // 5. Set the new head and break the circle
        ListNode* newHead = newTail->next;
        newTail->next = nullptr;

        return newHead;
    }
};
```