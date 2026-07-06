
## Q1 **1288. Remove Covered Intervals**

**Problem Statement:**
Given an array `intervals` where `intervals[i] = [l_i, r_i]`.
Interval `[a, b)` is covered by interval `[c, d)` if and only if `c <= a` and `b <= d`.
Return the number of remaining intervals after removing all intervals that are covered by another interval in the list.

**Example 1:**

* **Input:** `intervals = [[1,4],[3,6],[2,8]]`
* **Output:** `2`
* **Explanation:** Interval `[3,6]` is covered by `[2,8]`, therefore it is removed. `[1,4]` and `[2,8]` are the remaining intervals.

**Example 2:**

* **Input:** `intervals = [[1,4],[2,3]]`
* **Output:** `1`

**Constraints:**

* `1 <= intervals.length <= 1000`
* `intervals[i].length == 2`
* `0 <= l_i < r_i <= 10^5`
* All the given intervals are **unique**.



## My sol

First i sort only on start but then [[1,2],[1,4]] will fail as [1,2] will not cover [1,4] so we need sorting by decending on base of end so now output array after sort be [[1,4],[1,2]] so [1,4] will cover [1,2]







```cpp
class Solution {
    static bool comparator(const vector<int>& a, const vector<int>& b) {
    if (a[0] != b[0])
        return a[0] < b[0];  // ascending on 1st value
    return a[1] > b[1];      // descending on 2nd value
}
public:
    int removeCoveredIntervals(vector<vector<int>>& intervals) {
        sort(intervals.begin(),intervals.end(),comparator);
        int st=intervals[0][0];
        int ed=intervals[0][1];
        int rem=0;
        int n=intervals.size();
        for(int i=1;i<n;i++){
            int a=intervals[i][0];
            int b=intervals[i][1];
            if(st<=a && b<=ed) rem++;
            else{
                st=a;
                ed=b;
            }
        }
        return n-rem;
    }
};
```