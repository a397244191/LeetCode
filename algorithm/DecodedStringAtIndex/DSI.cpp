class Solution {
public:
    string decodeAtIndex(string S, int K) {
        vector<string> str;
        vector<long long int> repeateT;
        string temp(S.substr(0,1));
        long long int rep = 1;
        long long int total = 0;
        for(int i = 1 ; i < S.length() ; i++) {
            if(S[i] >= '0' && S[i] <= '9'){
                rep *= (S[i] - '0');
                if(!temp.empty()){
                    str.push_back(temp);
                    temp = "";
                }
                
            } else{
                if(temp.empty()){
                    repeateT.push_back(rep);
                    rep = 1;
                }
                temp += S[i];
                
            }
        }
        if(!temp.empty()) str.push_back(temp);
        if(repeateT.size() < str.size()) repeateT.push_back(rep);
        
        vector<long long int> strSum;
        strSum.push_back(str[0].length());
        for(int i = 1 ; i < str.size() ; i++) {
            strSum.push_back(strSum.back() * repeateT[i-1] + str[i].length());
        }
        for(int i = strSum.size() - 1 ; i >= 0;) {
            K = (K-1) % strSum[i] + 1;
            if(K > strSum[i] - str[i].length()){
                return str[i].substr(K - (strSum[i] - str[i].length()) - 1,1);
            } else {
                i--;    
            }
            
        }
        string ans = "Error";
        return ans;
    }
};