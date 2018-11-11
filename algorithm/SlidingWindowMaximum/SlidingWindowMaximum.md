# Sliding Window Maximum
我明明選題方式自認很隨機，可是似乎還是挺偏門的?
## 題目介紹及構思
- input
  - nums(vector< int>)
    - a list of some number
  - k(int)
    - the number of group member
- process
  - find the max from every continue k number in numbers 
- output
  - vector< int>
    - a list of every max number

想到一個之前merge k list一樣的方法。

## 開始
k個值比大小什麼的，在沒有特別方法時 ~~(可是這題後來發現有)~~ 就是丟在heap裡面處理是比較好的，所以就將k個值先丟進priority_queue裡面，並包含著它的index，每次都取top(最大值)出來，當top的index低於目前找的範圍時就pop出去來維持top是範圍中最大值。

```C++ =
// push k number into pq
for(i = 0 ~ len - k + 1) {
    if(pq.empty()) break;
    while(pq.top().second < i) pq.pop();
    ans.push_back(pq.top().first);
    if(k + i < len)
        pq.push((nums[k + i],k + i));
}
```
這裡第一行是為了確保input空的狀況 ~~(因為被坑了)~~ 。

除了被測資坑了RE外，改好就能AC了。

## 參考答案
只能說，我沒有設想周到，原來這題可以很greedy的方式解決。

### deque
一個頭尾都能取丟的queue，我看到這方式後才驚覺我還太天真了。因為在k個值進去後，在最大值之前的值根本沒有用，而只要進來的值足夠大，也可以直接將在第一大後面的值丟掉。所以產生了這種要對頭尾都做事的queue。

```C++ =
for(i = 0 ~ len) 
{
    // pop less than nums[i] and index less than i
    while(!dq.empty() && dq.back().second < nums[i])
        dq.pop_back();
    // push nums[i]
    dq.push_back(make_pair(i, nums[i]));
    // pop outside the range(i-k ~ i)
    if(dq.front().first <= i-k){
        dq.pop_front();
    }
    // push max(i-k ~ i)
    if(i - k+1 >= 0){
        ans.push_back(dq.front().second);
    }
}
```
這分四步驟
1. 先對所有自己前頭比自己小的都丟掉，因為`num[i]`在range中了，所以之後都會用這個值，其他小的用不到。
2. 丟進`num[i]`就是將值丟進range陣列中。
3. 丟掉index低於range的頭，畢竟已經不在範圍中了。
4. 在range足夠大後開始丟入max值進去答案。

這複雜度在評估後是<a href="https://www.codecogs.com/eqnedit.php?latex=O(N)" target="_blank"><img src="https://latex.codecogs.com/gif.latex?O(N)" title="O(N)" /></a>(全部只會丟進去一次丟出來一次)，比用資料結構估出來的<a href="https://www.codecogs.com/eqnedit.php?latex=O(Nlog(N))" target="_blank"><img src="https://latex.codecogs.com/gif.latex?O(Nlog(N))" title="O(Nlog(N))" /></a>好多了。也許對解決這題沒有差別，但就是認為能想出來真好。

## 感想
某意義上，可能是太閒了，在沒有比賽後才如此愉悅的打一些題目的東西。雖然難度可能因為自我侷限被限制在一個難度下，不過看看一些解題方法跟神秘跳躍思考的技巧，不免都覺得十分有趣。
