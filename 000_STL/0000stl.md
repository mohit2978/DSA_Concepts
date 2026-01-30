## 📚 C++ STL Functions for Competitive Programming (CP)

### I. Containers (Data Structures)

| Container | Header | Description | Key Functions/Properties |
| :--- | :--- | :--- | :--- |
| **`vector<T>`** | `<vector>` | Dynamic array. Fast random access. | `push_back()`, `pop_back()`, `size()`, `empty()`, `resize()`, `begin()`, `end()`, `[i]` (access) |
| **`string`** | `<string>` | Sequence of characters. | `size()`, `length()`, `append()`, `substr()`, `find()`, `c_str()` |
| **`pair<T1, T2>`** | `<utility>` | Groups two heterogeneous values. | `first`, `second`, `make_pair()` |
| **`map<K, V>`** | `<map>` | Sorted associative container (stores key-value pairs). Implemented as a Self-Balancing BST. | `insert()`, `erase()`, `find()`, `count()`, `begin()`, `end()`, `[key]` (access/insert) |
| **`unordered_map<K, V>`** | `<unordered_map>` | Unsorted associative container (hash table). Faster average case access than `map`. | `insert()`, `erase()`, `find()`, `count()`, `[key]` (access/insert) |
| **`set<T>`** | `<set>` | Sorted container of unique elements. Implemented as a Self-Balancing BST. | `insert()`, `erase()`, `find()`, `count()`, `lower_bound()`, `upper_bound()` |
| **`unordered_set<T>`** | `<unordered_set>` | Unsorted container of unique elements (hash table). Faster average case access than `set`. | `insert()`, `erase()`, `find()`, `count()` |
| **`priority_queue<T>`** | `<queue>` | Max-heap by default (largest element at top). | `push()`, `pop()`, `top()`, `empty()`, `size()` |
| **`queue<T>`** | `<queue>` | FIFO (First-In, First-Out) structure. | `push()`, `pop()`, `front()`, `empty()`, `size()` |
| **`stack<T>`** | `<stack>` | LIFO (Last-In, First-Out) structure. | `push()`, `pop()`, `top()`, `empty()`, `size()` |
| **`deque<T>`** | `<deque>` | Double-ended queue. Fast insertion/deletion at both ends. | `push_front()`, `push_back()`, `pop_front()`, `pop_back()`, `front()`, `back()` |

---

### II. Algorithms (`<algorithm>`)

| Function | Usage | Description | Time Complexity |
| :--- | :--- | :--- | :--- |
| **`sort()`** | `sort(begin, end)` | Sorts a range of elements. | $O(N \log N)$ |
| **`reverse()`** | `reverse(begin, end)` | Reverses the order of elements in a range. | $O(N)$ |
| **`max()`**, **`min()`** | `max(a, b)`, `min({a, b, c, ...})` | Returns the greater/lesser of two or more values. | $O(1)$ / $O(N)$ |
| **`max_element()`**, **`min_element()`** | `max_element(begin, end)` | Returns an iterator to the largest/smallest element in a range. | $O(N)$ |
| **`swap()`** | `swap(a, b)` | Exchanges the values of two variables. | $O(1)$ |
| **`fill()`** | `fill(begin, end, value)` | Assigns a new value to all elements in a range. | $O(N)$ |
| **`unique()`** | `unique(begin, end)` | Removes consecutive duplicate elements (does not change container size; returns iterator to new end). **Requires prior sorting.** | $O(N)$ |
| **`lower_bound()`** | `lower_bound(begin, end, val)` | Finds the first element $\ge$ `val` in a sorted range. | $O(\log N)$ |
| **`upper_bound()`** | `upper_bound(begin, end, val)` | Finds the first element $>$ `val` in a sorted range. | $O(\log N)$ |
| **`binary_search()`** | `binary_search(begin, end, val)` | Checks if an element exists in a sorted range. | $O(\log N)$ |
| **`next_permutation()`** | `next_permutation(begin, end)` | Generates the lexicographically next greater permutation. | $O(N)$ |

---

### III. Numeric Operations (`<numeric>`)

