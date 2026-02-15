### Comparison Table: Arrays vs. Bitwise Operations

Here is the comparison table based on your notes, illustrating how bitwise operations can replace boolean arrays for memory and performance efficiency.

| Feature | Array Operation | Bitwise Operation |
| :--- | :--- | :--- |
| **1. Initialize** | `boolean[] arr = new boolean[32];` | `int arr = 0;` |
| **Description** | Creates an array to store 32 boolean values. | Uses a single integer (32 bits) to store the same data. |
| **2. Target Index** | `int idx = k;` | `int mask = 1 << k;` |
| **Description** | Selects the index `k`. | Creates a "mask" by shifting `1` to the `k`-th position. |
| **3. Set to True** | `arr[idx] = true;` | `arr = arr \| mask;` |
| **Description** | Sets the value at index `k` to true. | Sets the `k`-th bit to `1` using the **OR** (`\|`) operator. |
| **4. Set to False** | `arr[idx] = false;` | `arr = arr & ~mask;` |
| **Description** | Sets the value at index `k` to false. | Sets the `k`-th bit to `0` using **AND** with the negated mask (`~`). |
| **5. Check Condition**| `if (arr[idx] == true) { ... }` | `if ((arr & mask) != 0) { ... }` |
| **Description** | Checks if the value at index `k` is true. | Checks if the `k`-th bit is `1` (non-zero result means true). |

---

### Why use Bitwise over Arrays?

* **Memory Efficiency:** An array of 32 booleans can take up 32 bytes (or more due to object overhead), while an `int` takes exactly 4 bytes.
* **Performance:** Bitwise operations are executed directly by the CPU in a single clock cycle, making them significantly faster than array lookups.
* **Copying/State Management:** You can copy the entire "state" of 32 flags by simply copying one integer, whereas copying an array requires a loop or `System.arraycopy()`.

Now let us seee sudoku solver!!see its previous code first!!

![alt text](<006bitwise operation and recursion_231229_130956(20).jpg>) 
![alt text](<006bitwise operation and recursion_231229_130956(21).jpg>) 

## Initial sudoku solver


```java
    private boolean isPossibleToPlaceNumber(char[][] board, int r, int c, int num) {

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

    public boolean sudokuSolver(char[][] board, ArrayList<Integer> list, int idx) {
        if (idx == list.size())
            return true;

        int r = list.get(idx) / 9;
        int c = list.get(idx) % 9;

        for (int num = 1; num <= 9; num++) {
            if (isPossibleToPlaceNumber(board, r, c, num)) {
                board[r][c] = (char) ('0' + num);

                if (sudokuSolver(board, list, idx + 1))
                    return true;

                board[r][c] = '.';
            }
        }

        return false;
    }

    public void solveSudoku(char[][] board) {
        ArrayList<Integer> list = new ArrayList<>(); // blank places
        int n = 9;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (board[i][j] == '.') {
                    list.add(i * n + j);
                }
            }
        }
    }



```


![alt text](<006bitwise operation and recursion_231229_130956(22).jpg>) ![alt text](<006bitwise operation and recursion_231229_130956(23).jpg>) ![alt text](<006bitwise operation and recursion_231229_130956(24).jpg>) ![alt text](<006bitwise operation and recursion_231229_130956(25).jpg>) 

## 2nd code sudoku solver

```java
    boolean[][] rows = new boolean[10][10];
    boolean[][] cols = new boolean[10][10];
    boolean[][][] mats = new boolean[3][3][10];

    public boolean sudokuSolver_02(char[][] board, ArrayList<Integer> list, int idx) {
        if (idx == list.size())
            return true;

        int r = list.get(idx) / 9;
        int c = list.get(idx) % 9;

        for (int num = 1; num <= 9; num++) {
            if (!rows[r][num] && !cols[c][num] && !mats[r / 3][c / 3][num]) {
                board[r][c] = (char) ('0' + num);
                rows[r][num] = cols[c][num] = mats[r / 3][c / 3][num] = true;

                if (sudokuSolver_02(board, list, idx + 1))
                    return true;

                board[r][c] = '.';
                rows[r][num] = cols[c][num] = mats[r / 3][c / 3][num] = false;
            }
        }

        return false;
    }

    public void solveSudoku_02(char[][] board) {
        ArrayList<Integer> list = new ArrayList<>(); // blank places
        int n = 9;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (board[i][j] == '.') {
                    list.add(i * n + j);
                } else {
                    int num = board[i][j] - '0';
                    rows[i][num] = cols[j][num] = mats[i / 3][j / 3][num] = true;
                }
            }
        }

        sudokuSolver_02(board, list, 0);
    }

```

