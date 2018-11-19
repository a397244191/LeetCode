class Solution {
public:
    int removeBoxes(vector<int>& boxes) {
        
        for(int i = 0 ; i < 100 ; i++)
            for(int j = 0 ; j < 100 ;j++)
                for(int k = 0 ; k<100 ; k++) DP[i][j][k] = 0;
        
        return DFS(0,boxes.size()-1,0,boxes);
    }
    int DFS(int head,int tail,int rep,vector<int>& boxes) {
        if(head > tail) return 0;
        else if(DP[head][tail][rep]) return DP[head][tail][rep];
        while(tail > head && boxes[tail] == boxes[tail-1]) {
            tail--;
            rep++;
        }
        DP[head][tail][rep] = DFS(head,tail-1,0,boxes) + (rep+1) * (rep+1);
        for(int i = head ; i < tail ; i++) {
            if(boxes[i] == boxes[tail]) {
                DP[head][tail][rep] = max(DP[head][tail][rep],DFS(head,i,rep+1,boxes) + DFS(i+1,tail-1,0,boxes));
            }
        }
        return DP[head][tail][rep];
    }
private:
    int DP[100][100][100];
};