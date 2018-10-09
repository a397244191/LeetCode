# Online Stock Span
也許腦袋還不夠清醒，幸好這次題目簡單點。

## 題目介紹及構思
- input
  - StockSpanner
    - non
      - constructor
  - next
    - price(int)
      - the price of today
- process
  - calculate the span of the stock's price today
- output
  - StockSpanner
    - non
  - next
    - int
      - the stock span

似乎沒有複雜的關係，應該不會花太久。

## 開始
首先先對題目做分析，它是問，從今天往前，連續小於等於自己價格的票數，像是範例`100,80,60,70,60`這裡的70前面有一個比自己小所以是2(包含自己)，而後面60雖然有另一個60比自己小，但並沒有接連自己所以是1。

### 往回掃
最簡單的想法就是每個數都往回看看有幾個比自己小的，直到大於自己才計算完畢。但這樣時間複雜上有<a href="https://www.codecogs.com/eqnedit.php?latex=O(N^2)" target="_blank"><img src="https://latex.codecogs.com/gif.latex?O(N^2)" title="O(N^2)" /></a>，在考慮有沒有<a href="https://www.codecogs.com/eqnedit.php?latex=O(N)" target="_blank"><img src="https://latex.codecogs.com/gif.latex?O(N)" title="O(N)" /></a>可以解決的方式。

### 紀錄前一次
因為這記數是要包含自己往前連續，所以不會有跳過誰的可能，因此如果我記錄每個往前的數量，就可以跳過這個數量，這樣amortized analysis下來每個值被查看的次數會是const，所以時間上是linear，因此就決定記錄兩個陣列，prices跟spans。
```C++ = 
int next(int price){
    last = prices.size() - 1;
    prices.push_back(price);
    while(last >= 0 && price >= prices[last]) {
        last -= spans[last];
    }
    spans.push_back(prices.size() - last - 1);

    return spans.back();
}
```

沒什麼需要注意的，頂多就是第一個值沒人可查看會直接結束，第一次測試還因為這樣拿到RE ~~(沒submit就有結果真是好功能)~~ 。但在注意last值後解決AC了。

## 參考答案
其實想法一樣，不過不愧是放在tag上的詞，用stack果然才是更好的。想法一樣，只是我沒想到被跳過就沒了這件事情，還不斷擴大vector儲存，參考中使用stack直接拋棄留下最新的一個，不僅能省空間(大多情況)，也能減少不斷擴大陣列的時間。而還有一點差別是，有人用兩個stack，而另一個人是用pair一次存兩個而已。

## 感想
其實這題應該說是STL或容器的練習而已。偶爾練習自己的基本用法也是很不錯的。