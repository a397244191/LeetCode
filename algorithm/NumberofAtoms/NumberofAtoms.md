# Number of Atoms
跟昨天一樣類型，而且似乎更簡單，以前覺得複雜認為可能解不出來。

## 題目介紹及構思
- input
  - formula(string)
    - a chemical formula
- process
  - count the number of each atom
- output
  - ans(string)
    - a formula, we can see how many is each atom in this chemical formula.

基本上也就是解括弧的問題，而這次資訊上面比昨天精簡。

## 開始
一開始想說可以簡單一點，但發現因為()外有個數字要乘所以決定跟昨天一樣用recursive來解決。

### 主處理部分

問題不難，atoms名稱一定是大寫字母+小寫字母(也可能沒有)，另一種則是()包起來的是一個更小的化學式，而這兩者後面都會接上數字(若只有1則沒數字)。所以我的解決方法就是針對前面兩種狀態分別處理，再合流一起處理外部數字。

```C++ = 
map<string,int> func(string formula) {
    int i = 0;
    map<string,int> table;
    while(i < formula.length()){
        map<string,int> temp;
        s = i;// the pos of the substring begining 
        if(formula[i] == '('){
            int parestack = 0
            while(i < length) {//get the substring pos of sub formula
                if('(') parestack++;
                else if(')') parestack--;
                if(parestack == 0) break;
                i++;
            }
            temp = func(formula.substr(s+1,i-s-1));// remove the '(' and ')'
            i++;//move the end of this string
        }
        else if(formula[i] == 'A'~'Z'){
            i++;// remove the uppercase letter
            while(i < length && formula[i] == 'a' ~ 'z') i++//get the substring pos of sub formula
            temp[formula.substr(s,i-s)] = 1;// for having the same style to do count
        }
        //count the number
        substrpos = i;
        while(i < length && formula[i] == '0' ~ '9') i++;
        if(substrpos == i) value = 1;
        else value = stoi(formula.substr(s,i-s));
        
        while()table[Name] += temp[Name] * value;
        // push all element of temp into table 

    }
    return table;
}
```
先從最開始說起，對於有()的sub formula就是去記錄它的子字串位置，並且去除頭尾的'(',')'字元，將整段變簡潔再遞回處理，並將結果放進temp中。而單元素的部分，先處理它到底是什麼名稱，有無小寫的部分，並配合前面放進temp中，而預設的值就是1。

最後再根據剛剛的結果，將數字部分找出來(沒找到預設1)，最後去列出所有temp的元素並乘上數字加進table中。

### map轉回字串
但因為題目要求是回傳一段字串為簡化的化學式，所以最後還需要一一列出map元素來轉成字串。
```C++ = 
string countOfAtoms(string formula) {
    string ans = "";
    map<string,int> table = countAtoms(formula);
    while(){
        ans += Name;
        if(table[Name] != 1){
            ans += to_string(table[Name]);
        }
    }
    return ans;
}
```
這部分注意數量1以外沒有特別部分。

似乎沒有陷阱的情況下，我也有好好釐清每個部分的事情，所以簡單AC了。

## 參考答案
參考解答大致方法都是一樣的，用recursive或是stack解決，比較有趣的是Regular Expressions的解法。

它對字串分析出`"([A-Z][a-z]*)(\\d*)|(\\()|(\\))(\\d*)"`這樣的模式，切成名稱+數字、左括弧、右括弧+數字的三種狀態處理，用java內建的方法直接做到分割的部分，著實有趣。

# 感想
因為有了昨天經驗，所以發現用while帶替會寫自動加+的for會簡便，因為內層還能繼續跑些無用的部分而不需要把整個大迴圈下的都走一次(或是注意結束的i值)。