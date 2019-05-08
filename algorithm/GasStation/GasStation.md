# Gas Station
照邏輯走，應該是簡單的greedy。
## 題目介紹及構思
- input
  - gas(vector< int>)
    - you can get gas[i] in station i.
  - cost(vector< int>)
    - you need cost[i] from station i to station i+1
- process
  - there are N gas stations along a circular route
- output
  - int
    - the number of start station, if you can travel around the circuit once in the clockwise direction
  - -1
    - you can't

題目只有簡單的數字變化，應該可以線性時間解決。

## 開始
最簡單的做法就是從每個當作起點，看能不能走一圈。不過應該有更簡單的想法。

### 能走一步算一步
最後想出來的想法是，我就從任意點開始(基本上就是0開始)，假設他自己加的油可以往下走，就往下走，如果走不下去表示這不是起點，就將往回推找新起點。而回推時，因為後面都走過且確認至少可以走到當前終點，所以不用擔心半路走不到的狀況。而最後起點跟終點重合時，就找到起點了。

``` C++ =
i = b;
do{
    t += gas[i] - cost[i];
    if(t < 0) {// b is not start station
        b--;// if b < 0 to last station
        i = b;
    }
    else{// you can go start b to end l
        l++;// if l > size to first station
        i = l;
    }
}while(b != l);
return t >= 0 ? b : -1;
```

這次粗心的沒判到l的上界，所以吃了一個RE外，就AC了。

## 參考答案
其他方法雖然作法上不一樣，但細看後都是用推起點跟終點的方式。
## 感想
一開始還以為要沿路確認能否走到，但其實並不用，因為能走到的地方，換個起點還是能走到(前提是起點能走到這路的頭)。