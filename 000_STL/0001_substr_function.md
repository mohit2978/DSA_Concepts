# Mastering C++ `std::string::substr`

In C++, the `substr` function can be tricky because it doesn't use "start and end" indices like Python or Java. Instead, it uses **"start index and length."**

**The Syntax:** `s.substr(pos, len);`

---

### 1. From Index $k$ to the End (Included)
To get everything from index $k$ all the way to the very end of the string:

```cpp
string result = s.substr(k); 
// Note: If you omit the second argument, it automatically goes to the end.
```

### 2. From Index $0$ up to $k$ (Excluded)
To get the first part of the string before index $k$:

```cpp
string result = s.substr(0, k); 
// This gives you 'k' characters starting from index 0. 
// Indices included: 0, 1, ..., k-1.
```

### Summary Table for your Notes

| Goal | Code | Indices Included |
| :--- | :--- | :--- |
| **Start to $k$ (excluded)** | `s.substr(0, k)` | $0$ to $k-1$ |
| **Start to $k$ (included)** | `s.substr(0, k + 1)` | $0$ to $k$ |
| **$k$ to End (included)** | `s.substr(k)` | $k$ to `s.size() - 1` |
| **$k$ to End (excluded)** | `s.substr(k + 1)` | $k+1$ to `s.size() - 1` |

---

### ⚠️ The Engineer's Warning: Out of Bounds
* If $k = s.size()$, `s.substr(k)` returns an empty string `""`.
* If $k > s.size()$, the program will throw `std::out_of_range` and **crash** on Codeforces. Always ensure your index is within the string bounds!

# C++ Substring: i to j Logic

| Range Type | Code Snippet | Number of Characters (Length) |
| :--- | :--- | :--- |
| **[i, j]** (Both Included) | `s.substr(i, j - i + 1)` | $j - i + 1$ |
| **[i, j)** (i Included, j Excluded) | `s.substr(i, j - i)` | $j - i$ |
| **(i, j]** (i Excluded, j Included) | `s.substr(i + 1, j - i)` | $j - i$ |
| **(i, j)** (Both Excluded) | `s.substr(i + 1, j - i - 1)` | $j - i - 1$ |

### ⚠️ Physics Tip:
The "Length" is the most important part. Always verify: 
$\text{Length} = \text{Last\_Index\_Included} - \text{First\_Index\_Included} + 1$