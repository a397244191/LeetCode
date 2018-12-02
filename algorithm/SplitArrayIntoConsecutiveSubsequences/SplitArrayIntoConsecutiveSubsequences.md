# Split Array into Consecutive Subsequences
燒腦，但最後很有趣
## 題目介紹及構思
- input
  - nums(vector< int>)
    - a sorted integer array
- process
  - check it can split into some consecutive subsequences at least 3 element.
- output
  - bool
    - we can split array into consecutive subsequences

要考慮數字從何開始，是否連續，跟何時結束。

## 開始
需要思考的問題就是有沒有辦法一掃過去就能知道它是再開始還是接續。而如果斷了，要判斷前面片段是不是足夠3個。最後我考慮出3個暫時狀態：還需要2個才足夠、需要1個才足夠跟已經足夠3個但還能接。

### 計算連續跟總值
所以一開始先保證整段是連續的，而既然保證連續，就去紀錄數量就好。
```C++ =
record.push_back({1});
last = nums[0];
pos = 0;
for(int i = 1 ~nums.size()){
    if(nums[i] == last) record[pos].back() ++;
    else if(diff(nums[i],last) == 1) {
        record[pos].push_back(1);
        last++;
    } else {
        record.push_back({1});
        pos++;
        last = nums[i];
    }
}
```
這裡將nums切成一小段一小段的丟入record。而record每段都是連續的，而`record[i]`中每個值是該值的總量。

### 統計使用量
這時就拿出前面說的三種狀態，存成count，然後利用每次的數量做處理。
```C++ =
for(k = 0 ~ record.size()) {
    count{0,0,0};
    for(i = 0 ~ record[k].size()) {
        next{0,0,0};
        use = record[k][i];
        // 1
        if(count[0] + count[1] > use) return false;
        //2
        use -= count[0];
        next[1] = count[0];
        use -= count[1];
        next[2] = count[1];
        //3
        if(use >= count[2]) {
            use-= count[2];
            next[2] += count[2];
            next[0] = use;
        } else next[2] += use;
        count = next;
    }
    //4
    if(count[0], count[1] != 0 ) return false;
}
//5
return true;
```

1. 先讓現在的值(use)確保可以接續所有未完成的sequeces，如果不行直接結束。
2. 將use減去count[0]跟count[1]並紀錄到next[1]跟next[2]，這表示那些sequence各自增加一個。
3. 如果use比count[2]還多(表示有足夠數量去接續已經足夠3個的值)，而多餘的就去當做另一個開頭(count[0] = use)。而如果不足，就只有use個sequence可以繼續使用。
4. 如果這段record已經用完，卻還有sequence還沒足夠3個，則是false。
5. 如果所有record都沒有false，則是true。

### 精簡
確認半天後，沒有任何意外的AC了。這時發現似乎可以更簡單的完成這部分(就是不用先分好record)，而且如果這樣，就不用花space去紀錄。
```C++ = 
count{0,0,0};
for(i = 0 ~ i < nums.size()) {
    now = nums[i];
    next{0,0,0};
    use = 0;
    // 1
    while(nums[i] == now){
        use++;
        i++;
    } 
    // 2
    // part 1 + 2 + 3
    // 3
    if(i >= nums.size() || nums[i] - nums[i-1] > 1){
        if(count[0] != 0 || count[1] != 0 ) return false;
        count[2] = 0;
    }
}
// 4
return true;
```
1. 去計算重複數量
2. 就是做原本1,2,3的步驟
3. 這部分呢，就是當結束或跟上面record結束一樣，這段sequence不可能連續的時候，去判斷是否還有不到3的sequence。
4. 如果沒事，就是true

精減時，判斷結束忘了做確認，所以吃了一次WA，不過這只是個人疏失，還是成功AC了。

## 參考答案
解答上有兩種做法，可能腦袋有點昏，想了一陣子才清楚。

### 紀錄開頭結尾
兩個值的總數分別是count(x)跟count(y)。可以總結成幾個狀況：
1. x + 1 = y & count(x) > count(y) : 有count(x) - count(y)個sequence在x時結束。
2. x + 1 = y & count(x) < count(y) : 有count(y) - count(x)個sequence在x+1時開始。
3. x + 1 != y : 有count(x)個sequence在x時結束。

這可以開一個start的陣列去儲存開始的點，當有需要結束時去判斷能否有足夠個長度超過3的開始點到結束點。

### 先確保有3個值sequence
這比較有趣，先去紀錄所有值的總數存放map(因為不確定上限值不能開陣列)，然後開始對nums查看。這用tail跟count查看，tail是指他前一個值有足夠3個element當sequence。此時nums得到一個值x，判斷方式如下：
1. count(x) = 0 : 已經被使用完了，跳過。
2. tail(x) > 0 : 有值在這足夠3個sequence繼續接下去。tail(x)--,tail(x+1)++
3. count(x+1),count(x+2) > 0 : 新增一個3個element的sequence。count(x+1)--,count(x+2)--,tail(x+3)++
4. other : 無法構成。fail

這方法很神秘，就是確保3個值當一個sequence，所以不會需要判斷無法構成sequence的問題。

## 感想
可能有點晚的關係，腦筋卡卡，寫起來挺燒腦的。
