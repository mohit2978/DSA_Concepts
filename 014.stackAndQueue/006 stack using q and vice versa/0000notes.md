# Notes


## Stack using q

### Pop efficient pop() in O(1)

```cpp
class QueueStack {
    queue<int>q;
   // queue<int>helperQ;
public:
    QueueStack() {
    }
    
    void push(int x) {
        int s = q.size(); 
        q.push(x); 
        for (int i = 0; i < s; i++) {
            q.push(q.front()); 
            q.pop(); 
        }
    }
    
    int pop() {
        int val=q.front();
        q.pop();
        return val;
    }
    
    int top() {
        return q.front();
    }
    
    bool isEmpty() {
        return q.size()==0;
    }
};

```
here push takes O(n) time and pop takes O(1) time