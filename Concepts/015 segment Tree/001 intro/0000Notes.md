# Notes

![alt text](Scanned_20250807-0455.jpg)


 ![alt text](Scanned_20250807-0456-01.jpg)

 ![alt text](Scanned_20250807-0456-02.jpg)

 ![alt text](Scanned_20250807-0456-03.jpg)


```cpp

 void buildTree(vector<int>& nums,int s,int e,int i){

    if(s==e){
        segtree[i]=nums[s];
        return;
    }

    int mid=(s+e)/2;
    buildTree(nums,s,mid,2*i+1);
    buildTree(nums,mid+1,e,2*i+2);

    segtree[i]=segtree[2*i+1]+segtree[2*i+2];

 }
 ```

## Update Query


![alt text](Scanned_20250807-1517-01.jpg)


![alt text](Scanned_20250807-1517-02.jpg) 

![alt text](Scanned_20250807-1517-03.jpg) 

```cpp
 void updateTree(int idx,int val,int s,int e,int i){

    if(s==e){
        segtree[i]=val;
        return;
    }
    int mid=(s+e)/2;
    if(idx<=mid) updateTree(idx,val,s,mid,2*i+1);
    else updateTree(idx,val,mid+1,e,2*i+2);

    segtree[i]=segtree[2*i+1]+segtree[2*i+2];
 }

```

## GetValue

![alt text](Scanned_20250807-1558-01.jpg)
 ![alt text](Scanned_20250807-1558-02.jpg) 
![alt text](Scanned_20250807-1558-03.jpg)

```cpp
int getSum(int l,int r,int s,int e,int i){

    if(r<s || e<l) return 0;

    if(l<=s && e<=r) return segtree[i];

    int mid=(s+e)/2;

    return getSum(l,r,s,mid,2*i+1)+getSum(l,r,mid+1,e,2*i+2);
}
```

## Why we take 4*n as size of tree??



 ![alt text](Scanned_20250807-1558-04.jpg) 

![alt text](Scanned_20250807-1558-05.jpg)


 ![alt text](Scanned_20250807-1558-06.jpg) 

## Question

![alt text](image.png)

```cpp
// User function Template for C++

class Solution {
    void buildSegmentTree(int i, int l, int r, vector<int>& segmentTree, int arr[]) {
        if(l == r) {
            segmentTree[i] = arr[l];
            return;
        }
        
        int mid = l + (r-l)/2;
        buildSegmentTree(2*i+1, l, mid, segmentTree, arr);
        buildSegmentTree(2*i+2, mid+1, r, segmentTree, arr);
        segmentTree[i] = segmentTree[2*i + 1] + segmentTree[2*i + 2];
    }
    
    int querySegmentTree(int start, int end, int i, int l, int r, vector<int>& segmentTree) {
        if(l > end || r < start) {
            return 0;
        }
        
        if(l >= start && r <= end) {
            return segmentTree[i];
        }
        
        int mid = l + (r-l)/2;
        return querySegmentTree(start, end, 2*i+1, l,    mid, segmentTree) + 
               querySegmentTree(start, end, 2*i+2, mid+1, r, segmentTree);
    }
  public:
    vector<int> querySum(int n, int arr[], int q, int queries[]) {
               vector<int> segmentTree(4*n);
        
        buildSegmentTree(0, 0, n-1, segmentTree, arr);
        
        vector<int> result;
        for(int i = 0; i < 2*q; i+=2) {
            int start = queries[i]-1;   //Input is in 1 base indexing
            int end   = queries[i+1]-1; //Input is in 1 based indexing
            
            result.push_back(querySegmentTree(start, end, 0, 0, n-1, segmentTree));
        }
        
        return result;

        
    }
};
```
We only need array only first time when builiding segment tree!! after that we no need of array.


We only need segmentTree array after that, Now here we have created function independently .

we can create in class too can see on later notes



















