class Solution {
public:
    int surfaceArea(vector<vector<int> >& grid) {
        int result = 0;
        for(int i = 0 ; i < grid.size() ; i++) {
            for(int j = 0 ; j < grid[i].size() ; j ++) {
                result += 4 * grid[i][j] + 2*(grid[i][j] > 0 ? 1:0);
                if(i > 0) result -= 2*min(grid[i-1][j],grid[i][j]);
                if(j > 0) result -= 2*min(grid[i][j-1],grid[i][j]);
            }
        }
        return result;
    }
};
