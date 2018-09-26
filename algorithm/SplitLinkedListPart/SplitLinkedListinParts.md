# Split Linked List in Parts
最近都是邏輯題，回來考慮一些資料結構題。
## 題目介紹及構思
- input
  - root(ListNode*)
    - val(int)
    - next(ListNode*)
- process
  - split the link list
- output
  - ans(vector<ListNode*>)
    - No two lists have a size differing by more than 1.

找到長度分配好數量就沒問題了。

## 開始
題目大致就是分成找長度跟分配問題。

### 長度及分配
長度很簡單，就是指標一直跑下去讓它跑到空為止一值增加長度就可以。而分配上，就是先用除的均分，多餘的就分配給前面的段，這樣就能滿足兩個條件:任兩段長度差不能多於一，及每一段都比後面的長或是相同。所以大致如下。
```C++ =
len = 0;
while(use = NULL){
    len++;
    use = use->next;
}
partNum = len/k, addOne = len%k;
```

### 製造List陣列
因為我不太清楚題目input是否能被變動，所以我選擇了做一個新的方式。因為分段還有出現空list的狀況，讓我思考很久。不過運用一些方式解決了。
```C++ = 
use = root;
for(i = 0 ~ k){
    head = go = NULL;
    if(i <moreOneP){
        head = go = new ListNode(use->val);
        use = use->next;
    }
    for(j = 0 ~ eachPartN){
        now = new ListNode(use->val);
        if(go != NULL)
            go->next = now;
        else head = now;
            go = now;
        use = use->next;
    }
    ans.push_back(head);
}
return ans;
```

首先對於需要多一個的先取出一個值當頭，然後用迴圈不斷取下一個，而對於那些沒有頭的，在裡面創造一個後，讓頭指向創造出來的。

題目沒有複雜到會有陷阱的地方，所以一次AC。

## 參考答案
解法大致跟我想的沒有出入，注意到的大概就兩點。

### 直接切input
這做法簡單粗暴，完全不理會有沒有可能對input修改造成問題，當然這裡只有這個小問題所以沒有影響，但果然還是怕怕的。
```C++ = 
t = root
for(i = 0 ~ k)
{
    q = p = t;
    while(p go next until p is null or the number is enough);
    t = p->next;
    p->next = NULL;
    ans.push_back(q);
}
```
直接跑到足夠數量切斷，然後再往下一段跑。因為只有做改變值的方式，所以效率極高。但缺點是對於之後那個root拿去做別的事情的希望是不可能的了。

### 創造空頭
這方法跟我的一樣，但寫得更為精簡。因為他用先製造出一個頭的方式，來防止沒有頭的狀況，所以很簡單的就能完成後面動作。
```C++ = 
for(i = 0 ~ k){
    write = head = new ListNode(0)
    while(the number is enough){
        write = write->next = new ListNode(use->val);
        use = use->val;
    }
    ans.push_back(head->next);
}
```
產生一個不需要的頭，就能讓指標不用擔心head或是write是NULL的情況，很好處理各種例外。

## 感想
要解決簡單題目很簡單，但要想的深入很難。有時候因為想太簡單而做的複雜是常有之事，總之多想想吧。
