#include <bits/stdc++.h>
using namespace std;

class Solution{
        void computeLPS(vector<int>&lps,string &s){
             int i=1;
             int j=0;
             while(i<s.size()){
                if(s[i]==s[j]){
                    lps[i]=j+1;
                    i++;
                    j++;
                }else{
                    while(j!=0 && s[i]!=s[j]){
                        j=lps[j-1];
                    }
                    if(s[i]==s[j]){
                        lps[i]=j+1;
                        j++;
                    }
                    i++;
                }
             }
        }
    public:
        vector <int> search(string pat, string txt){
         string s=pat +"$"+txt;
         int m=pat.size();
         int n=txt.size();
         vector<int>lps(s.size(),0);
         computeLPS(lps,s);
         vector<int> ans;
         for(int i=m+1;i<lps.size();i++){
            if(lps[i]==m){
                ans.push_back(i-2*m);
            }
         }
         return ans;
        }
};