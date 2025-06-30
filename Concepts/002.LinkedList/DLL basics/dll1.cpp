#include <bits/stdc++.h>
using namespace std;

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


class Solution {
public:

    ListNode* arrayToLinkedList1(vector<int> &nums) {

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
    //My solution
    ListNode* arrayToLinkedList2(vector<int> &nums) {
        ListNode * tmpHead=new ListNode(-1);
        ListNode * curr=tmpHead;
        for(int n:nums){
            ListNode * tmp=new ListNode(n);
            curr->next=tmp;
            tmp->prev=curr;
            curr=curr->next;
        }

        curr=tmpHead->next;
        curr->prev=nullptr;
        tmpHead->next=nullptr;
        delete tmpHead;
        return curr;
    }

       ListNode* deleteHead1(ListNode* head) {
        if (head == nullptr || head->next == nullptr) 
            return nullptr;

        ListNode* prev = head;      
        head = head->next;    
        head->prev = nullptr;   
        prev->next = nullptr;  
        return head;          
    }

    //My sol
    ListNode * deleteHead2(ListNode* head) {
        if(head==nullptr || head->next==nullptr) return nullptr;
        ListNode* newHead=head->next;
        newHead->prev=nullptr;
        delete head;
        return newHead;
    }

    ListNode* deleteTail1(ListNode* head) {
        if (head == nullptr || head->next == nullptr) {
            return nullptr;  
        }
        
        ListNode* tail = head;
        while (tail->next != nullptr) 
            tail = tail->next; 
        
        ListNode* newTail = tail->prev;
        newTail->next = nullptr;
        tail->prev = nullptr;
        delete tail;  
        
        return head; 
    }

    //My sol
    ListNode* deleteTail2(ListNode* head) {
        if(head==nullptr||head->next==nullptr) return nullptr;
        ListNode * tmp=head;
        while(tmp->next->next!=nullptr){
            tmp=tmp->next;
        }
        ListNode* node =tmp->next;
        node->prev=nullptr;
        tmp->next=nullptr;
        delete node;
        return head;

    }

};

// Helper Function to print the linked list
void printLL(ListNode* head) {
    while (head != NULL) {
        cout << head->val << " ";
        head = head->next;
    }
    cout << endl;
}

int main() {
    vector<int> nums = {1, 2, 3, 4, 5};
    Solution sol;
    ListNode* head = sol.arrayToLinkedList1(nums);

    cout << "The doubly linked list is: ";
    printLL(head);

    return 0;
}