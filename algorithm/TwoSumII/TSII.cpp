class Solution {
public:
    vector<int> twoSum(vector<int>& numbers, int target) {

        map<int,pair<int,int>> m;
        for(int i = numbers.size()-1 ; i >= 0 ; i--){
            if(m.find(numbers[i]) == m.end())
                m[numbers[i]] = pair<int,int>(i,-1);
            else if(m[numbers[i]].second == -1)
                m[numbers[i]].second = i;
        }
            
        for(int i = 0 ; i < numbers.size() ; i++)
            if(m.find(target - numbers[i]) != m.end()) {
                if(m[target - numbers[i]].first != i) 
                    return vector<int>{i+1,m[target - numbers[i]].first+1};
                else if(m[target - numbers[i]].second != -1)
                    return vector<int>{i+1,m[target - numbers[i]].second+1};
            }
        return vector<int>{-1,-1};
    }
};