## Code  final

```java

import java.util.ArrayList;

class Solution {
    // 1. Initialize our bitmasks (Integers instead of boolean arrays)
    int[] rows = new int[9];
    int[] cols = new int[9];
    int[][] boxes = new int[3][3];

    public void solveSudoku(char[][] board) {
        ArrayList<Integer> emptyCells = new ArrayList<>();
        
        // 2. Pre-process: Fill masks with initial board state & find empty cells
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                if (board[i][j] == '.') {
                    emptyCells.add(i * 9 + j);
                } else {
                    int val = board[i][j] - '0';
                    int mask = 1 << (val - 1);
                    
                    // Set bits for existing numbers
                    rows[i] |= mask;
                    cols[j] |= mask;
                    boxes[i / 3][j / 3] |= mask;
                }
            }
        }
        
        solve(board, emptyCells, 0);
    }

    private boolean solve(char[][] board, ArrayList<Integer> emptyCells, int idx) {
        if (idx == emptyCells.size()) return true;

        int r = emptyCells.get(idx) / 9;
        int c = emptyCells.get(idx) % 9;
        
        for (int val = 1; val <= 9; val++) {
            int mask = 1 << (val - 1); // Create mask for number val

            // 3. O(1) Safety Check using Bitwise AND
            // "If bit is NOT set in row AND col AND box"
            if ((rows[r] & mask) == 0 && 
                (cols[c] & mask) == 0 && 
                (boxes[r / 3][c / 3] & mask) == 0) {
                
                // Place
                board[r][c] = (char)(val + '0');
                
                // 4. Update Masks (Set Bit)
                rows[r] |= mask;
                cols[c] |= mask;
                boxes[r / 3][c / 3] |= mask;

                if (solve(board, emptyCells, idx + 1)) return true;

                // 5. Backtrack (Clear Bit using AND NOT)
                rows[r] &= ~mask;
                cols[c] &= ~mask;
                boxes[r / 3][c / 3] &= ~mask;
                
                board[r][c] = '.';
            }
        }
        return false;
    }
}
```

This is a **Pro-Level Optimization**. By applying the bitwise logic from your notes, we can remove the `isitsafe` loop entirely. 

Instead of scanning the row/column every time (which takes time), we maintain 3 integer arrays that act as "memory" for what numbers are already used.

### The Mapping Strategy
We replace the boolean checks with bitwise integers as shown in your notes:

* **`rows[9]`**: `rows[r]` stores which numbers are currently present in row $r$.
* **`cols[9]`**: `cols[c]` stores which numbers are currently present in column $c$.
* **`grids[3][3]`**: `grids[r/3][c/3]` stores which numbers are in that $3 \times 3$ block.

---

### The Bitwise Logic (From your table)

1.  **Target Number `val` (1-9):** We convert this to a bit mask:
    > `int mask = 1 << (val - 1);`  
    *(Using 0-8th bits for numbers 1-9).*

2.  **Check if Safe:** Instead of a loop, we check if the bit is **NOT** set in any of our 3 masks:
    > `if ((rows[r] & mask) == 0 && (cols[c] & mask) == 0 && (grids[r/3][c/3] & mask) == 0)`

3.  **Place Number (Set Bit):**
    > `rows[r] |= mask;`

4.  **Backtrack (Unset Bit):**
    > `rows[r] &= ~mask;`

---

### Why this is a "Game Changer"

| Feature | Standard `isitsafe` | Bitmasking `isitsafe` |
| :--- | :--- | :--- |
| **Complexity** | $O(9)$ (Iterates row, col, and grid) | **$O(1)$** (Direct bitwise check) |
| **Operations** | ~27 comparisons per call | 3 bitwise `&` operations |
| **Memory** | Uses no extra memory | Uses only 27 integers total |

Because the `solve` function is called recursively thousands of times, reducing $O(9)$ to $O(1)$ provides a massive performance boost.


