class Solution {
public:
    bool xorGame(vector<int>& nums) {
        int xorNum = 0;
        int nonZeroCount = 0;
        bool AliceBegin = true;
        for(int i = 0  ;i < nums.size() ; i++){
            nonZeroCount ++;
            xorNum ^= nums[i];
            if(xorNum == 0) {
                AliceBegin ^= (nonZeroCount%2 != 0);
                nonZeroCount = 0;
            }
        }
        if(xorNum == 0) 
            return true;
        else 
            return (AliceBegin ^ (nonZeroCount%2 != 0));
    }
};