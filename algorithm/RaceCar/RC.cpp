
class Solution {
public:
    int racecar(int target) {
        target =11;
        vector<int> Inum;
        Inum.push_back(0);
        Inum.push_back(1);
        
        while(Inum.size() <= target) {

            int pos = Inum.size() - 1;
            vector<int> inc = {};
            vector<int> dec = {};
            
            for(int i = 1 ; i < Inum.size() ; i++){
                inc.push_back(Inum[i]);
                dec.push_back(Inum[Inum.size() - i]);
            }

            for(int i = 0 ; i < inc.size() ; i++)
                Inum.push_back(Inum[pos]+2+min(inc[i],dec[i]));
            

            int speed = 2;
            for(int i = pos - 1 ; i >= pos*3/4 ; ){
                for(int j = 0 ; j < inc.size() ; j++){
                    Inum[i + j + 1] = min(Inum[i + j + 1],Inum[i]+1 + inc[j]);
                }
                i -= speed;
                speed *= 2;
            }
            Inum.push_back(Inum[pos] + 1);
            
        }

        return Inum[target];
    }
};