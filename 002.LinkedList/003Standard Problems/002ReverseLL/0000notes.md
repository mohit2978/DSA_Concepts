## Notes


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