# Leetcode 91 Decode ways

https://leetcode.com/problems/decode-ways/description/

### Problem Description
You have intercepted a secret message encoded as a string of numbers. The message is decoded via the following mapping:
* `"1"` -> `'A'`
* `"2"` -> `'B'`
* ...
* `"25"` -> `'Y'`
* `"26"` -> `'Z'`

However, while decoding the message, you realize that there are many different ways you can decode the message because some codes are contained in other codes (`"2"` and `"5"` vs `"25"`).

Given a string `s` containing only digits, return the **number of ways** to **decode** it. If the entire string cannot be decoded in any valid way, return `0`.

The test cases are generated so that the answer fits in a **32-bit** integer.

---

### Examples

**Example 1:**
* **Input:** `s = "12"`
* **Output:** `2`
* **Explanation:** `"12"` could be decoded as `"AB"` (1 2) or `"L"` (12).

**Example 2:**
* **Input:** `s = "226"`
* **Output:** `3`
* **Explanation:** `"226"` could be decoded as `"BZ"` (2 26), `"VF"` (22 6), or `"BBF"` (2 2 6).

**Example 3:**
* **Input:** `s = "06"`
* **Output:** `0`
* **Explanation:** `"06"` cannot be mapped to `"F"` because of the leading zero (`"6"` is different from `"06"`). In this case, the string is not a valid code, so return `0`.

---

### Constraints
* `1 <= s.length <= 100`
* `s` contains only digits and may contain leading zero(s).

---

### Recursion

```java
class Solution {
    public int solveDecoding(String s,int idx){
        if(idx==s.length()) return 1;
        char c=s.charAt(idx);
        int n1=c-'0';
         int a1=0,a2=0;
        if(n1>0){
            a1=solveDecoding(s,idx+1);
        }
        if(idx+1<s.length()){
               char c1=s.charAt(idx+1);
             int n2=c1-'0';
            

            int newno=n1*10+n2;
            if(newno>=10&&newno<=26){
                 a2=solveDecoding(s,idx+2);
        }
        }
     
        return a1+a2;
    }
    public int numDecodings(String s) {
        //if(s.length()==1) return 1;
        return solveDecoding(s,0);
    }
}
```

## Memoization

```java
class Solution {
    public int solveDecoding(String s,int idx,int[] dp){
        if(idx==s.length()) return dp[idx]=1;
        if(dp[idx]!=-1) return dp[idx];
        char c=s.charAt(idx);
        int n1=c-'0';
         int a1=0,a2=0;
        if(n1>0){
            a1=solveDecoding(s,idx+1,dp);
        }
        if(idx+1<s.length()){
               char c1=s.charAt(idx+1);
             int n2=c1-'0';
            

            int newno=n1*10+n2;
            if(newno>=10&&newno<=26){
                 a2=solveDecoding(s,idx+2,dp);
        }
        }
     
        return dp[idx]=a1+a2;
    }
    public int numDecodings(String s) {
        int[] dp=new int[s.length()+1];
        Arrays.fill(dp,-1);
        return solveDecoding(s,0,dp);
    }
}
```
## Tabulation

```java
class Solution {
  
    public int solveDecoding(String s,int IDX,int[] dp){
      for(int idx=s.length();idx>=0;idx--){
            if(idx==s.length()) 
                { dp[idx]=1;
                  continue;
                }
            char c=s.charAt(idx);
            int n1=c-'0';
            int a1=0,a2=0;
            if(n1>0){
                a1=dp[idx+1];
            }
            if(idx+1<s.length()){
               char c1=s.charAt(idx+1);
                int n2=c1-'0';
            

                int newno=n1*10+n2;
                if(newno>=10&&newno<=26){
                    a2=dp[idx+2];
            }
        }
     
        dp[idx]=a1+a2;
      }
        
    return dp[0];

    }
    public int numDecodings(String s) {
        int[] dp=new int[s.length()+1];
        return solveDecoding(s,0,dp);
    }
}
```

# Leetcode 139 word break

https://leetcode.com/problems/word-break/description/

### Problem Description
Given a string `s` and a dictionary of strings `wordDict`, return `true` if `s` can be segmented into a space-separated sequence of one or more dictionary words.

**Note** that the same word in the dictionary may be reused multiple times in the segmentation.

---

### Examples

