import java.util.*;

class Solution {

    public int kDistinctChar(String s, int k) {
        

        int n = s.length();  
        int maxLen = 0;  

        HashMap<Character, Integer> mpp = new HashMap<>();
        
        int l = 0, r = 0;
        
        while(r < n){
            char charR = s.charAt(r);
            mpp.put(charR, mpp.getOrDefault(charR, 0) + 1);
            if(mpp.size() > k){
                char charL = s.charAt(l);
                mpp.put(charL, mpp.get(charL) - 1);
                if(mpp.get(charL) == 0){
                    mpp.remove(charL);
                }
                l++;
            }
            if(mpp.size() <= k){
                maxLen = Math.max(maxLen, r - l + 1);
            }
            
            r++;
        }
        
        // Return the maximum length
        return maxLen;
    }

    public static void main(String[] args) {
        String s = "aaabbccd";  
        int k = 2;
        
        // Create an instance of Solution class
        Solution sol = new Solution();
        
        int length = sol.kDistinctChar(s, k);
        
        // Print the result
        System.out.println("Maximum length of substring with at most " + k + " distinct characters: " + length);
    }
}
