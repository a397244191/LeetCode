class Solution {
public:
    vector<vector<int>> updateMatrix(vector<vector<int>>& matrix) {
        if(matrix.size() < 1) return matrix;
        nearestZero = vector<vector<int>>(matrix.size(),vector<int>(matrix[0].size(),-1));
        queue<pair<int,int>> q;
        int mr = matrix.size(), mc = matrix[0].size();
        int move[4][2] = {{1,0},{-1,0},{0,1},{0,-1}};
        for(int i = 0 ; i < matrix.size() ; i++) {
            for(int j = 0 ; j < matrix[i].size() ; j++) {
                if(matrix[i][j] == 1) continue;
                nearestZero[i][j] = 0;
                q.push(pair<int,int>(i,j));
                
            }
        }
        while(!q.empty()) {
            pair<int,int> use = q.front();
            int val = nearestZero[use.first][use.second];
            q.pop();
            for(int k = 0 ; k < 4 ; k++) {
                int nr = use.first + move[k][0],nc = use.second + move[k][1];
                if(nr >=0 && nr < mr && nc >= 0 && nc < mc && matrix[nr][nc] == 1) {
                    if(nearestZero[nr][nc] == -1 || nearestZero[nr][nc] > val + 1) {
                        nearestZero[nr][nc] = val + 1;
                        q.push(pair<int,int>(nr,nc));
                    }
                }
            }
        }
        return nearestZero;
    }
private:
    vector<vector<int>> nearestZero;
};