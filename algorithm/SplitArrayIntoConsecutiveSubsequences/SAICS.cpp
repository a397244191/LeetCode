class Solution {
public:
    bool isPossible(vector<int>& nums) {
        vector<int> count{0,0,0};
        int last = -1;
        for(int i = 0 ; i < nums.size() ; i) {
            int now = nums[i];
            if(last != -1 && last + 1 != now ){
                if(count[0] != 0 || count[1] != 0 ) return false;
                count[2] = 0;
            }
            last = now;
            vector<int> next{0,0,0};
            int use = 0;
            while(nums[i] == now){
                use++;
                i++;
            } 
            if(count[0] + count[1] > use) return false;
            use -= count[0];
            next[1] = count[0];
            use -= count[1];
            next[2] = count[1];
            if(use >= count[2]) {
                use-= count[2];
                next[2] += count[2];
                next[0] = use;
            } else next[2] += use;
            count = next;
        }
        if(count[0] != 0 || count[1] != 0 ) return false;
        return true;
        
    }
};