class Solution {
public:
    Solution(int N, vector<int> blacklist) {
        sort(blacklist.begin(),blacklist.end());
        int p = -1;
        for(int i = 0 ; i < blacklist.size() ; i++) {
            if(blacklist[i] != p + 1) whitelist.push_back(pair<int,int>(p+1,blacklist[i]-1));
            p = blacklist[i];
        }
        if(p < N - 1) whitelist.push_back(pair<int,int>(p+1,N-1));
        rangeAcc.push_back(whitelist[0].second - whitelist[0].first + 1);//get range first range
        for(int i = 1 ; i < whitelist.size() ; i++){
            rangeAcc.push_back(whitelist[i].second - whitelist[i].first + 1+rangeAcc.back());
        }
        
        MOD = rangeAcc.back();
        
        srand(time(NULL));
    }
    
    int pick() {
        int r = (rand()%MOD) + 1;
        // find in which range r is.
        int index = lower_bound(rangeAcc.begin(),rangeAcc.end(),r) - rangeAcc.begin();
        // get number
        int number = whitelist[index].first + (index == 0 ? r : (r - rangeAcc[index - 1])) - 1;
        
        return number;
    }
private:
    int MOD;
    vector<pair<int,int>> whitelist;
    vector<int> rangeAcc;
};

/**
 * Your Solution object will be instantiated and called as such:
 * Solution obj = new Solution(N, blacklist);
 * int param_1 = obj.pick();
 */