# Notes

## Q1 simple power set or set of subsets

### cpp way
```cpp
#include <bits/stdc++.h>
using namespace std;

class Solution {
private:
    void func(int ind, int n, vector<int> &nums, vector<int> &arr, vector<vector<int>> &ans) {
        if (ind == n) {
            ans.push_back(arr);
            return;
        }

      
        func(ind + 1, n, nums, arr, ans);

        arr.push_back(nums[ind]);
        func(ind + 1, n, nums, arr, ans);

        arr.pop_back();
    }

public:
    vector<vector<int>> powerSet(vector<int> &nums) {
        vector<vector<int>> ans;  // List to store all subsets
        vector<int> arr;  // Temporary list to store the current subset
        func(0, nums.size(), nums, arr, ans);  // Start the recursive process
        return ans;  // Return the list of all subsets
    }
};

// Main method to test the code
int main() {
    Solution sol;
    vector<int> nums = {1, 2, 3};
    vector<vector<int>> result = sol.powerSet(nums);
    
    // Print the result
    for (const auto &subset : result) {
        cout << "[";
        for (int num : subset) {
            cout << num << " ";
        }
        cout << "]" << endl;
    }

    return 0;
}

```

### Java way

```java

//Another way to generate power set one was by bits 
//both have same TC 
//can see in bits power set
class Solution {
    private void generatePowerSet(int[] a ,int n,List<List<Integer>> res, List<Integer>tres,int idx){
        if(idx==n){
            res.add(new ArrayList<>(tres));
            return;
        }
        tres.add(a[idx]);
        generatePowerSet(a,n,res,tres,idx+1);
        tres.remove(tres.size()-1);
        generatePowerSet(a,n,res,tres,idx+1);
    }
    public List<List<Integer>> powerSet(int[] nums) {
        List<List<Integer>> res=new ArrayList<>();
        List<Integer>tres=new ArrayList<>();
        generatePowerSet(nums,nums.length,res,tres,0);
        return res;
    }
}
```

### Java bits way 


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
## Q2 Subsets I

Given an array nums of n integers. Return array of sum of all subsets of the array nums.



Output can be returned in any order.

---
Example 1

Input : nums = [2, 3]

Output : [0, 2, 3, 5]

Explanation :

When no elements is taken then Sum = 0.

When only 2 is taken then Sum = 2.

When only 3 is taken then Sum = 3.

When element 2 and 3 are taken then sum = 2+3 = 5.

Example 2

Input : nums = [5, 2, 1]

Output : [0, 1, 2, 3, 5, 6, 7, 8]

Explanation :

When no elements is taken then Sum = 0.

When only 5 is taken then Sum = 5.

When only 2 is taken then Sum = 2.

When only 1 is taken then Sum = 1.

When element 2 and 1 are taken then sum = 2+1 = 3.

### Java
```java
class Solution {
    private void generatePowerSet(int[] a ,int n, List<Integer>res,int idx,int sum){
        if(idx==n){
            res.add(sum);
            return;
        }
        generatePowerSet(a,n,res,idx+1,sum);
        sum+=a[idx];
        generatePowerSet(a,n,res,idx+1,sum);
        
    }
    public void  powerSet(int[] nums, List<Integer>res) {
  
        generatePowerSet(nums,nums.length,res,0,0);
        
    }
    public List<Integer> subsetSums(int[] nums) {
       List<Integer>res=new ArrayList<>();
       powerSet(nums,res);
       return res;
    }
}
```
### Cpp

```cpp
#include <bits/stdc++.h>
using namespace std;
/*
Time Complexity: O(2N), where N is the size of the given array.
Each element has two possibilities (include or exclude), resulting in 2N combinations.

Space Complexity: O(N)
The recursion stack space will take O(N). Note that if you consider the space used to return the output that the space complexity can go up to O(2N).
*/
class Solution {
private: 
    // Helper function to calculate subset sums
    void func(int ind, int sum, vector<int> &nums, vector<int> &ans) {

        if(ind == nums.size()) {
 
            ans.push_back(sum);
            return;
        }

        func(ind + 1, sum + nums[ind], nums, ans); 

        func(ind + 1, sum, nums, ans); 
    }

public:

    vector<int> subsetSums(vector<int>& nums) {
        vector<int> ans; 
 
        func(0, 0, nums, ans);
        return ans;
    }
};

int main() {

    vector<int> nums = {1, 2, 3};
    

    Solution sol;

    vector<int> result = sol.subsetSums(nums);
    

    cout << "Subset sums are: ";
    for (int sum : result) {
        cout << sum << " ";
    }
    cout << endl;

    return 0;
}

```

