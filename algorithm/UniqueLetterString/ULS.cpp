#define MODNUM 1000000007
class Solution {
public:
    int uniqueLetterString(string S) {
        int last[26];
        int use[26];
        int result = 0;
        for(int i = 0 ; i < 26 ; i++) last[i] = use[i] = -1;
        for(int i = 0 ; i < S.length();i++){
            int now = (int)(S[i] - 'A');
            result += (use[now] - last[now]) * (i - use[now]);
            result%=MODNUM;
            if(last[now] != use[now]) last[now] = use[now];
            use[now] = i;
        }
        int finalV = S.length();
        for(int i = 0 ; i < 26 ; i++) {
            result += (use[i] - last[i]) * (finalV - use[i]);
            result%=MODNUM;
        }
        return result;
    
    }
};