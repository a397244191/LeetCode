# Two Sum
第一次leetcode使用，就先從簡單題目下手吧。雖然被坑了兩次，可是這比競賽時好的地方在於會告訴你什麼測資爆掉欸！突然覺得好佛心哦！！！

## 題目介紹及構想
- input
  - nums(vector< int>)
    - 一堆數字陣列
  - target(int)
    - 一個目標加起來的數字
- process
  - 找尋nums中，兩個可以加起來等於target的
- output
  - ans(vector< int>)
    - 兩個數字，是加起來等於target的數字在nums的index

想法是，最簡單的二次迴圈掃過去找到加起來等於target的回傳。可是做過競賽的看到<a href="https://www.codecogs.com/eqnedit.php?latex=O(N^2)" target="_blank"><img src="https://latex.codecogs.com/gif.latex?O(N^2)" title="O(N^2)" /></a>表示不行 ~~(莫名其妙的任性和堅持)~~，就想到最簡單的binary search啦，還可以順便練習自己不熟的STL，感受到一舉兩得的方式壓到<a href="https://www.codecogs.com/eqnedit.php?latex=O(NlogN)" target="_blank"><img src="https://latex.codecogs.com/gif.latex?O(NlogN)" title="O(NlogN)" /></a>。

## 開始
啊，一進去看到的是class Solution，瞬間就發現跟競賽不一樣，不是一個完整的code？想了想應該適用裡面的function完成就好吧，可是因為STL不熟，另外開啟IDE來測試執行(後來才發現下面有Run code可以用)。
好傻好天真的我練習了一下，就簡單的sort、for-loop、lower_bound、return vector，看起來完美的完成了。
以下是大致上內容
``` C++ =
    vector<int> twoSum(vector<int>& nums, int target) {
        sort(nums)
        for(i = 0~nums.size()){
            low = lowerbound;
            if(*low == findNum){
                return ans// i,low-begin()
            }
        }
    }
```
## 遭逢失敗
經歷兩次失敗，發現自己沒看清題目介紹。
### sort錯了嗎
啊～WA了！這才發現，我不該sort nums的，這樣原本的位置出不來啊！改了一下，多用了一個vector< int> use(nums)來做動作。
### 同一個數！？
發現這錯後，才知道"You may assume that each input would have exactly one solution, and you may not use the same element twice." 裡面的" you may not use the same element twice."不是說我可以相信數字都不一樣，而是說，你不能用同樣的element組合。
## 結束了?
改完兩個bug後，Ac終於現身了。我發現有個解答可以看，點進去看了一下，第一個答案，標準雙層迴圈，很好，可以。第二個震驚了我，竟然不是<a href="https://www.codecogs.com/eqnedit.php?latex=O(NlogN)" target="_blank"><img src="https://latex.codecogs.com/gif.latex?O(NlogN)" title="O(NlogN)" /></a>直接跳到<a href="https://www.codecogs.com/eqnedit.php?latex=O(N)" target="_blank"><img src="https://latex.codecogs.com/gif.latex?O(N)" title="O(N)" /></a>！？才發現有更簡單的hash解法啊！看來我修行還不夠，只能想到最基本的想法。
## 假解?
### 想法
我寫完後想了一下，發現我寫的不夠好，因為如果裡面能組成target的數字是相同的，但我只有一個這數字呢?因為答案是另一個解。
### 驗證後
因為他說，我可以保證有一解，而且我是sort從最小的開始，所以遇到target/2的數字時，已經找完全部陣列了，如果還沒有就是無解，所以一定會有兩個target/2的數字，所以想法不成立。


## 感想
這是我開始leetcode的第一題，訝異的judge code需求不同、好心的給錯誤結果、更高思維的解法、自以為的假答案。雖然有些東西不是第一次，但這讓我覺得這東西挺有趣的。而後面東補補西補補的Ac code，讓我覺得明明這麼漂亮的想法被我寫的有點冗長，有點難看感到慚愧。
