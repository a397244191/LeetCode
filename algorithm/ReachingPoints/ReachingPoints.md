# Reaching Points
數學題目越刁鑽，知道解法就越簡單。
## 題目介紹及構思
- input
  - sx(int)
  - sy(int)
  - tx(int)
  - ty(int)
    - (sx,sy) is start point, (tx,ty) is target point
- process
  - (x,y) can move to (x + y, y) or (x, x + y)
- output
  - return true is start can move to target

說來慚愧，這題昨天就看到了，今天還是沒有解法。

## 開始
我不斷從ax+by = tx, cx + dy = ty 的方程式方面一直考慮。結果繞了一大圈，沒辦法反解出a,b,c,d。最後自暴自棄看了解答。

### 暴力解
當然，這題可以嘗試exp的展開，假若sx,sy不一樣，然後tx,tx又超大，這深度無可估量。所以保證不可行的。

最後我偷看了別人的討論發現我找不出來的癥結點。

## 參考答案
我一直考慮從sx,sy開始找到tx,ty的方法，但其實有個更好的方式是從tx,ty來找到sx,sy。這是為什麼呢。

### 題目條件
首先條件一開始，就是sx,sy,tx,ty都是正數(<a href="https://www.codecogs.com/eqnedit.php?latex=1\sim&space;10^9" target="_blank"><img src="https://latex.codecogs.com/gif.latex?1\sim&space;10^9" title="1\sim 10^9" /></a>)，而(x,y)變化條件是x加上y或是y加上x。

### 討論
綜合兩條件可以得知(x1,y1)變成(x2,y2)(走一步)，(x2,y2)會有保留前一個的x1或y1，而另一個y2或x2則是x1+y1的值。因此，如果保留的值大於被改變的值，就會發生前一個不在第一象限的狀況，可試題目起點跟終點都在第一象限，且只有做加法，所以不可能發生。

### 結論
因此可以保證任意點(x,y)，若 x > y，則前一個點是(x-y,y)，反之為(x,y-x)。得到這結論就可以從剛剛暴力解的指數成長變成其中一個路徑了。

### 延伸
因為我們知道x,y的路徑唯一，所以可以將減法延伸為除法，因為值到x < y之前，都會是往(x - y, y)走。所以延伸出任意點(x,y)的前一個轉彎點。在x > y時，會是(x%y,y)，反之為(x,y%x)。就這樣不斷重複到抵達(sx,sy)。

### 射線上判斷
當sx = x 或是 sy = y時，表示這次是最後一次轉向，而能否抵達(sx,sy)就不能在除x或y了(因為這樣就過頭了)。因此就要變成這樣
1. sx = x, (y-sy) % sx
2. sy = y, (x-sx) % sy

因為這是讓sx一直加sy到達x(或反之)，所以要除的值會是sy，並且被除的是sx跟x的距離。而如果無法為0，就是無法到達。

```C++ =
bool reachingPoints(int sx, int sy, int tx, int ty) {
    while(sx < tx && sy < ty) {
        if(tx > ty) tx %= ty;
        else ty %= tx;
    }
    return (sx == tx && !((ty-sy) % sx)) || (sy == ty && !((tx-sx) % sy));
}
```

整個解法乾淨簡單到我不禁想我一開始到底在想什麼。

## 感想
雖然很想直接痛批自己智商退化，可是有時候真的鑽牛角尖鑽錯地方時，往往就是看不到另一條選項。我太認為這題會是一個數學公式的解法，而忽略了其它可能。