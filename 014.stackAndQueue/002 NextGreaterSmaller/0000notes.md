# Notes
![alt text](<002Nger l Nser l range count_231121_163402.jpg>)

![alt text](<002Nger l Nser l range count_231121_163402(1).jpg>) 

---

## Next greater smaller

```java
import java.util.Stack;
import java.util.ArrayDeque;

public class question {

    // N : Next, G = greater, S : Smaller, L : Left, R : Right
    public static void NGOR(int[] arr, int[] ans) {
        int n = arr.length;
        Arrays.fill(ans, n); // Java : Arrays.fill(ans,n);

        Stack<Integer> st = new Stack<>();
        for (int i = 0; i < n; i++) {
            while (st.length != 0 && arr[st.peek()] < arr[i]) {
                ans[st.pop()] = i;
            }
            st.push(i);
        }
    }

    public static void NGOL(int[] arr, int[] ans) {
        int n = arr.length;
        Arrays.fill(ans, -1); // Java : Arrays.fill(ans,-1);

        Stack<Integer> st = new Stack<>();
        for (int i = n - 1; i >= 0; i--) {
            while (st.length != 0 && arr[st.peek()] < arr[i]) {
                ans[st.pop()] = i;
            }
            st.push(i);
        }
    }

    public static void NSOR(int[] arr, int[] ans) {
        int n = arr.length;
        Arrays.fill(ans, n); // Java : Arrays.fill(ans,n);

        Stack<Integer> st = new Stack<>();
        for (int i = 0; i < n; i++) {
            while (st.length != 0 && arr[st.peek()] > arr[i]) {
                ans[st.pop()] = i;
            }
            st.push(i);
        }
    }

    public static void NSOL(int[] arr, int[] ans) {
        int n = arr.length;
        Arrays.fill(ans, -1); // Java : Arrays.fill(ans,-1);

        Stack<Integer> st = new Stack<>();
        for (int i = n - 1; i >= 0; i--) {
            while (st.length != 0 && arr[st.peek()] > arr[i]) {
                ans[st.pop()] = i;
            }
            st.push(i);
        }
    }
}   

```

## Cpp

```c++

#include <iostream>
#include <stack>
#include <vector>

using namespace std;

// N : Next, G = greater, S : Smaller, L : Left, R : Right
void NGOR(vector<int> &arr, vector<int> &ans)
{
    int n = arr.size();
    ans.resize(n, n); //Java :  Arrays.fill(ans,n);

    stack<int> st;
    for (int i = 0; i < n; i++)
    {
        while (st.size() != 0 && arr[st.top()] < arr[i])
        {
            ans[st.top()] = i;
            st.pop();
        }
        st.push(i);
    }
}

void NGOL(vector<int> &arr, vector<int> &ans)
{
    int n = arr.size();
    ans.resize(n, -1); //Java :  Arrays.fill(ans,-1);

    stack<int> st;
    for (int i = n - 1; i >= 0; i--)
    {
        while (st.size() != 0 && arr[st.top()] < arr[i])
        {
            ans[st.top()] = i;
            st.pop();
        }
        st.push(i);
    }
}

void NSOR(vector<int> &arr, vector<int> &ans)
{
    int n = arr.size();
    ans.resize(n, n); //Java :  Arrays.fill(ans,n);

    stack<int> st;
    for (int i = 0; i < n; i++)
    {
        while (st.size() != 0 && arr[st.top()] > arr[i])
        {
            ans[st.top()] = i;
            st.pop();
        }
        st.push(i);
    }
}

void NSOL(vector<int> &arr, vector<int> &ans)
{
    int n = arr.size();
    ans.resize(n, -1); //Java :  Arrays.fill(ans,-1);

    stack<int> st;
    for (int i = n - 1; i >= 0; i--)
    {
        while (st.size() != 0 && arr[st.top()] > arr[i])
        {
            ans[st.top()] = i;
            st.pop();
        }
        st.push(i);
    }
}

```

# Understanding Monotonic Stacks

A **Monotonic Stack** is a specialized stack data structure that maintains elements in a specific sorted order (either increasing or decreasing) at all times. When a new element is added that would violate this order, you must "pop" existing elements until the order is restored.

---

### 1. Monotonically Increasing Stack
In an increasing stack, every element is **larger than (or equal to)** the element below it.

* **Rule:** Before pushing element $X$, pop all elements $Y$ such that $Y > X$.
* **Final State (Bottom to Top):** `[1, 3, 5, 8]`
* **Primary Use:** Finding the **Next Smaller Element**. Because the stack "kicks out" larger elements, the element left sitting below $X$ is the first value to its left that is smaller than it.



