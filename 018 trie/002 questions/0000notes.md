# Notes
![alt text](002_231121_163402.jpg)

![alt text](002_231121_163402(1).jpg) ![alt text](002_231121_163402(2).jpg) ![alt text](002_231121_163402(3).jpg) ![alt text](002_231121_163402(4).jpg) 

See better solution first see wrong one 

```cpp

class Trie {
    struct Node{
        bool eow;
        int cnt;
        vector<Node *>child;
        Node(){
            eow=false;
            cnt=0;
            child.resize(26,nullptr);
        }
    };
    Node * root;
	public:
	    Trie() {
	        root=new Node();
	    }

	    void insert(string word) {
	    Node* node = root;
        for (char ch : word) {
            int idx = ch - 'a';
            (node->cnt)++;
            if (node->child[idx] == nullptr) {
                node->child[idx] = new Node();
            }
            node = node->child[idx];
        }
        node->eow = true;  
        (node->cnt)++;
    	}

	    int countWordsEqualTo(string word) {
	          Node* node = root;
        for (char ch : word) {
            int idx = ch - 'a';
            if (node->child[idx] == nullptr) {
                return 0;
            }
            node = node->child[idx];
        }
        return (node->eow==false)?0:(node->cnt);
    	}

	    int countWordsStartingWith(string word) {
	           Node* node = root;
        for (char ch : word) {
            int idx = ch - 'a';
            if (node->child[idx] == nullptr) {
                return 0;
            }
            node = node->child[idx];
        }
        return node->cnt;
    	}

	    void erase(string word) {
	    Node* node = root;
        for (char ch : word) {
            int idx = ch - 'a';
            (node->cnt)--;
            node = node->child[idx];
        }
        (node->cnt)--;
        if(node->cnt==0) node->eow = false; 
        
	    }
};

/**
 * Your Trie object will be instantiated and called as such:
 * Trie* obj = new Trie();
 * obj->insert(word);
 * int param_2 = obj->countWordsEqualTo(word);
 * int param_3 = obj->countWordsStartingWith(prefix);
 * obj->erase(word);
 */
```
### Why Single `cnt` Fails

If you use one `cnt` variable, you lose the ability to differentiate between a **full word** and a **prefix**.

#### Example Scenario:
1. `insert("bus")`
2. `insert("business")`

**At the node 's' (in "bus"):**
* `cnt` will be **2** (1 for the word "bus", 1 for the prefix of "business").
* `eow` will be **true**.

**The Conflict:**
* `countWordsEqualTo("bus")` should return **1**.
* Your code returns `node->cnt`, which is **2**.

---

### The Fix: `countEnd` vs `countPrefix`

To make the Trie robust, use two variables:
1. **`countEnd` (or `ew`)**: Incremented **only** at the final node of an `insert`.
2. **`countPrefix` (or `cp`)**: Incremented at **every** node along the path.

#### Corrected Logic for `countWordsEqualTo`:
```cpp
int countWordsEqualTo(string word) {
    Node* node = root;
    for (char ch : word) {
        int idx = ch - 'a';
        if (node->child[idx] == nullptr) return 0;
        node = node->child[idx];
    }
    // Return the specific counter for word endings
    return node->countEnd; 
}
```
### Correct perfect code

```cpp
class Trie {
    struct Node {
        int countEnd;    // Number of words ending at this node
        int countPrefix; // Number of words passing through this node
        vector<Node*> child;

        Node() {
            countEnd = 0;
            countPrefix = 0;
            child.resize(26, nullptr);
        }
    };

    Node* root;

public:
    Trie() {
        root = new Node();
    }

    void insert(string word) {
        Node* node = root;
        for (char ch : word) {
            int idx = ch - 'a';
            if (node->child[idx] == nullptr) {
                node->child[idx] = new Node();
            }
            node = node->child[idx];
            node->countPrefix++; // One more word uses this path
        }
        node->countEnd++; // One more word ends here
    }

    int countWordsEqualTo(string word) {
        Node* node = root;
        for (char ch : word) {
            int idx = ch - 'a';
            if (node->child[idx] == nullptr) return 0;
            node = node->child[idx];
        }
        return node->countEnd;
    }

    int countWordsStartingWith(string prefix) {
        Node* node = root;
        for (char ch : prefix) {
            int idx = ch - 'a';
            if (node->child[idx] == nullptr) return 0;
            node = node->child[idx];
        }
        return node->countPrefix;
    }

    void erase(string word) {
        // Safety check: only erase if word exists
        if (countWordsEqualTo(word) == 0) return;

        Node* node = root;
        for (char ch : word) {
            int idx = ch - 'a';
            node = node->child[idx];
            node->countPrefix--; 
        }
        node->countEnd--;
    }
};

```

![alt text](002_231121_163402(5).jpg) ![alt text](002_231121_163402(6).jpg) ![alt text](002_231121_163402(7).jpg) ![alt text](002_231121_163402(8).jpg) ![alt text](002_231121_163402(9).jpg) ![alt text](002_231121_163402(10).jpg) ![alt text](002_231121_163402(11).jpg) ![alt text](002_231121_163402(12).jpg) ![alt text](002_231121_163402(13).jpg) ![alt text](002_231121_163402(14).jpg) ![alt text](002_231121_163402(15).jpg) ![alt text](002_231121_163402(16).jpg) ![alt text](002_231121_163402(17).jpg) ![alt text](002_231121_163402(18).jpg) ![alt text](002_231121_163402(19).jpg) ![alt text](002_231121_163402(20).jpg) ![alt text](002_231121_163402(21).jpg) ![alt text](002_231121_163402(22).jpg) ![alt text](002_231121_163402(23).jpg) ![alt text](002_231121_163402(24).jpg) ![alt text](002_231121_163402(25).jpg) ![alt text](002_231121_163402(26).jpg)

![alt text](002_231121_163402(27).jpg) ![alt text](002_231121_163402(28).jpg) ![alt text](002_231121_163402(29).jpg) ![alt text](002_231121_163402(30).jpg) ![alt text](002_231121_163402(31).jpg) ![alt text](002_231121_163402(32).jpg) ![alt text](002_231121_163402(33).jpg) ![alt text](002_231121_163402(34).jpg) ![alt text](002_231121_163402(35).jpg) ![alt text](002_231121_163402(36).jpg) ![alt text](002_231121_163402(37).jpg) ![alt text](002_231121_163402(38).jpg) ![alt text](002_231121_163402(39).jpg) ![alt text](002_231121_163402(40).jpg) ![alt text](002_231121_163402(41).jpg) ![alt text](002_231121_163402(42).jpg) ![alt text](002_231121_163402(43).jpg)







