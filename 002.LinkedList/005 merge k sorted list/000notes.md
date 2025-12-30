# Notes
![alt text](<003 merge k sorted list and reverse nodes_240412_185705 (1).jpg>)

![alt text](<003 merge k sorted list and reverse nodes_240412_185705 (1)(1).jpg>) ![alt text](<003 merge k sorted list and reverse nodes_240412_185705 (1)(2).jpg>) ![alt text](<003 merge k sorted list and reverse nodes_240412_185705 (1)(3).jpg>) ![alt text](<003 merge k sorted list and reverse nodes_240412_185705 (1)(4).jpg>) ![alt text](<003 merge k sorted list and reverse nodes_240412_185705 (1)(5).jpg>) 

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