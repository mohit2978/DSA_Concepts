# Q1 Word ladder I


## Problem Statement

Given are the two distinct words `startWord` and `targetWord`, and a list of size `N`, denoting `wordList` of unique words of equal size `M`. Find the length of the shortest transformation sequence from `startWord` to `targetWord`.

Keep the following conditions in mind:
* A word can only consist of lowercase characters.
* Only one letter can be changed in each transformation.
* Each transformed word must exist in the `wordList` including the `targetWord`.
* `startWord` may or may not be part of the `wordList`.

**Note:** If there’s no possible way to transform the sequence from `startWord` to `targetWord` return `0`.

---

## Examples

**Example 1**
> **Input:** `wordList = ["des","der","dfr","dgt","dfs"]`, `startWord = "der"`, `targetWord = "dfs"`
> **Output:** `3`
> **Explanation:** > The length of the smallest transformation sequence from "der" to "dfs" is 3
> i.e. "der" -> (replace ‘e’ by ‘f’) -> "dfr" -> (replace ‘r’ by ‘s’) -> "dfs".
> So, it takes 3 different strings for us to reach the `targetWord`. Each of these strings are present in the `wordList`.

**Example 2**
> **Input:** `wordList = ["geek", "gefk"]`, `startWord = "gedk"`, `targetWord = "geek"`
> **Output:** `2`
> **Explanation:** > The length of the smallest transformation sequence from "gedk" to "geek" is 2
> i.e. "gedk" -> (replace ‘d’ by ‘e’) -> "geek" .
> So, it takes 2 different strings for us to reach the `targetWord`. Each of these strings are present in the `wordList`.

---

## Quiz: Now your turn!

**Input:** `wordList = ["hot", "dot", "dog", "lot", "log"]`, `startWord = "hit"`, `targetWord = "cog"`

**Output:**
Pick your answer:
* [ ] 3
* [ ] 0
* [ ] 2
* [ ] 1

*(Senior Engineer Hint: Before you try to mentally build the BFS tree, look at the 3rd condition in the problem statement and look at the `targetWord` vs the `wordList`. Always check the base edge-cases first!)*

---

## Constraints

* `1 ≤ wordList.length ≤ 100`
* `1 ≤ wordList[i].length ≤ 10`
* `startWord.length == targetWord.length == wordList[i].length`
* `startWord`, `targetWord`, and `wordList[i]` consist of lowercase English letters.
* `startWord != targetWord`




## Word Ladder I — Complete Guide

### Read the Hint First

The senior engineer hint is gold:

> "Look at the 3rd condition vs the targetWord vs the wordList"

**Condition 3:** Each transformed word must exist in the `wordList` **including the targetWord**.

```
wordList = ["hot", "dot", "dog", "lot", "log"]
targetWord = "cog"

Is "cog" in wordList? ❌ NO

→ Answer is 0 immediately, no BFS needed
```

**Quiz Answer: 0**

---

### The Mental Checklist Before Writing Any Code

This is what separates senior from junior thinking:

```
Step 1: Is targetWord in wordList?      → if NO, return 0 immediately
Step 2: Is wordList empty?              → return 0
Step 3: Is startWord == targetWord?     → return 1 (already there)
Step 4: Only then → run BFS
```

Always check **base cases before algorithm**. Saves time in interviews.

---

### Why BFS? Not DFS, Not DP?

```
Problem asks for SHORTEST transformation sequence
          ↓
SHORTEST PATH in an unweighted graph
          ↓
BFS — always finds shortest path first
      DFS finds A path, not necessarily shortest
      DP doesn't apply — no overlapping subproblems
```

Think of it as a **graph problem**:
```
Each word = node
Edge between two words = differ by exactly 1 letter
Find shortest path from startWord to targetWord
```

---

### The Approach — BFS Level by Level

```
Level 1:  startWord              → distance 1
Level 2:  all words 1 change away → distance 2
Level 3:  all words 2 changes away → distance 3
...
When targetWord is dequeued → return its level
```

The trick to generate neighbours efficiently:

```cpp
// For each position, try all 26 letters
word = "der"
pos 0: 'a'er, 'b'er ... 'z'er  → check each in wordSet
pos 1: d'a'r, d'b'r ... d'z'r  → check each in wordSet
pos 2: de'a', de'b' ... de'z'  → check each in wordSet
```

