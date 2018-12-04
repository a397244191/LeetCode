class Solution {
public:
    bool judgePoint24(vector<int>& nums) {
        vector<bool> visit(4,false);
        for(int i = 0 ; i < 4 ; i++) visit[i] = false;
        vector<double> use;
        DFS(-1,nums,visit,use);
        
        for(int i = 0 ; i < allPair.size() ; i++) {
            if(calculate(allPair[i])) {
                //cout << i <<endl;
                return true;
            }
        }
        return false;
        
    }
    void DFS(int now,vector<int>& nums,vector<bool>& visit,vector<double>& use) {
        //cout << "!" <<endl;
        if(use.size() == 4) {
            allPair.push_back(use);
            return ;
        }
        if(now != -1 && visit[now]) return;
        if(now != -1){
            visit[now] = true;
            use.push_back(nums[now]);
        }
        for(int i = 0 ; i < 4 ; i++) {
            if(i != now) {
                DFS(i,nums,visit,use);
            }
        }
        if(now != -1){
            visit[now] = false;
            use.pop_back();
        }
    }
    
    bool calculate(vector<double>& num)
    {
        char useOp[4] = {'+','-','*','/'};
        for(int i = 0 ; i < 4 ;i++) {
            for(int j = 0 ; j < 4 ; j++){
                for(int k = 0 ; k < 4 ; k++){
                    //cout << '!' << endl;
                    vector<char>op{useOp[i],useOp[j],useOp[k]};
                    vector<bool> visit{false,false,false};
                    bool temp = check(-1,num,op,visit,0,0);
                    if(temp) {
                        //cout << op[0] << op[1] << op[2] << endl;
                        return true;
                    }
                }
            }
        }
        
        return false;
    }
    
    bool check(int now, vector<double>& num, vector<char>& op,vector<bool>&visit, int order,double ans){
        //cout << '?' << endl;
        if(order > 3 && abs(ans-24) < 0.00001) return true;
        else if(order > 3) return false;
        if(now != -1 && visit[now]) return false;
        bool ok = false;
        vector<double> before = num;
        if(now != -1){
            /*if(op[0] == '/' && op[1] == '/' && op[2] == '-'){
                cout << num[0] << ',' << num[1] << ',' << num[2] << ',' << num[3] << endl;
                cout << now << endl;
                cout << num[now] << op[now] << num[now+1] << endl;
            }*/
            visit[now] = true;
            num[now] = TwoPair(num[now],num[now+1],op[now]);
            num[now+1] = num[now];
            if(now == 0 && visit[1]) num[2] = num[0];
            else if(now == 2 && visit[1]) num[1] = num[3];
            ans = num[now];
        }
        for(int i = 0 ; i < 3 ; i++) {
            if(i != now) {
                ok |= check(i,num,op,visit,order+1,ans);
            }
        }
        
        num = before;
        if(now != -1) visit[now] = false;
        return ok;
    }
    
        
    double TwoPair(double a,double b, char op) {
        if(op == '+')
            return a + b;
        else if(op == '-')
            return a - b;
        else if(op == '*')
            return a * b;
        else if(b == 0) return 0;
        else return a / b;
    }
private :
    vector<vector<double>> allPair;
};