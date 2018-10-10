# Decoded String at Index
題目想法很簡單，做法要思考。
## 題目介紹及構思
- input
  - S(string)
    - code string
    - S.length() is less than 100;
    - char is lowerletter or digit
    - letter is lowerletter
    - first char is letter
  - K(int)
    - find the Kth char in encode string
    - <a href="https://www.codecogs.com/eqnedit.php?latex=K\le&space;10^9" target="_blank"><img src="https://latex.codecogs.com/gif.latex?K\le&space;10^9" title="K\le 10^9" /></a>
- process
  - do encode and find the K-th
- output
  - string
    - the K-th char

因為encode完後會有<a href="https://www.codecogs.com/eqnedit.php?latex=2^{63}" target="_blank"><img src="https://latex.codecogs.com/gif.latex?2^{63}" title="2^{63}" /></a>個字母，所以不太可能真的跑去encode，只能做數字解。

## 開始
因為每次遇到數字X(X = 2 ~ 9)，就要重複X次數字前的字串，雖然數字不用疊是好處理，但一直乘很容易爆數字上限，好顯它有限制上限小於long long，還有辦法直接算。

### 分解字串
首先要知道要怎麼在不需要一直repeate字串的情況下分解字串，不然一展開就會直接爆炸。最後我想到一個記錄的方式。開兩個陣列一個記錄重複字串一個記錄前面所有字串的次數。舉個例子`abc234de2g3`就會是下表格。
|code|repeate|
|:---:|:----:|
| abc |  24  |
|  de |   2  |
|  g  |   3  |

24表示abc重複24次，2表示abc重複24+de重複2次，依此類推的分解字串S。而在其中做了點小撇步(沒多大意義)，就是當總數超過K後就不再記錄。

```C++ = 
str;
repeateT;
temp = S[0];
rep = 1;
total = 0;
for(i = 1 ~ N) {
    if(S[i] is digit){
        rep *= S[i];
        if(!temp.empty()){
            str.push_back(temp);
            temp = "";
        }
    } else{
        if(temp.empty()){
            repeateT.push_back(rep);
            rep = 1;
        }
        temp += S[i];
    }
}
if(!temp.empty()) str.push_back(temp);
if(repeateT.size() < str.size()) repeateT.push_back(rep);
```

而這裡我本來少做了一件事情是，我以為題目有保證數字結尾後來才發現沒有而吃了RE ~~(其實submit前我的第六感告訴我有這問題，不信邪的丟上去才吃了一個RE)~~ 。

### 開始找出處
因為字串不斷repeate，所以可以利用mod的方式找到位置，為了找這位置，我再用了一個陣列儲存，該到加上該段會被repeate的數量。依上面範例為例會是`[3,74,149]`，第一段是abc重複所以長度3，第二段會是abc(24)de重複，所以長度是24 * 3 + 2 = 74，依此類推。

之後不斷做mod跟確認範圍的方式找到正確答案。
```C++ =
strSum.push_back(str[0].length());
for(int i = 1 ~ N) {
    strSum.push_back(strSum.back() * repeateT[i-1] + str[i].length());
}

for(int i N-1 ~ 0) {
    K = (K-1) % strSum[i] + 1;// index 1
    if(K > strSum[i] - str[i].length()){// K repeate in str[i]
        return str[i].substr(K - (strSum[i] - str[i].length()) - 1,1);
    } else { // K repeate in next str
        i--;    
    }
}
```
用了-1mod+1的方式得到index為1的值。依此下去找到正確位置。

經過一陣思考跟被坑後AC了。

## 參考答案
參考答案方法跟我想的一樣，我是很想這樣說啦。

但它的寫法不用存東西也不用算什麼，兩次迴圈就解決我考慮很久記錄跟思考才想到的解決方法。所以基本上想法一樣，但做法是我的極簡化。所以就不多說什麼了，留下code就行。

```C++ = 

string decodeAtIndex(string S, int K) {
    N = S.size();
    size = 0;
    // Find size = length of decoded string
    for (i = 0 ~ N) {
        if (S[i] is digit)
            size *= S[i];
        else
            size++;
    }

    for (i = N - 1 ~ 0) {
        K %= size;
        if (K == 0 && S[i] is letter)
            return S[i];

        if (S[i] is digit)
            size /= S[i];
        else
            size--;
    }
}
```
不需要記錄只要往回察看就能解決問題。 ~~(事後看到tag是stack我才發現我想太多了)~~

## 感想
這次沒有很難，但要完全理解做法跟寫得很精簡不花空間很難。只能說又學到了一課?