# Notes
![alt text](<007extras_240212_010313 (1).jpg>)

![alt text](<007extras_240212_010313 (1)(1).jpg>) ![alt text](<007extras_240212_010313 (1)(2).jpg>) ![alt text](<007extras_240212_010313 (1)(3).jpg>) ![alt text](<007extras_240212_010313 (1)(4).jpg>) ![alt text](<007extras_240212_010313 (1)(5).jpg>)


## Ques sort 0-1-2

### Brute 

```cpp
#include <bits/stdc++.h>

using namespace std;

// Definition of singly linked list:
struct ListNode {
    int val;
    ListNode* next;
    ListNode() {
        val = 0;
        next = NULL;
    }
    ListNode(int data1) {
        val = data1;
        next = NULL;
    }
    ListNode(int data1, ListNode* next1) {
        val = data1;
        next = next1;
    }
};
/*
TC-->O(2N)
SC-->O(1)
*/
class Solution {
public:
    // Function to sort the linked list
    ListNode* sortList(ListNode* head) {
        // Initialize counts
        int c0 = 0, c1 = 0, c2 = 0;
        ListNode* temp = head;

       /* Count the number of 0s, 
       1s, and 2s in the list*/
        while (temp != NULL) {
            if (temp->val == 0)
                c0++;
            else if (temp->val == 1)
                c1++;
            else if (temp->val == 2)
                c2++;
            temp = temp->next;
        }

        temp = head;

       /* Reassign values to 
       the nodes based on 
       the counts*/
        while (temp != NULL) {
            if (c0 > 0) {
                temp->val = 0;
                c0--;
            } else if (c1 > 0) {
                temp->val = 1;
                c1--;
            } else if (c2 > 0) {
                temp->val = 2;
                c2--;
            }
            temp = temp->next;
        }

        return head;
    }
};

// Function to print linked list
void printList(ListNode* head) {
    while (head != NULL) {
        cout << head->val << " ";
        head = head->next;
    }
    cout << endl;
}

// Function to create new node
ListNode* newNode(int data) {
    ListNode* node = new ListNode(data);
    return node;
}

int main() {
    // Creating a linked list
    ListNode* head = newNode(1);
    head->next = newNode(2);
    head->next->next = newNode(0);
    head->next->next->next = newNode(1);
    head->next->next->next->next = newNode(2);
    head->next->next->next->next->next = newNode(0);
    head->next->next->next->next->next->next = newNode(1);

    // Print original list
    cout << "Original list: ";
    printList(head);

    // Sort the list
    Solution sol;
    head = sol.sortList(head);

    // Print sorted list
    cout << "Sorted list: ";
    printList(head);

    return 0;
}

```

### Mysol

```java

/* Definition of singly Linked List:
class ListNode {
    int val;
    ListNode next;

    ListNode(int data1) {
        val = data1;
        next = null;
    }

    ListNode(int data1, ListNode next1) {
        val = data1;
        next = next1;
    }
}
*/
import java.util.*;
class Solution {

    public ListNode sortList(ListNode head) {
        if(head==null || head.next==null) return head;
        ListNode h1=new ListNode(-1);
        ListNode h2=new ListNode(-2);
        ListNode h3=new ListNode(-3);

        ListNode t1=h1;
        ListNode t2=h2;
        ListNode t3=h3;

        ListNode t=head;
        while(t!=null){
            ListNode nextNode=t.next;
            if(t.val==0){
                t1.next=t;
                t1=t1.next;
            }
             if(t.val==1){
                t2.next=t;
                t2=t2.next;
            }
             if(t.val==2){
                t3.next=t;
                t3=t3.next;
            }
            t.next=null;
            t=nextNode;
        }
        head=(h1.next!=null?h1.next:(h2.next!=null?h2.next:h3.next));
        t1.next=h2.next!=null?h2.next:h3.next;
        t2.next=h3.next;
        
        h1.next=null;
        h2.next=null;
        h3.next=null;

        return head;

    }
}


/*
Complexity Analysis
Time Complexity: O(N) because the code
 traverses the linked list once. Here, N
  represents the length of the linked list 
  or the number of nodes present in the linked list.
Space Complexity: O(1) because 
no extra space is used and we just change the
 links of the nodes.

*/
```

### Optimal

