class Solution {
public:
    string findReplaceString(string S, vector<int>& indexes, vector<string>& sources, vector<string>& targets) {
        string output;
        vector<int> rep(S.length(),-1);
        
        for(int i = 0 ; i < indexes.size() ; i++) {
            if(!S.compare(indexes[i],sources[i].length(),sources[i])) rep[indexes[i]] = i;
        }
        
        for(int i = 0 ; i < rep.size() ; i++) {
            if(rep[i] >= 0) {
                output += targets[rep[i]];
                i += sources[rep[i]].length() - 1;
            }else {
                output += S[i];
            }
        }
        
        
        return output;
    }
};