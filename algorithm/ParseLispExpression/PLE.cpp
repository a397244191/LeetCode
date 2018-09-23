class Solution {
public:
    int evaluate(string expression) {
        map<string,int> table;
        return expRecursive(expression,table);
    }
private:
    map<string,int> valueTable;
    int expRecursive(string expression,map<string,int>& table) {
        map<string,int> insideTable = table;
        int ans = 0;
        if(expression[0] != '(')
        {
            if(insideTable.find(expression)!= insideTable.end()){
                return insideTable[expression];
            }
            int ind = 0;
            bool neg = false;
            if(expression[ind] == '-'){
                neg = true;
                ind = 1;
            }
            for(ind ; ind < expression.length() ; ind++)
                if(expression[ind] >= '0' && expression[ind] <= '9')
                    ans = ans*10 + (expression[ind] - '0');
            return ans * (neg?(-1):1);
        }
        else if(expression[1] == 'a' || expression[1] == 'm'){
            bool value1Ok = false;
            int substrbegin = 5;
            int strbegin = 5;
            if(expression[1] == 'm') substrbegin = strbegin = 6;
            int value1=0,value2=0;
            int parestack = 0;
            for(int i = strbegin ; i < expression.length() ; i++) {
                if(expression[i] == '(') parestack++;
                else if(expression[i] == ')') parestack--;
                if(expression[i] == ')' && parestack == 0){
                    if(!value1Ok){
                        value1 = expRecursive(expression.substr(substrbegin,i-substrbegin+1),insideTable);
                        value1Ok = true;
                    }    
                    else {
                        value2 = expRecursive(expression.substr(substrbegin,i-substrbegin+1),insideTable);
                        break;
                    }
                    
                    substrbegin = i+2;
                    i++;
                }
                else if((expression[i] == ' ' || expression[i] == ')') && parestack <= 0){
                    if(!value1Ok){
                        value1 = expRecursive(expression.substr(substrbegin,i-substrbegin),insideTable);
                        value1Ok = true;
                    }    
                    else {
                        value2 = expRecursive(expression.substr(substrbegin,i-substrbegin),insideTable);
                        break;
                    }
                    substrbegin = i+1;
                }
            }
            return ((expression[1] == 'a') ? (value1 + value2) : (value1 * value2)); 
        }
        else if(expression[1] == 'l'){
            bool isName = true;
            string Name = "";
            int substrbegin = 5;
            int parestack = 0;
            int value = 0;
            for(int i = 5 ; i < expression.length() ; i++){
                if(expression[i] == '(') parestack++;
                if(expression[i] == ')') parestack--;
                if(expression[i] == ')' && parestack == 0){
                    if(isName){
                        Name = expression.substr(substrbegin,i-substrbegin+1);
                        isName = false;
                    }
                    else {
                        value = expRecursive(expression.substr(substrbegin,i-substrbegin+1),insideTable);
                        insideTable[Name] = value;
                        isName = true;
                    }
                    substrbegin = i+2;
                    i ++;
                }
                else if((expression[i] == ' ' || expression[i] == ')') && parestack <= 0){
                    if(isName){
                        Name = expression.substr(substrbegin,i-substrbegin);
                        isName = false;
                    }
                    else {
                        value = expRecursive(expression.substr(substrbegin,i-substrbegin),insideTable);
                        insideTable[Name] = value;
                        isName = true;
                    }
                    substrbegin = i+1;
                    if(expression[i] == ')') break;
                }
            }
            return expRecursive(Name,insideTable);
        }
    }
};