This is O(M × 26) per word instead of O(N) comparisons — much faster for large wordLists.

---

### The Code

```cpp
#include <bits/stdc++.h>
using namespace std;

int wordLadderLength(string startWord, string targetWord,
                     vector<string>& wordList) {

    // Base case: targetWord must be in wordList
    unordered_set<string> wordSet(wordList.begin(), wordList.end());
    if (!wordSet.count(targetWord)) return 0;

    // BFS
    queue<pair<string, int>> q;   // {word, level}
    q.push({startWord, 1});
    wordSet.erase(startWord);     // mark visited by removing from set

    while (!q.empty()) {
        auto [word, level] = q.front();
        q.pop();

        // try changing each position
        for (int i = 0; i < word.size(); i++) {
            char original = word[i];

            for (char c = 'a'; c <= 'z'; c++) {
                if (c == original) continue;
                word[i] = c;

                if (word == targetWord) return level + 1;

                if (wordSet.count(word)) {
                    wordSet.erase(word);      // mark visited
                    q.push({word, level + 1});
                }
            }
            word[i] = original;   // restore
        }
    }
    return 0;   // no path found
}
```

---

### Dry Run — Example 1

```
startWord = "der"   targetWord = "dfs"
wordList  = ["des","der","dfr","dgt","dfs"]
```

**Base case check:** "dfs" in wordList ✅ continue.

```
Initial: wordSet = {des, der, dfr, dgt, dfs}
         erase "der" → wordSet = {des, dfr, dgt, dfs}

Queue: [("der", 1)]
```

```
Pop ("der", 1):
  pos 0 'd': try aer,ber... no matches
  pos 1 'e': try dar,dbr... "dfr" ✅ → push ("dfr", 2)
                             "des"? no, wrong pos
  pos 2 'r': try dea,deb... "des" ✅ → push ("des", 2)

wordSet = {dgt, dfs}
Queue: [("dfr",2), ("des",2)]
```

```
Pop ("dfr", 2):
  pos 0 'd': no matches
  pos 1 'f': try dar... no matches
  pos 2 'r': try dfa,dfb... "dfs" == targetWord! ✅

return 2 + 1 = 3 ✅
```

---

### Dry Run — Example 2

```
startWord = "gedk"   targetWord = "geek"
wordList  = ["geek", "gefk"]
```

**Base case:** "geek" in wordList ✅

```
Queue: [("gedk", 1)]
wordSet = {gefk}   (geek stays for target check)

Pop ("gedk", 1):
  pos 2 'd': try geak, gebk... "geek" == targetWord! ✅

return 1 + 1 = 2 ✅
```

---

### Why `wordSet.erase(word)` instead of a visited set?

```cpp
// Instead of:
unordered_set<string> visited;
visited.insert(word);

// We do:
wordSet.erase(word);
```

Same effect — once a word is visited, removing it from wordSet prevents revisiting. One less data structure, same correctness.

---

### Complexity

```
N = wordList size
M = word length

Time:  O(N × M × 26)
       ↑            ↑
   BFS visits    each word tries
   each word     M×26 neighbours
   at most once

Space: O(N) for wordSet + O(N) for queue = O(N)
```

---

### Summary

```
Key decisions made:

1. Base case check first       → return 0 if target not in list
2. BFS not DFS                 → guarantees shortest path
3. Try all 26 letters per pos  → O(M×26) neighbour generation
4. Erase from wordSet          → O(1) visited tracking
5. Return level+1 at target    → count includes startWord
```

| Check | Question to ask |
|---|---|
| Before BFS | Is targetWord in wordList? |
| Neighbour gen | Change each position to a-z |
| Visited | Erase from wordSet |
| Found target | Return current level + 1 |
| Queue empty | Return 0 — no path |



## Word Ladder BFS Tree — Visual Dry Run

### Example 1

```
startWord = "der"   targetWord = "dfs"
wordList  = ["des","der","dfr","dgt","dfs"]
```
![alt text](image.png)

![alt text](image-1.png)

![alt text](image-2.png)

![alt text](image-3.png)
---

### What the Tree is Showing You

Each level in the BFS tree = one transformation step:

```
Level 1:  der          → distance 1  (start)
Level 2:  dfr, des     → distance 2  (1 change from der)
Level 3:  dfs          → distance 3  (1 change from dfr) ← TARGET
```

