class Solution {
public:
    vector<string> generateParenthesis(int n) {
        string str = "";
        return rec(n,0,str);
    }
    vector<string> rec(int n,int s,string last) {
        vector<string> ans;
        if(s == 0 && n == 0) 
            ans.push_back(last);
        else {
            vector<string> addleft,addright;
            if(s < n) addleft = rec(n,s+1,last+"(");
            if(s > 0) addright = rec(n-1,s-1,last+")");
            ans = addleft;
            for(int i = 0 ; i < addright.size();i++) {
                ans.push_back(addright[i]);
            }
        }
        return ans;
    }
};