class Solution {
public:
    int cutOffTree(vector<vector<int>>& forest) {
        vector<int> arr;
        for(int i = 0 ; i < forest.size() ; i++)
            for(int j = 0 ; j < forest[i].size() ; j++)
                if(forest[i][j] > 0) arr.push_back(forest[i][j]);
        sort(arr.begin(),arr.end());
        pair<int,int> start = pair<int,int>(0,0);
        int length = 0;
        for(int i = 0 ;i < arr.size() ; i++) {
            pair<int,pair<int,int>> temp = BFS(start,forest,arr[i]);
            if(temp.first == -1) return -1;
            length+=  temp.first;
            start = temp.second;
        }
        return length;
    }
    
    pair<int,pair<int,int>> BFS(pair<int,int> now ,vector<vector<int>> forest,int target){
        int mr = forest.size(), mc = forest[0].size();
        int dir[4][2] = {{1,0},{-1,0},{0,1},{0,-1}};
        vector<vector<bool>> visit = vector<vector<bool>>(mr,vector<bool>(false,mc));
        
        for(int i = 0 ; i < mr ; i++)for(int j = 0 ; j < mc ; j++) visit[i][j] = false;
        queue<pair<int,pair<int,int>>> q;
        q.push(pair<int,pair<int,int>>(0,now));
        while(!q.empty()) {
            pair<int,pair<int,int>> use = q.front();
            q.pop();
            pair<int,int> pos = use.second;
            
            
            if(visit[pos.first][pos.second] || forest[pos.first][pos.second] == 0) {
                
                continue;
            }
            if(forest[pos.first][pos.second] == target) return use;
            visit[pos.first][pos.second] = true;
            for(int i = 0 ; i < 4 ; i++){
                int nr = pos.first+dir[i][0], nc = pos.second+dir[i][1];
                pair<int,int> npos = pair<int,int>(nr,nc);
                if(nr >= 0 && nr < mr && nc >= 0 && nc < mc)
                    q.push(pair<int,pair<int,int>>(use.first+1,npos));     
            }
        }
        return pair<int,pair<int,int>>(-1,pair<int,int>(-1,-1));
    }
};