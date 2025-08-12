# Notes

## Selection sort 

```cpp
class Solution {
public:
    vector<int> selectionSort(vector<int>& nums) {
        for(int i=0;i<nums.size();i++){
            int min=i;
            for(int j=i+1;j<nums.size();j++){
                if(nums[j]<nums[min]){
                    min=j;
                }
            }
            if(min!=i){
                swap(nums[min],nums[i]);
            }
        }
        return nums;
    }
};

```
## Bubble sort 

```cpp
class Solution {
public:
    vector<int> bubbleSort(vector<int>& arr) {
        for(int i=0;i<arr.size();i++){
            bool swapped=false;
            for(int j=0;j<arr.size()-i-1;j++){
                if(arr[j]>arr[j+1]){
                    swap(arr[j],arr[j+1]);
                    swapped=true;
                }
            }
            if(swapped==false) break;
        }
        return arr;
    }
};

```
## Insertion sort

```cpp
class Solution {
public:
    vector<int> insertionSort(vector<int>& arr) {
        for(int i=1;i<arr.size();i++){
            for(int j=i-1;j>=0;j--){
                if(arr[j]>arr[j+1]) swap(arr[j],arr[j+1]);
                else break;
            }
        }
        return arr;
    }
};

```

## Merge sort

```cpp

class Solution {
    void merge(vector<int>& arr,int lo,int mid,int hi){
        vector<int> temp;
        int left = lo;
        int right = mid + 1;
        while(left<=mid && right <=hi){
            if(arr[left]<=arr[right]){
                temp.push_back(arr[left++]);
            }else 
                temp.push_back(arr[right++]);
        }
        while (left <= mid) {
            temp.push_back(arr[left++]);
        }

        while (right <= hi) {
            temp.push_back(arr[right++]);
        }
        for (int i = lo; i <= hi; i++) {
            arr[i] = temp[i - lo];
        }
    }
    void mergeSortFunction(vector<int>& arr,int lo,int hi){
        if(lo>=hi) return;
        int mid=(lo+hi)/2;
        mergeSortFunction(arr,lo,mid);
        mergeSortFunction(arr,mid+1,hi);
        merge(arr,lo,mid,hi);
    }
public:
    vector<int> mergeSort(vector<int>& nums) {
         mergeSortFunction(nums,0,nums.size()-1);
         return nums;
    }
};

```

## Quick Sort

```cpp
class Solution {
    int getPartiton(vector<int>& arr,int l,int r){
        int pivot=arr[r];
        int i=0,j=0;
        while(i<=r){
            if(arr[i]<=pivot){
                swap(arr[i],arr[j]);
                i++;
                j++;
            }else{
                i++;
            }
        }
        return j-1;
    }

    void sortQuick(vector<int>& arr,int l,int r){
            if(l>=r) return;

            int p=getPartiton(arr,l,r);
            sortQuick(arr,l,p-1);
            sortQuick(arr,p,r);
    }
public:
    vector<int> quickSort(vector<int>& nums) {
        int n=nums.size();
        sortQuick(nums,0,n-1);
        return nums;
    }
};

```

## Heap sort

```cpp
class Solution {
    void downheapify(vector<int> &v ,int size ,int i){
        int idx=i;
        int leftidx=2*i+1;
        int rightidx=2*i+2;
        if(leftidx<size && v[leftidx]>v[idx]) idx=leftidx;
        if(rightidx<size && v[rightidx]>v[idx]) idx=rightidx;
        if(idx!=i){
            swap(v[idx],v[i]);
            downheapify(v,size,idx);
        }
    }
public:
    void heapSort(vector<int>&nums) {
        int n=nums.size();
        for(int i=n/2-1;i>=0;i--){
            downheapify(nums,n,i);
        }

        for(int i=n-1;i>=0;i--){
            swap(nums[i],nums[0]);
            downheapify(nums,i,0);
        }

    }
};
```

























