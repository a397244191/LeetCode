class Solution {
public:
    vector<int> eventualSafeNodes(vector<vector<int>>& graph) {
        int n = graph.size();
        visit = vector<bool>(n,false);
        record = vector<bool>(n,false);
        
        vector<int> ans;
        for(int i = 0 ; i < n ; i++) {
            if(DFS(i,graph)) ans.push_back(i);
        }
        
        return ans;
    }
    
private:
    vector<bool> visit;
    vector<bool> record;
    
    bool DFS(int node, vector<vector<int>>& graph) {
        if(visit[node]) return record[node];
        visit[node] = true;
        for(int i = 0 ; i < graph[node].size() ; i++) {
            if(!DFS(graph[node][i],graph)) {
                return record[node];
            } 
        }
        return (record[node] = true);
    }
};