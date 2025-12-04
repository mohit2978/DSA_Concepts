# Minimum number of bracket reversals to make an expression balanced

>Note: Very easy just need to know formula

Given a string s consisting of only opening and closing brackets '(' and ')', find out the minimum number of reversals required to convert the string into a balanced expression.



If it is not possible to make the brackets balanced, return -1. A reversal means changing '(' to ')' or vice-versa.


Examples:
Input: s = ")(())((("

Output: 3



Explanation: One way to balance is:

"((())())". There is no balanced sequence

that can be formed in lesser reversals.

---

Input: s = "(()((()(())(("

Output: -1

Explanation: There's no way we can balance

this sequence of braces.

---

Constraints:
1 <= s.length <= 10^4

### Just see maths

$$\text{Reversals} = \frac{m+n}{2} + \frac{m \pmod 2}{2} + \frac{n \pmod 2}{2}$$

which simplifies to:

$$\text{Reversals} = \lceil \frac{m}{2} \rceil + \lceil \frac{n}{2} \rceil$$

---

$$\text{Reversals} = \left(\frac{\text{open}}{2}\right) + (\text{open} \pmod 2) + \left(\frac{\text{close}}{2}\right) + (\text{close} \pmod 2)$$

where $\text{open}$ is the number of unbalanced opening brackets, $n$, and $\text{close}$ is the number of unbalanced closing brackets, $m$)
This is a way to express the ceiling function $\lceil x/2 \rceil$ using integer division and the modulo operator, but it has a slight adjustment in standard implementations.

```cpp
class Solution {
public:
   
    int countRev(string s) {
        int n = s.length(); 
        
        /* If string is of odd length, it is not 
        possible to balance the paranthesis */
        if(n % 2) return -1;
        
        int open = 0, close = 0;
        
        for(int i=0; i < n; i++) {
            if(s[i] == '(') open++;
            else {
                if(open > 0) open--;
                else close++;
            }
        }

        int ans = (open / 2) + (open % 2) + (close / 2) + (close % 2);
        
        return ans; 
    }
};

```
Basically 

$$\text{Reversals} = \lceil \frac{m}{2} \rceil + \lceil \frac{n}{2} \rceil$$

m is no of open unbalanced brackets 

n is no of unbalanced closed brackets

now see 

$$\lceil \frac{x}{2} \rceil = \lfloor \frac{x}{2} \rfloor + (x \pmod 2)$$

## Proof by Cases (Using Positive Integers)

Case 1: When $x$ is Even ($x = 2k$)If $x$ is even, the remainder $x \pmod 2 = 0$.$$\begin{align*}
\text{LHS} &= \lceil \frac{2k}{2} \rceil = \lceil k \rceil = k \\
\text{RHS} &= \lfloor \frac{2k}{2} \rfloor + (2k \pmod 2) \\
&= \lfloor k \rfloor + 0 \\
&= k
\end{align*}$$Since $k = k$, the identity holds.

Case 2: When $x$ is Odd ($x = 2k + 1$)If $x$ is odd, the remainder $x \pmod 2 = 1$.$$\begin{align*}
\text{LHS} &= \lceil \frac{2k+1}{2} \rceil = \lceil k + \frac{1}{2} \rceil = k + 1 \\
\text{RHS} &= \lfloor \frac{2k+1}{2} \rfloor + ((2k+1) \pmod 2) \\
&= \lfloor k + \frac{1}{2} \rfloor + 1 \\
&= k + 1
\end{align*}$$Since $k + 1 = k + 1$, the identity holds.This identity is a neat trick used in integer-based algorithms to effectively perform the ceiling operation $\lceil \dots \rceil$ without relying on floating-point arithmetic.









