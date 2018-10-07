# Chalkboard XOR Game
數學吸引人的地方，在於它看起來很難，卻往往有一個簡單精美的解法在那裡。你不知道它，但看到後卻印象深刻。

## 題目介紹及構思
- input
  - nums(vector< int>)
    - a list of numbers that are non zero.
- process
  - xor game, play move a numver and other numbers xor sum is 0, he is loser.
- output
  - bool
    - if first player is win, return true

XOR精美題目

## 開始
我一開始想，既然沒有用到任何特殊方法(tag顯示)，那絕對不是展開找解。只有數學能想到答案。

### XOR
先談談XOR特性，它的真值表如下
|  A  |  B  | A XOR B |
|:---:|:---:|:-------:|
|  T  |  T  |    F    |
|  T  |  F  |    T    |
|  F  |  T  |    T    |
|  F  |  F  |    F    |

當兩個相同時就會為0，相反為1。所以兩個完全相同的數XOR就會是0，而0跟數XOR會是該數。因此，當有N個相同數X的情況下，XOR合會因為N為奇數而為X偶數個為0。
### 為0者輸
談談這遊戲，只要你拿走數字後XOR合是0，就輸了。而即使舉個簡單一個範例，如果要展開，就會是一個Exponential的展開，所以一定有更合乎邏輯的想法。不過我先對一個5個數字的題目展開，結果是只要對方不直接選擇自己輸的情況，Alice(先手)輸了。 ~~(不過這展開超多個，好累)~~

### 先手必敗?
因此我考慮，在最後一次前讓對方先輸，但這幾乎是不可能的，因為你要讓對方選擇只有輸的選項只會在剩下奇數個相同數的情況，但這情況只發生在Alice開始為偶數個的情況，但如果開始時為偶數個Alice不必挑狀況(不直接選歸0選項)就會贏了。

### 輪流法則
所以大致上應該可以發現一個狀況。
| first | nums number |  result  |
|:-----:|:-----------:|:--------:|
| Alice |     even    | Alice win|
| Alice |      odd    |Alice lose|
|  Bob  |     even    |Alice lose|
|  Bob  |      odd    | Alice win|

因此我只要掃過去，遇到XOR合歸0時修改誰先手(因為這坨0可以做先手交換，如果奇數個換人，偶數個不變)並且nums總數歸0。最後就會產生這四種結果了。

### 轉換
```C++ = 
bool xorGame(vector<int>& nums) {
    xorNum = 0;
    count = 0;
    Alicefirst = true;
    for(i = 0 ~ n){
        count ++;
        xorNum XOR nums[i];
        if(xorNum == 0) {
            switch Alicefirst by count
            count = 0;
        }
    }
    return (Alicefirst ^ (count%2 != 0));
    // if first and even or nofirst and odd
    }
```
很簡單的想法，結果吃WA了。

### WA原因
其實原因很簡單，我看錯題意以為它有說開始全部XOR不為0。所以我加設了一個`if(xorNum == 0) return true`，因為一開始就是0，所以Alice贏。

經過一番波折AC了。

## 參考答案
我只是照著遊戲最加思考去做，但事實上，有個完全不用管過程的解法(雖然基本上一樣啦)。
```C++ =
for(all) xorN XOR nums[i]
return (xorN == 0) || (nums.size()%2 == 0);
```
沒看錯，其實根本不用管過程，只要全部是偶數個Alice必勝，而總合0亦然。其他狀況就輸。而這個方式的證明其實就是我解題的想法最終答案。如果我能想到再多一點，其實就會是參考解答了。

## 感想
單純的問題，誇張的展開，複雜的可能，簡單的解法。雖然很難，但是想通就是個很簡單的題目。