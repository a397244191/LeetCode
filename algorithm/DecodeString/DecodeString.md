# Decode String

## 題目介紹及構思
- input
  - s(string)
    - a encode string
- process
  - decode this string, like 3[a] > aaa, 3[a2[b]] > abbabbabb
- output
  - string
    - the decode string

印象之前有解過類似題目。

## 開始
這題目基本上就是兩種狀況。

1. 直接是字串，像 a
2. 有重複次數，像 3[a]

而當有被重複字串中有另一組被重複字串時，是需要展開的，所以考慮用recursive來分解它。

``` C++ =

if(s[i] is number)
    count the repeate number
else if(s[i] is '['){
    while(go to the partner of pair);
    use = decode(s.substr());
    while(rep--) ans += use;
}
else ans += s[i]

```

大致判斷式就用三種狀況來解決。如果是數字，因為沒有保證數字是小於10，所以要紀錄數字。而遇到'['時，就去找配對的']'將中間recursive下去。而都不是的情況(因為']'會被處理過去，所以不用理這狀況)就直接補上字串。

本來打算測試一下發現，因為是用recursive所以不能直接在function直接改字串，所以直接丟了看看，一次AC。

## 參考答案
因為這次題目屬於基本題，解法就沒什麼特別的變化。

## 感想
最近都不想花太多時間在解題上。所以都只挑了些簡單的基礎題，維持解題的手感。