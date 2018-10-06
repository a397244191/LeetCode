class Solution {
public:
    int superEggDrop(int K, int N) {
        vector<int> last,now;
        for(int i = 0 ; i <= N ; i++) last.push_back(i);
        
        for(int i = 2 ; i <= K ; i++){
            now = vector<int>{0};
            for(int j = 1 ; j < last.size() ; j ++){
                int pos = now.back()+last[j-1] + 1;
                now.push_back(pos);
                if(now.back() >= N) {
                    *(now.end()-1) = N;
                    break;
                }
            }
            last = now;      

        } 
        return last.size() - 1;
    }
};