![alt text](<006bitwise operation and recursion_231229_130956(26).jpg>) ![alt text](<006bitwise operation and recursion_231229_130956(27).jpg>) ![alt text](<006bitwise operation and recursion_231229_130956(28).jpg>) ![alt text](<006bitwise operation and recursion_231229_130956(29).jpg>) ![alt text](<006bitwise operation and recursion_231229_130956(30).jpg>)

```java


    int[] row = new int[10];
    int[] col = new int[10];
    int[][] mat = new int[3][3];

    public boolean sudokuSolver_03_bits(char[][] board, ArrayList<Integer> list, int idx) {
        if (idx == list.size())
            return true;

        int r = list.get(idx) / 9;
        int c = list.get(idx) % 9;

        for (int num = 1; num <= 9; num++) {
            int mask = 1 << num;
            if ((row[r] & mask) == 0 && (col[c] & mask) == 0 && (mat[r / 3][c / 3] & mask) == 0) {
                board[r][c] = (char) ('0' + num);
                row[r] ^= mask;
                col[c] ^= mask;
                mat[r / 3][c / 3] ^= mask;

                if (sudokuSolver_03_bits(board, list, idx + 1))
                    return true;

                board[r][c] = '.';

                row[r] ^= mask;
                col[c] ^= mask;
                mat[r / 3][c / 3] ^= mask;

            }
        }

        return false;
    }

    public void solveSudoku_03_bits(char[][] board) {
        ArrayList<Integer> list = new ArrayList<>(); // blank places
        int n = 9;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (board[i][j] == '.') {
                    list.add(i * n + j);
                } else {
                    int num = board[i][j] - '0';
                    int mask = 1 << num;
                    row[i] ^= mask;
                    col[j] ^= mask;
                    mat[i / 3][j / 3] ^= mask;
                }
            }
        }

        sudokuSolver_03_bits(board, list, 0);
    }
```
This code uses the **XOR Toggle Trick** (`^=`), which is a clever variation of the bitwise operations we just discussed. Here is the breakdown of why this specific version is efficient and how it differs from the standard approach:

---

### 1. The XOR Toggle Trick (`^=`)
In your previous notes, you saw two distinct steps:
1.  **Set:** `arr |= mask` (Turn ON)
2.  **Unset:** `arr &= ~mask` (Turn OFF)

This code replaces both with a single operator: **XOR (`^`)**.

* **Logic:**
    * $0 \oplus 1 = 1$ (If bit is empty, XOR sets it).
    * $1 \oplus 1 = 0$ (If bit is set, XOR clears it).
* **Why it works here:**
    * You have a safety check `if ((row[r] & mask) == 0)` right before the first toggle. This guarantees the bit is currently `0`.
    * **Place (Forward):** `row[r] ^= mask` flips `0` to `1`.
    * **Backtrack (Return):** `row[r] ^= mask` flips `1` back to `0`.
* **Benefit:** It allows you to write the exact same line of code for both "doing" and "undoing" the move.

---

### 2. Mask Shift (`1 << num`)
* **Code:** `int mask = 1 << num;`
* **Difference:** Unlike the previous `1 << (num - 1)` which used bits 0-8, this uses bits **1-9**.
    * Number 1 uses bit index 1.
    * Number 9 uses bit index 9.
* **Effect:** This effectively "wastes" the 0-th bit, but it makes the code slightly cleaner because you don't need to subtract 1 from `num` every time you calculate the mask.

---

### 3. Pre-Processing Logic
The driver function correctly initializes the state:
1.  **Scan Grid:** It loops through `i` and `j`.
2.  **Empty Cells:** Adds `.` coordinates to the list.
3.  **Filled Cells:** Immediately updates the `row`, `col`, and `mat` bitmasks using `^=`.
4.  **Crucial:** If you didn't do this, the solver would try to place numbers that conflict with the pre-filled clues.

---

### Code Walkthrough Example
Imagine placing number **5** at **(0,0)**:
1.  **Mask:** `1 << 5` (Binary `...100000`).
2.  **Check:** `if ((row[0] & mask) == 0)` $\to$ Checks if the 5th bit is OFF.
3.  **Toggle ON:** `row[0] ^= mask`. Now `row[0]` remembers "5 is used".
4.  **Recurse:** Try to solve the rest of the board.
5.  **Toggle OFF:** `row[0] ^= mask`. `row[0]` forgets "5 is used" (Backtracking).

