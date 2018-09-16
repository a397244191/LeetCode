# Design Circular Queue
data struct設計。
## 題目介紹及構想
- input
  - function(vector< string>)
    - call function name
  - value(vector< string>)
    - the input for call function
- process
  - 設計一個circular queue不用內建STL，其中包含enqueue,dequeue,Front,Rare,isEmpty,isFull
    - 維持Queue size為k。
- output
  - success(bool)
    - in enqueue and dequeue, return the action is success or not.
  - value(int)
    - in Front and Rare, return the front value or rare value. 

其實這在學習資料結構上是基本的想法。就是在一個陣列上用兩個參數表示頭尾。

## 開始
設計變數f跟r表示頭尾關係，後來發現full跟empty關係有點不明確而增設變數判斷是否滿的。
```C++ = 
class MyCircularQueue {
public:
    int f,r,size;
    bool full;
    int* arr;
    /** Initialize your data structure here. Set the size of the queue to be k. */
    MyCircularQueue(int k) {
        init arr in size k
        size = k;
        f = r = 0;
        full is false
    }
    
    /** Insert an element into the circular queue. Return true if the operation is successful. */
    bool enQueue(int value) {
        if(isFull()) return false;
        arr[r] = value;
        r = next pos, is the tail in arr goto the 0.
        full = (r == f);//check the full when we push a value
        return true;
    }
    
    /** Delete an element from the circular queue. Return true if the operation is successful. */
    bool deQueue() {
        if(isEmpty()) return false;
        f = next pos, is the tail in arr goto the 0.
        full = false;// full must be false, beacuse we pop one value
        return true;
    }
    
    /** Get the front item from the queue. */
    int Front() {
        return a[f], if not empty
    }
    
    /** Get the last item from the queue. */
    int Rear() {
        return a[r-1], if not empty
    }
    
    /** Checks whether the circular queue is empty or not. */
    bool isEmpty() {
        if full return false, else return f == r
    }
    
    /** Checks whether the circular queue is full or not. */
    bool isFull() {
        return full;
    }
};
```

設計上沒有什麼問題，也注意到要初始化。和r是指最後一個value的下一個。所以一次AC。

## 參考答案
這題我覺得很基本型態的資料結構設計，而也沒有解答。

可是參考到了幾個有趣的想法。

- Empty歸0
  - 它在dequeue時做了一件事，發現空了就把f跟r歸0減少複雜的想法。
- mod
  - 很有趣的一直讓f跟r加1，而要查詢時是f%size來解決，這是我覺得超級有趣的點。 
    - 也因為測試資料次數不會超過1000筆，所以他這樣做沒問題

## 感想
因為沒有太難的想法，這次算是輕鬆向的題目。