#### Dry Run Example
Array: `[5, 2, 7, 4]`
1.  **Push 5:** Stack is empty. Stack: `[5]`
2.  **Push 2:** $2 < 5$. Pop `5`. Stack: `[2]`
3.  **Push 7:** $7 > 2$. Push `7`. Stack: `[2, 7]`
4.  **Push 4:** $4 < 7$. Pop `7`. Stack: `[2, 4]`

---

### 2. Monotonically Decreasing Stack
In a decreasing stack, every element is **smaller than (or equal to)** the element below it.

* **Rule:** Before pushing element $X$, pop all elements $Y$ such that $Y < X$.
* **Final State (Bottom to Top):** `[10, 8, 6, 2]`
* **Primary Use:** Finding the **Next Greater Element**. The stack "kicks out" smaller elements, so the element $X$ eventually sits on top of is the first value to its left that is larger than it.



#### Dry Run Example
Array: `[3, 8, 2, 5]`
1.  **Push 3:** Stack is empty. Stack: `[3]`
2.  **Push 8:** $8 > 3$. Pop `3`. Stack: `[8]`
3.  **Push 2:** $2 < 8$. Push `2`. Stack: `[8, 2]`
4.  **Push 5:** $5 > 2$. Pop `2`. Stack: `[8, 5]`

---

### 3. Summary Table

| Stack Type | Order (Bottom to Top) | Pop Condition | Used to find... |
| :--- | :--- | :--- | :--- |
| **Increasing** | `[1, 2, 5, 9]` | `Stack.top() > Current` | Next **Smaller** Element |
| **Decreasing** | `[9, 5, 2, 1]` | `Stack.top() < Current` | Next **Greater** Element |

---

### 4. The "Challenger" Analogy
Think of the current element as a **challenger** trying to find a place in the stack:

* **In an Increasing Stack:** The challenger wants to find smaller values to stand on. It "fights" (pops) anyone taller than itself until it finds someone shorter.
* **In a Decreasing Stack:** The challenger is looking for taller values to hide behind. It "fights" (pops) anyone shorter than itself until it finds someone taller.



### 5. Complexity
* **Time Complexity:** $O(N)$ — Every element is pushed and popped exactly once.
* **Space Complexity:** $O(N)$ — In the worst case (already sorted array), all elements stay in the stack.
---


# Monotonic Stack: Next Greater/Smaller Element Logic

This collection of functions implements the **Monotonic Stack** pattern. This pattern is used to find the first element that satisfies a comparison condition (greater or smaller) to the left or right of every element in an array in linear time.

>The core idea is to maintain a monotonic stack (a stack where elements are always in increasing or decreasing order). When a new element breaks the order, we have found the "answer" for the elements currently in the stack.

---

### 1. Function Overview Matrix

| Function | Name | Search Direction | Comparison | Default Value (Boundary) |
| :--- | :--- | :--- | :--- | :--- |
| **NGOR** | Next Greater on Right | Left to Right | `arr[top] < arr[curr]` | `n` (Right Boundary) |
| **NGOL** | Next Greater on Left | Right to Left | `arr[top] < arr[curr]` | `-1` (Left Boundary) |
| **NSOR** | Next Smaller on Right | Left to Right | `arr[top] > arr[curr]` | `n` (Right Boundary) |
| **NSOL** | Next Smaller on Left | Right to Left | `arr[top] > arr[curr]` | `-1` (Left Boundary) |

---

### 2. Detailed Logic Explanation

#### Next Greater on Right (NGOR)
Finds the first index `j > i` such that `arr[j] > arr[i]`.
* **Mechanism**: As we iterate forward, the current element `arr[i]` "challenges" elements in the stack. If `arr[i]` is greater than the element at the stack's top index, then `i` is the answer for that index. 
* **Stack Property**: The stack remains **monotonically decreasing** (bottom to top).



#### Next Greater on Left (NGOL)
Finds the first index `j < i` such that `arr[j] > arr[i]`.
* **Mechanism**: We iterate **backwards**. The current element `arr[i]` (which is to the left of the items in the stack) acts as the potential "Greater" element for the items we've already passed.
* **Stack Property**: The stack remains monotonically decreasing.

#### Next Smaller on Right (NSOR)
Finds the first index `j > i` such that `arr[j] < arr[i]`.
* **Mechanism**: Similar to NGOR, but the current element `arr[i]` "challenges" the stack to see if it is **smaller**.
* **Stack Property**: The stack remains **monotonically increasing**.



