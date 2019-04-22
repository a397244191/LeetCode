class Solution {
public:
    vector<int> largestDivisibleSubset(vector<int>& nums) {
        if(nums.empty()) return nums;
        sort(nums.begin(),nums.end());
        vector<int> total(nums.size(),1);
        vector<int> record(nums.size(),-1);
        for(int i = 1 ; i < nums.size() ; i++) {
            for(int j = 0 ; j < i ; j++) {
                if(nums[i] % nums[j] == 0) {
                    if(total[i] < total[j] + 1){
                        total[i] = total[j] + 1;
                        record[i] = j;
                    }
                }
            }
        }
        int lastNum = -1,totalNum = 0;
        for(int i = 0 ; i < nums.size() ; i++) {
            if(totalNum < total[i]){
                lastNum = i;
                totalNum = total[i];
            }
        }
        vector<int> ans;
        for(int i = lastNum ; i >= 0 ; ) {
            ans.push_back(nums[i]);
            i = record[i];
        }
        reverse(ans.begin(),ans.end());
        return ans;
    }
};