# Generate Parentheses
畫面改版了，然後變智障了。

## 題目介紹及構思
- input
  - n(int)
    - the number of pairs of parentheses
- process
  - generate the all combinations by n pairs of parentheses 
- output
  - vector< string>
    - all combinations

因為要把組合印出來，所以沒有什麼好優化的，就列出來。

## 開始
想說就很簡單的recursive，字串一次增加一個，加上兩個數字確保數量在n以下，及括弧是正確的。

```C++ =
vector<string> rec(int n,int s, string str) {
    if(n == s == 0) return vector<string>{str};
    if(s < n) addL = rec(n,s+1,str+"(");
    if(s > 0) addR = rec(n-1,s-1,str+")");
    return addL + addR ;
}
```
簡單的判斷，當我可以增加左半部就增加'('，當我可以補上右半部就增加')'，而如果n跟s都為0就表示我們用完了，可以回傳答案。只要s不小於0就不會是錯誤的組合，而s小於n就不用用超過n組。

不過因為改版我眼花看錯，以為他的output就是我的答案，然後以為全對，其實我根本忘了加走到長度滿的時候回傳，結果我的答案是空的吃了WA。不過補上去就AC了，看來只是我眼花。

## 參考答案
方法基本相同，不過我用遞回時是用回傳來接收答案，但其實可以直接把vector丟下去自己加，會更快速點。

## 感想
又忙了幾天，寫寫簡單題目當作休閒放鬆也不錯?
