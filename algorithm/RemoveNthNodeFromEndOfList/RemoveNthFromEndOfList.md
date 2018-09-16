# Remove Nth Node From End of List
最近做的題目都在計算，該朝向有點資料結構的部分瞧瞧了。

## 題目介紹及構想
- input
  - head(ListNode*)
    - 單向List的頭指標
  - n(int)
    - 被刪除的是倒數第n的位置
- process
  - 相信input的n是存在一個Node在這List上，並刪除它。
- output
  - output(ListNode*)
    - 刪除倒數第n個後的新List的頭

因為題目有說希望用one-pass解決，所以想法用兩個指標開始找，在n不是0前，只動前面的，當n=0時，讓兩個指標距離維持，最後頭指標為NULL時刪除後指標的下一個。

## 開始
程式如下表示
``` C++ =
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        ListNode temp(0,head),*RF = &temp,now = head;
        while(now){
            now to next;
            if(n) n --;
            else RF to next;
        }
        remove RF->next;
        return temp->next;
    }
    
```

雖然說是中等難度，但這題型相對簡單，沒有太大問題變解決。

## 參考答案
因為題目沒有太多需求，基本概念都是一樣的，只是解答code裡面有先跑一層for拉開N的距離在前進這點有令我困惑一下，可是大致上應該也算是one-pass吧?

## 感想
今天因為有點怠惰，下午並沒有開始做，好險吃飽後有點動力的把今天進度完成了。