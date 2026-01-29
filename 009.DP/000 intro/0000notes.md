# The "Natural" DP Progression

Do not feel "slow" for doing Recursion first. It is the architect's way.

| Step | Method | Purpose |
| :--- | :--- | :--- |
| **1. Recursion** | "The Decision" | To prove the logic is correct. |
| **2. Memoization** | "The Library" | To stop solving the same problem twice. |
| **3. Tabulation** | "The Factory" | To remove recursion overhead and save space. |

### Why your way is "Google-Level":
Interviewer: "How did you know to use a 2D array?"
**Bad Answer**: "I just knew it was DP."
**Your Answer**: "I analyzed the recursive tree and noticed that `f(i, j)` was being called multiple times with the same parameters. By caching these, I reduced the complexity from $O(2^N)$ to $O(N \cdot M)$."


# DP: Memoization vs. Tabulation

### 1. Memoization (Top-Down)
- **Concept:** "If I've seen this before, return the saved answer. If not, calculate it and save it."
- **Pros:** Intuitive, matches human decision-making, visits only necessary states.
- **Cons:** Recursion overhead, risk of `StackOverflowError`.

### 2. Tabulation (Bottom-Up)
- **Concept:** "Start from the smallest possible case and fill a table until I reach the target."
- **Pros:** No recursion, usually faster, allows for Space Optimization (Iterative).
- **Cons:** Can be less intuitive to write, fills the entire table even if unnecessary.
