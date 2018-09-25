class Solution {
public:
    int longestIncreasingPath(vector<vector<int>>& matrix) {
        int maxLen = 0;
        for(int i = 0 ; i < matrix.size() ;i++) {
            vector<bool> temp(matrix[i].size(),false);
            vector<int> tempLen(matrix[i].size(),1);
            visit.push_back(temp);
            pLen.push_back(tempLen);
        }
        
        for(int i = 0 ; i < matrix.size() ; i++) {
            for(int j = 0 ; j < matrix[i].size(); j ++) {
                if(!visit[i][j])maxLen = max(maxLen,DFS(matrix,i,j));
            }
        }

        return maxLen;
    }
    int DFS(vector<vector<int>>& matrix,int row,int col) {
        if(visit[row][col]) return pLen[row][col];
        visit[row][col] = true;
        for(int i = row - 1 ; i <= row + 1 ; i++){
            for(int j = col - 1 ; j <= col + 1 ; j++){
                if(i < 0 || j < 0 || i >= matrix.size() || j >= matrix[i].size() || (i == row && j == col) || (i != row && j != col))
                    continue;
                if(matrix[i][j] > matrix[row][col]) pLen[row][col] = max(pLen[row][col],DFS(matrix,i,j) + 1);
            }
        }
        return pLen[row][col];
    }
private:
    vector<vector<bool>> visit;
    vector<vector<int>> pLen;
};