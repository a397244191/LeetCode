# Reverse Nodes in k-Group
我才不會說看錯題目了呢QQ

## 題目介紹及構思
- input
  - head(ListNode*)
  - k(int)
- process
  - every k node reverse. if not enough, don't need to do anything.
- output
  - ListNode*
    - the new list head

就是想辦法每k個反轉而已 ~~(一開始看成頭k個)~~

## 開始
前面犯蠢不多贅述，所以我打算把k個反轉拉出來寫。

### 子段反轉
就是傳入頭尾，並反轉此段(保證頭尾都有值)，而這裡要反轉的是頭的下一個到尾。並回傳下一次頭(就是這段反轉後的尾)
```C++ =
ListNode* SubReverse(ListNode* head, ListNode* tail) {
    use = head->next;
    newhead = use;
    rList.next = tail->next;
    while(rList.next!=tail) {
        temp =use->next;
        use->next = rList.next;
        rList.next = use;
        use = temp;
        if(temp) temp = temp->next;
    }
    head->next = rList.next;
    return newhead;
}
```
先將新的list(rList)接上不用反轉的地方(尾端的下一個)，然後開始重複一個動作，use指向rList.next(已被反轉的部分)，而rList再接上use就能做完反轉的部分，一直直到tail也被反轉玩而結束。最後再讓反轉段的前一個(head)接上rList.next就完成了。而回傳新的頭(也就是反轉後的最後一個值)，以便後面繼續。

### 搜尋子段反轉頭尾
先用一個root接上head(以防一些空指標問題)，然後開始找k個值，有找到開始反轉而回傳的就繼續使用。直到沒有足夠長度可以反轉或結束後，就回傳答案。
```C++ =
ListNode* reverseKGroup(ListNode* head, int k) {
    root.next = head;
    use = &root;
    while(use) {
        tail = use->next;
        for(i = 1 ~ k) {
            if(tail) tail = tail->next;
        }
        if(!tail) return root.next;
        use = SubReverse(use,tail);
    }
    return root.next;
}
```
之後回傳root.next將整段回傳結束。

除了看錯題目吃了RE ~~(看到還想說題目寫錯了吧，空list長度不是0嘛?怎麼會有反轉1出現)~~ 以外，一次就AC了。

## 參考答案
看了幾個方式，因為題目就那樣子，所以也沒太大的變化，就不多提了。

## 感想
這次題型難度不高，就是對指標認識更多而已，不了傻傻的看錯題目外，沒什麼問題。