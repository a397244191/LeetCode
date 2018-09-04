class KthLargest {
public:
    vector<int> smallHeap;
    int size;
    int kNum;
    KthLargest(int k, vector<int> nums) {
        int len = nums.size();
        size = 0;
        kNum = k;
        for(int i = 0 ; i < len ; i++) {
            add(nums[i]);
        }
    }
    
    int add(int val) {
        if(size == kNum && val < smallHeap[0]) return smallHeap[0];
        size += 1;
        smallHeap.push_back(val);
        bubbleUp(size - 1);
        if(size > kNum)
            Pop();
        return smallHeap[0];
    }
    
    void bubbleUp(int now){
        if(now == 0) return;
        while(smallHeap[now] < smallHeap[(now-1)/2] ) {
                swap(smallHeap[now],smallHeap[(now-1)/2]);
                now = (now-1)/2;
        }
    }
    
    void Pop(){
        int i = 0;
        size -= 1;
        smallHeap[0] = smallHeap[size];
        smallHeap.pop_back();
        while(i*2+1 < size) {
            if(i*2+2 >= size || (smallHeap[i*2+1] <= smallHeap[i*2+2] && smallHeap[i] > smallHeap[i*2+1])) {
                swap(smallHeap[i],smallHeap[i*2+1]);
                i = i*2+1;
            } else if(smallHeap[i*2+1] > smallHeap[i*2+2] && smallHeap[i] > smallHeap[i*2+2]){
                swap(smallHeap[i],smallHeap[i*2+2]);
                i = i*2+2;
            } else break;
        }
    }
};

/**
 * Your KthLargest object will be instantiated and called as such:
 * KthLargest obj = new KthLargest(k, nums);
 * int param_1 = obj.add(val);
 */