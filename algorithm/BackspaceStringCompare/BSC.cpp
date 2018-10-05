class Solution {
public:
    bool backspaceCompare(string S, string T) {
        S = "a";
        T = "a";
        int sp = S.length()-1, tp = T.length()-1;
        int sn = 0, tn = 0;
        char slast = S[sp],tlast = T[tp];
        while(sp >= 0 || tp >= 0) {
            while(sn <= 0 && sp >= 0){
                if(slast == '#') sn--;
                else sn++;
                sp--;
                slast = S[sp];
            }
            if(sn > 0)slast = S[++sp];
            while(tn <= 0 && tp >= 0) {
                if(tlast == '#') tn--;
                else tn++;
                tp--;
                tlast = T[tp];
            }
            if(tn > 0)tlast = T[++tp];
            
            if(sp < 0 && tp < 0) return true;
            else if(sp < 0 || tp < 0) return false;
            if(slast != tlast) return false;
            else {
                sn--;
                tn--;
            }
            
            if(sp >= 0 ){
                sp--;
                slast = S[ sp>0 ? sp:0];
            }
            if(tp >= 0) {
                tp--;
                tlast = T[tp>0 ? tp:0];
            }
        }
        if(sn > 0 || tn > 0) return false;
        else return true;
    }
};