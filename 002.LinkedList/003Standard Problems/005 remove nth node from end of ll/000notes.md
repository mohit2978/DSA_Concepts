# Notes

## Brute

just calculate length and then get nth node from last

2 times traversal needed

## Optimal

It is not fast and slow pointer it is just 2-ptr used here 

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
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        ListNode *temp=new ListNode(-1);
        temp->next=head;
        ListNode * first=head;
        int k=n;
        while(n--){
            first=first->next;
        }
        ListNode * sec=head;
        ListNode* tsec=temp;
        while(first){
            first=first->next;
            sec=sec->next;
            tsec=tsec->next;
        }
        tsec->next=sec->next;
        sec->next=nullptr;
        delete(sec);
        head=temp->next;
        temp->next=nullptr;
        delete (temp);
        return head;
    }
};
```
Time Complexity:O(n) because the code iterates through the linked list twice, once to move the 'first' pointer 'n' positions ahead and then to move both 'first' and 'sec' pointers until 'first' reaches the end.
Space Complexity:O(1) because the code uses a constant amount of extra space, regardless of the input size; only a few pointers are created.

## Efficient without a dummy node

```cpp
class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        // 1. Initialize two pointers
        ListNode *fast = head;
        ListNode *slow = head;

        // 2. Move 'fast' n steps ahead
        for (int i = 0; i < n; ++i) {
            fast = fast->next;
        }

        // 3. Handle the Edge Case: If fast is null after n steps, 
        // it means the head (n-th from end) must be removed.
        if (fast == nullptr) {
            ListNode* new_head = head->next;
            // Optionally delete the old head to free memory
            delete head; 
            return new_head;
        }

        // 4. Move both pointers until 'fast' reaches the end
        // When fast->next is null, slow will be one node *before* the target
        while (fast->next != nullptr) {
            fast = fast->next;
            slow = slow->next;
        }

        // 5. Remove the target node (which is slow->next)
        ListNode* node_to_delete = slow->next;
        slow->next = node_to_delete->next; // Bypass the target node

        // 6. Free the memory for the removed node
        delete node_to_delete; 
        
        return head;
    }
};
```