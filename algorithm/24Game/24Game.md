# 24 Game
窮舉，題目不難，但要好好寫很難。
## 題目介紹及構思
- input
  - nums(vector< int>)
    - four number
- process
  - you can add +-*/() and change the order of four number
- output
  - bool
    - if those can calculate to 24, return true

總之就是窮舉數字的排列組合，然後窮舉個順序的運算元。

## 開始
因為沒有要列出算，所以()只是表示可以任意順序不用參考。

### 排列組合
用DFS方式，在結束遞迴的時候將visit再次設為false。就能讓所有狀況都走一便，並紀錄下來即可。
```C++ =
void DFS(now,nums,visit,use) {
        if(use.size() == 4) {
            allPair.push_back(use);
            return ;
        }
        if(now != -1 && visit[now]) return;
        if(now != -1){
            visit[now] = true;
            use.push_back(nums[now]);
        }
        for(i = 0 ~ 4) {
            if(i != now) {
                DFS(i,nums,visit,use);
            }
        }
        if(now != -1){
            visit[now] = false;
            use.pop_back();
        }
    }
```

這裡利用now = -1 來代替每個點起點這個迴圈。並在遞迴結束清空設置。

### 運算元迴圈
對所有排列方式做一次所有運算。

```C++ = 
bool judgePoint24(vector<int>& nums) {
    //set 
    DFS();
    for(num : allPair){
        calculate(num);
    }
}
bool calculate(num)
{
    char useOp[4] = {'+','-','*','/'};
    for(int i = 0 ; i < 4 ;i++) {
        for(int j = 0 ; j < 4 ; j++){
            for(int k = 0 ; k < 4 ; k++){
                op{useOp[i],useOp[j],useOp[k]};
                visit{false,false,false};
                if(check(-1,num,op,visit,0,0))
                    return true;
            }
        }
    }
        
    return false;
}

```
將數字組合丟進去後，直接用三層迴圈直接得到所有+-*/的組合。

### 計算可能結果
因為順序可以隨意(利用括弧)，所以用DFS方式，將這三個運算任意順序計算一次。

```C++ =
bool check(now, num, op,visit,order,ans){
    //1
    if(order > 3 && abs(ans-24) < 0.00001) return true;
    else if(order > 3) return false;
    if(now != -1 && visit[now]) return false;
    before = num;
    if(now != -1){
        //2
        visit[now] = true;
        num[now] = TwoPair(num[now],num[now+1],op[now]);
        num[now+1] = num[now];
        //3
        if(now == 0 && visit[1]) num[2] = num[0];
        else if(now == 2 && visit[1]) num[1] = num[3];
        ans = num[now];
    }
    //4
    for(int i = 0 ; i < 3 ; i++) {
        if(i != now) {
            if(check(i,num,op,visit,order+1,ans)) 
                return true;
        }
    }
    //5 
    num = before;
    if(now != -1) visit[now] = false;
    return false;
    }
```

1. 當用完三個運算後，查看是否為24，反之或其他狀況回傳false
2. 紀錄當前狀況，並計算該次運算(TwoPoint)
3. 因為是將紀錄的4個數字直接替換成結果，所以遇到先算中間後，會出現做左邊運算後結果無法給最右邊計算。所以多做兩個判斷。
4. 繼續遞迴運算
5. 回復狀態，因為沒有結束所以是false

### WA
因為一些小問題沒設置好，吃了WA。修改後AC。

## 參考答案
果然hard難度，就是會出現一些簡單的方法解決我要繞一大圈的題目。

### 交換到尾端
看到一個有趣的解法是，將所有數字都丟到尾端一次，然後計算尾端兩值的四種結果。再去遞迴下去。
```C++ =
bool func(nums) {
    int n = nums.size();
    //1
    if (n == 1) return nums[0] < 24.000001 && nums[0] > 23.999999;
    //2
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < i; ++j) {
            auto nc = nums;
            //3
            swap(nc[i], nc[n - 1]);
            swap(nc[j], nc[n - 2]);
            auto rs = getResults(nc[n - 1], nc[n - 2]);
            nc.pop_back();
            //4
            for (auto r: rs) {
                nc.back() = r;
                if (can24(nc)) return true;
            }
        }
    //5
    return false;

}
```

1. 算完後，判段是否為24
2. 兩層迴圈得到任一兩不同數
3. 將兩數丟到尾端，並計算得到6個運算結果(/跟-會有兩種)
4. 將結果丟入原本的尾端，然後遞迴下去
5. 所有狀況結束，false

這一個簡單的雙層迴圈架構就能解決我要窮舉兩次的方法。

## 感想
感覺今天思考不利。有點混亂，不過還是解決了。