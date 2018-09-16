# Kth Largest Element in a Stream
明明很清楚，可以細節錯誤總是一直出現。題目歸類:heap

## 題目介紹及構想
- input
  - k(int)
    - 要找的第K大的k
  - nums(vector< int>)
    - 最初的數字
  - val(int)
    - 每次新增一個val在這數字列
- process
  - init(k,nums)
    - 建立一個儲存
  - add(int val)
    - 將val加入陣列並找出第k大的
- output
  - result(int)
    - 每次add後回傳第k大的值

想法是建立一個small heap，只要長度維持k，頂端就永遠是第k大的。

## 開始
想法簡單，我就開始建立heap之旅。
```C++ =
class KthLargest {
public:
    vector<int> smallHeap;
    int size;
    int kNum;
    KthLargest(int k, vector<int> nums) {
        size = 0;
        kNum = k;
        loop:{
            add(nums[i]);
        }
    }
    
    int add(int val) {
        if(size is enough and val < small) return small;
        push(val);
        bubbleUp(val position);
        if(size > K) Pop();
        return small;
    }
    
    void bubbleUp(int now){keep the now element is right position}
    
    void Pop() {pop the small element}
};

```

### RE
還沒丟之前就一直跑不過code?看了半天是size沒有初始化啊!改完成功後，嘗試丟一次，又是RE?原來是一開始根本沒有陣列值，在add的地方還給它`return small[0]`的問題。

### WA第一彈
丟上去了，才發現自己add裡面是寫長度不為0而已，但其實要長度不到K也包含，所以改了一下又可以了。

### WA第二彈
這次測資有很多重復的值，我才發現當左右邊數值一樣時，我就不做事了!?多加了一個=後終於AC了。

### 修改
後來發現，我的code一開始是全放進去再pop到需要的位置，這樣子我認為有狀況，就嘗試看看複雜度，當N足夠大時，pop的複雜度會是<a href="https://www.codecogs.com/eqnedit.php?latex=O(logN)" target="_blank"><img src="https://latex.codecogs.com/gif.latex?O(logN)" title="O(logN)" /></a>，但如果我維持heap為k時，pop複雜度會是<a href="https://www.codecogs.com/eqnedit.php?latex=O(logk)" target="_blank"><img src="https://latex.codecogs.com/gif.latex?O(logk)" title="O(logk)" /></a>，當然N很小時沒有差別，但N很大時，整題時間會是<a href="https://www.codecogs.com/eqnedit.php?latex=(N-k)logN" target="_blank"><img src="https://latex.codecogs.com/gif.latex?(N-k)logN" title="(N-k)logN" /></a>跟<a href="https://www.codecogs.com/eqnedit.php?latex=Nlogk" target="_blank"><img src="https://latex.codecogs.com/gif.latex?Nlogk" title="Nlogk" /></a>，所以把它從`loop:push all;loop:pop N-k`改成`loop:add(nums[i])`的方式，而實際證明，除了logN其實很小外，測資N也沒有大到可以誇張的地步，所以反而後者因為call function上變的比前者慢個誤差值的範圍。

### 參考code
後來參考後，大多數程式都是利用內建函式Priority Queue的方式來完成，當然這應該是目前最好的解法，畢竟compiler和撰寫者都把它優化到很好的地步，不過這次是為了讓我多練習一些資料結構的認知，所以還是自己撰寫的一段heap的函式。

## 感想
題目是寫easy，這似乎是很糟的狀態，畢竟紅字出現了那麼多次。這也讓我知道我對一些資料結構 ~~(當然還有一些粗心的細節啦)~~ 的認知並沒辦法支持我一次就建立起來，雖然之後大多數時間也不會需要自己建立資料結構。不過如果未來能練習到，借用這些經驗和認知來快速的建立起一個資料結構，對我的能力也會有很大的保證。