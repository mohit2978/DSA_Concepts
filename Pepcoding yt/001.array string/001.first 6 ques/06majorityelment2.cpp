//https://leetcode.com/problems/majority-element-ii/
class Solution {
    public:
        vector<int> majorityElement(vector<int>& arr) {
            int v1=arr[0];
            int c1=1;
            int v2=arr[0];
            int c2=0;
            for(int i=1;i<arr.size();i++){
                if(v1==arr[i]) c1++;
                else if(v2==arr[i]) c2++;
                else {
                    if(c1==0){
                        v1=arr[i];
                        c1=1;
                    }else if (c2==0){
                        v2=arr[i];
                        c2=1;
                    }else {
                        c1--;
                        c2--;
                    }
                }
            }
             c1=0,c2=0;
            for(int i=0;i<arr.size();i++){
                if(arr[i]==v1) c1++;
                if(v1!=v2 && arr[i]==v2) c2++;
            }
            vector<int> res;
            if(c1>(arr.size()/3)) res.push_back(v1);
            if(c2>(arr.size()/3)) res.push_back(v2);
            return res;
        }
    };