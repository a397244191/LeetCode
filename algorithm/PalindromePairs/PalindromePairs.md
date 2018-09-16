# Palindrome Pairs
不該每天都做應該做得出來的題目。

## 題目介紹及構想
- input
  - words(vector< string>)
    - 一堆字串組
- process
  - 判斷是否有兩個字串組合起來是palindrome string。
- output
  - result(vector<vecotr< int>>)
    - 全部配對組

今天有點不一樣的是，我先參考了答案再回來寫。

## 參考答案
每次都是在做自己會的東西，有意義嗎?今天決定去寫之前沒怎麼嘗試過的hash題目。畢竟hash我知道它也認識，但就沒用過。

### 選擇題目
在hash table找了半天，這題感覺很不錯就決定是他了。

### 分析題目
題目最簡單想法是將所有字串做組合，再去看是否為palindrome。而這樣想法的結果是<a href="https://www.codecogs.com/eqnedit.php?latex=O(N^{2}k)" target="_blank"><img src="https://latex.codecogs.com/gif.latex?O(N^{2}k)" title="O(N^{2}k)" /></a>，其中N是words的總數目，k是最長字串長。

對此當然有異議拉，畢竟這是hash table題，但其實我對hash table實際操作沒有很大的概念。所以在討論區找到了一份寫完整table查詢的code。

建立hash table
```C++ =
struct Node{
    Node* child[26];
    int index;
    vector<int> subPalindrome;
    Node(int ind) {
        index = ind;
        all child = NULL;
    }
}
class Solution{    
private:
    Node* root;
public:
    Build(vector<string> words){
        root = new Node(-1);
        for(int i = 0 ~ words.length() - 1){
            s = reverse words[i]
            Insert(s,i);
        }
    }
    Insert(string s,int i){
        Node* use = root;
        for(char c in s){
            int num = c - 'a';
            if(use->child[num] == NULL){
                use->child[num] = new Node(-1);
            }
            use = use->child;
        }
        use->child.index = i;
    }
}
```
當然跟STL裡面的內容差異我不清楚，可是基本上跟著樹的樣子下去查詢，複雜度只要<a href="https://www.codecogs.com/eqnedit.php?latex=O(k)" target="_blank"><img src="https://latex.codecogs.com/gif.latex?O(k)" title="O(k)" /></a>是可以確定的。看過code後，我也對於hash table比較清楚了，當然之前是知道，但沒看過code長相而已。

而這段code查詢時，是藉由一個一個字元去查詢，然後檢查剩下字元是否為palindrome而決定是否正確。而如果查詢結束還有可以找的字串，則繼續查詢下去到結束，並沿路記錄上來，這樣可以把剩餘字串為palindrome的查詢壓到整段code只需要<a href="https://www.codecogs.com/eqnedit.php?latex=O(Nk)" target="_blank"><img src="https://latex.codecogs.com/gif.latex?O(Nk)" title="O(Nk)" /></a>。

最後稍微分析複雜度吧。

初始設定<a href="https://www.codecogs.com/eqnedit.php?latex=O(Nk)" target="_blank"><img src="https://latex.codecogs.com/gif.latex?O(Nk)" title="O(Nk)" /></a> + 剩餘字串查詢<a href="https://www.codecogs.com/eqnedit.php?latex=O(Nk)" target="_blank"><img src="https://latex.codecogs.com/gif.latex?O(Nk)" title="O(Nk)" /></a>(累計最多) + 全部字串查詢<a href="https://www.codecogs.com/eqnedit.php?latex=O(Nk)" target="_blank"><img src="https://latex.codecogs.com/gif.latex?O(Nk)" title="O(Nk)" /></a> = <a href="https://www.codecogs.com/eqnedit.php?latex=O(Nk)" target="_blank"><img src="https://latex.codecogs.com/gif.latex?O(Nk)" title="O(Nk)" /></a>

當然還有檢查剩餘字串是否為palindrome，不過算上去理應很小被忽略了，最糟應該也只有<a href="https://www.codecogs.com/eqnedit.php?latex=O(Nk^{2})" target="_blank"><img src="https://latex.codecogs.com/gif.latex?O(Nk^{2})" title="O(Nk^{2})" /></a>吧，至於是不是就不清楚了，畢竟沒有詳細計算所以就先當作討論者提及的<a href="https://www.codecogs.com/eqnedit.php?latex=O(Nk)" target="_blank"><img src="https://latex.codecogs.com/gif.latex?O(Nk)" title="O(Nk)" /></a>吧。

## 開始
雖然看了hash table的細節，可是最後我是用STL的map來完成的 ~~(所以說了這麼多你還是偷懶嗎?)~~ ，畢竟一開始研究的時間過長，所以今天先完成他，明天再來嘗試自己寫一次吧。而這部分是看懂後再多找些方法才確定的，也參考了別人的答案。
```C++ =
    vector<vector<int>> palindromePairs(vector<string>& words){
        map<string,int> m;
        for(string in words){
            reverse(words[i]);
            m.push(word[i],i);
        }
        for(i = 0 ~ words.length()-1){
            for(j = 0~words[i].length()){
                left = words[i](0~j-1);
                right = words[i](j~end);
                
                if(left in m && right is palindrome && m[left] != i){
                    result.push({i,m[left]});
                }
                if(right in m && !left.empty() && left is palindrome && m[right] != i){
                    result.push(m[right],i);
                }
            }
        }
        return result
    }
```

### 判斷方式
對於string，有兩種判斷，一種是a接b，另一個是b接a，而要如何判斷誰先誰後才成立呢，就是將字串切半，如果一邊跟map裡面某個是一樣的，只要另一邊字串可以是palindrome就能接起來，左邊找到，就是當前字串接查詢字串，另一種就是查詢字串接當前字串。

### 刪去多餘
舉個簡單例子，0:"abc",1:"cba"，他們本身因為互為反向，所以可以兩邊接，沒寫好條件會出現。

| left | right | result |
| ------ | ----- | ----------------- |
| abc | null | abccba |
| null | abc | cbaabc |
| cba | null | cbaabc |
| null | cba | abccba |

這樣`[0,1],[1,0]`的狀況會出現兩次，所以我們要排除其中一種，就是對於一邊空字串排除一個，而code裡面排除的是left是空的情況就會變成。

| left | right | result |
| ------ | ----- | ----------------- |
| abc | null | abccba |
| null | abc | false |
| cba | null | cbaabc |
| null | cba | false |

這樣剛好能刪去一半多餘的答案。

至於結果因為有參考過，即使吃了飯才開始寫也沒太大問題，而且細節在參考時就被發現了。

## 感想
我最不擅長，或是練習最少的部分，就是關於hash跟字串處理了，這次裡面用到這兩個部分算是了解更多應用跟練習，明天應該也會繼續這類型題目，來讓自己能力更精進吧。