## Q3 power set with duplicates 


Given an integer array nums, which can have duplicate entries, provide the power set.



Duplicate subsets cannot exist in the solution set. Return the answer in any sequence.

---
Example 1

Input : nums = [1, 2, 2]

Output : [ [ ] , [1] , [1, 2] , [1, 2, 2] , [2] , [2, 2] ]

Example 2

Input : nums = [1, 2]

Output : [ [ ], [1] , [2] , [1, 2] ]

```cpp
class Solution {
    void solve(vector<int>& arr,int i ,vector<vector<int>>& res,vector<int>& tres){
        if(i==arr.size() ){
          res.push_back(tres);
            return;
        }
     
        tres.push_back(arr[i]);
        solve(arr,i+1,res,tres);
        tres.pop_back();
        int j=i+1;
        for(;j<arr.size() && arr[j]==arr[i];j++){

        }
        solve(arr,j,res,tres);
    }
public:
    vector<vector<int> > subsetsWithDup(vector<int>& nums) {
        vector<vector<int>>res;
        vector<int> tres;
        sort(nums.begin(),nums.end());
        solve(nums,0,res,tres);
        return res;
    }
};
```
![alt text](<004 30-4-2022 n queen_231229_115513.jpg>)
![alt text](<004 30-4-2022 n queen_231229_115513(1).jpg>) ![alt text](<004 30-4-2022 n queen_231229_115513(2).jpg>) ![alt text](<004 30-4-2022 n queen_231229_115513(3).jpg>) ![alt text](<004 30-4-2022 n queen_231229_115513(4).jpg>) ![alt text](<004 30-4-2022 n queen_231229_115513(5).jpg>) ![alt text](<004 30-4-2022 n queen_231229_115513(6).jpg>) ![alt text](<004 30-4-2022 n queen_231229_115513(7).jpg>) ![alt text](<004 30-4-2022 n queen_231229_115513(8).jpg>) ![alt text](<004 30-4-2022 n queen_231229_115513(9).jpg>) ![alt text](<004 30-4-2022 n queen_231229_115513(10).jpg>) ![alt text](<004 30-4-2022 n queen_231229_115513(11).jpg>) ![alt text](<004 30-4-2022 n queen_231229_115513(12).jpg>) ![alt text](<004 30-4-2022 n queen_231229_115513(13).jpg>) ![alt text](<004 30-4-2022 n queen_231229_115513(14).jpg>) ![alt text](<004 30-4-2022 n queen_231229_115513(15).jpg>) ![alt text](<004 30-4-2022 n queen_231229_115513(16).jpg>) ![alt text](<004 30-4-2022 n queen_231229_115513(17).jpg>) ![alt text](<004 30-4-2022 n queen_231229_115513(18).jpg>) ![alt text](<004 30-4-2022 n queen_231229_115513(19).jpg>) ![alt text](<004 30-4-2022 n queen_231229_115513(20).jpg>) ![alt text](<004 30-4-2022 n queen_231229_115513(21).jpg>) ![alt text](<004 30-4-2022 n queen_231229_115513(22).jpg>)

