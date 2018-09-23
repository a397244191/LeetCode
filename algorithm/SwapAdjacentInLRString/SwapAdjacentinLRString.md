# Swap Adjacent in LR String
今天看到都沒想法，還是選簡單點的題目吧。

## 題目介紹及構思
- input
  - start(string)
    - only char 'R','L',or'X'
  - end(string)
    - only char 'R','L',or'X'
- process
  - L only go left, R only go right, and RL can not swap.
- output
  - bool
    - return we can transform from start to end by swap "RX" or "XL".

因為沒有動腦的想法，這題不複雜就來建構式解決 ~~(一一排除法，沒有參考依據，自己在說)~~ 吧。

## 開始
總之對於這個，因為只能往一個方向移動並且兩字串長度保證一樣，所以大致需要排除三種狀態：數量不同、位置無法抵達、LR交錯。

1. 所以先從數量開始下手，起首先去紀錄L跟R的位置。用了四個vector來存取，分別是start的L,start的R,end的L,end的R。
```C++ = 
vector<int> sL,sR,eL,eR;
for(i = 0~start.length()){
    if(s[i] == L) sL.push_back(i);
    if(s[i] == R) sR.push_back(i);
    if(e[i] == L) eL.push_back(i);
    if(e[i] == R) eR.push_back(i);
}
if(sL!=eL || sR!=eR) // size neq
    return false;
```
2. 因為R衡向右L衡向左，而順序不會變動，所以只要比對同個索引下的pos值，就能確定我的R或L能否移動到定點。
為了方便看到結構，我把兩個放在同一個迴圈處理。
```C++ =
for(int i = 0 ~max(sL.size(),sR.size())){
    if(i < sL.size() && sL[i] < eL[i]) return false;
    if(i < sR.size() && sR[i] > eR[i]) return false;
}
```
3. 當L跟R移動有交錯時，就無法抵達，因為沒有RL做交換的動作。
因為只要有R或L一個清空，另一個就會因為方向相同而不會交錯產生，也因為前面排除數量跟自身無法抵達的問題，所以也不用擔心其他狀況。因此只要有一個用完就結束，不需要兩者都跑完確認。
```C++ = 
Rpos = Lpos = 0;
while(Rpos < sR.size() && Lpos < sL.size()){
    if(sL[Lpos] < sR[Rpos])Lpos++;
    else if(eR[Rpos] < eL[Lpos]) Rpos++;
    else return false;
}
return true;
```

這樣就能逐步式的把所有狀態解決，也因此沒有出現問題，直接AC。

## 參考答案
我的解法比較接近muti-pass，但我看到一個用許多減單想法建構出的one-pass解法
```C++ =
l = 0 ,r = 0;
for(i = 0~start.size()){
    if(start == L) l++
    else if(R) r--;
    if(end == R) r++;
    else if(L) l--;
    if(l&&i) return false;
    if(l < 0 || r < 0) return false;
}
if(l||r) return false;
return true;
```
這是用簡單的邏輯想法構建而成，應該算是這題最精簡的想法了。因為是往右掃過整個字串，L一定會先出現在start，而R會先出現在end，所以只要l or r是 比0小的表示無法到達的狀況。而如果兩個都有值，表示到某個位置情況，該位置左邊有起點的L跟終點的R但還沒看到任何起點的R或終點L，表示必定會發生交錯。而最後，如果l跟r有一個不是0，就表示數量是不同多的。

簡單的紀錄跟三個判別式就能解決這個問題，我只能說寫法美妙到，我看過就理解並記起來了。

# 感想
昨天打完AC開始記錄時就臨時有事，只好今天在把它完成，現在有點不知道完成日子要記錄到昨天還是今天。
