class Solution {
public:
    bool reachingPoints(int sx, int sy, int tx, int ty) {
        while(sx < tx && sy < ty) {
            if(tx > ty) tx %= ty;
            else ty %= tx;
        }
        return (sx == tx && (ty-sy) % sx == 0) || (sy == ty && (tx-sx) % sy == 0);
    }
};