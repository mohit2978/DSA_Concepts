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