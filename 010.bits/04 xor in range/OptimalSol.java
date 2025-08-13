import java.util.*;

class Solution {
  
    private int XORtillN(int n) {
        if(n % 4 == 1) return 1;
        if(n % 4 == 2) return n + 1;
        if(n % 4 == 3) return 0;
        return n;
    }
    
    /* Function to find the XOR 
    of numbers from L to R */
    public int findRangeXOR(int l, int r) {
        return XORtillN(l - 1) ^ XORtillN(r);
    }
    
    public static void main(String[] args) {
        int l = 3, r = 5;

        Solution sol = new Solution(); 

        int ans = sol.findRangeXOR(l, r);
        
        System.out.println("The XOR of numbers from " + l + " to " + r + " is: " + ans);
    }
}
