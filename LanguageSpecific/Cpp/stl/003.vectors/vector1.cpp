#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {

	vector<int>v;
	int n;
	cin>>n;
	for(int i=0;i<n;i++){
	    int val;
	    cin>>val;
	    v.push_back(val);
	}
	
	for(int i=0;i<v.size();i++){
	    cout<<v[i]<<" ";
	}

     /*
     input: 
     5
     12
     11
     14
     7
     0
     output:12 11 14 7 0 
     */

    for(int x:v)
        cout<<x<<" ";

     // Declaring Iterator
    vector<int> :: iterator itr;
    
    for(itr = v.begin(); itr!=v.end(); itr++)
          cout<<*itr<<" ";
    
    cout<<endl;
    
    // Traversing again using new iterator
    // using auto keyword
    for(auto itr2 = v.begin(); itr2!=v.end(); itr2++)
        cout<<*itr2<<" ";  


     int arr[] = {10, 5, 20};
    int n = sizeof(arr)/sizeof(arr[0]);
    
    vector<int> v(arr, arr+n);
    
    // Traversing vector using new iterator
    // using auto keyword
    for(auto itr = v.begin(); itr!=v.end(); 
                                       itr++)
        cout<<*itr<<" ";     
    return 0;
}
