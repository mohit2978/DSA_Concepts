# Notes
![alt text](<005 lru cache_240218_120443 (1).jpg>)

![alt text](<005 lru cache_240218_120443 (1)(1).jpg>) ![alt text](<005 lru cache_240218_120443 (1)(2).jpg>) ![alt text](<005 lru cache_240218_120443 (1)(3).jpg>) ![alt text](<005 lru cache_240218_120443 (1)(4).jpg>) ![alt text](<005 lru cache_240218_120443 (1)(5).jpg>) ![alt text](<005 lru cache_240218_120443 (1)(6).jpg>) ![alt text](<005 lru cache_240218_120443 (1)(7).jpg>) ![alt text](<005 lru cache_240218_120443 (1)(8).jpg>)


![alt text](<005 lru cache_240218_120443 (1)(9).jpg>) 


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
Thats a good code but need to have a lot of checks in addFirst and removeNode ,better use this 

```java
class LRUCache {
  private HashMap<Integer, Node> mp;

  private class Node {
    int key;
    int val;
    Node prev = null;
    Node next = null;

    Node(int key, int val) {
      this.key = key;
      this.val = val;
    }
  }

  private Node head = null;
  private Node tail = null;
  private int cap;
  private int llSize;

  public LRUCache(int capacity) {
    mp = new HashMap<>();
    cap = capacity;
    llSize = 0;
    head = new Node(-1, -1);
    tail = new Node(-2, -2);
    head.next = tail;
    tail.prev = head;
  }

  private void removeNode(Node node) {
    Node prevNode = node. prev;
    Node nextNode = node .next;
    prevNode.next = nextNode;
    nextNode.prev = prevNode;
    node.next = null;
    node.prev = null;
    llSize--;
  }

  private void addFirst(Node node) {
    Node nextNode = head.next;
    node.prev = head;
    node.next = nextNode;
    nextNode.prev = node;
    head.next = node;
    llSize++;
  }

  private void makeRecent(Node node) {
    if (head.next == node) return;
    removeNode(node);
    addFirst(node);
  }

  private Node fetchValue(int key) {
    Node node = mp.get(key);
    makeRecent(node);
    return node;
  }

  public int get(int key) {
    if (!mp.containsKey(key)) return -1;
    return fetchValue(key).val;
  }

  public void put(int key, int value) {
    if (mp.containsKey(key)) {
      fetchValue(key).val = value;
      return;
    }
    Node node = new Node(key, value);
    addFirst(node);
    mp.put(key, node);
    if (mp.size() > this.cap) {
      Node lruNode = this.tail.prev;
      removeNode(lruNode);
      mp.remove(lruNode.key);
    }
  }
}

```
code 1 is here above code and code 2 is upper one
## Ai review 

This is a classic comparison between the **"Senior" Pattern (Sentinel Nodes)** and the **"Junior" Pattern (Conditional Checks)**.

**Verdict:** The first implementation (Code 1) is significantly better.

Here is the breakdown of why Code 1 is the standard for production systems and interviews.

###  The "Sentinel Node" Pattern (Code 1)
In Code 1, you initialize two dummy nodes: `head` and `tail`.

* **Head:** Always points to the start (but holds no data).
* **Tail:** Always points to the end (but holds no data).
* **Real Data:** Always floats between these two.

### The Magic
Because `head` and `tail` always exist, you never encounter a null pointer.

* You don't need to check `if (head == null)`.
* You don't need to check `if (size == 1)`.
* You don't need to check `if (node == tail)`.

### The "Spaghetti Logic" (Code 2)
In Code 2, `head` and `tail` can be `null`. This forces you to handle every edge case manually.

Look at the nightmare that is `removeNode` in Code 2:

```java
// Code 2: 20 lines of dangerous 'if-else' blocks
private void removeNode(Node node){
    if(llSize==1){
        // Handle single element
    } else if(node == head){
        // Handle head removal
    } else if(node == tail){
        // Handle tail removal
    } else {
        // Handle middle removal
    }
}
```

### Why this is bad:

* **Bug Prone:** It is extremely easy to forget one pointer update (e.g., forgetting to set `head.prev` to `null` when moving `head`).
* **Hard to Read:** The logic is buried under validational checks.
* **Slower (slightly):** CPU branch prediction hates excessive `if-else` chains.


![alt text](<005 lru cache_240218_120443 (1)(12).jpg>) ![alt text](<005 lru cache_240218_120443 (1)(13).jpg>) ![alt text](<005 lru cache_240218_120443 (1)(14).jpg>) ![alt text](<005 lru cache_240218_120443 (1)(15).jpg>) ![alt text](<005 lru cache_240218_120443 (1)(16).jpg>) ![alt text](<005 lru cache_240218_120443 (1)(17).jpg>) ![alt text](<005 lru cache_240218_120443 (1)(18).jpg>)
