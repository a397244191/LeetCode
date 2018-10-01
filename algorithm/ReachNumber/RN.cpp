class Solution {
public:
    int reachNumber(int target) {
        target = abs(target);
        int number = 1;
        int step = 1;
        int endNum = target / 2;
        bool tarStatus = (target % 2 == 1),status = true;// true is odd
        int check = 0;
        int add = 1;
        for(step = 1 ; step < 80000 ; step++){
            if(endNum < number && !(tarStatus ^ status)) break;
            else number = number + add;
            check++;
            if(!(step%2)) status ^= true;
            if(check == 4){
                add ++;
                check = 0;
            } else if(check == 1) add ++;
        }
        
        return step;
    }
};