**Example 1:**
* **Input:** `s = "leetcode", wordDict = ["leet","code"]`
* **Output:** `true`
* **Explanation:** Return `true` because `"leetcode"` can be segmented as `"leet code"`.

**Example 2:**
* **Input:** `s = "applepenapple", wordDict = ["apple","pen"]`
* **Output:** `true`
* **Explanation:** Return `true` because `"applepenapple"` can be segmented as `"apple pen apple"`. Note that you are allowed to reuse a dictionary word.

**Example 3:**
* **Input:** `s = "catsandog", wordDict = ["cats","dog","sand","and","cat"]`
* **Output:** `false`

---

### Constraints
* `1 <= s.length <= 300`
* `1 <= wordDict.length <= 1000`
* `1 <= wordDict[i].length <= 20`
* `s` and `wordDict[i]` consist of only lowercase English letters.
* All the strings of `wordDict` are **unique**.

---

## Recursion

```java
class Solution {
    Set<String>hset;
    private boolean helper(String s,int idx){
        if(idx==0) return true;
        for(int j=idx-1;j>=0;j--){
            if(hset.contains(s.substring(j,idx))&& helper(s,j)){
                return true;
            }
        }
        return false;
    }
    public boolean wordBreak(String s, List<String> wordDict) {
        hset=new HashSet<>(wordDict);
        return helper(s,s.length());
    }
}
```

## Memoization

```java
class Solution {
    Set<String>hset;
    private boolean helper(String s,int idx,int[] dp){
        if(idx==0) return true;
        if(dp[idx]!=-1) return dp[idx]==1;
        for(int j=idx-1;j>=0;j--){
            if(hset.contains(s.substring(j,idx))&& helper(s,j,dp)){
                dp[idx]=1;
                return true;
            }
        }
        dp[idx]=0;
        return false;
    }
    public boolean wordBreak(String s, List<String> wordDict) {
        hset=new HashSet<>(wordDict);
        int[] dp=new int[s.length()+1];
        Arrays.fill(dp,-1);
        return helper(s,s.length(),dp);
    }
}
```

## Tabulation

```java
class Solution {
    Set<String> hset;

    private boolean helper(String s, int IDX, int[] dp) {

        dp[0] = 1;
        for (int idx = 0; idx <= IDX; idx++) {
            for (int j = idx - 1; j >= 0; j--) {
                if (hset.contains(s.substring(j, idx)) && dp[j] == 1) {
                    dp[idx] = 1;

                }
            }

        }
        return dp[IDX] == 1;
    }

    public boolean wordBreak(String s, List<String> wordDict) {
        hset = new HashSet<>(wordDict);
        int[] dp = new int[s.length() + 1];

        return helper(s, s.length(), dp);
    }
}
```


## Optimization

```java
int maxLen = 0;
for (String w : wordDict) maxLen = Math.max(maxLen, w.length());

for (int i = 1; i <= n; i++) {
    for (int j = i - 1; j >= Math.max(0, i - maxLen); j--) {
        if (dp[j] && hset.contains(s.substring(j, i))) {
            dp[i] = true;
            break;
        }
    }
}
```
# Leetcode 1043 Partition Array for Maximum Sum

https://leetcode.com/problems/partition-array-for-maximum-sum/description/

### Problem Description
Given an integer array `arr`, partition the array into (contiguous) subarrays of length **at most** `k`. After partitioning, each subarray has their values changed to become the maximum value of that subarray.

Return the *largest sum of the given array after partitioning*. Test cases are generated so that the answer fits in a **32-bit** integer.

---

### Examples

**Example 1:**
* **Input:** `arr = [1,15,7,9,2,5,10], k = 3`
* **Output:** `84`
* **Explanation:** `arr` becomes `[15,15,15,9,10,10,10]`.

**Example 2:**
* **Input:** `arr = [1,4,1,5,7,3,6,1,9,9,3], k = 4`
* **Output:** `83`

**Example 3:**
* **Input:** `arr = [1], k = 1`
* **Output:** `1`

---

### Constraints
* `1 <= arr.length <= 500`
* `0 <= arr[i] <= 10^9`
* `1 <= k <= arr.length`

---

## Recursion

