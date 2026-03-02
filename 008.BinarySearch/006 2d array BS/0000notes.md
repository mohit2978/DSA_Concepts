# Q1 Median Matrix


Given a 2D array matrix that is row-wise sorted. The task is to find the median of the given matrix.

---

Example 1

Input: matrix=[ [1, 4, 9], [2, 5, 6], [3, 7, 8] ] 

Output: 5

Explanation: If we find the linear sorted array, the array becomes 1 2 3 4 5 6 7 8 9. So, median = 5

---

Example 2

Input: matrix=[ [1, 3, 8], [2, 3, 4], [1, 2, 5] ] 

Output: 3

Explanation: If we find the linear sorted array, the array becomes 1 1 2 2 3 3 4 5 8. So, median = 3
![alt text](Scanned_20251221-1443-01.jpg)
 ![alt text](Scanned_20251221-1443-02.jpg) 
 ![alt text](Scanned_20251221-1443-03.jpg) 
 ![alt text](Scanned_20251221-1443-04.jpg) 
 ![alt text](Scanned_20251221-1443-05.jpg) 
![alt text](Scanned_20251221-1443-06.jpg) 
### Code


```cpp

class Solution{
    int countElementLessThanEqualTo(int val,vector<vector<int>>&mat,int n,int m){
        int cnt=0;
        for(int i=0;i<mat.size();i++){
            cnt+=(upper_bound(mat[i].begin(),mat[i].end(),val)-mat[i].begin());
        }
        return cnt;
    }
public:
    int findMedian(vector<vector<int>>&matrix) {
        int n = matrix.size();
        int m = matrix[0].size(); 
        
        int low = INT_MAX, high = INT_MIN;

        for (int i = 0; i < n; i++) {
            low = min(low, matrix[i][0]);
            high = max(high, matrix[i][m - 1]);
        }
         int req = (n * m) / 2;
            while (low <= high) {
                int mid=(low+high)/2;
                if(countElementLessThanEqualTo(mid,matrix,n,m)>req) high=mid-1;
                else low=mid+1;
          }
          return low;
    }
};
```
or 

```cpp
class Solution{
    int countElementLessThanEqualTo(int val,vector<vector<int>>&mat,int n,int m){
        int cnt=0;
        for(int i=0;i<mat.size();i++){
            cnt+=(upper_bound(mat[i].begin(),mat[i].end(),val)-mat[i].begin());
        }
        return cnt;
    }
public:
    int findMedian(vector<vector<int>>&matrix) {
        int n = matrix.size();
        int m = matrix[0].size(); 
        
        int low = INT_MAX, high = INT_MIN;

        for (int i = 0; i < n; i++) {
            low = min(low, matrix[i][0]);
            high = max(high, matrix[i][m - 1]);
        }
         int req = (n * m) / 2;
            while (low <= high) {
                int mid=(low+high)/2;
                if(countElementLessThanEqualTo (mid,matrix,n,m)>req) high=mid-1;
                else low=mid+1;
          }
          return high+1;
    }
};
```

same code just returning (high+1) as on last iteration high,low will be on same element and then 

# Q2 Search in a 2D matrix

Given a 2-D array mat where the elements of each row are sorted in non-decreasing order, and the first element of a row is greater than the last element of the previous row (if it exists), and an integer target, determine if the target exists in the given mat or not.


Example 1

Input: mat = [ [1, 2, 3, 4], [5, 6, 7, 8], [9, 10, 11, 12] ], target = 8

Output: True

Explanation: The target = 8 exists in the 'mat' at index (1, 3).

Example 2

Input: mat = [ [1, 2, 4], [6, 7, 8], [9, 10, 34] ], target = 78

Output: False

Explanation: The target = 78 does not exist in the 'mat'. Therefore in the output, we see 'false'.

Constraints

 -  n == mat.length
 -  m == mat[i].length
  - 1 <= m, n <= 100
  - -$10^4$ <= mat[i][j], target <= $10^4$

### Brute --> Serach in every cell O(n*m)

### Better-->

