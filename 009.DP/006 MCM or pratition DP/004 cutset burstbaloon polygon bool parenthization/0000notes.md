# Notes

![alt text](<012cutset burstbaloon polygon bool parenthization_231121_163402.jpg>)



![alt text](<012cutset burstbaloon polygon bool parenthization_231121_163402(1).jpg>) ![alt text](<012cutset burstbaloon polygon bool parenthization_231121_163402(2).jpg>) ![alt text](<012cutset burstbaloon polygon bool parenthization_231121_163402(3).jpg>) 

```java

public int minCut(String str) {
    int n = str.length();
    boolean[][] isPlaindrome = new boolean[n][n]; // Typo 'isPlaindrome' matches source

    // Fill Palindrome Table (Gap Strategy)
    for (int gap = 0; gap < n; gap++) {
        for (int i = 0, j = gap; j < n; i++, j++) {
            if (gap == 0)
                isPlaindrome[i][j] = true;
            else if (gap == 1)
                isPlaindrome[i][j] = str.charAt(i) == str.charAt(j);
            else
                isPlaindrome[i][j] = str.charAt(i) == str.charAt(j) && isPlaindrome[i + 1][j - 1];
        }
    }

    int[] dp = new int[n];
    Arrays.fill(dp, -1);
    
    // Call Memoization (or change to minCut_dp for Tabulation)
    return minCut_memo(str, 0, isPlaindrome, dp);
}

public int minCut_memo(String str, int si, boolean[][] isPlaindrome, int[] dp) {
    // Optimization: If the substring from 'si' to end is a palindrome, 0 cuts needed
    if (isPlaindrome[si][str.length() - 1])
        return dp[si] = 0;
    
    if (dp[si] != -1)
        return dp[si];

    int minAns = (int) 1e9;
    for (int cut = si; cut < str.length(); cut++) {
        // Only make a cut if the left part (si...cut) is a palindrome
        if (isPlaindrome[si][cut]) {
            minAns = Math.min(minAns, minCut_memo(str, cut + 1, isPlaindrome, dp) + 1);
        }
    }
    return dp[si] = minAns;
}


```


![alt text](<012cutset burstbaloon polygon bool parenthization_231121_163402(4).jpg>) ![alt text](<012cutset burstbaloon polygon bool parenthization_231121_163402(5).jpg>) ![alt text](<012cutset burstbaloon polygon bool parenthization_231121_163402(6).jpg>) ![alt text](<012cutset burstbaloon polygon bool parenthization_231121_163402(7).jpg>) 

![alt text](<012cutset burstbaloon polygon bool parenthization_231121_163402(8).jpg>) 

```java
public int minCut_dp(String str, int SI, boolean[][] isPlaindrome, int[] dp) {
    // Loop backwards because dp[si] depends on dp[cut + 1] (future index)
    for (int si = str.length() - 1; si >= 0; si--) {
        
        // Optimization: If the substring from 'si' to end is a palindrome, 0 cuts needed
        if (isPlaindrome[si][str.length() - 1]) {
            dp[si] = 0;
            continue;
        }

        int minAns = (int) 1e9;
        // Try every possible cut
        for (int cut = si; cut < str.length(); cut++) {
            if (isPlaindrome[si][cut]) {
                minAns = Math.min(minAns, dp[cut + 1] + 1);
            }
        }
        dp[si] = minAns;
    }
    return dp[SI];
}
```


![alt text](<012cutset burstbaloon polygon bool parenthization_231121_163402(9).jpg>) ![alt text](<012cutset burstbaloon polygon bool parenthization_231121_163402(10).jpg>)




![alt text](<012cutset burstbaloon polygon bool parenthization_231121_163402(11).jpg>) ![alt text](<012cutset burstbaloon polygon bool parenthization_231121_163402(12).jpg>) ![alt text](<012cutset burstbaloon polygon bool parenthization_231121_163402(13).jpg>) ![alt text](<012cutset burstbaloon polygon bool parenthization_231121_163402(14).jpg>) ![alt text](<012cutset burstbaloon polygon bool parenthization_231121_163402(15).jpg>) ![alt text](<012cutset burstbaloon polygon bool parenthization_231121_163402(16).jpg>)

### Memoization

```java

class Solution {
    public int maxCoins(int[] nums, int si, int ei, int[][] dp) {
        if (dp[si][ei] != -1)
            return dp[si][ei];

        int lval = si - 1 == -1 ? 1 : nums[si - 1];
        int rval = ei + 1 == nums.length ? 1 : nums[ei + 1];

        int maxAns = 0;
        for (int cut = si; cut <= ei; cut++) {
            int lans = (cut == si) ? 0 : maxCoins(nums, si, cut - 1, dp);
            int rans = (cut == ei) ? 0 : maxCoins(nums, cut + 1, ei, dp);

            maxAns = Math.max(maxAns, lans + lval * nums[cut] * rval + rans);
        }

        return dp[si][ei] = maxAns;

    }

    public int maxCoins(int[] nums) {
        int n = nums.length;
        int[][] dp = new int[n][n];
        for (int[] d : dp)
            Arrays.fill(d, -1);

        return maxCoins(nums, 0, n - 1, dp);
    }
}
```

### tabulation
```cpp

class Solution {
int maxCoins(vector<int>& nums,vector<vector<int>> dp) {
         for(int gap=0;gap<nums.size();gap++){
            for(int si=0,ei=gap;ei<nums.size();si++,ei++){
                int lval = si - 1 == -1 ? 1 : nums[si - 1];
                int rval = ei + 1 == nums.size()? 1 : nums[ei + 1];
                int maxAns = 0;
                for(int cut=si;cut<=ei;cut++){
                    int lans=(cut==si)?0:dp[si][cut-1];
                    int rans=(cut==ei)?0:dp[cut+1][ei];
                    maxAns=max(maxAns,lans+rans+lval*nums[cut]*rval);
                }
                dp[si][ei]=maxAns;
            }
         }
        return dp[0][nums.size()-1];
    }

  
public:
    int maxCoins(vector<int>& nums) {
        int n=nums.size();
        vector<vector<int>> dp(n,vector<int>(n,-1));
        return maxCoins(nums,dp);
    }
};
```
we put `int lans=(cut==si)?0:dp[si][cut-1];` as when cut =si then cut-1=si-1 and when si=0 cut-1 will be less than 0 so which gives segmentation faul in cpp and out of bound error in java

similarly for `cut==ei` condition

 ![alt text](<012cutset burstbaloon polygon bool parenthization_231121_163402(17).jpg>) ![alt text](<012cutset burstbaloon polygon bool parenthization_231121_163402(18).jpg>) ![alt text](<012cutset burstbaloon polygon bool parenthization_231121_163402(19).jpg>) ![alt text](<012cutset burstbaloon polygon bool parenthization_231121_163402(20).jpg>) ![alt text](<012cutset burstbaloon polygon bool parenthization_231121_163402(21).jpg>) ![alt text](<012cutset burstbaloon polygon bool parenthization_231121_163402(22).jpg>) ![alt text](<012cutset burstbaloon polygon bool parenthization_231121_163402(23).jpg>) ![alt text](<012cutset burstbaloon polygon bool parenthization_231121_163402(24).jpg>) ![alt text](<012cutset burstbaloon polygon bool parenthization_231121_163402(25).jpg>) ![alt text](<012cutset burstbaloon polygon bool parenthization_231121_163402(26).jpg>)





