The key thing to notice — `des` at level 2 is **never explored**. BFS found the target through `dfr` first, so it returns immediately with `level + 1 = 3`. This is exactly why BFS guarantees the shortest path — it explores level by level, so the **first time you reach the target is always the shortest way**.

---

### Why `des` is a Dead End (Even if We Explored It)

```
des → one change away: des→dfs? (e→f, s→s) — no, two changes
    → des→dfr? no
    → des→dgt? no
des has no path to dfs in one step → would return nothing
```

BFS naturally skips this because target was already found from `dfr`. This is the **BFS guarantee** — shortest path always found before longer paths are explored.



`set.count()` is simple — it returns either **0 or 1**.

---

### Why Only 0 or 1?

Because a `set` (and `unordered_set`) **cannot have duplicates**. So any key either:

```cpp
exists in set  →  count returns 1
doesn't exist  →  count returns 0
```

That's it. It's essentially a **yes/no lookup**.

---

### In Code

```cpp
unordered_set<string> wordSet = {"des", "dfr", "dgt", "dfs"};

wordSet.count("dfr")   // → 1  (exists)
wordSet.count("xyz")   // → 0  (doesn't exist)
wordSet.count("dfs")   // → 1  (exists)
```

---

### How It's Used in Word Ladder

```cpp
if (wordSet.count(word)) {   // count returns 1 = truthy
    wordSet.erase(word);
    q.push({word, level + 1});
}
```

This is exactly the same as writing:

```cpp
if (wordSet.find(word) != wordSet.end())  // longer way
if (wordSet.count(word) == 1)             // explicit way
if (wordSet.count(word))                  // shorthand — most common
```

All three mean the same thing. `count()` is preferred because it's the shortest and most readable.

---

### count() vs find() — When to Use Which

```cpp
// Use count() when you only need YES/NO
if (wordSet.count(word))          // ✅ clean, simple

// Use find() when you need the ITERATOR too
auto it = wordSet.find(word);
if (it != wordSet.end()) {
    // use *it directly
}
```

---

### Why Not Just Use count() on a map?

`map` and `unordered_map` also have `.count()` — same behaviour, returns 0 or 1:

```cpp
unordered_map<char, int> freq;
freq['a'] = 3;

freq.count('a')   // → 1
freq.count('z')   // → 0
```

The only container where `.count()` can return more than 1 is `multiset` or `multimap` — because those allow duplicates:

```cpp
multiset<int> ms = {1, 1, 2, 3, 3, 3};
ms.count(3)   // → 3  (three copies of 3)
ms.count(1)   // → 2
ms.count(9)   // → 0
```

---

### One-Line Summary

```
set.count(x)  =  "does x exist in the set?"
                  1 = yes,  0 = no
```


This is called **Structured Bindings** — introduced in C++17.

---

### What It Does

```cpp
auto [word, level] = q.front();
```

It **unpacks** a `pair` (or tuple/struct) into individual named variables in one line.

Without it you'd write:

```cpp
// old way — C++14 and before
pair<string, int> p = q.front();
string word  = p.first;
int    level = p.second;

// new way — C++17 structured binding
auto [word, level] = q.front();
```

Exact same result, one line instead of three.

---

### How It Maps

```cpp
queue<pair<string, int>> q;
//         ↑       ↑
//       first   second

auto [word, level] = q.front();
//    ↑       ↑
//  first   second

// word  → maps to pair.first  (the string)
// level → maps to pair.second (the int)
```

The variables are assigned **left to right** matching the order of the pair/struct members.

---

### Works on Pairs, Tuples, Structs

```cpp
// pair
pair<int, string> p = {1, "hello"};
auto [num, str] = p;
// num = 1, str = "hello"

// tuple
tuple<int, string, bool> t = {42, "world", true};
auto [a, b, c] = t;
// a=42, b="world", c=true

// struct
struct Point { int x, y; };
Point pt = {3, 7};
auto [x, y] = pt;
// x=3, y=7
```

---

### Also Works in Range-based For Loops

Very common with maps:

```cpp
unordered_map<char, int> freq = {{'a',3}, {'b',2}};

// old way
for (auto& p : freq) {
    cout << p.first << " → " << p.second;
}

// C++17 structured binding — much cleaner
for (auto& [ch, count] : freq) {
    cout << ch << " → " << count;
}
```

