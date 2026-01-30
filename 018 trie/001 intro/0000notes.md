# The Trie: The "Digital Dictionary"

### 1. The Core Idea
- A Trie is a prefix tree where every node represents a single character.
- **Paths = Words.**
- **Common Prefixes** are shared (e.g., "APPLE" and "APPLY" share the same "APPL" path).

### 2. Time Complexity
- **Insert:** $O(L)$ where $L$ is the length of the word.
- **Search:** $O(L)$.
- **Space:** $O(AlphabetSize \cdot TotalCharacters)$. (Memory can be high, but it's very fast).

### 3. The "Physics" Rule
The time to find a word depends **only** on the length of the word, not on how many other words are in the Trie. This is why it's faster than a Hash Map for prefix-based searches.

![alt text](<001_231121_163402 (1)(1).jpg>) ![alt text](<001_231121_163402 (1)(2).jpg>) ![alt text](<001_231121_163402 (1)(3).jpg>) ![alt text](<001_231121_163402 (1)(4).jpg>) ![alt text](<001_231121_163402 (1)(5).jpg>) ![alt text](<001_231121_163402 (1)(6).jpg>) ![alt text](<001_231121_163402 (1)(7).jpg>) ![alt text](<001_231121_163402 (1)(8).jpg>) 

This version of the Trie is the Standard Object-Oriented Implementation. It is much more flexible and memory-efficient for "sparse" data (where many nodes don't have children) compared to the static array version(see it later).
### Java
```java
class Trie {
    Node root;
     class Node{
        boolean eow;
        Node[] child;
        public Node(){
            this.eow=false;
            this.child=new Node[26];
        }
    }
     
    public Trie() {
         root=new Node();
       
    }
    
    public void insert(String word) {
        Node node=root;
        for(char ch:word.toCharArray()){
            if(node.child[ch-'a']==null){
                
                node.child[ch-'a']=new Node();
            }
            node=node.child[ch-'a'];
        }
        node.eow=true;
    }
    
    public boolean search(String word) {
        Node node=root;
        for(char ch:word.toCharArray()){
            if(node.child[ch-'a']==null){
                return false;
            }
            node=node.child[ch-'a'];
        }
        return node.eow;
    }
    
    public boolean startsWith(String prefix) {
       Node node=root;
        for(char ch:prefix.toCharArray()){
            if(node.child[ch-'a']==null){
                return false;
            }
            node=node.child[ch-'a'];
        }
        return true;
    }
}

/**
 * Your Trie object will be instantiated and called as such:
 * Trie obj = new Trie();
 * obj.insert(word);
 * boolean param_2 = obj.search(word);
 * boolean param_3 = obj.startsWith(prefix);
 */
```
### Cpp


```cpp
#include <string>
#include <vector>

using namespace std;

class Trie {
private:
    struct Node {
        bool eow; // end of word
        Node* child[26];

        Node() {
            eow = false;
            for (int i = 0; i < 26; i++) {
                child[i] = nullptr;
            }
        }
    };

    Node* root;

public:
    Trie() {
        root = new Node();
    }

    // Optional: Destructor to free memory
    ~Trie() {
        clear(root);
    }

    void clear(Node* node) {
        for (int i = 0; i < 26; i++) {
            if (node->child[i]) clear(node->child[i]);
        }
        delete node;
    }

    void insert(string word) {
        Node* node = root;
        for (char ch : word) {
            int idx = ch - 'a';
            if (node->child[idx] == nullptr) {
                node->child[idx] = new Node();
            }
            node = node->child[idx];
        }
        node->eow = true;
    }

    bool search(string word) {
        Node* node = root;
        for (char ch : word) {
            int idx = ch - 'a';
            if (node->child[idx] == nullptr) {
                return false;
            }
            node = node->child[idx];
        }
        return node->eow;
    }

    bool startsWith(string prefix) {
        Node* node = root;
        for (char ch : prefix) {
            int idx = ch - 'a';
            if (node->child[idx] == nullptr) {
                return false;
            }
            node = node->child[idx];
        }
        return true;
    }
};

```
or Simple Cpp

```cpp

class Trie{
    struct Node{
        bool eow;
        vector<Node *>child;
        Node(){
            eow=false;
            child.resize(26,nullptr);
        }
    };
    Node * root;
    public:

    Trie(){
        root=new Node();
    }
    void insert(string word) {
        Node* node = root;
        for (char ch : word) {
            int idx = ch - 'a';
            if (node->child[idx] == nullptr) {
                node->child[idx] = new Node();
            }
            node = node->child[idx];
        }
        node->eow = true;  
    }

    bool search(string word) {
        Node * node=root;
        for(char ch:word){
            if(node->child[ch-'a']==nullptr) return false;
            node=node->child[ch-'a'];
        }
        return node->eow;
    }

    bool startsWith(string prefix) {
        Node* node = root;
        for (char ch : prefix) {
            int idx = ch - 'a';
            if (node->child[idx] == nullptr) {
                return false;
            }
            node = node->child[idx];
        }
        return true;
    }
};

/**
 * Your Trie object will be instantiated and called as such:
 * Trie* obj = new Trie();
 * obj->insert(word);
 * bool param_2 = obj->search(word);
 * bool param_3 = obj->startsWith(prefix);
 */

```
# Trie Navigation: The "Signpost" Physics

In your Trie implementation, the pointer logic follows a very specific sequence. A common point of confusion is whether the `node` pointer represents the letter you are currently looking at, or the junction you just arrived at.

---

### 1. The "Road Sign" Analogy
Think of the Trie as a series of **Cities** connected by **Highways**:

* **The Node is the City:** Each city is a destination representing a prefix.
* **The `child[idx]` array is the Signpost:** At the edge of the city, there are 26 signs pointing to potential next destinations.

When your code executes `if (node->child[idx] == nullptr)`:
1.  **The Check:** You are currently **inside a City** (Node). You are looking at the signpost to see if there is a road built to the next city (the next character).
2.  **The Move:** If the road exists, you **travel** to that city: `node = node->child[idx]`.
3.  **The Arrival:** Now, you are standing in the **new city**, ready to look for the next signpost.

---

### 2. The "Physics" of the Final Node
This explains why your `search` and `insert` functions correctly mark the end of a word. Let’s trace the word **"CAT"**:

* **Initial State:** Your `node` pointer is at `root` (The "Entry Gates" to the entire dictionary).
* **Loop for 'C':** You were at `root`, found the sign for 'C', and moved to `Node_C`.
* **Loop for 'A':** You were at `Node_C`, found the sign for 'A', and moved to `Node_A`.
* **Loop for 'T':** You were at `Node_A`, found the sign for 'T', and moved to **`Node_T`**.
* **Loop Ends.**

Now, your `node` pointer is standing exactly in **`Node_T`**. This is why `node->eow = true` correctly marks "CAT" as a word—you are standing in the city that represents the completed path.

---

### 3. The Golden Rule of Trie Pointers

> **The Rule:** The `node` pointer always represents the **state after** the current character has been processed.

| Character Processed | Pointer Location | Represents Prefix |
| :--- | :--- | :--- |
| (None) | `root` | `""` (Empty) |
| 'C' | `node` | `"C"` |
| 'A' | `node` | `"CA"` |
| 'T' | `node` | `"CAT"` |

### 4. Why this matters
Because you check `child[idx]` **before** moving, you ensure that you never "fall off" the tree. If a signpost points to a `nullptr`, you know immediately that the road was never built (the word doesn't exist) without having to travel there.


## The "Hidden" Trie Complexity
 here is one more "Trie Secret" regarding your code:

The Memory Leak: In your struct Node, you are using new Node(). In C++, every new needs a delete. If your Trie object is destroyed, all those nodes you created stay "alive" in the computer's memory because you don't have a Destructor.

The Teacher's way vs. The Senior way:
Teacher: "Don't worry about it for now, it's just a LeetCode problem."

Senior: "If this were a real app (like a keyboard autocomplete), your phone would run out of RAM in an hour."

How to "Clean Up the Cities" (The Destructor)
To fix this, you need a recursive function to "demolish" the cities when you're done

```cpp
~Trie() {
    clear(root);
}

void clear(Node* node) {
    for (Node* next : node->child) {
        if (next) clear(next); // If a road exists, go there and demolish it first
    }
    delete node; // Once all roads ahead are gone, delete this city
}
```

Below implementation is a solid static-array-based Trie, which is often faster in competitive programming due to better cache locality compared to object-oriented implementations.
```java

class Trie {
    static final int MAXN = 90005;
    static final int ALPHABET_SIZE = 26;
    static int sz = 0;
   int[][] t = new int[MAXN][ALPHABET_SIZE];
   int[][] dp = new int[MAXN][ALPHABET_SIZE];
    public Trie() {
        
    }
    
    public void insert(String s) {
        int v = 0;
        for (int i = 0; i < s.length(); i++) {
            int c = s.charAt(i) - 'a';
            if (t[v][c] == 0) {
                sz++;
                t[v][c] = sz;
            }
 
            if (i == s.length() - 1) {
                dp[v][c] = 1;
            }
 
            v = t[v][c];
        }
    }
    
    public boolean search(String tmp) {
         int v = 0;
        for (int i = 0; i < tmp.length(); i++) {
            int c = tmp.charAt(i) - 'a';
            if (t[v][c] == 0) {
                return false;
            }
 
            if (i == tmp.length() - 1) {
                if (dp[v][c] == 1) {
                    return true;
                }
                return false;
            }
 
            v = t[v][c];
        }
        return false;
    }
    
    public boolean startsWith(String prefix) {
            int v = 0;
        for (int i = 0; i < prefix.length(); i++) {
            int c =prefix.charAt(i) - 'a';
            if (t[v][c] == 0) {
                return false;
            }
 
            if (i == prefix.length() - 1) {
                if (dp[v][c] == 1 || t[v][c]!=0) {
                    return true;
                }
                return false;
            }
 
            v = t[v][c];
        }
        return false;
    }
}

/**
 * Your Trie object will be instantiated and called as such:
 * Trie obj = new Trie();
 * obj.insert(word);
 * boolean param_2 = obj.search(word);
 * boolean param_3 = obj.startsWith(prefix);
 */

```
### Improved

```java
class Trie {
    // Standard competitive programming constraints
    // Total characters in all words usually determines MAXN
    private static final int MAXN = 100005; 
    private static final int ALPHABET_SIZE = 26;
    
    // t[node][char] stores the index of the child node
    private int[][] t;
    // isEndOfWord[node] marks if a word ends at this node
    private boolean[] isEndOfWord;
    private int sz;

    public Trie() {
        t = new int[MAXN][ALPHABET_SIZE];
        isEndOfWord = new boolean[MAXN];
        sz = 0; // Reset sz for every new instance
    }
    
    public void insert(String s) {
        int v = 0;
        for (char ch : s.toCharArray()) {
            int c = ch - 'a';
            if (t[v][c] == 0) {
                t[v][c] = ++sz; // Increment sz and assign to new node
            }
            v = t[v][c];
        }
        isEndOfWord[v] = true;
    }
    
    public boolean search(String word) {
        int v = 0;
        for (char ch : word.toCharArray()) {
            int c = ch - 'a';
            if (t[v][c] == 0) return false;
            v = t[v][c];
        }
        return isEndOfWord[v];
    }
    
    public boolean startsWith(String prefix) {
        int v = 0;
        for (char ch : prefix.toCharArray()) {
            int c = ch - 'a';
            if (t[v][c] == 0) return false;
            v = t[v][c];
        }
        // If we reached here, the path exists, so the prefix exists
        return true;
    }
}

```
In competitive programming (like LeetCode), there is usually an additional unspoken constraint: the **Sum of Lengths ($\sum |L|$)** of all words is typically capped around $10^5$ or $5 \times 10^5$ to prevent memory overflow.

### 1. Why $4 \times 10^8$ is Impossible
If you tried to set `MAXN = 400,000,000`:
* `int t[MAXN][26]` would require $400,000,000 \times 26 \times 4 \text{ bytes}$.
* This calculation equals **41.6 Gigabytes** of RAM.
* Most platforms limit you to **256 Megabytes**. Therefore, a static array of that size will cause a "Memory Limit Exceeded" (MLE) or a "Compilation Error."

### 2. Why `90005` or `100005` Works
The reason the code passes with a `MAXN` of only $\approx 10^5$ is that the test cases are designed to fit within standard memory limits.

* **Prefix Sharing:** Many words share the same beginning. For example, "International" and "Internet" share the first 5 characters (`I-n-t-e-r`), so they only use 5 nodes for that prefix instead of 10.

* **Test Case Limits:** Even if the *call limit* is high, the actual test data provided by the judge usually totals around 50,000 to 100,000 nodes to stay within the 256MB boundary.

### 3. How to handle this safely in C++
If you are worried about guessing `MAXN` incorrectly, the safest way to implement a Trie in C++ is the **Pointer-based approach**. It allocates memory dynamically only when a character actually appears, removing the need for a `MAXN` constant entirely.

#### C++ Safe Pointer Insert
```cpp
// This version doesn't need MAXN at all.
// It only consumes memory for the characters actually inserted.
void insert(string word) {
    Node* v = root;
    for (char ch : word) {
        int c = ch - 'a';
        if (!v->child[c]) {
            v->child[c] = new Node(); // Only creates what is needed
        }
        v = v->child[c];
    }
    v->eow = true;
}
```
#### Cpp

```cpp
#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Trie {
private:
    // MAXN should be the total number of characters across all words + 1
    static const int MAXN = 100005; 
    static const int ALPHABET_SIZE = 26;

    // t[node][char] stores the ID of the child node
    // Using a vector of arrays to keep it on the heap
    vector<vector<int>> t;
    // isEndOfWord[node] is true if a word ends at this node
    vector<bool> isEndOfWord;
    int sz;

public:
    Trie() {
        // Initialize with root node (index 0)
        t.assign(MAXN, vector<int>(ALPHABET_SIZE, 0));
        isEndOfWord.assign(MAXN, false);
        sz = 0; 
    }
    
    void insert(string s) {
        int v = 0;
        for (char ch : s) {
            int c = ch - 'a';
            if (t[v][c] == 0) {
                t[v][c] = ++sz; // Assign next available node ID
            }
            v = t[v][c];
        }
        isEndOfWord[v] = true;
    }
    
    bool search(string word) {
        int v = 0;
        for (char ch : word) {
            int c = ch - 'a';
            if (t[v][c] == 0) return false;
            v = t[v][c];
        }
        return isEndOfWord[v];
    }
    
    bool startsWith(string prefix) {
        int v = 0;
        for (char ch : prefix) {
            int c = ch - 'a';
            if (t[v][c] == 0) return false;
            v = t[v][c];
        }
        return true; // The path exists, so the prefix exists
    }
};

```

### Pro-Tip for Competitive Programming
- If you are using this in a competitive programming contest (like LeetCode), the memory limit is usually generous but the time limit is tight.

- Static Array (your previous version) is usually faster because it allocates all memory at once and avoids the overhead of many small new calls.

- Pointer-based (this version) is safer and more realistic for real-world software development.

![alt text](<001_231121_163402 (1)(9).jpg>)
 ![alt text](<001_231121_163402 (1)(10).jpg>)
  ![alt text](<001_231121_163402 (1)(11).jpg>)
   ![alt text](<001_231121_163402 (1)(12).jpg>) 
   ![alt text](<001_231121_163402 (1)(13).jpg>)
    ![alt text](<001_231121_163402 (1)(14).jpg>)
     ![alt text](<001_231121_163402 (1)(15).jpg>)

![alt text](<001_231121_163402 (1)(16).jpg>) 


![alt text](<001_231121_163402 (1)(17).jpg>)

```java
class MapSum {
     Node root;
  
     class Node{
       
        Node[] child;
        int value;
        public Node(){
            this.child=new Node[26];
            this.value=0;
        }
    }

    public MapSum() {
        root=new Node();
    }
    
    public void insert(String key, int val) {
        Node node=root;
        for(char ch:key.toCharArray()){
            if(node.child[ch-'a']==null){
                
                node.child[ch-'a']=new Node();
            }
           
            node=node.child[ch-'a'];
            
        }
        node.value=val;
     
    }
     int sum;
    private void travel(Node node){
        sum+=node.value;
        for(int i=0;i<26;i++){
            if(node.child[i]!=null){
                  //sum+=node.child[i].value;
                 travel(node.child[i]);
            }
           }
         }
    
    public int sum(String prefix) {
       Node node=root;
        for(char ch:prefix.toCharArray()){
            if(node.child[ch-'a']==null){
                return 0;
            }
            node=node.child[ch-'a'];
        }
        sum=0;
         travel(node);
        return sum;
    }
}

/**
 * Your MapSum object will be instantiated and called as such:
 * MapSum obj = new MapSum();
 * obj.insert(key,val);
 * int param_2 = obj.sum(prefix);
 */

```

 ![alt text](<001_231121_163402 (1)(18).jpg>) ![alt text](<001_231121_163402 (1)(19).jpg>) ![alt text](<001_231121_163402 (1)(20).jpg>) ![alt text](<001_231121_163402 (1)(21).jpg>) ![alt text](<001_231121_163402 (1)(22).jpg>) ![alt text](<001_231121_163402 (1)(23).jpg>) ![alt text](<001_231121_163402 (1)(24).jpg>) ![alt text](<001_231121_163402 (1)(25).jpg>) ![alt text](<001_231121_163402 (1)(26).jpg>) ![alt text](<001_231121_163402 (1)(27).jpg>) ![alt text](<001_231121_163402 (1)(28).jpg>) ![alt text](<001_231121_163402 (1)(29).jpg>) ![alt text](<001_231121_163402 (1)(30).jpg>) ![alt text](<001_231121_163402 (1)(31).jpg>) ![alt text](<001_231121_163402 (1)(32).jpg>) ![alt text](<001_231121_163402 (1)(33).jpg>) ![alt text](<001_231121_163402 (1)(34).jpg>) ![alt text](<001_231121_163402 (1)(35).jpg>) ![alt text](<001_231121_163402 (1)(36).jpg>) ![alt text](<001_231121_163402 (1)(37).jpg>) ![alt text](<001_231121_163402 (1)(38).jpg>) ![alt text](<001_231121_163402 (1)(39).jpg>) ![alt text](<001_231121_163402 (1)(40).jpg>) ![alt text](<001_231121_163402 (1)(41).jpg>) ![alt text](<001_231121_163402 (1)(42).jpg>)

![alt text](<001_231121_163402 (1)(43).jpg>) ![alt text](<001_231121_163402 (1)(44).jpg>) ![alt text](<001_231121_163402 (1)(45).jpg>) ![alt text](<001_231121_163402 (1)(46).jpg>) ![alt text](<001_231121_163402 (1)(47).jpg>) ![alt text](<001_231121_163402 (1)(48).jpg>) ![alt text](<001_231121_163402 (1)(49).jpg>) ![alt text](<001_231121_163402 (1)(50).jpg>) 

```java

class Solution {
    class Trie {
    Node root;
     class Node{
        Node[] child;
         String word;
        public Node(){
            this.child=new Node[26];
            this.word=null;
        }
    }
     
    public Trie() {
         root=new Node();
       
    }
    
    public void insert(String word) {
        Node node=root;
        for(char ch:word.toCharArray()){
            if(node.child[ch-'a']==null){
                
                node.child[ch-'a']=new Node();
            }
            node=node.child[ch-'a'];
        }
        node.word=word;
    }
        public void dfs(char[][] board,int i,int j,int[][] dir,List<String>res,Node node){
            
            char ch=board[i][j];
            if(ch=='*'|| node.child[ch-'a']==null) return;
            node=node.child[ch-'a'];
            if(node.word!=null){
                res.add(node.word);
                node.word=null;
            }
        
             board[i][j]='*';        
            for(int d=0;d<4;d++){
                 int newi=i+dir[d][0];
                 int newj=j+dir[d][1];
                 if(newi>=0 && newi<board.length && newj>=0 && newj<board[0].length){
                        dfs(board,newi,newj,dir,res,node);
                      }
                }
            board[i][j]=ch;
                  
            }
    

}
    public List<String> findWords(char[][] board, String[] words) {

        Trie t=new Trie();
        for(String str:words){
            t.insert(str);
        }
        
        List<String>res=new ArrayList<>();
        int[][] dir={{-1,0},{1,0},{0,1},{0,-1}};
        for(int i=0;i<board.length;i++){
            for(int j=0;j<board[0].length;j++){
                        t.dfs(board,i,j,dir,res,t.root);
                }
            }
        

        return res;
     }
}
```


![alt text](<001_231121_163402 (1)(51).jpg>) ![alt text](<001_231121_163402 (1)(52).jpg>) ![alt text](<001_231121_163402 (1)(53).jpg>) ![alt text](<001_231121_163402 (1)(54).jpg>) ![alt text](<001_231121_163402 (1)(55).jpg>) ![alt text](<001_231121_163402 (1)(56).jpg>) ![alt text](<001_231121_163402 (1)(57).jpg>) 

















