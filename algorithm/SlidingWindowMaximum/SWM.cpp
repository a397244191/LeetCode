class cmp
{
public:
  bool operator() (const pair<int,int>& lhs, const pair<int,int>& rhs) const
  {
    return lhs.first > rhs.first;
  }
};

class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        priority_queue<pair<int,int>> pq;
        int len = nums.size();
        for(int i = 0 ; i < k ; i++) 
            if(i < len)
                pq.push(pair<int,int>(nums[i],i));
        vector<int> ans;
        for(int i = 0 ; i < len - k + 1 ; i++) {
            if(pq.empty()) break;
            while(pq.top().second < i) pq.pop();
            ans.push_back(pq.top().first);
            if(k + i < len)
                pq.push(pair<int,int>(nums[k + i],k + i));
        }
        return ans;
    }
};