
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int longestConsecutive(vector<int>& a) {
        int n = a.size();
     
        if (n == 0) return 0;
        int longest = 1; 
        unordered_set<int> st;
        for (int i = 0; i < n; i++) {
            st.insert(a[i]);
        }
        for (auto it : st) {

            if (st.find(it - 1) == st.end()) {
   
                int cnt = 1; 
                int x = it; 
                while (st.find(x + 1) != st.end()) {
                    x = x + 1; 
                    cnt = cnt + 1; 
                }
                longest = max(longest, cnt);
            }
        }
        return longest;
    }
};

int main() {
    vector<int> a = {100, 4, 200, 1, 3, 2}; 

    // Create an instance of solution class
    Solution solution; 
    // Function call for finding longest consecutive sequence
    int ans = solution.longestConsecutive(a); 
    cout << "The longest consecutive sequence is " << ans << "\n";
    return 0;
}
/*
here tc-->O(n)
brute-->O(n^2)
Sort and then see optimal so tc -->O(nlgn)
*/