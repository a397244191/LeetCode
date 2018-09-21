class Solution {
public:
    vector<int> maxNumber(vector<int>& nums1, vector<int>& nums2, int k) {
        vector<int> m_best={};
        vector<int> n_best={};
        int s = 0;
        int m = nums1.size();
        
        m_best = findMaxOrderFirst(nums1,k);
        n_best = findMaxOrderFirst(nums2,k);
        //check the max size
        m = m_best.size();
        int n = n_best.size();
        
        if(n_best[0] == -1) return m_best;
        else if(m_best[0] == -1) return n_best;
        
        vector<int> ans;
        for(int i = 0 ; i < k ; i ++) ans.push_back(-1);
        for(int i = m ; i >= k-n ; i-- ) {
            vector<int> use1,use2;
            if(i > 0)
                use1 = findMaxOrderFirst(m_best,i);
            if(k-i > 0)
                use2 = findMaxOrderFirst(n_best,k-i);
            
            int a = 0,b = 0;
            bool cover = false;
            bool cont = true;
            
            for(int j = 0 ; j < k ; j ++) {
                int maxNum = -1;
                if(b == use2.size() || ( a != use1.size() && use2[b] < use1[a])){
                    maxNum = use1[a];
                    a++;
                }
                else if(a == use1.size() || ( b != use2.size() && use2[b] > use1[a])){
                    maxNum = use2[b];
                    b++;
                }
                else {
                    int x = 0;
                    for(x ; x < m-a || x < n-b ; x++){
                        if(b+x == use2.size() || ( a+x != use1.size() && use2[b+x] < use1[a+x])){
                            maxNum = use1[a];
                            a++;
                            break;
                        }
                        else if(a+x == use1.size() || ( b+x != use2.size() && use2[b+x] > use1[a+x])){
                            maxNum = use2[b];
                            b++;
                            break;
                        }
                    }
                    if(maxNum == -1){
                        maxNum = use2[b];
                        b++;
                    }
                }
                
                if(ans[j] < maxNum) {
                    cover = true;
                }
                else if(!cover && ans[j] > maxNum) break;
                
                if(cover) {
                    ans[j] = maxNum;
                }
            }
        }
        return ans;
        
        
    }
    
    vector<int> findMaxOrderFirst(vector<int>& num, int k) {
        vector<int> use={-1};
        if(k == 0 || num.size() == 0) return use;
        else use.pop_back();
        int s = 0;
        int l = num.size();
        for(int i = 0  ;i < k ; i++) {
            int maxNum = num[s];
            int pos = s;
            for(int j = s + 1 ; j < l && l - j >= k - i ; j++){

                if(maxNum < num[j]) {
                    maxNum = num[j];
                    pos = j;
                }
            }
            use.push_back(maxNum);
            s = pos + 1;
            if(s == l) break;
        }
        return use;
    }
    
    
};