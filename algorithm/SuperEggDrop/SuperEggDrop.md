# Super Egg Drop
耗費一天解它，不過解答很狂，值得。

## 題目介紹及構思
- input
  - N(int)
    - N floor
  - K(int)
    - K eggs
- process
  - throw egg on T(T > F), egg is broken. otherwise, save.
  - try t times, and use at most K egg, we can find any F.
- output
  - t(int)
    - t times in this question, we can find the answer.

以為它的binary search是指找egg在哪層破掉的方法。信誓旦旦的開始後，才發現實際上是這題的解法。

## 開始
一開始很天真的以為，就用binary search去做DP，`DP[k][n] = 1 + max(DP[k-1][n/2],DP[k][n/2])`就可以了，這只是個<a href="https://www.codecogs.com/eqnedit.php?latex=O(NK)" target="_blank"><img src="https://latex.codecogs.com/gif.latex?O(NK)" title="O(NK)" /></a>的DP題而已，做下去後一直發現n/2部分橋不攏，吃了幾次WA以為都是對的，直到遇到了(k,n) = (2,9)。

### 正式開始
發現問題點，就是其實真正的DP式是<a href="https://www.codecogs.com/eqnedit.php?latex=DP[k][n]&space;=&space;1&space;&plus;&space;min(max(DP[k-1][x],DP[k][n-x])),&space;\forall&space;1\le&space;x\le&space;n" target="_blank"><img src="https://latex.codecogs.com/gif.latex?DP[k][n]&space;=&space;1&space;&plus;&space;min(max(DP[k-1][x],DP[k][n-x])),&space;\forall&space;1\le&space;x\le&space;n" title="DP[k][n] = 1 + min(max(DP[k-1][x],DP[k][n-x])), \forall 1\le x\le n" /></a>赫然覺得有夠難的。

### 直接展開
一開始我想的方法是維持DP是NK大小，但發現這樣每次跑X都會需要走X次，這樣就完全炸到<a href="https://www.codecogs.com/eqnedit.php?latex=O(KN^2)" target="_blank"><img src="https://latex.codecogs.com/gif.latex?O(KN^2)" title="O(KN^2)" /></a>，雖然N不大，但應該還是會TLE。所以想到一個方法。

### 新DP紀錄
這次DP的第二維度，改成了步數，如下。

```C++ =
last = 1:n
for(i = 1 ~ k){
now = {0};
t = 0;
    for(j = 1 ~ n){
        for(int k = 0~now.size())
        last = binary(last,n - j);
        add = min(add,max(lastN,k));
    }
    if(t <= add + 1) {
        now.push_back(j);
        t++;
    }
    else now.back() = j;
}
```
大致上想法還是如同前一個想法，只是稍微提升了後半部的方式，整體大約會是<a href="https://www.codecogs.com/eqnedit.php?latex=O(KN\sqrt{NlogN})" target="_blank"><img src="https://latex.codecogs.com/gif.latex?O(KN\sqrt{NlogN})" title="O(KN\sqrt{NlogN})" /></a>，至於為何開根號，是因為t跟N的關係是<a href="https://www.codecogs.com/eqnedit.php?latex=N&space;\le&space;\frac{t(t-1)}{2}" target="_blank"><img src="https://latex.codecogs.com/gif.latex?N&space;\le&space;\frac{t(t-1)}{2}" title="N \le \frac{t(t-1)}{2}" /></a>的緣故，不過結論似乎是我弄錯了，因為吃了TLE。

### 解析
其實狀況似乎挺極限的，因為實際算下來大約是<a href="https://www.codecogs.com/eqnedit.php?latex=10^8" target="_blank"><img src="https://latex.codecogs.com/gif.latex?10^8" title="10^8" /></a>，然後實際t沒有如實下降那麼多，就大約在一些狀況會爆開吧。 ~~(後來認為是這樣，我以為剛好壓線的說)~~

