# Notes

## Q1 kth largest in an array 

 easy hai ye toh
```cpp

class Solution {
public:
    int kthLargestElement(vector<int>& nums, int k) {
        priority_queue<int>pq;
        int n=nums.size();
        for(int i=0;i<n;i++){
            pq.push(nums[i]);
        }
        int ans=0;
        while(k-->0){
           ans=pq.top();
           pq.pop();
        }
        return ans;
    }
};

```

## Q2 Kth largest element in a stream of running integers

Implement a class KthLargest to find the kth largest number in a stream. It should have the following methods:

KthLargest(int k, int [] nums) Initializes the object with the integer k and the initial stream of numbers in nums
int add(int val) Appends the integer val to the stream and returns the kth largest element in the stream.
Note that it is the kth largest element in the sorted order, not the kth distinct element.


### Examples:
Input: [KthLargest(3, [1, 2, 3, 4]), add(5), add(2), add(7)]

Output: [null, 3, 3, 4]

Explanation: initial stream = [1, 2, 3, 4], k = 3.

add(5): stream = [1, 2, 3, 4, 5] -> returns 3

add(2): stream = [1, 2, 2, 3, 4, 5] -> returns 3

add(7): stream = [1, 2, 2, 3, 4, 5, 7] -> returns 4

---

Input: [KthLargest(2, [5, 5, 5, 5], add(2), add(6), add(60)]

Output: [null, 5, 5, 6]

Explanation: initial stream = [5, 5, 5, 5], k = 2.

add(2): stream = [5, 5, 5, 5, 2] -> returns 5

add(6): stream = [5, 5, 5, 5, 2, 6] -> returns 5

add(60): stream = [5, 5, 5, 5, 2, 6, 60] -> returns 6

#### Solution

K is fixed here naa so we push k  elements only to the min heap ,as if we take max heap we cant get kth largest without popping (k-1)th largest



```cpp
class KthLargest {
private:
    int K; // Integer K
    priority_queue <int, vector<int>, greater<int>> pq; // Min-heap 
    
public:

    // Constructor
    KthLargest(int k, vector<int>& nums) {
        K = k; 
        for(int i = 0; i < nums.size(); i++) {
            // If the size of min-heap is less than k
            if(pq.size() < K) pq.push(nums[i]); // Add the current element
            
            // Else if the top element is smaller than the current element
            else if(nums[i] > pq.top()) {
                pq.pop(); // Pop the top element
                pq.push(nums[i]); // Add the current element
            }
        }
    }
    
    int add(int val) {
        // If the size of the queue is less than K
        if(pq.size() < K) {
            pq.push(val);

            return pq.top();
        }

        // If the smallest element is less than the element to be added
        if(val > pq.top()) {
            pq.pop(); // Remove the top element
            pq.push(val); // Add the current element
        }
        
        return pq.top(); // Return the Kth largest element
    }
};
```

how min heap gives on top kth max??

we make min -heap of k size.

suppose 1,2,3,4,5,6,7,8 need 4th largest ,min heap of 4 size initailly [1,2,3,4],1 is top

then 5 come 5>1(top) so [2,3,4,5] 2 is top

then 6 6>2(top) so [3,4,5,6] 3 is top

then 7>3(top) so [4,5,6,7] 4 is top

then 8>4 so [5,6,7,8] 5 is top ,5 is 4th largest

now suppose 10,11 came after additon so 5,6 will be popped off 

[7,8,10,11] be heap and 7 is top and 4th largest

#### Complexity Analysis:

---
Time Complexity:
KthLargest(K, nums): O(NlogK), where N is the number of elements in the given list.
For each element, insertion into the min-heap of size at most K takes O(logK) time. Hence, the overall time complexity of this method is O(NlogK)

add(val): O(log K)
If the size of the heap is less than k, inserting the value takes O(log K). If the heap already has k elements and the new value is greater than the smallest (heap top), we remove the top and insert the new value — both operations take O(log K). Therefore, each call to add takes O(log K) time.

---

Space Complexity: O(K)
This is because a min-heap of size at most K is maintained, which results in O(K) space in the worst case.