---

### Verdict
This is a **highly optimized competitive programming implementation**. It is faster to type and slightly cleaner than using separate `|` and `& ~` operations, provided you strictly check for safety before toggling.

Would you like me to analyze the time complexity of this specific bitmask version compared to your original version?

 ![alt text](<006bitwise operation and recursion_231229_130956(31).jpg>) ![alt text](<006bitwise operation and recursion_231229_130956(32).jpg>) ![alt text](<006bitwise operation and recursion_231229_130956(33).jpg>)

![alt text](<006bitwise operation and recursion_231229_130956(34).jpg>) ![alt text](<006bitwise operation and recursion_231229_130956(35).jpg>) ![alt text](<006bitwise operation and recursion_231229_130956(36).jpg>) ![alt text](<006bitwise operation and recursion_231229_130956(37).jpg>) ![alt text](<006bitwise operation and recursion_231229_130956(38).jpg>) ![alt text](<006bitwise operation and recursion_231229_130956(39).jpg>) ![alt text](<006bitwise operation and recursion_231229_130956(40).jpg>) ![alt text](<006bitwise operation and recursion_231229_130956(41).jpg>) ![alt text](<006bitwise operation and recursion_231229_130956(42).jpg>) ![alt text](<006bitwise operation and recursion_231229_130956(43).jpg>) ![alt text](<006bitwise operation and recursion_231229_130956(44).jpg>) ![alt text](<006bitwise operation and recursion_231229_130956(45).jpg>) ![alt text](<006bitwise operation and recursion_231229_130956(46).jpg>) ![alt text](<006bitwise operation and recursion_231229_130956(47).jpg>) ![alt text](<006bitwise operation and recursion_231229_130956(48).jpg>) ![alt text](<006bitwise operation and recursion_231229_130956(49).jpg>) ![alt text](<006bitwise operation and recursion_231229_130956(50).jpg>) ![alt text](<006bitwise operation and recursion_231229_130956(51).jpg>) ![alt text](<006bitwise operation and recursion_231229_130956(52).jpg>) ![alt text](<006bitwise operation and recursion_231229_130956(53).jpg>) ![alt text](<006bitwise operation and recursion_231229_130956(54).jpg>) 



```java
public class l006_Nqueen {
    static boolean[] rows, cols, diags, adiags;

    public static int nqueen_01(int n, int tnq, int bno, String psf) {
        if (tnq == 0) {
            System.out.println(psf);
            return 1;
        }
        int count = 0;
        for (int bidx = bno; bidx < n * n; bidx++) {
            int r = bidx / n, c = bidx % n;
            if (!rows[r] && !cols[c] && !diags[r - c + n - 1] && !adiags[r + c]) {
                rows[r] = cols[c] = diags[r - c + n - 1] = adiags[r + c] = true;
                count += nqueen_01(n, tnq - 1, bidx + 1, psf + "(" + r + "," + c + ") ");
                rows[r] = cols[c] = diags[r - c + n - 1] = adiags[r + c] = false;
            }
        }
        return count;
    }

    static int row = 0, col = 0, diag = 0, adiag = 0;

    public static int nqueen_02(int n, int tnq, int bno, String psf) {
        if (tnq == 0) {
            System.out.println(psf);
            return 1;
        }
        int count = 0;
        for (int bidx = bno; bidx < n * n; bidx++) {
            int r = bidx / n, c = bidx % n;
            if ((row & (1 << r)) == 0 && (col & (1 << c)) == 0 && (diag & (1 << (r - c + n - 1))) == 0
                    && (adiag & (1 << (r + c))) == 0) {
                row ^= (1 << r);
                col ^= (1 << c);
                diag ^= (1 << (r - c + n - 1));
                adiag ^= (1 << (r + c));

                count += nqueen_02(n, tnq - 1, bidx + 1, psf + "(" + r + "," + c + ") ");

                row ^= (1 << r);
                col ^= (1 << c);
                diag ^= (1 << (r - c + n - 1));
                adiag ^= (1 << (r + c));
            }
        }
        return count;
    }

    public static int nqueen_03(int n, int floor, String psf) {
        if (floor == n) {
            System.out.println(psf);
            return 1;
        }
        int count = 0, r = floor;
        for (int room = 0; room < n; room++) {
            int c = room;
            if ((row & (1 << r)) == 0 && (col & (1 << c)) == 0 && (diag & (1 << (r - c + n - 1))) == 0
                    && (adiag & (1 << (r + c))) == 0) {
                row ^= (1 << r);
                col ^= (1 << c);
                diag ^= (1 << (r - c + n - 1));
                adiag ^= (1 << (r + c));

                count += nqueen_03(n, floor + 1, psf + "(" + r + "," + c + ") ");

                row ^= (1 << r);
                col ^= (1 << c);
                diag ^= (1 << (r - c + n - 1));
                adiag ^= (1 << (r + c));
            }
        }
        return count;
    }

    public static boolean isPalindrome(String str, int i, int j) {
        while (i <= j) {
            if (str.charAt(i) != str.charAt(j))
                return false;
            i++;
            j--;
        }
        return true;
    }

    public static void solution(String str, int i, String asf) {
        if (i >= str.length()) {
            System.out.println(asf);
            return;
        }
        for (int j = i; j < str.length(); j++) {
            if (isPalindrome(str, i, j)) {
                solution(str, j + 1, asf + "(" + str.substring(i, j + 1) + ") ");
            }
        }
    }

    public static void main(String... args) {
        int n = 4, tnq = 4;
        // rows = new boolean[n];
        // cols = new boolean[n];
        // diags = new boolean[n + n - 1];
        // adiags = new boolean[n + n - 1];
        // System.out.println(nqueen_02(n, tnq, 0, ""));
        System.out.println(nqueen_03(n, 0, ""));
    }
}

```

