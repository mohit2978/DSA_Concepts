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