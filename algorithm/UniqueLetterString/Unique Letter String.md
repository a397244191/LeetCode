# Unique Letter String
找出字串中所有子字串的unique的數量。

## 題目介紹及構想
- input
  - S(string)
    - 輸入的字串
- process
  - 計算所有子字串，並算出它們總共的 the number of unique Letter.
- output
  - result(int)
    - 結果數字需要mod(1e9)

一開始我想把每個子字串跑一次，但這樣是<a href="https://www.codecogs.com/eqnedit.php?latex=O(N^3)" target="_blank"><img src="https://latex.codecogs.com/gif.latex?O(N^3)" title="O(N^3)" /></a>，所以要想壓下去。

## 開始
以下N都是字串長

一開始想當然是最簡單的<a href="https://www.codecogs.com/eqnedit.php?latex=O(N^3)" target="_blank"><img src="https://latex.codecogs.com/gif.latex?O(N^3)" title="O(N^3)" /></a>解法，每個區間跑一次算出這區間的unique letter。開始分析後覺得他可以做成recursive，這樣似乎會遞回到深處爆炸，就想到DP方式。但DP對於S = 10000似乎有點微妙，local的變數似乎無法承受<a href="https://www.codecogs.com/eqnedit.php?latex=10^8" target="_blank"><img src="https://latex.codecogs.com/gif.latex?10^8" title="10^8" /></a>的數量。最後我開始考慮對於DP分解成迴圈的想法是否能用<a href="https://www.codecogs.com/eqnedit.php?latex=O(N^2)" target="_blank"><img src="https://latex.codecogs.com/gif.latex?O(N^2)" title="O(N^2)" /></a>來做處理，最後想到一個<a href="https://www.codecogs.com/eqnedit.php?latex=O(N)" target="_blank"><img src="https://latex.codecogs.com/gif.latex?O(N)" title="O(N)" /></a>的解法並且空間也是<a href="https://www.codecogs.com/eqnedit.php?latex=O(N)" target="_blank"><img src="https://latex.codecogs.com/gif.latex?O(N)" title="O(N)" /></a> ~~(當然可以壓到const space不過寫法上就個人認為有點不美觀)~~ 。

``` C++ =
    int uniqueLetterString(string S) {
        bool check[26] = {false};
        find all char exist in S, set check[it] = true;
        int result = 0;
        for(i = 0~26) {
            char findCh = (char)(i + 'A');
            if no this char continue
            int last = 0,use = 0;
            string tempS = findCh + S + findCh;//set the new string, let the head and tail is findCh
            loop(all char in tempS by j ) {
                if tempS[j] is findCh {
                    the result add (use-last)*(j-use), and mod the modNum
                    if(last != use) last = use;//last go next 
                    use = j;//use go next
                }
            }
        }
        return result;
    }
```
整段程式複雜度是const<a href="https://www.codecogs.com/eqnedit.php?latex=O(N)" target="_blank"><img src="https://latex.codecogs.com/gif.latex?O(N)" title="O(N)" /></a>，所以依舊是<a href="https://www.codecogs.com/eqnedit.php?latex=O(N)" target="_blank"><img src="https://latex.codecogs.com/gif.latex?O(N)" title="O(N)" /></a>，而space因為複製一段S來用所以也是<a href="https://www.codecogs.com/eqnedit.php?latex=O(N)" target="_blank"><img src="https://latex.codecogs.com/gif.latex?O(N)" title="O(N)" /></a>，不過這部分加上一些處理就可以是不必要的空間。

想法很簡單，就是對某字元做搜尋，它會被當最unique letter的狀況只有包含它並前整段substring都沒有它，發生的情況只有它前一個跟後一個相同字元中間區段，而這區段因該字元位置做區分，做為起點跟終點，所以總共包含該字元的子字串數量有left * right，然後依次該類字元做一次，共做所有字元(A~Z，因為他說只有大寫字母)。最後結果就會是所有子字串所有unique letter的量。有想過每個字元處理事情的部分寫成陣列儲存，在同一次迴圈內做了話會比較快，但想用最開始的想法完成就沒去用了。不然架構如下

```C++ = 
    int uniqueLetterString(string S) {
        int last[26] = -1;
        int use[26] = -1;
        init last and use
        for(i = 0 ; i < S.length();i++){
            int now = (int)(S[i] - 'A');
            result += (use[now] - last[now]) * (i - use[now]);
            result%=MODNUM;
            if(last != use) last = use;
            use = i;
        }
        for(i = 0 ~ 26){
            result += (use[i] - last[i]) * (S.length() - use[i]);
            result%=MODNUM;
        }
        return result;
    
    }
```

打完後發現好精簡，似乎應該用這版本。不僅時間複雜度一樣但更快，空間複雜度還是const。實際submit快了4ms。看來難看都是自己在說，其實會很好。而兩種方式都是一次AC，表示我對細節上還是有注意透徹。

## 參考答案
其實解答狀況跟我做法大致相同，不過他們都是用hash table配上list去做處理，大致上空間都是<a href="https://www.codecogs.com/eqnedit.php?latex=O(N)" target="_blank"><img src="https://latex.codecogs.com/gif.latex?O(N)" title="O(N)" /></a>而時間也是<a href="https://www.codecogs.com/eqnedit.php?latex=O(N)" target="_blank"><img src="https://latex.codecogs.com/gif.latex?O(N)" title="O(N)" /></a>，做法是把index放進hashtable的list裡，然後再每個list都處理一次，處理次數總和剛好是N。

## 感想
難度很高，如果是一開始處理這類型了話會很直接完但想破頭吧，但有了一些概念想法堆積，至少可以在有限時間內想到時間上最佳的複雜度 ~~(畢竟做過一些題目後，對於最佳複雜度心裡有個底)~~ 跟持續思考去reduce它的space需求。這兩點在現在的我看來是感到滿意的。

順帶一提，看到解答有一個英文詞彙"on the fly"，就想到當年上課時老師用誇張的語氣說有些人最喜歡聽到這詞，因為感覺就是不用使用空間一樣。真的自己看到後會心一笑。
