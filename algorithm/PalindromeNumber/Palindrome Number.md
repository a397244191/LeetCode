# Palindrome Number
本來解決hard就不想打了啦。

## 題目介紹及構想
- input
  - x(int)
    - 判斷的數字
- process
  - 判斷是否是palindrome number
- output
  - output(bool)
    -結果是否為palinderome number

他說不用string，最簡單想法是stack倒過去一半解決。

## 開始
想著用stack來解決，發現一些狀況，最後是這方式。
```C++ =
    bool isPalindrome(int x) {
        if(x<0) return false;
        find head
        while(head > tail){
            if(head != tail) return false;
        }
        return true;
    }
```

### MLE
我還是第一次親眼見到這東西，算一算stack存最多10個int然後長度一個int，竟然炸memory!?雖然是local確認沒有submit。

### WA
修改後，最後決定用兩個變數來判斷，結果head的部分因為超過<a href="https://www.codecogs.com/eqnedit.php?latex=10^{9}" target="_blank"><img src="https://latex.codecogs.com/gif.latex?10^{9}" title="10^{9}" /></a>所以炸了。改變一下find head的部分解決了。

### 參考答案
發現很有趣的想法是，就是做數字反轉，然後將結果跟input比較就能解決了，雖然迴圈次數差不多，可是Runtime上差距很大。只能說，怎麼沒想到呢，其實我還是把它當作string的想法解決吧。

## 感想
解決了hard還以為有點自信了，結果自己還是粗心大意的在小細節跌倒了。