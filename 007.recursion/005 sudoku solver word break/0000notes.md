# Notes

![alt text](<005 sudoku solver word break_231229_131220.jpg>)
![alt text](<005 sudoku solver word break_231229_131220(1).jpg>) ![alt text](<005 sudoku solver word break_231229_131220(2).jpg>) ![alt text](<005 sudoku solver word break_231229_131220(3).jpg>) ![alt text](<005 sudoku solver word break_231229_131220(4).jpg>) ![alt text](<005 sudoku solver word break_231229_131220(5).jpg>) 

```java
class Solution {
    private boolean isitsafe(char[][] board, int r, int c, int num) {

        // row
        for (int i = 0; i < 9; i++) {
            if (board[i][c] - '0' == num)
                return false;
        }

        // col
        for (int i = 0; i < 9; i++) {
            if (board[r][i] - '0' == num)
                return false;
        }

        // 3 X 3
        r = (r / 3) * 3;
        c = (c / 3) * 3;
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
                if (board[r + i][c + j] - '0' == num)
                    return false;

        return true;

    }
     private boolean solve(char[][] board,ArrayList<Integer>index,int idx){
       if(idx==index.size()) return true;
             int r=index.get(idx)/9;
             int c=index.get(idx)%9;
             for(int val=1;val<=9;val++){
                 if(isitsafe(board,r,c,val)){
                     board[r][c]=(char)(val+'0');
                     if(solve(board,index,idx+1)) return true;
                     board[r][c]='.';
                 }
             }
         return false;
         
     }
    private void storage(char[][] board,ArrayList<Integer>index){
        for(int i=0;i<9;i++){
            for(int j=0;j<9;j++){
                if(board[i][j]=='.'){
                    index.add(i*9+j);
                }
            }
        }
    }
    public void solveSudoku(char[][] board) {
        ArrayList<Integer>index=new ArrayList<>();
        storage(board,index);
        solve(board,index,0);
    }
}

```

This is a **Correct and Well-Optimized** solution! 

You have implemented the Backtracking approach perfectly. Specifically, you used the **"Pre-calculation of Empty Cells"** strategy, which is better than the standard naive approach.

### Why your code is good:

* **Coordinate Flattening ($i \times 9 + j$):**
    * Instead of searching for the next empty cell `.` using nested loops inside every recursive call (which costs $O(81)$ time per step), you scan the board once at the start.
    * You store the locations of all `.` in an `ArrayList`.
    * During recursion, you just pick the next coordinate from the list in $O(1)$ time. 
    * This makes the recursion significantly faster.
* **Correct Backtracking Logic:**
    * **Place:** `board[r][c] = val`
    * **Recurse:** `solve(..., idx + 1)`
    * **Backtrack:** `board[r][c] = '.'` (Crucial step to "undo" the move if it leads to a dead end).
* **Correct Safety Check (`isitsafe`):**
    * Your logic for finding the top-left corner of the $3 \times 3$ subgrid `(r/3)*3` is mathematically sound and handles all subgrids correctly.

---

### Complexity Analysis

* **Time Complexity:** $O(9^M)$, where $M$ is the number of empty cells. This is standard for Sudoku, but your constant factor is lower because you don't scan for empty cells repeatedly.
* **Space Complexity:** $O(M)$ to store the `ArrayList` of empty indices, plus the recursion stack depth.

---

### Minor Suggestion (Interview Polish)

Your code is excellent as is. The only tiny thing you might change in an interview is the variable naming to be slightly more descriptive, though this is nitpicking:
* `index` $\to$ `emptyCells`
* `storage` $\to$ `findEmptyCells`

**Verdict:** This code is Interview Ready. 🟢


```java
       // 3 X 3
        r = (r / 3) * 3;
        c = (c / 3) * 3; explain

```
This logic is a clever mathematical trick to find the Top-Left Corner of the 3x3 sub-grid that contains your cell (r, c).

It works because of **Integer Division**. In C++ and Java, division drops the decimal part (truncates).

