# Notes

```cpp
class Trie {
private:
    // Dynamic 2D vector: trie[nodeID][char 0-25] = nextNodeID
    vector<vector<int>> trie;
    
    // Counts how many words PASS through this node (Prefix Count)
    vector<int> passCnt;
    
    // Counts how many words END exactly at this node
    vector<int> endCnt;

public:
    Trie() {
        // Initialize Root Node (Index 0)
        createNode();
    }

    // Helper to add a new empty node and return its ID
    void createNode() {
        trie.push_back(vector<int>(26, -1)); // -1 means null
        passCnt.push_back(0);
        endCnt.push_back(0);
    }

    // 1. INSERT
    void insert(string word) {
        int node = 0;
        for (char c : word) {
            int idx = c - 'a';
            
            // If path doesn't exist, create it
            if (trie[node][idx] == -1) {
                trie[node][idx] = trie.size(); // Next ID is current size
                createNode();
            }
            
            node = trie[node][idx]; // Move to child
            passCnt[node]++;        // Increment prefix count
        }
        endCnt[node]++; // Mark word end
    }

    // 2. SEARCH (Returns true if word exists)
    bool search(string word) {
        int node = 0;
        for (char c : word) {
            int idx = c - 'a';
            
            // If path is broken, word doesn't exist
            if (trie[node][idx] == -1) return false;
            
            node = trie[node][idx];
            
            // If passCnt is 0, it means this node was "deleted"
            if (passCnt[node] == 0) return false; 
        }
        return endCnt[node] > 0;
    }

    // 3. DELETE (Decrements counts)
    // Note: Assumes the word actually exists in the Trie
    void erase(string word) {
        if (!search(word)) return; // Safety check

        int node = 0;
        for (char c : word) {
            int idx = c - 'a';
            node = trie[node][idx];
            passCnt[node]--; // Reduce count (Lazy Delete)
        }
        endCnt[node]--; // Remove "End of Word" marker
    }

    // 4. STARTS WITH (Prefix Search)
    bool startsWith(string prefix) {
        int node = 0;
        for (char c : prefix) {
            int idx = c - 'a';
            if (trie[node][idx] == -1) return false;
            node = trie[node][idx];
            if (passCnt[node] == 0) return false;
        }
        return passCnt[node] > 0;
    }
};
```
This version of the Trie is an **excellent, robust implementation**. It is significantly better than static array or fixed-pointer versions for 95% of use cases, including interviews and competitive programming.

Here is why this specific version is considered "top-tier" logic:

---

### 1. It is "Crash-Proof" (Dynamic Memory)
* **Static Array Problem:** If you pre-allocate `int trie[100000][26]`, you might run out of memory for large inputs or get a **Time Limit Exceeded (TLE)** error just by trying to reset/clear it for multiple test cases.
* **Your Code:** It starts empty. It grows exactly as much as needed. You never have to guess the size of `MAXN` or risk a segmentation fault.

---

### 2. It Handles "Lazy Deletion" Perfectly
Most Trie implementations cannot delete words easily because they have to recursively free memory and check if a branch is truly empty.
* **Your Code:** You use **`passCnt--`**. You don’t actually need to delete the node; you just mark it as "unused" (a ghost node). This makes deletion **$O(L)$** and incredibly simple to code. Future searches will see `passCnt == 0` and treat the path as if it doesn't exist.

---

### 3. It Handles Duplicates
Standard boolean Tries (`isEnd = true`) fail when duplicates are involved because they can't distinguish between having 1 copy of "apple" or 50 copies.
* **Your Code:** * `endCnt` tracks exactly how many times a specific word ends there.
    * `passCnt` tracks exactly how many words pass through that path.
    * This is essential for problems where you need to remove only *one* instance of a word.

---

### Comparison: Boolean vs. Counting Trie

| Feature | Standard (Boolean) | Your Version (Counting) |
| :--- | :--- | :--- |
| **Duplicates** | Not supported. | **Supported fully.** |
| **Deletion** | Hard/Recursive. | **Easy ($O(L)$).** |
| **Prefix Stats** | Needs a full traversal. | **Instant (via `passCnt`).** |

---

### One Professional Optimization (Pro Tip)
Currently, your `erase` function might traverse the word twice:
1.  Once inside `search(word)` to verify it exists.
2.  Once inside the logic to actually decrement the counts.

**The Fix:** You can merge this into a **Single Pass** for maximum speed. In most competitive programming scenarios, if the problem guarantees that you only erase words that were previously inserted, you can skip the "existence check" entirely and decrement counts as you walk down the tree.

---


1-pass erase 

```cpp
void erase(string word) {
        vector<int> path; // To remember the nodes we visited
        int node = 0;

        // 1. GO DOWN (Traverse & Record)
        for (char c : word) {
            int idx = c - 'a';
            // If path breaks, abort immediately. No counts changed.
            if (trie[node][idx] == -1) return; 
            
            node = trie[node][idx];
            // If node exists but is effectively deleted (ghost node)
            if (passCnt[node] == 0) return; 

            path.push_back(node);
        }

        // 2. CHECK & UPDATE (Backtrack)
        // Only proceed if the word actually exists here
        if (endCnt[node] > 0) {
            endCnt[node]--; // Remove the "End" marker
            
            // Go through the recorded nodes and decrement passCnt
            for (int n : path) {
                passCnt[n]--;
            }
        }
    }
```




















































































