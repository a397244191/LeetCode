# Basic Calculator
一個基本的字串處理做成只有加減的計算機
## 題目介紹及構想
- input
  - s(string)
    - 一段運算，一定是合法的。
- process
  - 處理s的運算內容
- output
  - result(int)
    - s處理完的結果。

就是一路看過去，遇到數字存進stack，遇到符號做對應事情。

## 開始
因為只有加減法，所以除了遇到`()`外都可以直接運算。

```C++
    int TopOp(stack<int>& s,stack<char>& op);// do "s.secondTop() op s.top()"
    int calculate(string s){
        stack<int> number;
        stack<char> op;
        int num = 0;
        bool numC = false;// check we have a number is running
        while(s[i],0<=i<s.length){
            if(s[i] is number){
                num = num*10 + s[i]-'0';
                numC = true;
            } else if(numC){
                number.push(num);
                numC = false;
                if(op.top is '+' or '-'){
                    number.push(TopOp(number,op));
                }
            }
            if(s[i]!= ')' && s[i] != ' ' && !(s[i] <= '9' && s[i] >= '0')) {
                op.push(s[i]);
            } else if(s[i] == ')'){
                op.pop();// pop the '('
                if(!op.empty() && op.top() != '(')
                    number.push(TopOp(number,op));
            }
        }
        
        if(numContinue){// final char is number, so we need to do final operation
            number.push(num);
            numContinue = false;
            num = 0;
            if(!op.empty() && op.top() != '(')
                number.push(TopOp(number,op));
        })
        return number.top();
    }
```

因為沒有乘除優先問題，所以可以很簡單的分析。一次AC。

## 參考答案
參考答案是沒有的，可是看到一個4ms的code後覺得很有趣。因為他是用recursive來用做()的處理，所以想法比我的還要精簡，而且又對於一開始的字串尾端加上')'來防止最後是數字的發生。看完只有佩服能想出這樣做法。整段code用switch case完成，非常精簡有條理。

## 感想
簡單運算跟簡單處理，這次很小心的顧及到了所有小細節，並沒有遇上困難，算是好的結局。