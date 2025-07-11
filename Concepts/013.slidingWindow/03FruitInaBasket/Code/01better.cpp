#include <bits/stdc++.h>
using namespace std;

class Solution{
  public:
    int totalFruits(vector<int>& s){
        unordered_map<char,int>mp;
        int n=s.size();
        int res=0;
        int l=0;
        for(int r=0;r<n;r++){
            mp[s[r]]++;
            while(mp.size()>2){
                mp[s[l]]--;
                if(mp[s[l]]==0) mp.erase(s[l]);
                l++;
            }
           res=max(res,r-l+1);
        }
        return res;
    }
};