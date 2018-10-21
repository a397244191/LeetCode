# Regular Expression Matching
還是很不習慣新畫面，又懶得自己處理input只好努力習慣吧。

## 題目介紹及構思
- input
  - s(string)
    - be empty and contains only lowercase letters a-z.
  - p(string)
    - be empty and contains only lowercase letters a-z, and characters like . or *.
- process
  - '.' can replace to any element, and '*' is repeate zero or more last element.
  - check p == s
- output
  - bool
    if p == s return true
    
DP問題，兩字串比對，似乎有很多可以參考的想法。

## 開始
首先需要分析特例(後來發現因為DP表要+1所以沒差，反而因為判這特例吃了幾次WA)。大致上就是兩個有一為空的時會出現狀況。

### 特例處理
大致上先從p是空的開始，只要s也是空的就對了，但如果不是就是錯的。而s為空比較複雜，需要判斷p是否可以兼容空的字串。
```C++ = 
isEmpty(string s){
    if(s.back() != '*') return false;
    for(int i = 0~length()-1){
        if(s[i] != '*' && s[i+1] != '*') return false;
    }
    return true;
}
```

基本上就是看最後是不是可以repeate(後來發現是奇數個問題，先判奇數會更好但覺得沒必要)跟是否出現有不是repeate的字元。而其他狀況就是可以包含空字串。

### 正式部分
一開始想說跟之前某個題目一樣倒著看試試，但發現還是有些問題，或是去記錄連續重複的字元跟是否可重複，但又發現有'.'這個干涉。最後想到了跟LCS相仿的二維DP嘗試看看。

#### DP大小
因為要記錄兩為空的狀態，所以需要各加1，而因為string p的部分要排除'*'的關係所以要先計算出非'*'的字元數目。所以假設P為string p的非'*'長度，而S為string s的長度，則DP表就是(P+1)(S+1)的大小。

#### 解析DP內容
DP是一個bool二維陣列，而記錄的是當下的`DP[i][j]`就是p.sub(0,i)是否等於s.sub(0,j)，這裡注意的是，p的長是指不包含'*'的p長，而string 的index單位是從1開始。以下用"aaabb"跟"a*aab*bc*"來看

|p string\s string|0|a|a|a|b|b|
|:---:|:---:|:---:|:---:|:---:|:---:|:---:|
|0 |1|0|0|0|0|0|
|a*|1|1|1|1|0|0|
|a |0|1|1|1|0|0|
|a |0|0|1|1|0|0|
|b*|0|0|1|1|1|1|
|b |0|0|1|1|1|1|
|c*|0|0|1|1|1|1|

規則先不提，可以看到~~(太長了啦)~~，`DP[1][3]`是指"a*"跟"aaa"是否相同的表示。

#### DP規則
本部分其是最重要的重點在這，就是什麼時候會是正確的。首先，狀況分兩種，相同跟不相同，而字元也分兩種，有repeate跟沒有的。而這四種狀況可以分成變成。

|is same|is repeated|get|
|:---:|:---:|:---:|
|T|T|`check[i][j] = check[i-1][j] || check[i-1][j-1] || check[i][j-1]`|
|T|F|`check[i][j] = check[i-1][j-1]`|
|F|T|`check[i][j] = check[i-1][j]`|
|F|F|`check[i][j] = flase`|

敘述就是以下幾種統合
1. 當相同時可以表示s跟p都增加一個字元(斜對角)，而如果又是repeate就可以等同s延伸字元(從左)。
2. 當repeate時，表示可以為空字串，所以可以等同於s增加字元但沒影響(從上)。
3. 當他們不同時，且又不是repeate，就表示不合，為false

所以判斷補分可以寫成
```C++ = 
if(rep) {
    check[i][j] = check[i-1][j];//rule 2
    if(same) check[i][j] |= check[i-1][j-1] || check[i][j-1];// rule 1
}else {
    if(same) check[i][j] = check[i-1][j-1];// rule 1
    // rule 3
}
```
因為預設false所以不用擔心其他狀況。而這裡same是包含p是'-'的情況。

最後回傳check.back().back()的真值就是答案。

### 一些WA
大致上方向是對的但包含一些愚蠢的submit還是有些討論部分。

#### 愚蠢想法
在判斷特例時，因為一開始想說就拚是否連續兩個非'*'就好，但發現如果長度為一(其實是奇數)就會出現只有一個非'*'的狀況而判錯。修改後，又發現是最後字元部分非'*'而判錯，經過兩次修正後成功。

#### '-'跟same
一開始不知道怎麼回事，我把'-'跟相同判開發現有不同狀況(實為相同，想錯了)而導致一個奇怪的組合判斷錯誤。修正後又因為忘了把debug code拿掉再吃一次WA。

總之經過上述狀況跟問題，最後成功AC了。

## 參考答案
參考解答有兩個，一個是recursive另一個是DP。

### recursive
這一開始我擔心的複雜度似乎沒出現。

他的想法簡單，兩種想法
1. repeate時，可以跳過該repeate繼續 -> rec(p+2,s)
2. 現在比對相同時，非repeate -> rec(p+1,s+1)
3. repeate且現在比對相同時，繼續判斷repeate延伸 -> rec(p,s+1)

依照三種可能不斷遞回(但因為狀況分類，最多存在兩個分支，最少為0)，若p跑完或s跑完，另一者沒有則為flase。反之為true。然後利用binary operator的特性，將重要的放置前，則可以保證不會recursive過多部分(裁支)。不過因為這展開沒有簡單的分析，不過看這解法出現應該是能保證沒問題啦~~(應該)~~ 。

### DP
至於DP部分，因為大致想法就是那樣，只差在做法上有top跟buttom的區分，不過表格應該沒有區別，就不多談了。

## 感想
基本的DP題，建立上沒有太多問題，看來還行。
