# Create Maximum Number
努力活化腦細胞中。好難。

## 題目介紹及構思
- input
  - nums1(vector< int>)
  - nums2(vector< int>)
  - k(int)
- process
  - form nums1 and nums2, merge to the max number (length = k),k <= m+n(first and second number list length)
- output
  - ans(vector< int>)
   - length = k, the max number list.

想法簡單，對兩個陣列可放置的數字優先處理直到結束。理應是這樣。

## 開始
先說說第一次想法好了。因為需要滿足長度k這條件，所以不能無條件往下找，必須保證找到這數字之後能滿足k個。所以產生以下想法。

```C++
    b1=0,b2=0
    m = nums1.size,n = nums2.size
    mL = m,nL=n
    while(k--){
        n1 = {-1,-1,-1}
        n2 = {-1,-1,-1}
        for(i = b1 ; i < m && ((m-i-1) >= (k-nL))
            if(n1[0]<nums1[i]) 
                n1[0] = nums1[i] n1[1] = n1[0],n1[2]=i;
        for(i = b2 ; i < n && ((n-i-1) >= (k-mL))
            if(n2[0]<nums2[i]) 
                n2[0] = nums2[i] n2[1] = n2[0],n2[2]=i;
                
        // compare n1 n2
        n1 > n2 b1 move to n1[2] push n1[0]
        n1 < n2 b2 move to n2[2] push n2[0]
        if(equal)
        n1[1] < n1[2] do n1 > n2
        else do n1 < n2
    }
```

我以為就這樣，當兩者相同，如果前面次大的跟比較小，就先被拿走。結果。

### 後面更重要
想法結束發現一個測資是`[6,7]`,`[6,0,4]`然後k = 5。因為我只比前面，所以後面就不管它，結果因為6都是頭而取錯了。

這時候我認為不能重蹈覆轍，決定直接換想法，因為後面比較還沒有想法。

### 重新想法
我第一個想到的是DP跟全配對，就是取出nums1的最長(m at most k)序列best1跟nums2的最長(n at most k)序列best2，並用best1建立一個<a href="https://www.codecogs.com/eqnedit.php?latex=k^2" target="_blank"><img src="https://latex.codecogs.com/gif.latex?k^2" title="k^2" /></a>的表格list查詢nums1在長度x(x<m<=k)的最佳解。

然後用best2逐漸拔掉一個最小值的方法去查詢對應的`list[x]`可以merge成長度k的解，直到無組合可查。

流程大概如下

```C++
    best1 = find(nums1,k);//mk
    best2 = find(nums2,k);//nk
    
    list build // max(m,k)^2
    
    ans = list length k ,and all -1
    for(best2 decrease){//max(n,k)
        merge list[i] and best2, and compare ans and now//k
    }
    
```

這裡設想兩種狀況，m,n < k 及 k < m,n。

- m,n < k
  - m組合下可以產生<a href="https://www.codecogs.com/eqnedit.php?latex=O(m^2)" target="_blank"><img src="https://latex.codecogs.com/gif.latex?O(m^2)" title="O(m^2)" /></a>陣列，然後時間複雜大概是<a href="https://www.codecogs.com/eqnedit.php?latex=O(max(m,n)k)" target="_blank"><img src="https://latex.codecogs.com/gif.latex?O(max(m,n)k)" title="O(max(m,n)k)" /></a>
- k < m,n
  - 組合下可以產生<a href="https://www.codecogs.com/eqnedit.php?latex=O(k^2)" target="_blank"><img src="https://latex.codecogs.com/gif.latex?O(k^2)" title="O(k^2)" /></a>陣列，然後時間複雜大概是<a href="https://www.codecogs.com/eqnedit.php?latex=O(k^2)" target="_blank"><img src="https://latex.codecogs.com/gif.latex?O(k^2)" title="O(k^2)" /></a>

結果在測試階段就被MLE擊倒。

### 不列表想法
前半部一樣將兩者長度設定於min(nums1.size,k)跟min(nums2.size,k)，後半決定不列表改用直接作，就是取出前面為長度i後面為長度k-i的方式做。

現在設定m = min(nums1.size,k)跟n = min(nums2.size,k)方便後續解說。

```C++ = 
for( i = m ; i >= k-n ; i--){//decrease best1
    use1 = find(best1,i);//mi
    use2 = find(best2,k-i);//n(k-i)
    merge use1 and use2, and compare ans
}
return ans
```

就是把建表的部分內建化，當m+n跟k接近時還好，當best1跟best2都長k時，i = k/2有做差<a href="https://www.codecogs.com/eqnedit.php?latex=O(k^2)" target="_blank"><img src="https://latex.codecogs.com/gif.latex?O(k^2)" title="O(k^2)" /></a>時間，總合算來會是<a href="https://www.codecogs.com/eqnedit.php?latex=O(k^3)" target="_blank"><img src="https://latex.codecogs.com/gif.latex?O(k^3)" title="O(k^3)" /></a>

### bug產生
一開始在做merge時，因為長度總合就是k，所以不用擔心前面問題，只要管後面，我一開始用當時失敗測資時，只想到要比一個，所以出現了一種`[6,1,2,7]`,`[6,1,2,8]`, k = 8出錯了。

所以把merge改用迴圈檢查後方。

### 空陣列
出現一個`[]`,`[1,2]`,k=2的測資，因為防止回傳空出現error，所以我find裡面空的匯回傳-1，導致答案錯了，增加一些判斷修正後解決。

### merge判斷迴圈
判斷兩者後方一樣的迴圈出來條件寫錯，寫成and，但應該要用or來做才對，修改後AC。

### 回到最初想法
我後來在merge時，做了判斷後方的方法後，跑去試試看了舊想法印證。

結果跑出一個測資把我炸得滿頭灰。

狀況是這樣的，它兩個陣列藏有很多9，總數大約15個，但是第二個陣列中9後面的值超小，導致一值output第一個陣列，結果因為第一個陣列過短，無法先output出第二陣列的9，導致9的長度不夠。

所以得正這不是完全greedy的題目，要先做一些方法才能解決。

## 參考答案
因為參考答案看完覺得都還好 ~~(不易理解)~~ ，所以沒有想法 ~~(其實有點看的霧颯颯就先不管了)~~。

# 感想
因為難得好幾天才做一題hard，似乎腦袋還沒清醒弄得有點看不懂別人想法。