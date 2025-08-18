# Notes

## Spiral Matrix

![alt text](image.png)

![alt text](Scanned_20250819-0416.jpg)

```cpp

class Solution {
public:
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        int str=0,stc=0;
        int enr=matrix.size()-1;
        int enc=matrix[0].size()-1;
        vector<int> res;

        while(str<= enr && stc<=enc){

            for(int j=stc;j<=enc;j++) res.push_back(matrix[str][j]);

            str++;

            for(int i=str;i<=enr;i++) res.push_back(matrix[i][enc]);

            enc--;

            if(str<=enr){

                for(int j=enc;j>=stc;j--) res.push_back(matrix[enr][j]);

                enr--;
            }

           if(stc<=enc){
                
                for(int i=enr;i>=str;i--) res.push_back(matrix[i][stc]);

                stc++;
           }
        }

        return res;

    }
};

```

















