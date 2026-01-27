# Notes

![alt text](<004heap implementation _240517_174240.jpg>) 
![alt text](<004heap implementation _240517_174240(2).jpg>) 
![alt text](<004heap implementation _240517_174240(3).jpg>) 
![alt text](<004heap implementation _240517_174240(4).jpg>) 
![alt text](<004heap implementation _240517_174240(5).jpg>) 

# Why the Height of a Heap is $\log N$

In a Binary Heap, the tree is always **complete**, meaning every level is fully filled except possibly the last level, which is filled from left to right. This structure ensures the minimum possible height for a given number of nodes.

---

### 1. The Relationship Between Nodes and Levels
Let $H$ be the height of the tree (where a single root node has $H = 0$).

* **Level 0:** $2^0 = 1$ node
* **Level 1:** $2^1 = 2$ nodes
* **Level 2:** $2^2 = 4$ nodes
* **Level $h$:** $2^h$ nodes

In a **perfect** binary tree where every level is full, the total number of nodes $N$ is the sum of nodes at each level:
$$N = 2^0 + 2^1 + 2^2 + \dots + 2^H$$

This is a geometric series that sums to:
$$N = 2^{H+1} - 1$$

---

### 2. Solving for Height ($H$)
To find the height in terms of $N$, we rearrange the formula:

1.  Add 1 to both sides:
    $$N + 1 = 2^{H+1}$$
2.  Take the logarithm (base 2) of both sides:
    $$\log_2(N + 1) = H + 1$$
3.  Isolate $H$:
    $$H = \log_2(N + 1) - 1$$

For large $N$, the constants $(-1$ and $+1)$ become insignificant, leaving us with:
$$H \approx \log_2 N$$

---

### 3. Why this matters for Complexity
Every time you move down one level in a heap (during `heapify`), you are essentially cutting the remaining number of nodes you have to look at by **half**. This "divide by two" behavior is the definition of a logarithmic relationship.

* **Searching in a List:** $O(N)$
* **Moving through Heap Height:** $O(\log N)$

---

### Summary
> "A heap is a complete binary tree. Because the number of nodes doubles at each level, the number of levels required to hold $N$ nodes is only $\log_2 N$. This logarithmic height is what makes heap operations like insertion and deletion so fast."


![alt text](<004heap implementation _240517_174240(6).jpg>) ![alt text](<004heap implementation _240517_174240(7).jpg>) ![alt text](<004heap implementation _240517_174240(8).jpg>) ![alt text](<004heap implementation _240517_174240(9).jpg>) ![alt text](<004heap implementation _240517_174240(10).jpg>) ![alt text](<004heap implementation _240517_174240(11).jpg>) ![alt text](<004heap implementation _240517_174240(12).jpg>) ![alt text](<004heap implementation _240517_174240(13).jpg>) ![alt text](<004heap implementation _240517_174240(14).jpg>) ![alt text](<004heap implementation _240517_174240(15).jpg>) ![alt text](<004heap implementation _240517_174240(16).jpg>) ![alt text](<004heap implementation _240517_174240(17).jpg>) ![alt text](<004heap implementation _240517_174240(18).jpg>) ![alt text](<004heap implementation _240517_174240(19).jpg>) ![alt text](<004heap implementation _240517_174240(20).jpg>) ![alt text](<004heap implementation _240517_174240(21).jpg>)

![alt text](<004heap implementation _240517_174240(22).jpg>) ![alt text](<004heap implementation _240517_174240(23).jpg>) 

## Basic Min Heap code 

