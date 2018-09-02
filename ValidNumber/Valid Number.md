# Valid Number
hard題再開，這次是基本邏輯題，應該比資料結構應用簡單。
## 題目介紹及構想
- input
  - s(string)
    - 字串疑似數字
- process
  - 確認字串狀況
- output
  - output(bool)
    - 回傳true當字串是數字。其他則false

想法簡單，就是將字串一直跑到尾檢查所有狀況。

## 開始
做了才發現要處理很多，總之開了幾個bool參數，去判斷一些狀況，像是whilespace,dot,exp等等。

### WA dot problem
因為小數點連續錯了三次。第一次沒有判".3"為true，第二次改進後變成"3."不是true，結果好笑的來了"."我判成了true。之後為了處理狀況，決定重新設計，one-pass的寫法把全部混在一起不好改。

## 改變後
這次決定分成三步驟來處理，雖然還是全部掃一次而已，可是切成三個迴圈可以明確分工。
```C++ = 
    bool isNumber(string s) {
        loop(1) delete white space in head;
        //main string check
        loop(2){
            if(whitespace) break //go next step
            if(check sign)
            else if(check num)
            else if(check dot){
                if(only dot and there isn't any number after this dot) return false;
            }
            else if(check exp 'e')
            else return false;//otherwise false sample
            i++;//next char
        }
        loop(3){
            //go to the end of string
            //and check other char is whitespace or not
            //if not whitespace, return false;
        }
        return isNum;// true,main string stop at the correct result 
    }
```

### 第一次loop
我們將多餘的開頭空格去除，整段沒有任何問題。

### 第二次迴圈
基本上借用一些bool來去判斷當前狀況跟檢查，檢查的有'.','e','+','-'這些特殊字符是否出現在能出現的地方。

#### 小數點陰魂不散
繼上次"."被坑後，我特地開了一個onlyDot的變數，當只有小數點出現時，且後方沒有數字出現時，回傳false。結果測試半天，一樣沒測試到只有"."的狀況，多加了一個`i == len - 1`才解決。

#### exp也出問題
我以為狀況都解決了，沒想到出現測資是"e23"的狀況，原來當初在設計時，只檢查出"23e"不是數字，沒有想到'e'在前的狀況，多加了一個判斷說e能否出現的變數後解決。

## 所有正確範例統整
他題目有先說開始前要確保所有狀況，可是對於".3"和"3."是後來想到的，所以造成了一些bug。這裡來統整所有會出現的正確範例吧。
1. "+123456"
2. "-123.456"
3. "123."
4. ".456"
5. "+123e+456"
6. "123.e-456"

特殊錯誤範例
1. "123+456"
  正負號一定只能在數字開頭
2. "-e333"
  exp前面一定要有數字
3. "34e2.1"
  exp後面一定是整數
4. "123 014"
  整串只有一個數字
5. "."
  小數點可只有頭或尾有數字，但不能單獨出現
6. "222e"
  exp後一定要有數字

## 參考答案
沒有參考答案，可是看到一個驚人的code
```C++ =
#include <string>
#include <regex>

class Solution {
private:
    static std::regex const number_pattern;
public:
    bool isNumber(std::string const& s) {
        return std::regex_match(s, number_pattern);
    }
};

// non-(const integral) static member variables must be initialized out-of-line.
std::regex const Solution::number_pattern{R"(^\s*[-+]?(?:\d+|\d+\.\d*|\d*\.\d+)(?:e[+-]?\d+)?\s*$)"};
```
說實在，我也蠻佩服用這方法的人。我之前學過compiler也看過這類型的東西，將這兩者聯結我覺得很厲害。

其實也沒什麼好分析的，就是用內建完成，主要該分析的只有那個number_pattern寫什麼。我來稍微解析看看好了。

先排除掉開頭結尾的東西
- R
  - 指字串會是one row的意思
- (^$)
  - 就是開始跟結束的標記
然後需要認知一些重要用法
- \s
  - 就是空格的意思 
- [string]
  - 就是這個是在string裡面其中一個
- (something)
  - ()包含著一個subpattern，有點像加減法的()判斷先後，這是一個區塊
- \d
  - 數字 
- ?
  - 可有可無，有就出現一次，也可以不出現
- ?:
  - 不會backtrack，backtrack會被需要是指要回頭檢察，可是這只要掃過去所以不用。
- \+
  - [XXX]+ 表示XXX會出現1到N次，N可以無限多
- \*
  - ? 和 +的整合，[XXX]*表示出現0到N次
- |
  - 跟or一樣，就是 a | b表示出現會是 a或b，但不會交替出現。

依序判斷後面東西。
1. \s*

  可以接受一堆空格開頭，沒有也行。
  
2. [-+]?

  出現+或-，且只有一次或沒出現。
  
3. \d+ | \d+\.\d* | \d*\.\d+

  判斷為123或123.或.123這三種，至於123.456被包含在後兩者。
  
4. (e[+-]?\d+)?

  可有可無的exp，但出現一定會是e+123的樣子。
  
5. \s*

  總之接受後面一堆空格。

因為compiler所以稍微學過寫這些正規表示式，所以看到後有點好奇的認真拆開來看看。
## 感想
這次也是hard，可是因為是邏輯題的關係，我比較擅長解決，沒有遇到太大的困難，最多就是對於"123."和".123"在出現WA前不確定 ~~(其實是不想承認)~~ 是數字。而也看到了C++有另一個神奇的函式可以分析正規表示式 ~~(我直到今天要寫心得才知道中文名稱，之前都只知道是regex)~~ 。
