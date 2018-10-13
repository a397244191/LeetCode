# Sum of Subsequence Widths
最近莫名都選到跟數學有關的題目，算了，來試試。

## 題目介紹及構思
- input
  - A(vector< int>)
    - lenght is equal or less than 20000
    - each element is equal or less than 20000
- process
  - the width of each subsequence is the diff between max number and min number.
- output
  - int
    - a number % 1e9+7

數字很明顯的不給用<a href="https://www.codecogs.com/eqnedit.php?latex=O(N^2)" target="_blank"><img src="https://latex.codecogs.com/gif.latex?O(N^2)" title="O(N^2)" /></a>，又沒有開log的地方，看來要想個linear的解法。

## 開始
這數字即使要讓所有數字配對一次都要<a href="https://www.codecogs.com/eqnedit.php?latex=O(N^2)" target="_blank"><img src="https://latex.codecogs.com/gif.latex?O(N^2)" title="O(N^2)" /></a>，光想就很頭痛，為了簡化題目就先sort一下。

### sort後規律
因為亂跳很難想辦法，就先sort看看有什麼好想法，而sort完後想到一個不錯的規律，就是從頭尾開始，因為這樣保證選取兩個數為最大跟最小，那是不適中間可以隨意組合?而中間隨意組合就是pascal的一排，而這一排相等於<a href="https://www.codecogs.com/eqnedit.php?latex=2^n" target="_blank"><img src="https://latex.codecogs.com/gif.latex?2^n" title="2^n" /></a>。這樣就不用考慮會有幾個，直接乘上去就行，看來解決一半問題了。

### 頭尾組合
這組合會很簡單的增加，例如:1,2,3,4,5,6,7,8的例子下，第一組會是(1,8)，再來是(1,7)跟(2,8)，依此類推，有趣的是每次只增加一個。因為任兩相鄰組合都會產生一個重複，所以不會一次增加很多。那這樣是不是有規律呢?這是要考慮的問題。後來發現，因為它的width是尾(大的)減去頭(小的)，所以會產生很好玩的現象如下。

1. 8 - 1 => (8,1)
2. 7 - 1 + 8 - 2 =>(8,1) + (7,2)
3. 6 - 1 + 7 - 2 + 8 - 3 => (8,1) + (7,2) + (6,3)

因為每個數字都會因為分裂而保留一個，然後因為和另一組分裂重疊而保證一個，所以每次只會增加一組更小的組合。因為每次組合不再需要每個都去算一次，而是直接增加兩個數字就可以了。

### 結論
推斷完兩個原因後，就能很簡單的知道每次都會增加`(lastwidth + (A[right] - A[left])) * 2^n`的結論。因此完成loop。

``` C++ = 
int sumSubseqWidths(vector<int>& A) {
    sum = 0;
    MOD = 1000000007;   
    sort(A.begin(),A.end());
    powTwo = 1;
    left = 0, right = A.size() - 1;
    sub = 0;
    while(left < A.size() && right >= 0) {
        sub = (sub + A[right] - A[left]) % MOD;
        long long int add = ((long long int)sub * powTwo) % MOD;
        sum += add;        
        sum %= MOD;
        left++;
        right--;
        powTwo = (powTwo<<1) % MOD;
    }        
    return sum;
}
```

這裡只有add會爆int範圍，為了減少long long的計算而只用到它 ~~(忘了哪聽到long long計算比較慢)~~ 。結果因此吃虧了，因為忘了在裡面強轉而導致數字先爆int範圍導致答案錯了。修改後AC。

## 參考答案
因為想法出來後就是個簡單的題目，所以解答也不多敘述了大致都跟我一樣。

## 感想
這次題目十分漂亮，只是為啥每次數學解時常常遇到pascal啊。是不是排列組合太經典了呢。 ~~(又或是這本身就是精簡電腦最擅長的重複運算方法呢)~~
