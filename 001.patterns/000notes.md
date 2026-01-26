# Patterns

## Pattern 1

n=5
```
    A
   ABA
  ABCBA
 ABCDCBA
ABCDEDCBA
```
### Mycode
```cpp
class Solution {
public:
    void pattern17(int n) {
        int space=n-1;
        int lim=1;
        for(int i=1;i<=n;i++){
            for(int j=1;j<=space;j++) cout<<" ";
            char ch='A';
            for(int j=1;j<=lim;j++){
                cout<<ch;
               if(j!=lim) ch++;
            }
            if(ch!='A') ch--;
            int k=1;
            while(ch!='A'){
                cout<<ch;
                ch--;
                k++;
            }
            if(k<lim) cout<<ch;
            cout<<endl;
            space--;
            lim++;
        }
    }  
};

```
The "Bug" in your current logic

Your current code handles $n=1, 2, 3$ okay, but it's more complex than it needs to be. The main issue is the while(ch != 'A') condition. It stops the moment ch becomes 'A', which forces you to manually print it afterward.

### Ai code

```cpp
class Solution {
public:
    void pattern17(int n) {
        int space = n - 1;
        
        for (int i = 1; i <= n; i++) {
            // 1. Spaces
            for (int j = 1; j <= space; j++) cout << " ";
            
            // 2. Increasing loop (A -> Peak)
            char ch = 'A';
            for (int j = 1; j <= i; j++) {
                cout << ch++;
            }
            
            // 3. Decreasing loop (Peak-1 -> A)
            // After the loop above, ch is one step ahead of the peak, 
            // so we subtract 2 to start the descent.
            ch -= 2; 
            for (int j = 1; j < i; j++) {
                cout << ch--;
            }
            
            cout << endl;
            space--;
        }
    }
};
```
## Pattern 2

n=5
```
1        1
12      21
123    321
1234  4321
1234554321
```

```cpp
class Solution {
public:
    void pattern12(int n) {
        int space=2*n-2;
        int lim=1;
        for(int i=0;i<n;i++){

            for(int j=1;j<=lim;j++){
                cout<<j;
            }
            for(int j=1;j<=space;j++){
                cout<<" ";
            }
            for(int j=lim;j>=1;j--){
                cout<<j;
            }
            cout<<"\n";
            lim++;
            space-=2;
        }
    }
};

```


