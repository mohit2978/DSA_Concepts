## Notes

### Reverse a LL
```cpp

class Solution {
   ListNode* reverse(ListNode* head){

    ListNode * curr=head;
    ListNode* prev=nullptr;

    while(curr!=nullptr){
        ListNode * storage=curr->next;
        curr->next=prev;
        prev=curr;
        curr=storage;
    }

    return prev;

   }
public:
    ListNode* reverseList(ListNode* head) {
        if(head==nullptr || head->next==nullptr) return head;
        return reverse(head);
    }
};

```

tc-->O(n)

### Mid of ll

Given the head of a singly Linked List, return the middle node of the Linked List.



If the Linked List has an even number of nodes, return the second middle one.

---
Examples:
Input: head -> 3 -> 8 -> 7 -> 1 -> 3

Output(value at returned node): 7

Explanation: There are 5 nodes, so the middle node is the 3rd Node, with value 7.

---

Input: head -> 2 -> 9 -> 1 -> 4 -> 0 -> 4

Output(value at returned node): 4

Explanation: There are 6 nodes, thus both the 3rd and 4th nodes are middle. So the 2nd middle node (4th Node) is returned with value 4.

---

Constraints:
1 <= number of Nodes in the Linked List <= 105

-10^4 <= ListNode.val <= 10^4

```cpp
class Solution {
public:
    ListNode* middleOfLinkedList(ListNode* head) {
        if(head==nullptr || head->next==nullptr) return head;
        ListNode * fast=head;
        ListNode * slow=head;
        while(fast!=nullptr && fast->next!=nullptr){
            slow=slow->next;
            fast=fast->next->next;
        }
        return slow;

    }
};
```

### Delete the mid node

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
public:
    ListNode* deleteMiddle(ListNode* head) {
        if(head==nullptr || head->next==nullptr) return nullptr;
        ListNode * fast=head;
        ListNode * slow=head;
        ListNode * temp=nullptr;
        while(fast!=nullptr && fast->next!=nullptr){
            temp=(temp==nullptr)?slow:(temp->next);
            slow=slow->next;
            fast=fast->next->next;
        }
        temp->next=slow->next;
        delete(slow);
        return head;
    }
};
```