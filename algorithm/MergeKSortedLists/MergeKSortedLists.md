# Merge k Sorted Lists
休息一天，做個想法不難，但不用STL麻煩得要死的題目吧。~~(雖然我偷懶用STL了)~~

## 題目介紹及構思
- input
  - lists(vector<ListNode*>)
    - a vector of sorted lists
- process
  - merge those lists.
- output
  - ListNode*
    - a sorted list

難點不在merge上，而是因為list數量多時，比較每個list頭的部分一般比會不是很有效率，要善用工具。

## 開始
因為這種題目沒有太多想法，因為切成不同段並sort好，就是merge sort的核心想法 ~~(應該啦，自己說)~~ ，不過這次有很多段(k)如果要一個個拿來比，時間複雜度會是<a href="https://www.codecogs.com/eqnedit.php?latex=O(kN)" target="_blank"><img src="https://latex.codecogs.com/gif.latex?O(kN)" title="O(kN)" /></a>，N是所有list內的值總數。因為N基本上是無法刪去的，畢竟都有N個數了至少也要全看過一次。但要如何減少比較的次數呢，就是用heap的方式來讓k個數比較從k次變成log(k)次就行了，而我這裡使用STL的priority_queue來完成這部分 ~~(不好意思，就是想偷懶)~~ ，因此結果如下。
```C++ =
ListNode* mergeKLists(vector<ListNode*>& lists) {
    priority_queue<ListNode*,vector<ListNode*>,cmp> pq;
    for(auto l = lists) {
        if(l)
            pq.push(l);
    }
    ListNode* ans = NULL;
    ListNode* tail = NULL;
    while(!pq.empty()) {
        use = pq.top();
        if(!ans) {
            ans = use;
            tail = ans;
        }
        else {
            tail->next = use;
            tail = tail->next;
        }
        pq.pop();
        if(use->next)
            pq.push(use->next);
    }
    return ans;
}    
```

這裡主要注意一些NULL的狀況就沒有問題了。唯一坑人的點是，listNode竟然是空的，弄得炸了RE，修好就沒問題AC了。

## 參考答案
因為想法基本就這樣，不過看解答還是有些有趣的點就來一一說一下。大致分成<a href="https://www.codecogs.com/eqnedit.php?latex=O(Nlog(N))" target="_blank"><img src="https://latex.codecogs.com/gif.latex?O(Nlog(N))" title="O(Nlog(N))" /></a>、<a href="https://www.codecogs.com/eqnedit.php?latex=O(kN)" target="_blank"><img src="https://latex.codecogs.com/gif.latex?O(kN)" title="O(kN)" /></a>跟<a href="https://www.codecogs.com/eqnedit.php?latex=O(Nlog(k))" target="_blank"><img src="https://latex.codecogs.com/gif.latex?O(Nlog(k))" title="O(Nlog(k))" /></a>。

### 直接重來
這雖然完全忽略題目的意義跟想法，但是挺簡單暴力的。就是直接全拉出來跑sort結束這問題(笑)，不過就炸掉題目的美意了。

### 一個個來
第二種複雜度到是有兩個方法，第一個就是直接讓k個頭一個個比，沒有太多想法的方式，就先不提，另一個是說就兩個兩個來，一次只比較兩個list，雖然在想法上是比前一個有點效率，但實際複雜度還是被歸類在一起就是了。

剛好分成k跑N次(一起比較)跟N跑k次(一次拿兩個比較)

### 優化後
對於這裡就很有意思的對上兩個方式分別改進，一次比k個改進法就是我的方法，而對一次比兩個的方式就是把它當merge sort的方式，先兩兩合併(每次不重複使用)，雖然似乎merge次數一樣多，但因為list的值每層都只使用一次(上面說的一次比兩個是指一直合併進其中一個，所以一次合併用過的值會快速逼近N)，這方法似乎比自己寫head簡單吧 ~~(其實我也不知道)~~ 。不過這方法沒有靈活的腦袋了話大概會絆倒炸了幾次吧。

### listNode*
看了其他人code後，其實又發現我的一些問題。像是要串接起來，其實不用使用指標，可以用一個空的頭當作使用，接再next(而之後需要也是取next)，這樣就不用擔心會有一些空指標的問題。

## 感想
主要是compare還是不太會寫，偷偷跑去google一下(笑)