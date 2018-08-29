# Reverse Integer
腦袋昏昏沉沉怎麼打都錯。

## 題目介紹及構想
- input
  - x(int)
    - 要被反轉的數
- process
  - 將x反轉成result
- output
  - result(int)
    - 被反轉的數，overflow為0

這應該沒很難，就除來除去乘來乘去結束?

## 開始
總之將大致想法如下
``` C++ =
    int Reverse(int x) {
        int result;
        abs(x);
        flag = x < 0;
        while(x){
            result = result * 10 + x % 10;
            x /= 10;
            if(overflow check);
        }
        if(overflow) return 0;
        else return result;
    }
```

## 設想不週
本來今天什麼都不想做啦，可是還是來試試看一題簡單的好了，讓自己感覺有進度?結果是噩夢開始~~(笑)~~。

### overflow?
本來overflow判斷是`result < 0`表是轉過去了，結果很棒的，它給的測資剛好又轉回來正數。只好改成在`result = result *10 + ...`之前判 `result > 214748364`讓它被* 10之前知道會爆炸。

### 整數範圍知多少
int的範圍是。恩很棒，我做了什麼?我把$-2^{31}$轉正了，然後爆炸。因為今天累了，直接例外處理，結束QQ。

## 參考答案
我看了看想了想，才想到x%10不用管正負號吧?所以看到了解答乾淨的樣子，而且還不用擔心轉正爆炸。看了感慨一下。
順便去看了別人的code(執行後速度更快的)，他直接用double來儲存，這樣就不會爆炸了，而且判斷更簡單，只能簡單到自嘆不如。

## 感想
這次是只為了進度而做的進度。累了不打code之於酒後不開車，一樣見紅，只是你撞出WA，人家撞出傷。
