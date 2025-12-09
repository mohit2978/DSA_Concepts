# Notes

## Q1 leaders in an array  

![alt text](image.png)


```cpp
class Solution {
public:
    vector<int> leaders(vector<int>& nums) {
      vector<int> res;
      int n=nums.size();
      int maxel=-(1e4+1);
      for(int i=n-1;i>=0;i--){
            if(nums[i]>maxel){
                maxel=nums[i];
                res.push_back(nums[i]);
            }
      }

      reverse(res.begin(),res.end());
      return res;
    }

};
```

tc-->O(n)

## Q2 Equilibrium point 
![img.png](img.png)

```cpp

class Solution {
    public:
      // Function to find equilibrium point in the array.
      int findEquilibrium(vector<int> &arr) {
          long sum=0;
          for(int i=0;i<arr.size();i++){
              sum+=arr[i];
          }
          int lsum=0;
          for(int i=0;i<arr.size();i++){
              sum-=arr[i];
              if(sum==lsum) return i;
              lsum+=arr[i];
          }
          
          return -1;
          
      }
  };
  
  ```

## Q3 remove duplicates from sorted array


Given an integer array nums sorted in non-decreasing order, remove all duplicates in-place so that each unique element appears only once.



Return the number of unique elements in the array.



If the number of unique elements be k, then,

Change the array nums such that the first k elements of nums contain the unique values in the order that they were present originally.
The remaining elements, as well as the size of the array does not matter in terms of correctness.
The driver code will assess correctness by printing and checking only the first k elements of the modified array.


An array sorted in non-decreasing order is an array where every element to the right of an element is either equal to or greater in value than that element.


Examples:
---
Input: nums = [0, 0, 3, 3, 5, 6]

Output: 4

Explanation:

Resulting array = [0, 3, 5, 6, _, _]

There are 4 distinct elements in nums and the elements marked as _ can have any value.

---

Input: nums = [-2, 2, 4, 4, 4, 4, 5, 5]

Output: 4

Explanation:

Resulting array = [-2, 2, 4, 5, _, _, _, _]

There are 4 distinct elements in nums and the elements marked as _ can have any value.


```cpp
//remove duplicates from sorted array
class Solution {
    public int removeDuplicates(int[] nums) {
        int i=1;
        int j=0;
        while(i<nums.length){
            if(nums[i]!=nums[j]) {
                j++;
                nums[j]=nums[i];
            }
            i++;
        }
        return j+1;
    }
}

```

## Q4 second largest element in an array

```java
class Solution {
    //two loops O(N)+O(N)
    public int secondLargestElement1(int[] nums) {
        int max1=nums[0];
        for(int i=1;i<nums.length;i++){
            if(nums[i]>max1) max1=nums[i];
        }

        int max2=Integer.MIN_VALUE;
        for(int i=0;i<nums.length;i++){
            if(nums[i]==max1) continue;
            if(nums[i]>max2) max2=nums[i];
        }
        return max2==Integer.MIN_VALUE?-1:max2;
    }
    //one loop O(N)
    public int secondLargestElement(int[] nums) {
        if (nums.length < 2) {
          return -1;
        }
        int largest = Integer.MIN_VALUE;
        int secondLargest = Integer.MIN_VALUE;
        for (int i = 0; i < nums.length; i++) {

            if (nums[i] > largest) {
                 secondLargest = largest;
                largest = nums[i];
            } 
            else if (nums[i] > secondLargest && nums[i] != largest) {
                secondLargest = nums[i];
            }

        }

        return secondLargest == Integer.MIN_VALUE ?  -1 : secondLargest;
}
}
```

## Q5 sort array of  0 and 1

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


## Q6 sort array 0,1,2

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

## Q7 segregate 0,1,2,3

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

just try to make parts