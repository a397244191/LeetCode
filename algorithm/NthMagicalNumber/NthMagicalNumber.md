# Nth Magical Number
跑去玩SQL query，又休息了一天，該上工囉。

## 題目介紹及構思
- input
  - N(int)
    - the Nth number is divisible by either A or B.
  - A(int)
    - one divisor
  - B(int)
    - one divisor
- process
  - find the Nth number
- output
  - ans(int)
    - the Nth number % 1e9+7

我想說應該用binary search的概念解決。

## 開始
應該沒有很難，就是找到一個A或B的倍數，然後比它小的有N-1個，怎麼寫就是，X/A+X/B-X/AB = N(AB = `A*B/gcd(A,B)`)，此時X就是答案。我還很擔心數字爆炸所以用了long long。

我煩惱一下子，因為一開始想說用線性方式不斷比較A和B，直到第N個，可是N太大了，只好用binary search，可是這樣有A有B不好寫，就決定分開寫。

```C++ = 
    int nthMagicalNumber(int N, int A, int B) {
        long long int AB = A * B / gcd(A,B);
        long long l = 1, r = N;
        while(l<r) {
            mid = (l + r) / 2
            X = mid
            Y = AX/B
            Z = AX/AB
            if(X+Y-Z > N) r = mid - 1;
            else if(X+Y-Z < N)l = mid + 1;
            else return XA%MOD
        }
        check l and r
        
        l = Al/B - 1
        r = Ar/B - 1
        
        swap(A,B)
        while(l<r) {
            mid = (l + r) / 2
            X = mid
            Y = AX/B
            Z = AX/AB
            if(X+Y-Z > N) r = mid - 1;
            else if(X+Y-Z < N)l = mid + 1;
            else return XA%MOD
        }
        check l and r
        
        return -1;
    }
```

因為有點臨時寫binary，所以很亂沒有寫成function，但是這次有記得對mid做+1跟-1的動作。

### 愚蠢紀錄
先記錄我愚蠢的直接submit的狀況，後面才是正式修改問題的重點。

#### 寫錯邊
我大於的方向寫反了。

#### debug沒拿掉
我因為沒拉出去debug，所以在裡面做改變NAB的值，忘了拔掉。

#### 忘了改
因為有些類似的我習慣複製貼上再改，結果忘了把l改成r就丟了。

### 公倍數
我一開始AB就想說直接乘就好，沒想到直到遇到submit才發現我忘了取gcd去除。

### 就是因為+1跟-1
因為`l = mid + 1` 跟 `r = mid - 1`才可以讓binary search達到中止條件中止。結果因為要保留l跟r的紀錄，所以造成l或r還沒有check就出事情了。

只好在外面重新對l跟r做check是否答案。(而且因為兩次所以檢查也要在兩個外面檢查)。

到這裡我已經覺得有點醜了，但礙於當下沒有別的想法就只好先以過為主。

### 還是+1跟-1
這次再切換lr從A到B的lr時，因為兩者接近數字又大，所以剛好沒有包含到，然後就出現第二次沒有包含答案的狀況了。



經過一連串的問題，總算AC了。


## 參考答案
知後當然要去參考一下答案拉。

### 於數解法
簡單來說，就是利用公倍數L來縮減範圍，最後用我一開始想到的線性解法。

```C++ = 
int L = A*B/gcd(A,B);
int M = L/A + L/B - 1;
int q = N / M,r = N % M;
int ans = (M * L) % MOD;
for( 0 <= i < r-1){
    if(A <= B) A += A;
    else B += B;
}

if(r == 0) return ans;
else return (ans+min(A,B))%MOD;
```

就是說，先找出LCM，然後算出一個LCM有M個小於等於它的值。這樣就會產生`N=M * q + r`的算式，因為經過q個公倍數後`q*LCM`就會是第`q*M`個數，而如果還有多就是再加上r個就可以，並且r一定小於M。

然後開始算再多幾個A或是幾個B，線性解就是當`A <= B`時A就是當前A是最小的，反之就是B最小，讓最小的往下一個。而因為我們用LCM取r了，所以不會遇到`A==B`的情況，因為如過`A==B`就會因為等於LCM而被除盡。

而最糟糕的情況是A和B是互值，這樣r最大會是A+B-1個。

### 高級 binary search
好啦，說是高級其實是我想太複雜。我明明知道可以用數字去binary search，卻沒有想到可以把整段數字拿來用。因為數字最大會是`N*max(A,B)`，所以我只要想像有一個`N*max(A,B)`的陣列去做binary search就好了。

只能說我設想太複雜了，一直考慮兩個陣列換來換去的做法。

# 感想
題目不難，想法很容易生出來，減少複雜度也不會太難想到，唯一問題是我實作對上一些小細節時一直出錯跟沒有注意到而已。在來就是想的太難了，反而因為鑽牛角鑽到死在一堆細節上。