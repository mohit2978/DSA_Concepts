# Notes

![alt text](<003matrix ques_240112_103551(1).jpg>) ![alt text](<003matrix ques_240112_103551(2).jpg>) ![alt text](<003matrix ques_240112_103551(3).jpg>) ![alt text](<003matrix ques_240112_103551(4).jpg>) ![alt text](<003matrix ques_240112_103551(5).jpg>) ![alt text](<003matrix ques_240112_103551(6).jpg>) ![alt text](<003matrix ques_240112_103551(7).jpg>) ![alt text](<003matrix ques_240112_103551(8).jpg>) ![alt text](<003matrix ques_240112_103551(9).jpg>)

```java

class Solution {
    public void dfs(int [][]grid,int[][] dir,boolean[][] vis,int i,int j,int orgcolor,int color){

         vis[i][j]=true;
        for(int diri=0;diri<4;diri++){
            int newi=i+dir[diri][0];
            int newj=j+dir[diri][1];
            if((newi<0||newj<0 || newi>=grid.length  || newj>= grid[0].length||(newi>=0 && newi<grid.length &&newj>=0 &&newj<grid[0].length && grid[newi][newj]!=orgcolor && grid[newi][newj]!=-orgcolor))&&grid[i][j]==orgcolor)
            {
                grid[i][j]=-orgcolor;
                
            }
            if(newi>=0 && newi<grid.length &&newj>=0 &&newj<grid[0].length &&vis[newi][newj]==false && grid[newi][newj]==orgcolor){
                
                dfs(grid,dir,vis,newi,newj,orgcolor,color);
            }
            
        }
        
    }
    public int[][] colorBorder(int[][] grid, int row, int col, int color) {
        int [][] dir={{0,1},{0,-1},{-1,0},{1,0}};
        boolean [][] vis=new boolean[grid.length][grid[0].length];
        int orgcolor=grid[row][col];
        dfs(grid,dir,vis,row,col,orgcolor,color);
        for(int i=0;i<grid.length;i++){
            for(int j=0;j<grid[0].length;j++){
                if(grid[i][j]==-orgcolor){
                    grid[i][j]=color;
                }
            }
        }
        return grid;
    }
}
```


 ![alt text](<003matrix ques_240112_103551(10).jpg>) ![alt text](<003matrix ques_240112_103551(11).jpg>) ![alt text](<003matrix ques_240112_103551(12).jpg>) ![alt text](<003matrix ques_240112_103551(13).jpg>) ![alt text](<003matrix ques_240112_103551(14).jpg>) ![alt text](<003matrix ques_240112_103551(15).jpg>) ![alt text](<003matrix ques_240112_103551(16).jpg>) ![alt text](<003matrix ques_240112_103551(17).jpg>) ![alt text](<003matrix ques_240112_103551(18).jpg>) 
 
 ```java
 class Solution {
    public class pair{
        int i,j,dist;
        pair(int i,int j,int dist){
            this.i=i;
            this.j=j;
            this.dist=dist;
        }
    }
    private void gcc(int [][] grid,int i,int j,LinkedList<pair>q,int[][] dir,int [][] vis){
        q.addLast(new pair(i,j,0));
        vis[i][j]=-1;
        //grid[i][j]=2;
        for(int d=0;d<4;d++){
            int newi=i+dir[d][0];
            int newj=j+dir[d][1];
            if(newi>=0 && newi< grid.length && newj>=0 && newj <grid[0].length && grid[newi][newj]==1&& vis[newi][newj]!=-1){
                gcc(grid,newi,newj,q,dir,vis);
            }
        }
    }
    private void getConnectedComp(int [][] grid,LinkedList<pair>q,int[][] dir,int [][] vis){
          for(int i=0;i<grid.length;i++){
            for(int j=0;j<grid[0].length;j++){
                if(grid[i][j]==1){
                    gcc(grid,i,j,q,dir,vis);
                    return;
                    
                }
            }
    }
    }
    private int getShortestBridge_BFS(int [][] grid,LinkedList<pair>q,int[][] dir,int [][] vis){
        while(q.size()>0){
            pair p=q.removeFirst();
            if(grid[p.i][p.j]==1 && vis[p.i][p.j]!=-1){
                return p.dist-1;
            }
            if(vis[p.i][p.j]==-2) continue;
            if(vis[p.i][p.j]!=-1) vis[p.i][p.j]=-2;
           
          for(int d=0;d<4;d++){
            int newi=p.i+dir[d][0];
            int newj=p.j+dir[d][1];
            if(newi>=0 && newi< grid.length && newj>=0 && newj <grid[0].length && vis[newi][newj]!=-2 && vis[newi][newj]!=-1){
                q.addLast(new pair(newi,newj,p.dist+1));
            }
        }
        }
        return -1;
    }
    public int shortestBridge(int[][] grid) {
        LinkedList<pair>q=new LinkedList<>();       
        int[][] vis=new int[grid.length][grid[0].length];

        int[][] dir={{-1,0},{1,0},{0,-1},{0,1}};
        getConnectedComp(grid,q,dir,vis);
       return  getShortestBridge_BFS(grid,q,dir,vis);
        
    }
}
```
 
 
 ![alt text](<003matrix ques_240112_103551(19).jpg>) ![alt text](<003matrix ques_240112_103551(20).jpg>) ![alt text](<003matrix ques_240112_103551(21).jpg>) ![alt text](<003matrix ques_240112_103551(22).jpg>)












































