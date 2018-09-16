class Solution {
public:
    int reverse(int x) {
        if(x == -2147483648) return 0;
        int result = 0;
        bool flag = x < 0;
        if(flag) x *= -1;
        bool over = false;
        while(x) {
            cout << result;
            if(result > 214748364) over = true;
            result = result * 10 + x % 10;
            x /= 10;
        }
        
        if(flag) result *= -1;
        if(over) return 0;
        return result;
    }
};