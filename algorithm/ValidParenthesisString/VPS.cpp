class Solution {
public:
    bool checkValidString(string s) {
        int allLeft = 0;
        int allRight = 0;
        for(int i = 0 ; i < s.length() ; i++) {
            allLeft += s[i] == ')' ? -1 : 1;
            allRight += s[i] == '(' ? 1 : -1;
            if(allLeft < 0 ) return false;
            allRight = max(allRight,0);
        }
        return (allRight == 0);
    }
};