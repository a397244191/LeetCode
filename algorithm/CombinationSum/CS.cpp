class Solution {
public:
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        cand = candidates;
        vector<int> use;
        combination(target,0,use);
        return ans;
    }
    void combination(int target,int now,vector<int>& use) {
        if(target == 0){
            ans.push_back(use);
            return ;
        }
        else if(target < 0 || now >= cand.size()) return ;
        int c = 0;
        for(int i = 0 ; cand[now]*i <= target ; i++) {
            c++;
            if(i > 0) use.push_back(cand[now]);
            combination(target - cand[now] * i, now+1,use);
        }
        for(int i = 0 ; i < c-1 ; i++) {
            use.pop_back();
        }
    }
private:
    vector<int> cand;
    vector<vector<int>> ans;
};