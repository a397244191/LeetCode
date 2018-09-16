class Solution {
public:
    bool isNumber(string s) {
        // delete white space
        int i = 0,len = s.length();
        while(i < len) {
            if(s[i] == ' ') i++;
            else break;
        }
        if(s[i] != '.' && s[i] != '+' && s[i] != '-' && (s[i]>'9' || s[i] < '0')) return false;
        bool dotExist = false;
        bool onlyDot = true;
        bool signUse = true;
        bool expExist = false;
        bool canExp = false;
        bool isNum = true;
        while(i < len) {
            if(s[i] == ' ') break;
            if(signUse && (s[i] == '+' || s[i] == '-')){//check sign
                signUse = false;
                isNum = false;
            }
            else if(s[i] >= '0' && s[i] <= '9'){// is number
                onlyDot = false;
                isNum = true;
                signUse = false;
                canExp = true;
            }
            else if(!dotExist && s[i] == '.'){
                dotExist = true;
                if(onlyDot && (i == len - 1 || (i < len - 1 && (s[i+1] < '0' || s[i+1] > '9')))) return false;
            }
            else if(canExp && !expExist && s[i] == 'e') {
                dotExist = true;
                expExist = true;
                signUse = true;
                isNum = false;
            }
            else return false;
            i ++;
        }
        while(i < len) {
            if(s[i] == ' ') i++;
            else return false;
        }
        return isNum;
    }
};