#### Next Smaller on Left (NSOL)
Finds the first index `j < i` such that `arr[j] < arr[i]`.
* **Mechanism**: Iterates backwards to find the first smaller value to the left.
* **Stack Property**: The stack remains monotonically increasing.

---

### 3. Complexity Analysis

* **Time Complexity**: $O(n)$
    * Each element is pushed onto the stack exactly once.
    * Each element is popped from the stack at most once.
    * Even though there is a nested `while` loop, the total number of operations across the entire execution is $2n$.
* **Space Complexity**: $O(n)$
    * In the worst case (a sorted array where no elements are popped), the stack will store all $n$ indices.

---

### 4. Common Applications

Monotonic stacks are essential for solving higher-level problems:
1. **Largest Rectangle in Histogram**: Uses **NSOL** and **NSOR** to find the width boundaries for each bar.
2. **Trapping Rain Water**: Uses **NGOL** and **NGOR** to find the heights of the surrounding walls.
3. **Sliding Window Maximum**: Can be solved using a variation of the monotonic property (though usually implemented with a Deque).
4. **Sum of Subarray Minimums**: Uses **NSOL** and **NSOR** to determine the range in which an element is the minimum.

----

### Monotonic Stack Properties

To remember which stack to use, look at what the "challenger" (the current element) is looking for. If the challenger wants to **pop** elements because it is **bigger**, the stack stays **decreasing**. If it pops elements because it is **smaller**, the stack stays **increasing**.

| Function | Name | Stack Property | Explanation |
| :--- | :--- | :--- | :--- |
| **NGOR** | Next Greater Right | **Monotonically Decreasing** | Elements stay in the stack as long as they are large. A larger element pops them. |
| **NGOL** | Next Greater Left | **Monotonically Decreasing** | We loop backwards, but the logic is the same: larger elements pop smaller ones. |
| **NSOR** | Next Smaller Right | **Monotonically Increasing** | Elements stay in the stack as long as they are small. A smaller element pops them. |
| **NSOL** | Next Smaller Left | **Monotonically Increasing** | We loop backwards; smaller elements pop the larger ones currently in the stack. |

---

### Visualizing the Stack State (Bottom to Top)

#### 1. Next Greater (Right or Left)
The stack will look like: `[10, 8, 6, 3]`
* If the next number is `7`, it pops `3` and `6`, then sits on top of `8`.
* **Result**: The stack always stays in **decreasing** order from bottom to top.


#### 2. Next Smaller (Right or Left)
The stack will look like: `[2, 5, 7, 9]`
* If the next number is `4`, it pops `9`, `7`, and `5`, then sits on top of `2`.
* **Result**: The stack always stays in **increasing** order from bottom to top.


---

### Pro-Tip for Identification
* **Greater** in the name $\rightarrow$ **Decreasing** Stack.
* **Smaller** in the name $\rightarrow$ **Increasing** Stack.

*The stack property is always the **opposite** of the search target.*



![alt text](<002Nger l Nser l range count_231121_163402(2).jpg>) ![alt text](<002Nger l Nser l range count_231121_163402(3).jpg>) ![alt text](<002Nger l Nser l range count_231121_163402(4).jpg>) ![alt text](<002Nger l Nser l range count_231121_163402(5).jpg>) ![alt text](<002Nger l Nser l range count_231121_163402(6).jpg>) ![alt text](<002Nger l Nser l range count_231121_163402(7).jpg>) ![alt text](<002Nger l Nser l range count_231121_163402(8).jpg>) ![alt text](<002Nger l Nser l range count_231121_163402(9).jpg>) ![alt text](<002Nger l Nser l range count_231121_163402(10).jpg>) ![alt text](<002Nger l Nser l range count_231121_163402(11).jpg>) ![alt text](<002Nger l Nser l range count_231121_163402(12).jpg>) ![alt text](<002Nger l Nser l range count_231121_163402(13).jpg>)


---

```cpp
class StockSpanner {
    stack<pair<int,int>> stk;
    int day;
public:
    StockSpanner() {
        day=0;
        stk.push({-1,-1});
    }
    
    int next(int price) {
        while(stk.top().first!=-1 && stk.top().first<=price){
            stk.pop();
        }
        int span=day-stk.top().second;
        stk.push({price,day++});
        return span;
    }
};

/**
 * Your StockSpanner object will be instantiated and called as such:
 * StockSpanner* obj = new StockSpanner();
 * int param_1 = obj->next(price);
 */
 ```
`{-1,-1}` if you do not put and stk is empty and next() is called then span calucation will give memory error as nothing on top() and u are accessing it.