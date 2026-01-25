# Notes

## Stack using LL basic using ll class

```java

class LinkedListStack {
    LinkedList<Integer>ll;
    public LinkedListStack() {
        ll=new LinkedList<>();
    }

    public void push(int x) {
       ll.addFirst(x);
    }

    
    public int pop() {
        int val=this.top();
      ll.removeFirst();
      return val;
    }

    public int top() {
       return ll.getFirst();
    }

    public boolean isEmpty() {
        return ll.size()==0;
    }
}

```
## Queue using ll using ll class

```java

class LinkedListQueue {
    LinkedList<Integer>ll;
    public LinkedListQueue() {
        ll=new LinkedList<>();
    }

    public void push(int x) {
       ll.addLast(x);
    }

    public int pop() {
        int val=this.peek();
      ll.removeFirst();
      return val;
    }

    public int peek() {
       return ll.getFirst();
    }

    public boolean isEmpty() {
        return ll.size()==0;
    }
}

```

Now we need to put these functions ourself!!
```java
    ListNode th = null, tt = null;

    private void addFirst(ListNode node) {
        if (th == null)
            th = tt = node;
        else {
            node.next = th;
            th = node;
        }
    }

    public void addLast(int val) {
        Node node = new Node(val);
        if (th== null)
            th= tt = node;
        else {
            tt.next = node;
            tt= node;
        }
    }

int removeFirst() {
    if (th == nullptr) return -1; // Stack is empty

    ListNode* temp = th;
    int val = temp->val;

    if (th == tt) { 
        // Case: Only one node exists
        th = tt = nullptr;
    } else {
        // Case: Multiple nodes exist
        th = th->next;
    }

    temp->next = nullptr; 
    delete temp; // Always free the memory
    size--;      // Always decrement size
    return val;
}

```



## Stack using LL

```cpp

struct ListNode{
        int val;
        ListNode * next;
        ListNode(int x){
            this->next=nullptr;
            this->val=x;
        }
    };
class LinkedListStack {
    ListNode* th;
    ListNode *tt;
    int size;
    void addFirst(ListNode* node) {
        if (th == nullptr)
            {
                th=node;
                tt=node;
            }
        else {
            node->next = th;
            th = node;
        }
        size++;
    }

    int getFirst(){
        return th->val;
    }
int removeFirst() {
    if (th == nullptr) return -1; // Stack is empty

    ListNode* temp = th;
    int val = temp->val;

    if (th == tt) { 
        // Case: Only one node exists
        th = tt = nullptr;
    } else {
        // Case: Multiple nodes exist
        th = th->next;
    }

    temp->next = nullptr; 
    delete temp; // Always free the memory
    size--;      // Always decrement size
    return val;
}
    int sizeFun(){
        return size;
    }
public:
    LinkedListStack() {
        th=tt=nullptr;
        this->size=0;
    }
    
    void push(int x) {
        addFirst(new ListNode(x));
    }
    
    int pop() {
        return removeFirst();
    }
    
    int top() {
        if(isEmpty()==true) return -1;
        return getFirst();
    }
    
    bool isEmpty() {
        return sizeFun()==0;
    }
};
```
This  is correct code which we get after discussion with AI
### First submission
```cpp

struct ListNode{
        int val;
        ListNode * next;
        ListNode(int x){
            this->next=nullptr;
            this->val=x;
        }
    };
class LinkedListStack {
    ListNode* th;
    ListNode *tt;
    int size;
    void addFirst(ListNode* node) {
        if (th == nullptr)
            {
                th=node;
                tt=node;
            }
        else {
            node->next = th;
            th = node;
        }
        size++;
    }

    int getFirst(){
        return th->val;
    }
    int removeFirst(){
        if(th==nullptr) return -1;
        int val=th->val;
        ListNode * temp=th;
        th=th->next;
        temp->next=nullptr;
        delete(temp);
        size--;
        return val;
    }
    int sizeFun(){
        return size;
    }
public:
    LinkedListStack() {
        th=tt=nullptr;
        this->size=0;
    }
    
    void push(int x) {
        addFirst(new ListNode(x));
    }
    
    int pop() {
        return removeFirst();
    }
    
    int top() {
        return getFirst();
    }
    
    bool isEmpty() {
        return sizeFun()==0;
    }
};
```
This removeFirst makes `tt` dahngling if ll has only 1 node and we delete that so

```cpp
    int removeFirst(){
        if(th==nullptr) return -1;
        int val=th->val;
         size--;
        if(th==tt){
            th=tt=nullptr;
            return val;
        }
        ListNode * temp=th;
        th=th->next;
        temp->next=nullptr;
        delete(temp);
        return val;
    }
```
i modified but ai said now 

### The Memory Leak
In your new if(th == tt) block, you set the pointers to nullptr and return the value immediately. You never call delete on that last node, and you never decrement size. Over time, this will consume unnecessary memory.

So we get that so ai code

```cpp
int removeFirst() {
    if (th == nullptr) return -1; // Stack is empty

    ListNode* temp = th;
    int val = temp->val;

    if (th == tt) { 
        // Case: Only one node exists
        th = tt = nullptr;
    } else {
        // Case: Multiple nodes exist
        th = th->next;
    }

    temp->next = nullptr; 
    delete temp; // Always free the memory
    size--;      // Always decrement size
    return val;
}
```

## Queue using LL


```cpp
struct ListNode{
        int val;
        ListNode * next;
        ListNode(int x){
            this->next=nullptr;
            this->val=x;
        }
};

class LinkedListQueue {
    ListNode* th;
    ListNode *tt;
    int size;
    void addLast(int val) {
        ListNode* node = new ListNode(val);
        if (th== nullptr)
            th= tt = node;
        else {
            tt->next = node;
            tt= node;
        }
        size++;
    }
int removeFirst() {
    if (th == nullptr) return -1; // Stack is empty

    ListNode* temp = th;
    int val = temp->val;

    if (th == tt) { 
        // Case: Only one node exists
        th = tt = nullptr;
    } else {
        // Case: Multiple nodes exist
        th = th->next;
    }

    temp->next = nullptr; 
    delete temp; // Always free the memory
    size--;      // Always decrement size
    return val;
}

    int getLast(){
        if(size==0) return -1;
        return th->val;
    }
public:
    LinkedListQueue() {
        th=tt=nullptr;
        this->size=0;
    }
    
    void push(int x) {
        addLast(x);
    }
    
    int pop() {
        return removeFirst();
    }
    
    int peek() {
        return getLast();
    }
    
    bool isEmpty() {
        return size==0;
    }
};
```

Atlast can also add a destructor 

```cpp

~LinkedListQueue() {
        while (th != nullptr) {
            ListNode* temp = th;
            th = th->next;
            delete temp;
        }
        tt = nullptr;
        size = 0;
    }
```    



