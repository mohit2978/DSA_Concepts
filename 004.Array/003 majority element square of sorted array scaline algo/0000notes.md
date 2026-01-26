# Notes

![alt text](<001 7 ques majority element_250225_163213_1.jpg>)
 ![alt text](<001 7 ques majority element_250225_163213_2.jpg>)
  ![alt text](<001 7 ques majority element_250225_163213_3.jpg>)


### Q1

```cpp
//https://leetcode.com/problems/faulty-keyboard/
#include<bits/stdc++.h>
using namespace std;

class Solution {
    private:
        void reverse(string &s ,int si,int ei){
            if(si==ei) return;
            while(si<ei){
                char ch=s[si];
                s[si]=s[ei];
                s[ei]=ch;
                si++;
                ei--;
            }
        }
    public:
        string finalString(string s) {
            string res;
            int j=0;
            for(int i=0;i<s.size();i++){
                if(s[i]=='i'){
                    reverse(res,0,res.size()-1);
                }else res.push_back(s[i]);
            }
            return res;
        }
    };

    int main (){
        Solution s;
        cout<<s.finalString("mohit")<<endl;
        return 0;
    }
```


![alt text](<001 7 ques majority element_250225_163213_4.jpg>)

   

### Q2

```cpp
#include<bits/stdc++.h>
using namespace std;

class Solution {
    public:
        bool finalString(string s1,string s2) {
            if(s1.size()>s2.size()) return false;
            int i=0;
            int j=0;
            while(i<s1.size() && j<s2.size()){
                if(s1[i]==s2[j]){
                    i++;
                    j++;
                }else if(i>0 && s2[j]==s1[i-1]) j++;
                else return false;
            }
            if(i!=s1.size() && j==s2.size()) return false; // some charater not in s1
            while(j!=s2.size()){
                if(s2[j]!=s1[i-1]) return false;
                j++;
            }
            return true;
        }
    };

 int main() {
    Solution s;
    cout<<s.finalString("sumeet","ssummmeettt")<<endl;
    cout<<s.finalString("shree","shrrre")<<endl;
    return 0;
 }   
 ```


![alt text](<001 7 ques majority element_250225_163213_5.jpg>)

### Q3

```java
class Solution {
    public int[] sortedSquares(int[] nums) {
        int [] res=new int[nums.length];
        int i=0;
        int j=nums.length-1;
        int resptr=j;
        while(i<=j){
            int sqi=nums[i]*nums[i];
            int sqj=nums[j]*nums[j];
            if(sqi>sqj){
                res[resptr]=sqi;
                i++;
            }
            else{
                res[resptr]=sqj;
                j--;
                
            }
            resptr--;
        }
        return res;
    }
}
```

![alt text](<001 7 ques majority element_250225_163213_6.jpg>) 
![alt text](<001 7 ques majority element_250225_163213_7.jpg>) 
![alt text](<001 7 ques majority element_250225_163213_8.jpg>)
![alt text](<001 7 ques majority element_250225_163213_9.jpg>) 
![alt text](<001 7 ques majority element_250225_163213_10.jpg>)

![alt text](<001 7 ques majority element_250225_163213_11.jpg>) 


### majority element

```cpp
class Solution {
    public:
        int majorityElement(vector<int>& nums) {
            int n=nums.size();
            int count=1;
            int v=nums[0];
            for(int i=1;i<n;i++){
                if(nums[i]==v) count++;
                else{
                    count--;
                    if(count==0){
                        count=1;
                        v=nums[i];
                    }
                }
            }
        int cnt1 = 0;
        for (int i = 0; i < n; i++) {
            if (nums[i] ==v) {
                cnt1++;
            }
        }
        
        return (cnt1>(n/2))?v:-1;    
        }
    };
```

### Majority element 2

```cpp

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

```


 ### Imp scaline algo

 ```cpp
 #include<bits/stdc++.h>
using namespace std;
int getSumInRange(vector<int>&vec, int n,vector<vector<int>>updates){

    for(vector<int> v: updates){
        int s=v[0];
        int e=v[1];
        int val=v[2];
        vec[s]=val;
        vec[e+1]=-val;
    }
}

void getPrefixSum(vector<int>&v){

    for(int i=1;i<v.size();i++){
        v[i]=v[i-1]+v[i];
    }
}

void print(vector<int>& v){
    for(int val :v){
        cout<<val<<" ";
    }
    cout<<endl;
}

int main(){
    vector<int>v(6,0); 
    vector<vector<int>>updates ={{1,3,2},{2,4,3},{0,2,-2}};
    getSumInRange(v,5,updates);
    getPrefixSum(v);
    print(v);
    return 0;
}

```



