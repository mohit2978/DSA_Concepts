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
    //insert at head
    ListNode* insertAtHead(ListNode* &head, int X) {
        ListNode* node=new ListNode(X);
        node->next=head;
        head=node;
        return head;
    }

    //insert at tail
    ListNode* insertAtTail(ListNode* &head, int X) {
        ListNode *node=new ListNode(X);
        if(head==nullptr){
            head=node;
            return head;
        }
        ListNode *tmp=head;
        while(tmp->next!=nullptr){
            tmp=tmp->next;
        }
        tmp->next=node;
        return head;
    }

    //insert at kth position

    ListNode* insertAtKthPosition(ListNode* &head, int X, int K) {
        if(K==1) return insertAtHead(head,X);
        ListNode * tmp=head;
        for(int i=1;i<K-1;i++){
            tmp=tmp->next;
        }
        ListNode * list=tmp->next;
        ListNode * node=new ListNode(X);
        tmp->next=node;
        node->next=list;
        return head;
    }
    //insert node having val val before node of val X
    //it is possible X is not present in LL
    ListNode* insertBeforeX(ListNode* &head, int X, int val) {
        if(head==nullptr) return head;
        if(head->val==X) return insertAtHead(head,val);
        ListNode * tmp=head;
        ListNode * prev=nullptr;
        while(tmp!=nullptr && tmp->val!=X){
            prev=tmp;
            tmp=tmp->next;
        }
        if(tmp==nullptr) return head; //if X is not present then return as it is
        ListNode* node=new ListNode(val);
        prev->next=node;
        node->next=tmp;
        return head;
    }
    

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

    //delete kth node if k=1 delete head fucntion call if we have size too
    //then if k== size we can can deleteTail but here we have no size
    ListNode* deleteKthNode(ListNode* &head, int k) {
        if(head==nullptr) return head;
        if (k==1) return deleteHead(head);
        ListNode* tmp=head;
        for(int i=1;i<k-1;i++){
            tmp=tmp->next;
        }
        ListNode *deletenode=tmp->next;
        tmp->next=deletenode->next;
        delete deletenode;
        return head;
    }

    //delete node with value X

    ListNode* deleteNodeWithValueX(ListNode* &head, int X) {
        if(head->val==X) return deleteHead(head);
        ListNode * prev=nullptr;
        ListNode * curr= head;
        while(curr!=nullptr && curr->val!=X  ){
            //first check curr !=null then check for curr->val
            prev=curr;
            curr=curr->next;
        }
        if(curr==nullptr) return head;
        prev->next=curr->next;
        delete curr;
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
