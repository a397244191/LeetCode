# Maximum Frequency Stack
繼昨天hash問題，今天再來一次
## 題目介紹及構想
- input
  - function(vector< string>)
    - call function name
  - value(vector< string>)
    - the input for call function
- process
  - in a stack, we pop the max frequency. if they are the same, pop the number near top.
- output
  - output(int)
    - in function pop, output the top and max frequency.

想法是push需要根據數字作查詢，然後pop須根據次數作查詢。

## 開始
既然被分類到hash table就會用到map，然後既然名稱有stack就用到stack，所以第一個結構是map(int frequency,stack< int> num)的樣子儲存，但是push上出現了一點紛爭，就是我本來只是想根據maxfreqency會發現push時不好查詢，最後的方法依舊是用map<int nums,int freq>來做查詢。

```C++ =
class FreqStack {
    map<int,stack<int>> table;
    map<int,int> freq;
    int maxfreq;
public:
    FreqStack() {
        init maxfreq
    }
    
    void push(int x) {
        freq[x] = freq[x] exist?1: freq[x]+1;
        f = freq[x];
        table[f.push(x);
        maxfreq = max(maxfreq,f);
    }
    
    int pop() {
        n = table[maxfreq].pop();
        freq[n]--;
        if(table[maxfreq] is empty) maxfreq--;
        return n;
    }
};
```

### RE
第一次看到RE，我想說應該是`freq[x]`的關係吧?畢竟沒有初始化會不會`freq[x]++`出現爆炸的數字。然後再收到了RE。

### WA
這是有點突然靈機一動的，我發現table可以用vector阿，為啥要用map呢?結果發現我的vector在pop下去後在push上去會因為push_back而錯位置。

後來AC後回頭看，原來是我忘了做table.pop_back的動作來維持最後一個是maxfreq而已。

### 初始化很重要
因為vector修改失敗，我又回來看看RE的問題，結果竟然不是我的`freq[x]`錯呀，也不是stack用錯阿。是我的maxfreq忘了初始化!!我才想說FreqStack不用寫東西呢!結果就出這個大災難。

## 參考答案
寫完後，發現有參考答案可以看，我就跑去看看了。然後處理就是我的最終版本類似，沒什麼討問點。再去看看比較快的版本，就發現，它們用`vector<vector<int>>`來做table查詢，只要記得pop_back就會很快呢!果然在STL上map雖然方便但比在index是int時還是vector比較方便。

## 感想
這次題目也用了很多STL的部分。繼續習慣這些STL東西跟練習吧。