# Notes

![alt text](<001stack queue cons adapters_231121_163402.jpg>)
![alt text](<001stack queue cons adapters_231121_163402(1).jpg>)

```java
public class stack {
    private int[] arr;
    private int tos;
    private int NoOfElements;
    private int MaxCapacity;

    protected void intialize(int size) {
        this.arr = new int[size];
        this.tos = -1;
        this.NoOfElements = 0;
        this.MaxCapacity = size;
    }

    public stack() {
        intialize(10);
    }

    public stack(int size) {
        intialize(size);
    }

    protected int Capacity() {
        return this.MaxCapacity;
    }

    public int size() {
        return this.NoOfElements;
    }

    public boolean isEmpty() {
        return this.NoOfElements == 0;
    }

    protected void StackEmptyException() throws Exception {
        if (this.NoOfElements == 0)
            throw new Exception("StackISEmpty");
    }

    protected void StackOverflowException() throws Exception {
        if (this.NoOfElements == this.MaxCapacity)
            throw new Exception("StackOverflow");
    }

    protected void push_(int data){
        this.arr[++this.tos] = data;
        this.NoOfElements++;
    }

    public void push(int data) throws Exception{
        StackOverflowException();
        push_(data);
    }

    protected int top_() {
        return this.arr[this.tos];
    }

    public int top() throws Exception {
        StackEmptyException();
        return top_();
    }

    protected int pop_(){
        int rv = this.arr[this.tos];
        this.arr[this.tos] = 0;
        this.tos--;
        this.NoOfElements--;

        return rv;
    }

    public int pop() throws Exception{
        StackEmptyException();
        return pop_();
    }
}

```

 ![alt text](<001stack queue cons adapters_231121_163402(2).jpg>) 
 ![alt text](<001stack queue cons adapters_231121_163402(3).jpg>) 

## Simple stack in cpp

```cpp
using namespace std;

class stack
{
private:
    int *arr;
    int tos;
    int NoOfElements;
    int MaxCapacity;

protected:
    void intialize(int size)
    {
        this->arr = new int[size];
        this->tos = -1;
        this->NoOfElements = 0;
        this->MaxCapacity = size;
    }

    void StackEmptyException()
    {
        if (this->NoOfElements == 0)
            throw("StackISEmpty");
    }

    void StackOverflowException()
    {
        if (this->NoOfElements == this->MaxCapacity)
            throw("StackOverflow");
    }

    void push_(int data)
    {
        this->arr[++this->tos] = data;
        this->NoOfElements++;
    }

    int top_()
    {
        return this->arr[this->tos];
    }

    int pop_()
    {
        int rv = this->arr[this->tos];
        this->arr[this->tos] = 0;
        this->tos--;
        this->NoOfElements--;

        return rv;
    }

public:
    int size()
    {
        return this->NoOfElements;
    }

    bool isEmpty()
    {
        return this->NoOfElements == 0;
    }

    void push(int data)
    {
        StackOverflowException();
        push_(data);
    }

    int top()
    {
        StackEmptyException();
        return top_();
    }

    int pop()
    {
        StackEmptyException();
        return pop_();
    }
};

class dynamicStack : stack
{
};

```

 ![alt text](<001stack queue cons adapters_231121_163402(4).jpg>) 

## Dynamic stack

 ```cpp

public class dynamicStack extends stack {

    public dynamicStack() {
        super();
    }

    public dynamicStack(int size) {
        super(size);
    }

    public dynamicStack(int[] arr) {
        int n = arr.length;
        super.intialize(2 * n);

        for (int ele : arr)
            super.push_(ele);
    }

    @Override
    public void push(int data) throws Exception{
        if (super.size() == super.Capacity()) {
            int n = super.size();
            int[] temp = new int[n];
            int i = n - 1;
            while (super.size() != 0)
                temp[i--] = super.pop_();

            super.intialize(2 * n);

            for (int ele : temp)
                super.push_(ele);
        }

        super.push(data);
    }

}
 ```


 ![alt text](<001stack queue cons adapters_231121_163402(5).jpg>) 
 ![alt text](<001stack queue cons adapters_231121_163402(6).jpg>) 
 ![alt text](<001stack queue cons adapters_231121_163402(7).jpg>) 
 
