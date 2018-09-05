class Solution {
public:
    vector<int> getRow(int rowIndex) {
        vector<int> first{1},second{1,1};
        vector<int> *use = &first,*last = &second;
        if(rowIndex == 0) return first;
        for(int i = 1 ; i < rowIndex ; i++ ) {
            for(int i = 1 ; i < last->size(); i ++){
                if(i < use->size()) (*use)[i] = (*last)[i] + (*last)[i-1];
                else use->push_back((*last)[i] + (*last)[i-1]);
            }
            use->push_back(1);
            swap(use,last);
        }
        return *last;
        
    }
};