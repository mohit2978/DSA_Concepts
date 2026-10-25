# Leetcode 410

https://leetcode.com/problems/split-array-largest-sum/description/



```java
class Solution {
    private int helper(int[] arr, int k, int n, int idx, int[][] dp) {
        if (k == 1) {
            int sum = 0;
            for (int i = idx; i < n; i++) {
                sum += arr[i];
            }
            return dp[idx][k] = sum;
        }
        if (dp[idx][k] != -1)
            return dp[idx][k];
        int currSum = 0;
        int ans = Integer.MAX_VALUE;
        for (int i = idx; i < n; i++) {
            currSum += arr[i];
      
            int rest= helper(arr, k - 1, n, i + 1, dp);
            ans = Math.min(ans, Math.max(rest, currSum));
        }
        return dp[idx][k] = ans;
    }

    public int splitArray(int[] arr, int k) {
        int n = arr.length;
        int[][] dp = new int[n + 1][k + 1];
        for (int[] d : dp) {
            Arrays.fill(d, -1);
        }

        return helper(arr, k, n, 0, dp);
    }
}
```


can be done by binary serach too as a min max problem


```cpp
class Solution {
    bool booksallocatedTomStudents(vector<int> &arr, int m, long long k) {
        int student = 1;
        int i = 0;
        long long sum = 0;
        while (i < arr.size()) {
            sum += arr[i];
            if (sum > k) {
                student++;
                sum = arr[i];
            }
            i++;
        }
        return student <= m;
    }

   public:
    int largestSubarraySumMinimized(vector<int> &arr, int m) {
        long long si = *max_element(arr.begin(), arr.end());
        long long ei = accumulate(arr.begin(), arr.end(), 0);
        if (m == 1) return ei;
        if (m > arr.size()) return -1;  // edge case
        while (si <= ei) {
            long long mid = (si + ei) / 2;
            if (booksallocatedTomStudents(arr, m, mid)) {
                ei = mid - 1;
            } else
                si = mid + 1;
        }
        return si;
    }
};
```

