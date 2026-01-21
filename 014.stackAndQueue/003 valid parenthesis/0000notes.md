# Notes

![alt text](<003class 3 valid parenthesis and ques_231121_163402.jpg>)

## Way-1

```cpp
class Solution {
public:
    bool isValid(string str) {
       unordered_map<char,int>mp={{'(',-1},{')',1},{'{',-2},{'}',2},{'[',-3},{']',3}};
       stack<char> stk;
       for (char ch:str){
            if(mp[ch]<0) stk.push(ch);
            else{
                if(stk.size()==0) return false;
                char top=stk.top();
                stk.pop();
                if(mp[top]+mp[ch]!=0) return false;
            }
       }
       return stk.size()==0;
    }
};
```

![alt text](<003class 3 valid parenthesis and ques_231121_163402(1).jpg>)

```cpp

// 20
bool isValid(string str)
{
    if (str.length() == 0)
        return true;
    int n = str.length();
    if (str[0] == ')' || str[0] == ']' || str[0] == '}')
        return false;
    if (str[n - 1] == '(' || str[n - 1] == '[' || str[n - 1] == '{')
        return false;

    stack<char> st;
    for (int i = 0; i < n; i++)
    {
        char ch = str[i];
        if (ch == '(' || ch == '[' || ch == '{')
            st.push(ch);
        else
        {
            if (st.size() == 0) // more no of closing brackets
                return false;
            else if (ch == ')' && st.top() != '(')
                return false;
            else if (ch == ']' && st.top() != '[')
                return false;
            else if (ch == '}' && st.top() != '{')
                return false;
            else
                st.pop();
        }
    }

    return st.size() == 0; // st.size() != 0; // means No of Opening Brackets
}
```

 ![alt text](<003class 3 valid parenthesis and ques_231121_163402(2).jpg>)
  ![alt text](<003class 3 valid parenthesis and ques_231121_163402(3).jpg>)
   ![alt text](<003class 3 valid parenthesis and ques_231121_163402(4).jpg>) 
   ![alt text](<003class 3 valid parenthesis and ques_231121_163402(5).jpg>) 
   ```cpp

bool validateStackSequences(vector<int> &pushed, vector<int> &popped)
{
    stack<int> st;
    int i = 0, n = popped.size();
    for (int ele : pushed)
    {
        st.push(ele);
        while (st.size() != 0 && st.top() == popped[i])
        {
            st.pop();
            i++;
        }
    }

    return i != n; // st.size() == 0;
}

   ```
   ![alt text](<003class 3 valid parenthesis and ques_231121_163402(6).jpg>) 
   ![alt text](<003class 3 valid parenthesis and ques_231121_163402(7).jpg>)


![alt text](<003class 3 valid parenthesis and ques_231121_163402(8).jpg>)
 ![alt text](<003class 3 valid parenthesis and ques_231121_163402(9).jpg>) 
 
 ```cpp
// 1249
string minRemoveToMakeValid(string s)
{
    vector<int> st;
    int n = s.length();
    for (int i = 0; i < n; i++)
    {
        char ch = s[i];
        if (ch == '(')
            st.push_back(i);
        else if (ch == ')')
        {
            if (st.size() != 0 && s[st.back()] == '(')
                st.pop_back();
            else
                st.push_back(i);
        }
    }

    string ans = "";
    int idx = 0;
    for (int i = 0; i < n; i++)
    {
        if (idx < st.size() && st[idx] == i)
        {
            idx++;
            continue;
        }

        ans.push_back(s[i]);
    }

    return ans;
}
 ```
 
 ![alt text](<003class 3 valid parenthesis and ques_231121_163402(10).jpg>) ![alt text](<003class 3 valid parenthesis and ques_231121_163402(11).jpg>) ![alt text](<003class 3 valid parenthesis and ques_231121_163402(12).jpg>) ![alt text](<003class 3 valid parenthesis and ques_231121_163402(13).jpg>) ![alt text](<003class 3 valid parenthesis and ques_231121_163402(14).jpg>) ![alt text](<003class 3 valid parenthesis and ques_231121_163402(15).jpg>)







