# Notes

![alt text](image.png)

```cpp

class Solution{
	public:
		int matrixMultiplication(vector<int>& arr){
            int n=arr.size();
            vector<vector<int>> dp(n,vector<int>(n,0));
            for(int gap=1;gap<n;gap++){
                for(int i=1,j=gap;j<n;i++,j++){
                    if(i==j) continue;
                    int mini=1e9;
                    for(int k=i;k<=j-1;k++){
                        int ans=0;
                        ans+=dp[i][k];
                        ans+=dp[k+1][j];
                        ans+=(arr[i-1]*arr[k]*arr[j]);
                        mini=min(mini,ans);
                    }
                    dp[i][j]=mini;
                }
            }
            return dp[1][n-1];
    	}
};

```

![alt text](Scanned_20250826-2338-01.jpg) 
![alt text](Scanned_20250826-2338-02.jpg)
 ![alt text](Scanned_20250826-2338-03.jpg) 
 ![alt text](Scanned_20250826-2338-04.jpg)

## Rajneesh way 


```cpp

class Solution{
	public:
		int matrixMultiplication(vector<int>& arr){
            int n=arr.size();
            vector<vector<int>> dp(n,vector<int>(n,0));
            for(int gap=1;gap<n;gap++){
                for(int i=0,j=gap;j<n;i++,j++){
                    if(i+1==j) continue;
                    int mini=1e9;
                    for(int k=i+1;k<=j-1;k++){
                        int ans=0;
                        ans+=dp[i][k];
                        ans+=dp[k][j];
                        ans+=(arr[i]*arr[k]*arr[j]);
                        mini=min(mini,ans);
                    }
                    dp[i][j]=mini;
                }
            }
            return dp[0][n-1];
    	}
};
```

seems quite logical 

`i+1==j`--> one matrix only so return 0;

`k=i+1 to <=j-1` -->  as from front we leave anelement and from last we leave an element

then next is also simple !!


![alt text](Scanned_20250827-0002.jpg)

 ![alt text](Scanned_20250827-0003.jpg)











