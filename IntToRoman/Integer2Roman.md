# Integer to Roman
昨天在找題目時，看到這個挺有趣的題目。
## 題目介紹及構想
- input
  - num(int)
    - 目標數字
- process
  - 建立字串和數字表格，一一查詢組合。
- output
  - output(string)
    - 一組字串，是num的羅馬拼法

想法沒多複雜，建造查詢陣列，然後直接從大到小查詢結束為止。

## 開始
大致想法如下
``` C++ =
    string intToRoman(int num){
        build string(about MDCLXVI);
        build number arr(1000,900...5,4,1);
        while(num != 0){
            if(num > now use number) add string into output
            else now use number to next
        }
        return output
    }
```
### 建造陣列
看起來很簡單，但要如何製造字串和數字陣列呢?數字陣列我沒多想，就是直接`int arr[13] = {1000,900,500,400,...,5,4,1}`這樣，但字串呢?因為string用不熟，所以我後來找到的一個string token的方式，方法如下
``` C++ =
string useStr("M CM D CD C ... IX V IV I");
istringstream iss(outputstr);
string token;
vector<string> str;
while(getline(iss, token, ' ')) {
    str.push_back(token);
}
```
這樣就建造出一個查詢陣列str裡面有跟arr對應的字串。
### 代換字串
接下來就用while迴圈，一直查詢可填入字串，直到num歸0。
``` C++ =
string output;
int use = 0;
while(num && use < 13) {
    if(num >= arr[use]){
        output += str[use];
        num -= arr[use];
    } else use++;
}
```
這部分也沒有問題，就是從上往下找，如果可以放就放進字串，不行就下一個字串。

## 簡單問題有簡單的處理法
一次就AC了也令我感慨，好險打code似乎沒退步太多?因為這沒有解答，可是去討論看了別人code之後依舊讓我驚訝了。(以下code改成C++格式)
```C++ = 
class Solution {
public:
    string intToRoman(int num) {
        string M[] = {"", "M", "MM", "MMM"};
        string C[] = {"", "C", "CC", "CCC", "CD", "D", "DC", "DCC", "DCCC", "CM"};
        string X[] = {"", "X", "XX", "XXX", "XL", "L", "LX", "LXX", "LXXX", "XC"};
        string I[] = {"", "I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX"};
        return M[num/1000] + C[(num%1000)/100] + X[(num%100)/10] + I[num%10];
    }
};
```
### 簡評
因為這題目組合很少，建表上跟本不用我那看起來有點華麗的寫法，直接土法煉鋼的手打建表，速度上快上許多。仔細看了一下，沒有冗長的運算，沒有複雜的邏輯，直接建好一個表格就能直接用位數值代換進去。看起來也沒有特別複雜或是難看，而最重要的時間因為沒有處理字串部分更是比我快上許多。
### 反思
再回頭想想，是不是每次一個問題一來，我就要將裡面建立的表做出一個邏輯構想呢?有些單調簡單的東西，數量不多的情況下，人來做是不是比指揮電腦完成更好呢?想了一陣子，也明白各有各的優缺點，而且我的建表上，也不是完全沒有手打一串的東西，既然都有手動的過程，是不是簡單到直接建完就好，不用再有手動有電腦作業會比較好呢?至少做完且看完這題後，我有對這部分認知加深點。

## 感想
第二天的coding日常，在簡單的題目和快速的解題後結束了。這次發現自己對建表上的想法跟其他人有所差異是好事，未來上，如果再次有這種，其實很少的建表模式，說不定我能簡單的面對而非想了一大段方式解決。