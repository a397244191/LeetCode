class Solution {
private:
    int TopOp(stack<int>& s,stack<char>& op ){
        int second = s.top();
        s.pop();
        int first = s.top();
        s.pop();
        char opChar = op.top();
        op.pop();
        if(opChar == '+') return (first + second);
        else return (first - second);
    }
public:
    int calculate(string s) {
        int result = 0;
        if(s.empty()) return result;
        stack<int> number;
        stack<char> op;
        int num = 0;
        bool numContinue = false;
        for(int i = 0 ; i < s.length() ; i++){
            if(s[i] <= '9' && s[i] >= '0') {
                num = num*10+(int)(s[i]-'0');
                numContinue = true;
            } else if(numContinue){
                number.push(num);
                numContinue = false;
                num = 0;
                if(!op.empty() && op.top() != '(')
                    number.push(TopOp(number,op));
            }
            if(s[i]!= ')' && s[i] != ' ' && !(s[i] <= '9' && s[i] >= '0')) {
                op.push(s[i]);
            } else if(s[i] == ')'){
                op.pop();
                if(!op.empty() && op.top() != '(')
                    number.push(TopOp(number,op));
            }
        }
        if(numContinue){
            number.push(num);
            numContinue = false;
            num = 0;
            if(!op.empty() && op.top() != '(')
                number.push(TopOp(number,op));
        }
        return number.top();
        
    }
};