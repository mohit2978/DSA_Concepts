# Notes 
![alt text](<002Hashmap heap recursion_240901_131144_260207_163123_0.png>) ![alt text](<002Hashmap heap recursion_240901_131144_260207_163123_1.png>) ![alt text](<002Hashmap heap recursion_240901_131144_260207_163123_2.png>) ![alt text](<002Hashmap heap recursion_240901_131144_260207_163123_3.png>) ![alt text](<002Hashmap heap recursion_240901_131144_260207_163123_4.png>) ![alt text](<002Hashmap heap recursion_240901_131144_260207_163123_5.png>) ![alt text](<002Hashmap heap recursion_240901_131144_260207_163123_6.png>) ![alt text](<002Hashmap heap recursion_240901_131144_260207_163123_7.png>) ![alt text](<002Hashmap heap recursion_240901_131144_260207_163123_8.png>) ![alt text](<002Hashmap heap recursion_240901_131144_260207_163123_9.png>) ![alt text](<002Hashmap heap recursion_240901_131144_260207_163123_10.png>) ![alt text](<002Hashmap heap recursion_240901_131144_260207_163123_11.png>) ![alt text](<002Hashmap heap recursion_240901_131144_260207_163123_12.png>) ![alt text](<002Hashmap heap recursion_240901_131144_260207_163123_13.png>) ![alt text](<002Hashmap heap recursion_240901_131144_260207_163123_14.png>) ![alt text](<002Hashmap heap recursion_240901_131144_260207_163123_15.png>) ![alt text](<002Hashmap heap recursion_240901_131144_260207_163123_16.png>) ![alt text](<002Hashmap heap recursion_240901_131144_260207_163123_17.png>)


![alt text](<002Hashmap heap recursion_240901_131144_260207_163123_18.png>) 




---

# 🏔️ HEAP — Complete Notes

## Image 1 — Comparison Table: Why Heap?

Before understanding Heap, the instructor compares 4 data structures across 4 operations to show WHY we need Heap.

| Data Structure | Search | Insert | Delete | Min/Max |
|---|---|---|---|---|
| Unsorted Array | O(N) | O(1) | O(N) | O(N) |
| Sorted Array | O(log N) | O(N) | O(N) | O(1) |
| Linked List | O(N) | O(1) | O(N) | O(N) |
| **Heap** | **O(log N)** | **O(log N)** | **O(log N)** | **O(1)** |

**Why is Delete O(N) in Unsorted Array?**
You first search (O(N)), then delete. But in a sorted array after deleting, you must shift all subsequent elements to fill the gap — that's another O(N). So the total cost stays O(N) but for a different reason.

**Why is Insert O(N) in Sorted Array?**
You must find the correct position to maintain sorted order (O(log N) search), but then shift all elements to the right to make room — that shifting is O(N).

**The critical insight the instructor makes:** Delete is always dependent on Search — you Search first, then Delete. So the time complexity of both is the same, EXCEPT in Sorted Array where you additionally need to shift elements after deletion to fill the empty space.

**Why is Min/Max O(1) in Sorted Array?**
Because the minimum is always at index 0 and maximum at the last index — constant time access.

**Why is Heap the best?**
No other data structure gives you O(log N) for Insert, Search, Delete AND O(1) for Min/Max simultaneously. This is the unique power of Heap.

---

## Image 2 — When to Use Heap & Binary Tree Types

**Important clarification on "insertion" terminology:**
When we say insert is O(1) for Unsorted Array or Linked List, we are NOT saying insert in sorted order. We are simply saying "insert into the data structure" — just add it anywhere. This is just insertion into a DS, not sorted insertion.

**The new data structure (Heap) gives us:**
- Insert → O(log N)
- Search → O(log N)
- Delete → O(log N)
- Find Min/Max → O(1)

**When do we use Heap?**
The instructor says: when **finding Min/Max is our primary task**, and we also need reasonably fast insert/search/delete — that's when we use Heap.

**Typical interview questions that require Heap:**
- Kth largest element
- Kth smallest element
- Kth minimum
- And similar order-statistic problems

**Binary Tree (BT) — Two Types:**

The instructor introduces two types of Binary Trees to set up the definition of Heap:

**1. Almost Complete Binary Tree:**
All levels are completely filled EXCEPT the last level. The last level is filled from LEFT to RIGHT (you cannot have a node on the right if the left is empty).

**2. Perfect Binary Tree:**
ALL levels are completely filled. Every internal node has exactly 2 children, and all leaf nodes are at the same level.

**Heaps are Almost Complete Binary Trees** — this is the structural definition of a Heap.

---

## Image 3 — Heap Structure, Height, and Implementation

