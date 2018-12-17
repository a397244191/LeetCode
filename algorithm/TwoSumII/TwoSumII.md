# Two Sum II - Input array is sorted
復健題。
## 題目介紹及構思
- input
  - numbers(vector< int>)
    - a array sorted.
  - target
    - the target number
- process
  - find two number can sum to target
- output
  - return the index(1-base)

不愧是復健，除了出了一次WA外，還沒發現它input已經sort了。

## 開始
其實題目很簡單，就直接用binary search就可以解決了。

```C++ =
for(i = 0 ~ numbers.size()) {
    ind = binary(numbers[i+1 : end], target - number[i]);
    if(ind != numbers.end()) return {i+1, ind+1};
}
return {-1,-1};
```

結果因為我沒注意到它已經是sorted的array。結果就丟map附index。然後忘了可能有兩個重複值可以當組合，但因為沒紀錄到兩個index導致答案出的index會是相同的問題。稍為修改就過了。

## 參考答案
這裡還有一點可以用unorder_map讓search降到const time(理論)。會更有效率。

## 感想
其實Two Sum題目也做過了，只是為了復健，找了一題不一樣前提的題目來做(可是沒注意題目給的條件導致沒啥意義)。
