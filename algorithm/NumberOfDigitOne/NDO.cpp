class Solution {
public:
    int countDigitOne(int n) {
        int len = 0;
        int t = n;
        int mod = 1;
        vector<int> dig;
        while(t) {
            dig.push_back(t%10);
            t /= 10;
            len++;
        }
        for(int i = 1 ; i < len ; i++)mod*=10;
        reverse(dig.begin(),dig.end());
        vector<int> countDig;
        int ten = 1;
        for(int i = 1 ; i <= 9 ;i++) {
            countDig.push_back(i*ten);
            ten *= 10;
        }
        int ans = 0;
        for(int i = 0 ; i < dig.size() ; i++) {
            ans += countDig[len-2-i] * dig[i];
            if(dig[i] > 1) {
                ans += mod;
            } else if(dig[i] == 1) {
                ans+= n%mod + 1;
            }
            mod /= 10;
        }
        return ans;
    }
};