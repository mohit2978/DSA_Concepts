# Notes
![alt text](<006bitwise operation and recursion_231229_130956.jpg>)

![alt text](<006bitwise operation and recursion_231229_130956(1).jpg>) ![alt text](<006bitwise operation and recursion_231229_130956(2).jpg>) ![alt text](<006bitwise operation and recursion_231229_130956(3).jpg>) ![alt text](<006bitwise operation and recursion_231229_130956(4).jpg>) ![alt text](<006bitwise operation and recursion_231229_130956(5).jpg>) ![alt text](<006bitwise operation and recursion_231229_130956(6).jpg>) ![alt text](<006bitwise operation and recursion_231229_130956(7).jpg>) ![alt text](<006bitwise operation and recursion_231229_130956(8).jpg>) ![alt text](<006bitwise operation and recursion_231229_130956(9).jpg>)
![alt text](<006bitwise operation and recursion_231229_130956(10).jpg>) 
![alt text](<006bitwise operation and recursion_231229_130956(11).jpg>) 
![alt text](<006bitwise operation and recursion_231229_130956(12).jpg>) 
![alt text](<006bitwise operation and recursion_231229_130956(13).jpg>) 
![alt text](<006bitwise operation and recursion_231229_130956(14).jpg>) 
![alt text](<006bitwise operation and recursion_231229_130956(15).jpg>) 
![alt text](<006bitwise operation and recursion_231229_130956(16).jpg>)
![alt text](<006bitwise operation and recursion_231229_130956(17).jpg>) 
![alt text](<006bitwise operation and recursion_231229_130956(18).jpg>) 


```java
public class l005_bits {

    public static int leftShift(int x) {
        return x << 1;
    }

    public static int rightShift(int x) {
        return x >> 1;
    }

    public static int setTrue(int x, int idx) {
        int mask = 1 << idx;
        return x | mask;
    }

    public static int setFalse(int x, int idx) {
        int mask = ~(1 << idx);
        return x & mask;
    }

    public static int multiplyBy2(int num, int pow) {
        return (num << pow);
    }

    public static int divideBy2(int num, int pow) {
        return (num >> pow);
    }

    public static boolean isEven(int x) {
        return (x & 1) == 0;
    }

    // 231
    public boolean isPowerOfTwo(int n) {
        return n > 0 && (n & (n - 1)) == 0;
    }

    // 342
    public boolean isPowerOfFour(int n) {
        if (!isPowerOfTwo(n))
            return false;
        // for c++. unsigned int N = n;
        int count = 0;
        while (n != 0) {
            if ((n & 1) == 0)
                count++;
            n >>>= 1; // only for java, cpp N >>=1;
        }

        return (count & 1) == 0;
    }

    // 136
    public int singleNumber(int[] nums) {
        int ans = 0;
        for (int ele : nums) {
            ans ^= ele;
        }

        return ans;

    }

    // 268
    public int missingNumber(int[] nums) {
        int n = nums.length, ans = n, i = 0;
        while (i < n) {
            ans ^= nums[i] ^ (i++);

        }
        return ans;
    }

    // 191

    public int hammingWeight_1(int n) {
        int count = 0, i = 0;
        while (i < 32) {
            if ((n & (1 << i)) != 0)
                count++;
            i++;
        }

        return count;
    }

    public int hammingWeight_2(int n) {
        int count = 0, i = 0;
        while (n != 0) {
            if ((n & 1) != 0)
                count++;
            n >>>= 1;
        }

        return count;
    }

    public int hammingWeight_3(int n) {
        int count = 0;
        while (n != 0) {
            count++;
            n = (n & (n - 1));
        }

        return count;
    }

    // 338
    public int[] countBits(int n) {
        int[] ans = new int[n + 1];
        for (int i = 1; i <= n; i++) {
            ans[i] = ans[i & (i - 1)] + 1;
        }

        return ans;

    }

    //260
    public int[] singleNumber(int[] nums) {
        int xor = 0;
        for(int ele : nums) xor ^= ele;
        int mask = xor & (-xor);
        
        int a = 0, b = 0;
        for(int ele : nums){
            if((ele & mask) == 0) a ^= ele;
            else b ^= ele;
        }
        
        return new int[]{a,b};
    }

    //287 -> after linkedlist
    
}

```
![alt text](<006bitwise operation and recursion_231229_130956(19).jpg>) 
![alt text](<006bitwise operation and recursion_231229_130956(20).jpg>) 
![alt text](<006bitwise operation and recursion_231229_130956(21).jpg>) 
![alt text](<006bitwise operation and recursion_231229_130956(22).jpg>) ![alt text](<006bitwise operation and recursion_231229_130956(23).jpg>) ![alt text](<006bitwise operation and recursion_231229_130956(24).jpg>) ![alt text](<006bitwise operation and recursion_231229_130956(25).jpg>) ![alt text](<006bitwise operation and recursion_231229_130956(26).jpg>) ![alt text](<006bitwise operation and recursion_231229_130956(27).jpg>) ![alt text](<006bitwise operation and recursion_231229_130956(28).jpg>) ![alt text](<006bitwise operation and recursion_231229_130956(29).jpg>) ![alt text](<006bitwise operation and recursion_231229_130956(30).jpg>) ![alt text](<006bitwise operation and recursion_231229_130956(31).jpg>) ![alt text](<006bitwise operation and recursion_231229_130956(32).jpg>) ![alt text](<006bitwise operation and recursion_231229_130956(33).jpg>)

