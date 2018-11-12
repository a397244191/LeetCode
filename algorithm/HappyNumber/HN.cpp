class Solution {
public:
    bool isHappy(int n) {
        unordered_set<int> visit;
        //n = 4;
        while(visit.find(n) == visit.end()){
            visit.insert(n);
            int num = 0;
            while(n) {
                int mod = n%10;
                num += mod*mod;
                n/=10;
            }
            n = num;
        }
        //cout << n;
        if(n== 1) return true;
        else return false;
    }
};