**Why Almost Complete BT matters:**
Because Heap is an Almost Complete Binary Tree, its height is **always O(log N)**. This is guaranteed — it can never be skewed or unbalanced. This is what gives all heap operations their O(log N) guarantee.

**The instructor says:** Do a Heap Level 1 recording/video for deeper understanding of heap operations.

**Critical distinction — Array vs Heap Array:**
- A regular array is NOT a Heap
- But a **Heap Array** (an array used to represent a heap) IS used to make a Heap
- The array stores the tree level by level (BFS order)

**Critical distinction — Priority Queue vs Heap:**
- A Priority Queue is NOT a Heap
- A Priority Queue is an ADT (Abstract Data Type) — it defines behavior, not implementation
- It is USED to behave like a Heap
- Think of it like: Stack is an ADT, Array is used to implement it

**Practical rule for coding:**
- For **implementation** → use Array (to store the heap internally)
- For **solving problems/queries** → use Priority Queue (the interface Java/C++ provides)

---

# 🔁 RECURSION — Complete Notes

## Image 4 — Recursion Concepts + Intro to Hash Map

**Recursion Question 1 → Subsets of a given set**
This is a classic recursion problem. Given a set, generate all possible subsets (power set). This is solved using recursion by making include/exclude decisions at each element.

**Recursion Question 2 → Recursion with Backtracking = Pruning**
When we use Recursion WITH Backtracking, it is called **Pruning**.

Why "Pruning"? Because:
- We go to every possible solution path
- If a path does NOT lead to the desired solution
- We go BACK (backtrack) and try another path
- We prune (cut off) the dead-end branches

This is used in problems like N-Queens, Sudoku Solver, Rat in a Maze, etc.

**Recursion Question 3 → Divide & Conquer**
Quick Sort and Merge Sort are examples of **Recursion with Divide & Conquer**. You divide the problem into smaller subproblems, solve them recursively, and combine the results.

---

# 🗂️ HASH MAP — Complete Notes

## Image 4 (continued) — Hash Map Basics

**Hash Map operations and their time complexities:**
- Insert → O(1)
- Delete → O(1)
- Search on some index/key → O(1)

All three are O(1) — this is the power of Hash Map.

---

## Image 5 — Direct Access Table (DAT)

**Problem:** Count the frequency of elements in: `0, 1, 8, 4, 6, 8, 9, 1, 1, 0, 1`

**Solution approach:** Use a **Direct Access Table (DAT)**

What is a DAT? It is:
- Just a Hash Map where keys are numbers
- OR simply a plain array (if the frequency/value range is not very large)

**When can you use a plain array instead of a Hash Map?**
When the key range is small and known. For example, if all elements are between 0–9, you can use an array of size 10 as your "hash map."

**Rule:** For Count Sort type problems → Use DAT

The instructor then transitions: "Let's now see the Hash Map concept in detail."

---

## Image 6 — How Hash Map Works Internally

**The mechanism:**

There is a **Pool of Keys** (e.g., A, B, C, D, E, F, G, H).

These keys are passed through a **Hash Function**.

The Hash Function is applied ON the key and returns a number (an array index).

The value is then stored at that index in an array.

**So:** Based on the value returned by the Hash Function, the value is placed at that array index. The value is stored in the array at that position.

**Visually:**
```
Key (e.g., "C") → [Hash Function] → index 2 → Array[2] = value
```

This is why lookup is O(1) — given a key, apply the hash function, get the index directly, access the array at that index. No searching needed.

---

## Image 7 — Collision & Chaining

**Collision:** A collision occurs when **multiple keys map to the same array index** through the hash function.

**Example:** If h("A") = 3 and h("G") = 3, both want to go to index 3 — that's a collision.

**How to avoid collision?**
Use a better hash function that distributes keys more uniformly.

**But if collision still occurs, two main techniques to handle it:**

**Technique 1 — Chaining:**
- At each array index, instead of storing one value, store a **Linked List**
- When multiple keys map to the same index, all their values go into the Linked List at that index
- When searching, go to the index and then search within the Linked List

**Important note from instructor (in red):**
Chaining is what is used in interviews. No other method can be easily implemented in an interview setting.

**Searching in Chaining:**
We do searching within the Linked List at each index.

---

## Image 8 — Chaining: Load Factor & Time Complexity

**Linked List search takes O(N)** — but we try to keep the Linked List size limited.

**How?** By keeping the Linked List of size λ (lambda). This limits the size of each LL, so:
- Search time in each LL = O(λ)
- Insert time = O(λ)
- Delete time = O(λ)

Since λ is limited (kept small by design), we say insert and delete time is effectively **O(1)**.

**λ (lambda) is called the Load Factor.**

The load factor = number of elements / table size. When it gets too large, the hash table **rehashes** (resizes) itself to keep λ small.