```java
class Solution {
    int ans=Integer.MIN_VALUE;
    private int helper(int [] arr,int k,int n ,int idx,int sum){
        if(idx==n){
            ans=Math.max(ans,sum);
            return -1;
        }
        int currMax=Integer.MIN_VALUE;
        for(int i=idx;i<n&&i<idx+k;i++){
            currMax=Math.max(currMax,arr[i]);
            int tsum=sum;
            tsum+=((i-idx+1)*currMax);
            helper(arr,k,n,i+1,tsum);
        }
        return -2;
    }
    public int maxSumAfterPartitioning(int[] arr, int k) {
        int n=arr.length;
         helper(arr,k,n,0,0);
         return ans;
    }
}
```

## Memoization

```java
class Solution {
  
    private int helper(int [] arr,int k,int n ,int idx,int[] dp){
        if(idx==n){
           
            return dp[idx]=0;
        }
        if(dp[idx]!=-1) return dp[idx];
        int currMax=Integer.MIN_VALUE;
        int ans=0;
        for(int i=idx;i<n&&i<idx+k;i++){
            currMax=Math.max(currMax,arr[i]);
            int tsum=0;
            tsum+=((i-idx+1)*currMax);
            tsum+=helper(arr,k,n,i+1,dp);
            ans=Math.max(ans,tsum);
        }
        return dp[idx]=ans;
    }
    public int maxSumAfterPartitioning(int[] arr, int k) {
        int n=arr.length;
        int[] dp=new int[n+1];
        Arrays.fill(dp,-1);
        return helper(arr,k,n,0,dp);
    
    }
}
```

## Isnt is be sliding window as subarray is there??

"Subarray" only tells you the data is contiguous. The technique depends on **what the problem asks you to produce**.

## The key difference

| | Sliding window | Partition DP |
|---|---|---|
| **Picks** | one subarray (or counts/compares subarrays) | a split of the **whole** array into many subarrays |
| **Every element** | may or may not be in the answer | belongs to exactly one piece |
| **Typical ask** | "longest/shortest subarray with sum <= K", "count subarrays with at most K distinct" | "partition into pieces", "split into K groups", "ways to cut" |
| **Why it works** | adding or removing an element moves the condition in one direction, so two pointers never need to go back | choices interact (a cut here changes what's best there), so you try all options and reuse subresults |

In 1043 you aren't looking for one good subarray. You are cutting the entire array into pieces, and the best cut for the last piece depends on the best cut for everything before it. That is DP.

## Quick test to tell them apart

1. **Does the answer include every element?** If yes (a partition), think DP.
2. **Is it one subarray or a count of subarrays?** Think sliding window, prefix sums, or Kadane.
3. **Do the words "partition", "split", "cut", "divide into K" appear?** Think partition DP.
4. **Can you decide greedily by moving two pointers forward without regret?** If yes, window. If a locally good cut can hurt later, DP.

## Other "subarray" patterns, for completeness

- **Fixed or variable window:** longest substring without repeats, minimum window substring.
- **Prefix sum + hashmap:** count subarrays with sum = K (negatives allowed, so windows fail).
- **Kadane (a 1D DP):** maximum subarray sum.
- **Monotonic deque:** sliding window maximum.
- **Binary search on the answer:** Split Array Largest Sum (410) can be solved with it, as I mentioned for Form 2.

## They also combine

Look at your own earlier problem, counting partitions with each sum <= M. The DP is partition DP, but the transition `dp[i] = dp[L] + ... + dp[i-1]` was sped up with a **sliding window** over `dp`. In 1043, the inner loop `len <= k` is a small window scanning back for the last piece. So a window can live inside a DP as an optimization, but it can't replace the DP when you must cut the whole array.

 this is worth remembering: seeing "subarray" should trigger the questions above, not an automatic window.

## Tabulation

```java
class Solution {

    private int helper(int[] arr, int k, int n, int[] dp) {

     dp[n] = 0;
        for (int idx = n - 1; idx >= 0; idx--) {
            int currMax = Integer.MIN_VALUE;
            int ans = 0;
            for (int i = idx; i < n && i < idx + k; i++) {
                currMax = Math.max(currMax, arr[i]);
                int tsum = 0;
                tsum += ((i - idx + 1) * currMax);
                tsum += dp[i+1];
                ans = Math.max(ans, tsum);
            }
            dp[idx] = ans;
        }
        return dp[0];
    }

    public int maxSumAfterPartitioning(int[] arr, int k) {
        int n = arr.length;
        int[] dp = new int[n + 1];

        return helper(arr, k, n, dp);

    }
}
```

# Leetcode 132 already one palindrome partitioning -2

