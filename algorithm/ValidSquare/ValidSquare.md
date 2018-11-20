# Valid Square
想說今天來點簡單的，結果沒想清楚不斷陣亡
## 題目介紹及構思
- input
  - p1(vector< int>)
    - a 2D point
  - p2(vector< int>)
    - a 2D point
  - p3(vector< int>)
    - a 2D point
  - p4(vector< int>)
    - a 2D point
- process
  - check the four points are a square
- output
  - bool
    - if they can be a square, return true

很簡單的判斷 ~~(不耍笨了話)~~
  
## 開始
判斷正方形主要分成三種：直角、邊相同、可圍成正方形。所以程式分成三段解決。

### 直角問題
就是利用<a href="https://www.codecogs.com/eqnedit.php?latex=a^2&plus;b^2=c^2" target="_blank"><img src="https://latex.codecogs.com/gif.latex?a^2&plus;b^2=c^2" title="a^2+b^2=c^2" /></a>的特性，保證兩條路平方合等於第三條。

```C++ =
len1 = (p1[0] - p2[0]) * (p1[1] - p2[1]);
len2 = (p1[0] - p3[0]) * (p1[1] - p3[1]);
len3 = (p1[0] - p4[0]) * (p1[1] - p4[1]);
if(len1 + len2 == len3);
else if(len1 + len3 == len2) swap(p3,p4);
else if(len3 + len2 == len1) swap(p2,p4);
else return false;
```
這部分為了之後統一順便將最近的兩點變到p2跟p3。

### 邊長相同
這部分就直接檢查最短兩點是否相同即可 ~~(可是我忘了交換過了len要重算，吃了WA)~~

```C++ =
len1 = (p1[0] - p2[0]) * (p1[1] - p2[1]);
len2 = (p1[0] - p3[0]) * (p1[1] - p3[1]);
if(len1 != len2) return false;
```

### 可否圍成
因為前兩個判斷沒有保證方向是否在同一邊，所以第三個利用向量關係來做判斷，簡化如下
<a href="https://www.codecogs.com/eqnedit.php?latex=p_1&space;&plus;&space;\overrightarrow{p_1p_2}&plus;\overrightarrow{p_1p_3}&space;=&space;p1&space;&plus;&space;(p2-p1)&plus;(p3-p1)&space;=&space;p2&space;&plus;&space;p3&space;-&space;p1" target="_blank"><img src="https://latex.codecogs.com/gif.latex?p_1&space;&plus;&space;\overrightarrow{p_1p_2}&plus;\overrightarrow{p_1p_3}&space;=&space;p1&space;&plus;&space;(p2-p1)&plus;(p3-p1)&space;=&space;p2&space;&plus;&space;p3&space;-&space;p1" title="p_1 + \overrightarrow{p_1p_2}+\overrightarrow{p_1p_3} = p1 + (p2-p1)+(p3-p1) = p2 + p3 - p1" /></a>

```C++ =
if(p2[0] + p3[0] - p1[0] == p4[0] && p2[1] + p3[1] - p1[1] == p4[1]) return true;
else return false;
```

以上三步驟，都判斷完後即可AC。至於吃了幾次WA分別是：
1. 忘了最後加總是向量不是點
2. 忘了len1,len2要做相同確認
3. 忘了len1,len2的點可能被交換
4. 不知道單一點不算是正方形

除了第四點不太確定外，另外三次WA都是我沒想清楚導致的。

## 參考答案
題目基本上沒有異議，至少都需要判斷上述方式，所以沒啥特別想記錄的參考答案。

## 感想
我以為可以偷懶簡單點，結果被自己腦袋坑了。