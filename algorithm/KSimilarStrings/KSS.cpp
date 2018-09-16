class Solution {
public:
    int kSimilarity(string A, string B) {
        
        unordered_set<string> mySet;
        queue<pair<string,int> > q;
        q.push(pair<string,int>(A,0));
        while(!q.empty()) {
            
            pair<string,int> use = q.front();
            q.pop();
            string now = use.first;
            bool next = false;
            for(int i = 0 ; i < now.length() ; i ++){
                if(now[i] == B[i]) continue;
                for(int j = i + 1 ; j < B.length() ; j++) {
                    if(now[i] == B[j] && now[i] != now[j]) {
                        swap(now[i],now[j]);
                        if(mySet.find(now) == mySet.end()){
                            mySet.insert(now);
                            q.push(pair<string,int>(now,use.second+1));
                        }
                        swap(now[i],now[j]);
                        next = true;
                        break;
                    }
                }
            }
            if(next == false) return use.second;
        }
        return 0;
    }
};