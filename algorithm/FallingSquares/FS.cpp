class Solution {
public:
    vector<int> fallingSquares(vector<pair<int, int>>& positions) {        
        vector<int> ans;
        int maxNum = 0;
        higharea.insert(pair<int,int>(1,0));
        for(int i = 0 ; i < positions.size() ; i++) {
           int temp = maxHigh(positions[i].first,positions[i].second);
            maxNum = temp > maxNum ? temp : maxNum;
            ans.push_back(maxNum);
        }
        return ans;
    }
    int maxHigh(int start, int high) {
        int finish = start + high - 1;
        map<int,int>::iterator startState, endState, maxState;
        startState = higharea.lower_bound(start);
        endState = higharea.lower_bound(finish);
        if(startState == higharea.end() || startState->first > start) startState--;
        if(endState != higharea.end() && endState->first <= finish) endState++; 
        maxState = startState;
        map<int,int>::iterator it;
        
        int nexthigh = startState->second;
        for(map<int,int>::iterator it = startState ; it != endState ; it++) {
            nexthigh = it->second;
            if(it->second > maxState->second) maxState = it;
        }
        higharea[start] = high + maxState->second;
        for(map<int,int>::iterator it = startState ; it != endState ; it++) {
            if(it == startState) continue;
            it->second = higharea[start];
        }
        if(higharea.find(finish + 1) == higharea.end())
            higharea[finish + 1] = nexthigh;
        return higharea[start];
    }
    map<int,int> higharea;
};