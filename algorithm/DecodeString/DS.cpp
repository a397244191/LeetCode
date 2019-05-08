class Solution {
public:
    string decodeString(string s) {
        string use;
        string ans;
        int rep = 0;
        //cout << s << endl;
        //if(s.empty() || s[0] > '9' || s[0] < '0') return s;
        for(int i = 0 ; i < s.size() ; i++) {
            //cout << s[i] << endl;
            if(s[i] >= '0' && s[i] <= '9') {
                rep = rep*10 + s[i] - '0';
            } else if(s[i] == '[') {
                int pos = i;
                int n = 1;
                while(n) {
                    i++;
                    if(s[i] == '[')n++;
                    else if(s[i] == ']') n--;
                }

                use = decodeString(s.substr(pos+1,i-pos-1));
                while(rep--) {
                    //cout << rep;
                    ans+=use;
                }
                rep++;
            } else {
                ans += s[i];
            }
        }
        return ans;
    }
};