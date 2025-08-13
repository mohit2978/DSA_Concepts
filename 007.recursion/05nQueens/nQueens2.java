import java.util.*;
public class nQueens2 {
    public static boolean isSafeToPlaceQueen(boolean[][] boxes, int r, int c) {
        int[][] dir = { { 0, -1 }, { -1, -1 }, { -1, 0 }, { -1, 1 }, { 0, 1 }, { 1, 1 }, { 1, 0 }, { 1, -1 } };
        int n = boxes.length;
        for (int d = 0; d < dir.length; d++) {
            for (int rad = 1; rad <= n; rad++) {
                int x = r + rad * dir[d][0];
                int y = c + rad * dir[d][1];

                if (x >= 0 && y >= 0 && x < n && y < n) {
                    if (boxes[x][y])
                        return false;
                }
                else 
                   break;
            }
        }
        return true;
    }
    public static int nqueen_01(boolean[][] boxes, int tnq, int bno ) {
        if (tnq == 0) {
          
            return 1;
        }
        int count = 0, n = boxes.length;
        for (int bidx = bno; bidx < n * n; bidx++) {
            int r = bidx / n, c = bidx % n;
            if (isSafeToPlaceQueen(boxes, r, c)) {
                boxes[r][c] = true;
                count += nqueen_01(boxes, tnq - 1, bidx + 1);
               
                boxes[r][c] = false;
            }
        }
           return count;
       }
    public int totalNQueens(int n) {
        boolean[][] boxes=new boolean[n][n];
        return nqueen_01(boxes,n,0);
       
    }

    public static void main(String[] args){
        nQueens2 sol=new nQueens2();
        int val=sol.totalNQueens(4);
        System.out.println("total combination : "+val);
        //total combination : 2
    }
}