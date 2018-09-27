# Contain Virus
bug感覺跟題目的virus一樣，擋了一組，另一組又長起來了。
## 題目介紹及構思
- input
  - grid(vector<vector< int>>)
    - the map show the infected cell and other cell.
- process
  - calculate how many wall do we need to build.
- output
  - wall(int)
    - the number of walls we build

題目設計成greedy的樣子，因為他不要求最少牆數或是最大存活，只要求要建多少牆，並且建造原因是因為當前可能感染最多。題目也表示不會出現最多感染數有兩組的情況。

## 開始
基本上就是一直搜尋所有被感染處，分別是:計算各感染群可能感染總數、阻擋最大感染群建牆數、未被阻擋cell開始感染，依次循環。

### 開始前設定
首先設定，我想把感染群的起點固定在一個數目內(不用再整張圖搜尋感染點)，所以DFS的狀況會有4種，除上述三種外加最初查詢總數狀況(單純瀏覽的DFS)。

#### DFS狀態
分成0:單純瀏覽、1:計算總數、2:計算牆數、跟3:感染細胞，至於細節後面再來看

#### 公用變數
為了方便作DFS所以把是否被拜訪跟移動方向是否有牆拉出來當class變數。
##### 拜訪
visit是一個二維bool陣列，來記錄是否被拜訪過，當然每次DFS前都需初始化。
##### 移動
因為想了半天不知道牆要怎麼儲存，最後決定用一個三維陣列`row*col*4`的方式紀錄4個方向的牆是否存在。

#### 病毒群
為了簡單記錄病毒群，用了一個pair的陣列去儲存每個病毒群起始點(同一區塊記錄一個)的座標。

### 主要流成
主要架構大致如下:
```C++ =
record virus group = n
loop(at most n)
{
    loop(all virus group)
        count the cell that will be infected.
    after loop, get maxp
    if(maxp is not existed) break
    wall += build walls for defending the max virus group
    infect the other cell that not defence
    merge virus group
}
return wall
```
主要是並沒有利用while跳出，而是是否存在多於一的感染數。而while是保證最多會跑的次數(病毒群數)。

#### 記錄病毒群
這部分很簡單，整個圖瀏覽當遇到沒有拜訪且事被感染的點時記錄下來，並DFS下去對每個作拜訪紀錄。
```C++ =
for(i,j = 0~row,0~col)
    if(!visit || [i][j] == 1){
        virus.push_back(pair(i,j));
        DFS(i,j,0);
    }
```
#### 計算病毒群感染
對所有記錄的病毒群分別作DFS(每次拜訪清空)，找出最大感染病毒群。
```C++ =
maxN = 0,maxpos = -1;
for(i = 0~n){   
    initvisit
    pos = virus[i];
    infect = DFS(pos.first,pos.second,1);
    if(more than maxN){
        maxN = infect;
        maxpos = i;
    }   
}
if(maxp == -1) break;
```
在這部分，當沒有多於一個感染時，maxpos就會是0而結束。

#### 建牆
這部分都是交給DFS做，主函式只有做增加建牆數的動作。
```C++ = 
pos = maxpos;
wall += DFS(pos.first,pos.second,2);
```

#### 感染下去
除了第一個(其實包含也沒差，因為有牆)外都跑DFS去感染周遭。
```C++ =
for(i = 0 ~ n){
    pos = virus[i];
    DFS(pos.first,pos.second,3)
}
```

#### 合併病毒群
因為擴張後有可能跟其他群合併，為了減少病毒群數，所以對每個做DFS，而這次都共用一個visit，當被拜訪過的狀況，就視為跟其他群相連合併了。
```C++ = 
virus.erase(maxPos);
InitVisit(row,col);
for(i = 0 ~ n, i not add 1) {
    pos = virus[i];
    if(visit){
        virus.erase(i);
    }else{
        DFS(pos.first,pos.second,0);
        i++;
    }
}       
```
這裡特別的有兩個，第一個是去刪除我們包圍的病毒群(因為必定已不需要)，第二是不讓for做i++動作，而是根據狀況+1，這樣可以不會因為刪除一個點而跳過狀況發生。

到這裡主要流程就完成了。

