# Notes
![alt text](<004asteroid collection largest area others_231121_163402.jpg>)
![alt text](<004asteroid collection largest area others_231121_163402(1).jpg>) ![alt text](<004asteroid collection largest area others_231121_163402(2).jpg>) ![alt text](<004asteroid collection largest area others_231121_163402(3).jpg>) ![alt text](<004asteroid collection largest area others_231121_163402(4).jpg>) ![alt text](<004asteroid collection largest area others_231121_163402(5).jpg>) ![alt text](<004asteroid collection largest area others_231121_163402(6).jpg>)

```cpp
vector<int> asteroidCollision(vector<int> &arr)
{
    stack<int> st;

    int n = arr.size();
    for (int ele : arr)
    {
        if (ele > 0)
        {
            st.push(ele);
            continue;
        }

        while (st.size() != 0 && st.top() > 0 && st.top() < -ele)
            st.pop();

        if (st.size() != 0 && st.top() == -ele)
            st.pop();
        else if (st.size() == 0 || st.top() < 0)
            st.push(ele);
        else//if you do not put this else then also it works perfect
        {
        }
    }

    vector<int> ans(st.size(), 0);
    int idx = st.size() - 1;
    while (st.size() != 0)
    {
        ans[idx--] = st.top();
        st.pop();
    }

    return ans;
}
```

![alt text](<004asteroid collection largest area others_231121_163402(7).jpg>) 
![alt text](<004asteroid collection largest area others_231121_163402(8).jpg>) 

```java
class Solution {
  public int[] nextsmallertor(int[] heights) {
    int[] res = new int[heights.length];
    Stack<Integer> stk = new Stack<>();
    stk.push(0);
    // to right so move left to right
    for (int i = 1; i < heights.length; i++) {
      while (stk.size() > 0 && heights[stk.peek()] > heights[i]) {
        res[stk.peek()] = i;
        stk.pop();
      }
      stk.push(i);
    }
    while (stk.size() > 0) {
      res[stk.peek()] = heights.length;
      stk.pop();
    }
    return res;
  }

  public int[] nextsmallertol(int[] heights) {
    int[] res = new int[heights.length];
    Stack<Integer> stk = new Stack<>();
    stk.push(heights.length - 1);
    // to left so move right to left
    for (int i = heights.length - 1; i >= 0; i--) {
      while (stk.size() > 0 && heights[stk.peek()] > heights[i]) {
        res[stk.peek()] = i;
        stk.pop();
      }
      stk.push(i);
    }
    while (stk.size() > 0) {
      res[stk.peek()] = -1;
      stk.pop();
    }
    return res;
  }

  public int largestRectangleArea(int[] heights) {
    int[] res1 = nextsmallertor(heights);
    int[] res2 = nextsmallertol(heights);
    int mxarea = 0;
    for (int i = 0; i < heights.length; i++) {
      int area = 0;
      int width = res1[i] - res2[i] - 1;
      area = width * heights[i];
      if (area > mxarea) mxarea = area;
    }

    return mxarea;
  }
}

```
### The Algorithm Breakdown

Here's how this logic applies to your specific implementation:

* **`nextsmallertor` ($O(N)$):** Traverses the array from left to right. Each height is pushed once and popped at most once.
* **`nextsmallertol` ($O(N)$):** Traverses the array from right to left. Again, each height is pushed once and popped at most once.
* **Calculating Max Area ($O(N)$):** A final `for` loop iterates through the results to calculate the area for each bar and find the maximum.

$O(N) + O(N) + O(N) = O(3N)$, which is **$O(N)$**. Space Complexity is also **$O(N)$** due to the size of the stack and result arrays.

Now we need only 1 traversal So we compute nextSmallerToRight(nse(next smaller element)) on fly!!