```cpp 
class Solution{
    vector<int>heap;
    void upheapify(int idx){
        int pidx=(idx-1)/2;
        if(pidx>=0 && heap[pidx]>heap[idx]){
            swap(heap[pidx],heap[idx]);
            upheapify(pidx);
        }
    }
    void downheapify(int idx ){
        int n=heap.size();
        int residx=idx;
        int lidx=2*idx+1;
        int ridx=2*idx+2;
        if(lidx<n && heap[residx]>heap[lidx]){
            residx=lidx;
        }
        if(ridx<n && heap[residx]>heap[ridx]){
            residx=ridx;
        }
        if(residx!=idx){
            swap(heap[residx],heap[idx]);
            downheapify(residx);
        }

    }
    void heapify( int ind, int val) {
        int oldVal=heap[ind];
        heap[ind]=val;
        if(oldVal>heap[ind]) upheapify(ind);
        else downheapify(ind);
    }
    void add(int val){
        heap.push_back(val);
        upheapify(heapSize()-1);
    }
    void remove(){
        if(heapSize()==0) return;
        if(heapSize()==1) {
            heap.pop_back();
            return;
        }
        int idx=heapSize()-1;
        swap(heap[0],heap[idx]);
        heap.pop_back();
        downheapify(0);
    }
    public:

        void initializeHeap(){

        }

        void insert(int key){
            add(key);
        }

        void changeKey(int index, int new_val){
            heapify(index,new_val);
        }

        void extractMin(){
            remove();
        }

        bool isEmpty(){
            return heap.size()==0;
        }

        int getMin(){
            if(isEmpty()==true) return -(1e5+1);
            return heap[0];
        }

        int heapSize(){
            return heap.size();
        }
};

```

## Basic max heap code
```cpp

class Solution{
    vector<int>heap;
    void upheapify(int idx){
        int pidx=(idx-1)/2;
        if(pidx>=0 && heap[pidx]<heap[idx]){
            swap(heap[pidx],heap[idx]);
            upheapify(pidx);
        }
    }
    void downheapify(int idx ){
        int n=heap.size();
        int residx=idx;
        int lidx=2*idx+1;
        int ridx=2*idx+2;
        if(lidx<n && heap[residx]<heap[lidx]){
            residx=lidx;
        }
        if(ridx<n && heap[residx]<heap[ridx]){
            residx=ridx;
        }
        if(residx!=idx){
            swap(heap[residx],heap[idx]);
            downheapify(residx);
        }

    }
    void heapify( int ind, int val) {
        int oldVal=heap[ind];
        heap[ind]=val;
        if(oldVal<heap[ind]) upheapify(ind);
        else downheapify(ind);
    }
    void add(int val){
        heap.push_back(val);
        upheapify(heapSize()-1);
    }
    void remove(){
        if(heapSize()==0) return;
        if(heapSize()==1) {
            heap.pop_back();
            return;
        }
        int idx=heapSize()-1;
        swap(heap[0],heap[idx]);
        heap.pop_back();
        downheapify(0);
    }
    public:

        void initializeHeap(){

        }

        void insert(int key){
            add(key);
        }

        void changeKey(int index, int new_val){
            heapify(index,new_val);
        }

        void extractMax(){
            remove();
        }

        bool isEmpty(){
            return heap.size()==0;
        }

        int getMax(){
            if(isEmpty()==true) return -(1e5+1);
            return heap[0];
        }

        int heapSize(){
            return heap.size();
        }
};
```

![alt text](<004heap implementation _240517_174240(24).jpg>) ![alt text](<004heap implementation _240517_174240(25).jpg>) ![alt text](<004heap implementation _240517_174240(26).jpg>) ![alt text](<004heap implementation _240517_174240(27).jpg>) ![alt text](<004heap implementation _240517_174240(28).jpg>) ![alt text](<004heap implementation _240517_174240(29).jpg>) ![alt text](<004heap implementation _240517_174240(30).jpg>) ![alt text](<004heap implementation _240517_174240(31).jpg>) ![alt text](<004heap implementation _240517_174240(32).jpg>)

# Correct Heap Operations: Add vs. Remove

In a Binary Heap, we use different "heapify" directions depending on whether we are growing or shrinking the tree.

---

