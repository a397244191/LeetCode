class Solution {
public:
    bool validSquare(vector<int>& p1, vector<int>& p2, vector<int>& p3, vector<int>& p4) {
        
        int len1 = (p2[0] - p1[0])*(p2[0] - p1[0]) + (p2[1] - p1[1])*(p2[1] - p1[1]);
        int len2 = (p3[0] - p1[0])*(p3[0] - p1[0]) + (p3[1] - p1[1])*(p3[1] - p1[1]);
        int len3 = (p4[0] - p1[0])*(p4[0] - p1[0]) + (p4[1] - p1[1])*(p4[1] - p1[1]);
        if(len1 == 0 ) return false;
        if(len1+len3 == len2) swap(p3,p4);
        else if(len3+len2 == len1) swap(p2,p4);
        else if(len1+len2 == len3);
        else return false;
        len1 = (p2[0] - p1[0])*(p2[0] - p1[0]) + (p2[1] - p1[1])*(p2[1] - p1[1]);
        len2 = (p3[0] - p1[0])*(p3[0] - p1[0]) + (p3[1] - p1[1])*(p3[1] - p1[1]);
        if(len1 != len2) return false;
        if(p2[0] + p3[0] - p1[0] == p4[0] && p2[1] + p3[1] - p1[1] == p4[1]) return true;
        else return false;
    }
};