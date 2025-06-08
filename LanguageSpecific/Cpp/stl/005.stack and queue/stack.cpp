#include<bits/stdc++.h>
using namespace std;

int main() {
    stack<int> st;

    // Push elements into stack
    st.push(10);
    st.push(20);
    st.push(30);

    // Display and pop elements from stack
    cout << "Stack elements (Top to Bottom):" << endl;
    while (!st.empty()) {
        cout << st.top() << " ";  // View the top element
        st.pop();                 // Remove the top element
    }
    cout << endl;

    return 0;
}
