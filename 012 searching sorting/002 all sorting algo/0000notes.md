# Notes
![alt text](<001_ss231229_225958 (1).jpg>)
![alt text](<001_ss231229_225958 (1)(1).jpg>) ![alt text](<001_ss231229_225958 (1)(2).jpg>) ![alt text](<001_ss231229_225958 (1)(3).jpg>) ![alt text](<001_ss231229_225958 (1)(4).jpg>) ![alt text](<001_ss231229_225958 (1)(5).jpg>) ![alt text](<001_ss231229_225958 (1)(6).jpg>) ![alt text](<001_ss231229_225958 (1)(7).jpg>) ![alt text](<001_ss231229_225958 (1)(8).jpg>) ![alt text](<001_ss231229_225958 (1)(9).jpg>)





## Selection sort 

```cpp
class Solution {
public:
    vector<int> selectionSort(vector<int>& nums) {
        for(int i=0;i<nums.size();i++){
            int min=i;
            for(int j=i+1;j<nums.size();j++){
                if(nums[j]<nums[min]){
                    min=j;
                }
            }
            if(min!=i){
                swap(nums[min],nums[i]);
            }
        }
        return nums;
    }
};

```
## Bubble sort 

```cpp
class Solution {
public:
    vector<int> bubbleSort(vector<int>& arr) {
        for(int i=0;i<arr.size();i++){
            bool swapped=false;
            for(int j=0;j<arr.size()-i-1;j++){
                if(arr[j]>arr[j+1]){
                    swap(arr[j],arr[j+1]);
                    swapped=true;
                }
            }
            if(swapped==false) break;
        }
        return arr;
    }
};

```
## Insertion sort

```cpp
class Solution {
public:
    vector<int> insertionSort(vector<int>& arr) {
        for(int i=1;i<arr.size();i++){
            for(int j=i-1;j>=0;j--){
                if(arr[j]>arr[j+1]) swap(arr[j],arr[j+1]);
                else break;
            }
        }
        return arr;
    }
};

```

## Merge sort

```cpp

class Solution {
    void merge(vector<int>& arr,int lo,int mid,int hi){
        vector<int> temp;
        int left = lo;
        int right = mid + 1;
        while(left<=mid && right <=hi){
            if(arr[left]<=arr[right]){
                temp.push_back(arr[left++]);
            }else 
                temp.push_back(arr[right++]);
        }
        while (left <= mid) {
            temp.push_back(arr[left++]);
        }

        while (right <= hi) {
            temp.push_back(arr[right++]);
        }
        for (int i = lo; i <= hi; i++) {
            arr[i] = temp[i - lo];
        }
    }
    void mergeSortFunction(vector<int>& arr,int lo,int hi){
        if(lo>=hi) return;
        int mid=(lo+hi)/2;
        mergeSortFunction(arr,lo,mid);
        mergeSortFunction(arr,mid+1,hi);
        merge(arr,lo,mid,hi);
    }
public:
    vector<int> mergeSort(vector<int>& nums) {
         mergeSortFunction(nums,0,nums.size()-1);
         return nums;
    }
};

```

## Quick Sort

```cpp
class Solution {
    int getPartiton(vector<int>& arr,int l,int r){
        int pivot=arr[r];
        int i=0,j=0;
        while(i<=r){
            if(arr[i]<=pivot){
                swap(arr[i],arr[j]);
                i++;
                j++;
            }else{
                i++;
            }
        }
        return j-1;
    }

    void sortQuick(vector<int>& arr,int l,int r){
            if(l>=r) return;

            int p=getPartiton(arr,l,r);
            sortQuick(arr,l,p-1);
            sortQuick(arr,p,r);
    }
public:
    vector<int> quickSort(vector<int>& nums) {
        int n=nums.size();
        sortQuick(nums,0,n-1);
        return nums;
    }
};

```

## Heap sort

```cpp
class Solution {
    void downheapify(vector<int> &v ,int size ,int i){
        int idx=i;
        int leftidx=2*i+1;
        int rightidx=2*i+2;
        if(leftidx<size && v[leftidx]>v[idx]) idx=leftidx;
        if(rightidx<size && v[rightidx]>v[idx]) idx=rightidx;
        if(idx!=i){
            swap(v[idx],v[i]);
            downheapify(v,size,idx);
        }
    }
public:
    void heapSort(vector<int>&nums) {
        int n=nums.size();
        for(int i=n/2-1;i>=0;i--){
            downheapify(nums,n,i);
        }

        for(int i=n-1;i>=0;i--){
            swap(nums[i],nums[0]);
            downheapify(nums,i,0);
        }

    }
};
```

