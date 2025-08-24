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