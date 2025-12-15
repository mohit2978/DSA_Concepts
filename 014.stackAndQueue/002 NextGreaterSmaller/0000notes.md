# Notes
![alt text](<002Nger l Nser l range count_231121_163402.jpg>)

![alt text](<002Nger l Nser l range count_231121_163402(1).jpg>) ![alt text](<002Nger l Nser l range count_231121_163402(2).jpg>) ![alt text](<002Nger l Nser l range count_231121_163402(3).jpg>) ![alt text](<002Nger l Nser l range count_231121_163402(4).jpg>) ![alt text](<002Nger l Nser l range count_231121_163402(5).jpg>) ![alt text](<002Nger l Nser l range count_231121_163402(6).jpg>) ![alt text](<002Nger l Nser l range count_231121_163402(7).jpg>) ![alt text](<002Nger l Nser l range count_231121_163402(8).jpg>) ![alt text](<002Nger l Nser l range count_231121_163402(9).jpg>) ![alt text](<002Nger l Nser l range count_231121_163402(10).jpg>) ![alt text](<002Nger l Nser l range count_231121_163402(11).jpg>) ![alt text](<002Nger l Nser l range count_231121_163402(12).jpg>) ![alt text](<002Nger l Nser l range count_231121_163402(13).jpg>)

---

## Next greater smaller

```java
import java.util.Stack;
import java.util.ArrayDeque;

public class question {

    // N : Next, G = greater, S : Smaller, L : Left, R : Right
    public static void NGOR(int[] arr, int[] ans) {
        int n = arr.length;
        Arrays.fill(ans, n); // Java : Arrays.fill(ans,n);

        Stack<Integer> st = new Stack<>();
        for (int i = 0; i < n; i++) {
            while (st.length != 0 && arr[st.peek()] < arr[i]) {
                ans[st.pop()] = i;
            }
            st.push(i);
        }
    }

    public static void NGOL(int[] arr, int[] ans) {
        int n = arr.length;
        Arrays.fill(ans, -1); // Java : Arrays.fill(ans,-1);

        Stack<Integer> st = new Stack<>();
        for (int i = n - 1; i >= 0; i--) {
            while (st.length != 0 && arr[st.peek()] < arr[i]) {
                ans[st.pop()] = i;
            }
            st.push(i);
        }
    }

    public static void NSOR(int[] arr, int[] ans) {
        int n = arr.length;
        Arrays.fill(ans, n); // Java : Arrays.fill(ans,n);

        Stack<Integer> st = new Stack<>();
        for (int i = 0; i < n; i++) {
            while (st.length != 0 && arr[st.peek()] > arr[i]) {
                ans[st.pop()] = i;
            }
            st.push(i);
        }
    }

    public static void NSOL(int[] arr, int[] ans) {
        int n = arr.length;
        Arrays.fill(ans, -1); // Java : Arrays.fill(ans,-1);

        Stack<Integer> st = new Stack<>();
        for (int i = n - 1; i >= 0; i--) {
            while (st.length != 0 && arr[st.peek()] > arr[i]) {
                ans[st.pop()] = i;
            }
            st.push(i);
        }
    }
}   

```

## Cpp

```c++

#include <iostream>
#include <stack>
#include <vector>

using namespace std;

// N : Next, G = greater, S : Smaller, L : Left, R : Right
void NGOR(vector<int> &arr, vector<int> &ans)
{
    int n = arr.size();
    ans.resize(n, n); //Java :  Arrays.fill(ans,n);

    stack<int> st;
    for (int i = 0; i < n; i++)
    {
        while (st.size() != 0 && arr[st.top()] < arr[i])
        {
            ans[st.top()] = i;
            st.pop();
        }
        st.push(i);
    }
}

void NGOL(vector<int> &arr, vector<int> &ans)
{
    int n = arr.size();
    ans.resize(n, -1); //Java :  Arrays.fill(ans,-1);

    stack<int> st;
    for (int i = n - 1; i >= 0; i--)
    {
        while (st.size() != 0 && arr[st.top()] < arr[i])
        {
            ans[st.top()] = i;
            st.pop();
        }
        st.push(i);
    }
}

void NSOR(vector<int> &arr, vector<int> &ans)
{
    int n = arr.size();
    ans.resize(n, n); //Java :  Arrays.fill(ans,n);

    stack<int> st;
    for (int i = 0; i < n; i++)
    {
        while (st.size() != 0 && arr[st.top()] > arr[i])
        {
            ans[st.top()] = i;
            st.pop();
        }
        st.push(i);
    }
}

void NSOL(vector<int> &arr, vector<int> &ans)
{
    int n = arr.size();
    ans.resize(n, -1); //Java :  Arrays.fill(ans,-1);

    stack<int> st;
    for (int i = n - 1; i >= 0; i--)
    {
        while (st.size() != 0 && arr[st.top()] > arr[i])
        {
            ans[st.top()] = i;
            st.pop();
        }
        st.push(i);
    }
}

```