### 1. The Logic Step-by-Step

Let's look at the rows (`r`). The Sudoku board is split into 3 "Block Rows":
* **Block 0:** Rows 0, 1, 2
* **Block 1:** Rows 3, 4, 5
* **Block 2:** Rows 6, 7, 8

#### Step A: `r / 3` (Find the Block ID)
* If `r` is 0, 1, or 2 $\to$ `r / 3` is **0**.
* If `r` is 3, 4, or 5 $\to$ `r / 3` is **1**.
* If `r` is 6, 7, or 8 $\to$ `r / 3` is **2**.
*(This tells us which "strip" of blocks we are in.)*

#### Step B: `* 3` (Find the Start Index)
Now we multiply that ID back by 3 to get the actual row index where that block starts.
* $0 \times 3 = 0$
* $1 \times 3 = 3$
* $2 \times 3 = 6$

---

### 2. Visual Example

Imagine we are checking valid numbers for the cell at **Row 5, Col 7 (5, 7)**.

**Find Start Row:**
1.  $5 / 3 = 1$
2.  $1 \times 3 = 3$
* **Start Row is 3.**

**Find Start Col:**
1.  $7 / 3 = 2$
2.  $2 \times 3 = 6$
* **Start Col is 6.**

**Result:** The top-left corner of the $3 \times 3$ box containing cell (5, 7) is **(3, 6)**.

Q

```text
int r=index.get(idx)/9;

int c=index.get(idx)%9; 

why it works why / gives row and % gives col

```
This works because you are effectively counting groups of 9. Think of the Sudoku board as a long line of 81 numbers (from 0 to 80), laid out row by row.

### 1. The Analogy: Egg Cartons
Imagine you have a basket of eggs, and you are filling cartons that hold 9 eggs each.

* **Rows** are the Cartons.
* **Columns** are the specific slots inside a carton (0 to 8).

If you pick up **Egg #20**:

* **How many full cartons have passed?**
    * $20 / 9 = 2$.
    * You have filled Carton 0 and Carton 1 completely. You are now inside **Carton #2 (Row 2)**.
    * **Division gives the group number.**
* **Which slot is it in the current carton?**
    * $20 \pmod 9 = 2$ (Remainder).
    * After filling the first 18 spots (2 cartons), you have 2 eggs left over. You place this egg in **Slot #2 (Column 2)**.
    * **Modulo gives the position inside the group.**

---

### 2. Visualizing the Grid Indices
Here is how the indices look if you flatten the 2D grid:

| Row / Col | 0 | 1 | 2 | ... | 8 |
| :--- | :--- | :--- | :--- | :--- | :--- |
| **Row 0** | 0 | 1 | 2 | ... | 8 |
| **Row 1** | 9 | 10 | 11 | ... | 17 |
| **Row 2** | 18 | 19 | **20** | ... | 26 |

* **Row Logic:** To get to Index 20, you had to skip over Row 0 (9 items) and Row 1 (9 items). That's $9 + 9 = 18$ items.
    * $20 / 9 = 2$ (You are in the 3rd row, index 2).
* **Col Logic:** Once you are in Row 2, how many steps right do you take?
    * You start at 18. To get to 20, you step 2 times.
    * $20 \pmod 9 = 2$.

---

### Summary Rule
For any 2D matrix of width **W**:
* **Row = Index / W** (How many full rows fit?)
* **Col = Index % W** (What is the remainder/offset?)

![alt text](<005 sudoku solver word break_231229_131220(6).jpg>) ![alt text](<005 sudoku solver word break_231229_131220(7).jpg>) ![alt text](<005 sudoku solver word break_231229_131220(8).jpg>) ![alt text](<005 sudoku solver word break_231229_131220(9).jpg>) ![alt text](<005 sudoku solver word break_231229_131220(10).jpg>) ![alt text](<005 sudoku solver word break_231229_131220(11).jpg>) ![alt text](<005 sudoku solver word break_231229_131220(12).jpg>) ![alt text](<005 sudoku solver word break_231229_131220(13).jpg>) 