for all other details see 012.hashamp Heap/000 questions/001 Hashmap Heap Creation/003 heap implemenatation notes/000notes.md

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
* **Nodes at height 0 (Leaves):** $N/2$ nodes, 0 work.
* **Nodes at height 1:** $N/4$ nodes, 1 level of sinking.
* **Nodes at height $h$:** $N/2^{h+1}$ nodes, $h$ levels of sinking.

### The Mathematics
The total work $W$ is:
$$W = \sum_{h=0}^{\log N} \frac{N}{2^{h+1}} \cdot h$$

Factoring out $N/2$:
$$W = \frac{N}{2} \sum_{h=0}^{\log N} \frac{h}{2^h}$$

The summation $\sum_{h=0}^{\infty} \frac{h}{2^h}$ is a known convergent series that equals **2**.
$$W = \frac{N}{2} \cdot 2 = O(N)$$

**Conclusion:** Since the majority of nodes (the leaves) do zero work, and only the root does $\log N$ work, the average work per node is constant.

---

## 2. Top-Down Approach ($O(N \log N)$)
This is the method where we treat the array as $N$ successive insertions using `up-heapify`.

### The Logic
In this case, work is based on the **depth** of the node from the root.
* **Node at depth 0 (Root):** 1 node, 0 work.
* **Nodes at depth 1:** 2 nodes, 1 level of climbing.
* **Nodes at depth $d$:** $2^d$ nodes, $d$ levels of climbing.

### The Mathematics
The total work $W$ is:
$$W = \sum_{d=0}^{\log N} d \cdot 2^d$$

This is an arithmetico-geometric series. The sum of this series is:
$$W = (\log N - 1) \cdot 2^{\log N + 1} + 2$$

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



## Basic Heap code 

```cpp 

#include <bits/stdc++.h>
using namespace std;

class Heap {
        void upHeapify(int i){
            if(i==0) return;
           int parIdx=(i-1)/2;
           if(v[parIdx]>v[i]){
               swap(v[parIdx],v[i]);
               upHeapify(parIdx);
           }
       }
       
       void downHeapify(int idx){
           int resIdx=idx;
           int lIdx=2*idx+1;
           int rIdx=2*idx+2;
           if(lIdx<v.size()&& v[lIdx]<v[resIdx]) resIdx=lIdx;
           if(rIdx<v.size() && v[rIdx]<v[resIdx]) resIdx=rIdx;
           if(resIdx!=idx){
               swap(v[resIdx],v[idx]);
               downHeapify(resIdx);
           }
           
       }
    public:
   vector<int> v;
    void insert(int val){
        v.push_back(val);
        if(v.size()==1) return;
        upHeapify(v.size()-1);
    }
    
    void Heapify(int index) {
        downHeapify(0);
    }
    
    void delete_from_heap(){
        int n=v.size();
        if(n==1) {
            v.pop_back();
            return;
        }
        swap(v[n-1],v[0]);
        v.pop_back();
        Heapify(0);
    }
    
};



int main() {
    Heap* h1 = new Heap();
    int n;
    cin>>n;
    for(int i=0; i<n; i++)
    {
        string command;
        cin>>command;
        if(command=="insert"){
            int value;
            cin>>value;
            h1->insert(value);
        }
        else if(command=="delete")
        {
            h1->delete_from_heap();
        }
        else if(command=="print"){
            for(auto j: h1->v)
            {
                cout<<j<<" ";
            }
            cout<<endl;
        }
    }

}

```
### Count sort

```cpp
#include <bits/stdc++.h>

using namespace std;

vector<int> countsort(vector<int>& arr) {
    int n = arr.size();

    int mnval=INT_MAX;
    int maxval = 0;
    for (int i = 0; i < n; i++){
        maxval = max(maxval, arr[i]);
        mnval=min(mnval,arr[i]);
    }

    // create and initialize count array
    vector<int> count(maxval-mnval + 1, 0);
    // count frequency of each element
    for (int i = 0; i < n; i++)
        count[arr[i]-mnval]++;

    // compute prefix sum
    for (int i = 1; i <= maxval-mnval; i++){
        count[i] += count[i - 1];
    }
    
    // build output array
    vector<int> ans(n);
    for (int i = n - 1; i >= 0; i--) {
        int idx=count[arr[i]-mnval] - 1;
        ans[idx] = arr[i];
        count[arr[i]-mnval]--;
    }

    return ans;
}

int main() {
    vector<int> arr = {7,8,9,5,5,5,6,8,8,8,9,7,6};
    vector<int> sorted = countsort(arr);

    for (int x : sorted)
        cout << x << " ";

    return 0;
}
```

Output 5 5 5 6 6 7 7 8 8 8 8 9 9 


