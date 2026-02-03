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

![alt text](<005 sudoku solver word break_231229_131220(6).jpg>) ![alt text](<005 sudoku solver word break_231229_131220(7).jpg>) ![alt text](<005 sudoku solver word break_231229_131220(8).jpg>) ![alt text](<005 sudoku solver word break_231229_131220(9).jpg>) ![alt text](<005 sudoku solver word break_231229_131220(10).jpg>) ![alt text](<005 sudoku solver word break_231229_131220(11).jpg>) ![alt text](<005 sudoku solver word break_231229_131220(12).jpg>) ![alt text](<005 sudoku solver word break_231229_131220(13).jpg>) ![alt text](<005 sudoku solver word break_231229_131220(14).jpg>) ![alt text](<005 sudoku solver word break_231229_131220(15).jpg>) ![alt text](<005 sudoku solver word break_231229_131220(16).jpg>)