---

### The `&` Matters

```cpp
auto  [word, level] = q.front();   // COPY  — modifying word/level doesn't affect queue
auto& [word, level] = q.front();   // REFERENCE — modifying affects original
```

In Word Ladder we use copy because we modify `word` in place (changing each character) and don't want to corrupt the queue:

```cpp
auto [word, level] = q.front();   // copy ✅
q.pop();

for (int i = 0; i < word.size(); i++) {
    char orig = word[i];
    word[i] = 'a';                // safely modifying the COPY
    ...
    word[i] = orig;
}
```

---

### Summary

| | Old way | C++17 structured binding |
|---|---|---|
| Syntax | `p.first`, `p.second` | `auto [a, b]` |
| Readability | low — `.first/.second` meaningless | high — custom names |
| Works on | pair only with `.first/.second` | pair, tuple, struct, array |
| Requires | C++11 | C++17 |

```cpp
// One-line mental model:
auto [word, level] = q.front();
//    ↑      ↑          ↑
//  name1  name2    pair/tuple to unpack
```




# Q2 Word ladder II


## Problem Statement

Given two distinct words `startWord` and `targetWord`, and a list denoting `wordList` of unique words of equal lengths. Find all shortest transformation sequence(s) from `startWord` to `targetWord`. You can return them in any order possible.

In this problem statement, we need to keep the following conditions in mind:
* A word can only consist of lowercase characters.
* Only one letter can be changed in each transformation.
* Each transformed word must exist in the `wordList` including the `targetWord`.
* `startWord` may or may not be part of the `wordList`.
* Return an empty list if there is no such transformation sequence.

---

## Examples

**Example 1**
> **Input:** `startWord = "der"`, `targetWord = "dfs"`, `wordList = ["des", "der", "dfr", "dgt", "dfs"]`
> **Output:** `[ ["der", "dfr", "dfs"], ["der", "des", "dfs"] ]`
> **Explanation:** The length of the smallest transformation sequence here is 3.
> Following are the only two shortest ways to get to the `targetWord` from the `startWord`:
> * `"der"` -> (replace ‘r’ by ‘s’) -> `"des"` -> (replace ‘e’ by ‘f’) -> `"dfs"`.
> * `"der"` -> (replace ‘e’ by ‘f’) -> `"dfr"` -> (replace ‘r’ by ‘s’) -> `"dfs"`.

**Example 2**
> **Input:** `startWord = "gedk"`, `targetWord= "geek"`, `wordList = ["geek", "gefk"]`
> **Output:** `[ ["gedk", "geek"] ]`
> **Explanation:** The length of the smallest transformation sequence here is 2.
> Following is the only shortest way to get to the `targetWord` from the `startWord`:
> * `"gedk"` -> (replace ‘d’ by ‘e’) -> `"geek"`.

---

## Quiz: Now your turn!

**Input:** `startWord = "abc"`, `targetWord = "xyz"`, `wordList = ["abc", "ayc", "ayz", "xyz"]`

**Output:**
Pick your answer:
* [ ] `[["abc", "ayz", "ayc", "xyz"]]`
* [ ] `[["abc", "ayc", "abc", "xyz"]]`
* [ ] `[]`
* [ ] `[["abc", "ayc", "ayz", "xyz"]]`

*(Senior Engineer Hint: Remember that BFS guarantees the shortest path. Trace the valid single-character mutations sequentially without revisiting previous states to prevent cycles like 'abc' -> 'ayc' -> 'abc'.)*

---

## Constraints

* `N` = Number of Words
* `M` = Length of Word
* `1 <= N <= 100`
* `1 <= M <= 10`



## Word Ladder II — Complete Guide

### Quiz Answer First

```
startWord = "abc"   targetWord = "xyz"
wordList  = ["abc", "ayc", "ayz", "xyz"]
```

Trace every possible path:

```
abc → ayc  (b→y)  ✅ in wordList
ayc → ayz  (c→z)  ✅ in wordList
ayz → xyz  (a→x)  ✅ in wordList

Length = 4 words = shortest possible
```

✅ Answer: **`[["abc", "ayc", "ayz", "xyz"]]`**

Why not the others:
```
Option 1: "abc→ayz→ayc→xyz" — ayz→ayc goes BACKWARD, longer path ❌
Option 2: visits "abc" twice — invalid, already visited ❌
Option 3: [] — path exists so empty is wrong ❌
```