![alt text](image.png)

## Radix sort 

![alt text](image-1.png)


![alt text](image-2.png)

```cpp
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Stable Counting Sort based on a specific digit (exp)
void countSort(vector<int>& arr, int exp) {
    int n = arr.size();
    vector<int> output(n);
    vector<int> freq(10, 0);

    // Store count of occurrences in freq[]
    for (int i = 0; i < n; i++) {
        int digit = (arr[i] / exp) % 10;
        freq[digit]++;
    }

    // Change freq[i] so that freq[i] contains actual position 
    // of this digit in output[]
    for (int i = 1; i < 10; i++) {
        freq[i] += freq[i - 1];
    }

    // Build the output array (Traverse backward for stability)
    for (int i = n - 1; i >= 0; i--) {
        int digit = (arr[i] / exp) % 10;
        int pos = freq[digit];
        output[pos - 1] = arr[i];
        freq[digit]--;
    }

    // Copy the output array to arr[], so that arr[] contains 
    // numbers sorted according to current digit
    for (int i = 0; i < n; i++) {
        arr[i] = output[i];
    }
}

void radixSort(vector<int>& arr) {
    if (arr.empty()) return;

    // Find the maximum number to know number of digits
    int mx = arr[0];
    for (int val : arr) {
        if (val > mx) mx = val;
    }

    // Do counting sort for every digit. 
    // Instead of passing digit number, exp is passed. 
    // exp is 10^i where i is current digit number.
    for (int exp = 1; mx / exp > 0; exp *= 10) {
        countSort(arr, exp);
    }
}

void display(const vector<int>& arr) {
    for (int i : arr) cout << i << " ";
    cout << endl;
}

int main() {
    vector<int> data = {170, 45, 75, 90, 802, 24, 2, 66};
    radixSort(data);
    display(data);
    return 0;
}

```

![alt text](image-3.png)




# Time Complexity Analysis: Radix Sort

The overall time complexity of Radix Sort is **$O(d \cdot (n + k))$**, where:
* **$n$**: The number of elements in the input array.
* **$d$**: The number of digits in the maximum element (number of passes).
* **$k$**: The range of the input values for the stable sort (base of the number system).

---

### 1. Breakdown by Components

#### A. Finding the Maximum Element
* The algorithm first iterates through the array once to find `mx`.
* **Complexity:** $O(n)$.

#### B. The External Loop (Digit Passes)
* The `while` loop in `radixSort` runs once for every digit in the largest number.
* For a number like 802, it runs 3 times (ones, tens, hundreds).
* **Complexity:** $O(d)$.

#### C. The Internal Subroutine (Counting Sort)
Inside each of the $d$ passes, `countSort` is called, which performs the following:
1.  **Frequency Count:** Iterates through $n$ elements to populate the `freq` array.
2.  **Prefix Sum:** Iterates through the `freq` array of size $k$ (which is 10 for decimal).
3.  **Output Array Construction:** Iterates through $n$ elements backwards to ensure stability.
4.  **Copying Back:** Iterates through $n$ elements to update the original array.
* **Complexity per pass:** $O(n + k)$.

---

### 2. Total Complexity Calculation
Since the $O(n + k)$ Counting Sort is nested inside the $O(d)$ loop:
$$Total\ Time = O(d \cdot (n + k))$$

---

### 3. Comparison with Other Sorting Algorithms

| Algorithm | Best Case | Average Case | Worst Case |
| :--- | :--- | :--- | :--- |
| **Radix Sort** | $O(d \cdot (n + k))$ | $O(d \cdot (n + k))$ | $O(d \cdot (n + k))$ |
| **Quick Sort** | $O(n \log n)$ | $O(n \log n)$ | $O(n^2)$ |
| **Merge Sort** | $O(n \log n)$ | $O(n \log n)$ | $O(n \log n)$ |

### 4. Key Takeaways
* **Not Comparison-Based:** Unlike QuickSort or MergeSort, Radix Sort does not compare elements directly, allowing it to bypass the $O(n \log n)$ lower bound for sorting.
* **Efficiency:** If the number of digits $d$ is small (constant), Radix Sort can appear to perform in linear $O(n)$ time.
* **Dependency:** The complexity is heavily dependent on the word size of the integers being sorted.


# Why Radix Sort is Less Popular Than Merge Sort

Although Radix Sort can achieve $O(n)$ performance when the number of digits $d$ is small, it faces several limitations that make **Merge Sort** a more robust choice for standard libraries.

---