nqueens3()

This code is an implementation of the **N-Queens problem using Bitmasking** for optimization. This is widely considered the most efficient way to solve N-Queens (often referred to as the "bitwise solution").

Here is a breakdown of the logic, specifically focusing on the math used to track diagonals.

---

### 1. The Variables
* **`floor` (Row $r$):** Represents the current row we are trying to place a Queen in. The recursion moves `floor + 1`, ensuring we place exactly one Queen per row.
* **`room` (Column $c$):** The loop iterates through columns $0$ to $n-1$.

---

### 2. The 4 Safety Checks (Bitmasks)
Instead of checking the board with loops ($O(N)$), we check 4 integers ($O(1)$) to see if a spot is safe.

#### A. Column Check (`col`)
* **Formula:** `1 << c`
* **Logic:** Tracks which columns are occupied. If we place a queen at $(0, 2)$, the 2nd bit of `col` becomes $1$.

#### B. Normal Diagonal (`diag`)
* **Formula:** `r - c + (n - 1)`
* **Logic:** For any cell $(r, c)$ on a main diagonal (top-left to bottom-right), the value $r - c$ is constant.
    * *Example:* $(1, 0), (2, 1), (3, 2) \to 1-0=1, 2-1=1, 3-2=1$.
* **Why `+ (n - 1)`?** $r - c$ can be negative (e.g., $0 - 3 = -3$). Bit shifts cannot be negative. Adding $n - 1$ shifts the range to be strictly positive (from $0$ to $2n - 2$).

#### C. Anti-Diagonal (`adiag`)
* **Formula:** `r + c`
* **Logic:** For any cell on an anti-diagonal (top-right to bottom-left), the value $r + c$ is constant.
    * *Example:* $(0, 2), (1, 1), (2, 0) \to 0+2=2, 1+1=2, 2+0=2$.
* **Range:** $0$ to $2n - 2$.

#### D. Row Check (`row`) — Technically Redundant
* **Formula:** `1 << r`
* **Note:** Since your recursion moves `floor` to `floor + 1`, you naturally never visit the same row twice. This check doesn't break anything, but you could delete the row logic entirely and the code would still work perfectly.

---

### 3. The XOR Toggle (`^=`)
This code uses the **XOR trick** for Backtracking that we discussed earlier. 

* **Place:** `col ^= (1 << room)` flips the bit from $0$ to $1$.
* **Backtrack:** `col ^= (1 << room)` flips the bit from $1$ back to $0$.

