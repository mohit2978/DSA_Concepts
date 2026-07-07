# Notes
![alt text](<008 target set_231121_163402.jpg>)
![alt text](<008 target set_231121_163402(1).jpg>)
![alt text](<008 target set_231121_163402(2).jpg>) 
```java
class Solution {
public static int coinChange_comb(int[] coins,int Tar,int[] dp){
        dp[0]=1;
        
        for(int coin:coins)
        {
         for(int tar=coin;tar<=Tar;tar++){
          if(tar-coin>=0){
              dp[tar]+=dp[tar-coin];
          }
              
       }
         
    }
    return dp[Tar];
    }
    public int change(int amount, int[] coins) {
  
        if(amount==0) return 1;
        int[] dp=new int[amount+1];
       
        int res= coinChange_comb(coins,amount,dp);
       
        return res;
    }
}
```

![alt text](<008 target set_231121_163402(3).jpg>) ![alt text](<008 target set_231121_163402(4).jpg>) ![alt text](<008 target set_231121_163402(5).jpg>) 

```java
public static int coinChange_comb(int[] coins,int Tar,int[][] dp){
    for(int i=0;i<dp.length;i++){
        for(int tar=0;tar<dp[0].length;tar++){
            if(tar==0) {
                dp[i][tar]=1;
                continue;
            }
            for(int idx=0;idx<=i;idx++){
            if(tar-coins[idx]>=0){
                dp[i][tar]+=dp[idx][tar-coins[idx]];
            }
        }
     }
    }
    return dp[coins.length-1][Tar];
     
    }
    public int change(int amount, int[] coins) {
  
        if(amount==0) return 1;
        int[][] dp=new int[coins.length][amount+1];
       
        int res=coinChange_comb(coins,amount,dp);
       
        return res;
       
    }
```

![alt text](<008 target set_231121_163402(6).jpg>) ![alt text](<008 target set_231121_163402(7).jpg>) ![alt text](<008 target set_231121_163402(8).jpg>)
![alt text](<008 target set_231121_163402(9).jpg>) ![alt text](<008 target set_231121_163402(10).jpg>) ![alt text](<008 target set_231121_163402(11).jpg>) ![alt text](<008 target set_231121_163402(12).jpg>) ![alt text](<008 target set_231121_163402(13).jpg>) ![alt text](<008 target set_231121_163402(14).jpg>) ![alt text](<008 target set_231121_163402(15).jpg>)