### 1. Adding an Element (Insertion)
**Logic:** `push_back` $\to$ **Up-Heapify** (Swim)

* **Step 1:** Add the new element to the very end of the array (`push_back`). This maintains the **Complete Binary Tree** property.
* **Step 2:** The new element might be larger than its parent. To fix this, we **Up-Heapify** (compare with parent and swap upwards).
* **Why not Down-Heapify?** If you pushed the new element to the end, then swapped it to the root, you would be displacing the current maximum value and forcing a small value to the top, which then has to sink all the way down. Up-heapify is more direct.This is too much work !! 

---

### 2. Removing an Element (Poll/Pop)

While removing we know root is max or min so we remove that as need to get max or min according to heap so after getting that we need to fill that empty root so we swap by end elemet and then perform downhepify on root

**Logic:** Swap Root with Last $\to$ `pop_back` $\to$ **Down-Heapify** (Sink)

* **Step 1:** Swap the element at index `0` (the root) with the element at the last index.
* **Step 2:** Remove the last element (`pop_back`).
* **Step 3:** The new root is now a value that was previously at the bottom (likely very small). To fix this, we **Down-Heapify** from the root downwards.
* **Why this way?** We must remove the root, but we can't leave a hole. Swapping with the last element is the only way to remove a node while keeping the tree "complete."

---

### 3. Summary of Directions

| Action | Starting Point | Direction | Algorithm |
| :--- | :--- | :--- | :--- |
| **Add** | Last Index | Bottom $\to$ Top | **Up-Heapify** |
| **Remove** | Root (Index 0) | Top $\to$ Bottom | **Down-Heapify** |

### 4. C++ Implementation Comparison

```cpp
// ADDING
void push(int val) {
    arr.push_back(val);
    upHeapify(arr.size() - 1); // Move UP from bottom
}

// REMOVING
void pop() {
    swap(arr[0], arr[arr.size() - 1]);
    arr.pop_back();
    downHeapify(0); // Move DOWN from root
}
```

## Heap impl general
```java
import java.util.ArrayList;

public class heap {
    private ArrayList<Integer> arr;
    private int size = 0;
    private boolean isMax = true;

    private void intialize(boolean isMax) {
        this.arr = new ArrayList<>();
        this.size = 0;
        this.isMax = isMax;
    }

    public heap() {
        intialize(true);
    }

    public heap(int[] arr, boolean isMax) { // O(n)
        intialize(isMax);
        for (int ele : arr)
            this.arr.add(ele);

        for (int i = this.arr.size() - 1; i >= 0; i--) {
            downHeapify(i);
        }

        this.size = arr.length;
    }

    // General Functions.

    public int size() {
        return this.size;
    }

    public boolean isEmpty() {
        return this.size == 0;
    }

    public void add(int data) { // O(logN)
        this.arr.add(data);
        this.size++;
        upheapify(this.size - 1);
    }

    public int remove() { // O(logN)
        int n = this.arr.size();
        int rv = this.arr.get(0);

        swap(0, n - 1);
        this.arr.remove(n - 1);
        this.size--;

        downHeapify(0);
        return rv;
    }

    public int peek() { // O(1)
        return this.arr.get(0);
    }

    private int compareTo(int a,int b){
        if(isMax){
            return this.arr.get(a) - this.arr.get(b);
        }else{
            return this.arr.get(b) - this.arr.get(a);
        }

    }

    private void swap(int i, int j) { // O(1)
        int ei = arr.get(i);
        int ej = arr.get(j);

        arr.set(i, ej);
        arr.set(j, ei);
    }

    private void upheapify(int ci) { // O(logn)
        int pi = (ci - 1) / 2;
        if (pi >= 0 && compareTo(ci,pi) > 0) {
            swap(pi, ci);
            upheapify(pi);
        }
    }

    private void downHeapify(int pi) { // O(logn)
        int maxIdx = pi;
        int lci = 2 * pi + 1;
        int rci = 2 * pi + 2;

        if (lci < this.arr.size() && compareTo(lci,maxIdx) > 0)
            maxIdx = lci;
        if (rci < this.arr.size() && compareTo(rci,maxIdx) > 0)
            maxIdx = rci;

        if (maxIdx != pi) {
            swap(maxIdx, pi);
            downHeapify(maxIdx);
        }
    }

}

```