### 1. Data Type Restrictions
* **Radix Sort:** It is a **non-comparison** sort designed specifically for integers, fixed-length strings, or data that can be mapped to integer keys. It is difficult to implement for floating-point numbers or complex custom objects.
* **Merge Sort:** It is a **comparison-based** sort. It can sort *any* data type as long as a "less than" operator is defined, making it much more versatile for general-purpose programming.

---

### 2. Space Inefficiency
* **Radix Sort:** Requires $O(n + k)$ auxiliary space to store the `output` and `freq` arrays for every pass.
* **Merge Sort:** Also requires $O(n)$ space, but modern implementations (like Timsort) are highly optimized for memory locality.
* **The Catch:** In Radix Sort, if the range of digits ($k$) or the number of elements ($n$) is large, the constant factors in memory allocation and deallocation can significantly slow down the program compared to the predictable overhead of Merge Sort.

---

### 3. Hardware and Cache Performance
* **Merge Sort:** Accesses data sequentially (linear scanning of sub-arrays). This is extremely "cache-friendly," as modern CPUs can pre-fetch the next elements of the array efficiently.
* **Radix Sort:** Often involves scattered memory access patterns when placing elements into the `output` array based on their digits. This leads to more **cache misses**, which can make it slower in practice than an $O(n \log n)$ algorithm like Merge Sort on modern hardware.

---

### 4. Constant Factors ($d$ vs $\log n$)
The time complexity of Radix Sort is $O(d \cdot n)$. 
* For 64-bit integers, $d$ can be up to 20 (for base 10).
* For Merge Sort, $\log n$ only reaches 20 when $n$ is roughly 1,000,000.
* **The Result:** For many practical array sizes, $d$ is actually larger than or equal to $\log n$, meaning Radix Sort loses its mathematical advantage while keeping its architectural disadvantages.


# The $d$ vs. $\log n$ Paradox

In Big O notation, we often assume $d$ (number of digits) is a small constant. However, for modern computing, $d$ is often large enough to make Radix Sort slower than Merge Sort.

### 1. Understanding $d$ (Radix Sort)
A 64-bit integer can hold values up to $18,446,744,073,709,551,615$. 
* In base 10, this number has **20 digits**.
* This means Radix Sort must perform **20 full passes** over the entire array ($20 \times n$ operations) to guarantee it is sorted.

### 2. Understanding $\log n$ (Merge Sort)
Merge Sort performs $\log_2 n$ passes over the data. 
* If $n = 1,000,000$, then $\log_2(1,000,000) \approx 19.93$ (roughly **20 passes**).
* If $n$ is smaller than a million, Merge Sort actually performs **fewer** passes than Radix Sort.

---

### 3. The Comparison at Different Scales
Let's look at how many passes each algorithm takes for 64-bit integers:

| Array Size ($n$) | Radix Sort Passes ($d$) | Merge Sort Passes ($\log_2 n$) | Winner (by Pass Count) |
| :--- | :--- | :--- | :--- |
| **1,000** | 20 | 10 | **Merge Sort** |
| **100,000** | 20 | 17 | **Merge Sort** |
| **1,048,576** | 20 | 20 | **Tie** |
| **10,000,000** | 20 | 24 | **Radix Sort** |

---

### 4. Why Merge Sort still wins the "Tie"
Even when the number of passes is the same (at $n \approx 10^6$), Merge Sort is usually faster because:

* **Simple Operations:** Merge Sort uses direct comparisons, which are very fast for CPUs. Radix Sort uses division, modulo, and multiple array writes per element, which are more "expensive" operations.
* **Cache Locality:** Merge Sort works on contiguous chunks of memory. Radix Sort jumps around the `output` array to place elements in their correct "buckets," leading to cache misses.
* **Overhead:** Radix Sort requires allocating and managing large auxiliary arrays (`freq` and `output`) for every single pass.

### Summary
For Radix Sort to truly outperform Merge Sort on 64-bit integers, your array usually needs to be **significantly larger than 1 million elements**. For smaller arrays, the "logarithmic" overhead of Merge Sort is actually smaller than the "constant" overhead of checking every digit in a 64-bit number.

---

### Summary Table

| Feature | Radix Sort | Merge Sort |
| :--- | :--- | :--- |
| **Generality** | Limited (Integers/Strings) | Universal (Any comparable type) |
| **Stability** | Yes | Yes |
| **Cache Friendliness** | Low | High |
| **Worst-Case TC** | $O(d \cdot n)$ | $O(n \log n)$ |
| **Main Drawback** | High cache misses & type limits | Extra $O(n)$ memory |

---

### Final Verdict
Merge Sort is used in standard libraries (like Java's `Arrays.sort` for objects) because it is **predictable, stable, and works on everything**. Radix Sort is treated as a **specialized tool** used only when you are certain you are sorting massive amounts of integers with a limited number of digits.
