#include <bits/stdc++.h>
using namespace std;


struct ListNode {
    int val; 
    ListNode* next;
    
    //constructors
    ListNode(int data1) : val(data1), next(nullptr) {} 
    ListNode(int data1, ListNode* next1) : val(data1), next(next1) {} 
};


class Solution {
public:
    //delete 1st node
    ListNode* deleteHead(ListNode* &head) {
        if(head==nullptr|| head->next==nullptr) return nullptr;
        ListNode *tmp=head;
        head=head->next;
        tmp->next=nullptr;
        return head;

    }
    //delete the last node
       ListNode* deleteTail(ListNode* &head) {
        if(head==nullptr|| head->next==nullptr) return nullptr;
        ListNode* tmp=head;
        while(tmp->next->next!=nullptr) tmp=tmp->next;
        delete tmp->next; //extra step here we need to delete it too 
        tmp->next=nullptr;
        return head;

    }
    //Function for Linked List Traversal
    vector<int> LLTraversal(ListNode* head) {
       vector<int>v;
        if(head==nullptr ) return v;
        ListNode* tmp=head;
        while(tmp!=nullptr){
            v.push_back(tmp->val);
            tmp=tmp->next;
        }
        return v;
    }
};

int main() {
    //Manual creation of nodes
    ListNode* y1 = new ListNode(2);
    ListNode* y2 = new ListNode(5);
    ListNode* y3 = new ListNode(8);
    ListNode* y4 = new ListNode(7);

    // Linking the nodes
    y1->next = y2;
    y2->next = y3;
    y3->next = y4;

    //Instance of
    //Solution class
    Solution sol;

    //Calling LLTraversal method 
    //To get the values
    vector<int> result = sol.LLTraversal(y1);

    //Printing the result
    cout << "Linked List Values:" << endl;
    for (int val : result) {
        cout << val << " ";
    }
    cout << endl;

    //Clean up 
    //Allocated memory
    delete y1;
    delete y2;
    delete y3;
    delete y4;

    return 0;
}