```cpp
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int largestRectangleArea(vector<int> &heights) {
        int n = heights.size();
        stack<int> st;
        int largestArea = 0;
        int area;
        int nse, pse;
        
        for(int i = 0; i < n; i++) {
            while(!st.empty() && heights[st.top()] >= heights[i]){
                int ind = st.top(); 
                st.pop();
                pse = st.empty() ? -1 : st.top();//we do not pop this as we need ared of this too
                nse = i;
                area = heights[ind] * (nse - pse - 1);
                largestArea = max(largestArea, area);
            }
            st.push(i);
        }
        
        while(!st.empty()) {
            nse = n;
            int ind = st.top(); 
            st.pop();
            pse = st.empty() ? -1 : st.top();
            area = heights[ind] * (nse - pse - 1);
            largestArea = max(largestArea, area);
        }
        
        return largestArea;
    }
};

int main() {
    vector<int> heights = {2, 1, 5, 6, 2, 3};
    Solution sol; 
    int ans = sol.largestRectangleArea(heights);
    cout << "The largest rectangle area is: " << ans << endl;
    return 0;
}
```

Q--> explain this nse is next smaller to right and pse is next smller to left  but ofr which element?

```cpp
     for(int i = 0; i < n; i++) {
            while(!st.empty() && heights[st.top()] >= heights[i]){
                int ind = st.top(); 
                st.pop();
                pse = st.empty() ? -1 : st.top();
                nse = i;
                area = heights[ind] * (nse - pse - 1);
                largestArea = max(largestArea, area);
            }
            st.push(i);
        } 
```

Ans-->
### The Crime Scene: Who Gets the Math?

This is the exact right question to ask. If you don't know *who* the math is being applied to, the formula is just blind memorization.

The `nse` and `pse` are being calculated strictly for the element that was **just popped from the stack** (`ind`). 

Think of the inner `while` loop as a crime scene. Here are the three actors involved:

#### 1. The Victim: `ind` (The Popped Element)
```cpp
int ind = st.top(); 
st.pop();
```
This is the bar whose final area we are calculating right now. It was sitting happily on top of the stack, thinking it could expand to the right forever, until...

#### 2. The Attacker: i (The Next Smaller Element to the Right - NSE)

```cpp
while(!st.empty() && heights[st.top()] >= heights[i])
// ...
nse = i;

```
The while loop only triggers because heights[i] is shorter than our victim (heights[ind]). This means i is the right-side wall. Our victim cannot expand past index i. Therefore, i is the Next Smaller Element (NSE) for our popped bar.

#### 3. The Foundation: st.top() (The Previous Smaller Element - PSE

Once the victim (`ind`) is popped, we look at who was sitting underneath it on the stack. Because we only push items onto the stack in increasing order, the item directly underneath our victim is mathematically guaranteed to be the closest bar to the left that is shorter than the victim. This makes the new `st.top()` the Previous Smaller Element (PSE) for our popped bar.

*(Note: If the stack is completely empty after popping the victim, it means nothing to the left was shorter than it, so its left wall is all the way at index -1).*

---

### A 5-Second Visual Example

Imagine `heights = [1, 5, 6, 2]`

* We push index 0 (height 1) onto the stack.
* We push index 1 (height 5) onto the stack.
* We push index 2 (height 6) onto the stack.

**Stack from bottom to top:** `[0, 1, 2]`

Now `i = 3` (height 2).

* **The Collision:** Height 2 is shorter than Height 6. The `while` loop triggers!
* **The Victim (`ind`):** We pop index 2 (Height 6).
* **The NSE (`nse`):** Who killed it? Index 3 (Height 2). So `nse = 3`.
* **The PSE (`pse`):** Who is left under it on the stack? Index 1 (Height 5). So `pse = 1`.

**The Math for the Victim (Height 6):**
* **Width:** `nse - pse - 1` -> 3 - 1 - 1 = 1
* **Area:** 6 * 1 = 6

The loop repeats because Height 2 is also shorter than Height 5 (the next item on the stack). Height 5 becomes the new victim, and the exact same process calculates its area!

---

