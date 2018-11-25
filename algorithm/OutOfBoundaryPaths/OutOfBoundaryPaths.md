# Out of Boundary Paths
因為上上次寫的題目，這次很快解決了。
## 題目介紹及構思
- input
  - m
    - the number of row
  - n
    - the number of column
  - N
    - the max times you can move
  - i
    - the position starting on row
  - j
    - the position starting on column
- process
  - how many kind of path can you let ball get outside
- output
  - the number of all path
    - % 1000000007

這次有移動次數相關，令我想到上次刪除相同連續數字的題目，便決定用三維DP。

## 開始
因為每個點都有因為移動步數不同而有不同的值，所以直接開了三維DP，分別是row,col跟move的次數。

### DFS
因為三數字最大都50，所以DP表是可以開足夠大，而且複雜度也能用<a href="https://www.codecogs.com/eqnedit.php?latex=O(N^3)" target="_blank"><img src="https://latex.codecogs.com/gif.latex?O(N^3)" title="O(N^3)" /></a>。而DFS也因為上次寫過類似的，所以很快。
```C++ =
MOD = 1000000007
int DFS(r,c,move,m,n) {
    if(dp[r][c][move] != -1) return dp[r][c][move];
    if(move == 0) return (dp[r][c][move] = 0);
    dir = {{1,0},{-1,0},{0,1},{0,01}}
    count = 0;
    for(int i = 0 ; i < 4 ; i++) {
        nr = r + dir[i][0],nc = c + dir[i][1];
        if(0 <= nr < m && 0 <= nc < n)  count += DFS(nr,nc,move-1,m,n);
        else count ++;
        count %= MOD;
    }
    return (dp[r][c][move] = count);
}
```

第一個判斷當已有值就回傳是必備的，而移動終止也結束。在來這裡跟大部分DFS最不同的是，超出邊界要做處理，因為本身題目就是要求算超出邊界的次數。

而每次count加上值後便會做mod，所以int便足夠儲存。

中間自己測試發現move欄位我只開50是不夠50步的，所以為了安全開成51*51*51的。便一次AC了。

## 參考答案
在看時間時發現比別人慢了一點，開始懷疑這題只要二維DP但其實沒找到。而在找的過程中發現，這題有趣的是其實有個bottom-up跟另類的top-down解法。而且都是用迴圈而非recursive。

### bottom-up
就是N-r-c的方式，其中N的部分是從小開始疊上去的。令任意dp[r][c][t]為四周總合(出邊界為+1)，直到N-1的時候結束。最後回傳dp[i][j][N-1]即是答案。而這方法可以對任意起點都有用的bottom-up方式。

### top-down
這部分最重要的是，它只用到2維DP便能做到結果。是一個相對省空間的做法。它利用每次統計剩下N步的時候走到該格的次數去移動到鄰近四格，而當超出邊界時，就令result加上該格被走到的次數。依此累積到N步走完，result便是答案。

## 感想
好在上次經歷三維DP洗禮，這次沒有太大困難。