---

### Word Ladder I vs II — The Key Difference

```
Word Ladder I                    Word Ladder II
─────────────────────            ──────────────────────────────
Find LENGTH of shortest path     Find ALL shortest paths
Return one number                Return list of lists
BFS alone is enough              BFS + path tracking needed
Stop at first hit                Must explore entire level
Simple queue                     Queue stores full path so far
```

---

### Why This Is Harder

In Word Ladder I, the moment you reach `targetWord` you return. In Word Ladder II:

```
You must NOT stop at first hit
You must finish exploring the ENTIRE level where target is found
Because another path at the same level might also reach target
```

This means you need to:

```
1. BFS level by level
2. Track the full PATH not just the word
3. Never revisit a word WITHIN the same path
4. Collect ALL paths that reach target at minimum level
5. Stop after the level where first hit occurs
```

---

### The Approach — BFS with Path Tracking

```cpp
#include <bits/stdc++.h>
using namespace std;

vector<vector<string>> findLadders(string startWord, string targetWord,
                                    vector<string>& wordList) {
    unordered_set<string> wordSet(wordList.begin(), wordList.end());

    // base case
    if (!wordSet.count(targetWord)) return {};

    // queue stores FULL PATH so far (not just current word)
    queue<vector<string>> q;
    q.push({startWord});

    // words used in CURRENT level — erase from wordSet after full level
    unordered_set<string> usedThisLevel;
    usedThisLevel.insert(startWord);

    vector<vector<string>> result;
    bool found = false;

    while (!q.empty() && !found) {
        int levelSize = q.size();     // process one full level at a time

        // collect words used in this level
        // erase them AFTER level, not during (other paths in same level need them)
        unordered_set<string> usedInLevel;

        for (int i = 0; i < levelSize; i++) {
            vector<string> path = q.front();
            q.pop();
            string word = path.back();   // current word = last in path

            // try all positions and all 26 letters
            for (int j = 0; j < word.size(); j++) {
                char orig = word[j];
                for (char c = 'a'; c <= 'z'; c++) {
                    if (c == orig) continue;
                    word[j] = c;

                    if (word == targetWord) {
                        path.push_back(word);
                        result.push_back(path);
                        path.pop_back();
                        found = true;     // don't stop — finish this level
                    }
                    else if (wordSet.count(word) && !usedThisLevel.count(word)) {
                        usedInLevel.insert(word);
                        path.push_back(word);
                        q.push(path);
                        path.pop_back();
                    }
                }
                word[j] = orig;
            }
        }

        // erase all words used in this level from wordSet
        // prevents future levels from revisiting them
        for (auto& w : usedInLevel)
            wordSet.erase(w);

        usedThisLevel = usedInLevel;
    }

    return result;
}
```

---

### The Trickiest Part — When to Erase from wordSet

This is what makes Word Ladder II hard:

```
WRONG — erase immediately (like Word Ladder I):
  Path A uses "dfr" → erased → Path B can't use "dfr"
  You miss valid paths at the SAME level ❌

CORRECT — erase after entire level is done:
  Path A uses "dfr" → kept for now
  Path B also uses "dfr" → both paths recorded ✅
  After level completes → erase "dfr"
  Next level can't revisit it ✅
```

---

Now walk through the full dry run interactively:---

![alt text](image-4.png)


![alt text](image-5.png)


![alt text](image-6.png)


![alt text](image-7.png)

![alt text](image-8.png)



![alt text](image-9.png)


### The 3 Critical Differences from Word Ladder I

```
Word Ladder I                     Word Ladder II
─────────────────                 ─────────────────────────────
queue<pair<string,int>>           queue<vector<string>>
stores word + level               stores FULL PATH

erase word immediately            erase word AFTER full level
→ other paths at same level       → other paths can still use it
  can't use it

return level+1 at first hit       set found=true, finish level
→ stops immediately               → collects ALL paths at that level
```

---

### Complexity

```
N = wordList size,  M = word length

Time:  O(N × M × 26 × N)
            ↑              ↑
       BFS per word    path copying (each path up to N words long)

Space: O(N × N × M)   — queue can hold N paths each of length N
```

Word Ladder II is significantly more expensive than I because storing full paths uses much more memory. For large inputs this is why the constraints are kept small (N ≤ 100).









