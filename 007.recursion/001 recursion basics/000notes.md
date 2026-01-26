# Notes

![alt text](<001 23-3-2022 recursion_231121_163402.jpg>)
![alt text](<001 23-3-2022 recursion_231121_163402(1).jpg>) ![alt text](<001 23-3-2022 recursion_231121_163402(2).jpg>) ![alt text](<001 23-3-2022 recursion_231121_163402(3).jpg>)

```java
    public static int mazePath(int sr, int sc, int er, int ec, String psf) {
        if (sr == er && sc == ec) {
            System.out.println(psf);
            return 1;
        }

        int count = 0;
        if (sc + 1 <= ec)
            count += mazePath(sr, sc + 1, er, ec, psf + "h"); // H
        if (sr + 1 <= er)
            count += mazePath(sr + 1, sc, er, ec, psf + "v"); // V
        if (sc + 1 <= ec && sr + 1 <= er)
            count += mazePath(sr + 1, sc + 1, er, ec, psf + "d"); // D

        return count;
    }

```


![alt text](<001 23-3-2022 recursion_231121_163402(4).jpg>) 
![alt text](<001 23-3-2022 recursion_231121_163402(5).jpg>) 
![alt text](<001 23-3-2022 recursion_231121_163402(6).jpg>) 

```java


    public static int mazePath2(int sr, int sc, int er, int ec, int[][] dir, String[] dirS, String psf) {
        if (sr == er && sc == ec) {
            System.out.println(psf);
            return 1;
        }

        int count = 0;
        for (int d = 0; d < dir.length; d++) {
            int r = sr + dir[d][0];
            int c = sc + dir[d][1];

            if (r >= 0 && c >= 0 && r <= er && c <= ec) {
                count += mazePath2(r, c, er, ec, dir, dirS, psf + dirS[d]);
            }

        }

        return count;
    }


```

![alt text](<001 23-3-2022 recursion_231121_163402(7).jpg>) 

![alt text](<001 23-3-2022 recursion_231121_163402(8).jpg>)

![alt text](<001 23-3-2022 recursion_231121_163402(9).jpg>) 

![alt text](<001 23-3-2022 recursion_231121_163402(10).jpg>) 

```cpp


    public static int mazePathJump(int sr, int sc, int er, int ec, int[][] dir, String[] dirS, String psf) {
        if (sr == er && sc == ec) {
            System.out.println(psf);
            return 1;
        }

        int count = 0;
        for (int d = 0; d < dir.length; d++) {
            for (int rad = 1; rad <= Math.max(er, ec); rad++) {
                int r = sr + rad * dir[d][0];
                int c = sc + rad * dir[d][1];

                if (r >= 0 && c >= 0 && r <= er && c <= ec) {
                    count += mazePathJump(r, c, er, ec, dir, dirS, psf + dirS[d] + rad);
                } else
                    break;
            }
        }

        return count;
    }


```

![alt text](<001 23-3-2022 recursion_231121_163402(11).jpg>) 
![alt text](<001 23-3-2022 recursion_231121_163402(12).jpg>) 
![alt text](<001 23-3-2022 recursion_231121_163402(13).jpg>) 
![alt text](<001 23-3-2022 recursion_231121_163402(14).jpg>) 

```java

    public static int floodFill(int sr, int sc, int er, int ec, boolean[][] vis, int[][] dir, String[] dirS,
            String psf) {
        if (sr == er && sc == ec) {
            System.out.println(psf);
            return 1;
        }

        vis[sr][sc] = true;
        int count = 0;
        for (int d = 0; d < dir.length; d++) {
            int r = sr + dir[d][0];
            int c = sc + dir[d][1];

            if (r >= 0 && c >= 0 && r <= er && c <= ec && !vis[r][c]) {
                count += floodFill(r, c, er, ec, vis, dir, dirS, psf + dirS[d]);
            }

        }
        vis[sr][sc] = false;
        return count;
    }

    public static int floodFillJump(int sr, int sc, int er, int ec, boolean[][] vis, int[][] dir, String[] dirS,
            String psf) {
        if (sr == er && sc == ec) {
            System.out.println(psf);
            return 1;
        }

        vis[sr][sc] = true;
        int count = 0;
        for (int d = 0; d < dir.length; d++) {
            for (int rad = 1; rad <= Math.max(er, ec); rad++) {
                int r = sr + rad * dir[d][0];
                int c = sc + rad * dir[d][1];

                if (r >= 0 && c >= 0 && r <= er && c <= ec) {
                    if (!vis[r][c])
                        count += floodFillJump(r, c, er, ec, vis, dir, dirS, psf + dirS[d] + rad);
                } else
                    break;
            }
        }

        vis[sr][sc] = false;
        return count;
    }


```


![alt text](<001 23-3-2022 recursion_231121_163402(15).jpg>) ![alt text](<001 23-3-2022 recursion_231121_163402(16).jpg>) ![alt text](<001 23-3-2022 recursion_231121_163402(17).jpg>) ![alt text](<001 23-3-2022 recursion_231121_163402(18).jpg>) ![alt text](<001 23-3-2022 recursion_231121_163402(19).jpg>) ![alt text](<001 23-3-2022 recursion_231121_163402(20).jpg>) ![alt text](<001 23-3-2022 recursion_231121_163402(21).jpg>) ![alt text](<001 23-3-2022 recursion_231121_163402(22).jpg>) ![alt text](<001 23-3-2022 recursion_231121_163402(23).jpg>) ![alt text](<001 23-3-2022 recursion_231121_163402(24).jpg>) 

```java



// User function Template for Java

// m is the given matrix and n is the order of matrix
class Solution {
    public static boolean isitsafe(int r,int c,int n,int[][]m){
        if(r>=0&&r<n&&c>=0&&c<n&&m[r][c]==1) return true;
       else return false;
    }
    public static void helper(int r,int c,int[][]m,int n,ArrayList<String>res,String psf,int[][] dir,String[] dirS){
        if(r==n-1&&c==n-1){
            res.add(psf);
            return;
        }
        m[r][c]=0;
        for(int i=0;i<dirS.length;i++){
            int nr=r+dir[i][0];
            int nc=c+dir[i][1];
            if(isitsafe(nr,nc,n,m)==true){
                helper(nr,nc,m,n,res,psf+dirS[i],dir,dirS);
            }
        }
        m[r][c]=1;
        
    }
    public static ArrayList<String> findPath(int[][] m, int n) {
        // Your code here
        
        ArrayList<String>res=new ArrayList<>();
        if(m[0][0]==0) return res;
        int[][] dir={{1,0},{-1,0},{0,-1},{0,1}};
        String[] dirS={"D","U","L","R",};
        helper(0,0,m,n,res,"",dir,dirS);
        return res;
    }
}

```

![alt text](<001 23-3-2022 recursion_231121_163402(25).jpg>)



![alt text](<001 23-3-2022 recursion_231121_163402(26).jpg>) ![alt text](<001 23-3-2022 recursion_231121_163402(27).jpg>) ![alt text](<001 23-3-2022 recursion_231121_163402(28).jpg>) ![alt text](<001 23-3-2022 recursion_231121_163402(29).jpg>) ![alt text](<001 23-3-2022 recursion_231121_163402(30).jpg>) ![alt text](<001 23-3-2022 recursion_231121_163402(31).jpg>) 