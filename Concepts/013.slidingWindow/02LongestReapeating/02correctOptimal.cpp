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
            mp[s[r]]++;
            while(mp[s[r]]>1){
                mp[s[l]]--;
                l++;
            }
           res=max(res,r-l+1);
        }
        return res;
    }
};