### 反過來
用now去找last不行，那能反過來嗎?因為這樣就變成<a href="https://www.codecogs.com/eqnedit.php?latex=O(K\sqrt{N})" target="_blank"><img src="https://latex.codecogs.com/gif.latex?O(K\sqrt{N})" title="O(K\sqrt{N})" /></a>了(在認為<a href="https://www.codecogs.com/eqnedit.php?latex=t\approx\sqrt{N}" target="_blank"><img src="https://latex.codecogs.com/gif.latex?t\approx\sqrt{N}" title="t\approx\sqrt{N}" /></a>的情況下)。所已開始想了到底是什麼關係，最後發現結論是`DP[k][t] = DP[k-1][t-1] + DP[k][t-1] + 1`，這就要回到最初想法來看，從X切開，下部是0到X，上部是X~N，所以上下的數量合剛好等於N-1，既然如此，就找到t-1步時，下面的數量去加上上面的數量就好啦，而結論就是剛剛的等式。

### 上限值
原本找到小遞方假解`DP[k][t] = DP[k-1][t] + DP[k][t-1]`卻發現這樣`DP[k][2]`會一直飆升，但實際上是不可能的，所以額外多做了一個上限值在步數t限制下，最高只有<a href="https://www.codecogs.com/eqnedit.php?latex=2^t" target="_blank"><img src="https://latex.codecogs.com/gif.latex?2^t" title="2^t" /></a>，但後來發現是我一開始走錯方向才會需要的。

經過假解WA後終於AC了。

## 參考答案
很棒的參考答案不一定都是難題，但只能說，難題常常會出現一些精美又意想不到的參考答案。

### binary search
雖然這裡的DP最大值沒有做到完全遞增或遞減，但其實也是有規律的。當`DP[k][x]`的x上升，這裡的DP1值會上升，但相對的`DP[k][n-x+1]`會下降，且這裡的DP2值也會下降。而最終，我們真正找到的會是當DP1跟DP2最接近的時候(甚至相等)。所以一樣可以利用binary search的特性，當DP1過小時上升x，DP2過小時下降x，直到離開或是相等時，此時x就是我們的解。為了預防其實不只差1的狀況所以最後用<a href="https://www.codecogs.com/eqnedit.php?latex=DP[k][n]&space;=&space;min(DP_{lo.status},DP_{hi.status})" target="_blank"><img src="https://latex.codecogs.com/gif.latex?DP[k][n]&space;=&space;min(DP_{lo.status},DP_{hi.status})" title="DP[k][n] = min(DP_{lo.status},DP_{hi.status})" /></a>來確保可以不會不小心找過頭。

這裡初始的上限是N下限是1，所以每次DP都會花<a href="https://www.codecogs.com/eqnedit.php?latex=log(N)" target="_blank"><img src="https://latex.codecogs.com/gif.latex?log(N)" title="log(N)" /></a>時間，總複雜度是<a href="https://www.codecogs.com/eqnedit.php?latex=O(KNlog(N))" target="_blank"><img src="https://latex.codecogs.com/gif.latex?O(KNlog(N))" title="O(KNlog(N))" /></a>

### 最佳化解
用上一個方法就是為了解決線性規律問題，但這規律可以更簡單。因為`DP[k][n]`的x一定是大於等於`DP[k][n-1]`的，因為要讓摔破蛋的狀況盡可能減少，所以x不到必要是不會上升的。所以只有當`DP[k][n-x]`超過`DP[k][x]`時，才有增加x的必要，因此可以讓x的增加限制在N以內，使得複雜度是<a href="https://www.codecogs.com/eqnedit.php?latex=O(KN)" target="_blank"><img src="https://latex.codecogs.com/gif.latex?O(KN)" title="O(KN)" /></a>。

### 數學
從頭到尾，都是建立在binary search跟DP上，現在要來點數學了。 ~~(不然Math的tag會哭泣的)~~

