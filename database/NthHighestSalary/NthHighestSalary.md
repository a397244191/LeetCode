
# Nth Highest Salary 
SQL太久沒用了，總之多練習一點

## 題目介紹及構思
- input
  - Employee(table1)
    - id(int)
    - Salary(int)
- output
  - getNthHighestSalary(N) (table)
    - Salary(int)
      - the Nth high Salary in Employee

有點難度了，我知道最大跟最小的方法，但第N個呢?

## 開始
想了一下排序很簡單用order by解決，但是要找到第N個位置怎麼找?後來看到一個給順序值的方式
```SQL
set @t1 = 0
select @t1 := @t1+1 ...
```

所以產生下列方法。

``` SQL
CREATE FUNCTION getNthHighestSalary(N INT) RETURNS INT
BEGIN
  set @t1 = 0;
  RETURN (
      # Write your MySQL query statement below.
      select S.Sa 
      from(
        select @t1 := @t1+1 as ID, E.Salary as Sa
        from Employee as E
        order by Sa ASC
      ) as S
      where S.ID = 1
      
  );
END
```

其實這個set我一直找不到要放哪，後來靈機一動才想到放在begin end 中間。

### 重複了
我第一次上去後，有一個測字錯了，就是裡面只有兩個100卻要找第二位，答案要是找不到，但我卻找到了第二個100。

這次開始我對query開始有點熟悉了，並且也回憶了當時的一些知識。所以很快的想到了group by的用法。

```SQL
CREATE FUNCTION getNthHighestSalary(N INT) RETURNS INT
BEGIN
  set @t1 = 0;
  RETURN (
      # Write your MySQL query statement below.
      select S.Salary 
      from(
        select @t1 := @t1+1 as ID, G.Salary
        from (
            select E.Salary
            from Employee as E
            group by E.Salary
        ) as G
        order by G.Salary ASC
      ) as S
      where S.ID = N
      
  );
END
```

這次我又對裡面多做了一層，把重複的挑掉。~~(後來發現多此一舉，用distinct就可以了)~~

### ASC和DESC
先生明前面是為了重複自己的蠢事，不是沒發現。

這次信心滿滿的丟了上去卻得到的WA，我才發現第N大的我竟然是用遞增排序。有點被自己逗樂了。以下是最終版。

```SQL
CREATE FUNCTION getNthHighestSalary(N INT) RETURNS INT
BEGIN
  set @t1 = 0;
  RETURN (
      # Write your MySQL query statement below.
      select S.Salary 
      from(
        select @t1 := @t1+1 as ID, G.Salary
        from (
            select E.Salary
            from Employee as E
            group by E.Salary
        ) as G
        order by G.Salary DESC
      ) as S
      where S.ID = N
      
  );
END
```

## 參考答案
我之後又試了一些方法，像是直接把group by 跟order by 放在一起，可是order by卻沒有反應了，這先不提。

### offset,limit
這讓我看見了一個超級簡單的寫法
```SQL
CREATE FUNCTION getNthHighestSalary(N INT) RETURNS INT
BEGIN
  SET N=N-1;
  RETURN (
      SELECT DISTINCT Salary FROM Employee ORDER BY Salary DESC LIMIT 1 OFFSET N
  );
END
```

一行就做到我想做的事情，用distinct來區隔多個重複，用offset來移動N個位置，用limit來限制table大小只有一行。只能說query的設計需要多練習跟多學習才會知道問題的簡單程度。

# 感想
今天第一次來嘗試不同於寫code的部分，畢竟一直看code讓自己沉浸習慣中也不好，需要多看看不同的東西。