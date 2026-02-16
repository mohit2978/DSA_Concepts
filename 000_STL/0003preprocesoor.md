# #define vs typedef

This is a classic "C/C++ Fundamentals" question. The difference separates those who know syntax from those who know compilation stages.

Here is the "Senior Engineer" breakdown:

### 1. The Core Difference: Who handles it?
* **`#define` (The Preprocessor):** This is a "Copy-Paste" tool. Before the compiler even sees your code, the preprocessor runs through your file and blindly replaces every instance of `#define A B` with `B`. It doesn't know what a "type" is.
* **`typedef` (The Compiler):** This is a specific instruction to the compiler to create an alias for a type. The compiler understands scope, pointers, and type safety.

### 2. The "Pointer Trap" (Why `typedef` wins)
This is the most dangerous trap with `#define`.

```c
#define PTR_DEF int*
typedef int* PTR_TYPE;

PTR_DEF a, b;  // Preprocessor expands to: int* a, b;
PTR_TYPE c, d; // Compiler sees: int* c; int* d;
```

**The Result for `#define`:**
* `a` is `int*` (Pointer).
* `b` is `int` (Integer!). **BUG.**

**The Result for `typedef`:**
* `c` is `int*`.
* `d` is `int*`. **Correct.**

### 3. Scope and Respect
* **`#define` ignores scope.** If you `#define` something inside a function, it still exists globally (until `#undef`). It brute-forces its way through braces `{}`.
* **`typedef` respects scope.** If you `typedef` inside a function or class, that type alias is only visible inside that scope.

### Summary Table

| Feature | `typedef` | `#define` |
| :--- | :--- | :--- |
| **Processed By** | Compiler (Understand types) | Preprocessor (Blind text replacement) |
| **Pointers** | Handles `int* a, b` correctly. | Fails `int* a, b` (makes `b` an `int`). |
| **Scope** | Respects `{}` scope rules. | Global (ignores scope). |
| **Semicolon** | Requires `;` at the end. | No `;` needed. |
| **Use Case** | Aliasing complex types (struct, func ptr). | Constants (`#define MAX 100`) or Macros. |

> **Senior Tip:**
> * Use `typedef` (or `using` in C++) for types. **Always.**
> * Use `const` or `enum` for constants.
> * Use `#define` only for "Include Guards" (`#ifndef`) or conditional compilation (`#ifdef DEBUG`). Do not use it for types.
