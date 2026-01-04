# Notes
![alt text](<003 merge k sorted list and reverse nodes_240412_185705 (1).jpg>)

![alt text](<003 merge k sorted list and reverse nodes_240412_185705 (1)(1).jpg>) 

### Mergesort lists

```cpp
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

```
### Merge k sorted lists

```java

/**
 * Definition for singly-linked list.
 * public class ListNode {
 *     int val;
 *     ListNode next;
 *     ListNode() {}
 *     ListNode(int val) { this.val = val; }
 *     ListNode(int val, ListNode next) { this.val = val; this.next = next; }
 * }
 */
class Solution {
    public ListNode merge(ListNode h1,ListNode h2){
        if(h1==null) return h2;
        if(h2==null) return h1;
        ListNode dummy=new ListNode(-1);
        ListNode curr=dummy;
        while(h1!=null&&h2!=null){
            if(h1.val<h2.val){
                ListNode node=new ListNode(h1.val);
                curr.next=node;
                h1=h1.next;
            }
            else{
                ListNode node=new ListNode(h2.val);
                curr.next=node;
                h2=h2.next;
            }
            curr=curr.next;
        }
        while(h1!=null){
             ListNode node=new ListNode(h1.val);
                curr.next=node;
                h1=h1.next;
             curr=curr.next;
            
        }
        while(h2!=null){
              ListNode node=new ListNode(h2.val);
                curr.next=node;
                h2=h2.next;
             curr=curr.next;
        }
        return dummy.next;
    }
    
    public ListNode mergelist(ListNode[] lists,int si,int li){
        if(si==li) return lists[si];
        int mid=(si+li)/2;
        ListNode l1=mergelist(lists,si,mid);
        ListNode l2=mergelist(lists,mid+1,li);
        return merge(l1,l2);
    }
    public ListNode mergeKLists(ListNode[] lists) {
        if(lists.length==0) return null;
        return mergelist(lists,0,lists.length-1);
    }
}
```


![alt text](<003 merge k sorted list and reverse nodes_240412_185705 (1)(2).jpg>) ![alt text](<003 merge k sorted list and reverse nodes_240412_185705 (1)(3).jpg>) ![alt text](<003 merge k sorted list and reverse nodes_240412_185705 (1)(4).jpg>) ![alt text](<003 merge k sorted list and reverse nodes_240412_185705 (1)(5).jpg>) 

```java

/**
 * Definition for singly-linked list.
 * public class ListNode {
 *     int val;
 *     ListNode next;
 *     ListNode() {}
 *     ListNode(int val) { this.val = val; }
 *     ListNode(int val, ListNode next) { this.val = val; this.next = next; }
 * }
 */
class Solution {
    public int length(ListNode head){
        if(head==null) return 0;
        ListNode curr=head;
        int length=0;
        while(curr!=null){
            curr=curr.next;
            length++;
        }
        return length;
    }
    public void addfirst(ListNode[]temp,ListNode node){
        if(temp[0]==null){
            temp[0]=temp[1]=node;
        }
        else{
            node.next=temp[0];
            temp[0]=node;
        }
    }
    
    public ListNode reverseKGroup(ListNode head, int k) {
        if(head==null||head.next==null||k==1) return head;
        ListNode[] temp=new ListNode[2];
        int len=length(head);
        ListNode ah=null;
        ListNode at=null;
        ListNode curr=head;
        while(len>=k){
            int tempVar=k;
            while(tempVar-->0){
                ListNode forward=curr.next;
                curr.next=null;
                addfirst(temp,curr);
                curr=forward;
            }
            if(ah==null){
                ah=temp[0];
                at=temp[1];
            }
            else{
                at.next=temp[0];
                at=temp[1];
            }
            temp[0]=temp[1]=null;
            len-=k;
            
        }
        at.next=curr;
        return ah;
        
    }
}

```


![alt text](<003 merge k sorted list and reverse nodes_240412_185705 (1)(6).jpg>) ![alt text](<003 merge k sorted list and reverse nodes_240412_185705 (1)(7).jpg>) ![alt text](<003 merge k sorted list and reverse nodes_240412_185705 (1)(8).jpg>) ![alt text](<003 merge k sorted list and reverse nodes_240412_185705 (1)(9).jpg>) ![alt text](<003 merge k sorted list and reverse nodes_240412_185705 (1)(10).jpg>) ![alt text](<003 merge k sorted list and reverse nodes_240412_185705 (1)(11).jpg>) ![alt text](<003 merge k sorted list and reverse nodes_240412_185705 (1)(12).jpg>) ![alt text](<003 merge k sorted list and reverse nodes_240412_185705 (1)(13).jpg>) ![alt text](<003 merge k sorted list and reverse nodes_240412_185705 (1)(14).jpg>) ![alt text](<003 merge k sorted list and reverse nodes_240412_185705 (1)(15).jpg>) ![alt text](<003 merge k sorted list and reverse nodes_240412_185705 (1)(16).jpg>)