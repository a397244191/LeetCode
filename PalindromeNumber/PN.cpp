class Solution {
public:
    bool isPalindrome(int x) {
        if(x < 0) return false;
        int head = 1,tail = 1;
        while(head < 1000000000) {
            if(x/(head*10) == 0) break;
            head*=10;
        }
        while(head > tail){
            if((x/head)%10 != (x/tail)%10) return false;
            head/=10;
            tail*=10;
        }
        return true;
    }
};