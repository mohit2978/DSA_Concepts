# Segregate odd and even nodes in LL




Given the head of a singly linked list. Group all the nodes with odd indices followed by all the nodes with even indices and return the reordered list.



Consider the 1st node to have index 1 and so on. The relative order of the elements inside the odd and even group must remain the same as the given input.


Examples:
---
Input: head -> 1 -> 2 -> 3 -> 4 -> 5

Output: head -> 1 -> 3 -> 5 -> 2 -> 4

Explanation: The nodes with odd indices are 1, 3, 5 and the ones with even indices are 2, 4.

---

Input: head -> 4 -> 3 -> 2 -> 1

Output: head -> 4 -> 2 -> 3 -> 1

Explanation: The nodes with odd indices are 4, 2 and the ones with even indices are 3, 1.

---

Input: head -> 1

Output:
head -> 1

---

```cpp


class Solution {
public:
    ListNode* oddEvenList(ListNode* head) {
        if(head==nullptr || head->next ==nullptr) return head;
        ListNode * even =new ListNode(-1);
        ListNode * odd =new ListNode(-1);
        ListNode * curr=head;
        ListNode * h1=odd;
        ListNode * h2=even;
        int index=1;
        while(curr!=nullptr){
            if(index%2==0){
                h2->next=curr;
                h2=h2->next;
            }else{
                h1->next=curr;
                h1=h1->next;
            }
            curr=curr->next;
            index++;
        }
        h1->next=even->next;
        h2->next=nullptr;
        even->next=nullptr;
        delete(even);
        h1=odd;
        odd=odd->next;
        h1->next=nullptr;
        delete(h1);
        return odd;
    }
};
```