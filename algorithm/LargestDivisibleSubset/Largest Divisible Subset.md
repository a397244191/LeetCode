# Largest Divisible Subset
開始尋覓目標，不過修練(X)興趣(O)繼續。
## 題目介紹及構思
- input
  - nums(vector< int>)
    - a set of some integers.
- process
  - find the largest subset.
    - For all pair (a,b) in subset S,  a % b = 0 or b % a = 0.
- output
  - vector< int>
    - the subset S.

因為最後是要找出subset，如果直接遞迴有爆炸疑慮。然後想到最基本的線性紀錄。

## 開始
因為手感還不是很好，怕出現不必要的失誤，所以把整個題目分成幾個階段:前處理，紀錄，後處理。

因為題目說要能互相整除(大除小)，所以有個很簡單的判斷，就是subset從小到大依序後，會是倍數關係，所以只要下一個大的數可以整除目前subset最大的數，即可加入此subset。

### 前處理
因為它只說給一個set，沒說大小順序，而這次題目，不sort的陣列會需要指數成長的遞迴方式解決，所以先將陣列排列好，而為了方便我是從小到大(但反之亦可)。

然後需要兩個紀錄陣列，一個紀錄當前數字(A)，包含所有比它小的數，subset包含A的最大值。這樣可以減少找到A後再去找可以被A整除的其它成員。

為了找到路徑的backtrack，需要紀錄任意數字(A)的前一個整除數，因未統計保證紀錄的數是第一個紀錄陣列最大值，所以不用擔心有錯誤路線(答案有非唯一，且接受所有種類答案)。

### 紀錄
紀錄方式非常簡單，不斷找出可以被當前數字(A)整除的數字，並從第一個紀錄陣列(total)找到最大subset的量值+1，若比當前A的量多，就替換，反之就保持A的值。

```C++ = 
for(int i = 1 ~nums.size() - 1) {
    for(int j = 0 ~ i) {
        if(nums[i] % nums[j] == 0) {
            if(total[i] < total[j] + 1) {
                total[i] = total[j] + 1;
                record[i] = j;
            }
        }
    }
}
```

這裡record是為了backtrack用。

### 後處理
因為精簡紀錄過程到只有紀錄的部分，所以後處理需要找出紀錄值中最大的subset，並backtrack出subset。

```C++ = 
int lastNum = -1,totalNum = 0;
for(int i = 0 ~ nums.size() - 1) {
    if(totalNum < total[i]){
        lastNum = i;
        totalNum = total[i];
    }
}
vector<int> ans;
for(int i = lastNum ; i >= 0 ; ) {
    ans.push_back(nums[i]);
    i = record[i];
}
reverse(ans);
return ans;
```

首先找到最大subset的尾(lastNum)，然後開始backtrack答案到ans中。最後因為我不保證輸出答案的順序要求，所以把答案reverse令它保正由小到大(因為原本方式可以保證由大到小找出答案)。

最後因為人為疏失弄錯loop的邊界導致吃了一個簡單的WA，不然就是一次AC了。

## 參考答案
大致參考了一個較好結果的解法，方法一樣，但在一些設計上是更好的，像是在後處理上有部分可以寫入紀錄中。不過想法是一樣的就不多說什麼。

## 感想
這次題目牽扯到有趣的DP來降低雜度的問題，想法對於有DP概念的人來說應該算簡單的。