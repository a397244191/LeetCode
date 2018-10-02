# Find And Replace in String
小小的字串練習

## 題目介紹及構思
- input
  - S(string)
    - original string
  - indexes(vector< int>)
    - replace position
  - sources(vector< string>)
    - replace from string
  - targets(vector< string>)
    - replace to string
- process
  - replace all string which is the same in original
- output
  - result(string)
    - a string that has been replaced.

替換字串而已。

## 開始
想法很簡單，就是一直掃過去，把該換的都換一遍。

### 掃字串
我一開始很天真的認為indexes是照順序的。所以就對indexes做一次交換中間補進去。

```C++ = 
string findReplaceString(string S, vector<int>& indexes, vector<string>& sources, vector<string>& targets) {
    for(i = 0 ~ indexes.size()){
        output += S.substr(last,indexes[i] - last);
        replace = true;
        for(j = 0 ~ sources[i].length()){
            if( not same) replace = false;
        }
        if(replace) {
            output += target[i];
            last = indexes[i];
        }
    }
    output += S.substr(last,S.length()-last);

    return output
}
```
看起來很完美了。

### 問題發現
我這次很小心的思考了一下，想到之前失足的經驗，決定仔細看看內文，indexes沒有sort啊!我整段都沒有看到他表示被sort好了。好險我有發現。

### sort不容易
可是這次元素中，它把東西拆成三部件indexes,sources,targets，用sort還要自己改寫也不容易呀。只好想想別的方法。

### 紀錄
這次很好的是S的長度只有1000，似乎可以紀錄值來用。所以開了一個S長的陣列，全部設-1，當遇到改變時紀錄被改變字串在targets的index。全部結束，再去一一替換。而因為題目有保證被交換的部分重疊是不可能的，所以沒有太大問題。

```C++ = 
string findReplaceString(string S, vector<int>& indexes, vector<string>& sources, vector<string>& targets) {
    rep(S.length(),-1);
        
    for(i = 0 ~ indexes.size()) {
        if(S.substr == sources[i] ) rep[indexes[i]] = i;
    }
        
    for(i = 0 ~ S.length()) {
        if(rep[i] >= 0) {
            output += targets[rep[i]];
            i += sources[rep[i]].length() - 1;// jump the char that has been replace
        }else {
            output += S[i];
        }
    }
    return output;
}
```

### MLE
這是自己測試時跑出來的，我一直百思不得其解原因，我不是才多用一點就跑出來。而原來，其實replace的loop中，i值變化寫錯了，導致無窮迴圈下output值不斷變常導致。

改完問題就AC了，這次沒有不小心出錯直接submit的狀況，應該算是一次AC吧。

## 參考答案
參考答案基本上跟我的想法一樣，就不提了。但看到一個比較有趣的做法真的是直接拿去sort。某意義上挺厲害的。

## 感想
這次有看清題目，有好好確認。算是處理狀況上表現不錯吧。