## Heapsort

```cpp
#include <iostream>
#include <vector>
#include <algorithm> // Required for std::swap

using namespace std;

class HeapSort {
public:
    // Custom comparator logic based on isMax flag
    static bool compareTo(int a, int b, bool isMax) {
        if (isMax)
            return a > b;
        else
            return a < b;
    }

    static void downheapify(int pi, vector<int>& arr, int li, bool isMax) {
        int targetIdx = pi;
        int lci = 2 * pi + 1;
        int rci = 2 * pi + 2;

        if (lci <= li && compareTo(arr[lci], arr[targetIdx], isMax))
            targetIdx = lci;
        if (rci <= li && compareTo(arr[rci], arr[targetIdx], isMax))
            targetIdx = rci;

        if (pi != targetIdx) {
            swap(arr[pi], arr[targetIdx]); 
            downheapify(targetIdx, arr, li, isMax);
        }
    }

    static void display(const vector<int>& arr) {
        for (int ele : arr)
            cout << ele << " ";
        cout << endl;
    }
};

int main() {
    vector<int> arr = { 10, 20, 30, -2, -3, -4, 5, 6, 7, 8, 9, 22, 11, 13 };
    int n = arr.size();
    
    // isMax = true -> Ascending Sort
    // isMax = false -> Descending Sort
    bool isMax = true; 

    // Build Heap: Start from the last non-leaf node (n/2 - 1)
    for (int i = n / 2 - 1; i >= 0; i--) {
        HeapSort::downheapify(i, arr, n - 1, isMax);
    }

    // Extraction phase
    int li = n - 1;
    while (li >= 0) {
        swap(arr[0], arr[li--]); // Move current root to the end
        HeapSort::downheapify(0, arr, li, isMax);
    }

    HeapSort::display(arr);

    return 0;
}
```
1st step build heap from array assume min heap 

2ns step extraction phase

# The Extraction Phase: Turning a Heap into a Sorted Array

Once the `Build-Heap` phase is finished, the maximum element (in a Max-Heap) is at `arr[0]`. However, the rest of the elements are not in order. The Extraction Phase fixes this.

### 1. The Logic Step-by-Step
We repeat the following process until the heap is empty:

1.  **Swap:** We swap the root (`arr[0]`) with the last element of the current heap (`arr[li]`). 
    * *Why?* This "locks" the largest element into its correct final position at the end of the array.
2.  **Shrink:** We decrease the heap size (`li--`). 
    * *Why?* We don't want to touch the elements we've already "locked" at the back.
3.  **Heal (Down-Heapify):** The new root is now a small value that was swapped up from the bottom. It violates the heap property. We call `downheapify` to sink it back to its correct spot.
    * *Why?* To bring the *next* largest element to `arr[0]` for the next iteration.

---

### 2. Sorting Direction
The type of heap you build determines the final sort order:

| Heap Type | Extraction Result | Final Array Order |
| :--- | :--- | :--- |
| **Max-Heap** | Largest elements moved to the back | **Ascending** (1, 2, 3...) |
| **Min-Heap** | Smallest elements moved to the back | **Descending** (3, 2, 1...) |

---

### 3. Complexity Analysis
* **Number of Extractions:** We perform $N$ extractions.
* **Work per Extraction:** Each `downheapify` takes $O(\log N)$ time (the height of the tree).
* **Total Time:** $N \times \log N = O(N \log N)$.

---

