# Recover Binary Search Tree
偷懶的下場是折磨自己。

## 題目介紹及構想
- input
  - root(TreeNode*)
    - 樹的root
- process
  - 找出錯誤的兩點，交換
- output
  - void
    - 因為不改變結構，不用回傳。

這題是DFS，題目說要用costant space解決，總之來試試看，想法是掃過去找到錯的數字就交換結束。

## 開始
第二天解決，正確的source code在下方，這只討論出的狀況。
### 做法簡介
DFS下去，找到不在正確範圍內的交換，結束。
### RE
原因，竟然是因為我把left node和right node的push用if else if合起來導致找不到而出錯。
### WA
發現錯誤的點新關係是在樹的左右兩端，我只跟上下關係做處理而錯誤。

當遇到錯誤，不要break，直接回頭找另一端的錯誤位置。
### RE
我還以為不會錯一樣的地方才對啊，結果是最開始code恢復要swap點為NULL而讓迴圈繼續跑的狀況出錯。
### WA
新發現，我第一次WA修改成當遇到錯誤直接回頭找另一邊，這次卻給我往下繼續出現問題的input。

範例測資是

![](https://i.imgur.com/eXJB91u.png)

是要交換紅色兩點來改變。

而後自行發現更複雜的錯誤測資。

![](https://i.imgur.com/y10xJ5f.png)

目前對此解決沒有想法。

第一天卡關在此。

## 第二天
今天在想了一下，把昨天那個用範圍判斷的方式拿掉，這次想法往為什麼<a href="https://www.codecogs.com/eqnedit.php?latex=O(N)" target="_blank"><img src="https://latex.codecogs.com/gif.latex?O(N)" title="O(N)" /></a>空間可以簡單的解決的方向去想。才發現其實想法非常簡單。

``` C++ =
  void recoverTree(TreeNode* root){
    stack<pair<TreeNode*,bool>> s;// root & left use or not
    s.push(root,false);
    // dfs inorder
    while(!s.empty()){
      use = s.pop
      if(left no visit){
        push(right,false);
        push(use,true);
        push(left,false);
      }
      if(last && last > use){
        if(sw1 == NULL) sw1 = last;
        sw2 = use;
      }
      last = use;
    }
    swap(sw1->val,sw2->val);
  }
```

### 開竅後
因為只有兩個錯誤，所以往BST特性去想，想到用inorder的方式探索就會獲得排列好的陣列，只要在裡面找出兩個錯誤的點就可以了。所以空間開到<a href="https://www.codecogs.com/eqnedit.php?latex=O(N)" target="_blank"><img src="https://latex.codecogs.com/gif.latex?O(N)" title="O(N)" /></a>的解決方法那麼簡單。而要如何在constant space解決呢，就是只記錄前一個值，來做比較，出問題後記錄最開始錯的跟最後錯的值做交換就可以了。

### RE?
這裡很有意思的發現，我的left跟right放進stack的順序反了，所以判斷當然錯了，不過還沒submit。

改完丟上去，又RE!?我才發現，當錯誤只出現一次時，我不小心的忘了記錄後面那個，導致它是NULL而出錯，改了一下就解決了。

## 參考答案
本題沒有參考答案，可是當我看到detail時發現，code runtime是140ms時疑問了一下，因為統計數據裡集中在30~60，我就去看看裡面寫的code，咦?怎麼是recursive?我知道DFS用revursive寫很簡單，可是迴圈沒有call function會比較好吧?所以我用recursive寫了一次，順便看看跟它的code差異在哪?

### 差異?
最後很好笑的，我發現問題了，在於我debug的時候不小心放了IO的處理，導致code變慢了，實際上code是很快的。只能說，這裡只接收它自定義的output而沒接收我不小印出來的output導致很好笑的AC卻很慢的結果。~~害我不小心丟了一堆submit去找問題，感覺好像在洗AC率一樣，有點慚愧，不知道能不能刪submit資料，讓它正常點~~

## 感想
總之先丟上東西，希望今天可以解決。

首次挑戰hard，想說這題還行，誰知道有一堆我想不到的測資。

經過這次解題，我發現我對於第一個解決方法太過鑽牛角尖導致沒發現另一條正確路感到羞愧。說好聽點是很熱衷認真，說難聽點可能變成不知變通。不過在經過這次教訓後，我了解到發現盲點的重要~~即使早就知道~~，下次再遇到這樣狀況，可能跟這次一樣，去睡一覺會比較好?
