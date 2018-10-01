# Reach a Number
這已經不是reach a number，而是research a number吧。

## 題目介紹及構思
- input
  - target(int)
    - <a href="https://www.codecogs.com/eqnedit.php?latex=-10^9&space;\le&space;target&space;\le&space;10^9" target="_blank"><img src="https://latex.codecogs.com/gif.latex?-10^9&space;\le&space;target&space;\le&space;10^9" title="-10^9 \le target \le 10^9" /></a>
- process
  - the n-th step, we move n.
- output
  - step(int)
    - how many steps we can reach the target.

數字太大了，應該是找規律。

## 開始
這題目的規則，絕對不會在sample中，只好自己推舉狀況。

- 想法一
  - 這是一連串連續的整數，我們要利用給於正負號來得到target，而可以確保的是target是負的狀況，只要將每一步的正負顛倒就能到達。所以target不需管正負。
- 想法二
  - 現在我不可能一一檢查是否到達，所以應該是從每一步可以到達的地方進行著手。

### 展開狀況
總之先把狀況展開吧，正負號無視。

|step|reach|
|:---:|:---:|
|1|1(+1)|
|2|1(1-2),3(1+2)|
|3|0(3-3),2(1-3),4(1+3),6(3+3)|
|4|0(4-4),2(2-4),4(0+4),6(2+4),8(4+4),10(6+4)|
|5|1(4-5),3(8-5),5(0+5),7(2+5),9(4+5),11(6+5),13(8+5),15(10+5)|

這時後發現了第一個可能規律(暫時)，可以抵達數量是奇偶交錯的可能性，而數量增加似乎有某層關係。

### 奇偶變換發現
因為手寫展開是不可能的，所以改用程式展開。

