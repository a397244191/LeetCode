class Solution {
public:
    int lastRemaining(int n) {
    /*
        int t = 62;
        vector<int> a;
        for(int i = 1 ; i <= t ; i++) a.push_back(i);
        while(a.size() > 1) {
            for(int i = 0 ; i < a.size() ; i++) {
                a.erase(a.begin()+i);
            }
            if(a.size() == 1) break;
            for(int i = a.size() - 1 ; i >= 0 ; i-= 2) {
                a.erase(a.begin()+i);
            }
        }
        return a[0];
    */
        //n = 64;
        bool flag = false, fromHead = true;
        int ans = 0, two = 1;
        while(n) {
            bool add = false;
            if((!(n%2) && !fromHead) || n == 1) add = true;
            if(flag) add ^= true;
            //cout << flag << ',' << add << ',' << two << endl;
            if(add) ans += two;
            two *= 2;
            if(add) flag = true;
            n /= 2;
            fromHead ^= true;
        }
        return ans;
    }
};