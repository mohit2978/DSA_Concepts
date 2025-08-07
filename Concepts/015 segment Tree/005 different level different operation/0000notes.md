 # Notes


![alt text](image.png)

Here it is given size is n=2^k so we know we will have 2*n nodes

so we can take segment tree size as 2*n or to be on safer side use 4*n.

![alt text](Scanned_20250807-1653-01.jpg)
 ![alt text](Scanned_20250807-1653-02.jpg)

```cpp

#include<bits/stdc++.h>
using namespace std;


class STree {
    vector<int>segtree;
    int n=0;
    int sz=0;
    int lvls=0;

 void buildTree(vector<int>& nums,int s,int e,int i,int level){

    if(s==e){
        segtree[i]=nums[s];
        return;
    }

    int mid=(s+e)/2;
    buildTree(nums,s,mid,2*i+1,level+1);
    buildTree(nums,mid+1,e,2*i+2,level+1);
    
    if(lvls%2==0){
        if(level%2!=0) segtree[i]=segtree[2*i+1]|segtree[2*i+2];
        else segtree[i]=segtree[2*i+1]^segtree[2*i+2];
        
    }else {
         if(level%2!=0) segtree[i]=segtree[2*i+1]^segtree[2*i+2];
        else segtree[i]=segtree[2*i+1]|segtree[2*i+2];
    }

 }



int getBitOp(int l,int r,int s,int e,int i,int levels){

    if(r<s || e<l) return 0;

    if(l<=s && e<=r) return segtree[i];

    int mid=(s+e)/2;

     if(lvls%2==0){
        if(levels%2!=0) return getBitOp(l,r,s,mid,2*i+1,levels+1)| getBitOp(l,r,mid+1,e,2*i+2,levels+1);
        else return getBitOp(l,r,s,mid,2*i+1,levels+1)^ getBitOp(l,r,mid+1,e,2*i+2,levels+1);
        
    }else {
         if(levels%2!=0) return getBitOp(l,r,s,mid,2*i+1,levels+1)^ getBitOp(l,r,mid+1,e,2*i+2,levels+1);
        else return getBitOp(l,r,s,mid,2*i+1,levels+1)| getBitOp(l,r,mid+1,e,2*i+2,levels+1);
    }
}
 void updateTree(int idx,int val,int s,int e,int i,int level){

    if(s==e){
        segtree[i]=val;
        return;
    }
    int mid=(s+e)/2;
    if(idx<=mid) updateTree(idx,val,s,mid,2*i+1,level+1);
    else updateTree(idx,val,mid+1,e,2*i+2,level+1);

     if(lvls%2==0){
        if(level%2!=0) segtree[i]=segtree[2*i+1]|segtree[2*i+2];
        else segtree[i]=segtree[2*i+1]^segtree[2*i+2];
        
    }else {
         if(level%2!=0) segtree[i]=segtree[2*i+1]^segtree[2*i+2];
        else segtree[i]=segtree[2*i+1]|segtree[2*i+2];
    }
 }

public:
    STree(vector<int>& nums,int treeLevels) {
        n=nums.size();
        sz=2*n;
        lvls=treeLevels;
        segtree.resize(sz);
        buildTree(nums,0,n-1,0,0);
    }
    void update(int index, int val) {

        updateTree( index, val,0,n-1,0,0);
        
    }
    
    int bitRange(int left, int right) {
        return getBitOp(left,right,0,n-1,0,0);
    }
};

vector<int> solve(int n, vector<int>a, vector<vector<int>> queries){
    STree st(a,n);
    
    vector<int> res;
    for(vector<int>q:queries){
        int idx=q[0]-1;
        int val=q[1];
        st.update(idx,val);
        res.push_back(st.bitRange(0,a.size()-1));
    }
    return res;
    

}
```
