```cpp

#include <bits/stdc++.h>
using namespace std;

class Solution {
private:
    //Fuction to perform binary search 
    bool binarySearch(vector<int>& mat, int target) {
        int n = mat.size(); 
        int low = 0, high = n - 1;

        //Perform binary search
        while (low <= high) {
            int mid = (low + high) / 2;
            
            //Return true if target is found
            if (mat[mid] == target) return true;
            else if (target > mat[mid]) low = mid + 1;
            else high = mid - 1;
        }
        //Return false if target not found
        return false;
    }
public:
    //Function to search for a given target in matrix
    bool searchMatrix(vector<vector<int>>& mat, int target) {
        int n = mat.size();
        int m = mat[0].size();

        for (int i = 0; i < n; i++) {
            
            /*Check if there is a possibility that
            the target can be found in current row*/
            if (mat[i][0] <= target && target <= mat[i][m - 1]) {
                
                /*Return result fetched 
                from helper function*/
                return binarySearch(mat[i], target);
            }
        }
        // Return false if target is not found
        return false; 
    }
};

int main() {
    
    vector<vector<int>> matrix = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}};
    int target = 8;
    
    //Create an instace of Solution class
    Solution sol;
    
    bool result = sol.searchMatrix(matrix, target);
    
    // Output the result
    result ? cout << "true\n" : cout << "false\n";
    
    return 0;
}

```

Complexity Analysis: 

Time Complexity: O(N + logM), where N is given row number, M is given column number. The rows are traversed in O(N) time complexity. Binary search is applied only once for a particular row, resulting in a time complexity of O(N + logM) instead of O(N*logM).

Space Complexity: As no additional space is used, so the Space Complexity is O(1).

### Optimal
treat 2d matrix as 1d

#### Why it works??

the first element of a row is greater than the last element of the previous row (if it exists)
[Given in question]

```cpp
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    //Function to search for a given target in matrix
    bool searchMatrix(vector<vector<int>>& mat, int target) {
        int n = mat.size();
        int m = mat[0].size();

        int low = 0, high = n * m - 1;
        //Perform binary search
        while (low <= high) {
            int mid = (low + high) / 2;
                
            //Calculate the row and column
            int row = mid / m, col = mid % m;
                
            //If target is found return true
            if (mat[row][col] == target) return true;
            else if (mat[row][col] < target) low = mid + 1;
            else high = mid - 1;
        }
        // Return false if target is not found
        return false; 
    }
};

int main() {
    
    vector<vector<int>> matrix = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}};
    int target = 8;
    
    //Create an instace of Solution class
    Solution sol;
    
    bool result = sol.searchMatrix(matrix, target);
    
    // Output the result
    result ? cout << "true\n" : cout << "false\n";
    
    return 0;
}

```

Complexity Analysis: 

Time Complexity: $O(log(N*M))$, where N is the number of rows in the matrix, M is the number of columns in each row. As, binary search is being applied on the 1-D array of size $N*M$.

Space Complexity: As no additional space is used, so the Space Complexity is O(1).

#### Follow up
Can this approach be extended to 3D or higher-dimensional arrays?

For higher-dimensional arrays: Flatten the array into a 1D structure and apply binary search. Use modular arithmetic to map 1D indices to multi-dimensional coordinates.


# Q3-->  Find the Row with Maximum Number of 1's

### Problem Statement
You are given a non-empty 2D binary matrix `mat` of size `n x m` consisting of only `0`s and `1`s. In this matrix, **each row is sorted in ascending order**.

Your task is to find the index of the row that contains the **maximum number of ones**.

**Notes:**
* If multiple rows have the same maximum number of ones, return the index of the row with the **smallest index**.
* If no row contains at least one `1`, return `-1`.
* The matrix is 0-indexed.

---

### Examples

#### Example 1:
**Input:** `n = 3, m = 3`  
**Matrix:**

```text
1 1 1
0 0 1
0 0 0
```
**Output:** `0`  
**Explanation:** - Row 0 has three 1's.
- Row 1 has one 1.
- Row 2 has zero 1's.
The row with the maximum 1's is index 0.

#### Example 2:
**Input:** `n = 2, m = 2`  
**Matrix:**

```text
0 0
0 0
```
**Output:** `-1`  
**Explanation:** The matrix does not contain any 1.

### Constraints
* `1 ≤ n, m ≤ 100`
* `mat[i][j]` is either `0` or `1`.
* Each row is sorted in non-decreasing order.

---

### Approaches

