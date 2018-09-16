# Combine Two Tables And Nth Highest Salary 
今天要來點不一樣的。SQL好久沒碰，翻好久書。

# Combine Two Tables
第一題先簡單點?
## 題目介紹及構思
- input
  - Person(table1)
    - PersonId(int) : primary key
    - FirstName(varchar)
    - LastName(varchar)
  - Address(table2)
    - AddressId(int) : primary key
    - PersonId(int)
    - City(varchar)
    - State(varchar)
- output
  - Result(table)
    - FirstName(varchar)
    - LastName(varchar)
    - City(varchar)
    - State(varchar)

應該沒有很難，就是看看PersonId一樣的把他找出來。

## 開始
一開始就碰壁。原本想說簡單的select,from,where就可以解決，其實不然。

### no table vs null

```SQL
select P.FirstName,P.LastName,A.City,A.State
from Person P, Address A
where P.PersonId = A.PersonId
```

結果發現測資我是沒有任何值，但解答是名字存在但是Address為null。經過一番google跟翻書，發現要用join。

### natural left outer join vs left join on
我在古老的筆記中發現用`Person P natural left outer join Address A`就能保留Person所有的東西。但是加進去後發現。

```SQL
select P.FirstName,P.LastName,A.City,A.State
from Person P natural left outer join Address A
where P.PersonId = A.PersonId
```

一樣是空的table阿?再找了一下，筆記跟書已經沒有更多敘述了。只好去google，找到了一個`left join`，這時候我就想為啥我多了兩個東西。開始去翻找natural跟outer的原因。一開始沒找到我比較了解的敘述，就開始亂刪，刪掉natural後，它就表示我的where語法錯誤。刪掉where答案就對了?

```SQL
select P.FirstName,P.LastName,A.City,A.State
from Person P natural left outer join Address A
```

我只好先丟丟看有沒有更多測資，結果就過了!?

### 原因
最後找到了natural其實會幫我們把相同的column做結合，所以跟join on 不同，需要把敘述放在on上面，而join where會錯的原因就是因為join它的條件是要放在on上而where是給select用的條件，所以語法上出現問題。

## 更多
後來經由參考一些資料，發現兩個相同功能的方式。
```SQL
select P.FirstName,P.LastName,A.City,A.State
from Person P left outer join Address A
on P.PersonId = A.PersonId
```

```SQL
select P.FirstName,P.LastName,A.City,A.State
from Person P left outer join Address A
on Using(PersonId)
```

兩種都是left join用personId來挑選的方法。
