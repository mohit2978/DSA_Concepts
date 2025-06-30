#include <bits/stdc++.h>
using namespace std;

// Definition of doubly linked list
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

// Solution class
class Solution {
public:

    ListNode* insertBeforeHead1(ListNode* head, int X) {
        ListNode* newHead = new ListNode(X, head, nullptr);
        
        head->prev = newHead;

        return newHead;
    }

    ListNode* insertBeforeHead2(ListNode* head, int X) {
         ListNode * node=new ListNode(X);
        if(head==nullptr ) return node;

        node->next=head;
        head->prev=node;
        head=node;
        return head;

    }
};


ListNode* arrayToLinkedList(vector<int> &nums) {
    if (nums.empty()) return nullptr; 

    ListNode* head = new ListNode(nums[0]); 

    ListNode* prev = head;             

    for (int i=1; i < nums.size(); i++) {

        ListNode* temp = new ListNode(nums[i], nullptr, prev);
        prev->next = temp;    
        prev = temp;         
    }
    return head;  
}

// Helper Function to print the linked list
void printLL(ListNode* head) {
    while (head != NULL) {
        cout << head->val << " ";
        head = head->next;
    }
    cout << endl;
}

int main() {
    vector<int> nums = {2, 3, 4, 5};
    
    ListNode* head = arrayToLinkedList(nums);
    

    cout << "Original List: ";
    printLL(head);

    Solution sol;
    
    head = sol.insertBeforeHead1(head, 1);
    
    // Print the Modified list
    cout << "Modified list: ";
    printLL(head);

    return 0;
}