### 4. Visualization of the "Locking" Effect
Imagine an array `[30, 20, 10]`:
1. **Swap** 30 and 10: `[10, 20, | 30]` (30 is locked).
2. **Heapify** 10: 20 moves up: `[20, 10, | 30]`.
3. **Swap** 20 and 10: `[10, | 20, 30]` (20 is locked).
4. **Result:** `[10, 20, 30]` (Fully Sorted).

### Summary for Interviews
> "The extraction phase is necessary because a heap is only a **partial ordering**. To get a **total ordering** (a sorted array), we repeatedly swap the maximum element to the end of the array and rebuild the heap with the remaining elements. This takes $O(N \log N)$ time."

for making heap from array we have two approaches 

1. Bottom up --> for non leaf node we call downheapify .this has TC of O(n)
2. top down--> for each array element insert in heap and apply upheapify.normal insertion of heap ,so for n insertions it takes o(n log n) time 

we use 1st one to build heap from array as takes O(n) time and let us discuss this in detail now



# Why $n/2$ to $0$ in Build Heap?

When we convert a random array into a heap, we only call `heapify` (or `downheapify`) on the **non-leaf nodes**. 

### 1. Leaf Nodes are Already Heaps
In a complete binary tree represented as an array, roughly half of the nodes are **leaves** (nodes with no children). 
* A single node with no children **already satisfies** the Max-Heap or Min-Heap property by default.
* Therefore, calling `downheapify` on a leaf node does nothing; it's a wasted operation.

### 2. Identifying the Last Non-Leaf Node
In a zero-indexed array of size **$n$**:
* **Leaf Nodes** are located from index $\lfloor n/2 \rfloor$ to $n-1$.
* **Non-Leaf Nodes** are located from index $0$ to $\lfloor n/2 \rfloor - 1$.

By starting at $n/2 - 1$, we are starting at the very last node that actually has at least one child.

---

### 3. The "Bottom-Up" Strategy
We process the nodes in **reverse order** ($n/2 \to 0$) to ensure that when we call `downheapify` on a parent, both of its child subtrees are **already valid heaps**.

1. We fix the smallest sub-trees at the bottom first.
2. We move up to the next level and fix those.
3. Finally, we fix the root.

If we started from the root ($0$) and moved down, the children might not be heaps yet, so the root wouldn't "sink" to its correct global position in one pass.

---

### 4. Mathematical Efficiency ($O(N)$ vs $O(N \log N)$)
This is the most surprising part:
* If you insert nodes one by one (top-down), the complexity is **$O(N \log N)$**.
* By using the **Bottom-Up** approach (starting from $n/2$), the complexity is actually **$O(N)$**.

**Why?**
Most nodes are at the bottom of the tree. In this approach, the nodes at the bottom move a very short distance (0 or 1 step), and only the few nodes at the top move the full height of the tree. The summation of this work converges to $O(N)$.

---

### Summary Table
| Strategy | Range | Complexity | Reason |
| :--- | :--- | :--- | :--- |
| **Top-Down** | $0$ to $n-1$ | $O(N \log N)$ | Treating it like $N$ separate insertions. |
| **Bottom-Up** | $n/2 - 1$ to $0$ | **$O(N)$** | Leaves are skipped; higher density of nodes do less work. |

# Mathematical Analysis of Build Heap Complexity

The difference in complexity arises from **where the most work is done**. In a binary tree, most nodes are at the bottom. 

---

## 1. Bottom-Up Approach ($O(N)$)
This is the method where we start from $n/2$ and use `down-heapify`.

### The Logic
Nodes at different heights do different amounts of work.
* **Nodes at height 0 (Leaves):** $N/2$ nodes, 0 work.as downheapify ,we cannot move more down than leaves so 0 work
* **Nodes at height 1:** $N/4$ nodes, 1 level of sinking. can move 1 level down so 1 work!!
* **Nodes at height $h$:** $N/2^{h+1}$ nodes, $h$ levels of sinking.

