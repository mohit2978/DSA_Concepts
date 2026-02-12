# Notes
![alt text](<005 lru cache_240218_120443 (1).jpg>)

![alt text](<005 lru cache_240218_120443 (1)(1).jpg>) ![alt text](<005 lru cache_240218_120443 (1)(2).jpg>) ![alt text](<005 lru cache_240218_120443 (1)(3).jpg>) ![alt text](<005 lru cache_240218_120443 (1)(4).jpg>) ![alt text](<005 lru cache_240218_120443 (1)(5).jpg>) ![alt text](<005 lru cache_240218_120443 (1)(6).jpg>) ![alt text](<005 lru cache_240218_120443 (1)(7).jpg>) ![alt text](<005 lru cache_240218_120443 (1)(8).jpg>)


![alt text](<005 lru cache_240218_120443 (1)(9).jpg>) 

## My code
```java
class LRUCache {
    private HashMap<Integer,Node>mp;
    private class Node{
        int key;
        int val;
        Node prev=null;
        Node next=null;

        Node(int key,int val){
            this.key=key;
            this.val=val;
        }
    }
    private Node head=null;
    private Node tail=null;
    private int cap;
    private int llSize;
    public LRUCache(int capacity) {
        mp=new HashMap<>();
        cap=capacity;
        llSize=0;
    }
    private void removeNode(Node node){
        if(llSize==1){
            this.head=this.tail=null;
        } else if(node ==head){
            Node nxtNode=node.next;
            nxtNode.prev=node.next=null;
            head=nxtNode;
        } else if(node ==tail){
            Node prevNode=node.prev;
            node.prev=prevNode.next=null;
            tail=prevNode;
        }else{
            Node prevNode=node.prev;
            Node nxtNode=node.next;
            prevNode.next=nxtNode;
            nxtNode.prev=prevNode;
            node.next=null;
            node.prev=null;
        }
        llSize--;
    }
    private void addFirst(Node node){
        if(head==null){
            head=tail=node;
            llSize++;
            return;
        }
        llSize++;
        node.next=head;
        head.prev=node;
        head=node;
        return;
    }
    private void makeRecent(Node node){
        if(head==node) return;
        removeNode(node);
        addFirst(node);
    }
    private Node fetchValue(int key){
         Node node=mp.get(key);
         makeRecent(node);
         return node;
    }
    public int get(int key) {
        if(!mp.containsKey(key)) return -1;
        return fetchValue(key).val;
    }
    
    public void put(int key, int value) {
        if(mp.containsKey(key)) {
           fetchValue(key).val=value;
           return ;
        }
        Node node=new Node(key,value);
        addFirst(node);
        mp.put(key,node);
        if(mp.size()>this.cap){
            Node tail=this.tail;
            removeNode(tail);
            mp.remove(tail.key);
        }
    }
}

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache obj = new LRUCache(capacity);
 * int param_1 = obj.get(key);
 * obj.put(key,value);
 */
```

## Rajneesh code
```java
import java.util.*;

class LRUCache {

    private class Node {
        int key = 0;
        int value = 0;

        Node prev = null, next = null;

        Node(int key, int value) {
            this.key = key;
            this.value = value;
        }
    }

    private HashMap<Integer, Node> map;
    private Node head = null, tail = null;
    private int capacity = 0;
    private int linkedListSize = 0;

    public LRUCache(int capacity) {
        this.map = new HashMap<>();
        this.capacity = capacity;
    }

    private void addFirst(Node node) {
        if (this.head == null)
            this.head = this.tail = node;
        else {
            this.head.next = node;
            node.prev = this.head;
            this.head = node;
        }
        this.linkedListSize++;
    }

    private void removeNode(Node node) {
        if (this.linkedListSize == 1)
            this.head = this.tail = null;
        else if (this.head == node) {
            Node prevNode = node.prev;
            prevNode.next = node.prev = null;
            this.head = prevNode;
        } else if (this.tail == node) {
            Node nextNode = node.next;
            nextNode.prev = node.next = null;
            this.tail = nextNode;
        } else {
            Node prevNode = node.prev;
            Node nextNode = node.next;

            prevNode.next = nextNode;
            nextNode.prev = prevNode;

            node.prev = node.next = null;
        }
        
        this.linkedListSize--;
    }

    private void makeRecentApp(Node node) {
        if (node == this.head)
            return;

        removeNode(node);
        addFirst(node);
    }

    private Node fetchNode(int key) {
        Node node = map.get(key);
        makeRecentApp(node);
        return node;
    }

    // make it recent app and return its state
    public int get(int key) {
        if (!map.containsKey(key))
            return -1;

        return fetchNode(key).value;
    }

    // key : appName, value : stateOfApp
    public void put(int key, int value) {
        if (map.containsKey(key)) {
            Node node = fetchNode(key);
            node.value = value;
        } else {
            Node node = new Node(key, value);
            addFirst(node);
            map.put(key, node);
            if (map.size() > this.capacity) {
                Node tail = this.tail;
                removeNode(tail);
                map.remove(tail.key);
            }
        }

    }
}

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache obj = new LRUCache(capacity);
 * int param_1 = obj.get(key);
 * obj.put(key,value);
 */
```


  ![alt text](<005 lru cache_240218_120443 (1)(12).jpg>) ![alt text](<005 lru cache_240218_120443 (1)(13).jpg>) ![alt text](<005 lru cache_240218_120443 (1)(14).jpg>) ![alt text](<005 lru cache_240218_120443 (1)(15).jpg>) ![alt text](<005 lru cache_240218_120443 (1)(16).jpg>) ![alt text](<005 lru cache_240218_120443 (1)(17).jpg>) ![alt text](<005 lru cache_240218_120443 (1)(18).jpg>)
