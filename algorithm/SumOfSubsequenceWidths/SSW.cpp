class Solution {
public:
    int sumSubseqWidths(vector<int>& A) {
        int sum = 0;
        const int MOD = 1000000007;
        
        sort(A.begin(),A.end());

        int powTwo = 1;
        int left = 0, right = A.size() - 1;
        int len = A.size() - 2;
        int sub = 0;
        while(left < A.size() && right >= 0) {
            sub = (sub + A[right] - A[left]) % MOD;
            long long int add = ((long long int)sub * powTwo) % MOD;
            sum += add;
            
            sum %= MOD;
            left++;
            right--;
            len--;
            powTwo = (powTwo<<1) % MOD;
        }
        
        return sum;
    }
};