# Notes
![alt text](<005 lru cache_240218_120443 (1).jpg>)

![alt text](<005 lru cache_240218_120443 (1)(1).jpg>) 
![alt text](<005 lru cache_240218_120443 (1)(2).jpg>)
 ![alt text](<005 lru cache_240218_120443 (1)(3).jpg>) 
 ![alt text](<005 lru cache_240218_120443 (1)(4).jpg>) ![alt text](<005 lru cache_240218_120443 (1)(5).jpg>) ![alt text](<005 lru cache_240218_120443 (1)(6).jpg>) 

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

Great question — let me build the intuition from scratch.

---

### What Operations LRU Cache Needs

```
get(key)  → find value by key         must be O(1)
            mark as recently used      must be O(1)

put(key)  → insert or update           must be O(1)
            evict LRU if full          must be O(1)
```

ALL four operations must be **O(1)**. This constraint drives everything.

---

### Try Each Structure Alone — See Why It Fails

---

#### Only HashMap

```
get(key) → O(1) ✅  perfect for lookup

but...

"mark as recently used" — how?
"find least recently used" — how?

HashMap has NO concept of order
it's just key→value pairs
no way to know which was used least recently ❌
```

---

#### Only Array

```
idea: keep array sorted by usage
most recent at front, LRU at back

get(key):
  scan array to find key → O(n) ❌ too slow

evict LRU:
  remove last element → O(1) ✅

"mark recently used":
  find element → O(n) ❌
  move to front → O(n) shift ❌
```

---

#### Only Linked List

```
get(key):
  scan from head to find key → O(n) ❌

evict LRU:
  remove tail → O(1) ✅

"mark recently used":
  move node to head → O(1) IF you have the pointer ✅
  but FINDING the node is O(n) ❌
```

---

#### Only Queue / Stack

```
Queue naturally tracks order
but no O(1) lookup by key ❌
no O(1) removal from middle ❌
```

---

### The Problem is Always Two Things

```
Every structure fails because the problem needs TWO things:

1. FAST LOOKUP by key        → need key→value mapping
2. FAST ORDER TRACKING       → need to know who was used least recently
                               AND be able to move things around quickly
```

No single structure does both. So combine two.

---

### Why HashMap Specifically

```
HashMap gives:
  key → node pointer         O(1) lookup ✅
  key → node pointer         O(1) insert ✅
  key → node pointer         O(1) delete ✅

The VALUE stored is not just the cache value
it's a POINTER to the node in the linked list

so HashMap answers: "where is this key in the list?"
in O(1) time
```

---

### Why Doubly Linked List Specifically

```
Need to track ORDER of usage:
  most recently used → head
  least recently used → tail (evict from here)

Need to MOVE a node to head when accessed:
  this requires removing it from current position
  and inserting at head

Removing from middle of list needs:
  pointer to prev node   ← why DOUBLY linked
  pointer to next node   ← why DOUBLY linked

  node.prev.next = node.next   // bypass node
  node.next.prev = node.prev   // bypass node
  → O(1) removal ✅

Singly linked list CANNOT remove from middle in O(1)
because you don't know the prev node ❌
```

---

### Why Not Other Ordered Structures

```
TreeMap / Balanced BST:
  ordered ✅
  but O(log n) operations ❌  not fast enough

Array with timestamps:
  store last-used time with each entry
  find minimum timestamp = O(n) ❌

Deque:
  O(1) at both ends ✅
  but O(n) removal from middle ❌

Doubly Linked List:
  O(1) removal from middle ✅ (with pointer)
  O(1) insert at head ✅
  O(1) remove from tail ✅
  maintains order ✅
```

---

### How They Work Together

```
HashMap stores:      key → pointer to Node in list
LinkedList stores:   Nodes in order of usage

GET operation:
  HashMap finds the node in O(1)     ← HashMap's job
  LinkedList moves it to head O(1)   ← LinkedList's job

PUT operation (new key):
  Create node, add to head of list   ← LinkedList's job
  Store key→node in HashMap          ← HashMap's job
  If full: remove tail node          ← LinkedList's job
           remove key from HashMap   ← HashMap's job

Every single step = O(1) ✅
```

---

### The Perfect Analogy

Think of a **library with a special shelf:**

```
HashMap  =  card catalog
            "which shelf position is this book?"
            instant lookup by title

Doubly Linked List  =  the shelf itself
            books arranged by recently used
            most recent at left end
            least recent at right end
            any book can be pulled out and
            moved to left end instantly
            (because each book knows its
             left AND right neighbour)

Together:
  "get book X"  → catalog tells you exact position O(1)
                → pull it out and put at left end  O(1)

  "no space"    → throw out rightmost book         O(1)
                → remove from catalog              O(1)
```

---

### Summary

| Need | Why | Structure |
|---|---|---|
| Find key instantly | scan would be O(n) | HashMap |
| Track usage order | know who's LRU | Doubly Linked List |
| Remove from middle | need prev AND next pointer | **Doubly** (not singly) linked |
| Move to front | reorder after access | Linked List head insert |
| Evict LRU | always remove oldest | Linked List tail remove |

```
HashMap alone     → fast lookup, no order      ❌
LinkedList alone  → has order, slow lookup     ❌
HashMap + DLL     → fast lookup + fast order   ✅ O(1) everything
```

