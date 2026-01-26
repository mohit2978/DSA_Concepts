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

![alt text](<004asteroid collection largest area others_231121_163402(7).jpg>) ![alt text](<004asteroid collection largest area others_231121_163402(8).jpg>) ![alt text](<004asteroid collection largest area others_231121_163402(9).jpg>) ![alt text](<004asteroid collection largest area others_231121_163402(10).jpg>) ![alt text](<004asteroid collection largest area others_231121_163402(11).jpg>) ![alt text](<004asteroid collection largest area others_231121_163402(12).jpg>)


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










