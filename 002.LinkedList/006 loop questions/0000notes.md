# Notes


![alt text](<004 loop questions_240218_115658 (1).jpg>)
 ![alt text](<004 loop questions_240218_115658 (1)(1).jpg>)
  ![alt text](<004 loop questions_240218_115658 (1)(2).jpg>)

  ```cpp
/*
Definition of singly linked list:
struct ListNode
{
    int val;
    ListNode *next;
    ListNode()
    {
        val = 0;
        next = NULL;
    }
    ListNode(int data1)
    {
        val = data1;
        next = NULL;
    }
    ListNode(int data1, ListNode *next1)
    {
        val = data1;
        next = next1;
    }
};
*/

class Solution {
public:
    bool hasCycle(ListNode *head) {
        ListNode * slow=head;
        ListNode * fast=head;
        while(fast!=nullptr && fast->next !=nullptr){
            slow=slow->next;
            fast=fast->next->next;
            if (slow==fast) return true;
        }
        return false;
    }
};

  ```
   ![alt text](<004 loop questions_240218_115658 (1)(3).jpg>)
    ![alt text](<004 loop questions_240218_115658 (1)(4).jpg>) 
   ![alt text](<004 loop questions_240218_115658 (1)(5).jpg>) 
   
### Starting point of loop code

```cpp

/*
Definition of singly linked list:
struct ListNode
{
    int val;
    ListNode *next;
    ListNode()
    {
        val = 0;
        next = NULL;
    }
    ListNode(int data1)
    {
        val = data1;
        next = NULL;
    }
    ListNode(int data1, ListNode *next1)
    {
        val = data1;
        next = next1;
    }
};
*/

class Solution {
    ListNode * hasCycle(ListNode *head) {
        ListNode * slow=head;
        ListNode * fast=head;
        while(fast!=nullptr && fast->next !=nullptr){
            slow=slow->next;
            fast=fast->next->next;
            if (slow==fast) return fast;
        }
        return nullptr;
    }
public:
    ListNode *findStartingPoint(ListNode *head) {
        ListNode* fast=hasCycle(head);
        if(fast==nullptr) return fast;
        ListNode * slow=head;
        while(slow!=fast){
            slow=slow->next;
            fast=fast->next;
        }
        return slow;
    }
};
```

# Mathematical Proof: Floyd’s Cycle-Finding Algorithm

To find the starting point of a loop, we use the algebraic relationship between the **Tortoise** (slow) and the **Hare** (fast).

## 1. Defining the Variables
Let:
* **$L$**: Distance from the Head to the Loop Start.
* **$C$**: Total length of the Cycle.
* **$d$**: Distance from the Loop Start to the Meeting Point.
* **$n$**: Number of full laps the Hare ran inside the loop.

To be ultra-precise about what $n$ represents: $n$ is the number of full laps the Fast pointer completes within the loop before the meeting happens.

---

## 2. Why the Slow Pointer Meets in One Rotation
A common question is: *How do we know the slow pointer hasn't done multiple laps?*

1.  **Entry Point:** When the slow pointer reaches the Loop Start, the fast pointer is already inside the loop at some position $k$.
2.  **Relative Distance:** The fast pointer is $C - k$ steps "behind" the slow pointer.
3.  **Relative Speed:** Every step, the fast pointer closes the gap by $1$ unit (since $2 - 1 = 1$).
4.  **The Catch:** It will take $C - k$ steps for them to meet. Since $C - k < C$, the slow pointer will always be caught **before** it completes one full rotation ($C$ steps).

Therefore, the distance the slow pointer travels ($T$) is strictly:
$$T = L + d$$

---

## 3. The Algebraic Proof
At the meeting point, the fast pointer has traveled exactly twice the distance of the slow pointer ($H = 2T$).

1.  **Distance of Slow:** $T = L + d$
2.  **Distance of Fast:** $H = L + nC + d$
3.  **The Equation:**
    The SubstitutionSince $H = 2vt$ and $T = vt$, we can substitute $vt$ with $T$:$$H = 2(T)$$
    $$L + nC + d = 2(L + d)$$
4.  **Simplify:**
    $$L + nC + d = 2L + 2d$$
5.  **Isolate $L$:**
    $$nC = L + d$$
    $$L = nC - d$$

### The "Aha!" Moment
We can rewrite $L = nC - d$ as:
$$L = (n - 1)C + (C - d)$$

This tells us that the distance from the **Head to the Loop Start** ($L$) is mathematically equal to:
* $(n - 1)$ full laps around the cycle...
* plus the **remaining distance** from the meeting point to the loop start ($C - d$).



---

## 4. Implementation Logic
Because $L = (n - 1)C + (C - d)$:
1.  Move one pointer back to the **Head**.
2.  Keep the other pointer at the **Meeting Point**.
3.  Move both at the **same speed** ($1$ step at a time).
4.  They will meet at the **Loop Start**.

# Can fast overtake slow?? No lets see why