```cpp
class Solution {
    unordered_set<string>setstr;
    bool wb(string  s){
        if(s.size()==0) return true;
        for(int len=1;len<=s.size();len++){
            string substring=s.substr(0,len);
            if(setstr.find(substring)!=setstr.end()){
                if(wb(s.substr(len))==true) return true;
            }
        }
        return false;
    }
public:
    bool wordBreak(string s, vector<string>& wordDict) {
        for(string str:wordDict){
            setstr.insert(str);
        }
        
        return wb(s);
    }
};
```

Gives TLE!!

### Complexity Analysis (Plain Recursion)

#### Time Complexity: $O(2^N)$ (Exponential)
**Why?** In the worst case (e.g., `s = "aaaaa"` and `dict = ["a", "aa", "aaa"]`), every character can be the start of a new branch in the decision tree.

* The recurrence relation is roughly: $T(N) = T(N-1) + T(N-2) + \dots + T(0)$.
* This summation behaves exactly like $2^N$.
* **The Reality:** If $N = 50$, $2^{50}$ is roughly **1,000,000,000,000,000** operations. This code would literally run until the universe ends, resulting in a **Time Limit Exceeded (TLE)** on any modern judge.

---

#### Space Complexity: $O(N)$
**Why?** The space complexity is determined by the maximum depth of the recursion stack.

* In the worst case (e.g., parsing "a", "a", "a"...), the stack depth goes as deep as the length of the string ($N$).
* Each level of the stack stores a few pointers/indices, resulting in linear space usage relative to the input string.

---

### Summary Table

| Metric | Complexity | Cause |
| :--- | :--- | :--- |
| **Time** | $O(2^N)$ | Overlapping subproblems being re-calculated constantly. |
| **Space** | $O(N)$ | Deepest possible branch in the DFS recursion tree. |

### The Mathematical Proof (Derivation)

We start with your recurrence equation for $N$:
$$T(N) = T(N-1) + T(N-2) + \dots + T(1) + T(0)$$
--- (Equation 1)

Now, let's write the same equation for the previous step, $N-1$:
$$T(N-1) = T(N-2) + \dots + T(1) + T(0)$$
--- (Equation 2)

#### The Trick
Notice that the entire right side of **Equation 2** (the sum from $N-2$ down to $0$) is exactly visible inside **Equation 1**.

Substitute **Equation 2** into **Equation 1**:
$$T(N) = T(N-1) + \underbrace{[T(N-2) + \dots + T(0)]}_{\text{This is just } T(N-1)}$$

So it simplifies to:
$$T(N) = T(N-1) + T(N-1)$$
$$T(N) = 2 \cdot T(N-1)$$

#### Conclusion
At every step, the total amount of work doubles.
* $T(N) = 2 \cdot T(N-1)$
* $T(N-1) = 2 \cdot T(N-2)$
* ...
* $T(N) = 2^N \cdot T(0)$

Therefore, the time complexity is **$O(2^N)$**.

---
### Why DP? (The Problem with Recursion)

The recursion is "dumb"—it has no memory. It solves the exact same subproblems over and over again, wasting billions of CPU cycles.

---

### Visualizing the Overlap
Suppose `s = "catsanddog"` and your dictionary is `["cat", "cats", "and", "sand", "dog"]`.

* **Path A:** You pick "cat" $\to$ recurse on "sanddog".
* **Path B:** You pick "cats" $\to$ recurse on "anddog".
    * Inside Path B, you pick "and" $\to$ recurse on **"dog"**.
* **Path C:** You pick "cat" $\to$ then "sand" $\to$ recurse on **"dog"**.

**The Problem:** We are calculating the answer for "dog" in Path B **AND** in Path C. In a large string, the algorithm might re-calculate the answer for the substring starting at index 10 **thousands of times**.

---

