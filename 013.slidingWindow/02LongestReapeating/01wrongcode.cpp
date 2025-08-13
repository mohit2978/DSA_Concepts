#include <bits/stdc++.h>
using namespace std;

class Solution{
  public:
    int longestNonRepeatingSubstring(string& s){
        unordered_map<char,int>mp;
        int n=s.size();
        int res=0;
        int l=0;
        for(int r=0;r<n;r++){
           if(mp.find(s[r])==mp.end()) mp[s[r]]++;
           else {
            while(s[l]!=s[r]){
                mp[s[l]]--;
                l++;
            }
           }
           res=max(res,r-l+1);
        }
        return res;
    }
};