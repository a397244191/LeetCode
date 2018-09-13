# K-Similar Strings
回憶(Memory)爆炸吧!

## 題目介紹及構想
- input
  - A(string)
    - before status
  - B(string)
    - after status
- process
  - do k times swap from A to B
- output
  - k(int)
    - after k times swaps, we can transform A into B. k is smallest.

雖然是圖，但題目樣子不像，因為要計算最少次數，所以做法是BFS。

## 開始
做法是BFS，所以就用queue去存取sting use跟int count，use是當前string狀況，count是目前做幾次swap。一開始想法簡單，就是用這方法直到use=B時回傳count，因為第一次出現正確狀態所以必然是最小。然後就收到了一則訊息MLE說你用的空間爆炸了。

### MLE first
怎麼會呢?然後稍微動手算了一下(一開始只想把想法寫出來)，發現我的想法出現問題，code如下。

```C++ = 
while(!q.empty()){
    loop(string use(i = 0 to n)){
        if(use[i]==B[i]) continue;
        loop(string B(j = i to n)){
            if(use[i]==B[j]) q.push(string.swap(i,j))
        }
    }
}
```
這裡有個超大障礙，就是我們每次會丟入queue的次數超級多，所以稍微做了修正，但因為要防止只有往前交換可行變成這樣。
```C++ =
while(!q.empty()){
    loop(string use(i = 0 to n)){
        if(use[i]==B[i]) continue;
        loop(string B(j = 0 to n)){
            if(use[i]==B[j]) q.push(string.swap(i,j))
            break;
        }
    }
}
```
這樣看起來很棒，每次queue只會丟入最多20個(字串長)。但其實不然，因為第二層就給你<a href="https://www.codecogs.com/eqnedit.php?latex=18^{19}" target="_blank"><img src="https://latex.codecogs.com/gif.latex?18^{19}" title="18^{19}" /></a>這種爆炸的指數展開。所以加入一些看起來有裁支的做法。然後發現這樣寫其實不用j = 0~n，用i~n也可以就變成了。
```C++ =
while(!q.empty()){
    bool visit[20] = {false}
    loop(string use(i = 0 to n)){
        if(use[i]==B[i] || visit[i]) continue;
        loop(string B(j = i to n)){
            visit[j] = true;
            if(use[i]==B[j]) q.push(string.swap(i,j))
            break;
        }
    }
}
```

恩，很棒呢，MLE測資過了，直到submit前我是這樣想的。

### MLE second
丟上去了才發現，我剛剛MLE的input根本沒有到達input上限的20字元阿!很明顯的這只是個將就的寫法，並沒有解決多少問題。

所以這次我想了一下，發現了一個問題!是不是有些交換後狀態根本就會一樣呢?答案是肯定的，所以我就用了unordered_set去儲存string狀態，當狀態出現時就不要再跑了。而AC code也產生了。而後也確認visit的寫法雖然有減少一些部分，但那個數量遠低於這次做法，所以就刪掉了(當然刪了也確定能過)。
```C++ =
    int kSimilarity(string A, string B) {
        unordered_set<string> mySet;
        queue<pair<string,int> > q;
        q.push(pair<string,int>(A,0));
        while(!q.empty()) {
            now,c = q.front();
            q.pop();
            bool next = false;// now == B
            for(i=0~n){
                if(now[i] == B[i]) continue;//if the pos is correct.
                for(j=i~n) {//find all right side char
                    if(now[i] == B[j] && now[i] != now[j]) {//if we can swap to correct, and this pos is wrong pos.
                        swap(i,j);
                        if(now is not in mySet){
                            mySet.insert(now);
                            q.push((now,c+1));
                        }
                        swap(i,j);
                        next = true;// now != B
                        break;//left the loop about swaping i
                    }
                }
            }
            if(next == false) return c;// now == B
        }
        return 0;//if no need to swap
    }
```

想法不錯(當下認為)，但看完detail後發現其實不是最好的。

## 參考答案
首先看完一些做法後，我的做法偏向裁支的用法，旦發現許多裁支都做得更好更有規律。

首先提提我的作法是把重複的結點刪除，這是裁支最基本的想法 ~~(雖然我第一時間沒想到)~~ ，但其實如果做法更有規律，能減少更多。舉個例子，有一份code是這樣。

```C++ =
    int kSimilarity(string A, string B) {
        for(int i = 0 ~A.size()){
            if(A[i] != B[i]){
            vector<int>t
                loop(j=i+1 ~ B.size()){
                    if(i,j swap can make two correct point)
                        swap(i,j);
                        return 1 + kSimilarity(A.substring(i+1),B.substring(i+1));
                    else if(B[i] == A[j]) t.push(j)//we can let pos i is correct
                }
                int ret = A.size()-1;// the max times swap
                for(j in t ){
                    swap(i,j);
                    ret = min(ret, 1 + kSimilarity(A.substring(i+1),B.substring(i+1)));
                    swap(i,j);
                }
                return ret;
            }
        }
        return 0;
    }
```
它這做法就很有規律的，確保前半部的字串是正確的情況，再去做後半部的比較，不斷刪減問題，也順便刪剪枝葉，畢竟某字元修正完後就不可能再修正它。即使最後是用recursive用DFS也因為分支夠少而不會令時間變慢，還能節省空間以防BFS的Memory爆開。

## 感想
今天本來想做做一些明顯是graph的題目，但似乎找到一個表面沒有圖題樣子的圖題。至少在一層層的改進上，完成了題目。即使不是最好，但也解決了。