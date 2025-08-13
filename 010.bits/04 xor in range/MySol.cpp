#include <bits/stdc++.h>
using namespace std;


class Solution{	
    int xorTillN(int n){
        if(n%4==0) return n; 
        else if(n%4==1) return 1;
        else if(n%4==2) return n+1;
        else return 0;
    }
	public:
		int findRangeXOR(int l,int r){
			return xorTillN(l-1)^xorTillN(r);
		}
};

//tc-->O(1) sc-->O(1)

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