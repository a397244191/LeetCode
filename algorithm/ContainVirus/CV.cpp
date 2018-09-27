class Solution {
public:
    int containVirus(vector<vector<int>>& grid) {       
        
         /*
        loop(the number of virus parts)
            loop(all not build wall and have virus)
                count add 0 number
            max(all virus parts)
            if(no cell be infect) break
            defence the max number
            add the number of wall
            infect the cell that not defence
            merge virus parts
        return wall
        */
        
        // init some value
        int row = grid.size(),col = grid[0].size();
        
        visit = vector<vector<bool>>(row,vector<bool>(col,false));
        wallExist = vector<vector<vector<bool>>>(row,vector<vector<bool>>(col,vector<bool>(4,false)));
        
        //check how many virus parts are there
        vector<pair<int,int>> virus;
        for(int i = 0 ; i < row ; i++)
            for(int j = 0 ; j < col ;j++){
                if(!visit[i][j] && grid[i][j] == 1) {
                    DFS(grid,i,j,0);
                    virus.push_back(pair<int,int>(i,j));
                }
            }
        
        int maxDay = virus.size();
        int wall = 0;
        // run day
        while(maxDay--) {
            
            InitVisit(row,col);
            int maxInfect = 0;
            int maxPos = -1;
            pair<int,int> pos;
            // count the number of the cell be infect in this virus parts
            for(int i = 0 ; i < virus.size() ; i++) {
                InitVisit(row,col);
                pos = virus[i];
                
                int infect = DFS(grid,pos.first,pos.second,1);
                if(infect > maxInfect){
                    maxPos = i;
                    maxInfect = infect;
                }
            }
            // if we can't infect any cell, the end.
            if(maxPos == -1) break;
            
            //build the wall in this max position
            pos = virus[maxPos];
            
            
            InitVisit(row,col);
            wall += DFS(grid,pos.first,pos.second,2);
            
            // infect other cell
            InitVisit(row,col);
            for(int i = 0 ; i < virus.size() ; i++) {
                pos = virus[i];
                DFS(grid,pos.first,pos.second,3);
            }
            
            //delete all virus parts that we don't need

            
            virus.erase(virus.begin()+maxPos);
            InitVisit(row,col);
            for(int i = 0 ; i < virus.size() ;) {
                pos = virus[i];
                if(visit[pos.first][pos.second]){
                    virus.erase(virus.begin()+i);
                }else{
                    DFS(grid,pos.first,pos.second,0);
                    i++;
                }
            }
            
        }
        return wall;
    }
private:
    vector<vector<vector<bool>>> wallExist;
    vector<vector<bool>> visit;
    int DFS(vector<vector<int>>& grid,int r,int c,int type)// 0 is review, 1 is count infect, 2 is build wall, 3 is infect cell
    {
        int row = grid.size(),col = grid[0].size();
        if(Over(row,col,r,c)) return 0;
        int dr[4] = { 1, 0,-1, 0};
        int dc[4] = { 0, 1, 0,-1};
        if(visit[r][c]) return 0;
        visit[r][c] = true;
        if(type <= 1 && grid[r][c] == 0) {
            return 1;
        }
        
        int count = 0;
        for(int i = 0 ; i < 4 ; i++){
            if(!wallExist[r][c][i]){
                switch(type){
                    case 0:
                    case 1:
                        count += DFS(grid,r+dr[i],c+dc[i],type);
                        break;
                    default:
                        if(!Over(row,col,r+dr[i],c+dc[i]) && grid[r+dr[i]][c+dc[i]] == 0){
                            if(type == 2){
                                wallExist[r][c][i] = true;
                                wallExist[r+dr[i]][c+dc[i]][(i+2)%4] = true;
                                count++;
                            }else{
                                grid[r+dr[i]][c+dc[i]] = 1;
                                visit[r+dr[i]][c+dc[i]] = true;
                            }
                        }
                        else count += DFS(grid,r+dr[i],c+dc[i],type);
                        break;
                }
            }
        }
        return count;
    }
    void InitVisit(int row,int col){
        for(int i = 0 ; i < row ; i++)
            for(int j = 0 ; j < col ; j++)
                visit[i][j] = false;
    }
    
    bool Over(int row,int col,int i,int j){
        return (i < 0 || i >= row || j < 0 || j >= col);
    }

};
