# Notes

![alt text](image.png)

```cpp

class Solution{
	public:
		int matrixMultiplication(vector<int>& arr){
            int n=arr.size();
            vector<vector<int>> dp(n,vector<int>(n,0));
            for(int gap=1;gap<n;gap++){
                for(int i=1,j=gap;j<n;i++,j++){
                    if(i==j) continue;
                    int mini=1e9;
                    for(int k=i;k<=j-1;k++){
                        int ans=0;
                        ans+=dp[i][k];
                        ans+=dp[k+1][j];
                        ans+=(arr[i-1]*arr[k]*arr[j]);
                        mini=min(mini,ans);
                    }
                    dp[i][j]=mini;
                }
            }
            return dp[1][n-1];
    	}
};

```

![alt text](Scanned_20250826-2338-01.jpg) 
![alt text](Scanned_20250826-2338-02.jpg)
 ![alt text](Scanned_20250826-2338-03.jpg) 
 ![alt text](Scanned_20250826-2338-04.jpg)

## Rajneesh way 


```cpp

class Solution{
	public:
		int matrixMultiplication(vector<int>& arr){
            int n=arr.size();
            vector<vector<int>> dp(n,vector<int>(n,0));
            for(int gap=1;gap<n;gap++){
                for(int i=0,j=gap;j<n;i++,j++){
                    if(i+1==j) continue;
                    int mini=1e9;
                    for(int k=i+1;k<=j-1;k++){
                        int ans=0;
                        ans+=dp[i][k];
                        ans+=dp[k][j];
                        ans+=(arr[i]*arr[k]*arr[j]);
                        mini=min(mini,ans);
                    }
                    dp[i][j]=mini;
                }
            }
            return dp[0][n-1];
    	}
};
```

seems quite logical 

`i+1==j`--> one matrix only so return 0;

`k=i+1 to <=j-1` -->  as from front we leave anelement and from last we leave an element

then next is also simple !!


![alt text](Scanned_20250827-0002.jpg)

 ![alt text](Scanned_20250827-0003.jpg)

### Dry Run: Matrix Chain Multiplication (Gap Method)

**Input Array:** `arr = {10, 20, 30, 40}`

This represents 3 matrices:
* **A:** $10 \times 20$ (between indices `0` and `1`)
* **B:** $20 \times 30$ (between indices `1` and `2`)
* **C:** $30 \times 40$ (between indices `2` and `3`)

**Initialization:** Create a 2D table `dp` filled with 0s.

---

### Step 1: Gap = 1 (Single Matrices)
* **i=0, j=1:** `i+1 == j`, so continue. `dp[0][1] = 0`.
    * *(Cost of Matrix A is 0)*
* **i=1, j=2:** `i+1 == j`, so continue. `dp[1][2] = 0`.
    * *(Cost of Matrix B is 0)*
* **i=2, j=3:** `i+1 == j`, so continue. `dp[2][3] = 0`.
    * *(Cost of Matrix C is 0)*

**Physics:** You don't pay anything if you don't multiply.

---

### Step 2: Gap = 2 (Two Matrices)

**Case 1: i=0, j=2 (Range 0 to 2 $\rightarrow$ Matrix A and B)**
* **Possible split k:** Must be between 0 and 2. Only `k=1`.
* **Formula:** `dp[0][1]` (Left Cost) + `dp[1][2]` (Right Cost) + `(arr[0] * arr[1] * arr[2])` (Merge Cost).
* **Calc:** $0 + 0 + (10 \times 20 \times 30) = 6000$.
* **Update:** `dp[0][2] = 6000`.

**Case 2: i=1, j=3 (Range 1 to 3 $\rightarrow$ Matrix B and C)**
* **Possible split k:** Only `k=2`.
* **Formula:** `dp[1][2]` + `dp[2][3]` + `(arr[1] * arr[2] * arr[3])`.
* **Calc:** $0 + 0 + (20 \times 30 \times 40) = 24000$.
* **Update:** `dp[1][3] = 24000`.

---

### Step 3: Gap = 3 (Full Chain: A, B, C)
**Range i=0, j=3.** We need the `min` of all splits `k` (where $k=1$ or $k=2$).

**Option 1: Split at k=1 (Matrix A) $\times$ (Matrices B-C)**
* **Cost:** `dp[0][1]` + `dp[1][3]` + Merge cost $(10 \times 20 \times 40)$.
* **Math:** $0 + 24000 + 8000 = \mathbf{32000}$.

**Option 2: Split at k=2 (Matrices A-B) $\times$ (Matrix C)**
* **Cost:** `dp[0][2]` + `dp[2][3]` + Merge cost $(10 \times 30 \times 40)$.
* **Math:** $6000 + 0 + 12000 = \mathbf{18000}$.

**Decision:** $18000 < 32000$.
* **Update:** `dp[0][3] = 18000`.

---

### Final Answer: 18000









