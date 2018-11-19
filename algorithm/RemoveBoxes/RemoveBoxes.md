# Remove Boxes
難度一個大躍進，直接爆炸
## 題目介紹及構思
- input
  - boxes(vector< int>)
    - some positive numbers
- process
  - remove a part of boxes, and find the max cost
- output
  - int
    - the max cost of removed all boxes

DP題，最終被自己卡死。
  
## 開始
這題，最終我沒有自己完全想完解法，而是頂著胎死腹中的解法去找答案解決。而正確解法放在參考答案中，這裡來敘述沒成功的兩個解法吧。

### top-down remove
這是最差的想法，我在失敗幾次後嘗試這方法，就是將每個片段刪除遞迴下去，而記錄的是boxes剩餘的串列，用map方式儲存，很直接的在沒很大的測資時就TLE了。而因為想法簡單，所以時間複雜度很好估計，wrost case就是<a href="https://www.codecogs.com/eqnedit.php?latex=O(2^n)" target="_blank"><img src="https://latex.codecogs.com/gif.latex?O(2^n)" title="O(2^n)" /></a>。而這題n是100。

### DP表格
我後來想到的是，用一個DP記錄第i個到第j個的答案，因為最終整段會是將零碎的DP值總和加上那一段最終因為刪掉中間障礙的值。而想法也很簡單。就是找到跟頭一樣的值切分。
```C++ = 
int DFS(int head, int tail) {
    if(some condition) return ...
    count = 0
    pos = vector<int>
    for(int i = head ; i <= tail ; i++) {
        if(boxes[i] == boxes[head]) pos.push_back(i); count ++;
        num = count * count;
        for(int j = 0 ; j < pos.size() - 1;  j++) {
            num+= DFS(pos[j],pos[j+1]);
        }
        num+=DFS(pos.back(),tail);
        DP[head][tail] = max(num,DP[head][tail]);
    }
    return DP[head][tail];

}
```

這個DPS經歷了三次自己沒看清楚的bug，第一次忘了算head自己，第二次忘了算最後到tail剩下的，而第三次忘了判斷頭尾交替狀況。不過這都不是這解法的疑慮。

### 大問題
第四次submit後，得到了一筆龐大的測資表示我錯了。而我也把測資整合成簡單版的:`[1,2,2,1,2,2,1,1]`

#### 問題說明
依照上面簡單版的想法可以知道，如果將1全部連起來會是4*4 + 2*2 + 2*2 = 24，但實際上是需要捨棄中間那個1來令2能連在一起有最大效益。所以需要改變我的想法。

### 思考後可行解法
最終我是想到將所有記錄點存下來，然後用排列組合來完成它。可是這時就發現，最糟狀況即使我排除了所有原本連在一起的1之後還是要窮舉50個，所以複雜度就直接在這飆升成無法解決的指數。

### 最終
在思考各方法後，無法解決這成長指數而放棄方法，直接去參考他人想法。

## 參考答案
這裡我找到一個跟我想法幾乎接近 ~~(廢話，DP跟DFS是基本，不就一樣了)~~ 。不過這裡DP是三維的。看到這個我只能表示，天阿，三維DP若沒有知道這想法是很難建立起來的，畢竟在逐步思考的過程中就先被難以查看DP狀態而受挫。

### DP三維分別
想法跟我一樣，就是記錄某點到某點的值，但不同的是，它還有記錄尾值被repeate次數。舉例來說，題目是`[1,2,1,2,1,2,1]`遞迴成`[1,2,1],[2,1,2],[1]`的想法

1. 最後的1 找到配對是第二個1，所以它的答案會是`[1,2,1],[2,1,2],[1]`的切分
2. 為何是`[1,2,1]`是因為保證可以繼續往前找是否有要繼續相連的1。
3. DFS參數則在`[1,2,1]`上為DFS(0,2,1)，表示有1個跟尾相同的變數要合併
4. 此時DFS(head,tail,rep)就是記錄當剩下head到tail要切除時，tail後有幾個跟tail一樣的值被連接上tail且無論那些值是怎麼來的。

這方法一出，我那個要窮舉的方法就解決了。因為原本方法被放在同一層思考的窮舉，因為一個一個做選擇而被深度稀釋掉了。因為不用意開始就窮舉好，而是到需要判斷時用二分法解決，這樣就能被DP自動分解一堆無謂的呼叫。

換句話說，原本我需要窮舉<a href="https://www.codecogs.com/eqnedit.php?latex=2^{50}" target="_blank"><img src="https://latex.codecogs.com/gif.latex?2^{50}" title="2^{50}" /></a>個分支，其實有很多我是知道它因為有在DP了但還是需要列舉出來一起計算。但換成三維後，可以直接根據重複次數查看狀態來防止再次展開的想法，也就是將兩次舊方法的窮舉(片段窮舉跟個數窮舉)用DP合併。

### 做法
大致跟我的想法一樣，不過有做一些前置處理。

```C++ = 
int DFS(head,tail,rep)
    if(head > tail) return 0;
    else if(DP[head][tail][rep]) return DP[head][tail][rep];
    while(tail > head && boxes[tail] == boxes[tail-1]) {
        tail--;
        rep++;
    }
    DP[head][tail][rep] = DFS(head,tail-1,0,boxes) + (rep+1) * (rep+1);
    for(int i = head ; i < tail ; i++) {
        if(boxes[i] == boxes[tail]) {
            DP[head][tail][rep] = max(DP[head][tail][rep],DFS(head,i,rep+1,boxes) + DFS(i+1,tail-1,0,boxes));
        }
    }
    return DP[head][tail][rep];
```
1. 判斷一些狀況結束遞迴
2. while部分是先加上一些已經相連的重複部分，畢竟已經相連就一定會連在一起。
3. 在來就是將尾端跟後面得部分當做已算完替除，剩餘部分遞迴當做第一次值。
4. 迴圈部分是找出所有跟尾一樣的部分，確認連接在一起的狀態值。

### 精進辦法
目前這精進辦法缺乏證據無法得知為何，通常這種遞迴要變快就是去刪減不必要的分支，但奇怪的是，我看了提供方法的令一種方法，跟令一個很快的方式。我自認為理解方法用意後，套用進方法中卻失敗了?這我難以理解的部分暫時就先放著吧，有興趣再回來探討跟更新篇幅。

## 感想
畢竟難以保證下次還能打題目是什麼時候，如果我繼續拖延這題，導致思考無法連貫了話，除了繼續解已經沒有效率及意義，也難以完成檢討。所以只好參考他人的方式解決這題。