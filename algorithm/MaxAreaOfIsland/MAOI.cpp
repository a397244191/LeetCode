class Solution {
public:
    int maxAreaOfIsland(vector<vector<int>>& grid) {
        int maxNum = 0;
        for(int i = 0 ; i < grid.size() ; i++) {
            for(int j = 0 ; j < grid[0].size() ; j++) {
                int temp = DFS(grid,i,j);
                maxNum = maxNum > temp ? maxNum : temp;
            }
        }
        return maxNum;
    }
    int DFS(vector<vector<int>>& grid,int r,int c) {
        if(grid[r][c] == 0) return 0;
        int dir[4][2] = {{1,0},{-1,0},{0,1},{0,-1}};
        int num = 1;
        grid[r][c] = 0;
        for(int i = 0 ;i < 4 ; i++) {
            int nr = r + dir[i][0], nc = c + dir[i][1];
            if(nr >= 0 && nc >= 0 && nr < grid.size() && nc < grid[0].size())
                num += DFS(grid,nr,nc);
        }
        return num;
    }
};