class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        vector<int> use(nums);
        sort(use.begin(),use.end());
        vector<int>::iterator low;
        vector<int> ans;
        for(int i = 0 ; i < use.size(); i++) {
            int findValue = target - use[i];
            low = lower_bound(use.begin(),use.end(),findValue);
            if(*low == findValue) {
                int first = find(nums.begin(),nums.end(),use[i]) - nums.begin();
                int second = find(nums.begin(),nums.end(),findValue) - nums.begin();
                if(first == second) second = find(nums.begin()+second+1,nums.end(),findValue) - nums.begin();
                ans.push_back(first);
                ans.push_back(second);
                return ans;
            }
        }
    }
};