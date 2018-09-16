class FreqStack {
    map<int,stack<int>> table;
    map<int,int> freq;
    int maxfreq;
public:
    FreqStack() {
        maxfreq = 0;
    }
    
    void push(int x) {
        if(freq.find(x) == freq.end()) freq[x] = 0;
        freq[x]++;
        table[freq[x]].push(x);
        maxfreq = max(maxfreq,freq[x]);
    }
    
    int pop() {
        int n = table[maxfreq].top();
        table[maxfreq].pop();
        freq[n]--;
        if(table[maxfreq].empty()) maxfreq--;
        return n;
    }
};


/**
 * Your FreqStack object will be instantiated and called as such:
 * FreqStack obj = new FreqStack();
 * obj.push(x);
 * int param_2 = obj.pop();
 */