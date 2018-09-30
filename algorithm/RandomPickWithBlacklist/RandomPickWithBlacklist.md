# Random Pick with Blacklist
能力未及，受益匪淺

## 題目介紹及構思
- input
  - Solution
    - N(int)
      - range is `[0,N)`
      - <a href="https://www.codecogs.com/eqnedit.php?latex=0&space;<&space;N&space;\le&space;1000000000" target="_blank"><img src="https://latex.codecogs.com/gif.latex?0&space;<&space;N&space;\le&space;1000000000" title="0 < N \le 1000000000" /></a>
    - blacklist(vector< int>)
      - rand number is not in blacklist
      - <a href="https://www.codecogs.com/eqnedit.php?latex=0\le&space;length&space;\le&space;min(N,100000)" target="_blank"><img src="https://latex.codecogs.com/gif.latex?0\le&space;length&space;\le&space;min(N,100000)" title="0\le length \le min(N,100000)" /></a>
  - pick
    - rand a number not in blacklist
- process
  - do some pick
- output
  - pick
    - randNum(int)
      - a number is in 0~N-1, and not in blacklist

隨手點進來，想不到什麼好方法。 ~~(可是還是手賤嘗試了)~~

畢竟平常沒做過random題目，總之試試看吧。

## 開始
其實沒有想太多，想說就是對blacklist做search，不在裡面就是合法的。

### set
總之先用set試試看吧。全部丟進set判斷需要<a href="https://www.codecogs.com/eqnedit.php?latex=O(logB)" target="_blank"><img src="https://latex.codecogs.com/gif.latex?O(logB)" title="O(logB)" /></a>(B是blacklist的長度)。

結果它如同理所當然的還了一個TLE給我。

### 偷看討論的開始
瞄了兩眼，其實有考慮過unordered_set的用法，畢竟它平均複雜度是const time。結果用了還是TLE。認定這題還是觀摩別人的想法好了。

因為後面基本都是來自參考別人，所以都丟在參考答案裡吧。

## 參考答案
對於random這件事充滿不明白的感覺，只好來觀摩了。

### 機率
之後認真的看了一個用unordered_set的想法，才明白我TLE的原因。

#### whitelist
當B > N/2時，這時候有兩件事情可以知道，我們有足夠空間開出一個whitelist，裡面是所有不在blacklist的值，而直接去random它的index拿到值會比去查在不在blacklist快。

#### blacklist
當B <= N/2時，就是對unordered_set去搜尋是否存在，而這時候，可以保證找到不在裡面的random機率是比0.5高的。

#### TLE原因
我認為主要原因應該那個機率問題，因為若是我的blacklist幾乎跟範圍一樣大時，我有高達9成多的機會就是一直loop，而random最不好的地方就是，是存在一個機會，你永遠無法取得你要的值的。而這機會因為我沒有做其他準備而被放大了。

### binary search
看到這個我想說，這不是跟set異曲同工嘛?都是<a href="https://www.codecogs.com/eqnedit.php?latex=O(logB)" target="_blank"><img src="https://latex.codecogs.com/gif.latex?O(logB)" title="O(logB)" /></a>時間，可是引起我好奇的是，它對whitelist做binary search。

#### Solution(N,blacklist)
對blacklist做sort，然後開始取出所有不在blacklist的「範圍」。沒錯，是範圍，所以這個陣列儲存是`pair<int,int>`的樣子。

之後建立一個陣列，裡面是每個區間範圍的加總，用說的有點難想像，舉個例子。

若前面表是`whitelist = {(0,2),(4,8),(11,17)}`，則會獲得`rangeAcc = {3,8,15}`，類似index範圍的概念，第一個區間有3個值，所以index值最多會是3，第二個區間有5個，而從3開始加上，所有index上限是8，然後有7個，index上限是15這樣。(index從1開始)。

之後去紀錄最後一個的值(上面範例是15)為range。

#### pick
接下來跟我不同的地方(應該說從頭到尾方法都不同)，它不用跑loop去重複random，因為一次random就能解決問題。

對於random的值，範圍令他介於1~range之間(r = rand()%range + 1)。然後用lower_bound去尋找它在第幾個區間(lower_bound(rangeAcc,r) - rangeAcc.begin)的index。

這時候`r - rangeAcc[index - 1] - 1`(-1是因為要讓index起始為0，而index = 0的情況`rangeAcc[index - 1]`就是 0)就是它在`whitelist[index]`的index ~~(詞窮，只有這個用詞)~~，所以加上`whitelist[index].first`後回傳的值就是在whitelist第r個值。

#### +1-1是門學問
因為我有點在理解後自己嘗試，所以一開始以為range要包含最後一個，所以要+1結果random出來的值就莫名超過N了，這才發現範圍應該是range個，而非到range，又因為只知道-1不知道為啥mod時要+1又吃了WA。

其實這裡的+1是為了可以找到正確的index，因為如果沒有+1會發生你的值是在後一段的頭，但卻被歸類在前一段而超出前一段範圍出錯。

example:

利用前面的範例`whitelist = {(0,2),(4,8),(11,17)}`，`rangeAcc = {3,8,15}`，當r = 3 時，因為沒有+1-1所以被找出是`rangeAcc[0]`，但其實3是在(4,8)中，所以直接算會是0+3 = 3不在whitelist中。如果純-1就會發生0變成-1的慘劇，而純+1就會發生18這個不在`[0,N)`的值出現的兩難，而兩者皆用就能避免者也能避免後者。

## 感想
這問題與其說我不會解決，不如說沒碰過這類型的題目，這不能單純的用複雜度去思考，還要理解random特性與機率的關係才能好好釐清問題。雖然解出來了，但不是完全自己想有點慚愧。 ~~(最近似乎一直偷看答案，明天還是去解簡單題提升自信好了)~~ 