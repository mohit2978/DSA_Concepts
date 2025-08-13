#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int longestConsecutive(vector<int>& nums) {
        set<int>s;
        for(int val:nums){
            s.insert(val);
        }
        int res=0;
        for(int val:nums){
            if(s.find(val-1)==s.end()){
                int tres=0;
                while(s.find(val)!=s.end()){
                    tres++;
                    val++;
                }
                if(tres>res) res=tres;
            }
        }
        return res;
    }
};