| Function | Usage | Description | Time Complexity |
| :--- | :--- | :--- | :--- |
| **`accumulate()`** | `accumulate(begin, end, initial_sum)` | Computes the sum of elements in a range (or applies a custom binary operation). | $O(N)$ |
| **`iota()`** | `iota(begin, end, value)` | Fills a range with sequential increasing values starting from `value`. | $O(N)$ |
| **`gcd()`** | `std::gcd(a, b)` (C++17) | Computes the greatest common divisor of $a$ and $b$. | $O(\log(\min(a, b)))$ |
| **`lcm()`** | `std::lcm(a, b)` (C++17) | Computes the least common multiple of $a$ and $b$. | $O(\log(\min(a, b)))$ |

---

### IV. Functional (`<functional>`)

| Function/Object | Usage | Description |
| :--- | :--- | :--- |
| **`std::function`** | `std::function<R(Args...)> f` | A type-safe wrapper for function pointers, lambda functions, or function objects. |
| **`std::bind`** | `std::bind(func, arg1, _1, ...)` | Creates a new function object by binding arguments to an existing function. (Less common in modern C++ due to lambdas.) |
| **`std::greater<T>`** | Used as a comparator: `priority_queue<int, vector<int>, greater<int>>` | Comparator that defines the "less than" relationship as the greater of the two values (useful for min-heaps/descending sort). |


# std::list STL (Doubly Linked List)

### 1. Core Properties
- **Non-Contiguous**: Elements are scattered in memory.
- **Bi-Directional**: Each node has `next` and `prev`.
- **No Random Access**: You cannot use `l[i]`. You must use an **iterator** to walk the list.

### 2. When to use List?
- You need to frequently **insert or delete** from the **front** or the **middle**.
- You don't know the size and want to avoid the $O(N)$ "reallocate and copy" cost of a vector.
- You do **not** need to jump to specific indices (like "give me the 500th element").

### 3. Important Special Member Functions
Unlike Vector, List has built-in optimized functions:
- `l.unique()`: Removes consecutive duplicate elements.
- `l.reverse()`: Reverses the list in $O(N)$ by swapping pointers.
- `l.sort()`: Uses a specialized Merge Sort ($O(N \log N)$) because `std::sort` doesn't work on lists.
- `l.splice()`: Moves elements from one list to another in $O(1)$ without copying.

### 4. The "Cache" Downside
Even though List is $O(1)$ for insertion, it is often **slower** than Vector for small amounts of data. 
- **Reason**: Vector's contiguous memory is "Cache Friendly." The CPU can predict the next element. 
- **List** requires the CPU to jump all over the RAM, causing "Cache Misses."


```cpp
#include <iostream>
#include <list>

int main() {
    std::list<int> l = {10, 20, 30};

    // 1. Adding elements
    l.push_back(40);    // [10, 20, 30, 40]
    l.push_front(5);    // [5, 10, 20, 30, 40]

    // 2. Accessing (No [] operator!)
    // int x = l[2];    // ERROR!
    int first = l.front();
    int last = l.back();

    // 3. Iterators (How we move through the chain)
    auto it = l.begin();
    std::advance(it, 2); // Move iterator to 3rd element
    l.insert(it, 25);    // Inserts 25 BEFORE the iterator

    // 4. Removal
    l.pop_front();
    l.remove(20);        // Removes ALL instances of 20 (Special List function)

    return 0;
}
```

### Comparison Table: Time Complexity

| Operation | `std::list` (DLL) | `std::vector` (Array) |
| :--- | :--- | :--- |
| **Random Access** (e.g., `arr[5]`) | **$O(N)$** (Must walk the chain) | **$O(1)$** (Direct jump) |
| **Insert/Delete at Front** | **$O(1)$** | **$O(N)$** (Must shift everyone) |
| **Insert/Delete at Back** | **$O(1)$** | **$O(1)$** (Amortized) |
| **Insert/Delete in Middle** | **$O(1)$*** | **$O(N)$** (Must shift everyone) |

> ***Note on Middle Insertion**: While the act of re-linking pointers is $O(1)$, you must first spend $O(N)$ time to reach the middle position using an iterator.

### Pro-Tip for Interviews
If an interviewer asks: "Why does `std::sort(l.begin(), l.end())` fail for a list?"

Answer: `std::sort` requires Random Access Iterators (the ability to jump around like it + 5). Since a list only allows you to step one-by-one (it++), you must use the list's own member function: l.sort().