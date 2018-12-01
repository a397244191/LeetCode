class Solution {
public:
    vector<int> findRedundantConnection(vector<vector<int>>& edges) {
        record = vector<int>(1001,-1);
        for(int i = 0 ; i < edges.size() ; i++) {
            if(edges[i][0] > edges[i][1]) swap(edges[i][0],edges[i][1]);
            if(find(edges[i][0]) == find(edges[i][1])) return edges[i];
            record[record[edges[i][1]]] = record[edges[i][0]];
        }
        return vector<int>{-1,-1};
    }
    int find(int n) {
        if(record[n] == -1) record[n] = n;
        if(record[n] != n)
            record[n] = find(record[n]);
        return record[n];
    }
    vector<int> record;
};