#### 前情題要
其實我最終想出的方法就是數學解的過程 ~~(其實我數學挺好的嘛\~雖然中途AC跑了)~~ ，所以前頭不加贅述就是我最終的DP表為recursive function f，且f(t,k)=1 + f(t−1,k−1) + f(t−1,k)，t是步數，k是蛋數。

#### 數學解證明
我們設立一個新的function g，另g(t,k) = f(t,k) - f(t,k-1)，而可以利用f(t,k) = 1 + f(t−1,k-1) + f(t−1,k)跟 f(t,k-1) = 1 + f(t−1,k−2) + f(t−1,k-1)而解出g(t,k) = g(t-1,k-1) + g(t-1,k)。的關係，而這關係從1開始了話就會變成Pascal's三角形的一部分。

![](https://i.imgur.com/utSunmL.png)

在此是預設f(t,0)是0。可能沒有很完整，但可以看到，扣除了底層一排一後，那形狀的確是Pascal's三角形，當然也是因為前面證明出來的g(t,k) = g(t-1,k-1) + g(t-1,k)導致的。因此<a href="https://www.codecogs.com/eqnedit.php?latex=g(t,k)&space;=&space;\left&space;(&space;\begin{matrix}&space;t&space;\\&space;k&space;\end{matrix}&space;\right&space;)" target="_blank"><img src="https://latex.codecogs.com/gif.latex?g(t,k)&space;=&space;\left&space;(&space;\begin{matrix}&space;t&space;\\&space;k&space;\end{matrix}&space;\right&space;)" title="g(t,k) = \left ( \begin{matrix} t \\ k \end{matrix} \right )" /></a>。而利用最初的g(t,k) = f(t,k) - f(t,k-1)，移項後的f(t,k) = f(t,k-1) + g(t,k)得到<a href="https://www.codecogs.com/eqnedit.php?latex=f(t,k)&space;=&space;\sum_{x&space;=&space;1}^{k}g(t,x)&space;=&space;\sum_{x&space;=&space;1}^{k}\left&space;(&space;\begin{matrix}&space;t\\x&space;\end{matrix}&space;\right&space;)" target="_blank"><img src="https://latex.codecogs.com/gif.latex?f(t,k)&space;=&space;\sum_{x&space;=&space;1}^{k}g(t,x)&space;=&space;\sum_{x&space;=&space;1}^{k}\left&space;(&space;\begin{matrix}&space;t\\x&space;\end{matrix}&space;\right&space;)" title="f(t,k) = \sum_{x = 1}^{k}g(t,x) = \sum_{x = 1}^{k}\left ( \begin{matrix} t\\x \end{matrix} \right )" /></a>。

#### binary search
這樣，只要找到正確的t就能解決問題，而正確的t值會令<a href="https://www.codecogs.com/eqnedit.php?latex=f(t,k)\ge&space;N" target="_blank"><img src="https://latex.codecogs.com/gif.latex?f(t,k)\ge&space;N" title="f(t,k)\ge N" /></a>，而<a href="https://www.codecogs.com/eqnedit.php?latex=1\le&space;t&space;\le&space;N" target="_blank"><img src="https://latex.codecogs.com/gif.latex?1\le&space;t&space;\le&space;N" title="1\le t \le N" /></a>，所以對t做binary search即可。而求f(t,k)的複雜度是K，因此整個解法複雜度是<a href="https://www.codecogs.com/eqnedit.php?latex=O(KlogN)" target="_blank"><img src="https://latex.codecogs.com/gif.latex?O(KlogN)" title="O(KlogN)" /></a>。

不過真不愧是數學解，竟然還用到二項式定理，只能說我還是才疏學淺呀。

## 感想
久久沒動腦袋，竟然因此砸下大量時間想這題，只能說我還需要多加磨練思考，畢竟停下思考會被時代淘汰的。
