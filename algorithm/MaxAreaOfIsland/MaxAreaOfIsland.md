# Max Area of Island
今天是基本的DFS練習。
## 題目介紹及構思
- input
  - grid(vector<vector< int>>)
    - a map with '0' or '1'
- process
  - calculate the max area.
- output
  - the max number

基本的DFS。

## 開始
沒有什麼問題，直接跑DFS。因為數字只有0跟1，所以直接代替拜訪過，當走過就將grid歸0。

```C++ =
int DFS(r,c)
{
    if(grid[r][c] == 0) return 0;
    grid[r][c] = 0;
    int num = 0;
    for( 4 direction)
        if(inside grid)
            num+= DFS(nextR, nextC);
            
    return num;
}
```

這部分沒有太大的問題，直接用DFS掃過整張就結束。

## 參考答案
基本題，沒有什麼特別有趣的參考解法。

## 感想
今天想休閒的打一題，就選了這個基本的DFS題練習。