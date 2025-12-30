# Notes

![alt text](<001basic ques segregate 0123 conatiner most wtr_231123_170649.jpg>)
 ![alt text](<001basic ques segregate 0123 conatiner most wtr_231123_170649(1).jpg>) ![alt text](<001basic ques segregate 0123 conatiner most wtr_231123_170649(2).jpg>) ![alt text](<001basic ques segregate 0123 conatiner most wtr_231123_170649(3).jpg>) ![alt text](<001basic ques segregate 0123 conatiner most wtr_231123_170649(4).jpg>) ![alt text](<001basic ques segregate 0123 conatiner most wtr_231123_170649(5).jpg>) ![alt text](<001basic ques segregate 0123 conatiner most wtr_231123_170649(6).jpg>) ![alt text](<001basic ques segregate 0123 conatiner most wtr_231123_170649(7).jpg>) ![alt text](<001basic ques segregate 0123 conatiner most wtr_231123_170649(8).jpg>) ![alt text](<001basic ques segregate 0123 conatiner most wtr_231123_170649(9).jpg>) ![alt text](<001basic ques segregate 0123 conatiner most wtr_231123_170649(10).jpg>)


![alt text](<001basic ques segregate 0123 conatiner most wtr_231123_170649(11).jpg>) ![alt text](<001basic ques segregate 0123 conatiner most wtr_231123_170649(12).jpg>) ![alt text](<001basic ques segregate 0123 conatiner most wtr_231123_170649(13).jpg>) ![alt text](<001basic ques segregate 0123 conatiner most wtr_231123_170649(14).jpg>) ![alt text](<001basic ques segregate 0123 conatiner most wtr_231123_170649(15).jpg>) ![alt text](<001basic ques segregate 0123 conatiner most wtr_231123_170649(16).jpg>)

## Q sort array of  0 and 1

```cpp
#include <iostream>
#include <vector>
#include <algorithm> // Required for swap

// Use the entire standard namespace to avoid typing 'std::' everywhere
using namespace std;

/**
 * Sorts a 0, 1 array in O(n) time using the two-pointer approach.
 * The 'left' pointer tracks the boundary between 0s and unsorted elements.
 */
void sort_01_array_two_pointers(vector<int>& arr) {
    int n = arr.size();
    int left = 0; // Pointer for the position to place the next 0

    // 'right' pointer iterates through the entire array, examining each element
    for (int right = 0; right < n; ++right) {
        // If the current element (arr[right]) is 0, it needs to move to the left side.
        if (arr[right] == 0) {
            // Perform the swap: The 0 at arr[right] swaps with whatever is at arr[left].
            // This moves the 0 to its correct, sorted position.
            swap(arr[left], arr[right]);
            
            // Increment 'left' to point to the next expected position for a 0, 
            // thereby expanding the sorted 0-section.
            left++;
        }
        // If arr[right] is 1, it's already in the correct half (or will be pushed 
        // there by subsequent swaps), so we just continue.
    }
}

// --- Example Usage ---
int main() {
    // 1. Initialize the array with 0s and 1s
    vector<int> array = {1, 0, 1, 0, 1, 1, 0};
    
    // 2. Print the original array
    cout << "Original Array: ";
    for (int x : array) {
        cout << x << " ";
    }
    cout << endl;

    // 3. Call the sorting function
    sort_01_array_two_pointers(array);

    // 4. Print the sorted array
    cout << "Sorted Array:   ";
    for (int x : array) {
        cout << x << " ";
    }
    cout << endl;

    return 0;
}
```


## Q sort array 0,1,2

```cpp
class Solution {
public:
    void sortZeroOneTwo(vector<int>& nums) {
        int n=nums.size();
        int i=0,j=0;
        int k=n-1;
        while(i<=k){
            if(nums[i]==0){
                swap(nums[i],nums[j]);
                i++;
                j++;
            }else if(nums[i]==1){
                i++;
            }else{
                swap(nums[i],nums[k]);
                k--;
            }
        }
    }
};
```

## Q segregate 0,1,2,3

```cpp
#include <bits/stdc++.h>
using namespace std;


void solve(){
   int arr[]={0,3,2,1,3,3,0,2,2,1,1,2};
   int size=sizeof(arr)/sizeof(arr[0]);
   int pt0=-1;
   int pt1=0;
   int ptu=size-1;
   int pt2=size;
   while(pt1<=ptu){
   	if(arr[pt1]==0){
   		pt0++;
   		swap(arr[pt0],arr[pt1]);
   		pt1++;
   	}else if(arr[pt1]==1){
   		pt1++;
   	}else if(arr[pt1]==2){
   		swap(arr[ptu],arr[pt1]);
   		ptu--;
   	}else{
   		pt2--;
   		swap(arr[pt2],arr[pt1]);
   		if(pt2==ptu) ptu--;
   	}
   }

   for(int i=0;i<size;i++){
   	cout<<arr[i]<<" ";
   }
}
int main()
{
#ifndef ONLINE_JUDGE
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
#endif	
	solve();
	return 0;
}

```




 ![alt text](<001basic ques segregate 0123 conatiner most wtr_231123_170649(17).jpg>) ![alt text](<001basic ques segregate 0123 conatiner most wtr_231123_170649(18).jpg>) ![alt text](<001basic ques segregate 0123 conatiner most wtr_231123_170649(19).jpg>) ![alt text](<001basic ques segregate 0123 conatiner most wtr_231123_170649(20).jpg>) ![alt text](<001basic ques segregate 0123 conatiner most wtr_231123_170649(21).jpg>) ![alt text](<001basic ques segregate 0123 conatiner most wtr_231123_170649(22).jpg>) ![alt text](<001basic ques segregate 0123 conatiner most wtr_231123_170649(23).jpg>)