```java

import java.util.*;
public class nQueens {
     public static boolean isSafeToPlaceQueen(boolean[][] boxes, int r, int c) {
        int[][] dir = { { 0, -1 }, { -1, -1 }, { -1, 0 }, { -1, 1 }, { 0, 1 }, { 1, 1 }, { 1, 0 }, { 1, -1 } };
        int n = boxes.length;
        for (int d = 0; d < dir.length; d++) {
            for (int rad = 1; rad <= n; rad++) {
                int x = r + rad * dir[d][0];
                int y = c + rad * dir[d][1];

                if (x >= 0 && y >= 0 && x < n && y < n) {
                    if (boxes[x][y])
                        return false;
                }
                else 
                   break;
            }
        }
        return true;
    }
     public static int nqueen_01(boolean[][] boxes, int tnq, int bno, List<String>temp, List<List<String>>res ) {
        if (tnq == 0) {
           res.add(new ArrayList<>(temp));
            return 1;
        }
        int count = 0, n = boxes.length;
        for (int bidx = bno; bidx < n * n; bidx++) {
            int r = bidx / n, c = bidx % n;
            if (isSafeToPlaceQueen(boxes, r, c)) {
                boxes[r][c] = true;
                StringBuilder sb=new StringBuilder();
                for(int i=0;i<n;i++){
                    if(i==c) sb.append("Q");
                    else sb.append(".");
                }
                temp.add(sb.toString());
                count += nqueen_01(boxes, tnq - 1, bidx + 1, temp,res);
                temp.remove(temp.size()-1);
                boxes[r][c] = false;
            }
        }
           return count;
       }
    public List<List<String>> solveNQueens(int n) {
        boolean[][] boxes=new boolean[n][n];
        List<List<String>>res=new ArrayList<>();
        List<String>temp=new ArrayList<>();
        nqueen_01(boxes,n,0,temp,res);
        return res;
    }
    public static void main(String[] args){
        nQueens  sol=new nQueens ();
        List<List<String>> val=sol.solveNQueens(4);
        System.out.println("total combination : "+val);
        //total combination : [[.Q.., ...Q, Q..., ..Q.], [..Q., Q..., ...Q, .Q..]]
    }
}
/*
Leetcode 51
Input: n = 4
Output: [[".Q..","...Q","Q...","..Q."],["..Q.","Q...","...Q",".Q.."]]
*/
```






 ![alt text](<004 30-4-2022 n queen_231229_115513(23).jpg>) ![alt text](<004 30-4-2022 n queen_231229_115513(24).jpg>) 

```java
import java.util.*;
public class nQueens2 {
    public static boolean isSafeToPlaceQueen(boolean[][] boxes, int r, int c) {
        int[][] dir = { { 0, -1 }, { -1, -1 }, { -1, 0 }, { -1, 1 }, { 0, 1 }, { 1, 1 }, { 1, 0 }, { 1, -1 } };
        int n = boxes.length;
        for (int d = 0; d < dir.length; d++) {
            for (int rad = 1; rad <= n; rad++) {
                int x = r + rad * dir[d][0];
                int y = c + rad * dir[d][1];

                if (x >= 0 && y >= 0 && x < n && y < n) {
                    if (boxes[x][y])
                        return false;
                }
                else 
                   break;
            }
        }
        return true;
    }
    public static int nqueen_01(boolean[][] boxes, int tnq, int bno ) {
        if (tnq == 0) {
          
            return 1;
        }
        int count = 0, n = boxes.length;
        for (int bidx = bno; bidx < n * n; bidx++) {
            int r = bidx / n, c = bidx % n;
            if (isSafeToPlaceQueen(boxes, r, c)) {
                boxes[r][c] = true;
                count += nqueen_01(boxes, tnq - 1, bidx + 1);
               
                boxes[r][c] = false;
            }
        }
           return count;
       }
    public int totalNQueens(int n) {
        boolean[][] boxes=new boolean[n][n];
        return nqueen_01(boxes,n,0);
       
    }

    public static void main(String[] args){
        nQueens2 sol=new nQueens2();
        int val=sol.totalNQueens(4);
        System.out.println("total combination : "+val);
        //total combination : 2
    }
}
```

![alt text](<004 30-4-2022 n queen_231229_115513(25).jpg>) ![alt text](<004 30-4-2022 n queen_231229_115513(26).jpg>) ![alt text](<004 30-4-2022 n queen_231229_115513(27).jpg>) ![alt text](<004 30-4-2022 n queen_231229_115513(28).jpg>) ![alt text](<004 30-4-2022 n queen_231229_115513(29).jpg>)
![alt text](<004 30-4-2022 n queen_231229_115513(30).jpg>)
