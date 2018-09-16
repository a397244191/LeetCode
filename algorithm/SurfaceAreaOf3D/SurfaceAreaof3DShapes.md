# Surface Area of 3D Shapes
計算表面積的題目。

## 題目介紹及構想
- input
  - grid(vector<vector< int> >)
    - 一個在N * N的範圍內，放置的每個cube塔高度
- process
  - 依照整個疊出來的形狀，計算其表面積。
- output
  - result(int)
    - 該立體形狀的表面積。

基底表面積6，由左到右由前到後由上到下，六個面，每被擋住一面表面積少2。

## 開始
我決定一個塔一個塔開始處理，若被前面興建的塔擋住就扣掉中間的面積。
``` C++ =
    int surfaceArea(vector<vector<int>>& grid) {
        for( i = 0 ~ n-1)
            for(j = 0 ~ n-1){
                result += surface area of the tower grid[i][j]
                if(i > 0) 
                    result -= the area between grid[i-1][j] and grid[i][j]
                if(i > 0)
                    result -= the area between grid[i-1][j] and grid[i][j]
            }
        return result;
    }
```

### 結束

題目沒有任何陷阱，頂多原本我打算寫成`result += 4*grid[i][j] + 2`後來想到塔可能是0，會多2，改了一下外都沒問題。

## 參觀解答跟其他人答案

我是先看到其他code再去看解答。

### 其它code

因為題目想法沒很難，所以就來看看其它code，這倒是吸引我的目光，整段code概念跟我差不多，但是很神奇的是他計算側面的面積時的用法，比較對象跟我一樣，但是不是用減法是用加法。這樣就不用像我的code一樣去 * 2而是直接加上去。這樣一層一層向外側補上去的感覺，我覺得能想到這樣的方式也很厲害。

### 解答

解答的想法很有趣，就是塔算起來後再去加上比四周高出的部分。可是因為判4方，所以多了一層迴圈，看起來我不是很喜歡?不過沒有用乘法，可能會比較好。不過看過別人code後驚豔度沒很高。

## 感想

今天的題目跟昨天一樣是easy的，而我也不負己望一次解決。主要挑選這題目的原因是我之前都在第一頁挑選，今天難得拉到最後頁看到New的標示，想試試看而已。今天就先這樣完成每日最低進度 ~~(雖然昨天好像更少就是)~~。