```java

public class stack {
    private class ListNode {
        int data = 0;
        ListNode next = null;

        public ListNode(int data) {
            this.data = data;
        }
    }

    private ListNode head = null;
    private ListNode tail = null;
    private int NoOfElements = 0;

    private void addFirst(ListNode node) {
        if (this.head == null) {
            this.head = node;
            this.tail = node;
        } else {
            node.next = this.head;
            this.head = node;
        }
    }

    private ListNode removeFirst() {
        ListNode rn = this.head;
        if (this.head == this.tail) {
            this.head = null;
            this.tail = null;
        } else {
            this.head = rn.next;
        }

        rn.next = null;
    }

    public int size() {
        return this.NoOfElements;
    }

    public boolean isEmpty() {
        return this.NoOfElements == 0;
    }

    protected void StackEmptyException() throws Exception {
        if (this.NoOfElements == 0)
            throw new Exception("StackISEmpty");
    }

    public void push(int data) {
        ListNode node = new ListNode(data);
        addFirst(node);
        this.NoOfElements++;
    }

    protected int top_() {
        return this.head.data;
    }

    public int top() throws Exception{
        StackEmptyException();
        return top_();
    }

    protected int pop_(){
       ListNode node = removeFirst();
       this.NoOfElements--;
       return node.data;
    }

    public int pop() throws Exception{
        StackEmptyException();
        return pop_();
    }

}
```


 ![alt text](<001stack queue cons adapters_231121_163402(8).jpg>) 
 ![alt text](<001stack queue cons adapters_231121_163402(9).jpg>) 

```java
public class queue {
    private class ListNode {
        int data = 0;
        ListNode next = null;

        public ListNode(int data) {
            this.data = data;
        }
    }

    private ListNode head = null;
    private ListNode tail = null;
    private int NoOfElements = 0;

    private void addLast(ListNode node) {
        if (this.head == null) {
            this.head = node;
            this.tail = node;
        } else {
            this.tail.next = node;
            this.tail = node;
        }
    }

    private ListNode removeFirst() {
        ListNode rn = this.head;
        if (this.head == this.tail) {
            this.head = null;
            this.tail = null;
        } else {
            this.head = rn.next;
        }

        rn.next = null;
    }

    public int size() {
        return this.NoOfElements;
    }

    public boolean isEmpty() {
        return this.NoOfElements == 0;
    }

    protected void QueueEmptyException() throws Exception {
        if (this.NoOfElements == 0)
            throw new Exception("QueueISEmpty");
    }

    public void push(int data) {
        ListNode node = new ListNode(data);
        addLast(node);
        this.NoOfElements++;
    }

    protected int top_() {
        return this.head.data;
    }

    public int top() throws Exception{
        QueueEmptyException();
        return top_();
    }

    protected int pop_(){
       ListNode node = removeFirst();
       this.NoOfElements--;
       return node.data;
    }

    public int pop() throws Exception{
        QueueEmptyException();
        return pop_();
    }

}

```

 ![alt text](<001stack queue cons adapters_231121_163402(10).jpg>)
![alt text](<001stack queue cons adapters_231121_163402(11).jpg>)

```java

public class queue {
    private int[] arr;
    private int NoOfElements;
    private int MaxCapacity;
    private int front;
    private int back;

    protected void intialize(int size) {
        this.arr = new int[size];
        this.front = this.back = 0;
        this.NoOfElements = 0;
        this.MaxCapacity = size;
    }

    public queue() {
        intialize(10);
    }

    public queue(int size) {
        intialize(size);
    }

    protected int Capacity() {
        return this.MaxCapacity;
    }

    public int size() {
        return this.NoOfElements;
    }

    public boolean isEmpty() {
        return this.NoOfElements == 0;
    }

    public void display() {
        
        for (int i = 0; i < this.NoOfElements; i++) {
            int idx = (this.front + i) % this.MaxCapacity;
            System.out.print(this.arr[idx] + " ");
        }

    }

    protected void QueueEmptyException() throws Exception {
        if (this.NoOfElements == 0)
            throw new Exception("QueueISEmpty");
    }

    protected void QueueOverflowException() throws Exception {
        if (this.NoOfElements == this.MaxCapacity)
            throw new Exception("QueueOverflow");
    }

    protected void push_(int data) {
        this.arr[this.back] = data;
        this.back = (++this.back % this.MaxCapacity);
        this.NoOfElements++;
    }

    public void push(int data) throws Exception {
        QueueOverflowException();
        push_(data);
    }

    protected int front_() {
        return this.arr[this.front];
    }

    public int front() throws Exception {
        QueueEmptyException();
        return front_();
    }

    protected int pop_() {
        int rv = this.arr[this.front];
        this.arr[this.front] = 0;
        this.front = (++this.front % this.MaxCapacity);
        this.NoOfElements--;

        return rv;
    }

    public int pop() throws Exception {
        QueueEmptyException();
        return pop_();
    }

}
```

![alt text](<001stack queue cons adapters_231121_163402(12).jpg>) ![alt text](<001stack queue cons adapters_231121_163402(13).jpg>) ![alt text](<001stack queue cons adapters_231121_163402(14).jpg>) ![alt text](<001stack queue cons adapters_231121_163402(15).jpg>)
