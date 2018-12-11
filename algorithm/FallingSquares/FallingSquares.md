# Falling Squares
休息又玩了一陣子，趕緊回來維持手感。
## 題目介紹及構思
- input
  - positions(vector<pair<int,int>>)
    - pair is a position and the square length.
- process
  - in the order push the squares, find the highest length in the temporary status.
- output
  - vector< int>
    - the list of the highest length after pushing each square.

如果用map紀錄狀態，應該可以做到。

## 開始
想法很簡單，用map<int,int>來儲存，前者是座標，後者是高度。這樣就不用排序我們的座標了。整個值表示，從map->first的做標開始，高度都是map->second。

### 更新map
想法簡單，就是去更新每次使用的地方，然後回傳更新後的高度，再更新目前最高點，將最高點放入答案中。

```C++ =
maxNum = 0;
higharea[0] = 0;
for(int i = 0 ; i < positions.size() ; i++) {
    temp = maxHigh(positions[i].first,positions[i].second);
    maxNum = temp > maxNum ? temp : maxNum;
    ans.push_back(maxNum);
}
return ans;
```

### 找到被影響的區間
這裡需要先找到被影響的區間，然後對這區間所有值做處理。
```C++ =
// start = pos[i].first, high = pos[i].second
finish = start + high - 1;
map<int,int>::iterator startState, endState, maxState;
startState = higharea.lower_bound(start);
endState = higharea.lower_bound(finish);
if(startState == higharea.end() || startState->first > start) startState--;
if(endState != higharea.end() && endState->first <= finish) endState++;
```
用lower_bound去找到頭尾的物件，然後對這兩個物件做處理。startState是最大的小等於start的位置，因為lower_bound是回傳小的大等於物件，所以當值超過是要往前一個物件，而endState是要找到不在範圍中的第一個點，所以如果找到剛好等於finish的點時，要往後一個。

### 區間最高點
因為沒有square摔下來的問題，所以直接對這startState到endState所有的高度找到最大就好。
```C++ =
maxState = startState;
        
int nexthigh = startState->second;
for(map<int,int>::iterator it = startState ; it != endState ; it++) {
    nexthigh = it->second;
    if(it->second > maxState->second) maxState = it;
}
```
一路從startState找到endState，將最高的物件更新到maxState去，然後要紀錄最後一個物件的高度(之後用到)。

### 更新值
我不確定刪掉跟更新會不會影響效率，所以我先用更新的方式做。
```C++ =
higharea[start] = high + maxState->second;
for(map<int,int>::iterator it = startState ; it != endState ; it++) {
    if(it == startState) continue;
    it->second = higharea[start];
}
if(higharea.find(finish + 1) == higharea.end())
    higharea[finish + 1] = nexthigh;
```
首先先將start設定成新高度，然後開始更新start到end的部分，因為startState會是不大於start的，所以不用更新。而finish是最後一個高度為high + maxState->second的位置，所以當finish+1不存在時，新增一個finish+1並將值設定為剛剛紀錄的nexthigh，讓原本沒被遮住的顯示原始高度。

之後回傳higharea[start]，表示這次更新範圍的最高點值。

### WA問題跟複雜度
這部分吃了兩次WA。一個是lower_bound回傳值看錯(我以為跟lower_bound一樣回傳不大於的)，而另一個是endState的位置用成範圍內最後一個值時出了小問題。修改後就AC了。

至於複雜度後來發現，其實不用用lower_bound來做麻煩的查詢，因為這裡中間更新的部分是用linear的方式處理，所以最糟狀況就是每次那段linear都是頭尾，以至於全部是<a href="https://www.codecogs.com/eqnedit.php?latex=O(N^2)" target="_blank"><img src="https://latex.codecogs.com/gif.latex?O(N^2)" title="O(N^2)" /></a>，所以可以直接當做linear全部掃過去就可以了。這樣上面的WA也不會出現了。

## 參考答案
看解答後發現有個Segment Tree的方法。它是將區間做成樹狀的處理方式，不過因為這題測資足夠<a href="https://www.codecogs.com/eqnedit.php?latex=O(N^2)" target="_blank"><img src="https://latex.codecogs.com/gif.latex?O(N^2)" title="O(N^2)" /></a>，所以我也不想深究它 ~~(偷懶)~~ 。不過還是紀錄一些看到覺得不錯的部分。

### 紀錄區間
因為所有點都給了，所以可以先找到所有被分割區間(無論是否被包在一起)，這跟我做的不斷製造區間相反，它是先做好區間分隔後去更新。

### Block (Square Root) Decomposition
這裡將區間再分成<a href="https://www.codecogs.com/eqnedit.php?latex=\sqrt{N}" target="_blank"><img src="https://latex.codecogs.com/gif.latex?\sqrt{N}" title="\sqrt{N}" /></a>個區間，然後先根據最左跟最右給於index(已經分好區間的座標) L跟R，從L到R原本需要R-L次更新，因為用了block切分的關係，只要跑<a href="https://www.codecogs.com/eqnedit.php?latex=\sqrt{N}" target="_blank"><img src="https://latex.codecogs.com/gif.latex?\sqrt{N}" title="\sqrt{N}" /></a>個區間加上L跟R區間的片段就可以了。

而裡面有兩個block高度的值，block跟block_read。這部分看了很久終於明白了，block是最後整段block被統一值的時候，block_read是整段當前最高值。如果要查詢時，片段會去查詢原本紀錄的highest跟block，整段會去查詢block_read，這樣就能找到L到R的最大值，而更新時，只有在整段更新時才更新block，所以不會出現問題。 ~~(雖然弄明白了，可是要說明狀態有點難)~~ 。

### Segment Tree and Lazy Propagation
這部分不是看得很明白，不過看懂前一個範例後似乎明白它如何加速了，它使用tree的架構去做到上面的方式，所以每次更新跟查詢都只要<a href="https://www.codecogs.com/eqnedit.php?latex=log(N)" target="_blank"><img src="https://latex.codecogs.com/gif.latex?log(N)" title="log(N)" /></a>就能做到一樣的事情 ~~(應該啦，有點不明白)~~ 。

## 感想
許久沒動工竟然敢挑戰hard，也是勇氣可佳，總之也算是名白一些新東西了，不虧。