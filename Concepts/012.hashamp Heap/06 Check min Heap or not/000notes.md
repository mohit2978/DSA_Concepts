## Notes

Given an array check if it represents a min-heap or not.
Print "Yes" if it represents a min-heap. Otherwise, print "No".

```cpp
#include <bits/stdc++.h>
using namespace std;
string solve(int* arr,int n,int i){
    int lidx=2*i+1;
    int ridx=2*i+2;
    string lres="Yes";
    string rres="Yes";
    if((lidx<n && arr[i]>arr[lidx]) || (ridx<n && arr[i]>arr[ridx])) return "No"; 
    
    if(lidx<n) lres=solve(arr,n,lidx);
    if(ridx<n) rres=solve(arr,n,ridx);
    
    if(lres=="No"|| rres=="No") return "No";
    return "Yes";
    
}
int main() {
    int t;
    cin>>t;
    while(t--){
        int n;
        cin>>n;
        int arr[n];
        for(int i=0; i<n; i++)
        {
            cin>>arr[i];
        }
        cout<<solve(arr,n,0)<<"\n";
    }
}

```