# Proof: The Discrete Gap Principle
**Goal:** To prove that the Fast pointer ($2x$) cannot "jump over" the Slow pointer ($1x$) in a linked list cycle.

---

## 1. Defining the State
Let's analyze the system at any time $t$ after the slow pointer has entered the loop.

* $S_t$: Position of the **Slow** pointer.
* $F_t$: Position of the **Fast** pointer.
* $C$: The total number of nodes in the cycle.
* $G_t$: The **Gap** (the number of steps the Fast pointer is "behind" the Slow pointer).

Mathematically, the gap is:
$$G_t = (S_t - F_t) \pmod C$$



---

## 2. The Transition (Step $t$ to $t+1$)
In a linked list, movement happens in discrete integer steps. When we move to the next iteration:
1.  **Slow moves 1 step:** $S_{t+1} = S_t + 1$
2.  **Fast moves 2 steps:** $F_{t+1} = F_t + 2$

Now, let's calculate the new gap $G_{t+1}$:
$$G_{t+1} = (S_{t+1} - F_{t+1}) \pmod C$$
$$G_{t+1} = ((S_t + 1) - (F_t + 2)) \pmod C$$
$$G_{t+1} = (S_t - F_t - 1) \pmod C$$

Substituting $G_t$ back into the equation:
$$G_{t+1} = (G_t - 1) \pmod C$$

---

## 3. The Logical Conclusion
This recurrence relation ($G_{t+1} = G_t - 1$) proves two critical things:

### A. The "No-Jump" Guarantee
Because the gap decreases by **exactly 1** every step, the sequence of gaps must be:
$$G_0, G_0-1, G_0-2, \dots, 2, 1, 0$$
Since the sequence involves integers and decreases by only 1 unit per step, it is **impossible** to move from a positive gap (behind) to a negative/overflow gap (ahead) without hitting **exactly 0**.

### B. The "One-Lap" Guarantee
The maximum initial gap $G_0$ when the Slow pointer enters the loop is $C-1$. 
* It takes exactly $G_0$ steps to reach a gap of 0.
* Since $G_0 < C$, the Slow pointer will have traveled fewer than $C$ nodes.
* **Result:** They meet before the Slow pointer completes its first revolution.



---

## 4. Summary
In any discrete system, if object A reduces the distance to object B by **1 unit per time step**, they **must** occupy the same coordinate before the distance becomes negative. In the context of Floyd's algorithm, $G_t = 0$ means `slow == fast`, triggering the detection.

```java

/**
 * Definition for singly-linked list.
 * class ListNode {
 *     int val;
 *     ListNode next;
 *     ListNode(int x) {
 *         val = x;
 *         next = null;
 *     }
 * }
 */
public class Solution {
    public ListNode detectCycle(ListNode head) {
        if(head==null||head.next==null) return null;
        ListNode slow=head;
        ListNode fast=head;
        while(fast!=null&&fast.next!=null){
            
            slow=slow.next;
            fast=fast.next.next;
            if(slow==fast) 
                 break;
        }
        if(slow==fast){
           slow=head;
           while(slow!=fast){
               slow=slow.next;
               fast=fast.next;
           }
            return slow;
        }
      return null;
    }
}
```

---

### What if we use $(F_t - S_t)$?

If we define the gap as the distance the Fast pointer is **ahead** of the Slow pointer:

1. **The Change:** Instead of the gap shrinking, the gap **grows** by 1 step every iteration: $G_{t+1} = G_t + 1$.
2. **The Wrap-Around:** In a cycle of length $C$, "gaining" a distance of $C$ is the same as returning to the same spot.
3. **The Conclusion:** The meeting occurs when the Fast pointer has gained exactly one full lap (or multiple laps) on the Slow pointer. Mathematically, $t \equiv 0 \pmod C$, which leads to the same meeting condition.

**Analogy:** If you are running 1 mph faster than me on a circular track, you are moving "away" from me, but eventually, you will come around and hit me from behind!

---

### Why the Gap MUST hit 0 in $C-1$ steps

1. **Relative Speed:** Since $V_{fast} = 2$ and $V_{slow} = 1$, the Hare closes the distance by exactly **1 node per second**.
2. **Maximum Distance:** In a circle of size $C$, the furthest the Hare can ever be from the Tortoise is $C-1$ nodes.
3. **The Guarantee:** - If the gap is 5, they meet in 5 steps.
   - If the gap is 10, they meet in 10 steps.
   - If the gap is $C-1$, they meet in $C-1$ steps.
4. **Conclusion:** Since the meeting happens in $C-1$ steps, and the Tortoise needs $C$ steps to finish a lap, the Hare **always** catches the Tortoise before the Tortoise completes its first circle.


### Origin of $2t$ and $t$ in the Equation

The terms are based on the **Speed** of the pointers:

- **Slow Pointer ($S_t$):** Moves at 1 step/time. 
  - Distance = $1 \times t = \mathbf{t}$
