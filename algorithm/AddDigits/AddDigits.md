# Add Digits
沒啥時間，找簡單題目當作例行公事做。

## 題目介紹及構思
- input
  - num(int)
- process
  - repeatedly add all its digits until the result has only one digit.
- output
  - ans(int)

他希望不要用迴圈或是遞回解決。

## 開始
其實很簡單，就是取9的餘數。不過似乎最近忙起來了，所以沒想清楚直接submit了，錯在9%9會等於0的狀況。

這WA吃的很突然，不過之前常遇到的狀況，就是做減1mod完再加1就可以，全都數學式無邏輯解法誕生。

```C++ =
    int addDigits(int num) {
        return (num-1) % 9 + 1;
    }
```

## 參考答案
這直觀上還是用迴圈或遞回可以明確模擬出流程，不過這纇基本題型，就是找出規律就可以解決，而這規律十分簡單。

基本上討論區答案也就這樣，所以沒有特別參考。

# 感想
這陣子開始有事情做，想放掉它，可是畢竟最初是為了養成習慣性的coding跟git push，所以還是硬來做個題目，等到適應日子後再來提高難度吧。