### The Senior Engineer Reality

You aren't calculating the area for the bar you are currently looking at (`i`). You are using `i` as a wall to calculate the final, locked-in area of the bars from the past (the stack).



![alt text](<004asteroid collection largest area others_231121_163402(9).jpg>) ![alt text](<004asteroid collection largest area others_231121_163402(10).jpg>) ![alt text](<004asteroid collection largest area others_231121_163402(11).jpg>) ![alt text](<004asteroid collection largest area others_231121_163402(12).jpg>)


```java
class Solution {
    public int[] nextsmallertor(int [] heights){
        int[] res=new int[heights.length];
        Stack<Integer>stk=new Stack<>();
        stk.push(0);
        //to right so move left to right
        for(int i=1;i<heights.length;i++){
            while(stk.size()>0&&heights[stk.peek()]>heights[i]){
                res[stk.peek()]=i;
                stk.pop();
            }
            stk.push(i);
            
        }
        while(stk.size()>0){
              res[stk.peek()]=heights.length;
              stk.pop();
          }
        return res;
    }
    public int[] nextsmallertol(int [] heights){
        int[] res=new int[heights.length];
        Stack<Integer>stk=new Stack<>();
        stk.push(heights.length-1);
        //to left so move right to left
        for(int i=heights.length-1;i>=0;i--){
            while(stk.size()>0&&heights[stk.peek()]>heights[i]){
                res[stk.peek()]=i;
                stk.pop();
            }
            stk.push(i);
            
        }
          while(stk.size()>0){
              res[stk.peek()]=-1;
              stk.pop();
          }
        return res;
    }
    public int largestRectangleArea(int[] heights) {
        int[] res1=nextsmallertor(heights);
        int[] res2=nextsmallertol(heights);
        int mxarea=0;
        for(int i=0;i<heights.length;i++){
            int area=0;
            int width=res1[i]-res2[i]-1;
            area=width*heights[i];
            if(area>mxarea)
                mxarea=area;
        }
        
      return mxarea;  
    }
    public int maximalRectangle(char[][] matrix) {
        int m=matrix.length;
        int n=matrix[0].length;
        int []arr=new int[n];
        int res=-(int)1e7;
        for(int i=0;i<m;i++){
            for(int j=0;j<n;j++){
                if(matrix[i][j]=='1') arr[j]=arr[j]+1;
                else arr[j]=0;
            }
            res=Math.max(res,largestRectangleArea(arr));
        }
        return res;
    }
}

```

 ![alt text](<004asteroid collection largest area others_231121_163402(13).jpg>)








 ![alt text](<004asteroid collection largest area others_231121_163402(14).jpg>) ![alt text](<004asteroid collection largest area others_231121_163402(15).jpg>) ![alt text](<004asteroid collection largest area others_231121_163402(16).jpg>) ![alt text](<004asteroid collection largest area others_231121_163402(17).jpg>) ![alt text](<004asteroid collection largest area others_231121_163402(18).jpg>) ![alt text](<004asteroid collection largest area others_231121_163402(19).jpg>) ![alt text](<004asteroid collection largest area others_231121_163402(20).jpg>) ![alt text](<004asteroid collection largest area others_231121_163402(21).jpg>) ![alt text](<004asteroid collection largest area others_231121_163402(22).jpg>) ![alt text](<004asteroid collection largest area others_231121_163402(23).jpg>) ![alt text](<004asteroid collection largest area others_231121_163402(24).jpg>) ![alt text](<004asteroid collection largest area others_231121_163402(25).jpg>) ![alt text](<004asteroid collection largest area others_231121_163402(26).jpg>) ![alt text](<004asteroid collection largest area others_231121_163402(27).jpg>) ![alt text](<004asteroid collection largest area others_231121_163402(28).jpg>) ![alt text](<004asteroid collection largest area others_231121_163402(29).jpg>) ![alt text](<004asteroid collection largest area others_231121_163402(30).jpg>)










