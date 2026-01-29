# Power set 

This can be acheieved by recusrion but let us see this way too

# Power Set Generation via Bitmasking

### 1. The Strategy: The Binary Checklist
Every subset is represented by a binary number between $0$ and $2^n - 1$.
- Imagine `nums = [10, 20, 30]`.
- We treat the bits of an integer `val` as a "Yes/No" checklist for each element.

| Decimal (`val`) | Binary (`i=2, 1, 0`) | Logic (Bits Set) | Resulting Subset |
| :--- | :--- | :--- | :--- |
| **0** | `0 0 0` | None | `[]` |
| **1** | `0 0 1` | 0th bit set | `[10]` |
| **3** | `0 1 1` | 0th & 1st bits set | `[10, 20]` |
| **7** | `1 1 1` | All bits set | `[10, 20, 30]` |

---

### 2. Code Breakdown

#### **A. The Total Count ($2^n$)**
`int count = (1 << n);`
- `1 << n` is the bitwise way to calculate $2^n$.
- This defines how many total subsets exist.

#### **B. The "Checklist" Loop**
`for(int val = 0; val < count; val++)`
- This loop generates every unique binary pattern from all zeros to all ones.

#### **C. The Bit Probe**
`if(val & (1 << i))`
- **The Mask:** `(1 << i)` creates a number with only the $i$-th bit set (e.g., $1, 2, 4, 8 \dots$).
- **The AND Operation:** `val & mask` results in a non-zero value only if `val` has the $i$-th bit turned on.

---

### 3. C++ vs. Java Observation
In your code, you noted:
> `if(val & (1 << i))` // In cpp this works but in java you need to put != 0

**The Physics of the Language:**
* **C++:** Interprets any **non-zero** integer as `true`. If the result of the bitwise AND is `4`, the `if` condition passes.
* **Java:** Requires a strict `boolean` (`true` or `false`). Since `val & mask` returns an `int`, Java will throw an error unless you explicitly compare it: `(val & (1 << i)) != 0`.

---

### 4. Complexity Analysis
* **Time Complexity:** $O(n \cdot 2^n)$
    - We iterate through $2^n$ combinations.
    - For each combination, we run an internal loop of $n$ to check bits.
* **Space Complexity:** $O(n \cdot 2^n)$
    - To store all subsets (if we are returning the answer).

---

### 5. Summary for Interviews
- **When to use:** When you need all possible combinations and $N$ is small (typically $N \le 20$).
- **Key Advantage:** It is iterative and avoids the overhead of recursion/backtracking.
- **Key Disadvantage:** It doesn't handle duplicate elements in the input array as easily as backtracking does.

### Cpp code

```cpp
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:

    vector<vector<int>> powerSet(vector<int>& nums) {
        

        int n = nums.size();
    
        vector<vector<int>> ans;

        int count = (1 << n);
        

        for(int val = 0; val < count; val++) {
            

            vector<int> subset;
            
            for(int i=0; i < n; i++) {
                if(val & (1 << i)) {//In cpp this works but in java you need to put !=0
                    subset.push_back(nums[i]);
                }
            }

            ans.push_back(subset);
        }

        return ans;
    }
};
/*
In Java, the & operator performs a bitwise AND, but the result is still an int. Java expects a boolean expression inside an if statement, and:

i & (1 << j) returns an int, not a boolean

So this is a compilation error

so use if ((i & (1 << j)) != 0)  in java

In C/C++, it's fine to use just if (i & (1 << j)) because non-zero integers are treated as true, but Java is stricter and requires explicit boolean expressions.
*/

int main() {
    vector<int> nums = {1, 2, 3};

    Solution sol; 

    vector<vector<int>> ans = sol.powerSet(nums);
    
    sort(ans.begin(), ans.end());

    cout << "The power set for the given array is: " << endl;
    
    for(int i=0; i < ans.size(); i++) {
        for(int j=0; j < ans[i].size(); j++) {
            cout << ans[i][j] << " ";        
        }
        cout << endl;
    }
    
    return 0;
}

/*
Output:
1 
1 2 
1 2 3 
1 3 
2 
2 3 
3 
*/
```

# Bitwise Check: `if (val & (1 << i))`

### The Mechanics
1. **`1 << i` (The Mask):** Creates a number where only the $i$-th bit is 1. All other bits are 0.
2. **`&` (The Filter):** Performs a bitwise AND between the input `val` and the mask. 
3. **The Result:**
   - If the $i$-th bit of `val` is **1**: The result is $2^i$ (a non-zero number).
   - If the $i$-th bit of `val` is **0**: The result is $0$.

### Language Nuance
- **In C++:** `if (number)` passes if `number != 0`. Since $2^i$ is never zero, the `if` block executes when the bit is set.
- **In Java/C#:** You must write `if ((val & (1 << i)) != 0)` because these languages require an explicit boolean.

### Example (val = 13, i = 2)
- Binary `val`: `1101`
- Mask `1 << 2`: `0100`
- `1101 & 0100` = `0100` (4)
- **Result:** True (The 2nd bit is ON).

In context of power set we are checking that from range 0 to 2^n we have a value and in that value if 1 is set than we put that number in set

Every index is treated as an bit posistion in number

# The Bit-to-Index Mapping

### The Core Concept
Every index `i` in the input array `nums` is treated as the $i$-th bit position in a binary number.

1. **Outer Loop (`val`):** Iterates through every possible combination of $N$ bits (from $0$ to $2^N-1$).
2. **Inner Loop (`i`):** Scans through each bit position of the current `val`.
3. **The Decision:** If the $i$-th bit is "ON", it means the element at `nums[i]` is "invited" to join the current subset.

### Visual Example (nums = [A, B, C])
If `val = 6` (Binary `110`):
- Bit 0: `0` (Skip `nums[0]` / A) as bit 0 is 0
- Bit 1: `1` (Take `nums[1]` / B)
- Bit 2: `1` (Take `nums[2]` / C)
- **Resulting Subset:** `[B, C]`

### Java code

```java

import java.util.*;
class Solution {
    public List<List<Integer>> powerSet(int[] nums) {
        int n=nums.length;
        List<List<Integer>> res = new ArrayList<>();
        int limit=(1<<n);//2 to power n no of susbsets

        for(int i=0;i<limit;i++){//iterating over 0 to 2^n
            List<Integer>subset=new ArrayList<>();
            for(int j=0;j<n;j++){//iterating over n bits as n bits for 2^n
                
                if((i &(1<<j))!=0){
                    subset.add(nums[j]);
                }
            }
            res.add(subset);
        }
     return res;
    }
    public static void main(String[] args) {
        int[] nums = {1,2,3,4};
        Solution sol = new Solution(); 
        List<List<Integer>>res=sol.powerSet(nums);
        System.out.println(res);
/*
Output:
[[], [1], [2], [1, 2], [3], [1, 3], [2, 3], [1, 2, 3], [4], [1, 4], [2, 4], [1, 2, 4], [3, 4], [1, 3, 4], [2, 3, 4], [1, 2, 3, 4]]
*/

    }
 
}
/*
tc->(n*(2^n)) two loops outer one of 2^n and inner one for n
sc->O((2^n)*n) 2^n subset and each size on avg we take as n for worst case
*/
/*
{1,2,3} n=3 so no of elements in set =2^n=8
000={}
001={3}
010={2}
011={2,3}
100={1}
101={1,3}
110={1,2}
111={1,2,3}

i loop iterates over 0 to <2^n

j loop over n bits as for subset of n number we need n bits to represent number between 
0 to 2^n

if bit is 1 then add that number else not
*/
```
