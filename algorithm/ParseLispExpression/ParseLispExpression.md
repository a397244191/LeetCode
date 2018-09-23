# Parse Lisp Expression
一個解括弧的題目

## 題目介紹及構思
- input
  - expression(string)
    - a well formatted, do let,add, and mult
- process
  - do some operator by key word
- output
  - number(int)
    - the answer of this expression

解括弧大概是重點，剩下都是小處理。

## 開始
一開始覺得很難，可是仔細看完後，因為都有好好的用括弧包起來，應該不會太複雜。

本來打算就直接解字串方式來處理，後來想到可以用子字串不斷遞回的方式。而這樣進來的字串就分兩種:純數字(或變數)及被括弧包住的expression。

### 數字(變數)區域
當然先針對簡單的純數字來處理。所以第一個狀況如下:
```C++ =
if(expression[0] != '('){
    if(table.find(expression)) return table[expression];
    neg = expression[0] == '-';
    begin = neg ? 1 : 0;
    int num = 0;
    for(i = begin ~ expression.length){
        num = num *10 + expression[i] - '0';
    }
    return num * (neg?(-1):1);
}
```
很簡單的把變數直接回傳值，而數字則判斷好正負後找出數字部分，在乘上neg的狀況。

### expression拆分
接下來就針對開頭字元做區分成加法(a)、乘法(m)、設變數(l)。
而其中加乘的內容只差在計算方式，就算在一起。

#### 計算
因為開頭起首一定是"(add "或是"(mult "之後才是我們要的，所以先在前面預設好一些變數，而因為只有兩個參數，所以順便記錄是否起出一個參數的狀況。
```C++ =
begin = substrb = is'a' ? 5 : 6;
value1,value2
valueOk = false;
parestack = 0;
for(i = begin ~ expression.size()){
    if('(') parestack++;
    else if(')') parestack--;
    if(')' && parestack == 0){
        (valueOk?value1:value2) = exp(substring(substrb~i));
        valueOk? break : (substrb = i+2);
        i++;
        valueOk = true;
    }
    else if((' ' || ')') && parestack <= 0){
        (valueOk?value1:value2) = exp(substring(substrb~i-1));
        valueOk? break : (substrb = i+1);
        valueOk = true;
    }
    return is'a'? value1 + value2 : value1 * value2;
}
```
這部分因為有()和純數字的狀況，所以分成兩種判斷(內容其實做一樣的事情)。
就是利用變數parestack去儲存括弧狀態，當為0就是目前括弧是被配對情況，所以這段是完整的，就把()中包的所有東西當成子字串做遞回去處理。而另一種狀況是純數字(變數)時，因為沒有)做結尾，只好用空格或原本最外圈(包著add或mult)的')'做判斷，而取出的字串就是前一個，而因為只要valueOk是true就表示現在取出的字串是第二個變數離開迴圈(避免最後"))"多餘的字串處理)。

最後再用頭字元是'a'與否來判斷做加法或是乘法。

#### 賦值動作
這裡比較複雜，因為會一直做取變數、取值並配對的動作，所以不知道什麼時候停止，因此需要的變數會有些不同。
```C++ = 
isName = true;
Name = "";
substrbegin = 5;
parestack = 0;
for(i = begin ~ expression.size()){
    if('(') parestack++;
    else if(')') parestack--;
    if(')' && parestack == 0){
        isName?Name = substring(substrb~i): table[Name] = exp(substring(substrb~i));
        isName ^= true;
        i++;
    }
    else if((' ' || ')') && parestack <= 0){
        isName?Name = substring(substrb~i): table[Name] = exp(substring(substrb~i));
        isName ^= true;
    }
    return exp(Name);
}
```
這邊就輪流做取Name跟更改table的動作，而利用它需要最後是expression的關係，所以總共會有奇數的狀態，因此可以得知最後一個Name其實是expression而去計算回傳它。

### bug
還是有些很蠢的bug，但也有一些思慮不周的。

#### mult是4個字母
我一開始以為是mul，然後打得很開心測試也很容易，結果發現測資是mult時傻眼了。稍微多個變數紀錄開頭就解決了。

#### table竟然不是同一個
出現了一個測資表示"(let x 2 (add (let x 3 (let x 4 x)) x))"，這裡因為()內外是不同table裡面，所以當賦值出了()就會失效，而我只有用一個map儲存導致最後的x都是同一個變成"4+4"的狀態，但其實外面的x應該是2，答案是"2+4"。因為範例出現的外變數放前面導致我認知上出問題。

這部分也很簡單但很暴力的解決它，就是直接傳值到下一層解決。

終於AC後，也感受到題目不難，只是複雜了點。

## 參考答案
特別注意到的就是map方式跟字串解讀。

### map方式
直接丟進stack裡面，然後一樣用公變數交給其他function做事情。而變數儲存上，利用stack當遇到'('時放入，清空狀態，而繼續做字串的token，在遇到')'時解決計算，著時是個超好的方法。

### 字串處理
這部分做法跟我一樣，不過它比較有概念的把找子字串的部分做出function，所以整個function看起來非常乾淨有架構。

# 感想
對於解決方式上認知增加，而對於架構要經過思考這件事情也有很直接的體悟。