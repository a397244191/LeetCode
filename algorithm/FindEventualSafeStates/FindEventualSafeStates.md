# Find Eventual Safe States
久久沒做圖的問題了。

## 題目介紹及構思
- input
  - G(vector<vector< int>>)
    - G[i] is the i-th node outedge
- process
  - find the safe node
- output
  - vector< int>
    - all safe node

找到可以有終點的node。

## 開始
看到這個，我還以為可以很天真的找子群，所以用了DFS跟圖反向的DFS，然後對所有只有一個點的群加入答案，結果發現，自體循環也不是安全的點而失敗了。

### 記錄狀態
這下子只好去想辦法在DFS中找到環了，做法很簡單，做DFS後只要再次走到被拜訪的點就算是一個環了。

### 殊途同歸
這時候我想到如果兩條路都走到同一個不就有問題了，所以自以為想了很好的方法在結束時對visit初始化。結果答案對了，但也TLE了。

### 查看記錄
後來我想到了，記然我要記錄狀態，我直接判斷狀態就好啦，幹嘛去改變visit的部分呢?所以加上了判斷已經確保正確的答案後成功了。

```C++ = 

vector<bool> visit;
vector<int> record;

vector<int> eventualSafeNodes(vector<vector<int>>& graph) {
    int n = graph.size();
    visit = all false
    record = all 0
     
    for(int i = 0 ~ n) {
        if(DFS(i,graph) > 0) ans.push_back(i);
    }  
    return ans;
}
int DFS(node, graph) {
    if(visit[node]) return record[node];
    record[node] = -1;
    visit[node] = true;
    for(int i = 0 ~ graph[node].size()) {
        if(DFS(graph[node][i],graph) < 0) {
            return record[node];
        } 
    }
    record[node] = 1;
    return 1;
}
```

這裡利用record來對已經拜訪過的點做記錄，在一次DFS完成。 ~~(其實在編輯記錄，將一堆冗詞刪去又是另一件事了)~~

在那之前，因為少了一條判斷所以又吃了TLE，不過修正後AC了。

## 參考答案
基本上參考答案的第二個想法跟我一樣，而另一個就比較有趣了。它是去記錄所有的正邊跟反邊，然後對所有沒有outedge的點保留。然後對保留點開始刪去正向邊的，當有個點j的正向邊被刪光表示j也是答案並加入queue。直到queue空了，即表示找完了。

## 感想
好久沒用圖的問題，至少基本的dfs沒有忘記。算是今天的收穫吧，至於解題方法可能還要多加練習。