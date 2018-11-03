class Solution {
public:
    bool isMatch(string s, string p) {
        int m = s.size() + 1, n = p.size() + 1;
        vector<vector<bool>> dp = vector<vector<bool>>(n,vector<bool>(m));
        for(int i = 0 ; i < n ; i++) 
            for(int j = 0 ; j < m ; j++)
                dp[i][j] = false;
        dp[0][0] = true;
        for(int i = 1 ; i < n ; i++) {
            char c = p[i - 1];
            if(c == '*') dp[i][0] = dp[i-1][0];
            for(int j = 1 ; j < m ; j++) {
                if(c == '*') {
                    dp[i][j] = dp[i-1][j-1] || dp[i-1][j] || dp[i][j-1];
                } else if(c == '?' || c == s[j - 1]) {
                    dp[i][j] = dp[i-1][j-1];
                }
            }
        }
        return dp[n-1][m-1];
    }
};