```cpp
#include <bits/stdc++.h>

using namespace std;

// Definition of singly linked list:
struct ListNode {
    int val;
    ListNode* next;
    ListNode() {
        val = 0;
        next = NULL;
    }
    ListNode(int data1) {
        val = data1;
        next = NULL;
    }
    ListNode(int data1, ListNode* next1) {
        val = data1;
        next = next1;
    }
};

class Solution {
public:
    // Function to sort the linked list
    ListNode* sortList(ListNode* head) {
       /* If the list is empty or has only one 
       node, return as it is already sorted*/
        if (head == NULL || head->next == NULL)
            return head;

        // Dummy nodes to point to heads of 
        // three lists
        ListNode* zeroHead = new ListNode(-1);
        ListNode* oneHead = new ListNode(-1);
        ListNode* twoHead = new ListNode(-1);

        // Pointers to current last nodes of 
        // three lists
        ListNode* zero = zeroHead;
        ListNode* one = oneHead;
        ListNode* two = twoHead;
        ListNode* temp = head;

       /* Traverse the original list 
       and distribute the nodes 
       into three lists*/
        while (temp != NULL) {
            if (temp->val == 0) {
                zero->next = temp;
                zero = temp;
            } else if (temp->val == 1) {
                one->next = temp;
                one = temp;
            } else if (temp->val == 2) {
                two->next = temp;
                two = temp;
            }
            temp = temp->next;
        }
        
        // Connect the three lists together
        zero->next = (oneHead->next) ? oneHead->next : twoHead->next;
        one->next = twoHead->next;
        two->next = NULL;

        // New head of the sorted list
        ListNode* newHead = zeroHead->next;

        // Delete dummy nodes
        delete zeroHead;
        delete oneHead;
        delete twoHead;
        
        return newHead;
    }
};

// Helper function to print linked list
void printList(ListNode* head) {
    while (head != NULL) {
        cout << head->val << " ";
        head = head->next;
    }
    cout << endl;
}

// Helper function to create a new node
ListNode* newNode(int data) {
    ListNode* node = new ListNode(data);
    return node;
}

int main() {
    // Creating a linked list
    ListNode* head = newNode(1);
    head->next = newNode(2);
    head->next->next = newNode(0);
    head->next->next->next = newNode(1);
    head->next->next->next->next = newNode(2);
    head->next->next->next->next->next = newNode(0);
    head->next->next->next->next->next->next = newNode(1);

    // Print original list
    cout << "Original list: ";
    printList(head);

    // Sort the list
    Solution sol;
    head = sol.sortList(head);

    // Print sorted list
    cout << "Sorted list: ";
    printList(head);

    return 0;
}

```

## Q add 1 to ll

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
    ListNode* reverseList(ListNode* head) {
        if(head==nullptr || head->next==nullptr) return head;
        return reverse(head);
    }
public:
    ListNode *addOne(ListNode *head) {
        if(head==nullptr) return new ListNode(1);
        ListNode *h=reverseList(head);
        ListNode *curr=h;
        ListNode *prev=curr;
        int carry=0;
        while(curr!=nullptr){
            int val=curr->val;
            if(curr==h) val+=1;
            val+=carry;
            carry=val/10;
            val=val%10;
            curr->val=val;
            prev=curr;
            curr=curr->next;
        }
        if(carry!=0){
            prev->next=new ListNode(carry);
        } 
        return reverseList(h);
    }
};
```

### Minor Refinement Suggestions
While the logic is solid, there are two areas where the code can be slightly more "idiomatic" or robust:

1. Logic Simplification in the Addition Loop
Inside your while loop, you use if(curr==h) val+=1; to add the initial 1. A cleaner way is to initialize your carry to 1 instead of 0. This treats the "initial +1" exactly like a carry from a previous digit.

2. The reverseList Wrapper
In your reverseList function, the check if(head==nullptr || head->next==nullptr) is technically redundant because your reverse function handles those cases naturally. Removing it keeps the code lean.

### Ai code

```cpp
class Solution {
    ListNode* reverse(ListNode* head) {
        ListNode *curr = head, *prev = nullptr;
        while (curr != nullptr) {
            ListNode *nextTemp = curr->next;
            curr->next = prev;
            prev = curr;
            curr = nextTemp;
        }
        return prev;
    }

public:
    ListNode *addOne(ListNode *head) {
        if (!head) return new ListNode(1);

        // 1. Reverse the list
        ListNode *h = reverse(head);
        
        // 2. Add one using a carry-first approach
        ListNode *curr = h, *prev = nullptr;
        int carry = 1; // Start with carry = 1 to represent the +1
        
        while (curr != nullptr && carry > 0) {
            int sum = curr->val + carry;
            curr->val = sum % 10;
            carry = sum / 10;
            prev = curr;
            curr = curr->next;
        }

        // 3. Handle leftover carry (e.g., 999 -> 1000)
        if (carry > 0) {
            prev->next = new ListNode(carry);
        }

        // 4. Reverse back to original order
        return reverse(h);
    }
};

```

### Complexity Analysis

Time Complexity
O(n) The reverseList function iterates through the linked list once to reverse it, taking O(n) time. The addOne function then calls reverseList twice, resulting in two O(n) operations. The while loop inside addOne iterates through the reversed list once, which is also O(n). Therefore, the dominant factor is O(n).
Space Complexity
O(1) The algorithm uses a constant amount of extra space for pointers (curr, prev, storage, h) and variables (carry, val). The space complexity does not depend on the size of the input linked list