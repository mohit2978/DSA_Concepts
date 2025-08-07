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
























