# Notes
## Prime Till N

![img_1.png](img_1.png)

### Brute 

For each number check isprime or not

```cpp
#include <bits/stdc++.h>
using namespace std;

class Solution {
private:
    bool isPrime(int n) {
        int count = 0;
      
        for(int i = 1; i <= sqrt(n); ++i) {
            if(n % i == 0) {

                count = count + 1;
                if(n / i != i) {
                    count = count + 1;
                }
            }
        }

        if(count == 2) return true;

        return false;
    }
    
public:
    vector<int> primeTillN(int n){
        vector<int> primes;
        for (int i = 2; i <= n; i++) {
            if (isPrime(i)){
                primes.push_back(i);
            }
        }
        return primes;
    }
};

int main() {
    int n = 7;
    
    /* Creating an instance of 
    Solution class */
    Solution sol; 
    
    // Function call to get all primes till N
    vector<int> ans = sol.primeTillN(n);
    
    cout << "All primes till N are: " << endl;
    for(int i=0; i < ans.size(); i++) {
        cout << ans[i] << " ";
    }
    
    return 0;
}

```
### Optimal

```cpp
class Solution {
public:
    vector<int> primeTillN(int n) {
        vector<bool> isPrime(n+1, true); 
        vector<int> ans;
        for(long long i=2; i <= n; i++) {
            if(isPrime[i]) {
                ans.push_back(i);
                for(long long val = i*i; val <= n; val += i) {
                    isPrime[val] = false;
                }
            }
        }  
        return ans;
    }
};

```



![img.png](img.png)

```cpp
//https://www.spoj.com/problems/TDPRIMES/
#include<bits/stdc++.h>
using namespace std;
int size=(int)1e8;
bool seive[(int)1e8];
void fio()
{
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    #ifndef ONLINE_JUDGE
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
    #endif
}
void seiveSol(){
   memset(seive,true,size);
    seive[0]=seive[1]=false;
    for(int i=2;i*i<=size;i++){
        if(seive[i]==true){
            for(int j=i*i;j<size;j+=i){
                seive[j]=false;
            }
        }
    }
    vector<int>prime;
    int cnt=1;
    for(int i=2;i<size;i++){
        if(seive[i]==true) {
            if(cnt%100==1){
                cout<<i<<endl;
            }
            cnt++;
        }
    }
}

int main(int argc, char const *argv[]) {
    fio();
    seiveSol();
    return 0;
}


```








