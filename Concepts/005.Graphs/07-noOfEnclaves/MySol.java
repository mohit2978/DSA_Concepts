class Solution {
    int helper(int i,int j,int [][] grid,int[][] dir){
        if(grid[i][j]==0) return 0;
        if(i==0||j==0||i==grid.length-1||j==grid[0].length-1) return -1;
         grid[i][j]=0;
        int res=1;
        for(int d=0;d<4;d++){
            int newi=i+dir[d][0];
            int newj=j+dir[d][1];
            int tres=helper(newi,newj,grid,dir);
            if(tres==-1) res=-1;// do not chnage to return as need to visit all other connected to this
            else if(res!=-1 )res+=tres; // do not remove if as then res will be added when res=-1 which we do not want
        }
         
        return  res;
    }
    public int numberOfEnclaves(int[][] grid) {
        int enclaves=0;
        int [][]dir={{0,-1},{0,1},{1,0},{-1,0}};
        for(int i=0;i<grid.length;i++)
        {
            for(int j=0;j<grid[0].length;j++){
                    if(grid[i][j]==1){
                    int tres=helper(i,j,grid,dir);
                    enclaves+=(tres==-1)?0:tres;
                }
            }
        }
        return enclaves;
    }
}