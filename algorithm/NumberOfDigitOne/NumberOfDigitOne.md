# Number of Digit One
又過了一陣子，這題挺有趣的
## 題目介紹及構思
- input
  - n(int)
- process
  - count all digit is 1 from all number less than and equal n.
- output
  - ans(int)
    - the number of the count

tag上只有math，純數學，本來還想到用表binary search看來不用。

## 開始
想法不難，首先我開始考慮每個位數的1會有多少。

### 計數
所以所有1位數只會有'1'有出現1，所以有1個。而2位數開始，會有'01','10','11',...,'91'總共有20個。而也逐漸找到規律，就是i位數有`i*pow(10,i-1)`個1。既然如此，我就開始對數字做一些位數處理。
```C++ =
len = 0;
t = n;
mod = 1;
dig;
while(t) {
    dig.push_back(t%10);
    t /= 10;
    len++;
}
for(i = 1 ~ len)mod*=10;
reverse(dig);
int ten = 1;
for(int i = 1 ; i <= 9 ;i++) {
    countDig.push_back(i*ten);
    ten *= 10;
}
```
這裡做了兩件事，分解n跟去建立i位數有多少1的表。然後分解n的位數反轉，令最大位數為頭，並先做一個mod值為了待會用於於數。

### 處理數字
`countDig[i]`是i位數1的個數，`dig[i]`是n的從頭開始的位數值。
首先要對於數字想法就是對於從頭開始的第i個，會有`dig[i]*countDig[len-i-2]`個1在小於len-i-1位數的位置。然後再根據`dig[i]`，去判斷這位數會有`mod`或是`n%mod+1`個1出現。依此累計。

```C++ =
ans = 0;
for(i = 0 ~ dig.size()) {
    ans += countDig[len-2-i] * dig[i];
    if(dig[i] > 1) {
        ans += mod;
    } else if(dig[i] == 1) {
        ans+= n%mod + 1;
        }
    mod /= 10;
}
return ans;
```
迴圈一開始是計算所有小於len-1-i位數的1在它小於`dig[i]`有幾個，而接下來是判斷該位數的1有多少，如果`dig[i]`大於1就表示所有1都被數進去而有mod個，如果等於1，出現1的次數就是n%mod+1個。最後讓mod跟dig的位數一起下降。

### overflow
很有趣的WA結果，因為一開始mod沒有另外算，導致算出超過int的狀況，而這值竟然還跟我的測資一模一樣，感受到滿滿惡意與嘲諷的測資。測資值 : 1410065408。

不過在解決WA問題後就AC了。

## 參考答案
看了別人的想法，才發現原來有更簡單的方式。雖然方法一樣，但我把它搞複雜了。它是從最小位數開始，去計算每個位數出現1的次數，所已不會像我一樣有剩下的。結果只用一個迴圈跟一行解決了我複雜方法才出來的問題。

```C++ =
int countDigitOne(int n)
{
    int countr = 0;
    for (long long i = 1; i <= n; i *= 10) {
        long long divider = i * 10;
        countr += (n / divider) * i + min(max(n % divider - i + 1, 0LL), i);
    }
    return countr;
}
```
前半是去計算我此位數出現1的次數，後半一樣是去算剩餘1的次數。

## 感想
數學題目都解法都不難，又都會出現神秘的精簡解法。每次都令我甘拜下風。

