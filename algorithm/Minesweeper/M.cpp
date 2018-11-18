class Solution {
public:
    vector<vector<char>> updateBoard(vector<vector<char>>& board, vector<int>& click) {
        stack<pair<int,int>> s;
        s.push(pair<int,int>(click[0],click[1]));
        int mr = board.size(), mc = board[0].size();
        while(!s.empty()) {
            pair<int,int> use = s.top();
            s.pop();
            if(board[use.first][use.second] == 'M'){
                board[use.first][use.second] = 'X';
                continue;
            } else if(board[use.first][use.second] == 'E') {
                int num = 0;
                for(int i = -1; i <= 1 ; i++) {
                    for(int j = -1; j <= 1 ; j++) {
                        int nr = use.first+ i, nc = use.second + j;
                        if(nr >= 0 && nr < mr && nc >= 0 && nc < mc && board[nr][nc] == 'M') {
                            num++;
                        }
                    }
                }
                if(num == 0) {
                    board[use.first][use.second] = 'B';
                    for(int i = -1; i <= 1 ; i++) {
                        for(int j = -1; j <= 1 ; j++) {
                            int nr = use.first+ i, nc = use.second + j;
                            if(nr >= 0 && nr < mr && nc >= 0 && nc < mc) {
                                s.push(pair<int,int>(nr,nc));
                            }
                        }
                    }
                } else {
                    board[use.first][use.second] = num + '0';
                }
            }
        }
    return board;
    }
};