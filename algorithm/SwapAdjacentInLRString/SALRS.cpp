class Solution {
public:
    bool canTransform(string start, string end) {
        vector<int> sRlist,sLlist,eRlist,eLlist;
        for(int i = 0 ; i < start.length() ; i++ ){
            if(start[i] == 'L') sLlist.push_back(i);
            else if(start[i] == 'R')sRlist.push_back(i);
            if(end[i] == 'L')eLlist.push_back(i);
            else if(end[i] == 'R')eRlist.push_back(i);
        }
        if(!(sLlist.size() == eLlist.size() && sRlist.size() == eRlist.size())) return false;
        
        for(int i = 0 ; i < sLlist.size() || i < sRlist.size() ; i++ ){
            if(i < sLlist.size() && sLlist[i] < eLlist[i]) return false;
            if(i < sRlist.size() && sRlist[i] > eRlist[i]) return false;
        }
        
        int Rpos = 0, Lpos = 0 ;
        
        while(Rpos < sRlist.size() && Lpos < sLlist.size()) {
            if(sRlist[Rpos] > sLlist[Lpos]) Lpos++;
            else if(eRlist[Rpos] < eLlist[Lpos]) Rpos++;
            else return false;
        }
        return true;
    }
};