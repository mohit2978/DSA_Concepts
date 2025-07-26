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