height of tree is `log N` as complete Binary tree!!
### The Mathematics
The total work $W$ is:
$$W = \sum_{h=0}^{\log N} \frac{N}{2^{h+1}} \cdot h$$

Factoring out $N/2$:
$$W = \frac{N}{2} \sum_{h=0}^{\log N} \frac{h}{2^h}$$

The summation $\sum_{h=0}^{\infty} \frac{h}{2^h}$ is a known convergent series that equals **2**.
$$W = \frac{N}{2} \cdot 2 = O(N)$$

**Conclusion:** Since the majority of nodes (the leaves) do zero work, and only the root does $\log N$ work, the average work per node is constant.

---

# Why we convert $\log N$ to $\infty$ in the Proof

In Big O analysis, we are looking for the **upper bound**. By changing the limit from $\log N$ to $\infty$, we are essentially saying: "Even if this tree were infinitely tall, the work would still be constant."

### 1. The Comparison
Let's look at the two sums:
1.  **Actual Work:** $W = \sum_{h=0}^{\log N} \frac{h}{2^h}$ (Finite)
2.  **Theoretical Cap:** $W = \sum_{h=0}^{\infty} \frac{h}{2^h}$ (Infinite)

Since all the terms in this series are positive, the infinite sum **must** be greater than or equal to the finite sum:
$$\sum_{h=0}^{\log N} \frac{h}{2^h} < \sum_{h=0}^{\infty} \frac{h}{2^h}$$

---

### 2. Why the Infinite Sum is Useful
The finite sum is mathematically "messy" to calculate exactly for every $N$. However, the infinite sum is a **Geometric Series** variant that has a clean, constant solution.

Using the Arithmetico-Geometric series formula:
$$\sum_{k=0}^{\infty} kx^k = \frac{x}{(1-x)^2}$$

# Deriving the Arithmetico-Geometric Series Formula

To prove the $O(N)$ complexity of Build Heap, we need the sum of the series $S$:
$$S = \sum_{k=0}^{\infty} kx^k = 0 + 1x^1 + 2x^2 + 3x^3 + 4x^4 + \dots$$

### Step 1: Set up the Equations
Write out the series $S$, and then write the series multiplied by $x$ (shifted by one position).

**Equation 1:**
$$S = x + 2x^2 + 3x^3 + 4x^4 + \dots$$

**Equation 2:**
$$xS = x^2 + 2x^3 + 3x^4 + 4x^5 + \dots$$

---

### Step 2: Subtract Equation 2 from Equation 1
Subtracting the two equations allows us to cancel out the coefficients:

$$S - xS = (x + 2x^2 + 3x^3 + 4x^4 + \dots) - (x^2 + 2x^3 + 3x^4 + \dots)$$

$$S(1-x) = x + (2x^2 - x^2) + (3x^3 - 2x^3) + (4x^4 - 3x^4) + \dots$$

This simplifies to:
$$S(1-x) = x + x^2 + x^3 + x^4 + \dots$$

---

### Step 3: Solve the Geometric Series
The right-hand side is now a standard **Infinite Geometric Series** with the first term $a = x$ and the common ratio $r = x$. The formula for this sum is $a / (1-r)$:

$$S(1-x) = \frac{x}{1-x}$$

---

### Step 4: Final Formula
Now, divide both sides by $(1-x)$ to isolate $S$:

$$S = \frac{x}{(1-x)^2}$$

---

### Step 5: Applying it to Heapify
In the Heapify proof, our ratio $x$ is $1/2$ 

as see 

$\sum_{h=0}^{\infty} \frac{h}{2^h}$


$\sum_{k=0}^{\infty} kx^k$

compare k is h here and x is 1/2.

$$S = \frac{1/2}{(1 - 1/2)^2}$$
$$S = \frac{1/2}{(1/2)^2}$$
$$S = \frac{1/2}{1/4} = 2$$

