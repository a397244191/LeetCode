class Solution {
public:
    vector<vector<int>> palindromePairs(vector<string>& words) {
        map<string,int> m;
        vector<vector<int>> result;
        //build hash map
        for(int i = 0  ; i < words.size() ; i++){
            string keyword = words[i];
            reverse(keyword.begin(),keyword.end());
            m[keyword] = i;
        }
        for(int i = 0 ; i < words.size() ; i++){
            for(int j = 0 ; j <= words[i].length() ; j ++) {
                string left = words[i].substr(0,j);
                string right = words[i].substr(j,words[i].length() - j);
                
                if(m.find(left) != m.end() && isPalindrome(right) && m[left] != i)
                    result.push_back(vector<int>{i,m[left]});
                if(m.find(right) != m.end() && left.length() > 0 && isPalindrome(left) && m[right] != i)
                    result.push_back(vector<int>{m[right],i});
            }
        }
        return result;
    }
    bool isPalindrome(string s){
        int l = 0,r = s.length()-1;
        while(l < r) {
            if(s[l] != s[r]) return false;
            l++;
            r--;
        }
        return true;
    }
};