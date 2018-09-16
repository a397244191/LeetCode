bool cmp (vector<int> a,vector<int> b) { return (a[1]==b[1]) ? a[0] > b[0] : a[1] < b[1] ; }

class Solution {
public:
    int intersectionSizeTwo(vector<vector<int>>& intervals) {
        int number = 0;
        sort(intervals.begin(),intervals.end(),cmp);
        vector<int> unInside;
        
        for(int i = 0 ; i < intervals.size() ; i++) unInside.push_back(2);
        
        for(int i = 0 ; i < intervals.size() ; i++) {
            int beginV = intervals[i][0];
            int endV = intervals[i][1];
            int needPush = unInside[i];
            for(int pos = endV ; pos > endV - needPush ; pos--) {
                for(int j = i ; j < intervals.size() ; j++) {
                    if(unInside[j] > 0 && intervals[j][0] <= pos) {
                        unInside[j]--;
                    }
                }
                number++;
            }
        }
        
        return number;
    }
};