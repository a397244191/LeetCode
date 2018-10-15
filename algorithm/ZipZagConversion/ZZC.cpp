class Solution {
public:
    string convert(string s, int numRows) {
        vector<string> sub;
        for(int i = 0 ; i < numRows ; i++) sub.push_back(string());
        int p = 0;
        bool inc = true;
        for(int i = 0 ; i < s.length() ; i++) {
            sub[p] += s[i];
            p += (inc ? 1 : (-1) );
            if( p == numRows - 1 || p == 0) inc ^= true;
            else if( p >= numRows || p < 0) p = 0;
        }
        string ans = sub[0];
        for(int i = 1 ;i < numRows ; i++) {
            ans += sub[i];
        }
        return ans;
    }
};