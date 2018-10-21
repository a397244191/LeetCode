class Solution {
public:
    bool isMatch(string s, string p) {
        int plen = 0;
        for(int i = 0 ; i < p.length() ; i++)
            if(p[i] != '*')plen++;
        vector<vector<bool>> check = vector<vector<bool>>(plen+1,vector<bool>(s.length()+1,false));
        check[0][0] = true;
        int puse = 0;
        for(int i = 1 ; i <= plen ; i++) {
            bool rep = false;
            char use = p[puse];
            if(puse < p.length() - 1 && p[puse+1] == '*') {
                rep = true;
                puse++;
            }
            puse++;
            for(int j = 0 ; j < s.length() + 1 ; j++) {
                if(j == 0) {
                    if(rep) check[i][j] = check[i-1][j];
                }
                else if(rep) {
                    if(j > 0 && (use=='.' || use == s[j-1]))
                        check[i][j] = check[i-1][j] || check[i-1][j-1] || check[i][j-1];
                    else 
                        check[i][j] = check[i-1][j];
                }else{
                    if(use=='.' || use == s[j-1]) 
                        check[i][j] = check[i-1][j-1];
                }
            }
        }
        
        
        return check.back().back();
    }
};