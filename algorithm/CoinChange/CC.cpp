class Solution {
public:
    int coinChange(vector<int>& coins, int amount) {

        vector<int> record(amount+1,0);
        for(int i = 0 ; i < coins.size() ; i++) {
            for(int j = 0 ; j <= amount ; j++) {
                if(j + coins[i] <= amount) {
                    if(j != 0 && record[j] == 0);
                    else if(record[j+coins[i]] == 0) record[j+coins[i]] = record[j] + 1;
                    else record[j+coins[i]] = min(record[j+coins[i]],record[j] + 1);
                } else break;
            }
        }
        if(amount != 0 && record[amount] == 0)
            return -1;
        else return record[amount];
    }
};