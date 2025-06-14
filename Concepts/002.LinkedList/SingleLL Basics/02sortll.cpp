#include <bits/stdc++.h>
using namespace std;


struct ListNode {
      int val;
      ListNode *next;
      ListNode() : val(0), next(nullptr) {}
      ListNode(int x) : val(x), next(nullptr) {}
     ListNode(int x, ListNode *next) : val(x), next(next) {}
 };
 
class Solution {
    private :
        ListNode* mid (ListNode * node){
            if(node==nullptr || node->next==nullptr) return node;
            ListNode* slow=node;
            ListNode* fast=node;
            while( fast->next!=nullptr && fast->next->next!=nullptr){
                slow=slow->next;
                fast=fast->next->next;
            }
            return slow;
        }  
    
        ListNode* merge(ListNode *l1,ListNode *l2){
            if(l1==nullptr && l2==nullptr) return l1;
            if(l1==nullptr) return l2;
            if(l2==nullptr) return l1;
             ListNode* tmp=new ListNode(-1);
            ListNode *itr1=l1;
            ListNode * itr2=l2;
            ListNode *curr=tmp;
            while(itr1!=nullptr && itr2!=nullptr){
                if(itr1->val < itr2->val){
                    curr->next=itr1;
                    curr=curr->next;
                    itr1=itr1->next;
                    curr->next=nullptr;
                }else{
                    curr->next=itr2;
                    curr=curr->next;
                    itr2=itr2->next;
                    curr->next=nullptr;
                }
            }
            if(itr1!=nullptr) curr->next=itr1;
            if(itr2!=nullptr) curr->next=itr2;
            ListNode * head=tmp->next;
            tmp->next=nullptr;
            delete(tmp);
            return head;
    
        }  
    public:
        ListNode* sortList(ListNode* head) {
            if(head==nullptr || head->next==nullptr) return head;
            ListNode* middle=mid(head);
            ListNode *l1=head;
            ListNode *l2=middle->next;
            middle->next=nullptr;
            l1=sortList(l1);
            l2=sortList(l2);
           return merge(l1,l2);
        }
};

int main(){
    
    return 0;
}