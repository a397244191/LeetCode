class Solution {
public:
    int numDecodings(string s) {
        int number[2] = {1,0};
        // now status : 
        // 0:single decode
        // 1:combinatorial decode
        if(s[0] == '0') return 0;
        
        for(int i = 1 ; i < s.length() ; i++) {
            int next[2] = {0,0};
            // single decode
            if(s[i] != '0')// now single decodethe, the number of possible status is sum of last status.
                next[0] = number[0] + number[1];
            else// if now is 0, we don't single decode 
                next[0] = 0;
            // combination decode
            int combNum = (s[i-1] - '0') *10 + (s[i] - '0');
            if(combNum <= 26 && combNum >= 10)
                next[1] = number[0];
            else // combinatorial decode don't exist. 
                next[1] = 0;
            number[0] = next[0];
            number[1] = next[1];
        }
        return number[0] + number[1];
    }
};