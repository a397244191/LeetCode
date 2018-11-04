# Longest Substring Without Repeating Characters
繼續復健(?)
## 題目介紹及構思
- input
  - s(string)
- process
  - check the length of substring without repeating characters
- output
  - int
    - the length of substring

 簡單用stack計算重複解決。

## 開始
主要記錄有兩個，有用到跟順序，所以我分成stack計路順序跟用array記錄使用與否。

```C++ =
int lengthOfLongestSubstring(string s)
{
    check[128] = {false}
    stack s, temp
    for(auto c : s)
    {
        if(check[c]){
            s.pop to temp(remove equal c and down),clear check
            temp pop to s, record check

        } else {
            s.push
            len++;
            maxS = max(maxS,len);
        }

    }
    return maxS;
}
```

一開始以為只有小寫字母，結果不是吃了一次WA。修過後AC了。

## 參考答案
看了參考答案，才發現更簡單的方式，直接用數字記錄，就能簡單的確認順序跟是否再substring裡。所以變成以下兩個判斷式。

```C++ =
if(check[c] < start) {
    //add in substring
    check[c] = i
    len ++;
} else {
    start = check[c] + 1;
    check[c] = i
    len = i - start + 1;
}
```

非常簡單還不用兩個stack倒來倒去的麻煩。

## 感想
比較簡單的題目，只要多思考點，就能產盛更精美跟優良的code。~~(應該啦)~~
