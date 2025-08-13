# Notes

## combination approach

![alt text](Scanned_20250814-0439.jpg)

![alt text](Scanned_20250814-0443.jpg)

```cpp
class Solution {
long long nCr(int n, int r) {
    if (r < 0 || r > n) return 0;
    if (r == 0 || r == n) return 1;
     r = min(r, n - r); 
    long long res = 1; // nC0
    for (int i = 1; i <= r; i++) {
        res = res * (n - i + 1) / i; // property: nCi = nC(i-1) * (n - i + 1) / i
    }
    return res;
}
public:
    int uniquePaths(int m, int n) {
        return (int)nCr(m+n-2,m-1);
    }
};

```


























