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





































