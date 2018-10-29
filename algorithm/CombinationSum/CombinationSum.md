# Combination Sum
到底要怎樣，才會發生這種事。桌上筆跡跟記憶中都解過這個題目，甚至印象中還記得一些自己寫的題解內容還有自言自語的說哪種方法會更快什麼的。可是解題網站、git記錄跟電腦記錄，卻都沒有被解過的跡象?!這太神奇了。

## 題目介紹及構思
- input
  - cadidates(vector< int>)
    - a list about some number
  - target(int)
    - a number
- process
  - use cadidates to combination sum to target.
  - we can use 0 or more times the any element in cadidates.
- output
  - vector<vector< int>>
    - a list of all combination pair.
## 開始
總之每個數字當一層遞迴，直到target歸0即記錄就好。

```C++ =

vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
    cand = candidates;
    vector<int> use;
    combination(target,0,use);
    return ans;
}
void combination(target,now,use) {
    if(target == 0){
        ans.push_back(use);
        return ;
    }
    else if(target < 0 || now >= cand.size()) return ;
    int c = 0;
    for(int i = 0 ; cand[now]*i <= target ; i++) {// add 0 or more(sum less than target)
        c++;
        if(i > 0) use.push_back(cand[now]);
        combination(target - cand[now] * i, now+1,use);
    }
    // pop all element in this part
    for(int i = 0 ; i < c-1 ; i++) {
        use.pop_back();
    }
}
```
~~(明明寫過的東西，弄的我不想寫題解了)~~總之因為要窮舉，所以直接利用遞迴一個個找到並解決。當target為0時表示找到了，而非0卻用光所有element或target超過0就是沒有。這裡空間複雜，扣除答案部分就是cadidates的長度，而時間呢因為每次展開的不同不好計算就不提了。~~(第一次對其實有點複雜的題目那麼敷衍)~~

## 參考答案
~~(當初，我記憶中，是用一個vector< vector>再那當參數傳遞，然後挺慢的，發現原有人把二維拉出來當class變數就能解決這問題。明明記得阿，怎麼都沒有記錄阿!!!)~~
總之，其它的code方向跟我差不多，畢竟要把所有組合的list弄出來，不然這可以改用DP的背包問題解決。

## 感想
想說差點斷坑一周，要上來繼續努力的，結果遇到了靈異現象，真是奇怪。
