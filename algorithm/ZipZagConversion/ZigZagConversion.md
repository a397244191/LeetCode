# ZigZag Conversion
神秘的字串。

## 題目介紹及構思
- input
  - s(string)
  - numRows
    - the number of rows in this zipzag
- process
  - do zipzag conversion
- output
  - string

很神秘的東西。很簡單。

## 開始
這題不用什麼敘述，直接上圖就能簡單明白問題。

![](https://i.imgur.com/V3daeKq.png)

照紅線走的順序是input，而我們要output橫著看的順序(左到右，上到下)。

而因為中間空格沒有意義，只是純粹讓圖有意義而已，所以無視，這樣規律也很好找，就是一直上下上下移動就可以了。

```C++ = 
string convert(string s, int numRows) {
    vector<string> sub(numRows);
    p = 0;
    inc = true;
    for( c : s) {
        sub[p] += c;
        p += (inc ? 1 : (-1) );
        if( p == numRows - 1 || p == 0) inc ^= true;
        else if( p >= numRows || p < 0) p = 0;
    }
    ans = sub[0];
    for(i = 1 ~ numRows) {
        ans += sub[i];
    }
    return ans;
}
```

這裡為了防止numRows為1的時候p不會動而多了一個設定，但其實只要令numRows為1時直接回傳就好。 ~~(可惡，害我吃WA)~~ 總之很簡單的題目就AC了。

## 參考答案
做法單調到沒有什麼討論空間。不過那個numRows為1直接回傳當下的確沒想到，不過沒影響可以很快修改正確的問題。

## 感想
休息了一天，總之先從簡單點的問題再來。
