# Longest Valid Parentheses
有趣的找括弧配對最長子字串。題目分類在dp。

## 題目介紹及構想
- input
  - s(string)
    - 一堆括弧(只有小括弧"()")
- process
  - 處理字串找出配對
- output
  - result(int)
    - 回傳總共長度

括弧我之前玩過，就是用stack紀錄處理，可是要如何紀錄長度呢，我想到用一串bool陣列紀錄有無配對，之後再找出最長的部分。

## 開始
基本概念如下。
``` C++ =
    int longestValidParentheses(string s) {
        bool check[s.len]
        stack
        for(i = 0~s.len-1){
            init check[i]
            if(left)stack.push(i);
            else if(!empty){
                check[i,stack.top] = true;
                stack.pop();
            }
        }
        loop : find the max length of all true in check array.
        return maxlen;
    }
```

### RE
結果它好好的給我一個""結束一筆測資，就因為length = 0，導致陣列開啟爆掉。

### CE
心急吃不了熱豆腐，因為上一個錯誤，導致生氣的以為沒問題丟了，才發現新開的變數沒有宣告型態。

## 參考答案
這題被歸在hard並非難度很高，而是DP解不容易，我的做法其實不需要紀錄，用stack解決，這反而不是DP而是多此一舉。

### 驚人的DP公式
翻著參考解答看到這段，我也只能配服DP的做法
```C++ =
if (s.charAt(i - 1) == '(') {
    dp[i] = (i >= 2 ? dp[i - 2] : 0) + 2;
} else if (i - dp[i - 1] > 0 && s.charAt(i - dp[i - 1] - 1) == '(') {
    dp[i] = dp[i - 1] + ((i - dp[i - 1]) >= 2 ? dp[i - dp[i - 1] - 2] : 0) + 2;
}
maxans = Math.max(maxans, dp[i]);
```

這一段是當該前字元為')'時要做的處理。簡單分成兩部分。

- 跟前一個配對上
  - 就直接`dp[i-2] + 2`，看看有沒有更前面配對連接。
- 沒跟前一個配對上
  - 嘗試去尋找更前面的配對，就是去找`dp[i-1]`往前配對完的前一個`i-dp[i-1]-1`，而如果配對上了。就是加上跟前一個`dp[i-1]`跟配對上的前一個`dp[i-dp[i-1]-2]`加起來的值+2(配對本身)。

看完還是只能說這DP公式想法太棒了。

### stack的真正用法
我的stack只有push,pop的功能，其實當stack空的時候做處理就不需要額外開陣列存再檢查。

### 左右看一下
最精美的code大概是最後一個吧。雖然它是two-pass，但在空間使用上遠超過前兩個。它的stack是用兩個數字紀錄左右括弧數目而已。然後只要左邊開始掃過去算一次，再從右邊掃過去算一次，就解決了 ~~當然濃縮成one-pass也可以，可是就少了美感?~~ ，這方法時間複雜度跟DP和stack一樣，但空間複雜度卻是精美的constant，要不是這題歸類DP，不然這才是最佳解吧。

```C++ =
if(left)left ++;
else right ++;
if(left == right) max(len,right*2);
if(right > left) left = right = 0;
```
以上是掃過去的部分code，至於反向就只是在歸0那部分有差異。
## 感想
又是一道hard題。說時在，依照想法可能沒有hard，但其解答的多樣及難以想到的解決法，是有hard的狀況。
