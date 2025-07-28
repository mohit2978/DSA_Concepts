#include <bits/stdc++.h>
using namespace std;
/*
Given two integers L and R. Find the XOR of the elements in the range [L , R].


Examples:
Input : L = 3 , R = 5

Output : 2

Explanation : answer = (3 ^ 4 ^ 5) = 2.

Input : L = 1, R = 3

Output : 0

Explanation : answer = (1 ^ 2 ^ 3) = 0.

Input : L = 4, R = 10

Output:
11

*/
class Solution {
public:
    int findRangeXOR(int l, int r){			

		int ans = 0;
        //before l everything will be cancelled out
        //suppose l=3 and r=5 so 1^2 will be both in l and r will cancel out
        //sp meed to xor 3^4^5
		for(int i=l; i <= r; i++) {
		    ans ^= i;
		}
		return ans;
	}
};
//tc-->O(r-l+1) sc-->O(1)
int main() {
    int l = 3, r = 5;
    
    /* Creating an instance of 
    Solution class */
    Solution sol; 
    
    /* Function call to get the
    XOR of numbers from L to R*/
    int ans = sol.findRangeXOR(l, r);
    
    cout << "The XOR of numbers from " << l << " to " << r << " is: " << ans;
    
    return 0;
}
