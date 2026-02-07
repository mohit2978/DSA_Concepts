# Q1 Problem Statement: Ninja's Training

Link--> https://takeuforward.org/plus/dsa/problems/ninja's-training?category=dynamic-programming&subcategory=2d-dp

### 1. Description
A Ninja is planning an **N-day** training schedule. On each day, the Ninja can perform any one of **three activities**:
1. **Running** (Activity 0)
2. **Fighting Practice** (Activity 1)
3. **Learning New Moves** (Activity 2)

Each activity has a specific number of **merit points** associated with it for each day. However, there is a constraint:
> **The Ninja cannot perform the same activity on two consecutive days.**

**Goal:** Your task is to find the **maximum total merit points** the Ninja can attain over the N days.

---

### 2. Input Format
- A 2D array `points` of size `N x 3`.
- `points[i][j]` represents the merit points for the $j^{th}$ activity on the $i^{th}$ day.

---

### 3. Example
**Input:**
`points = [[10, 40, 70], [20, 50, 80], [30, 60, 90]]`

**Output:** `210`

**Explanation:**
- **Day 0:** Ninja chooses Activity 2 (Merit = 70)
- **Day 1:** Ninja chooses Activity 1 (Merit = 50) — *Cannot choose Activity 2 again.*
- **Day 2:** Ninja chooses Activity 2 (Merit = 90) — *Cannot choose Activity 1 again.*
- **Total:** 70 + 50 + 90 = 210.

---

## Mysolution 

```cpp

class Solution {
public:
    int ninjaTraining(vector<vector<int>>& mat) {
        int n=mat.size();
        vector<vector<int>>dp(n,vector<int>(3,0));
        for(int i=0;i<3;i++) dp[0][i]=mat[0][i];

        for(int i=1;i<n;i++){
            dp[i][0]=mat[i][0]+max(dp[i-1][1],dp[i-1][2]);
            dp[i][1]=mat[i][1]+max(dp[i-1][0],dp[i-1][2]);
            dp[i][2]=mat[i][2]+max(dp[i-1][1],dp[i-1][0]);
        }
        return max({dp[n-1][0],dp[n-1][1],dp[n-1][2]});
    }
};
```

![alt text](<003matrix dp_260207_165630_0.png>) 
![alt text](<003matrix dp_260207_165630_1.png>)