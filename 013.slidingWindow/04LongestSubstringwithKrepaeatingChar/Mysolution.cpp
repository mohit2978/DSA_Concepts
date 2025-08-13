/*
Given a string s and an integer k.Find the length of the longest substring with at most k distinct characters.


Examples:
Input : s = "aababbcaacc" , k = 2

Output : 6

Explanation : The longest substring with at most two distinct characters is "aababb".

The length of the string 6.

Input : s = "abcddefg" , k = 3

Output : 4

Explanation : The longest substring with at most three distinct characters is "bcdd".

The length of the string 4.

Input : s = "abccab" , k = 4

Output:
6
*/
/*
Solution same as prev just in place of 2 just put K
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int kDistinctChar(string& s, int k) {
        unordered_map<char,int>mp;
        int n=s.size();
        int res=0;
        int l=0;
        for(int r=0;r<n;r++){
            mp[s[r]]++;
            if(mp.size()>k){
                mp[s[l]]--;
                if(mp[s[l]]==0) mp.erase(s[l]);
                l++;
            }
           res=max(res,r-l+1);
        }
        return res;
    }
};