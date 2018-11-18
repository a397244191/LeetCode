# Minesweeper
這題目名稱好懷念呢，從之前到現在，不知道寫過幾次有bug沒bug的踩地雷呢。
## 題目介紹及構思
- input
  - board(vector<vector< char>>)
    - the map of minesweeper
  - click(vector< int>)
    - the position of clcik
- process
  - open the position of click and other action after opening
- output
  - vector<vector< char>>
    - new status

沒有連續動作的input，所以可以簡單的寫一個DFS。
  
## 開始
沒有麼深奧方式，就是直接DFS不斷開啟。而狀態直接使用board來做判斷依據。

- 'E'
  - calculate the minesweeper near this block. if 0, this block is B, else, this block is the number of minesweeper near this block.
  - if 0, push other block into stack
- 'M'
  - become 'X'.
- other
  - nothing to do.

一個DFS判斷上面三件事情，結束後直接回傳broad。一次AC了。

## 參考答案
實作問題，方法上沒有什麼差別。

## 感想
踩地雷真懷念的題目。不過每次寫地雷難點對我都不是擴展，而是一堆部分交互的部分最辛苦了。