### The DP Intervention
Dynamic Programming changes the philosophy:
> **DP says:** "I solved index 10 once. I remember the answer is **TRUE**. Don't you dare calculate it again!"

---

### Efficiency Gain
By using an array or hash map to store these results:
1.  **First encounter:** Calculate the result for index $i$ and save it.
2.  **Subsequent encounters:** Look up the result in $O(1)$ time.

This simple "memory" is what collapses the time complexity from an impossible **$O(2^N)$** down to a manageable **$O(N^3)$** 
---

```cpp

class Solution {
unordered_set<string> setstr;
    vector<int> memo;
 bool wb(int idx, string &s){
// Base Case
        if (idx == s.size()) return true;

        // Step 3: Check the vector
        if (memo[idx] != -1) return memo[idx];

        for (int len = 1; idx + len <= s.size(); len++) {
            string substring = s.substr(idx, len);
            
            if (setstr.count(substring)) {
                // Recurse for the rest
                if (wb(idx + len, s)) {
                    return memo[idx] = 1; // Store True
                }
            }
        }

        return memo[idx] = 0; // Store False
    }
public:
    bool wordBreak(string s, vector<string>& wordDict) {
        setstr.clear(); // Good practice to clear if reusing class
        for (string str : wordDict) {
            setstr.insert(str);
        }

        // Step 2: Initialize the vector
        // Resize to string length and fill with -1
        memo.assign(s.size(), -1); 

        return wb(0, s);
    }
};
```
### Dynamic Programming (Memoization)

By adding a `vector<int> memo` (or a hash map) to store the results of `solve(idx)`, we transform the exponential explosion into a controlled polynomial process.

---

#### Time Complexity: $O(N^3)$

1.  **States:** There are $N$ unique indices to solve (from $0$ to $N-1$).
2.  **Work per State:** Inside each state, we run a loop up to $N$ times to check substrings starting from that index.
3.  **String Overhead:** Inside the loop, `s.substr()` takes $O(N)$ time to copy the characters and the dictionary lookup (hashing) also depends on the length of the string.
4.  **The Calculation:** $N \text{ (states)} \times N \text{ (loop)} \times N \text{ (substring)} = O(N^3)$.

> **Note:** For $N = 300$, $300^3 = 27,000,000$. This comfortably fits within the standard 1-second time limit (usually $\sim 10^8$ operations) of competitive programming.

---

#### Space Complexity: $O(N)$

1.  **Memo Array:** We need a vector of size $N$ to store the computed results for each index.
2.  **Recursion Stack:** The maximum depth of the stack remains $O(N)$.
3.  **Total:** $O(N + N) \to O(N)$.

---

### Comparison Summary

| Feature | Recursion | DP (Memoization) |
| :--- | :--- | :--- |
| **Time Complexity** | $O(2^N)$ (Horrible) | $O(N^3)$ (Fast) |
| **Space Complexity** | $O(N)$ (Stack) | $O(N)$ (Stack + Vector) |
| **Performance** | **TLE** for $N > 20$ | **Passes** for $N = 300+$ |
| **Main Issue** | Re-calculates same subproblems. | Substring copying/hashing is the bottleneck. |

---

TRie i hav used 

```java
class Solution {
class Trie {
    Node root;
     class Node{
        boolean eow;
        Node[] child;
        public Node(){
            this.eow=false;
            this.child=new Node[26];
        }
    }
     
    public Trie() {
         root=new Node();
       
    }
        
    public void insert(String word) {
        Node node=root;
        for(char ch:word.toCharArray()){
            if(node.child[ch-'a']==null){
                
                node.child[ch-'a']=new Node();
            }
            node=node.child[ch-'a'];
        }
        node.eow=true;
    }
    
    public boolean isConcatWord(String word,int i,int noOfWord,Node node) {
        if(i==word.length()){
            return noOfWord>=1?true:false;
        }

         for(int idx=i;idx<word.length();idx++){
            char ch=word.charAt(idx);
            if(node.child[ch-'a']==null){
                return false;
            }
            node=node.child[ch-'a'];
            if(node.eow==true){
            boolean r1=isConcatWord(word,idx+1,noOfWord+1,root);
            if(r1==true) return true;
           }
        }

       return false;    
    }
    
}
    public boolean wordBreak(String s, List<String> wordDict) {
        Trie t=new Trie();
        for(String str:wordDict){
            t.insert(str);
        }
        return t.isConcatWord(s,0,0,t.root);
    }
}
```

