class Solution {
public:
    int longestValidParentheses(string s) {
        bool havePair[s.length()] = {false};
        stack<int> leftP;
        
        for(int i = 0 ; i < s.length() ; i++){
            havePair[i] = false;
            if(s[i] == '(') leftP.push(i);
            else if(!leftP.empty()){ 
                int first = leftP.top();
                leftP.pop();
                havePair[i] = true;
                havePair[first] = true;
            }
        }
        int maxLen = 0,tempLen = 0;
        for(int i = 0 ; i < s.length() ; i++){
            if(havePair[i]) tempLen++;
            else tempLen = 0;
            maxLen = max(maxLen,tempLen);
        }
        
            
        return maxLen;
    }
};