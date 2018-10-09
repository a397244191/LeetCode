class StockSpanner {
public:
    StockSpanner() {
        
    }
    
    int next(int price) {
        if(prices.empty()){
            prices.push_back(price);
            spans.push_back(1);
            return spans.back();
        }
        int last = prices.size() - 1;
        prices.push_back(price);
        while(last >= 0 && price >= prices[last]) {
            last -= spans[last];
        }
        spans.push_back(prices.size() - last - 1);
        return spans.back();
    }
    vector<int> prices;
    vector<int> spans;
};

/**
 * Your StockSpanner object will be instantiated and called as such:
 * StockSpanner obj = new StockSpanner();
 * int param_1 = obj.next(price);
 */