### This approach is logically correct, but it has the exact same problem as the previous recursive solution: It will get Time Limit Exceeded (TLE) on large inputs.

Using a Trie makes the "matching" part faster ($O(\text{WordLength})$), but it doesn't solve the "Repeated Work" problem. You are still exploring the same indices over and over again.

---

### 1. Why it fails (The Hidden Recursion)
Even with a Trie, your recursion tree is exponential ($O(2^N)$).

**Imagine:** `s = "aaaaaaaa"` and the Trie has paths for `"a"`, `"aa"`, `"aaa"`.
* Your code will split at index 1, recurse... then fail... backtrack... 
* Then it splits at index 2... recurse...
* Eventually, you will reach index 5 via multiple different paths (e.g., $1+4, 2+3, 1+1+3$).

**The Bug:** Your code calculates `isConcatWord(index 5)` every single time it arrives there, regardless of how it got there. Without memory, the Trie is just a faster way to do a slow thing.

---

### 2. The Fix: Add Memoization (`Integer[] memo`)
You need to store the result of `isConcatWord(i)` so you never calculate it twice.

**The Strategy:**
* **`memo[i] = 1`**: We already checked this suffix, and it **can** be formed by other words.
* **`memo[i] = 0`**: We already checked this suffix, and it **cannot** be formed.
* **`memo[i] = null`**: We haven't been here yet.

---

### Your Fixed Code (Optimized)

| Optimization | Impact | Result |
| :--- | :--- | :--- |
| **Trie** | Replaces string slicing/hashing with pointer jumps. | $O(N)$ matching becomes $O(1)$ per char. |
| **Memoization** | Eliminates redundant recursive calls. | $O(2^N)$ becomes $O(N^2)$. |

```java

class Solution {
class Trie {
    Boolean[] memo;
    Node root;
     class Node{
        boolean eow;
        Node[] child;
        public Node(){
            this.eow=false;
            this.child=new Node[26];
        }
    }
     
    public Trie() {
         root=new Node();
       
    }
        
    public void insert(String word) {
        Node node=root;
        for(char ch:word.toCharArray()){
            if(node.child[ch-'a']==null){
                
                node.child[ch-'a']=new Node();
            }
            node=node.child[ch-'a'];
        }
        node.eow=true;
    }
    
    public boolean isConcatWord(String word,int i,int noOfWord,Node node) {
        if(i==word.length()){
            return noOfWord>=1?true:false;
        }
        if (memo[i] != null) return memo[i];
         for(int idx=i;idx<word.length();idx++){
            char ch=word.charAt(idx);
            if(node.child[ch-'a']==null){
                return memo[i] =false;
            }
            node=node.child[ch-'a'];
            if(node.eow==true){
            boolean r1=isConcatWord(word,idx+1,noOfWord+1,root);
            if(r1==true) return memo[i] =true;
           }
        }

       return memo[i] =false;    
    }
    
}
    public boolean wordBreak(String s, List<String> wordDict) {
        Trie t=new Trie();
        t.memo = new Boolean[s.length() + 1];
        for(String str:wordDict){
            t.insert(str);
        }
        return t.isConcatWord(s,0,0,t.root);
    }
}
```

### 3. Complexity Analysis (With Memoization)

By combining the **Trie** and **Memoization**, we achieve a highly optimized complexity that handles large strings and massive dictionaries with ease.

---

#### Time Complexity: $O(N \cdot W)$
* **$N$**: Length of the input string `s`.
* **$W$**: Length of the longest word in the dictionary (maximum depth of the Trie).