#### 1. Brute Force (Linear Search)
Traverse each row and count the number of 1's by iterating through all columns. Keep track of the maximum count and the corresponding row index.
* **Time Complexity:** `O(n * m)`
* **Space Complexity:** `O(1)`

#### 2. Better Approach (Binary Search)
Since each row is sorted, you don't need to count every 1. For each row, use **Binary Search** to find the first occurrence of `1`. The number of 1's in that row will be `m - (index of first 1)`.
* **Time Complexity:** `O(n * log m)`
* **Space Complexity:** `O(1)`

#### 3. Optimal Approach (The "Staircase" Search)
Start from the top-right corner `(row = 0, col = m-1)`.
1. If the current element is `1`, it means this row could be the one with the most 1's. Move left (`col--`) to see if there are even more 1's in this row and update your answer.
2. If the current element is `0`, move down (`row++`) to check the next row.
* **Time Complexity:** `O(n + m)`
* **Space Complexity:** `O(1)`

## Bruteforce

```cpp
class Solution {
  public:   
  int rowWithMax1s(vector < vector < int >> & mat) {
        int ans=0; int maxOnes=0;
        for(int i=0;i<mat.size();i++){
          int cnt=0;
          for(int j=0;j<mat[0].size();j++){
            if(mat[i][j]==1) cnt++;
          }
          if(cnt>maxOnes ) {
            maxOnes=cnt;
            ans=i;
          }
        }
        return maxOnes==0?-1:ans;
  }
};
```

# Binary search

```cpp
class Solution {

public:

    int rowWithMax1s(vector<vector<int>>& mat) {
        int n = mat.size();
        int m = mat[0].size();
        int cnt_max = 0; 
        int index = -1;  
        for (int i = 0; i < n; i++) {

            int cnt_ones =  mat[i].end()-lower_bound(mat[i].begin(), mat[i].end(), 1);
            if (cnt_ones > cnt_max) {
                cnt_max = cnt_ones;
                index = i;
            }
        }

        return index;
    }
};
```
### The "Staircase Search" Logic ($O(N + M)$)

This approach treats the matrix like a staircase to find the **leftmost `1`** in the entire matrix without scanning every cell.

#### The Algorithm:
1. **Start** at the top-right corner: `row = 0`, `col = m - 1`.
2. **While** you are inside the matrix boundaries:
    * **If `mat[row][col] == 1`**: 
        * This row is the current "champion" (it has the most `1`s seen so far).
        * Update `max_row_index = row`.
        * Move **Left** (`col--`) to see if there is an even earlier `1`.
    * **Else (`mat[row][col] == 0`)**:
        * This row cannot possibly beat the current champion.
        * Move **Down** (`row++`) to check the next row.

#### Why it works:
Since rows are sorted, as soon as you hit a `0` while moving left, you know that row has no more `1`s. By moving down, you are looking for a row that has a `1` at an even smaller column index than your current record.

```cpp
class Solution {

public:

    int rowWithMax1s(vector<vector<int>>& mat) {
        int n = mat.size();
        int m = mat[0].size();
        int cnt_max = 0; 
        int index = -1;  
        int row=0;
        int col=m-1;

        while(row<n && col>=0){
            if(mat[row][col]==1){
                index=row;
                col--;
            }else row++;
        }

        return index;
    }
};
```
# Q4--> Search in a 2D Matrix II

### Problem Statement
Write an efficient algorithm that searches for a value `target` in an `m x n` integer matrix `matrix`. 

This matrix has the following properties:
* Integers in each row are sorted in ascending order from left to right.
* Integers in each column are sorted in ascending order from top to bottom.

Your function should return `true` if the `target` exists in the matrix, and `false` otherwise.

---

### Examples

#### Example 1:
**Input:** 
```text

matrix = [
  [1,   4,  7, 11, 15],
  [2,   5,  8, 12, 19],
  [3,   6,  9, 16, 22],
  [10, 13, 14, 17, 24],
  [18, 21, 23, 26, 30]
]
```
target = 5

Output: true

Example 2:
Input: 
```text
matrix = [
[1,   4,  7, 11, 15],
[2,   5,  8, 12, 19],
[3,   6,  9, 16, 22],
[10, 13, 14, 17, 24],
[18, 21, 23, 26, 30]
]
```
target = 20
**Output:** `false`

---

