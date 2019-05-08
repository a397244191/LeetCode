class Solution {
public:
    double myPow(double x, int n) {
        long long t = n;
        if(t < 0) {
            t *= -1;
            x = 1.0/x;
        }
        double ans = 1;
        while(t) {
            if(t%2) ans *= x;
            x *= x;
            t>>=1;
        }
        return ans;
    }
};