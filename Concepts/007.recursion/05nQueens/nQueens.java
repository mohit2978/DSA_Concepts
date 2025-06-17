
import java.util.*;
public class nQueens {
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
     public static int nqueen_01(boolean[][] boxes, int tnq, int bno, List<String>temp, List<List<String>>res ) {
        if (tnq == 0) {
           res.add(new ArrayList<>(temp));
            return 1;
        }
        int count = 0, n = boxes.length;
        for (int bidx = bno; bidx < n * n; bidx++) {
            int r = bidx / n, c = bidx % n;
            if (isSafeToPlaceQueen(boxes, r, c)) {
                boxes[r][c] = true;
                StringBuilder sb=new StringBuilder();
                for(int i=0;i<n;i++){
                    if(i==c) sb.append("Q");
                    else sb.append(".");
                }
                temp.add(sb.toString());
                count += nqueen_01(boxes, tnq - 1, bidx + 1, temp,res);
                temp.remove(temp.size()-1);
                boxes[r][c] = false;
            }
        }
           return count;
       }
    public List<List<String>> solveNQueens(int n) {
        boolean[][] boxes=new boolean[n][n];
        List<List<String>>res=new ArrayList<>();
        List<String>temp=new ArrayList<>();
        nqueen_01(boxes,n,0,temp,res);
        return res;
    }
    public static void main(String[] args){
        nQueens  sol=new nQueens ();
        List<List<String>> val=sol.solveNQueens(4);
        System.out.println("total combination : "+val);
        //total combination : [[.Q.., ...Q, Q..., ..Q.], [..Q., Q..., ...Q, .Q..]]
    }
}
/*
Leetcode 51
Input: n = 4
Output: [[".Q..","...Q","Q...","..Q."],["..Q.","Q...","...Q",".Q.."]]
*/