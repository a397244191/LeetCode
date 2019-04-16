class Solution {
public:
    vector<int> searchRange(vector<int>& nums, int target) {
        int first = -1,last = -1;
        first = BSearch(nums,target,true);
        if(first >= 0) last = BSearch(nums,target,false);
        return vector<int>{first,last};
    }
    int BSearch(vector<int>& num, int target, bool findFirst) {
        int head = 0, tail = num.size() - 1;
        int use = head;
        while(head <= tail) {
            use = (head + tail) / 2;
            if(num[use] < target || (!findFirst && num[use] == target)) head = use + 1;
            else if(num[use] >= target) tail = use - 1;
        }
        if(tail >= 0 && num[tail] == target) return tail;
        else if(head < num.size() && num[head] == target) return head;
        else return  -1 ;
    }
};