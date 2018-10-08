# Race Car
今天腦袋怪怪的，一直在死胡同打轉。

## 題目介紹及構思
- input
  - target(int)
    - want to go to target
- process
  - move car by a speed
- output
  - int
    - how many instructions we use.

感覺可以跟上次那個每次增加1步的有一樣方法。

## 開始
依照上次經驗，我以為這次題目應該差不多，不會太難的。操作是A前進R轉反向，每次前進都會加快速度(init speed = 1, every A, go speed before speed * 2)，而每次轉向速度都會初始回1。

### 負方向
這次target都是正的，但它其實允許往負的方向走，但因為初始方向向正，所以往負方向需要先做一次R的動作，不僅沒意義也浪費一次操作。所以就不討論一開始就往負走。

### 走過頭再轉
最開始想法跟之前一樣，總之先走過頭再走回來呢?因為這次轉向後速度初始化，所以立馬打破簡單的想法。因為target = 4，用過頭再轉的方法，會是1->3->7->7(R)->6->4，但其實再3的地方連續轉兩次1->3->3(R)->3(R)->4，可以更快抵達。

#### 為何
這時思考為何不能走過頭。其實就是因為R重置了速度，且RR跟AR的步數一樣，因此較近的可以更快抵達。

### 步數指數增長
因為每次移動是指數增長，所以A，AA，AAA能抵達的地方都會是指數增加，因此每次多個A，其中的格子數剛好等於前一個A的長度。

