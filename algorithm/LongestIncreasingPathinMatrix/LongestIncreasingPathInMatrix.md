# Longest Increasing Path in a Matrix
類似走迷宮的題目

## 題目介紹及構思
- input
  - matrix(vector<vector< int>>)
    - maze map
- process
  - dfs map, find the longest increasing path
- output
  - maxLen(int)
    - the length of the longest increasing path

整張圖都跑過一次(DFS)，記錄最長路徑長跟查詢。

## 開始
題目不難，就是去DFS整張圖，沒個節點都記錄它的最長路徑長，下次再走到就只要提取值就好。不斷接上去就能找到最長遞增路徑長了。

### 主架構
先從主架構說起，分兩塊，初始化跟跑圖。
#### 初始化
首先先初始化一些必要資訊，像是否拜訪、目前最長路徑長度這兩個。
```C++ = 
for(i = 0 ~ matrix.size){
    visit.push_back(vector<bool>(matrix[i].size,false));
    pLen.push_back(vector<int>(matrix[i].size,1));
}
```
#### 跑圖
接下來遞迴也不難，就是整張圖都當起點DFS下去。
```C++ =
for(i = 0 ~ matrix.size)
    for(j = 0 ~ matrix[i].size)
        maxLen = max(maxLen,DFS(matrix,i,j));

return matLen;
```
### DFS
接下來看DFS的部分，大致有兩個狀況，走過、沒走過。而走過就回傳`pLen[row][col]`而沒走過就去瀏覽四周。

```C++ = 
int DFS(matrix,row,col){
    if(visit[row][col]) return pLen[row][col];
    visit[row][col] = true;
    for(i = row - 1 ~ row + 1)
        for(j = col - 1 ~ col + 1){
            if(i not in 0~matrix.size || j not in 0 ~ matrix[i].size || i,j is not four direction)
                continue;
            if(matrix[i][j] > matrix[row][col]) pLen[row][col] = max(pLen,DFS(matrix,i,j) + 1);
        }
    return pLen[row][col];
}
```
這裡其實弄錯兩件事情，就是不小心把對角移動也算進去了，讓我判斷不走的條件增加。還有其實visit我覺得很多餘，因為最後也是進去DFS回傳才用到visit。

### bug
有點算是自己沒看到的失誤，因為測資都是正方型所以沒注意，其實我前頭`j = 0 ~ matrix[i].size`時，少了`[i]`的部分，導致變成長方形後錯了。

不過修正好BUG後就沒問題的AC了。

## 參考答案
其實做法大致就是這樣，只是看到一個比較有趣的方式。
### 方向
因為之前我習慣用雙層迴圈去跑九宮格，但這次只有十字方向要走，寫成迴圈太複雜，不寫又一直重複相同事情，後來看到一個適用紀錄陣列的方式，去跑`4*2`陣列這樣就能表示4方位了。
### visit
這裡我後來發現visit有點用不到，而且使用後過於冗，我就看到一個方式很棒，pLen的遞方初始化為0。在DFS中在設定為1，如果是0就是沒拜訪過。看到時有點驚艷。

## 感想
雖然題目很基本，但就是因為基本題目，才會有更多更好的解決方法或是輕鬆讓code更好看的方式。這都是我覺得不足跟需要學習的。