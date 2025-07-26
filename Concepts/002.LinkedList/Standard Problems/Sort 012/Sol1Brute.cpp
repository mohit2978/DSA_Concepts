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