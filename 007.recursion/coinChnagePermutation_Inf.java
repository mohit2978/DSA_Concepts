/* package codechef; // don't place package name! */

import java.util.*;
import java.lang.*;
import java.io.*;

/* Name of the class has to be "Main" only if the class is public. */
class Codechef
{
        public static int coinChangePermutation_IN(int[] coins, int tar, String psf) {
        if (tar == 0) {
            System.out.println(psf);
            return 1;
        }

        int count = 0;
        for (int i = 0; i < coins.length; i++) {
            if (tar - coins[i] >= 0) {
                count += coinChangePermutation_IN(coins, tar - coins[i], psf + coins[i] + " ");
            }
        }

        return count;

    }

	public static void main (String[] args) throws java.lang.Exception
	{
		int[] coins = { 2, 3, 5, 7 };
        int tar = 10;
        coinChangePermutation_IN(coins,tar,"");

	}
}


/*
Output:
2 2 2 2 2 
2 2 3 3 
2 3 2 3 
2 3 3 2 
2 3 5 
2 5 3 
3 2 2 3 
3 2 3 2 
3 2 5 
3 3 2 2 
3 5 2 
3 7 
5 2 3 
5 3 2 
5 5 
7 3 
*/