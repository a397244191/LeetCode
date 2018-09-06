# Binary Tree Inorder Traversal
為了繼續做臨時起意的小project，先打個Medium題，順便練習tree的瀏覽。

## 題目介紹及構想
- input
  - root(TreeNode*)
    - the root of tree
- process
  - inorder
- output
  - ans(vector< int>)
    - inorder value of this tree
    
上次recover binary tree時用過的方法，所以已經沒有很難了。

## 開始
跟上次一樣，不用recursive來解，所以stack要記錄兩個值。
```
    vector<int> inorderTraversal(TreeNode* root) {
        stack<pair<TreeNode*,bool>> s;
        s.push(root,false);
        while(!s.empty()) {
            use = s.top();
            s.pop();
            if(use is null pointer) continue;
            if(left no visit){
                s.push(right,false));
                s.push(use,true));
                s.push(left,false));
            }else ans.push_back(val);
            
        }
        return ans;
    }
```

一次AC，看來對這方法我也熟悉了。

### 參考code
因為是基本方法，而且該看到神祕的方式也在之前看過了，這次就沒有參考code

## 感想
每日一code達成，繼續去小project吧。