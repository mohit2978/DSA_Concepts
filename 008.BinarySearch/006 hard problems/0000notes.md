# Q1 Median Matrix


Given a 2D array matrix that is row-wise sorted. The task is to find the median of the given matrix.

---

Example 1

Input: matrix=[ [1, 4, 9], [2, 5, 6], [3, 7, 8] ] 

Output: 5

Explanation: If we find the linear sorted array, the array becomes 1 2 3 4 5 6 7 8 9. So, median = 5

---

Example 2

Input: matrix=[ [1, 3, 8], [2, 3, 4], [1, 2, 5] ] 

Output: 3

Explanation: If we find the linear sorted array, the array becomes 1 1 2 2 3 3 4 5 8. So, median = 3

### Code


```cpp

class Solution{
    int countElementLessThanEqualTo(int val,vector<vector<int>>&mat,int n,int m){
        int cnt=0;
        for(int i=0;i<mat.size();i++){
            cnt+=(upper_bound(mat[i].begin(),mat[i].end(),val)-mat[i].begin());
        }
        return cnt;
    }
public:
    int findMedian(vector<vector<int>>&matrix) {
        int n = matrix.size();
        int m = matrix[0].size(); 
        
        int low = INT_MAX, high = INT_MIN;

        for (int i = 0; i < n; i++) {
            low = min(low, matrix[i][0]);
            high = max(high, matrix[i][m - 1]);
        }
         int req = (n * m) / 2;
            while (low <= high) {
                int mid=(low+high)/2;
                if(countElementLessThanEqualTo(mid,matrix,n,m)>req) high=mid-1;
                else low=mid+1;
          }
          return low;
    }
};
```
or 

```cpp
class Solution{
    int countElementLessThanEqualTo(int val,vector<vector<int>>&mat,int n,int m){
        int cnt=0;
        for(int i=0;i<mat.size();i++){
            cnt+=(upper_bound(mat[i].begin(),mat[i].end(),val)-mat[i].begin());
        }
        return cnt;
    }
public:
    int findMedian(vector<vector<int>>&matrix) {
        int n = matrix.size();
        int m = matrix[0].size(); 
        
        int low = INT_MAX, high = INT_MIN;

        for (int i = 0; i < n; i++) {
            low = min(low, matrix[i][0]);
            high = max(high, matrix[i][m - 1]);
        }
         int req = (n * m) / 2;
            while (low <= high) {
                int mid=(low+high)/2;
                if(countElementLessThanEqualTo (mid,matrix,n,m)>req) high=mid-1;
                else low=mid+1;
          }
          return high+1;
    }
};
```

same code just returning (high+1) as on last iteration high,low will be on same element and then 