**Final Result:** Since the sum of work per node converges to a constant (2), the total work for $N$ nodes is:
$$W = \frac{N}{2} \cdot 2 = O(N)$$



If we set $x = 1/2$:
$$\sum_{h=0}^{\infty} h\left(\frac{1}{2}\right)^h = \frac{1/2}{(1 - 1/2)^2} = \frac{1/2}{1/4} = 2$$

---

### 3. Conclusion for Complexity
Since the infinite sum equals **2**, and our actual work is **less** than the infinite sum, we can confidently say:
$$W \leq \frac{N}{2} \cdot 2$$
$$W \leq N$$

This proves that the work is bounded by a linear function of $N$, hence **$O(N)$**.

### Summary for an Interviewer
> "We treat the summation as an infinite series because it provides a clean upper bound. Since the series converges to a constant (2), it proves that the total work done is proportional to $N$, regardless of how large $N$ becomes."

## 2. Top-Down Approach ($O(N \log N)$)
This is the method where we treat the array as $N$ successive insertions using `up-heapify`.we insert one by one and apply upHeapify() 

### The Logic
In this case, work is based on the **depth** of the node from the root.
* **Node at depth 0 (Root):** 1 node, 0 work.as upheapify so no work to do ,as no level up than root

* **Nodes at depth 1:** 2 nodes, 1 level of climbing.
* **Nodes at depth $d$:** $2^d$ nodes, $d$ levels of climbing.

### The Mathematics
The total work $W$ is:
$$W = \sum_{d=0}^{\log N} d \cdot 2^d$$

This is an arithmetico-geometric series. The sum of this series is:
$$W = (\log N - 1) \cdot 2^{\log N + 1} + 2$$



# Mathematical Analysis of the Top-Down Series

The sum $W = \sum_{d=0}^{H} d \cdot 2^d$ represents the total work when every node at depth $d$ must climb up $d$ levels.


---

### 1. Step-by-Step Derivation (Shift and Subtract)
Let's derive it using the same method we used before, where $H = \log N$ and $r = 2$.

**Set up the equations:**
1. $S = (1 \cdot 2^1) + (2 \cdot 2^2) + (3 \cdot 2^3) + \dots + (H \cdot 2^H)$
2. $2S = (1 \cdot 2^2) + (2 \cdot 2^3) + (3 \cdot 2^4) + \dots + (H \cdot 2^{H+1})$

**Subtract Equation 1 from Equation 2:**
$$2S - S = (H \cdot 2^{H+1}) - (2^1 + 2^2 + 2^3 + \dots + 2^H)$$

**Simplify:**
* The term $(2^1 + 2^2 + \dots + 2^H)$ is a standard geometric series that sums to $(2^{H+1} - 2)$.
* So:
$$S = H \cdot 2^{H+1} - (2^{H+1} - 2)$$
$$S = (H - 1) \cdot 2^{H+1} + 2$$

---

### 2. Converting to $N$
We know that for a complete binary tree:
* $H \approx \log_2 N$
* $2^{H+1} \approx N$ (Total number of nodes)

Substitute these into our simplified equation:
$$W \approx (\log N - 1) \cdot N + 2$$
$$W \approx N \log N - N + 2$$

---

### 3. Conclusion
When we ignore lower-order terms and constants in Big O notation:
$$W = O(N \log N)$$

### Summary Comparison
* **Bottom-Up ($O(N)$):** The work is $\sum \frac{h}{2^h}$. The $2^h$ is in the **denominator**, so the terms get smaller. The sum stays small (converges).
* **Top-Down ($O(N \log N)$):** The work is $\sum d \cdot 2^d$. The $2^d$ is in the **numerator**, so the terms get larger. The sum grows significantly.

This is why "sinking" a node from the root down is much cheaper than "climbing" all leaf nodes to the top!

Since $2^{\log N}$ is $N$:
$$W \approx (N \cdot \log N)$$