### Constraints
* `m == matrix.length`
* `n == matrix[i].length`
* `1 <= n, m <= 300`
* `-10^9 <= matrix[i][j] <= 10^9`
* `-10^9 <= target <= 10^9`

---

### The "Search Space Reduction" Approach (Staircase Search)

Since both rows and columns are sorted, we can start at a corner where we have a decision to make. If we start at the **top-right** corner:
1. Every element to the **left** is smaller.
2. Every element **below** is larger.

#### Steps:
1. Start at `row = 0` and `col = n - 1`.
2. Compare `matrix[row][col]` with `target`:
    * If `matrix[row][col] == target`: Return `true`.
    * If `matrix[row][col] > target`: The target cannot be in this column (since all elements below it are even larger). Move **Left** (`col--`).
    * If `matrix[row][col] < target`: The target cannot be in this row (since all elements to the left are even smaller). Move **Down** (`row++`).
3. If the loop ends (out of bounds) without finding the target, return `false`.

---

```cpp
class Solution {
   public:
    bool searchMatrix(vector<vector<int>> &mat, int tar) {
        int n = mat.size();
        int m = mat[0].size();
        int row = 0;
        int col = m - 1;

        while (row < n && col >= 0) {
            if (mat[row][col] == tar)
                return true;
            else if (mat[row][col] > tar)
                col--;
            else
                row++;
        }

        return false;
        ;
    }
};
```

### Complexity Analysis
* **Time Complexity:** `O(m + n)`  
  In the worst case, you will traverse across the width and height of the matrix once.
* **Space Complexity:** `O(1)`  
  No extra space is used.


# Q5-->Find Peak Element II

### Problem Statement
A **peak element** in a 2D grid is an element that is **strictly greater** than all of its adjacent neighbors: left, right, top, and bottom.

Given a 0-indexed `m x n` matrix `mat` where no two adjacent cells are equal, find **any** peak element `mat[i][j]` and return its 0-indexed coordinates `[i, j]`.

**Notes:**
* The matrix is conceptually surrounded by an outer perimeter with the value `-1` in each cell.
* You must write an algorithm that runs in `O(m log n)` or `O(n log m)` time.

---

### Examples

#### Example 1:
**Input:** `mat = [[1, 4], [3, 2]]`  
**Output:** `[0, 1]`  
**Explanation:** Both 3 and 4 are peak elements. 
- For 4 (at `[0, 1]`): Neighbors are 1 (left), 2 (bottom), and -1 (top/right). 4 is greater than all.
- For 3 (at `[1, 0]`): Neighbors are 1 (top), 2 (right), and -1 (bottom/left). 3 is greater than all.
Either `[0, 1]` or `[1, 0]` is an acceptable answer.

#### Example 2:
**Input:** `mat = [[10, 20, 15], [21, 30, 14], [7, 16, 32]]`  
**Output:** `[1, 1]`  
**Explanation:** Both 30 and 32 are peak elements. 30 is at `[1, 1]` and 32 is at `[2, 2]`.

---

### Constraints
* `m == mat.length`
* `n == mat[i].length`
* `1 <= m, n <= 500`
* `1 <= mat[i][j] <= 10^5`
* No two adjacent cells are equal.

---

### Optimal Approach: Binary Search on Columns ($O(n \log m)$)

The core idea is to perform a binary search on the **columns** to find the peak, and for each column, find the **maximum element** in that column to ensure we only need to compare it with its horizontal neighbors.

#### Steps:
1. **Binary Search Range:** Set `low = 0` and `high = n - 1` (representing column indices).
2. **Find Mid:** Calculate `mid = (low + high) / 2`.
3. **Max in Column:** Find the index of the **maximum element** in the `mid` column. Let's call this row index `maxRow`.
4. **Compare with Neighbors:**
    * Check the left neighbor: `left = (mid > 0) ? mat[maxRow][mid - 1] : -1`
    * Check the right neighbor: `right = (mid < n - 1) ? mat[maxRow][mid + 1] : -1`
5. **Decide Search Direction:**
    * If `mat[maxRow][mid] > left` AND `mat[maxRow][mid] > right`: You found a peak! Return `[maxRow, mid]`.
    * If `mat[maxRow][mid] < left`: A peak must exist in the left half. Set `high = mid - 1`.
    * Else (`mat[maxRow][mid] < right`): A peak must exist in the right half. Set `low = mid + 1`.
