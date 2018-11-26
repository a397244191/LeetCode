# Valid Parenthesis String
這題只能怪我太笨。
## 題目介紹及構思
- input
  - s(string)
    -  a string containing only three types of characters: '(', ')' and '*'.
- process
  - check the string is valid
  - '*' can replace to '(', ')', or no char
- output
  - bool
    - return true, if valid

搞了半天，除了沒想到線性解法外，竟然沒注意到測資很小。

## 開始
因為受不了解法，跑去偷看答案，整個被超簡單想法弄清醒了。導致回不去了。這裡來敘述我很想在線性解決的想法吧。

### 數字記錄
一開始想法很簡單，記錄'*'的位置左邊有沒有左括弧，有的存起來去跟左配對，沒有就存到另一個去跟右配對，結果就錯了。

這裡出現一個測資是，所有'*'可以跟左括弧配對但其實會導致右括弧跟左括弧數量一樣位置相反的情況。

### 一個個記錄
改用stack去存*，當左邊被用光時就去當跟右邊配對的*。

結果有測資被拿去跟左括弧配對才是對的，導致錯誤。

### 多記錄
這次決定多做記錄，當左邊配對完後發現還有左括弧(表示在這配對群中)就需要先配對*當右括弧用。

結果才醒悟出一個測資，'*'是要可以當空字元的。

### 複雜形紀錄法
紀錄*被拿去配對的點時左括弧數量跟一些值，最後計算值到確定*比)數量多而判斷正確。

結果出現許多瑕疵而失敗。

### 最終參考
因為受不了一堆方法失敗了，偷偷看了解答，才發現原來很簡單。但因為太簡單的解法了，導致無法再想別的方法。

總之藉由解答簡單解法AC了。

## 參考答案
畢竟是參考來的，解法就寫在這。這裡有三種解法，暴力、DP、Greedy。

### 暴力
這裡不難，就是當遇到'*'時去遞回三種狀況，不過因為測資長有100，所以會導致TLE。

### DP
這是一個space是<a href="https://www.codecogs.com/eqnedit.php?latex=O(N^2)" target="_blank"><img src="https://latex.codecogs.com/gif.latex?O(N^2)" title="O(N^2)" /></a>，而time是<a href="https://www.codecogs.com/eqnedit.php?latex=O(N^3)" target="_blank"><img src="https://latex.codecogs.com/gif.latex?O(N^3)" title="O(N^3)" /></a>的解法。

簡單說就是從長度最短時開始判斷T or F，然後不斷增長，藉由被配對到的'('跟')'來做區分，當整段除了這對配對外都是配對成功時即為真。因為要從長度、起點、跟起點配對位置，三個考量，所以是<a href="https://www.codecogs.com/eqnedit.php?latex=O(N^3)" target="_blank"><img src="https://latex.codecogs.com/gif.latex?O(N^3)" title="O(N^3)" /></a>解。

### Greedy
我就是被這簡單的想法給打醒的，因為太簡單了，導致我都不知道一開始我在煩惱啥。

想法簡單，分兩個去計算，一個是'*'全變'('，另一組全變')'。

1. 當全變'('時，只要變成負的(')'過多)，即為false。
2. 而當全變')'時，所有變負情況都歸0(因為全變'('沒有結束，所以是可以將前半部所有'*'改成'('來解決變負情況)，而當最後值是大於0時('('過多)則為false。

當上述兩件false沒發生即為true。整個複雜度為<a href="https://www.codecogs.com/eqnedit.php?latex=O(N)" target="_blank"><img src="https://latex.codecogs.com/gif.latex?O(N)" title="O(N)" /></a>。

## 感想
想方設法的去降低時間複雜，除了沒解出正確方式外，也沒注意到其實測資允許一些範圍來去解決。這都是我的疏失。提醒我除了思考題目外還需要眼界大一點，來發現各種解法的路。