![alt text](<006bitwise operation and recursion_231229_130956(34).jpg>) ![alt text](<006bitwise operation and recursion_231229_130956(35).jpg>) ![alt text](<006bitwise operation and recursion_231229_130956(36).jpg>) ![alt text](<006bitwise operation and recursion_231229_130956(37).jpg>) ![alt text](<006bitwise operation and recursion_231229_130956(38).jpg>) ![alt text](<006bitwise operation and recursion_231229_130956(39).jpg>) ![alt text](<006bitwise operation and recursion_231229_130956(40).jpg>) ![alt text](<006bitwise operation and recursion_231229_130956(41).jpg>) ![alt text](<006bitwise operation and recursion_231229_130956(42).jpg>) ![alt text](<006bitwise operation and recursion_231229_130956(43).jpg>) ![alt text](<006bitwise operation and recursion_231229_130956(44).jpg>) ![alt text](<006bitwise operation and recursion_231229_130956(45).jpg>) ![alt text](<006bitwise operation and recursion_231229_130956(46).jpg>) ![alt text](<006bitwise operation and recursion_231229_130956(47).jpg>) ![alt text](<006bitwise operation and recursion_231229_130956(48).jpg>) ![alt text](<006bitwise operation and recursion_231229_130956(49).jpg>) ![alt text](<006bitwise operation and recursion_231229_130956(50).jpg>) ![alt text](<006bitwise operation and recursion_231229_130956(51).jpg>) ![alt text](<006bitwise operation and recursion_231229_130956(52).jpg>) ![alt text](<006bitwise operation and recursion_231229_130956(53).jpg>) ![alt text](<006bitwise operation and recursion_231229_130956(54).jpg>) 



```java
public class l006_Nqueen {
    static boolean[] rows, cols, diags, adiags;

    public static int nqueen_01(int n, int tnq, int bno, String psf) {
        if (tnq == 0) {
            System.out.println(psf);
            return 1;
        }
        int count = 0;
        for (int bidx = bno; bidx < n * n; bidx++) {
            int r = bidx / n, c = bidx % n;
            if (!rows[r] && !cols[c] && !diags[r - c + n - 1] && !adiags[r + c]) {
                rows[r] = cols[c] = diags[r - c + n - 1] = adiags[r + c] = true;
                count += nqueen_01(n, tnq - 1, bidx + 1, psf + "(" + r + "," + c + ") ");
                rows[r] = cols[c] = diags[r - c + n - 1] = adiags[r + c] = false;
            }
        }
        return count;
    }

    static int row = 0, col = 0, diag = 0, adiag = 0;

    public static int nqueen_02(int n, int tnq, int bno, String psf) {
        if (tnq == 0) {
            System.out.println(psf);
            return 1;
        }
        int count = 0;
        for (int bidx = bno; bidx < n * n; bidx++) {
            int r = bidx / n, c = bidx % n;
            if ((row & (1 << r)) == 0 && (col & (1 << c)) == 0 && (diag & (1 << (r - c + n - 1))) == 0
                    && (adiag & (1 << (r + c))) == 0) {
                row ^= (1 << r);
                col ^= (1 << c);
                diag ^= (1 << (r - c + n - 1));
                adiag ^= (1 << (r + c));

                count += nqueen_02(n, tnq - 1, bidx + 1, psf + "(" + r + "," + c + ") ");

                row ^= (1 << r);
                col ^= (1 << c);
                diag ^= (1 << (r - c + n - 1));
                adiag ^= (1 << (r + c));
            }
        }
        return count;
    }

    public static int nqueen_03(int n, int floor, String psf) {
        if (floor == n) {
            System.out.println(psf);
            return 1;
        }
        int count = 0, r = floor;
        for (int room = 0; room < n; room++) {
            int c = room;
            if ((row & (1 << r)) == 0 && (col & (1 << c)) == 0 && (diag & (1 << (r - c + n - 1))) == 0
                    && (adiag & (1 << (r + c))) == 0) {
                row ^= (1 << r);
                col ^= (1 << c);
                diag ^= (1 << (r - c + n - 1));
                adiag ^= (1 << (r + c));

                count += nqueen_03(n, floor + 1, psf + "(" + r + "," + c + ") ");

                row ^= (1 << r);
                col ^= (1 << c);
                diag ^= (1 << (r - c + n - 1));
                adiag ^= (1 << (r + c));
            }
        }
        return count;
    }

    public static boolean isPalindrome(String str, int i, int j) {
        while (i <= j) {
            if (str.charAt(i) != str.charAt(j))
                return false;
            i++;
            j--;
        }
        return true;
    }

    public static void solution(String str, int i, String asf) {
        if (i >= str.length()) {
            System.out.println(asf);
            return;
        }
        for (int j = i; j < str.length(); j++) {
            if (isPalindrome(str, i, j)) {
                solution(str, j + 1, asf + "(" + str.substring(i, j + 1) + ") ");
            }
        }
    }

    public static void main(String... args) {
        int n = 4, tnq = 4;
        // rows = new boolean[n];
        // cols = new boolean[n];
        // diags = new boolean[n + n - 1];
        // adiags = new boolean[n + n - 1];
        // System.out.println(nqueen_02(n, tnq, 0, ""));
        System.out.println(nqueen_03(n, 0, ""));
    }
}

```