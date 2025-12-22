# Notes

## Q1 median of two sorted arrays

![alt text](<006 youtube median of sorted arrays_231231_184214.jpg>)

![alt text](<006 youtube median of sorted arrays_231231_184214(1).jpg>) ![alt text](<006 youtube median of sorted arrays_231231_184214(2).jpg>) ![alt text](<006 youtube median of sorted arrays_231231_184214(3).jpg>) ![alt text](<006 youtube median of sorted arrays_231231_184214(4).jpg>) ![alt text](<006 youtube median of sorted arrays_231231_184214(5).jpg>) ![alt text](<006 youtube median of sorted arrays_231231_184214(6).jpg>) ![alt text](<006 youtube median of sorted arrays_231231_184214(7).jpg>) ![alt text](<006 youtube median of sorted arrays_231231_184214(8).jpg>) ![alt text](<006 youtube median of sorted arrays_231231_184214(9).jpg>) ![alt text](<006 youtube median of sorted arrays_231231_184214(10).jpg>) ![alt text](<006 youtube median of sorted arrays_231231_184214(11).jpg>) ![alt text](<006 youtube median of sorted arrays_231231_184214(12).jpg>)

```cpp
class Solution {
    public double findMedianSortedArrays(int[] nums1, int[] nums2) {
        if(nums2.length<nums1.length) return findMedianSortedArrays(nums2,nums1);
        int sz=nums1.length+nums2.length;
        int seg=(sz+1)/2;
        int lo=0;
        int hi=nums1.length;
        while(lo<=hi){
            int amid=(lo+hi)/2;
            int bmid=seg-amid;
            int aMidm1=(amid==0)?Integer.MIN_VALUE:nums1[amid-1];
            int amid1=(amid==nums1.length)?Integer.MAX_VALUE:nums1[amid];
            int bMidm1=(bmid==0)?Integer.MIN_VALUE:nums2[bmid-1];
            int bmid1=(bmid==nums2.length)?Integer.MAX_VALUE:nums2[bmid];            
            
            if(aMidm1<=bmid1 && bMidm1<=amid1 ){
                if(sz%2==0){
                    int v1=Math.max(aMidm1,bMidm1);
                    int v2=Math.min(amid1,bmid1);
                    return (v1+v2)/2.0;
                }
                else return Math.max(aMidm1,bMidm1);
            }
            else if(aMidm1>bmid1) hi=amid-1;
            else lo=amid+1;

        }
        return -1;
    }
}
```

 ![alt text](<006 youtube median of sorted arrays_231231_184214(13).jpg>) 
![alt text](<006 youtube median of sorted arrays_231231_184214(14).jpg>) 
![alt text](<006 youtube median of sorted arrays_231231_184214(15).jpg>) 
![alt text](<006 youtube median of sorted arrays_231231_184214(16).jpg>)
 ![alt text](<006 youtube median of sorted arrays_231231_184214(17).jpg>) 