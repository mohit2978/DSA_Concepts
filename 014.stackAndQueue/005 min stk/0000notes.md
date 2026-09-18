
## Q1 Remove Duplicate Letters
![alt text](<005min stk duplicate ltters trapping rain_231121_014732.jpg>)



![alt text](<005min stk duplicate ltters trapping rain_231121_014732(1).jpg>) ![alt text](<005min stk duplicate ltters trapping rain_231121_014732(2).jpg>) ![alt text](<005min stk duplicate ltters trapping rain_231121_014732(3).jpg>) ![alt text](<005min stk duplicate ltters trapping rain_231121_014732(4).jpg>) ![alt text](<005min stk duplicate ltters trapping rain_231121_014732(5).jpg>) 

## Q2 Smallest SUbsequence of Distinct characters

![alt text](<005min stk duplicate ltters trapping rain_231121_014732(6).jpg>)


## Q3 Min Stack


### Problem Statement — LeetCode 155. Min Stack (Medium)

Design a stack that supports push, pop, top, and retrieving the minimum element in **constant time**.

Implement the `MinStack` class:
- `MinStack()` initializes the stack object.
- `void push(int val)` pushes the element `val` onto the stack.
- `void pop()` removes the element on the top of the stack.
- `int top()` gets the top element of the stack.
- `int getMin()` retrieves the minimum element in the stack.

> You must implement a solution with **O(1) time complexity** for each function.

**Constraints:**
- `-2^31 <= val <= 2^31 - 1`
- Methods `pop`, `top` and `getMin` operations will always be called on **non-empty** stacks.
- At most `3 * 10^4` calls will be made to `push`, `pop`, `top`, and `getMin`.

---

### Example 1

**Input:**
```
["MinStack","push","push","push","getMin","pop","top","getMin"]
[[], [-2], [0], [-3], [], [], [], []]
```

**Output:**
```
[null, null, null, null, -3, null, 0, -2]
```

**Explanation:**
```cpp
MinStack minStack = new MinStack();
minStack.push(-2);
minStack.push(0);
minStack.push(-3);
minStack.getMin(); // return -3
minStack.pop();
minStack.top();    // return 0
minStack.getMin(); // return -2
```


```cpp
class MinStack {
public:
    stack<long long> st;
    long long min = 0;

    MinStack() {}

    void push(int val) {
        if (st.size() == 0) {
            st.push(val);
            min = val;
        } else {
            if (val < min) {
                st.push(val + (val - min));  // encoded value = 2*val - min
                min = val;
            } else {
                st.push(val);
            }
        }
    }

    void pop() {
        if (st.top() < min)
            min = min + (min - st.top());  // restore prevMin
        st.pop();
    }

    int top() {
        if (st.top() < min)
            return (int)min;
        return (int)st.top();
    }

    int getMin() {
        return (int)min;
    }
};
```

---


  ```Text

  val=2*currMin(from input)-prevMin(from min variable) (while adding)

prevMin=2*currMin(from min variablr)-val(from stack)(while top or delete)

```
##  My code

```cpp


class MinStack {
    long long min;
    stack<long long> stk;

   public:
    MinStack() { min = 0; }

    void push(int value) {
        if (stk.size() == 0) {
            stk.push(value);
            min = value;
            return;
        }
        if (value >= min)
            stk.push(value);
        else {
            stk.push(2 * value - min);
            min = value;
        }
    }

    void pop() {
        int val = stk.top();
        if (val >= min)
            stk.pop();
        else {
            int prevMin = 2 * min - val;
            stk.pop();
            min = prevMin;
        }
    }

    int top() {
        int val = stk.top();
        if (val >= min)
            return val;
        else {
            return min;
        }
    }

    int getMin() { return min; }
};
```

