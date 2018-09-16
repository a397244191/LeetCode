# Pascal's Triangle II
偶爾像偷懶一樣寫個簡單的東西。

## 題目介紹及構想
- input
  - rowIndex(int)
    - a number in `[0,33]`
- process
  - in k space find the answer
- output
  - result(vector)
    - the rowIndex row in pascal's triangle

簡單想法，兩個陣列交替使用，創造新的後再互換角色一直到結束，節省交替的時間空間。

## 開始
運用指標互換方式更換角色，減少程式碼的量或陣列互換的時間。
``` C++ =
    vector<int> getRow(int rowIndex) {
        vector<int> first{1},second{1,1};
        vector<int> *use = &first,*last = &second;
        if(rowIndex == 0) return first;//return {1}
        for(int i = 1~rowIndex - 1) {
            for(int i = 1~size of last){
                val = last[i] + last[i-1]
                if(i < the size of use) use[i] = val;
                else use.push_back(val);
            }
            use.push_back(1);// final value
            swap(use,last);
        }
        return *last;
    }
```

沒有很大問題，並且在確認k=33也沒有overflow後一次AC

### 參考code
參考後別人有兩種方式，第一種空間比我還省，只用一個陣列跟一個紀錄值就解決，而另一個則是用類似公式的方式在一層迴圈解決。我覺得都比我想得更省更好用，我也由衷佩服。

## 感想
因為今天想做點事情，雖然按照進度打了一題，但是挑了一個簡單題目來做。