**Why?**
* **Memoization Effect:** We visit every starting index $i$ in the string **at most once**. If we land on the same index again via a different path, we return the cached result in $O(1)$.
* **Trie Traversal:** For each index, we don't necessarily loop through the whole rest of the string. We only walk down the Trie as long as the characters match. This walk is capped by the length of the longest word in your dictionary ($W$).
* **Result:** This is significantly faster than $O(N^2)$ if the words in the dictionary are relatively short compared to a very long input string.

---

#### Space Complexity: $O(T + N)$
* **$T$**: Size of the Trie (the total number of nodes, which corresponds to the unique characters/prefixes in the dictionary).
* **$N$**: Size of the Memo array and the maximum depth of the recursion stack.

**Why?**
* **Trie Storage:** We must store all dictionary words in the Trie structure.
* **Linear Overhead:** The memoization array and the recursion depth both scale linearly with the length of the string $N$.

---

### Comparison: The Final Evolution

| Feature | Plain Recursion | Memoization + Set | Memoization + Trie |
| :--- | :--- | :--- | :--- |
| **Time** | $O(2^N)$ | $O(N^3)$ | **$O(N \cdot W)$** |
| **Bottleneck** | Branching | `substr()` & Hashing | Trie Depth |
| **Efficiency** | Worst | Good | **Optimal** |

---

AI code

```java
class Solution {
    class Trie {
        Node root;
        // MEMOIZATION ARRAY added here
        Boolean[] memo; 

        class Node {
            boolean eow;
            Node[] child;
            public Node() {
                this.eow = false;
                this.child = new Node[26];
            }
        }

        public Trie() {
            root = new Node();
        }

        public void insert(String word) {
            Node node = root;
            for (char ch : word.toCharArray()) {
                if (node.child[ch - 'a'] == null) {
                    node.child[ch - 'a'] = new Node();
                }
                node = node.child[ch - 'a'];
            }
            node.eow = true;
        }

        // Optimized Helper with Memoization
        public boolean isConcatWord(String word, int i) {
            if (i == word.length()) return true;
            
            // 1. CHECK MEMO
            if (memo[i] != null) return memo[i];

            Node node = root;
            for (int idx = i; idx < word.length(); idx++) {
                char ch = word.charAt(idx);
                
                // If Trie path ends, no word matches this prefix. Stop.
                if (node.child[ch - 'a'] == null) {
                    return memo[i] = false; // Store result
                }
                
                node = node.child[ch - 'a'];
                
                // If we found a valid word, recurse for the rest
                if (node.eow) {
                    if (isConcatWord(word, idx + 1)) {
                        return memo[i] = true; // Store result
                    }
                }
            }

            return memo[i] = false; // Store result
        }
    }

    public boolean wordBreak(String s, List<String> wordDict) {
        Trie t = new Trie();
        // Initialize memo with the size of string s
        t.memo = new Boolean[s.length() + 1]; 
        
        for (String str : wordDict) {
            t.insert(str);
        }
        
        // Removed unnecessary params (noOfWord, node)
        return t.isConcatWord(s, 0); 
    }
}
```
 Code Clean-up Notes
I removed a few things from your original code to make it cleaner and more professional for an interview setting:

* **`noOfWord`:** In LeetCode 139 ("Word Break"), we don't care about the count of words used, only the boolean possibility of a break. Removing this count-tracking simplifies the logic and reduces potential bugs.
* **`Node node` parameter:** You were passing `t.root` through every recursive call. It is much cleaner to access the `root` directly from the class scope or initialize `Node curr = root` at the start of your matching loop. This keeps your function signature focused only on the state that changes: the **index**.
* **`return false` logic:** Your check `if (node.child[...] == null) break;` (or return false) was spot on. Since the Trie is a prefix tree, if the path for a specific character doesn't exist, it is mathematically impossible for any longer word in your dictionary to match that prefix. Stopping there is the most efficient move.

try LeetCode 472