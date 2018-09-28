struct cmpfunc {
  bool operator() (const pair<int,int>& lhs, const pair<int,int>& rhs) const
  {return lhs.first*rhs.second<rhs.first*lhs.second;}
};

class Solution {
public:
    vector<int> kthSmallestPrimeFraction(vector<int>& A, int K) {
        map<pair<int,int>,pair<int,int>,cmpfunc> orderMap;
        
        int len = A.size();
        orderMap[pair<int,int>(A[0],A[len-1])] = pair<int,int>(0,len-1);
        pair<int,int> minNum;
        while(K--){
            minNum = orderMap.begin()->second;
            orderMap.erase(orderMap.begin());
            
            int mol = minNum.first,den = minNum.second;
            if(mol + 1 < len) orderMap[pair<int,int>(A[mol+1],A[den])] = pair<int,int>(mol+1,den);
            if(den - 1 > 0) orderMap[pair<int,int>(A[mol],A[den-1])] = pair<int,int>(mol,den-1);
            
        }
        vector<int> ans{A[minNum.first],A[minNum.second]};
        return ans;
    }
};