### DFS
0:單純瀏覽，1:記錄可能感染數，2:建牆+記錄數目，3:開始感染
這部分不複雜大致就是兩個，判斷是否拜訪或是其他狀況，跟去拜訪(嘗試感染)四周。
```C++ =
int DFS(r,c,type)
{
    row = grid.size(),col = grid[0].size();
    if(Over(r,c)) return 0;
    dr[4] = { 1, 0,-1, 0};
    dc[4] = { 0, 1, 0,-1};
    if(visit[r][c]) return 0;
    visit[r][c] = true;
    if(type <= 1 && grid[r][c] == 0) return 1;

        
    count = 0;
    for(i = 0 ~ 4){
        if(!wallExist[r][c][i]){
            switch(type){
                case 0:
                case 1:
                    count += DFS(r+dr[i],c+dc[i],type);
                    break;
                default:
                    if(!Over(r+dr[i],c+dc[i]) && grid[r+dr[i]][c+dc[i]] == 0){
                        if(type == 2){
                            wallExist[r][c][i] = true;
                            wallExist[r+dr[i]][c+dc[i]][(i+2)%4] = true;
                            count++;
                        }else{
                            grid[r+dr[i]][c+dc[i]] = 1;
                            visit[r+dr[i]][c+dc[i]] = true;
                        }
                    }
                    else count += DFS(r+dr[i],c+dc[i],type);
                    break;
            }
        }
    }
    return count;
}
```

#### 不訪問原因
首先去判斷我的位置是否在範圍內，其次是看是否拜訪過，最後根據狀況對於遇到沒有感染者的情況結束遞回。

#### switch
我本來以為用switch會有很棒的架構感，但似乎還好。

##### 單純瀏覽跟計算可感染數
這兩部分其實是一樣的，只是對於計算上有回傳值需要的有無而已。
##### 建牆跟感染
這部分對於一般狀況不變，當遇到下一個是0的情況，因為建牆有雙向問題，所以需要在上層處理，而為了防止遞回0的狀況，當感染時需要順便替下層做拜訪記錄。

### 遇到的bug
基本上除了一些忘了把debug的output拔掉的狀況，大致有兩個問題。

#### 感染比實際多?
因為一開始DFS是寫成有拜訪或無感染回傳，但發現這樣會忘了紀錄拜訪而導致重複計算，在判斷是否拜訪跟是否感染的中間插入紀錄拜訪的動作後解決。

#### 繞路而行的病毒
因為對於被我們感染的cell因為沒有繼續遞回而無拜訪紀錄，導致繞過別處走到同個點時，被當作本來就有的部分而出現問題。而後增加紀錄就解決問題了。

### 未submit發現問題
在submit前吃了很多error，所以其實完成的背後充滿著問題。

#### 無限loop
這部分因為思慮不周，以為不需要紀錄拜訪就可以完成DFS(認為有足夠中止條件)，最後卻發現其實都要，所以不斷看到程式爆炸。

#### 以為是邊界的非邊界
因為我在DFS時異想天開的認為，我在找病毒群時，會順便把遇到邊界的方向紀錄牆的存在，而導致後面遇到邊界的狀況全都因為超出陣列大小而爆炸。最後修改成需要判斷就判斷的方式解決。

#### 為了刪除捨棄正確數字
這部分並不是跟程式流程直接錯誤有關(也沒有一個現成測資證明錯誤)，就是在於，我認為紀錄我可以感染幾個點的地方，我認為可以順便紀錄要被刪除的點(因為只要連在一起就會被拜訪過而不跑)，但後來發現計算上出現了少許誤差，才發現每次計算其實需要把整個拜訪區域清除才行。

最後我選擇在感染後做一次不清除拜訪紀錄的DFS來刪除所有重疊的病毒群。

## 參考答案
沒有發現特別需要研究的部分，頂多就是看下來我似乎做太多時間複雜的要求了，其實並沒有優化到而已。不過因為不是令我驚訝的部分，就不深入探討了 ~~(其實想偷懶了)~~

## 感想
果然DFS這種東西，沒做久了總是會遺漏細節。不過這次AC狀況我還挺滿意，並沒有出現我最開始就方向錯誤的問題，大多出現在一些細節流程沒有理清楚的原因。