Because the code checks if the bit is $0$ before entering the recursion, XOR acts as a perfect "on/off" switch.

---


```java

// 1. PLACE QUEEN
// XOR (^) toggles the bit from 0 to 1 (Mark as unsafe)
col ^= (1 << c); 

// Recurse to next row
nqueen_03(n, floor + 1, ...);

// 2. REMOVE QUEEN (Backtrack)
// XOR (^) toggles the bit from 1 back to 0 (Mark as safe again)
col ^= (1 << c);
```

### Summary of Efficiency

* **Space Complexity:** Uses **$O(1)$** extra space via integers (`col`, `diag`, `adiag`) instead of an $O(N^2)$ board or multiple $O(N)$ boolean arrays. (Note: The recursion stack remains $O(N)$).
* **Time Complexity:** The safety check is an **instant bitwise AND (`&`)** operation rather than iterating through the board, significantly reducing the constant factor of the $O(N!)$ backtracking search.

---

# Q M Coloring Problem

### Problem Statement
Given an integer `M` and an undirected graph with `N` vertices (zero-indexed) and `E` edges, determine whether the graph can be colored with a maximum of `M` colors such that no two adjacent vertices have the same color applied to them.

In this context, coloring a graph refers to assigning a color to each vertex. If such a coloring is possible, return `true`; otherwise, return `false`.

### Examples

**Example 1**
```text
Input : N = 4 , M = 3 , E = 5 , Edges = [ (0, 1) , (1, 2) , (2, 3) , (3, 0) , (0, 2) ]
Output : true
Explanation : Consider the three colors to be red, green, blue.
We can color the vertex 0 with red, vertex 1 with blue, vertex 2 with green, vertex 3 with blue.
In this way we can color graph using 3 colors at most.
```
### Constraints
- $1 \leq N \leq 20$
- $1 \leq E \leq \frac{N \times (N-1)}{2}$
- $1 \leq M \leq N$
## Recursive code

```cpp
class Solution {
public:
    bool isSafe(int col, int node, vector<int>& colors, vector<int> adj[]) {
        // Check adjacent nodes
        for (int i = 0; i < adj[node].size(); i++) {
            if (colors[adj[node][i]] == col) return false;
        }
        return true; // Safe to color
    }

    // Recursive function to solve graph coloring problem
    bool solve(int node, int m, int n, vector<int>& colors, vector<int> adj[]) {
        // If all nodes are colored
        if (n == node) return true;
        // Try all colors from 1 to m
        for (int i = 1; i <= m; i++) {
            // Check if it is safe to color the node with color i
            if (isSafe(i, node, colors, adj)) {
             // Assign color i to node
                colors[node] = i;
                // Recursively try to color the next node
                if (solve(node + 1, m, n, colors, adj)) return true;
                // Reset color if it doesn't lead to a solution
                colors[node] = 0; 
            }
        }
        // No color can be assigned
        return false; 
    }

    // Function to check if the graph can be colored with m colors
    bool graphColoring(vector<vector<int>>& edges, int m, int n) {
     // Adjacency list representation of the graph 
        vector<int> adj[n];

        // Build the graph from edges
        for (int i = 0; i < edges.size(); i++) {
            adj[edges[i][0]].push_back(edges[i][1]);
            adj[edges[i][1]].push_back(edges[i][0]);
        }
        // Initialize all colors to 0 (uncolored)
        vector<int> colors(n, 0);
        // Start solving from the first node
        return solve(0, m, n, colors, adj);
    }
};
```

## Bitwise optimized code