**Other techniques for collision management exist** (mentioned at the bottom of Image 8), covered next.

---

## Image 9 — Open Addressing: Introduction & Linear Probing Setup

**Technique 2 — Open Addressing:**
In open addressing, all elements are stored IN the array itself — no linked lists, no extra memory outside the array.

When a collision occurs, we look for another empty slot in the array.

**Example setup:**
- Elements to insert: `11, 21, 44, 31, 22, 45, 43`
- Table size: 10
- Hash function: `h(x) = x % 10`

**Starting insertions:**

- 11 % 10 = 1 → 11 maps to index **1** ✓
- 21 % 10 = 1 → collision! Index 1 is taken → 21 goes to **next empty space** → index **2** ✓

**Key guarantee:** It is guaranteed that we will never have more elements than the table size. So we will always find an empty slot.

---

## Image 10 — Linear Probing: Continuing Insertions

Continuing from Image 9:

- 44 % 10 = 4 → maps to index **4** ✓
- 31 % 10 = 1 → index 1 is filled → try index 2 → filled → try index 3 → **31 goes to 3** ✓

**What is Linear Probing?**
When a collision happens, we search **linearly** (one by one, +1 each time) for the next empty slot. This linear search for an empty probe space is called **Linear Probing**.

**Table state so far:**

```
Index: 0  | 1  | 2  | 3  | 4  | 5 | 6 | 7 | 8 | 9
Value: _  | 11 | 21 | 31 | 44 | _ | _ | _ | _ | _
```

**Now comes 22:**
- 22 % 10 = 2 → index 2 is filled → linear probing → goes to next empty space → **index 5** ✓

(Index 3 and 4 are also filled, so probing goes 2→3→4→5, landing at 5.)

---

## Image 11 — Disadvantage of Linear Probing: Clustering

**Disadvantage of Linear Probing → Clustering**

Suppose indices 1, 2, 3, 6, 7 are already filled (a cluster exists).

**Question:** What is the probability of the next new element going to index 4?

At index 4, an element can arrive there if its hash maps to indices 1, 2, 3, OR 4 — because from any of those filled indices, linear probing will eventually push it to index 4.

- Elements ending in 1 → hash to 1 → probe → land at 4
- Elements ending in 2 → hash to 2 → probe → land at 4
- Elements ending in 3 → hash to 3 → probe → land at 4
- Elements ending in 4 → hash directly to 4

So probability of landing at index 4 = **4/10 = 40%**

Compare:
- Index 5 → only elements ending in 5 → probability = **1/10 = 10%**
- Index 8 → elements ending in 6, 7, 8 → probability = **3/10 = 30%**
- Index 9 → only elements ending in 9 → probability = **1/10 = 10%**
- Index 0 → only elements ending in 0 → probability = **1/10 = 10%**

All these add up to 100%.

**The problem:** The probability of getting filled NEAR the cluster (index 4) is **much higher** than other indices. So the cluster will keep growing!

---

## Image 12 — Primary Clustering: The Snowball Effect

**The real disadvantage:**
The chances of getting filled near a cluster is MORE than at any other index.

**Snowball analogy:**
Imagine a snowball rolling on snow. As it rolls, it picks up more snow and gets bigger. The bigger it gets, the MORE snow it picks up per roll. It just keeps growing.

Similarly:
- A smaller cluster has less probability of attracting the next element
- A larger cluster has MORE probability of attracting the next element
- So larger clusters grow even faster — a self-reinforcing cycle

This is called the **Clustering Effect** (or **Primary Clustering**) and we must avoid it.

This is why we don't use Linear Probing in practice.

---

## Image 13 — Search & Deletion in Linear Probing

