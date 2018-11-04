class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        int check[256];
        int maxSize = 0;
        for(int i = 0 ; i < 256 ; i++) check[i] = -1;
        int start = 0;
        int len = 0;
        for(int i = 0 ; i < s.length() ; i++) {
            if(check[s[i]] == -1 || check[s[i]] < start) {
                check[s[i]] = i;
                len ++;
                maxSize = len > maxSize ? len : maxSize;
            } else {
                start = check[s[i]] + 1;
                check[s[i]] = i;
                len = check[s[i]] - start + 1;
            }
        }
        return maxSize;
    }
};