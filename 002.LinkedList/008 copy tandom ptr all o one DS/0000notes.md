# Notes


![alt text](<006_231121_163402 (1).jpg>)







![alt text](<006_231121_163402 (1)(1).jpg>) ![alt text](<006_231121_163402 (1)(2).jpg>) ![alt text](<006_231121_163402 (1)(3).jpg>) ![alt text](<006_231121_163402 (1)(4).jpg>)

```java
/*
// Definition for a Node.
class Node {
    int val;
    Node next;
    Node random;

    public Node(int val) {
        this.val = val;
        this.next = null;
        this.random = null;
    }
}
*/

class Solution {
    public Node copyRandomList(Node head) {
        Node curr=head;
        Map<Node,Node>map=new HashMap<>();
        Node dummy=new Node(-1);
        Node tmp=dummy;
        while(curr!=null){
            Node node=new Node(curr.val);
            map.put(curr,node);
            tmp.next=node;
            tmp=tmp.next;
            curr=curr.next;
        }
        curr=head;
        tmp=dummy.next;
        while(curr!=null){
            Node rn=curr.random;
            Node rntmp=map.get(rn);
            tmp.random=rntmp;
            curr=curr.next;
            tmp=tmp.next;
        }
        return dummy.next;
    }
}
```

 ![alt text](<006_231121_163402 (1)(5).jpg>) ![alt text](<006_231121_163402 (1)(6).jpg>)



![alt text](<006_231121_163402 (1)(7).jpg>) ![alt text](<006_231121_163402 (1)(8).jpg>) ![alt text](<006_231121_163402 (1)(9).jpg>) ![alt text](<006_231121_163402 (1)(10).jpg>) 

```java

/*
// Definition for a Node.
class Node {
    int val;
    Node next;
    Node random;

    public Node(int val) {
        this.val = val;
        this.next = null;
        this.random = null;
    }
}
*/

class Solution {
    public Node copyRandomList(Node head) {
       Node curr=head;
       while(curr!=null)
       {
           Node str=curr.next;
           Node node=new Node(curr.val);
           curr.next=node;
           node.next=str;
           curr=str;
       }
       curr=head;
       while(curr!=null){
          if(curr.random!=null) curr.next.random=curr.random.next;
          else curr.next.random=null;
           curr=curr.next.next;
       }
       Node dummy=new Node(-1);
       Node tmp=dummy;
       curr=head;
       while(curr!=null){
         Node nxt=curr.next;
         tmp.next=nxt;
         curr.next=nxt.next;
         if(curr.next!=null) nxt.next=curr.next.next;
         curr=curr.next;
         tmp=tmp.next;
       }
       return dummy.next;
    }
}
```

![alt text](<006_231121_163402 (1)(11).jpg>) ![alt text](<006_231121_163402 (1)(12).jpg>) ![alt text](<006_231121_163402 (1)(13).jpg>) ![alt text](<006_231121_163402 (1)(14).jpg>) ![alt text](<006_231121_163402 (1)(15).jpg>) 