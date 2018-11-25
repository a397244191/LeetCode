class Solution {
public:
    int findPaths(int m, int n, int N, int i, int j) {
        dp = vector<vector<vector<int>>>(51,vector<vector<int>>(51,vector<int>(51,-1)));
        return DFS(i,j,N,m,n);
    }
    int DFS(int r, int c, int move,int high,int width) {
        if(dp[r][c][move] >= 0) return dp[r][c][move];
        else if(move == 0) {
            dp[r][c][move] = 0;
            return 0;
        }
        int dir[4][2] = {{1,0},{-1,0},{0,1},{0,-1}};
        
        int count = 0;
        for(int i = 0 ; i < 4 ; i++) {
            int nr = r + dir[i][0], nc = c + dir[i][1];
            if(nr >= 0 && nr < high && nc >= 0 && nc < width) count += DFS(nr,nc,move-1,high,width);
            else count++;
            count %= MOD;
        }
        dp[r][c][move] = count;
        return count;
    }
    vector<vector<vector<int>>> dp;
    int MOD = 1000000007;
};