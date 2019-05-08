# Pow(x, n)
簡單數學應用題。
## 題目介紹及構思
- input
  - x(double)
    - the base number
  - n(int)
    - the exponential number
- process
  - calculate the <a href="https://www.codecogs.com/eqnedit.php?latex=x^n" target="_blank"><img src="https://latex.codecogs.com/gif.latex?x^n" title="x^n" /></a>
- output
  - double
    - the ans of <a href="https://www.codecogs.com/eqnedit.php?latex=x^n" target="_blank"><img src="https://latex.codecogs.com/gif.latex?x^n" title="x^n" /></a>
- output

很基本的快速羃。

## 開始
這裡唯一的陷阱，大概就是負的次方吧!本身不難，但是因為int的儲存方式，導致負方向比正方向多1個數會導致overflow，只要處理好這部分就可以了。

### 前處理
為了防止n = -2147483648的狀況，所以用long long 的方式防止overflow

```C++ = 
long long t = n;
if(t < 0) {
    t *= -1;
    x = 1/x;
}
```
當負次方時，只要讓x為倒數即可。

### 計算
```C++ = 
while(t) {
    if(t%2) ans *= x;
    x *= x;
    t<<1;
}
```
這部分利用t的二進位判斷是否乘上x(<a href="https://www.codecogs.com/eqnedit.php?latex=x^{2^y}" target="_blank"><img src="https://latex.codecogs.com/gif.latex?x^{2^y}" title="x^{2^y}" /></a>)，就可以得到最終答案了。

## 參考答案
因為題型簡單明瞭，而數字範圍極大，所以方法大同小異。

## 感想
偶爾寫寫這種純方法的題目可以讓人認知基本功還未消失。