![](https://i.imgur.com/PwuWDsf.png)

除了列表外，還計算了數量(最上面是第二步開始)，似乎很穩定的在2次就做交換奇偶數，而原因就是步數是奇偶交換的吧(連續整數)，在遇到奇數步時，就會交換奇偶狀態。

### 數量變化發現
再來針對數量，似乎也包含著規律。為了驗證就展開更多吧，至於細節就省略。

![](https://i.imgur.com/MziE8vD.png)

數量變化似乎維持著1,2,2,2,3,4,4,4,5,6,6,6...的關係，先不提重複次數的問題了，數量變化似乎持續遞增。之後來歸納結論吧。

先從小的開始，(1),(1,3),(0,2,4,6)，似乎一直維持連續的奇數或連續偶數的關係。

#### 狀態保存
要驗證數量的變化，就必須從保證可以推算出上一次狀態的數量開始。

##### 加上偶數
先從加上一個偶數步數開始，設定必須保持兩點。

1. 現在有任一奇數(偶數)列，其中不存在一個數比這列中任一數小且奇偶性跟數列一樣卻不在其中的。
2. 加入的偶數，不會大於這數列最大的數。

因為上述兩點，又獲得兩個結論

1. 加上及減去偶數的數列是連續的奇數(偶數) - 條件1
2. 加上的數列必然包含該數列某一片段 - 條件2

減去數列中有兩點

1. 負向會絕對值回來，但最小也不會大於原數列最大 - 條件2
2. 包含數列最小值 - 條件1 & 條件2

所以可以先保證，新數列一定保存舊數列。

##### 加上奇數
因為加上奇數會變化奇偶性，所以先分開提。不過設定依舊有兩點可以確保。

1. 現在有任一奇數(偶數)列，其中不存在一個數比這列中任一數小且奇偶性跟數列一樣卻不在其中的。
2. 加入的奇數，不會大於這數列最大的數。

也有兩則結論，不過結論一奇偶相反，結論2也做了修改。

1. 加上及減去奇數的數列是連續的偶數(奇數) - 條件1
2. 加上的數列必然包含該數列 +1(-1) 的值 - 條件2

因為要向下相容，所以多了一個條件 : 

- 新數列一定是從0(1)開始的偶數(奇數)數列

至於原因就跟減去奇數的數列有關。

1. 負向會絕對值回來，但最小也不會大於原數列最大 - 條件2
2. 包含0(1) - 條件2，因為可以找到一個數=步數(步數+1)

所以可以先保證，新數列一定至少有舊數列的數量。


以上兩點都可以保證數量(舊數列數量)跟狀態(從0或1開始)。

#### 增加的關係
確保數量後，就要去觀察增加的量了。

經過上面確認，可以保證，任一步數移動後，會產生一個連續、數量比前面數列多、且奇偶性一樣的數列。而至於多多少呢?就來看看吧。

因為連續且從最小開始，所以數量增加一定跟最大的數有關。

現在增加有4種變化。

1. 偶數(最大值) + 偶數(步數)
2. 奇數(最大值) + 偶數(步數)
3. 偶數(最大值) + 奇數(步數)
4. 奇數(最大值) + 奇數(步數)

前兩者，增加的數量會是步數/2，因為變化量為偶數，所以增加這樣。但後兩者不同，因為奇數跟偶數配對性是(0,1),(2,3),(4,5)，奇數總是多偶數1，所以當奇數變成偶數列時，會有(步數+1)/2的變化，而反之則是(步數-1)/2的變化。

因此產生了4個為循環的發生，順序是2,4,1,3，而變化量剛好也會是4個為循環，比前次多的變化是n,n+1,n+1,n+1,n+2,n+3,n+3,n+3,n+4...的循環。

### code編寫
經過複雜的推算 ~~(當初是直接認定直接寫，只是寫解題心得時正式歸納出來就是了。)~~ ，得到了兩個可靠根據，奇偶變化跟數量集，而用兩個根據可以藉由判斷奇偶數跟他在奇偶數中的順序得到經過幾步可以到達。

#### 上限
當然要一步步推倒就需要上限值，如果上限直接是N了話，就不可能用一步步推演的方式了，而經過推算 ~~(暴力破解)~~ ，它可以在80000 ~~(其實更小，實際是直接爆int上限)~~ 步內抵達超過<a href="https://www.codecogs.com/eqnedit.php?latex=10^9" target="_blank"><img src="https://latex.codecogs.com/gif.latex?10^9" title="10^9" /></a>。

所以我們就由此方式，一步步也能在有限步數內找到，就很放心的開始了。

``` C++ =
target = abs(target)
endN = target/2
tarS = target%2, status = true// true is odd
step = 1, number = 1,add = 1,check

for(step ; step < 80000 ; step++)
{
    if(endN > number && tarS == status) break;
    else number += add;
    check++;
    if(!(step%2)) status ^= true;//switch status
    if(check == 4){// add + 1 condition
        add ++;
        check = 0;// check reset
    } else if(check == 1) add ++;// add + 1 condition
}

return step;
```

其中有一些需要探討的條件，其1是當我們數的在奇(偶)數列中的順序超過要找的值後且該數列奇偶性跟數字一樣時，就表示找到了步數。

而其他狀態就是往下一步走，並且設定一些變數，像是下一步的變化跟當前奇偶性狀態。

### 突如其來WA
好啦，其實只是因為燒腦找規律導致自己邏輯不清楚，在後面check值上算錯導致的。修改完後就AC了。

## 參考答案
只能說有經驗的人就是不同。當初我是用歸納法證明增加規則後直接做，接下來的想法都是在保證總步數>target時的想法。

#### 必定到達證明
我們持續往一個方向走，必定可以走到1,3,6,10...等位置，而中間被跳過的點呢，是不是有更好的想法去解決它。這時我們假設有一個S，它是1+2+3+...+n的值，且<a href="https://www.codecogs.com/eqnedit.php?latex=S\ge&space;target" target="_blank"><img src="https://latex.codecogs.com/gif.latex?S\ge&space;target" title="S\ge target" /></a>，這時有一種方式可以保證得到必定能走到target的方式。

- target = S
  - 直接到達
- S - target
  - even
    - 這時可以找到一個數delta = (S - target)/2，而我們可以利用剛走的步數1,2,3...,n的其中幾個相加得到delta，所以可以保證一定走到。
  - odd
    - 因為此時delta不是整數，所以保證不可能抵達，只要再繼續往前，直到S - target是偶數為止，就能解決。

這想法最後衍生出以下code。

```C++ = 
step = 0
S = 0
add = 1
while(target < S){
step++;
S+=add;
add ++;
}
while((S-target)%2){
step++;
S+=add;
add ++;
}

return step;
```
簡潔暴力的想法，可惜我這次想多了想不到。

#### 更精簡
這時候還是要拿出我的想法中，對於奇偶變化的說法，因為每兩次就會變化一次奇偶性，所以可到達步數就會是在n,n+1,n+2這三者中間決定，而決定方式就是判斷S-target跟n+1值。

```C++ = 
if(!((S-target)%2)) return n;
else if(!((n+1)%2)) return n+1;
else return n+2;
```

而更簡單的寫法是`return ((S - target) % 2)?n + 1 + n%2 : n;`，因為當n是奇數時就表示n+1是偶數，而偶數是不可能變化奇偶的，所以需要+1。

### 數學計算
以上的做法大致上都是去找到S然後再去判斷，但這個複雜度都是在<a href="https://www.codecogs.com/eqnedit.php?latex=O(\sqrt{target})" target="_blank"><img src="https://latex.codecogs.com/gif.latex?O(\sqrt{target})" title="O(\sqrt{target})" /></a>。而接下來看到的是，用const time直接找到n的方法。

而這方法只能說太基本到忘了，就是二次方公式解。因為S = 1+2+3+...+n，且<a href="https://www.codecogs.com/eqnedit.php?latex=S\ge&space;target" target="_blank"><img src="https://latex.codecogs.com/gif.latex?S\ge&space;target" title="S\ge target" /></a>，所以可得知<a href="https://www.codecogs.com/eqnedit.php?latex=\frac{n(n-1)}{2}\ge&space;target" target="_blank"><img src="https://latex.codecogs.com/gif.latex?\frac{n(n-1)}{2}\ge&space;target" title="\frac{n(n-1)}{2}\ge target" /></a>，而經由公式解得知，<a href="https://www.codecogs.com/eqnedit.php?latex=n\ge\frac{-1&plus;\sqrt{1&plus;8target}}{2}" target="_blank"><img src="https://latex.codecogs.com/gif.latex?n\ge\frac{-1&plus;\sqrt{1&plus;8target}}{2}" title="n\ge\frac{-1+\sqrt{1+8target}}{2}" /></a>

而S當然直接用<a href="https://www.codecogs.com/eqnedit.php?latex=S=\frac{n(n-1)}{2}" target="_blank"><img src="https://latex.codecogs.com/gif.latex?S=\frac{n(n-1)}{2}" title="S=\frac{n(n-1)}{2}" /></a>得到

再利用最後的三分法得到答案，整個就是在const time解決。 ~~(當然不能否認sqrt的複雜度，不過因為優化等原因，就不管了。就算自己寫一個也可以在log(target)解決)~~

## 感想
只能說在數學題目上，能精簡的方式也只有數學方法了。有時候不是不會這方法，而是根本沒想到可以搭在一起。