The combination is not arbitrary — each structure covers **exactly the weakness** of the other.

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


## LRU Cache — Two Implementations Compared

### The Core Difference in One Line

```
Code 1 (yours):  uses DUMMY head and tail nodes
Code 2:          uses REAL head and tail, handles edge cases manually
```

---

### Side by Side Comparison

#### Constructor

**Code 1 — dummy nodes:**
```java
head = new Node(-1, -1);   // dummy head
tail = new Node(-2, -2);   // dummy tail
head.next = tail;
tail.prev = head;
```

**Code 2 — no dummies:**
```java
// head and tail start as null
// no pre-wiring needed
```

---

#### removeNode

**Code 1 — always clean, no edge cases:**
```java
private void removeNode(Node node) {
    Node prevNode = node.prev;
    Node nextNode = node.next;
    prevNode.next = nextNode;    // always works — prev is at worst dummy head
    nextNode.prev = prevNode;    // always works — next is at worst dummy tail
    node.next = null;
    node.prev = null;
    llSize--;
}
```

**Code 2 — must handle every edge case manually:**
```java
private void removeNode(Node node) {
    if (this.linkedListSize == 1)           // only one node
        this.head = this.tail = null;
    else if (this.head == node) {           // removing head
        Node prevNode = node.prev;
        prevNode.next = node.prev = null;
        this.head = prevNode;
    } else if (this.tail == node) {         // removing tail
        Node nextNode = node.next;
        nextNode.prev = node.next = null;
        this.tail = nextNode;
    } else {                                // middle node
        Node prevNode = node.prev;
        Node nextNode = node.next;
        prevNode.next = nextNode;
        nextNode.prev = prevNode;
        node.prev = node.next = null;
    }
    this.linkedListSize--;
}
```

This is the **biggest difference**. Code 1 eliminates all 4 cases with dummy nodes.

---

#### addFirst

**Code 1 — always clean:**
```java
private void addFirst(Node node) {
    Node nextNode = head.next;    // head is always dummy, never null
    node.prev = head;
    node.next = nextNode;
    nextNode.prev = node;
    head.next = node;
    llSize++;
}
```

**Code 2 — must handle empty list:**
```java
private void addFirst(Node node) {
    if (this.head == null)              // empty list edge case
        this.head = this.tail = node;
    else {
        this.head.next = node;
        node.prev = this.head;
        this.head = node;
    }
    this.linkedListSize++;
}
```

---

#### put — eviction logic

**Code 1:**
```java
if (mp.size() > this.cap) {
    Node lruNode = this.tail.prev;   // tail.prev = LRU (tail is dummy)
    removeNode(lruNode);
    mp.remove(lruNode.key);
}
```

**Code 2:**
```java
if (map.size() > this.capacity) {
    Node tail = this.tail;           // tail itself = LRU (no dummy)
    removeNode(tail);
    map.remove(tail.key);
}
```

---

### Bug in Code 2 ⚠️

```java
// Code 2 addFirst — head points to MRU
this.head.next = node;
node.prev = this.head;
this.head = node;
```

Wait — this means head = most recently used. But in removeNode:

```java
else if (this.head == node) {
    Node prevNode = node.prev;      // head.prev — but head is MRU
    prevNode.next = node.prev = null;
    this.head = prevNode;
}
```

The direction is **reversed from Code 1**. Code 2 uses:

```
head = MRU (most recent)
tail = LRU (least recent, evict this)
```

Code 1 uses:

```
head.next = MRU  (dummy head → first real node = most recent)
tail.prev = LRU  (last real node → dummy tail = least recent)
```

Both are valid — just opposite conventions. Easy to get confused when reading.

---

### Complete Comparison Table

| Feature | Code 1 (dummy nodes) | Code 2 (real head/tail) |
|---|---|---|
| Dummy nodes | ✅ yes | ❌ no |
| removeNode cases | 1 case always | 4 cases (empty/head/tail/middle) |
| addFirst cases | 1 case always | 2 cases (empty/non-empty) |
| Null pointer risk | ✅ none | ⚠️ must handle carefully |
| Code length | shorter | longer |
| Bug surface area | small | larger |
| Interview preferred | ✅ yes | harder to get right |
| Head = | dummy | MRU node |
| Tail = | dummy | LRU node |
| LRU node | `tail.prev` | `tail` |

---

### The Dummy Node Trick — Why It's Superior

```
Without dummies — 4 cases in removeNode:
  1. list has 1 node
  2. removing head
  3. removing tail
  4. removing middle

With dummies — always 1 case:
  every real node always has a valid prev (at worst = dummy head)
  every real node always has a valid next (at worst = dummy tail)
  no null checks ever needed

This is a classic linked list trick worth memorising
applies to any doubly linked list problem
```

---

### Verdict

```
Code 1  →  cleaner, safer, interview recommended
            dummy nodes eliminate all edge cases
            removeNode is 6 lines vs 15 lines

Code 2  →  more verbose, more bug-prone
            valid but harder to write correctly under pressure
            the 4-case removeNode is easy to mess up in interviews
```

> If you're ever implementing a doubly linked list from scratch — **always use dummy head and tail**. It makes every operation uniform and eliminates null checks entirely.

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
