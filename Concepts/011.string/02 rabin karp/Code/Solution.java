import java.util.*;

class Solution {
    public List<Integer> search(String pat, String txt) {
        int n = pat.length();
        int m = txt.length();

        // Primes for Rabin-Karp algorithm
        int p = 7, mod = 101;

        // To store the hash values of pattern and substring of text
        int hashPat = 0, hashText = 0;

        int pRight = 1, pLeft = 1;

        // Computing the initial hash values
        for (int i = 0; i < n; i++) {
            hashPat = (hashPat + ((pat.charAt(i) - 'a' + 1) * pRight) % mod) % mod;
            hashText = (hashText + ((txt.charAt(i) - 'a' + 1) * pRight) % mod) % mod;
            pRight = (pRight * p) % mod;
        }

        // List to store the result
        List<Integer> ans = new ArrayList<>();

        // Traverse the text string
        for (int i = 0; i <= m - n; i++) {

            // If the hash value matches
            if (hashPat == hashText) {
              
                if (txt.substring(i, i + n).equals(pat)) ans.add(i);
            }

            if (i < m - n) {
                hashText = (hashText - ((txt.charAt(i) - 'a' + 1) * pLeft) % mod + mod) % mod;
                hashText = (hashText + ((txt.charAt(i + n) - 'a' + 1) * pRight) % mod) % mod;
                hashPat = (hashPat * p) % mod;

                // Updating the prime multiples
                pLeft = (pLeft * p) % mod;
                pRight = (pRight * p) % mod;
            }
        }

        return ans; // Return the stored result
    }
        public static void main(String[] args) {
        String txt = "ababcabcababc";
        String pat = "abc";

 
        Solution sol = new Solution();

        List<Integer> ans = sol.search(pat, txt);

        // Output
        System.out.print("The starting indices of all occurrences of " + pat + " in " + txt + " are: ");
        for (int it : ans) System.out.print(it + " ");
    }
}

/*
The starting indices of all occurrences of abc in ababcabcababc are: 2 5 10 
*/