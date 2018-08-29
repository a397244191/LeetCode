# Search in Rotated Sorted Array
被轉動了還是要來binary search一下。

## 題目介紹及構想

- input
  - nums(vector< int>)
    - 數字陣列，以排序好，但被旋轉了不知道幾格
  - target(int)
    - 要尋找的數字
- process
  - 在<a href="https://www.codecogs.com/eqnedit.php?latex=O(logN)" target="_blank"><img src="https://latex.codecogs.com/gif.latex?O(logN)" title="O(logN)" /></a>時間裡找到target在nums的位置
- output
  - output(int)
    - target在nums的位置，不存在為-1

<a href="https://www.codecogs.com/eqnedit.php?latex=O(logN)" target="_blank"><img src="https://latex.codecogs.com/gif.latex?O(logN)" title="O(logN)" /></a>是對排序好的陣列可以做到最快的搜尋方法，但這被轉過的陣列呢?總之做法應該也像binary search一樣吧。

## 開始

大致想法考慮頭尾相接點D的位置跟中間mid的位置關係分成三種:正常、D < mid、D > mid，所以code流程如下
``` C++ =
    while(left != right){
        mid = (left + right) / 2
        if(mid == target) return mid
        else if(left == mid) return -1
        else if(normal array(no rotated)) binary search
        else if(left < mid/*=> D > mid*/) {
            if(target < left < mid) left = mid// right < target < D
            else if(target > mid > left) left = mid// mid < target < D
            else if(mid > target > left) right = mid, array is normal
        } else if(left > mid/*=> D < mid*/) {
            if(target < left < mid) right = mid// D < target < mid
            else if(target > mid > left) right = mid// left < target < D
            else if(mid < target < left) left = mid, array is normal
        
        }
    }
```

大致上，一直搜索向正確的範圍找尋，就能找到最後數字。

## bug湧出

看起來一切安好，應該沒問題了，丟上去

### TLE

超出時間?因為這做法就是<a href="https://www.codecogs.com/eqnedit.php?latex=O(logN)" target="_blank"><img src="https://latex.codecogs.com/gif.latex?O(logN)" title="O(logN)" /></a>，所以狀況只有沒結束這點上。找了問題，啊!一定是我沒判left = right - 1這時候，因為這樣mid 會一直是left。新增條件後，還是TLE?!

#### 只是沒有完成

再仔細看了code，丟到其他測資看看，發現卡的數字怪怪的，這才發現，啊!我根本沒寫完code，normal裡的是空的!!

### RE

這就有點坑人了，因為它input的vector是[ ]的，所以right一開始就會是-1然後炸開，加個條件就解決了。

## 看完討論感想

看完人家code後才知道，我一樣寫太多了，其實只要target不被left和 mid夾起來，就直接當else就好，因為操作一樣。而normal array的情況，其實可以等同left < mid的情況來處理就好，雖然這樣，至少我確定了流程是一樣的，只差在是否精簡。

### 壞習慣

其實真的binary search裡，將left,right = mid + 1, mid - 1的方式可以排除很多例外，可是因為很少寫binary search所以沒有做-1,+1的動作，導致很多力外處理我要考慮，像是target = left,target = right, right - left = 1的狀況。

## 感想
題目不難而有趣，簡單的binary search一變化起來也是個好玩的題目。
