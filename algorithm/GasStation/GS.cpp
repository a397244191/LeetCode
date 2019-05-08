class Solution {
public:
    int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
        int b = 0, l = 0,t = 0,use = 0;
        do{
            t += gas[use] - cost[use];
            if(t < 0){
                b--;
                if(b < 0) b = gas.size() - 1;
                use = b;
            } else {
                l++;
                if(l >= gas.size()) l = 0;
                use = l;
            }
        }while(b != l);
        if(t < 0) return -1;
        else return b;
    }
};