## Ai code
```cpp
class MinStack {
    long long min;
    stack<long long> stk;

public:
    MinStack() { 
        min = 0; // Ideally standard is to leave uninit or handle in logic
    }

    void push(int value) {
        long long val = (long long)value; // Cast to long long immediately
        
        if (stk.empty()) {
            stk.push(val);
            min = val;
            return;
        }
        
        if (val >= min) {
            stk.push(val);
        } else {
            // Encode: 2*x - min
            // We use 2LL to force long long arithmetic
            stk.push(2LL * val - min);
            min = val;
        }
    }

    void pop() {
        if (stk.empty()) return;

        long long val = stk.top(); // FIX: Use long long
        stk.pop();

        if (val < min) {
            // Decode: prevMin = 2*min - encoded_val
            // Because val < min, we know it's an encoded value
            min = 2LL * min - val;
        }
        // If val >= min, it was a normal push, min doesn't change
    }

    int top() {
        if (stk.empty()) return -1; 

        long long val = stk.top(); // FIX: Use long long
        
        if (val < min) {
            // If it's an encoded value, the 'real' top is current min
            return (int)min;
        }
        return (int)val;
    }

    int getMin() {
        return (int)min;
    }
};

```


  ### The Min Stack Math Trick ($O(1)$ Space)

This is a classic "Math Trick" used to solve the Min Stack problem with **$O(1)$ extra space**. Normally, you would use two stacks (one for values, one for minimums). To do it with one stack, we need to encode the previous minimum into the value we push, so we can retrieve it later when we pop.

Here is the breakdown of why $2x - min$ works.

---

### 1. The Goal
When we push a new value $x$ that is smaller than the current `min`, we have two problems:
1. We need to update the `min` to $x$.
2. We need to remember the old minimum (`prevMin`) so we can restore it when $x$ is eventually popped.

---

### 2. The Logic (Encoding)
If $x < min$, we don't push $x$. Instead, we push a **"modified value"**: x is currMin
$$Val = 2x - PrevMin$$

**Why this specific formula?**
* We know that $x < Prev_min$.
* Therefore, $x - Prev_min < 0$.
* If we add $x$ to both sides, we get: $2x - Prev_min < x$.
* Since we update the current `min` to become $x$, this inequality means:
> The value stored on the stack ($2x - prevMin$) is **always LESS THAN** the current `min` ($x$).

This creates a **"Flag"**: whenever `stack.top() < min`, we know that the current node is a minimum value, and the stack actually holds an encoded value.

---

So point is while adding we set min=x but on stack we get even smaller value that means its encoded value!!



### 3. The Retrieval (Decoding)
When we pop a value `val` from the stack:

* **Case A: `val >= min`**
    * This is a normal value. The minimum didn't change when this was pushed.
    * Just pop it.
* **Case B: `val < min` (The Magic Case)**
    * This means `val` is the encoded value we pushed earlier.
    * The actual value we are popping is the current `min`.
    * **Restoring the Previous Min:**
        We know the formula was: $val = 2x - prevMin$
        Since $x$ is the current `min`, we can write: $val = 2 \cdot min - prevMin$
        Rearranging to find `prevMin`:
        $$prevMin = 2 \cdot min - val$$

---

### 4. Dry Run Example
Let's trace: **Push 3, Push 5, Push 2, Push 1**.

| Operation | Value ($x$) | Current min (Before) | Check ($x < min$?) | Stack Pushes | New min |
| :--- | :--- | :--- | :--- | :--- | :--- |
| **Push 3** | 3 | $\infty$ | Yes | 3 (First element) | 3 |
| **Push 5** | 5 | 3 | No | 5 | 3 |
| **Push 2** | 2 | 3 | Yes | $2(2) - 3 = \mathbf{1}$ | 2 |
| **Push 1** | 1 | 2 | Yes | $2(1) - 2 = \mathbf{0}$ | 1 |

**Stack Status:** `[3, 5, 1, 0]` (Top is 0). `min` is 1.

**Now let's POP:**
1.  **Pop Top (0):**
    * Check: $0 < min$ ($0 < 1$)? **Yes.**
    * This is a special node! Actual Value = `min` (1).
    * Restore Old Min: $2(1) - 0 = \mathbf{2}$.
2.  **Pop Top (1):**
    * Check: $1 < min$ ($1 < 2$)? **Yes.**
    * This is a special node! Actual Value = `min` (2).
    * Restore Old Min: $2(2) - 1 = \mathbf{3}$.
3.  **Pop Top (5):**
    * Check: $5 < min$? **No.**
    * Normal pop. `min` remains 3.

---

### Summary
We use **$2x - min$** because it guarantees the stored value is always smaller than the new minimum, acting as a flag that tells us: *"Stop! You need to rollback the minimum here."*