**Search in Linear Probing:**
- Compute the hash index for the key
- Start searching linearly from that index
- Continue until: the value is found OR an **empty index** is found (if empty, the element doesn't exist)

**Deletion — The Problem:**

Suppose the table has: `11 | 21 | 31 | 41 | 55` at indices 1–5.

Now delete **21** from index 2.

Then search for **31**:
- 31 % 10 = 1 → go to index 1 (found 11, not 31)
- Linear probe → go to index 2 → it's EMPTY now (21 was deleted)
- The algorithm concludes: **31 is not found** ❌

But 31 IS there at index 3! The deletion of 21 created a false empty slot that terminated the search too early.

**Solution → Use a Marker:**
Instead of truly deleting (making the slot empty), we place a **Marker** (also called a tombstone) at the deleted slot. The marker means: "Something was here before, but it's been deleted."

When searching and we encounter a Marker, we **continue searching** — we do NOT stop. We only stop if we find a genuinely empty slot (one that never had an element).

---

## Image 14 — Marker Behavior & Worst Case of Open Addressing

**Behavior on seeing a Marker during search:**
On seeing a Marker → **continue the search** (don't stop, the element might be further ahead).

**Time Complexity of Insert, Search, Delete in Open Addressing:**
In the **worst case**, they can all become **O(N)** — this happens when only one giant cluster exists and every probe goes through it linearly. It's essentially a linear search at that point.

**Clustering is the core problem here.** That's why we don't prefer Linear Probing.

---

## Image 15 — Quadratic Probing & Primary Clustering Solution

**Why Linear Probing fails:** Because we jump linearly (+1 each time), we create physical adjacent clusters (Primary Clustering).

**Solution → Quadratic Probing:**
Instead of jumping by 1 each time, we jump by **quadratic increments** (1, 4, 9, 16…).

**Formula for Linear Probing:**
`h(k, i) = (h(k) + i) mod TableSize`
(where i = collision number: 1st collision i=1, 2nd collision i=2, etc.)

**Formula for Quadratic Probing:**
`h(k, i) = (h(k) + c₁·i + c₂·i²) % TableSize`

This means:
- 1st collision → jump by c₁·1 + c₂·1² positions
- 2nd collision → jump by c₁·2 + c₂·4 positions
- 3rd collision → jump by c₁·3 + c₂·9 positions
- The jumps grow quadratically, spreading elements far apart

**Result:** No physical adjacent clusters form. Elements spread out more.

---

## Image 16 — Quadratic Probing: Secondary Clustering

**Quadratic Probing solves Primary Clustering**, but introduces a new problem.

Even though elements don't cluster physically (no adjacent filled slots), consider this:

If two keys X and Y both hash to the **same initial index**, then:
- They will both follow the **exact same probe sequence** after the collision
- 1st probe → same position
- 2nd probe → same position
- And so on...

They fight for the same slots even if they are physically far apart in the array. They create a **virtual cluster** — a "Secondary Cluster."

**This is called Secondary Clustering.**

The instructor explains: "Here we don't have clusters physically, but if two elements map to the same index in the array, they will follow the same sequence to insert into the array." This is like a virtual cluster, hence "Secondary Clustering."

---

## Image 17 — Double Hashing: Solution to Secondary Clustering

**Problem with Quadratic Probing:** Two keys colliding at the same index always follow the same probe sequence → Secondary Clustering.

**Root cause:** The probe sequence after collision is the same for both keys because the jump formula only depends on the collision number `i`, not on the key itself.

**Solution → Double Hashing:**
Use a SECOND, DIFFERENT hash function `h'(k)` that depends on the KEY:

`h(k, i) = (h(k) + i · h'(k)) mod TableSize`

Where:
- `h(k)` = primary hash function
- `h'(k)` = secondary hash function (completely different from h(k))
- `i` = collision number

**Now:** If keys X and Y both collide at the same index, their jump sizes are different because `h'(X) ≠ h'(Y)`. So they follow **completely different probe sequences** after the collision.

**No Secondary Clustering!**

The instructor notes: If two numbers do a collision, then they should NOT follow the same sequence after the collision management technique. Double Hashing achieves this.

---

## Image 18 — h'(k) Design & Triple Hashing

**What should h'(k) be?**
The secondary hash function `h'(k)` can be something like **SHA-256** or any function that guarantees:

> Two different values (keys) will give two different outputs (indices).

This ensures that colliding keys will always have different jump sizes and thus different probe sequences.

**Triple Hashing:**
Some people even use Triple Hashing — a third hash function. But:
- More complex to implement
- More time-consuming to compute
- It's a **tradeoff**: more hash functions = better collision management but more complexity

**General rule in practice:**
We use **Double Hashing only** — it provides a good balance between collision management quality and implementation complexity. Triple hashing is rarely worth it.

---

## Image 19 — Context & Purpose of These Notes

**This entire material** (Heap, Recursion, Hash Map) is prepared for:
- **Telephonic rounds** (phone interviews)
- **Face-to-face rounds** at top product companies like **Facebook (Meta)** and **Amazon**

This is interview-level DSA content — the depth of understanding expected for FAANG-level technical interviews.

---

## Complete Summary

**Heap:** An Almost Complete Binary Tree with O(log N) height always. Use it when Min/Max finding is the primary task. Implemented using Array, queried using Priority Queue.

**Recursion:** Three patterns — Subsets (pure recursion), Backtracking/Pruning (recursion + backtrack on failure), Divide & Conquer (QuickSort, MergeSort).

**Hash Map:** O(1) insert/delete/search. Collisions handled by Chaining (use in interviews, uses Linked Lists, introduces Load Factor λ) or Open Addressing (Linear Probing → Primary Clustering, Quadratic Probing → Secondary Clustering, Double Hashing → best solution, uses two different hash functions).