```cpp
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    // Recursive function with Bitmasking
    bool solve(int node, int m, int n, vector<long long>& colorMasks, vector<long long>& adj) {
        // Base case: If we went past the last node (0 to n-1), we are done
        if (node == n) return true;

        // Try all colors from 1 to m
        for (int c = 1; c <= m; c++) {
            
            // OPTIMIZATION HERE:
            // Check intersection of Current Node's Neighbors AND Existing Nodes with Color 'c'
            // If the result is 0, it means no neighbor has this color.
            if ((adj[node] & colorMasks[c]) == 0) {
                
                // Assign color 'c' to 'node' (Set the bit)
                colorMasks[c] |= (1LL << node);

                // Recurse
                if (solve(node + 1, m, n, colorMasks, adj)) return true;

                // Backtrack (Unset the bit)
                colorMasks[c] &= ~(1LL << node);
            }
        }
        return false;
    }

    bool graphColoring(vector<vector<int>>& edges, int m, int n) {
        // Use long long to support up to 64 nodes. 
        // adj[i] is a bitmask representing all neighbors of node i
        vector<long long> adj(n, 0);

        // Build the graph using bits
        for (auto& e : edges) {
            int u = e[0];
            int v = e[1];
            adj[u] |= (1LL << v); // Set v-th bit for u
            adj[v] |= (1LL << u); // Set u-th bit for v
        }

        // colorMasks[c] stores a bitmask of all nodes assigned to color c
        // Size is m + 1 because colors are 1-based
        vector<long long> colorMasks(m + 1, 0);

        return solve(0, m, n, colorMasks, adj);
    }
};

int main() {
    Solution sol;
    vector<vector<int>> edges = {
        {0, 1}, {0, 2}, {1, 2}, {1, 3}
    };
    int m = 3; 
    int n = 4; 

    if (sol.graphColoring(edges, m, n)) {
        cout << "The graph can be colored with " << m << " colors." << endl;
    } else {
        cout << "The graph cannot be colored with " << m << " colors." << endl;
    }

    return 0;
}
```
### Why is this better?

* **Complexity:** The original `isSafe` took $O(D)$ time where $D$ is the degree of the node (number of neighbors). The bitwise check takes **$O(1)$** time, as the CPU executes a bitwise AND in a single clock cycle.
* **Memory Locality:** Bitwise operations happen directly in **CPU registers**, which is significantly faster than repeatedly fetching neighbor values from a heap-allocated `vector<vector<int>>`.

---

### Constraint Note
This approach relies on the number of nodes $N$ fitting into a specific integer type:

* `int` supports $N \le 32$.
* `long long` supports $N \le 64$.
* **If $N > 64$:** You would need to use C++'s `std::bitset<100>`. This works exactly the same way but supports arbitrary sizes, though it is slightly slower than a raw `long long`.


# Learning Through Code: The Bitmask "Freeze Frame"

It is completely normal to learn better by seeing the code. In fact, most senior engineers prefer reading code over reading documentation because code doesn't lie.

Let's take a **"Freeze Frame"** of exactly what happens inside that bitwise check. This will solidify why it replaces the loop entirely.

### The "Freeze Frame" Visualization
Imagine we are in the middle of solving the graph.

* **Current Node:** 2
* **Neighbors of 2:** Node 0 and Node 1.
* **Binary for Node 0:** `...0001`
* **Binary for Node 1:** `...0010`
* **adj[2] Mask:** `...0011` (Neighbors are 0 and 1)

Now, we try to give Node 2 the color **Red** (Index 1).
* **Who currently has Red?** Let's say Node 0 and Node 5 already have Red.
* **colorMasks[1]:** `...100001` (Bits 0 and 5 are set)

### The Magic Operation
The code runs: `if ((adj[node] & colorMasks[c]) == 0)`

Let's do the math:

```text
  00000011  (adj[2] - The neighbors of Node 2)
& 00100001  (colorMasks[1] - Nodes that are already Red)
------------------------------------------------
  00000001  (Result is NOT zero!)
```

**Result:** The result is 1 (non-zero).  
**Meaning:** "Collision detected at bit 0!"

The CPU sees the collision instantly. It knows Node 0 is both a neighbor **AND** already Red. It returns `false` immediately.

```cpp
// O(Degree) - Loops 2 times for 2 neighbors
for (int neighbor : adj[node]) {
    if (colors[neighbor] == currentColor) return false;
}
```
we replaced above code with this below code!!

```cpp
// O(1) - One CPU cycle. No loops. No jumps.
if (adj[node] & colorMasks[c]) return false;
```

### When can you use this?
You can use this **Adjacency Mask** trick whenever:
* **N is small:** $N \le 64$ (using `long long`).
* **The graph is dense:** You check connectivity a lot.
* **The problem is NP-Hard:** Like Graph Coloring, Hamiltonian Path, or Traveling Salesman. These problems are exponential ($O(2^N)$), so shaving the inner loop from $O(N)$ to $O(1)$ makes your code roughly $N$ times faster.

