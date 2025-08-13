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