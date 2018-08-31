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
還未解決，不放上source code
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

卡關在此。
## 參考答案
還未參考

## 感想
總之先丟上東西，希望今天可以解決。

首次挑戰hard，想說這題還行，誰知道有一堆我想不到的測資。