# Q Word Search

### Problem Statement
Given a grid of `n x m` dimension grid of characters `board` and a string `word`. The word can be created by assembling the letters of successively surrounding cells, whether they are next to each other vertically or horizontally. It is forbidden to use the same letter cell more than once.

Return `true` if the word exists in the grid otherwise `false`.

### Examples

**Example 1**
```text
Input : board = [ ["A", "B", "C", "E"] , ["S" ,"F" ,"C" ,"S"] , ["A", "D", "E", "E"] ] , word = "ABCCED"
Output : true
Explanation : The word is coloured in yellow.
```

**Example 2**
```text
Input : board = [["A", "B", "C", "E"] , ["S", "F", "C", "S"] , ["A", "D", "E", "E"]] , word = "SEE"
Output : true
Explanation : The word is coloured in yellow.
```
### Constraints
- $n = \text{board.length}$
- $m = \text{board}[i].\text{length}$
- $1 \leq n, m \leq 6$
- $1 \leq \text{word.length} \leq 15$
- `board` and `word` consist of only lowercase and uppercase English letters.

Now as `n,m<=6` so `n*m<=36` so i no need of vis array i can use `long long` to track vis 




```cpp
class Solution {
    vector<vector<int>> dir = {{-1, 0}, {1, 0}, {0, 1}, {0, -1}};

    bool solve(vector<vector<char>>& board, int idx, string word, int widx,
               long long vis) {
        int n = board.size();
        int m = board[0].size();
        if (widx == word.size() - 1)
            return word[widx] == board[idx / m][idx % m] ? true : false;
        int r = idx / m;
        int c = idx % m;
        bool val = false;
        vis |= (1 << idx);
        if (word[widx] != board[r][c]) return val;

        for (int i = 0; i < 4; i++) {
            int newr = r + dir[i][0];
            int newc = c + dir[i][1];
            int newidx = newr * m + newc;
            if (newr >= 0 && newr < n && newc >= 0 && newc < m &&
                (vis & (1 << newidx)) == 0) {
                val |= solve(board, newidx, word, widx + 1, vis);
                if (val == true) return true;
            }
        }

        // vis &= ~(1 << idx);
        return val;
    }

   public:
    bool exist(vector<vector<char>>& board, string word) {
        int n = board.size();
        int m = board[0].size();
        for (int i = 0; i < n * m; i++) {
            if (board[i / m][i % m] == word[0]) {
                if (solve(board, i, word, 0, 0)) return true;
            }
        }
        return false;
    }
};
```

## Ai review

### It is very impressive, but it is also risky.

Here is the "Senior Engineer" assessment of using this specific code in an interview:

### The "High Risk, High Reward" Strategy

**1. The "Wow" Factor (Why it impresses)**
* **Space Optimization:** Most candidates allocate a full `vector<vector<bool>> visited` ($O(N \cdot M)$ space). You used a single `long long` integer ($O(1)$ space).
* **Clean Backtracking:** Passing `vis` by value eliminates the need for manual backtracking (`vis[r][c] = false`). This makes your code significantly shorter and less bug-prone.

**2. The "Fatal Flaw" (Why it fails)**
* **The 64-Cell Limit:** Your code will crash or fail if the board is larger than $8 \times 8$ (64 cells).
* If the interviewer gives you a $10 \times 10$ board, `1LL << 99` will overflow, and your logic breaks.
* **Standard Constraints:** LeetCode constraints for "Word Search" are usually $N, M \le 6$ (Total $\le 36$), so it works there. But in real life or follow-ups, grids are bigger.

### The "Senior" Verdict: How to Pitch It
If you write this, you **MUST** verbally call out the constraint immediately. Don't just write it. Say this:

> "I can solve this using a standard 2D visited array, but since the constraints here are small ($N \cdot M \le 64$), I will use a **Bitmask Optimization**. This reduces the auxiliary space from $O(N \cdot M)$ to $O(1)$ by storing the visited state in a single 64-bit integer. If the grid were larger, I would revert to the 2D array approach."

### Final Recommendation
* **For "Word Search I" (Small Grid):** Use your bitmask approach. It shows mastery.
* **For General DFS (Unknown Grid Size):** Stick to `vector<vector<bool>>`. It is safer and works for any size.