**Conclusion:** The majority of nodes are at the bottom (leaves) and they are forced to climb the maximum height of the tree, leading to $O(N \log N)$.

---

## Summary Table

| Feature | Bottom-Up (Down-Heapify) | Top-Down (Up-Heapify) |
| :--- | :--- | :--- |
| **Direction** | Sinks nodes down | Moves nodes up |
| **Leaf Work** | **Zero work** (most nodes) | **Max work** (most nodes) |
| **Total Work** | $O(N)$ | $O(N \log N)$ |
| **Efficiency** | Highly Optimized | Sub-optimal for building |


## Q Heapify Algorithm

Given an array of **n** integers, convert the array into a **Max-Heap** using the **Heapify** algorithm.

A **Max-Heap** is a complete binary tree where the value of each node is greater than or equal to the values of its children. In the array representation of a heap:
- The root is at index `0`.
- For any element at index `i`, its left child is at index `2*i + 1` and its right child is at index `2*i + 2`.

The goal is to rearrange the elements in the array in-place so that they satisfy the Max-Heap property.

### Example 1
**Input:** `arr = [4, 10, 3, 5, 1]`  
**Output:** `[10, 5, 3, 4, 1]`  

### Example 2
**Input:** `arr = [1, 3, 5, 4, 6, 13, 10, 9, 8, 15, 17]`  
**Output:** `[17, 15, 13, 9, 6, 5, 10, 4, 8, 3, 1]`  

### Constraints
- `1 <= arr.length <= 10^5`
- `1 <= arr[i] <= 10^6`


### Min heap it is 

```cpp
class Solution {
    void upheapify(int idx,vector<int>& arr){
        int pidx=(idx-1)/2;
        if(pidx>=0 && arr[pidx]>arr[idx]){
            swap(arr[pidx],arr[idx]);
            upheapify(pidx,arr);
        }
    }
    void downheapify(int idx,vector<int>& arr ){
        int n=arr.size();
        int residx=idx;
        int lidx=2*idx+1;
        int ridx=2*idx+2;
        if(lidx<n && arr[residx]>arr[lidx]){
            residx=lidx;
        }
        if(ridx<n && arr[residx]>arr[ridx]){
            residx=ridx;
        }
        if(residx!=idx){
            swap(arr[residx],arr[idx]);
            downheapify(residx,arr);
        }

    }
public:
    void heapify(vector<int> &nums, int ind, int val) {
        int oldVal=nums[ind];
        nums[ind]=val;
        if(oldVal>nums[ind]) upheapify(ind,nums);
        else downheapify(ind,nums);
    }
};
```
if old val was greater than and new value is less and it is min heap so offcurse value will move up

if old value is less than new value  and it is min heap so offcourse larger value will move down so we use downheapify

## Build heap from array 

Min heap
```cpp
class Solution {
       // Custom comparator logic based on isMax flag
 bool compareTo(int a, int b, bool isMax) {
        if (isMax)
            return a > b;
        else
            return a < b;
    }

 void downheapify(int pi, vector<int>& arr, int li, bool isMax) {
        int targetIdx = pi;
        int lci = 2 * pi + 1;
        int rci = 2 * pi + 2;

        if (lci <= li && compareTo(arr[lci], arr[targetIdx], isMax))
            targetIdx = lci;
        if (rci <= li && compareTo(arr[rci], arr[targetIdx], isMax))
            targetIdx = rci;

        if (pi != targetIdx) {
            swap(arr[pi], arr[targetIdx]); 
            downheapify(targetIdx, arr, li, isMax);
        }
    }
public:
    void buildMinHeap(vector<int> &nums) {
        int n=nums.size();
         for (int i = n / 2 - 1; i >= 0; i--) {
        downheapify(i, nums, n - 1,false);
    }
    }
};
```

We have seen this in heap sort why we using downheapfy. and why using from n/2 -1 to 0







