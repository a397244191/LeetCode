# Elimination Game
很簡單的題目，應該有很神秘的規律。
## 題目介紹及構思
- input
  - n(vector< int>)
    - a list of 1 to n.
- process
  - form head remove number
    - remove the first number and every other number afterward until you reach the end of the list.
  - from tail remove number
    - remove the last number and every other number from the remaining numbers.
  - until one number.
- output
  - int
    - the final number.

重複動作，因為每次減少一半數量，實行會是<a href="https://www.codecogs.com/eqnedit.php?latex=O(Nlog(N))" target="_blank"><img src="https://latex.codecogs.com/gif.latex?O(Nlog(N))" title="O(Nlog(N))" /></a>，不過太規律了，來想個辦法吧。

## 開始
總之先想出最基本的模式，在考慮怎麼用數學方式代替一個個刪除的動作吧。

### 基本型
先來直接模擬吧。

```C++ = 
int lastRemaining(int n) {
    /*
    int t = 62;
    vector<int> a;
    for(int i = 1 ; i <= t ; i++) a.push_back(i);
    while(a.size() > 1) {
        for(int i 0 ~ a.size() ; i++) {
            a.erase(a.begin()+i);
        }
        reverse(a);
    }
    return a[0];
    */
```
因為刪除一個後面都前進一格，所以前進只需要+1。不斷重複到只剩下一個。

### 數學想法
因為剛好都差2的方式，最先想到就是奇偶性值的可能。而每次都把剩下的數分奇偶(意義上的)，應該可以靠這樣推出答案。

#### 頭尾開始有差別
因為都預設第一個都是1，所以從頭開始都剩下偶數，而從尾了話，假設有偶數個就剩下奇數，反之亦然。

#### 奇偶結果
將奇偶結果二進位化，感覺就是答案了，但出現奇怪的結果。就是換算的數字感覺不太對。

拆解一下每個數字的奇偶(每次剃除一半數字後)，會發現一個新的二進位方式，而有趣的，因為最後前面都被刪去後它就永遠都是第一個，所以會有無限的1。這模式跟二補數的負數一樣呢。然後開始推幾個狀況。

#### 推結果
所以利用數量跟從頭尾來刪去這兩個條件，可以弄出個規律。

```C++ =
int lastRemaining(int n) {
    bool flag = false, fromHead = true;
    int ans = 0, two = 1;
    while(n) {
        bool add = false;
        if((!(n%2) && !fromHead) || n == 1) add = true;
        if(flag) add ^= true;
        if(add) ans += two;
        two *= 2;
        if(add) flag = true;
        n /= 2;
        fromHead ^= true;
    }
    return ans;
}
```
照負數規律，遇到第一個1就轉做inverse。組起來就能推出結果了。

總支也苦思一陣子，終於推出值得接受的答案一次AC。(雖然對為啥是負數充滿疑問)。

## 參考答案
看到一個跟4有關的recursive解。除了特定解外(1,2,3)，都可以遞回下去。
```C++ = 
int lastRemaining(int n) {
    if (n==1) return 1;
    if (n==2 || n==3) return 2;
    if (n%4 == 0 || n%4 == 1) return 4*lastRemaining(n/4) -2;
    else return 4*lastRemaining(n/4);
}
```

因為每次都頭尾掃一次就會回到最出狀態，所以可以將狀態分成4個。
1. 除4餘0或1 : 從第一個開始所以過去就會將奇數去除，而剩下的就是被4可以整除的在最後，所以回來會剃除4的倍數。
2. 除4餘2或3 : 從第一個開始所以過去就會將奇數去除，而剩下的就是被4不可以整除的在最後一個，所以回來會剃除非4的倍數。

上述兩個狀況會使剩下的數字都跟4有關，如果是剩4的倍數，就直接除4就變成新的index(反之新結果乘4就是答案)，而剩下非4的狀況，就會offset 2，所以推回去的答案要-2。

這個也相較合邏輯(比我自己想的)，不過複雜度上都是<a href="https://www.codecogs.com/eqnedit.php?latex=O(log(N))" target="_blank"><img src="https://latex.codecogs.com/gif.latex?O(log(N))" title="O(log(N))" /></a>就不計較了(?)

## 感想
這題雖然困惑一陣子，甚至開表單想規律，不過有想出來就好。