- **Fast Pointer ($F_t$):** Moves at 2 steps/time. 
  - Distance = $2 \times t = \mathbf{2t}$

**The Equation Breakdown:**
- $G_t = (F_t - S_t) \pmod C$
- $G_t = (2t - t) \pmod C$
- $G_t = t \pmod C$

### Mathematical Proof: Why Forward Gap $(F_t - S_t)$ Still Works

1. **The Growth:** Using $F_t - S_t$, the gap $G$ grows by 1 each step: $G_t = t \pmod C$.
2. **The "Lap" Concept:** In a cycle, the Fast pointer meets the Slow pointer again when it completes one full lap more than the Slow pointer.
3. **The Meeting Point:** - We need $G_t = 0 \pmod C$.
   - This occurs when $t = C, 2C, 3C \dots$
4. **The Guarantee:** Since the Slow pointer only moves 1 step per $t$, and the first meeting happens at $t = C$, the Slow pointer will have moved exactly distance $C$ (one full lap) and met the Fast pointer back at the start of the loop.

**Conclusion:** Whether the gap is "shrinking" from $C$ to $0$ or "growing" from $0$ to $C$, they land on the same node at the exact same time.
This shows that the gap increases by exactly 1 step every time $t$ increases. They will meet when $t$ becomes a multiple of $C$, because $C \pmod C = 0$.

### Proof: Why Slow Pointer Travels < 1 Full Cycle in this case tooo

1. **Relative Speed:** Fast moves at 2, Slow moves at 1. The gap increases by **1 unit per step**.
2. **The "Lap" Requirement:** To meet again, the Fast pointer must gain exactly **C** distance (one full lap) on the Slow pointer.
3. **Time to Meet:** It takes exactly **C steps** to gain a gap of C.
4. **Slow Pointer's Journey:** - In C steps, the Slow pointer travels distance C (exactly 1 lap).
   - **Crucial Point:** Because the Fast pointer is already inside the loop when the Slow pointer enters, the starting gap is already $> 0$.
   - This means they will meet in **less than C steps**.
   
**Conclusion:** Since they meet in $t < C$ steps, the Slow pointer travels a distance $D < C$. It is mathematically impossible for the Slow pointer to finish a full cycle before the Fast pointer catches it.

## More details
![alt text](<008 Ll loop questions_250420_111808.jpg>)
![alt text](<008 Ll loop questions_250420_111808(1).jpg>) ![alt text](<008 Ll loop questions_250420_111808(2).jpg>)

---

   ![alt text](<004 loop questions_240218_115658 (1)(6).jpg>)

![alt text](<004 loop questions_240218_115658 (1)(7).jpg>) ![alt text](<004 loop questions_240218_115658 (1)(8).jpg>) ![alt text](<004 loop questions_240218_115658 (1)(9).jpg>) 

```cpp

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
    ListNode * getTail(ListNode * head){
        if(head==nullptr|| head->next==nullptr) return head;
        ListNode * curr=head;
        while(curr->next!=nullptr){
            curr=curr->next;
        }
        return curr;
    }
    ListNode * hasCycle(ListNode *head) {
        ListNode * slow=head;
        ListNode * fast=head;
        while(fast!=nullptr && fast->next !=nullptr){
            slow=slow->next;
            fast=fast->next->next;
            if (slow==fast) return fast;
        }
        return nullptr;
    }

    ListNode *findStartingPoint(ListNode *head) {
        ListNode* fast=hasCycle(head);
        if(fast==nullptr) return fast;
        ListNode * slow=head;
        while(slow!=fast){
            slow=slow->next;
            fast=fast->next;
        }
        return slow;
    }
public:
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        if(headA==nullptr ||headB==nullptr) return nullptr;
        ListNode * tail=getTail(headA);      
        tail->next=headB;
        ListNode* intPoint=findStartingPoint(headA);
        tail->next=nullptr;
        return intPoint;
    }
};
```


### Find length of loop of LL

```cpp
/*
Definition of singly linked list:
struct ListNode
{
    int val;
    ListNode *next;
    ListNode()
    {
        val = 0;
        next = NULL;
    }
    ListNode(int data1)
    {
        val = data1;
        next = NULL;
    }
    ListNode(int data1, ListNode *next1)
    {
        val = data1;
        next = next1;
    }
};
*/

class Solution {
    ListNode * hasCycle(ListNode *head) {
        ListNode * slow=head;
        ListNode * fast=head;
        while(fast!=nullptr && fast->next !=nullptr){
            slow=slow->next;
            fast=fast->next->next;
            if (slow==fast) return fast;
        }
        return nullptr;
    }

public:
    int findLengthOfLoop(ListNode *head) {
        ListNode * ptr=hasCycle(head);
        if(ptr==nullptr) return 0;
        ListNode * curr=ptr->next;
        int len=1;
        while(curr!=ptr){
            curr=curr->next;
            len++;
        }
        return len;

    }
};

```






