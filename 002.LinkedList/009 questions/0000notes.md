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