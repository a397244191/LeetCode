# Find First and Last Position of Element in Sorted Array
終於結束人生一個階段了，開始復健。
## 題目介紹及構思
- input
  - nums(vector< int>)
    - a array in ascending order
  - target(int)
    - the value we need to find
- process
  - find the first and last position of target in nums
- output
  - vector< int>
    - a array of the number of first position and the number of last position
    - if not found, return [-1,-1]

題目說用<a href="https://www.codecogs.com/eqnedit.php?latex=O(log(N))" target="_blank"><img src="https://latex.codecogs.com/gif.latex?O(log(N))" title="O(log(N))" /></a>，所以也很直觀的用binary search。

## 開始
題目如果用STL，就直接用lower_bound跟upper_bound來解決。不過畢竟是復健，總是要動點腦跟動點手，所以還是手刻binary search吧。

### Binary Search
常見到不行得算法，而且這次又沒有任何變化，所以非常簡單到適合復健。
```C++ =
int BS(vector<int> num, int target)
{
    while(head <= tail) {
        mid = (head + tail) / 2;
        if(mid < target ) head = mid + 1;
        else if(mid >= target) tail = mid - 1;
    }
    if(tail is target) return tail;
    else if(head is target) return head;
    else return -1;
}
```

不斷依據mid 改變head跟tail直到找到(或找不到)target。

而上述方式可以找到我們這次題目要找的first position。

### last position
其實很簡單，就是讓相等時往後找即可，原本寫的只能往前找，因為只差一點，所以想修改上一個方法來達到效果。

```C++ = 
int BS(vector<int> num, int target, bool findFist)
{
    while(head <= tail) {
        mid = (head + tail) / 2;
        if(num[mid] < target || (!findFirst && num[mid] == target)) head = mid + 1;
        else if(num[mid] >= target) tail = mid - 1;
    }
    if(num[tail] is target) return tail;
    else if(num[head] is target) return head;
    else return -1;
}
```

新增了一個判斷，讓如果要找last position時，可以在第一次判斷時擋下相等的狀態。

### 統整
設計好方法後，只要呼叫兩次找到頭跟尾就結束了，不過多了個判斷令第一次就沒找到時可以不找第二次。

```C++ =
vector<int> searchRange(vector<int>& nums, int target) {
    int first = -1,last = -1;
    first = BS(nums,target,true);
    if(first >= 0) last = BS(nums,target,false);
    return vector<int>{first,last};
}
```

最後，畢竟是復健，預想了一些狀況又觀察了幾分鐘，一次就吃AC了。

## 參考答案
因為是基本的題型，所以也沒有太多差異。

### 直接推位置
看到有個有趣的方式，就是直接再找到的時候，將first跟last一個往前一個往後線性找，看來worst case沒有很多。

### 更好的binary
其實應該也就差一些邏輯判法改變能加快速度吧，不過復健就不多研究了(其實真的也沒差)。

## 感想
當兵期間，除了裡面沒有電腦，出來也只是想抒發一些情緒跟壓力，沒啥碰電腦，可以說是十分的怠惰。姑且寫的很小心，也測試很小心。剛好挑到的題目也沒有陷阱，是很直接的算法題。之後繼續開始練習的日子，就好好努力吧。
