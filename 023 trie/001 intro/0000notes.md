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

 ![alt text](<001_231121_163402 (1)(18).jpg>) ![alt text](<001_231121_163402 (1)(19).jpg>) ![alt text](<001_231121_163402 (1)(20).jpg>) ![alt text](<001_231121_163402 (1)(21).jpg>) ![alt text](<001_231121_163402 (1)(22).jpg>) ![alt text](<001_231121_163402 (1)(23).jpg>) ![alt text](<001_231121_163402 (1)(24).jpg>) ![alt text](<001_231121_163402 (1)(25).jpg>) ![alt text](<001_231121_163402 (1)(26).jpg>) 
 
 ## way-1
 
 ```java

class Solution {
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
    private StringBuilder res=new StringBuilder();
    private void traverse(StringBuilder wsf,Node node) {
        if(wsf.length()>res.length()){
            res=new StringBuilder(wsf);
        }
        //StringBuilder sb=new StringBuilder(wsf);
        Node tmp=node;
        for(int i=0;i<26;i++){
            if(node.child[i]!=null && node.child[i].eow==true){
                char ch=(char)(i+'a');
                traverse(wsf.append(ch),node.child[i]);
                wsf.deleteCharAt(wsf.length()-1);
            }
        }
       
    }
    public String traverse(){
        StringBuilder wsf=new StringBuilder();
        traverse(wsf,root);
        return res.toString();
    }
    

}
    public String longestWord(String[] words) {
        Trie t=new Trie();
        for(int i=0;i<words.length;i++){
            t.insert(words[i]);
        }
        return t.traverse();
    }
}

 ```
 
 ## way-2

 ```cpp
 
class Trie {
private:
    // Dynamic 2D vector: trie[nodeID][char 0-25] = nextNodeID
    vector<vector<int>> trie;
    
    // Counts how many words PASS through this node (Prefix Count)
    vector<int> passCnt;
    
    // Counts how many words END exactly at this node
    vector<int> endCnt;
    string res;
public:
    Trie() {
        res="";
        createNode();
    }

    // Helper to add a new empty node and return its ID
    void createNode() {
        trie.push_back(vector<int>(26, -1)); // -1 means null
        passCnt.push_back(0);
        endCnt.push_back(0);
    }
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
    void traverse(string wsf,int row){
            if(wsf.size()>res.size()){
                res=wsf;
            }
            for(int i=0;i<26;i++){
                if(trie[row][i]!=-1 && endCnt[trie[row][i]]>0){
                    wsf.push_back(i+'a');
                    traverse(wsf,trie[row][i]);
                    wsf.pop_back();
                }
            }
    }
    

    string tr(){
        traverse("",0);
        return res;
    }

 
};

class Solution {
public:
    string completeString(vector<string>& nums) {
        Trie t;
        for(string s:nums){
            t.insert(s);
        }
        return t.tr();
    }
};
```

AI way

```cpp
class Solution {
    class Trie {
    private:
        vector<vector<int>> trie;
        vector<int> endCnt; // Tracks valid words
        string res;

    public:
        Trie() {
            res = "";
            createNode();
        }

        void createNode() {
            trie.push_back(vector<int>(26, -1));
            endCnt.push_back(0);
        }

        void insert(string word) {
            int node = 0;
            for (char c : word) {
                int idx = c - 'a';
                if (trie[node][idx] == -1) {
                    trie[node][idx] = trie.size();
                    createNode();
                }
                node = trie[node][idx];
            }
            endCnt[node]++;
        }

        void traverse(string &wsf, int row) {
            // Check for longest length
            if (wsf.size() > res.size()) {
                res = wsf;
            }

            for (int i = 0; i < 26; i++) {
                int nextNode = trie[row][i];
                // CRITICAL: Next node must exist AND be a word itself
                if (nextNode != -1 && endCnt[nextNode] > 0) {
                    wsf.push_back(i + 'a');
                    traverse(wsf, nextNode);
                    wsf.pop_back();
                }
            }
        }

        string getLongestPrefixString() {
            string temp = "";
            traverse(temp, 0);
            return res;
        }
    };

public:
    string completeString(vector<string>& nums) {
        Trie t;
        for (string s : nums) {
            t.insert(s);
        }
        
        string ans = t.getLongestPrefixString();
        
        // Some problems ask to return "None" if empty. 
        // Logic checks usually require returning "" if nothing found.
        if (ans == "") return "None"; 
        return ans;
    }
};
```
In this approach we insert a word suppose at row[3] now endCnt[4] will be updated!!

 ### Why your logic works for "Lexicographically Smallest"

You might wonder: "If there is a tie (e.g., 'apple' and 'apply' are both length 5), how does the algorithm ensure it picks the smallest one?"

* **The Alpha-Order Loop:** Your loop runs from `i = 0` to `25` (mapping from 'a' to 'z').
* **Depth-First Exploration:** Because it is a DFS, the algorithm will fully explore every possible valid path starting with 'a', then 'b', and so on.
* **The Tie-Breaker:** * If the DFS finds "apple" first, `res` becomes "apple".
    * Later, when it finds "apply", your condition `wsf.size() > res.size()` checks the lengths.
    * Since 5 is **not** greater than 5, `res` is **not** updated.
    
**Result:** The lexicographically smaller word found earlier is preserved. This logic is perfect and avoids the need for a secondary string comparison like `wsf < res`.
 
 ![alt text](<001_231121_163402 (1)(27).jpg>) ![alt text](<001_231121_163402 (1)(28).jpg>) ![alt text](<001_231121_163402 (1)(29).jpg>) ![alt text](<001_231121_163402 (1)(30).jpg>) ![alt text](<001_231121_163402 (1)(31).jpg>) ![alt text](<001_231121_163402 (1)(32).jpg>) ![alt text](<001_231121_163402 (1)(33).jpg>) ![alt text](<001_231121_163402 (1)(34).jpg>) ![alt text](<001_231121_163402 (1)(35).jpg>) ![alt text](<001_231121_163402 (1)(36).jpg>) ![alt text](<001_231121_163402 (1)(37).jpg>) ![alt text](<001_231121_163402 (1)(38).jpg>) ![alt text](<001_231121_163402 (1)(39).jpg>) ![alt text](<001_231121_163402 (1)(40).jpg>) ![alt text](<001_231121_163402 (1)(41).jpg>) ![alt text](<001_231121_163402 (1)(42).jpg>)

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

