### How the Row is Decided (The "Column Max" Rule)

In a 2D Peak Find, we do not binary search on rows and columns at the same time. Instead:

1. **Pick a Column:** Use Binary Search to pick a `mid` column.
2. **Find the Row:** In that `mid` column, find the **index of the maximum element**.
   * Code logic: `int maxRow = findMaxRowInColumn(matrix, mid);`
3. **The Logic:**
   * By choosing the **largest** element in the column, you satisfy the "Peak" condition for the **Top** and **Bottom** neighbors automatically.
   * Now, the 2D problem is reduced to a 1D problem: Is this element larger than its **Left** and **Right** neighbors?
4. **Move the Search:**
   * If `matrix[maxRow][mid]` is smaller than the element to its right, a peak **must** exist somewhere in the right half of the matrix. 
   * We move the `low` pointer and repeat the "Find Max Row" process in the new `mid` column.


### The "Follow the Higher Neighbor" Logic

In the 2D Peak Element problem, once you find the maximum element in the `mid` column (`mat[maxRow][mid]`), you use the following movement rules:

#### 1. `if (mat[maxRow][mid] < left)`
* **Logic:** Even though `mat[maxRow][mid]` is the largest in its column, there is a neighbor to the left that is **even higher**.
* **Guarantee:** Because the values cannot increase forever (they must eventually decrease or hit the `-1` boundary), there **must** be a peak in the left half.
* **Movement:** `high = mid - 1`.

#### 2. `else if (mat[maxRow][mid] < right)`
* **Logic:** The right neighbor is higher than the current column maximum.
* **Guarantee:** A peak is guaranteed to exist somewhere in the right half.
* **Movement:** `low = mid + 1`.

#### 3. `else` (The Peak Found!)
* **Logic:** If the element is not smaller than its left neighbor AND not smaller than its right neighbor, it is **strictly greater** than both. 
* **Conclusion:** Since it was already the maximum in its column (greater than top/bottom), it is now a **2D Peak**.
* **Return:** `[maxRow, mid]`.   
#### Why this works:
By picking the maximum element in a column, we already know it is greater than its **top** and **bottom** neighbors. We then only need to check its **left** and **right** neighbors. If it's not a peak, we move toward the larger neighbor, guaranteed to eventually find a peak because of the `-1` boundaries.

---



```cpp
class Solution {
public:
    /* Helper function to find the index of the row
    with the maximum element in a given column*/
    int maxElement(vector<vector<int>>& arr, int col) {
        int n = arr.size();
        int max_val = INT_MIN;
        int index = -1;
        
        /* Iterate through each row to find the
        maximum element in the specified column*/
        for (int i = 0; i < n; i++) {
            if (arr[i][col] > max_val) {
                max_val = arr[i][col];
                index = i;
            }
        }
        // Return the index
        return index;
    }
    
    /* Function to find a peak element in 
     the 2D matrix using binary search */
    vector<int> findPeakGrid(vector<vector<int>>& arr) {
        int n = arr.size();     
        int m = arr[0].size();  
        
        /* Initialize the lower bound for 
        and upper bound for binary search */
        int low = 0;           
        int high = m - 1;      
        
        // Perform binary search on columns
        while (low <= high) {
            int mid = (low + high) / 2;  
            
            /* Find the index of the row with the 
            maximum element in the middle column*/
            int row = maxElement(arr, mid);
            
            /* Determine the elements to left and 
            right of middle element in the found row */
            int left = mid - 1 >= 0 ? arr[row][mid - 1] : INT_MIN;
            int right = mid + 1 < m ? arr[row][mid + 1] : INT_MIN;
            
            /* Check if the middle element 
             is greater than its neighbors */
            if (arr[row][mid] > left && arr[row][mid] > right) {
                return {row, mid};  
            } 
            else if (left > arr[row][mid]) {
                high = mid - 1;  
            } 
            else {
                low = mid + 1;
            }
        }
        
        // Return {-1, -1} if no peak element is found
        return {-1, -1};  
    }
};
```

### Complexity Analysis
* **Time Complexity:** `O(m * log n)` — We perform binary search on `n` columns (`log n` steps), and in each step, we traverse `m` rows to find the maximum element.
* **Space Complexity:** `O(1)` — No extra space is used.