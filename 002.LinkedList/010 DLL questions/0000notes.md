# Q1 Remove duplicated from sorted DLL

Given a doubly linked list of size `n`, sorted in non-decreasing order, remove all the duplicate nodes from the linked list such that each element appears only once.

Return the head of the modified doubly linked list.

#### Examples:

**Example 1:** **Input:** `1 <-> 2 <-> 2 <-> 3 <-> 3 <-> 4`  
**Output:** `1 <-> 2 <-> 3 <-> 4`  
**Explanation:** The duplicates (2 and 3) are removed, leaving only one instance of each.

**Example 2:** **Input:** `1 <-> 1 <-> 1 <-> 1`  
**Output:** `1`  
**Explanation:** All instances of 1 except the first one are removed.

#### Constraints:
* `1 <= n <= 10^5`
* `1 <= node.data <= 10^9`
* The linked list is sorted in non-decreasing order.


## My Approach 

```cpp
/*
Definition of doubly linked list:
struct ListNode
{
    int val;
    ListNode *next;
    ListNode *prev;
    ListNode()
    {
        val = 0;
        next = NULL;
        prev = NULL;
    }
    ListNode(int data1)
    {
        val = data1;
        next = NULL;
        prev = NULL;
    }
    ListNode(int data1, ListNode *next1, ListNode *prev1)
    {
        val = data1;
        next = next1;
        prev = prev1;
    }
};
*/

class Solution {
    void deleteNode(ListNode * node,ListNode* prevNode,ListNode * nextNode){
        prevNode->next=nextNode;
        if(nextNode!=nullptr) nextNode->prev=prevNode;
        delete(node);
    }
public:
    ListNode * removeDuplicates(ListNode *head) {
        if(head==nullptr || head->next==nullptr) return head;
        ListNode * curr=head;
        while(curr!=nullptr){
            ListNode * prev=curr;
            curr=curr->next;
            while(curr!=nullptr && curr->val==prev->val){
                ListNode *storage=curr;
                curr=curr->next;
                deleteNode(storage,prev,curr);
            }

        }
        return head;
    }
};
```

## Standard code

```cpp
ListNode * removeDuplicates(ListNode *head) {
    if (!head) return nullptr;

    ListNode* curr = head;
    while (curr != nullptr && curr->next != nullptr) {
        if (curr->val == curr->next->val) {
            ListNode* duplicate = curr->next;
            
            // Bridge the gap
            curr->next = duplicate->next;
            if (duplicate->next != nullptr) {
                duplicate->next->prev = curr;
            }
            
            delete duplicate; // Free memory
            // Note: Don't move 'curr' yet, need to check next node
        } else {
            curr = curr->next;
        }
    }
    return head;
}
```

AI told skip all duplicate node at once and instead  ofassiging prev->next again and again assign the next unique at once

```cpp
ListNode * removeDuplicates(ListNode *head) {
    if (!head) return head;

    ListNode* curr = head;

    while (curr != nullptr) {
        ListNode* nextUnique = curr->next;

        // 1. Skip all nodes that have the same value as curr
        while (nextUnique != nullptr && nextUnique->val == curr->val) {
            ListNode* temp = nextUnique;
            nextUnique = nextUnique->next;
            delete temp; // Still deleting to prevent leaks, but logic is grouped
        }

        // 2. Reconnect curr to the next unique node found
        curr->next = nextUnique;
        if (nextUnique != nullptr) {
            nextUnique->prev = curr;
        }

        // 3. Move curr to the next unique node
        curr = nextUnique;
    }

    return head;
}
```

All 3 have same Tc i.e. O(n) and SC as O(1)