![](https://i.imgur.com/uGaYVg6.png)

如上圖，可以看到從AA(3)走到AAA(7)，剛好等於從(0)走到AA(3)的移動距離。

#### 能做啥
因為每次R後都會初始速度，所以AA(3)到AAA(7)之間的就可以利用(0)到AA(3)的值，去做處理。

### 複製貼上
因為上面想法，只要在<a href="https://www.codecogs.com/eqnedit.php?latex=A_k&space;\rightarrow&space;A_{k&plus;1}" target="_blank"><img src="https://latex.codecogs.com/gif.latex?A_k&space;\rightarrow&space;A_{k&plus;1}" title="A_k \rightarrow A_{k+1}" /></a>(<a href="https://www.codecogs.com/eqnedit.php?latex=A_k" target="_blank"><img src="https://latex.codecogs.com/gif.latex?A_k" title="A_k" /></a>是連續k個A)放入遞增跟遞減的<a href="https://www.codecogs.com/eqnedit.php?latex=0\rightarrow&space;A_k" target="_blank"><img src="https://latex.codecogs.com/gif.latex?0\rightarrow&space;A_k" title="0\rightarrow A_k" /></a>就能當作從<a href="https://www.codecogs.com/eqnedit.php?latex=A_k" target="_blank"><img src="https://latex.codecogs.com/gif.latex?A_k" title="A_k" /></a>跟<a href="https://www.codecogs.com/eqnedit.php?latex=A_{k&plus;1}" target="_blank"><img src="https://latex.codecogs.com/gif.latex?A_{k&plus;1}" title="A_{k+1}" /></a>走到所有位置。而想法如下

```C++ = 
inc = dp[1:n]
dec = dp[n:-1:1]
for(i)
    dp.push_back(dp[n] + 2 + min(inc[i],dec[i]))
```
因為AR跟RR都是兩步，所以從頭跟從尾都是`dp[n]+2`，而在選取離頭進(inc)或是離尾近(dec)就能找到最佳步數(理論)。

#### 錯誤?
但這想法，在我確認了一下後以為理論被打破了因為5的地方，無論AARRAARA(1->3->3(R)->3(R)->4->6->6(R)->5)或是AAARAARA(1->3->7->7(R)->6->4->4(R)->5)，都沒有比AARARAA(1->3->3(R)->2->2(R)->3->5)好。

#### 研討問題
這問題是為什麼呢?我才發現，因為從頭往前的RR，如果後面還有R的情況下，可以兩者交換來做到減少一次R的操作。

### 問題出處
後來在多番思考 ~~(其中還莫名想出認為後來是看錯的情況丟了WA才清醒)~~ 。我總算整理出這些問題出現的點了。假設現在在位置N，下次A可以走到2N(大約值)，問題就會出現在N到3N/2的地方(RR的地方)，而且是來自N/2到N的地方(有RA的地方)，因為這裡必定存在RR跟R並存的狀態。

### 解析特例
這時候最花時間，因為需要確保RRAA...ARA...A換成RA...ARAA...A可以被減少(不然就要每次都linear掃回去，造成<a href="https://www.codecogs.com/eqnedit.php?latex=O(N^2)" target="_blank"><img src="https://latex.codecogs.com/gif.latex?O(N^2)" title="O(N^2)" /></a>的最糟結果)，後來發現回頭部分，因為前方都精簡步數化(以確保0 ~ N部分都為正確)的情況，所以不需要複雜的回頭(回頭步數非<a href="https://www.codecogs.com/eqnedit.php?latex=2^k-1" target="_blank"><img src="https://latex.codecogs.com/gif.latex?2^k-1" title="2^k-1" /></a>)，因為可以被調換順序成簡單的回頭加上其後步數。但最後還是沒有想到是否需要每格都去確認，就直接掃過去了。 ~~(做完後看解答發現更簡單的做法)~~ 

### 解決問題
把狀況大致設想完後決定了方法。
```C++ =
while(target > Inum.size()){
    inc = Inum;
    dec = reverse(Inum);
    for(i = 0 to n)
        Inum.push_back(Inum[pos]+2+min(inc,dec))
    speed = 2;
    for(int p = pos - 1 ; p >= i >= pos*3/4;) {
        for(int j = 0 ; j < inc.size(); j++){
            Inum[p+j+1] = min(Inum[p+j+1],Inum[p]+1+inc[j]);
        }
        p -= speed;
        speed *= 2;
    }
    Inum.push_back(Inum[pos] + 1);
}
```
這裡分成三塊，先把基本的(XRR,XRA)的部分初始好，再把先回頭(XRR...RA)的部分比較出來，最後再填上下一個狀態(XA)。

這裡發現，p不能直接跑到0，需要再半途時就砍掉，因為再往下可能出現RR但沒有RA的情況而導致錯誤。

### 經過
總之經過一番對於係數的修改WA後，AC了。至於係數修改部分大多出自腦袋卡住想不透。所以就不多做介紹。


## 參考答案
這裡看了解答後，發現完全不懂解答的想法，又繼續想了很久。

### Dijkstra's
因為這次的圖跟之前十分不同，導致我完全看不懂他的走法。但經過一番波折後，大致弄懂它的做法了，就是它是從target走返回0的做法(原因不太明瞭)，而運用開2倍大陣列的方式來紀錄每個點是向左向右的部分。然後走到0後(queue結束)`dist[0]`就是答案。

#### 不明白
因為看了半天還是不明白它的想法，最後決定大致了解一下 ~~(也可能今天不適合再思考了)~~ 。

### DP
這部分我還挺理解的，不過有趣的是，它是逐漸往前，不像我一塊塊處理。這裡用了很神秘的方式解決我RR...RA的狀況。
```C++ = 
for (i = 0 ~ k-1)
    dp[t] = min(dp[t], dp[t - (1<<(k-1)) + (1<<j)] + k-1 + j + 2);
```

因為今天不適合在思考了 ~~(偷懶)~~ ，所以沒有仔細去證明它的想法，但大致上就是從任何往回j格A並往前k-1個A可以抵達t的地方都走一次確認沒問題(我認為是所有RR...RA的狀況)，最後如果它是屬於後半部的情況再用`dp[t] = min(dp[t], dp[(1<<k) - 1 - t] + k + 1);`來去計算走過頭再回來的步法。

## 感想
今天不知道怎麼了，一直煩躁(?)，所以不僅問題想很久，也弄不太清楚問題。還是就這樣吧，至少解決了。