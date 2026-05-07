# Notes
![alt text](<005 lru cache_240218_120443 (1).jpg>)

![alt text](<005 lru cache_240218_120443 (1)(1).jpg>) ![alt text](<005 lru cache_240218_120443 (1)(2).jpg>) ![alt text](<005 lru cache_240218_120443 (1)(3).jpg>) ![alt text](<005 lru cache_240218_120443 (1)(4).jpg>) ![alt text](<005 lru cache_240218_120443 (1)(5).jpg>) ![alt text](<005 lru cache_240218_120443 (1)(6).jpg>) 

## LRU Cache — Complete Guide

### What is LRU Cache?

**LRU = Least Recently Used**

When cache is full and you need to add something new, evict the item that was **used least recently** — the one sitting idle the longest.

> Think of it like your browser tabs. When RAM is full, the browser kills the tab you haven't touched in the longest time.

---

### The Core Operations (both must be O(1))

```
get(key)        → return value if exists, else -1
                  mark this key as "recently used"

put(key, value) → insert or update key
                  if cache full → evict least recently used first
```

---

### Why This Data Structure?

We need **two things simultaneously**:

```
1. O(1) lookup by key          → HashMap
2. O(1) track usage order      → Doubly Linked List
                                  (move to front = recently used)
                                  (tail = least recently used)
```

Neither alone works. Together they do.Here is the internal structure first — how HashMap and Doubly Linked List work together:---

![alt text](image.png)


![alt text](<005 lru cache_240218_120443 (1)(7).jpg>) ![alt text](<005 lru cache_240218_120443 (1)(8).jpg>)


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


# LFU cache

## LFU Cache — Least Frequently Used

### LRU vs LFU — The Core Difference

```
LRU  →  evict the item unused for the LONGEST TIME
         "who was idle the longest?"

LFU  →  evict the item used the FEWEST TIMES overall
         "who was accessed the least?"
```

**Concrete example — cache capacity 2:**

```
put(1,10)   → cache: {1(freq=1), ...}
put(2,20)   → cache: {1(freq=1), 2(freq=1)}
get(1)      → cache: {1(freq=2), 2(freq=1)}   key=1 used twice now
put(3,30)   → cache full, must evict

LRU evicts: key=2  (least recently used)
LFU evicts: key=2  (lowest frequency = 1, key=1 has freq=2)

Same here — but watch this:

get(2)      → if key=2 still in LRU cache, freq becomes 2
put(4,40)   → 

LRU evicts: key=1  (key=2 was just used more recently)
LFU evicts: key=1  (both have freq=2, tie → evict least recently used among them)
```

The difference shows up when **old but frequently used** items compete with **new but rarely used** ones.

---

### Why LFU Needs a Completely Different Structure

LRU only tracks **one dimension** — time. One linked list handles it.

LFU tracks **two dimensions** — frequency AND time (for tie-breaking). You need:

```
1. key → (value, frequency)          HashMap 1
2. frequency → [list of keys]        HashMap 2  (each list = LRU within that freq)
3. minFreq tracker                   single integer
```

![alt text](image-6.png)

### The Code

```cpp
class LFUCache {
    struct Node {
        int key, val, freq;
        Node(int k, int v) : key(k), val(v), freq(1) {}
    };

    int capacity, minFreq;
    unordered_map<int, list<Node>::iterator> keyMap;  // key → iterator
    unordered_map<int, list<Node>> freqMap;           // freq → DLL

    void touch(int key) {
        auto it = keyMap[key];
        int f = it->freq;
        freqMap[f].erase(it);                        // remove from old freq bucket
        if (freqMap[f].empty()) {
            freqMap.erase(f);
            if (minFreq == f) minFreq++;             // update minFreq only if bucket gone
        }
        freqMap[f+1].push_front(*it);                // add to front of new freq bucket
        freqMap[f+1].front().freq = f + 1;
        keyMap[key] = freqMap[f+1].begin();          // update iterator in keyMap
    }

public:
    LFUCache(int cap) : capacity(cap), minFreq(0) {}

    int get(int key) {
        if (!keyMap.count(key)) return -1;
        touch(key);                                  // increment frequency
        return keyMap[key]->val;
    }

    void put(int key, int val) {
        if (capacity <= 0) return;
        if (keyMap.count(key)) {
            keyMap[key]->val = val;
            touch(key);                              // update existing key
            return;
        }
        if ((int)keyMap.size() == capacity) {        // evict LFU
            auto& lruList = freqMap[minFreq];
            keyMap.erase(lruList.back().key);        // back = LRU within min freq
            lruList.pop_back();
            if (lruList.empty()) freqMap.erase(minFreq);
        }
        freqMap[1].push_front({key, val});           // new node always freq=1
        keyMap[key] = freqMap[1].begin();
        minFreq = 1;                                 // new node resets minFreq to 1
    }
};
```

---

Now let's step through a dry run. Capacity = 2, operations: `put(1,10)`, `put(2,20)`, `get(1)`, `put(3,30)`, `get(2)`.---

![alt text](image-1.png)

![alt text](image-2.png)

![alt text](image-3.png)

![alt text](image-4.png)

![alt text](image-5.png)

### LRU vs LFU — Complete Comparison

| | LRU | LFU |
|---|---|---|
| Evicts | Least recently used | Least frequently used |
| Tie-breaking | N/A — time is unique | LRU within same frequency |
| Data structure | HashMap + 1 DLL | HashMap + HashMap of DLLs |
| Complexity | O(1) get/put | O(1) get/put |
| Code complexity | Simple | Much harder |
| minFreq tracker | Not needed | Critical — tracks which bucket to evict from |
| Best for | Temporal locality (recent = relevant) | Frequency locality (popular = relevant) |
| Real use case | Browser cache, OS page cache | CDN cache, music streaming |

---

### The One Tricky Part — minFreq Update Rules

This is where most LFU implementations go wrong:

```cpp
// minFreq increases by 1 only when:
// the old freq bucket becomes EMPTY after touch
if (freqMap[oldFreq].empty() && minFreq == oldFreq)
    minFreq++;

// minFreq resets to 1 always when:
// a brand new key is inserted (new keys always start at freq=1)
minFreq = 1;  // on every new put
```

> New insertions always reset `minFreq` to 1 because the new node starts at frequency 1 — which is by definition the new minimum.

![alt text](<005 lru cache_240218_120443 (1)(12).jpg>) ![alt text](<005 lru cache_240218_120443 (1)(13).jpg>) ![alt text](<005 lru cache_240218_120443 (1)(14).jpg>) ![alt text](<005 lru cache_240218_120443 (1)(15).jpg>) ![alt text](<005 lru cache_240218_120443 (1)(16).jpg>) ![alt text](<005 lru cache_240218_120443 (1)(17).jpg>) ![alt text](<005 lru cache_240218_120443 (1)(18).jpg>)
