class Solution {
public:
    int bestRotation(vector<int>& A) {
        int len = A.size();
        vector<int> rotate(A.size(),0);
        for(int i = 0 ; i < len ; i++){
            int beginR = (i + 1)%len;
            int endR = ((beginR + ((len - 1) - A[i])) + 1)%len;
            if(beginR != endR){
                rotate[beginR] --;
                rotate[endR]++;
            }
            
        }
        
        int minR = 0, minC = len,now = 0;
        
        for(int i = 0 ; i < len ; i++) {
            now += rotate[i];
            if(minC > now) {
                minC = now;
                minR = i;
            }
        }
        
        return minR;
    }
};