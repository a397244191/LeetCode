# K-th Smallest Prime Fraction
以為很複雜，然後發現不難，最後發現更簡單的解法。

## 題目介紹及構思
- input
  - A(vector< int>)
    - a order list of some prime including 1
  - K(int)
- process
  - find out the Kth smallest fraction
- output
  - ans(vector< int>(2))
    - a pair of the Kth smallest fraction

我最開始想說一個半三角形的關係圖，要如何比大小，後來發現用類似top-down的方式擴散就能維持最小值必定在容器內，而容器最大為K。

## 開始
最開始配對完後，大概會是這樣子。
![](https://i.imgur.com/lJaIgaC.png)
每個直排分子都一樣，而每個橫排分母都相同。分子由左往右遞增，分母由上往下遞增。

### 大小關係
最初我在考慮大小時，曾經想過，我可以明確知道任意點的右上(含右及上)是大於該點，跟左下(含左及下)是小於該點，因為分母跟分子的變化關係是相反的，所以可以確保大小，但是另外兩邊呢?最後我利用這關係想到了一個方法。

#### queue
我們先將最左下的(分子最小，分母最大)的放入queue中，因為它必定是整個中最小的，而他的上一格(A)跟右一格(B)是僅次它的(還未知道哪個小)，剩下的點呢，要不是至少大於A就是大於B。

![](https://i.imgur.com/JinNUiw.png)

如上圖，紅色圍起來的三角為必定大於A，綠色則是大於B。所以我們每次從queue中取出最小值後，把AB位置放進來，就能維持最小值在queue裡了。而若在非queue中有小於A和B的值，也只能表示AB不是下一個最小值。

而內部圖如下
```C++=
for(int i = 0 ; i < qSize ; i++) {
    pair<int,int> number = fracInd.front();
    fracInd.pop();
    if(A[minNum.first]*A[number.second] < A[number.first]*A[minNum.second]){
        fracInd.push(number);
    } else if(A[minNum.first]*A[number.second] > A[number.first]*A[minNum.second]){
        fracInd.push(minNum);
        minNum = number;
    }
}
```

而利用如果相同則表示內部有重複的則替除 ~~(後來發現要等到兩個相同的前面及中間都沒有最小值才有用)~~，其中這queue會最大只有K，因為每次抽出一個最小值只放入兩個最小值後補，所以會隨著找到第N小值而增加到N。

#### TLE
很簡單的想法，所以我也很天真的以為<a href="https://www.codecogs.com/eqnedit.php?latex=O(K^2)" target="_blank"><img src="https://latex.codecogs.com/gif.latex?O(K^2)" title="O(K^2)" /></a>很好，但出現TLE後仔細算過發現，對於這個K應該換算成A，因為<a href="https://www.codecogs.com/eqnedit.php?latex=K_{max}&space;=&space;A^2" target="_blank"><img src="https://latex.codecogs.com/gif.latex?K_{max}&space;=&space;A^2" title="K_{max} = A^2" /></a>，使得這個想法其實是<a href="https://www.codecogs.com/eqnedit.php?latex=O(A^4)" target="_blank"><img src="https://latex.codecogs.com/gif.latex?O(A^4)" title="O(A^4)" /></a>。

### 更好的資料結構
一開始想說用priority queue來做，但這樣除了把A拉出去當全域變數，不然一個結構就要放入4個値才能確保我們查詢index可以在constant的時間。即使拉出去也要確保不重複而多開東西紀錄出現狀況之類的。最後決定用`map<pair<int,int>,pair<int,int>>`這個神祕的東西來做處理，first是分數值，second是分別的index。

而為了要能做到快速的找出最小值，決定放個compare function來解決。而function如下。
```C++ = 
struct cmpfunc {
  bool operator() (const pair<int,int>& lhs, const pair<int,int>& rhs) const
  {return lhs.first*rhs.second<rhs.first*lhs.second;}
};
```

這樣map.begin()就永遠是最小值了。而內部也省略迴圈瀏覽的部分變成如下。
```C++ = 
minNum = orderMap.begin()->second;
orderMap.erase(orderMap.begin());
            
mol = minNum.first,den = minNum.second;
if(mol + 1 < len) 
    orderMap[(A[mol+1],A[den])] = (mol+1,den);
if(den - 1 > 0) 
    orderMap[(A[mol],A[den-1])] = (mol,den-1);
```
這樣因為map複雜度的關係可以省略到<a href="https://www.codecogs.com/eqnedit.php?latex=O(Klog(K))\approx&space;O(A^2log(A))" target="_blank"><img src="https://latex.codecogs.com/gif.latex?O(Klog(K))\approx&space;O(A^2log(A))" title="O(Klog(K))\approx O(A^2log(A))" /></a>

修改完後沒有遇到陷阱AC了。

## 參考答案
看了結果發現時間上落後別人一大截，然後就被看到的code打敗了。其實就跟之前某次兩個排列好數列一樣方式，去對0~1(因為<a href="https://www.codecogs.com/eqnedit.php?latex=\frac{p}{q},p<q" target="_blank"><img src="https://latex.codecogs.com/gif.latex?\frac{p}{q},p<q" title="\frac{p}{q},p<q" /></a>)做binary search，然後計算比mid小的有多少就解決了!!?

因為這次必定存在結果，所以即使是小數做binary search也不會出現完全沒終點的狀況。而這複雜度大約是<a href="https://www.codecogs.com/eqnedit.php?latex=O(Alog(K))=O(Alog(A))" target="_blank"><img src="https://latex.codecogs.com/gif.latex?O(Alog(K))=O(Alog(A))" title="O(Alog(K))=O(Alog(A))" /></a>，其實<a href="https://www.codecogs.com/eqnedit.php?latex=log(K)" target="_blank"><img src="https://latex.codecogs.com/gif.latex?log(K)" title="log(K)" /></a>還有點不精確，因為這K不是數量而是要看最小切分出來的差值倒數而定，不過開log其實就別計較了。

## 感想
我對自己發現規律跟想法並精進資料結構的思考是滿意的。但遺憾的是似乎有很多方式(我可能只看到一種)可以更簡單的去利用及解決。但這也訴說著我還有很多需要精進的地方再等著呢。